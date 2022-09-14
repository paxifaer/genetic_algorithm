//
// Created by Parsifal on 2022/9/14.
//
#include "SixPiece.h"

using namespace std;

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

int main()
{
    TestInitPopulationForTrain();

    std::vector<std::vector<int>> general_checkerboard;

    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> champion;
    std::vector<std::vector<int>> checkerboard;
    std::vector<std::vector<int>> checkerboard_piece_num;


    return 0;
}
