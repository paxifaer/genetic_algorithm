//
// Created by Parsifal on 2022/10/13.
//

#ifndef GENETIC_SIXINITIALIZE_H
#define GENETIC_SIXINITIALIZE_H
#include <iostream>
#include <memory>
#include <vector>
using namespace std;

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
    Up,Left,LeftUp,RightUp,OpponentUp,OpponentLeft,OpponentLeftUp,OpponentRightUp
};
struct DirectionBoardElement{
    int num;
    int left_enemy;
    int right_enemy;
    DirectionBoardElement():left_enemy(-1),right_enemy(-1),num(0){}
};
struct PieceDirection{
    std::vector<DirectionBoardElement>direction_piece_num;
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
    int opponent_player;
    std::vector<std::vector<int>> general_checkerboard;
    std::vector<std::vector<PieceDirection>> direction_checkerboard;
    std::vector<int> gene;
    Point real_six;
    Point opponent_six;
    Point max_pos;
    TemporaryData():target_num(6),max_score(0), real_six{-1,-1},opponent_six{-1,-1}, max_pos{-1,-1}{};
};

class InitParameter {
public:
    void InitPopulation(shared_ptr<TrainPiectElement> board);
    void InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board);
    void InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board);
    void InitializePieceDirectionSpace(std::shared_ptr<TemporaryData> tem);
    void InitializeDirectionBoard(int &position_x,int &pisition_y,std::shared_ptr<TemporaryData> tem);
    void InitializeDirectionBoardForOpponent(int &position_x,int &pisition_y,std::shared_ptr<TemporaryData> tem);
    void InitializeDirectionBoardOfEnemyNum(int &position_x,int &pisition_y,std::shared_ptr<TemporaryData> tem);

    virtual ~InitParameter();
};
#endif //GENETIC_SIXINITIALIZE_H
