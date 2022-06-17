//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
struct Point            //������Ľṹ��
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
enum check{
    huowu;
    chongwu;
    shuanghuosi;
    danhuosi;miansi;huosan;miansan; huoer;
    adaptability ;
};

class SixPiece {
    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> champion;//�ھ�����
    std::vector<int> global_chromosome[21];
    void Init(int checkerboard[][20], int checkerboard_piece_num[][1700]);

    void Record(int checkerboard[][20], int checkerboard_piece_num[3][1700], const int player, int x_position,
                int y_position) ;
    int WhoIsWinner(int checkerboard_piece_num[][1700], const int player) ;                  //ʤ���ж�

    void Grade(const int checkerboard[][20], const int checkerboard_piece_num[][1700], int table[][20], const int ply,
               chromosome gene);       //�������ֵĳ��򣬸�������ÿ����һ���ķ���

    void Search(int table[][20], int player, int &x, int &y, int checkerboard[][20]);       //�������� �ҳ����ֱ��з�ֵ����λ��


    Point AI(int checkerboard[][20], int checkerboard_piece_num[][1700], int player, int &winner,
             chromosome r1);
    void Championships(int checkerboard1[][20], int checkerboard_piece_num1[][1700], int player) ;

    void ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                    int checkerboard_piece_num1[][1700]) ;

    void Train(int checkerboard[][20], int checkerboard_piece_num[][1700], int train_time, int winner, int player) ;

    int PopulationPlayAGame(chromosome population1, chromosome population2, int checkerboard[][20],
                            int checkerboard_piece_num[][1700]) ;


};

#endif //GENETICALGORITHM_SIXPIECE_H
