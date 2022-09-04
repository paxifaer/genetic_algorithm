//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
#include "../../GenerateIterate/GenerateIterate.h"
#include "../../EasyThreadPool/easythreadpool.h"
#include <numeric>
#include <unordered_map>
#include <map>
struct Point            //������Ľṹ��?
{
    int x, y;
};

 enum class Gene{
    huowu = 0,
    mianwu,
    huosi,miansi,huosan,miansan, huoer,mianer,
    adaptability 
};

enum class IterateType{
    ForTrain=0,
    ForPlay,
    HasData
};
enum class Direction{
    Up,Left,LeftUp,RightUp
};
struct PieceDirection{
    std::vector<int>direction_piece_num;
    std::vector<int>direction_piece_type;//活死
    long long int score;

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
    int target_num;
    int len;
    long long int max_score;
    std::vector<std::vector<int>> general_checkerboard;
    std::vector<std::vector<PieceDirection>> direction_checkerboard;
    std::vector<int> gene;
    Point six;
    Point max_pos;
    TemporaryData():target_num(6),max_score(0), six{-1,-1}, max_pos{-1,-1}{};
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

    Point AI(std::shared_ptr<TemporaryData> tem);
    void SelectionOfChampions(const std::vector<std::vector<int>> & population) ;
    void MakeChampion(std::shared_ptr<TrainPiectElement> board) ;

    void ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                    int checkerboard_piece_num1[][1700]) ;

    void Train(std::shared_ptr<TrainPiectElement> &board) ;

    int PopulationPlayAGame(const int &player_gene_pos1,const int &player_gene_pos2,const std::shared_ptr<TrainPiectElement> board) ;

//    void CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) ;
    void SignalCommunication();
    void SignalCommunicationThread(std::vector<int> Chromosome,std::string str);
    void Play(int &type,std::shared_ptr<TrainPiectElement> board);
    void MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulation(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board);
private:
    void GetPKQueue(std::vector<int> &pk_queue);
    void PopulationContest(std::shared_ptr<TrainPiectElement> board);
    static void SingleContest(int &player1,int &player2,std::shared_ptr<TrainPiectElement> board,std::unordered_map<int,int> &ma);
    void UpdateNextRoundQueue(std::vector<int> &pk_queue,std::unordered_map<int,int> &ma);
    void SelectChampion(std::shared_ptr<TrainPiectElement> board,std::vector<int> &pk_queue);
//    void ReproduceTheNextGeneration(std::shared_ptr<TrainPiectElement> board);
    void CacheTemporaryDate(const std::shared_ptr<TrainPiectElement> board,std::shared_ptr<TemporaryData> tem,const int &player_gene_pos);
    void PlayStrategy(std::shared_ptr<TemporaryData> tem);
    void UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem,int &player);
    void FindMaxAndAddScore(std::shared_ptr<TemporaryData> tem,int &x,int &y);
    void UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem,int &player);
    int GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int type,int &x,int &y);
    int GetPieceType(std::shared_ptr<TemporaryData> tem,int &player,int type,int &x,int &y);
    void InitializePieceDirectionSpace(std::shared_ptr<TemporaryData> tem);
    long long int GetScore(std::shared_ptr<TemporaryData> tem,int &x,int &y,int direction);
};

#endif //GENETICALGORITHM_SIXPIECE_H
