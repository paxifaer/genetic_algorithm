//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
#include "../../GenerateIterate/GenerateIterate.h"
#include "../../EasyThreadPool/easythreadpool.h"
struct Point            //������Ľṹ��?
{
    int x, y;
};

struct chromosome {
    int huowu;
    int chongwu;
    int shuanghuosi;
    int danhuosi, miansi, huosan, miansan, huoer;

    int adaptability = 0;

};
 enum class Gene{
    huowu = 0,
    chongwu,
    shuanghuosi,
    danhuosi,miansi,huosan,miansan, huoer,
    adaptability 
};

enum class IterateType{
    ForTrain=0,
    ForPlay,
    HasData
};
enum class PieceDirection{
    Up = 0,
    Left,
    LeftUp,
    RightUp
};
//struct PieceElement
//        {
//    std::vector<std::vector<int>> general_checkerboard;
//    std::vector<std::vector<int>>  checkerboard;
//    std::vector<std::vector<int>>  checkerboard_piece_num;
//    std::vector<std::vector<int>> population;
//    std::vector<std::vector<int>> champion;
//    int population_num;
//    int champaion_num;
//    int train_time;
//    int  winner;
//    int  player;
//};

struct TrainPiectElement
{
    int  player;
    int population_num;
    int champaion_num;
    int train_time;
    int  winner;
    int iterate_type;
    int convergence_step;
    int contest_round;
    std::vector<std::vector<int>> general_checkerboard;

    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> champion;
    std::vector<std::vector<int>> checkerboard;
    std::vector<std::vector<int>> checkerboard_piece_num;

};
struct TemporaryData
{
    std::vector<std::vector<int>> general_checkerboard;
    std::vector<std::vector<std::vector<int>>> direction_checkerboard;
    int convergence_step;
};
class SixPiece :public General{
   public: 

    void Init();

    void Record(std::vector<std::vector<int>> &checkerboard, std::vector<std::vector<int>> &checkerboard_piece_num, const int player, int x_position,
                int y_position) ;
    int WhoIsWinner(const std::vector<std::vector<int>> &checkerboard_piece_num, const int &player) ;                  //ʤ���ж�

    void Grade(const std::vector<std::vector<int>> &checkerboard, const std::vector<std::vector<int>> &checkerboard_piece_num, std::vector<std::vector<int>>& table, const int ply,
               const chromosome &gene);       //棋盘评分的程序，给予棋盘每个点一定的分数
    
    int CheckCheckerBoard(const std::vector<std::vector<int>> &checkerboard_piece_num,const int &step,const int &quadrant,const int &player,const int &emeny,const Point & point);

    void CalculatQuardrantScore(std::vector<std::vector<int>> &table, const chromosome &gene,const int &temp,const int &num,const Point & point);
    void Search(const std::vector<std::vector<int>>& table, const int &player, int &x, int &y, const std::vector<std::vector<int>> &checkerboard);  //搜索函数 找出评分表中分值最大的位置

    chromosome ChromosomeSwitch(const std::vector<int> &population);

    Point AI(const std::vector<std::vector<int>> &checkerboard, const std::vector<std::vector<int>> &checkerboard_piece_num, int player, int &winner,
             chromosome r1);
    void SelectionOfChampions(const std::vector<std::vector<int>> & population) ;
    void MakeChampion(std::shared_ptr<TrainPiectElement> board) ;

    void ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                    int checkerboard_piece_num1[][1700]) ;

    void Train(std::shared_ptr<TrainPiectElement> &board) ;

    int PopulationPlayAGame(std::shared_ptr<TemporaryData> iterate_basic_data) ;

//    void CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) ;
    void SignalCommunication();
    void SignalCommunicationThread(std::vector<int> Chromosome,std::string str);
    void Play(int &type,std::shared_ptr<TrainPiectElement> board);
    void MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulation(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board);
private:
    std::vector<int> GetPKQueue(const std::shared_ptr<TrainPiectElement> board);
    void PopulationContest(int &play1,int &player2,std::shared_ptr<TrainPiectElement> board);
};

#endif //GENETICALGORITHM_SIXPIECE_H
