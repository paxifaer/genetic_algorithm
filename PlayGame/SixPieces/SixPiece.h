//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
#include "../../GenerateIterate/GenerateIterate.h"
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
enum  Gene{
    huowu = 0,
    chongwu,
    shuanghuosi,
    danhuosi,miansi,huosan,miansan, huoer,
    adaptability 
};

class SixPiece :public General{
   public: 
    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> champion;//�ھ�����
    std::vector<int> global_chromosome[21];
    std::vector<std::vector<int>> checkerboard{20};
    std::vector<std::vector<int>> checkerboard_piece_num{3};
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
    void Championships(std::vector<std::vector<int>>  &checkerboard1,std::vector<std::vector<int>> & checkerboard_piece_num1, int player) ;

    void ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                    int checkerboard_piece_num1[][1700]) ;

    void Train(std::vector<std::vector<int>> & checkerboard, std::vector<std::vector<int>> & checkerboard_piece_num,  int &train_time,const int & winner,const int & player) ;

    int PopulationPlayAGame(std::vector<int> population1, std::vector<int> population2, const std::vector<std::vector<int>> &checkerboard,
                             const std::vector<std::vector<int>> &checkerboard_piece_num) ;

    void CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) ;
    void SignalCommunication();
    void SignalCommunicationThread(std::vector<int> Chromosome,std::string str);
};

#endif //GENETICALGORITHM_SIXPIECE_H
