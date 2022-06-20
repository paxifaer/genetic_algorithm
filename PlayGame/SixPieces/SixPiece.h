//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
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

class SixPiece {
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
    void Search(int table[][20], int player, int &x, int &y, int checkerboard[][20]);       //�������� �ҳ����ֱ��з�ֵ����λ��


    Point AI(int checkerboard[][20], int checkerboard_piece_num[][1700], int player, int &winner,
             chromosome r1);
    void SelectionOfChampions(std::vector<int> population[20]) ;
    void Championships(int checkerboard1[][20], int checkerboard_piece_num1[][1700], int player) ;

    void ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                    int checkerboard_piece_num1[][1700]) ;

    void Train(int checkerboard[][20], int checkerboard_piece_num[][1700], int train_time, int winner, int player) ;

    int PopulationPlayAGame(std::vector<int> population1, std::vector<int> population2, int checkerboard[][20],
                            int checkerboard_piece_num[][1700]) ;
    void CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) ;

};

#endif //GENETICALGORITHM_SIXPIECE_H
