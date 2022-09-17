//
// Created by Parsifal on 2022/9/14.
//
#include "SixPiece.h"

using namespace std;

void InitChampion(std::shared_ptr<TrainPiectElement> board) {

    int i1 = 1500, i2 = 400, i3 = 300, i4 = 150, i5 = 75, i6 = 30, i7 = 6, i8 = 4;
    int i1_step = 200, i2_step = 100, i3_step = 80, i4_step = 40, i5_step = 20, i6_step = 8, i7_step = 3, i8_step = 2;
    std::vector<int> huowu, chongwu, shuanghuosi, danhuosi, miansi, huosan, miansan{i7, i7 - i7_step}, huoer{i8, i8 -
                                                                                                                 i8_step};
    for (int i = 0; i <= 3; i++) {
        huowu.emplace_back(i1 - i * i1_step);
        chongwu.emplace_back(i2 - i * i2_step);
    }
    for (int i = 1; i <= 4; i++) {
        huowu.emplace_back(i1 + i * i1_step);
        chongwu.emplace_back(i2 + i * i2_step);
    }
    for (int i = 0; i <= 1; i++) {
        shuanghuosi.emplace_back(i3 - i * i3_step);
        danhuosi.emplace_back(i4 - i * i4_step);
        miansi.emplace_back(i5 - i * i5_step);
        huosan.emplace_back(i6 - i * i6_step);
    }
    for (int i = 1; i <= 2; i++) {
        shuanghuosi.emplace_back(i3 + i * i3_step);
        danhuosi.emplace_back(i4 + i * i4_step);
        miansi.emplace_back(i5 + i * i5_step);
        huosan.emplace_back(i6 + i * i6_step);
    }

    for (int j1 = 0; j1 < 4; j1++) {
        for (int j2 = 0; j2 < 4; j2++) {
            for (int j3 = 0; j3 < 4; j3++) {
                {
                    board->population.push_back({
                                                        huowu[j1], chongwu[j2], shuanghuosi[j3],
                                                        danhuosi[0], miansi[0], huosan[0],
                                                        miansan[0], huoer[0]
                                                });
                }
            }
        }
    }

}
void TestInitPopulationForTrain()
{
    SixPiece test;
    std::shared_ptr<TrainPiectElement> board = make_shared<TrainPiectElement>();
    test.InitPopulationForTrain(board);
    cout<<board->population.size()<<" "<<board->population[0].size();
//    for(int i=0;i<board->population.size();i++)
//    {
//        for(int j=0;j<board->population[0].size();j++)
//        {
//            cout<<board->population[i][j]<<" ";
//        }
//        cout<<endl;
//    }
}

std::shared_ptr<TrainPiectElement> MakeTestData()
{
    std::shared_ptr<TrainPiectElement> board = make_shared<TrainPiectElement>();
    InitChampion(board);
    SixPiece test;
    test.InitPopulationForTrain(board);

    board->population_num = board->population.size();
    board->convergence_step=50;
    board->contest_round = 10;
    board->iterate_type=0;
    board->match_times = 3;
    board->champaion_num=64;
    board->general_checkerboard.resize(19,vector<int>(19));
    board->general_checkerboard[7][7] = 1;
    return board;
}

void TestRandomQueue()
{
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    SixPiece test;
    std::vector<int> pk_queue;
    pk_queue.resize(board->population_num);
//    iota(pk_queue.begin(), pk_queue.end(), 0);
    test.GetPKQueue(pk_queue);
    for(int i=0;i<pk_queue.size();i++)
        cout<<pk_queue[i]<<" ";
}
int main()
{
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    SixPiece test;
    test.MakeChampion(board);
//      TestRandomQueue();



    return 0;
}
