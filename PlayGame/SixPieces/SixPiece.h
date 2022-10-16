//
// Created by Parsifal on 2022/6/17.
//

#ifndef GENETICALGORITHM_SIXPIECE_H
#define GENETICALGORITHM_SIXPIECE_H

#include <iostream>
#include <vector>
#include "../../GenerateIterate/GenerateIterate.h"
#include "../../EasyThreadPool/easythreadpool.h"
#include "SixInitialize.h"
#include <numeric>
#include <unordered_map>
#include <map>
#include <mutex>




class SixPiece :public General,public InitParameter{
   public:

    mutex read;

    void MakeChampion(shared_ptr<TrainPiectElement> board);
    int PopulationPlayAGame(const int &player_gene_pos1,const int &player_gene_pos2,const std::shared_ptr<TrainPiectElement> board) ;
    void SignalCommunication();
    void MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board);


//    for test
    void DisPlayBoard(std::vector<std::vector<int>> general_checkerboard);
    void DisplayScore(std::shared_ptr<TemporaryData> tem);

    void GetPKQueue(std::vector<int> &pk_queue);

    void CacheTemporaryDate( std::shared_ptr<TrainPiectElement> board,std::shared_ptr<TemporaryData> tem,const int &player_gene_pos);

    void SetRecord(Point &pos,std::shared_ptr<TemporaryData> tem_player1,std::shared_ptr<TemporaryData> tem_player2);
    virtual ~SixPiece();
//private:
    void PopulationContest(std::shared_ptr<TrainPiectElement> board);
    void SingleContest(const int player1,const int player2,std::shared_ptr<TrainPiectElement> board,std::unordered_map<int,int> &ma);
    void UpdateNextRoundQueue(std::vector<int> &pk_queue,std::unordered_map<int,int> &ma);
    void SelectChampion(std::shared_ptr<TrainPiectElement> board,std::vector<int> &pk_queue);

    void UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem);
    void FindMaxAndAddScore(std::shared_ptr<TemporaryData> tem,int &x,int &y);
    void UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem);
    int GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int type,int &x,int &y);
    int GetPieceTypeForLeft(std::shared_ptr<TemporaryData> tem, int &player, int type,const int &x,const int &y);
    int GetPieceTypeForRight(std::shared_ptr<TemporaryData> tem, int &player, int type,const int &x,const int &y);

    long long int GetScore(std::shared_ptr<TemporaryData> tem,int &x,int &y,int direction);
    void CalCulateScoreForNowPlayer(std::shared_ptr<TemporaryData> tem);
    void CalCulateScoreForOppoNentPlayer(std::shared_ptr<TemporaryData> tem);

    void ShowChampion(std::shared_ptr<TrainPiectElement> board);
    void GetStepXStepY( int &step_x, int &step_y ,int &type);



};

#endif //GENETICALGORITHM_SIXPIECE_H
