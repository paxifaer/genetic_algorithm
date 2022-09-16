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


struct TrainPiectElement
{
    int population_num;
    int champaion_num;
    int iterate_type;
    int convergence_step;
    int contest_round;
    int match_times;
    std::vector<std::vector<int>> general_checkerboard;
    std::vector<std::vector<int>> population;
    std::vector<std::vector<int>> champion;

};

struct TemporaryData
{
    int target_num;
    int len;
    long long int max_score;
    int real_player;
    int now_player;
    std::vector<std::vector<int>> general_checkerboard;
    std::vector<std::vector<PieceDirection>> direction_checkerboard;
    std::vector<int> gene;
    Point real_six;
    Point opponent_six;
    Point max_pos;
    TemporaryData():target_num(6),max_score(0), real_six{-1,-1},opponent_six{-1,-1}, max_pos{-1,-1}{};
};

class SixPiece :public General{
   public:
    void InitPopulation(shared_ptr<TrainPiectElement> board);

    void MakeChampion(shared_ptr<TrainPiectElement> board);
    int PopulationPlayAGame(const int &player_gene_pos1,const int &player_gene_pos2,const std::shared_ptr<TrainPiectElement> board) ;
    void SignalCommunication();
    void MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board);
private:
    void GetPKQueue(std::vector<int> &pk_queue);
    void PopulationContest(std::shared_ptr<TrainPiectElement> board);
    void SingleContest(int player1,int player2,std::shared_ptr<TrainPiectElement> board,std::unordered_map<int,int> ma);
    void UpdateNextRoundQueue(std::vector<int> &pk_queue,std::unordered_map<int,int> &ma);
    void SelectChampion(std::shared_ptr<TrainPiectElement> board,std::vector<int> &pk_queue);
    void CacheTemporaryDate(const std::shared_ptr<TrainPiectElement> board,std::shared_ptr<TemporaryData> tem,const int &player_gene_pos);
    void UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem);
    void FindMaxAndAddScore(std::shared_ptr<TemporaryData> tem,int &x,int &y);
    void UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem);
    int GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int type,int &x,int &y);
    int GetPieceType(std::shared_ptr<TemporaryData> tem,int &player,int type,int &x,int &y);
    void InitializePieceDirectionSpace(std::shared_ptr<TemporaryData> tem);
    long long int GetScore(std::shared_ptr<TemporaryData> tem,int &x,int &y,int direction);
    void SetRecord(Point &pos,std::shared_ptr<TemporaryData> tem);


};

#endif //GENETICALGORITHM_SIXPIECE_H
