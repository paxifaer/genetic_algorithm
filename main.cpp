//#include "PlayGame/SixPieces/SixPiece.h"
//#include "spdlog/spdlog.h"
//#include "spdlog/sinks/rotating_file_sink.h"
//#include "spdlog/async.h"
//
//#define SPDLOG_FILENAME "log/SixPiece.log"
//#define SPDLOGGERNAME "SixPiece"
//#define LOGGER spdlog::get(SPDLOGGERNAME)
//
////void initspdlog()
////{
////    spdlog::flush_every(std::chrono::seconds(5));
////    auto file_logger = spdlog::rotating_logger_mt<spdlog::async_factory>(SPDLOGGERNAME, SPDLOG_FILENAME, 1024 * 1024 * 200, 5);
////    LOGGER->set_level(spdlog::level::info); // Set global log level to info
////    LOGGER->set_pattern("[%Y-%m-%d %H:%M:%S.%e %^%L%$ %t] %v");
////}
//
//int main()
//{
////    SixPiece a;
////    a.SignalCommunication();
//
//
//
//    return 0;
//}








#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"
#include <iostream>
using namespace std;
using namespace rapidjson;

Document readJsonfile(string path)
{

    rapidjson::Document doc;
    std::ifstream in(path, std::ios::binary);

    if (!in.is_open())
    {   cout<< "file is not open!!";
        return doc;
    }


    IStreamWrapper config(in);
    doc.ParseStream(config);

//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    doc.Accept(writer);

    in.close();
    return doc;
}

string readfile(string path){
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


void writeToJsonFile(string &jsonstr, string filepath)
{
    Document doc ;
    string str= readfile(filepath.c_str());
    doc.Parse(str.c_str());

    rapidjson::Document::AllocatorType &allocator = doc.GetAllocator();
    doc.SetObject();
    string time;
    doc.AddMember("1", "2", allocator);

    doc["1"] = "5";

    string fstr;
    rapidjson::StringBuffer strBuffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strBuffer);
    doc.Accept(writer);
    fstr = strBuffer.GetString();

    fstream fout(filepath,ios::out|ios::trunc);
    fout<<fstr<<endl;
    fout.close();

    std::cout << "writeToJsonFile end" <<std::endl;
}

int main()
{
    string str = "{\n"
                 "  \"max_time\": 22\n"
                 "}";
    string path = "D:\\study\\github\\genetic_algorithm\\1.json";
    cout<<readfile(path);
    writeToJsonFile(str,path);
    return 0;
}