//
// Created by Parsifal on 2022/10/13.
//
#include "SixSelfPlay.h"

string SelfPlay::MakeIterateData(const std::shared_ptr<TrainPiectElement> board)
{
    string str;
    for(int i=0;i<board->champion.size();i++)
    {
        for(int j=0;j<board->champion[0].size();j++)
        {
            str+='_';
            str+=to_string(board->champion[i][j]);
        }
    }
    return str;
}

void SelfPlay::ParseIteratrDate(std::shared_ptr<TrainPiectElement> board,string &str)
{
    int pos=0;
    for(int i=0;i<board->champion.size();i++)
    {
        for(int j=0;j<board->champion[0].size();j++)
        {

            string number;
            if(str!="")
               pos++;
            else
            {
                return ;
            }
               while(str[pos]!='_')
               {
                   number+=str[pos];
                   pos++;
               }
            board->champion[i][j] = stoi(number);
        }
    }
}


string SelfPlay::readfile(string path){
    ifstream  readFile;

    readFile.open(path);  //打开需要操作的文件

    if (readFile.fail())
    {
        cout<<"fail";
        return path;   //说明文件读取失败！
    }

    std::string   sBuffer;

    readFile>>sBuffer;

    return sBuffer;
}

bool SelfPlay::IsConfigEmpty(string path)
{
    rapidjson::Document doc ;
    string str= readfile(path.c_str());
//    cout<<str;
    doc.Parse(str.c_str());
//    doc.SetObject();
    string time ;
    time = doc["max_time"].GetString();
    return time=="0";
}

void SelfPlay::writeToJsonFile( string filepath,const std::shared_ptr<TrainPiectElement> board)
{
    rapidjson::Document doc ;
    rapidjson::Value val;
    string str= readfile(filepath.c_str());
    doc.Parse(str.c_str());

    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
//    doc.SetObject();
    string time = doc["max_time"].GetString();
    doc["max_time"] = val.SetString(to_string(stoi(time)+1).c_str(), allocator);
    string iterate = "time_"+time;
    char* time1 = new char[strlen(iterate.c_str()) + 1];;
    strcpy(time1, iterate.c_str());
    string cache =  MakeIterateData(board);
    doc.AddMember(rapidjson::StringRef(time1), val.SetString(cache.c_str(), allocator), allocator);

    string fstr;
    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
    doc.Accept(writer);
    fstr = strBuffer.GetString();

    fstream fout(filepath,ios::out|ios::trunc);
    fout<<fstr<<endl;
    fout.close();

}


void SelfPlay::WriteData(const std::shared_ptr<TrainPiectElement> board,string path,int sleep_time)
{

    while(true)
    {

        Sleep(sleep_time);
        {
            lock_guard<mutex> lock(read);
            writeToJsonFile(path, board);
            cout<<"write"<<endl;
        }
    }
}

void SelfPlay::ReadData(string filepath, const std::shared_ptr<TrainPiectElement> board) {
    rapidjson::Document doc;
    string str = readfile(filepath.c_str());
    doc.Parse(str.c_str());
    int time = stoi(doc["max_time"].GetString());
    if(time ==0)
    {
        SixPiece test;
        test.InitPopulationForTrain(board);
    }

}
void SelfPlay::Train()
{
    SixPiece test;
    std::shared_ptr<TrainPiectElement> board;
    string path = "D:\\study\\github\\genetic_algorithm\\conf\\TrainData.json";

    int sleep_time = 1000;
    auto RecordData = [&](){
        WriteData(board, path, sleep_time);
    };
    thread write_data(RecordData);
    write_data.detach();

    if(IsConfigEmpty(path))
        board = MakeTestData(test);
    test.MakeChampion(board);


}
std::shared_ptr<TrainPiectElement> SelfPlay::MakeTestData(SixPiece &test)
{
    std::shared_ptr<TrainPiectElement> board = make_shared<TrainPiectElement>();


    board->population_num = 256;
    board->convergence_step=50;
    board->contest_round = 3;
    board->iterate_type=0;
    board->match_times = 3;
    board->champaion_num=64;
    board->general_checkerboard.resize(19,vector<int>(19));
    board->general_checkerboard[7][7] = 1;
    test.InitPopulationForTrain(board);
    return board;
}


int main()
{
    SelfPlay train;
    train.Train();
}