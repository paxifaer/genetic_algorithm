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
class TestParallel{
public:
    int test=10;
    void sss()
    {
        ParallelCalculate pool{3};

        for(int i=0;i<100;i++)
        pool.commit([&](){cal(test,test);});
        int i=1;
        pool.ParallelAccum(i);
    }
    void cal(int a,int a1)
    {
        int i=0,j=0;
        for( i=0;i<10000;i++)
        {
            for(j=0;j<1000;j++)
            {}
        }
        cout<<i+j<<endl;
    }
};

void TestParallelCal()
{
    SixPiece test;
    TestParallel te;
    te.sss();

}

struct test{
    int a;
    vector<int >vec;
};

void FixTempory()
{
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    SixPiece test;
    std::vector<int> pk_queue;
    pk_queue.resize(board->population_num);



    std::shared_ptr<TemporaryData> ply_1st = std::make_shared<TemporaryData>();
    std::shared_ptr<TemporaryData> ply_2st = std::make_shared<TemporaryData>();
//    ply_1st->general_checkerboard = std::move(board->general_checkerboard);
    test.CacheTemporaryDate(board, ply_1st,1);
}

void SetRecord(Point pos,std::shared_ptr<TemporaryData> tem)
{
    tem->general_checkerboard[pos.x][pos.y]=tem->real_player;
}

int TestGetPieceType(std::shared_ptr<TemporaryData> tem, int player, int type, int x, int y)
{

        int sum1 = 1,sum2=1;
        int step_x = 0, step_y = 0;
        int res = 0;
        int opponent_player = player==1?2:1;
        switch (type) {
            case static_cast<int>(Direction::Left):
                step_x = 1;
                step_y = 0;
                break;
            case static_cast<int>(Direction::Up):
                step_x = 0;
                step_y = 1;
                break;
            case static_cast<int>(Direction::LeftUp):
                step_x = 1;
                step_y = 1;
                break;
            case static_cast<int>(Direction::RightUp):
                step_x = 1;
                step_y = -1;
                break;
            case static_cast<int>(Direction::OpponentLeft):
                step_x = 1;
                step_y = 0;
                break;
            case static_cast<int>(Direction::OpponentUp):
                step_x = 0;
                step_y = 1;
                break;
            case static_cast<int>(Direction::OpponentLeftUp):
                step_x = 1;
                step_y = 1;
                break;
            case static_cast<int>(Direction::OpponentRightUp):
                step_x = 1;
                step_y = -1;
                break;
        };

        if ((x - step_x) >= 0 && (y - step_y) >= 0&&(x - step_x) < tem->len && (y - step_y < tem->len)) {
            sum1 += tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type];
        }
        if ((x + step_x) >= 0 && (y + step_y >= 0)&&(x + step_x) < tem->len && (y + step_y < tem->len)) {
            sum2 += tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type];
        }
        int num1 = tem->target_num - sum1;
        int num2 = tem->target_num - sum2;
        while (num1--) {
            if(x - step_x>=0&&x - step_x<tem->len&&y - step_y>=0&&y - step_y<tem->len)
            {
                int find_move_x =
                        step_x * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num1);//step_x maybe -1,1 by direction,
                int find_move_y =
                        step_y * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num1);
                if ((x - find_move_x) >= 0 && (y - find_move_y) >= 0 &&(x - find_move_x) <tem->len && (y - find_move_y) <tem->len&&
                    tem->general_checkerboard[x - find_move_x][y - find_move_y] != opponent_player) {
                    continue;
                } else {
                    res++;
                    break;
                }
            }
        }
        while (num2--) {
            if(x - step_x>=0&&x - step_x<tem->len&&y - step_y>=0&&y - step_y<tem->len)
            {
                int find_move_x =
                        step_x * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num2);
                int find_move_y =
                        step_y * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num2);
                if ((x + find_move_x) < tem->len && (y + find_move_y) < tem->len &&(x + find_move_x) >=0 && (y + find_move_y) >=0 &&
                    tem->general_checkerboard[x + find_move_x][x + find_move_y] != opponent_player) {
                    continue;
                } else {
                    res++;
                    break;
                }
            }
        }
        cout<<res<<endl;
        return res;
}

void TestGetPiece()
{
    SixPiece test;
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    std::shared_ptr<TemporaryData> ply_1st = std::make_shared<TemporaryData>();
    test.CacheTemporaryDate(board, ply_1st,1);
    ply_1st->now_player=1;
    ply_1st->real_player = 1;
    ply_1st->opponent_player=2;
    ply_1st->len = ply_1st->general_checkerboard.size();
    ply_1st->direction_checkerboard.resize(ply_1st->len, std::vector<PieceDirection>(ply_1st->len));

    test.InitializePieceDirectionSpace(ply_1st);
    Point a = {7,7};
    test.SetRecord(a,ply_1st);
//    int i = 7,j=7;

    for (int i = 0; i < ply_1st->len; i++) {
        for (int j = 0; j < ply_1st->len; j++) {
            if (ply_1st->general_checkerboard[i][j] == ply_1st->real_player) {
                if (i > 0 && ply_1st->general_checkerboard[i - 1][j] == ply_1st->real_player) {
                    int num = ply_1st->direction_checkerboard[i -
                                                          1][j].direction_piece_num[static_cast<int>(Direction::Left)];//迭代每一步棋子数量
                    int real_num = num + 1;
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                    while (--num) {
                        ply_1st->direction_checkerboard[i -
                                                    num][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                    }
                } else if (i == 0 || ply_1st->general_checkerboard[i - 1][j] != ply_1st->real_player) {
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = 1;
                }

                if (j > 0 && ply_1st->general_checkerboard[i][j - 1] == ply_1st->real_player) {
                    int num = ply_1st->direction_checkerboard[i][j -
                                                             1].direction_piece_num[static_cast<int>(Direction::Up)];
                    int real_num = num + 1;
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                    while (--num) {
                        ply_1st->direction_checkerboard[i][j -
                                                       num].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                    }
                } else if (j == 0 || ply_1st->general_checkerboard[i][j - 1] != ply_1st->real_player) {
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = 1;
                }

                if (j > 0 && i > 0 && ply_1st->general_checkerboard[i - 1][j - 1] == ply_1st->real_player) {
                    int num = ply_1st->direction_checkerboard[i - 1][j -
                                                                 1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
                    int real_num = num + 1;
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                    while (--num) {
                        ply_1st->direction_checkerboard[i - num][j -
                                                             num].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                    }
                } else if (j == 0 || i == 0 || ply_1st->general_checkerboard[i - 1][j - 1] != ply_1st->real_player) {
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = 1;
                }

                if (j > 0 && i < ply_1st->len - 1 && ply_1st->general_checkerboard[i + 1][j - 1] == ply_1st->real_player) {
                    int num = ply_1st->direction_checkerboard[i + 1][j -
                                                                 1].direction_piece_num[static_cast<int>(Direction::RightUp)];
                    int real_num = num + 1;
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                    while (--num) {
                        ply_1st->direction_checkerboard[i + num][j -
                                                             num].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                    }
                } else if (j == 0 || i == ply_1st->len - 1 || ply_1st->general_checkerboard[i + 1][j - 1] != ply_1st->real_player) {
                    ply_1st->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = 1;
                }

            }
        }
    }



    for (int i = 0; i < ply_1st->len; i++) {
        for (int j = 0; j < ply_1st->len; j++) {
            if (ply_1st->general_checkerboard[i][j] == 0) {

                test.CalCulateScoreForNowPlayer(ply_1st,i,j);
                test.CalCulateScoreForOppoNentPlayer( ply_1st,i,j);
                test.FindMaxAndAddScore(ply_1st, i, j);
            }
            if(ply_1st->real_six.x!=-1||ply_1st->opponent_six.x!=-1)
                break;
        }
    }
}



void TestGetPieceNum()
{
    SixPiece test;
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    std::shared_ptr<TemporaryData> ply_1st = std::make_shared<TemporaryData>();
    test.CacheTemporaryDate(board, ply_1st,1);
    ply_1st->now_player=1;
    ply_1st->real_player = 1;
    ply_1st->opponent_player=2;
    ply_1st->len = ply_1st->general_checkerboard.size();
    ply_1st->direction_checkerboard.resize(ply_1st->len, std::vector<PieceDirection>(ply_1st->len));




    test.InitializePieceDirectionSpace(ply_1st);
    Point a = {7,7};
    ply_1st->general_checkerboard[7][7]=ply_1st->opponent_player;
//    test.SetRecord(a,ply_1st);
    ply_1st->direction_checkerboard[7][7].direction_piece_num[static_cast<int>(Direction::OpponentUp)]= test.GetPieceNum(
            ply_1st, ply_1st->real_player, static_cast<int>(Direction::OpponentUp), a.x, a.y);
    a = {7,8};
    test.SetRecord(a,ply_1st);
    cout<<test.GetPieceNum(ply_1st, ply_1st->opponent_player,static_cast<int>(Direction::OpponentUp),a.x,a.y);
}
void TestSingleContest()
{
    SixPiece test;
    std::shared_ptr<TrainPiectElement> board = MakeTestData();
    std::shared_ptr<TemporaryData> ply_1st = std::make_shared<TemporaryData>();
    test.CacheTemporaryDate(board, ply_1st,1);
    ply_1st->now_player=1;
    ply_1st->real_player = 1;
    ply_1st->opponent_player=2;
    ply_1st->len = ply_1st->general_checkerboard.size();
    ply_1st->direction_checkerboard.resize(ply_1st->len, std::vector<PieceDirection>(ply_1st->len));

    test.InitializePieceDirectionSpace(ply_1st);
    int player_gene_pos1 = 25940; int player_gene_pos2 = 46722;
    std::unordered_map<int, int> ma;
    test.SingleContest(ply_1st->now_player,ply_1st->opponent_player,board,ma);

}
int main()
{
//    std::shared_ptr<TrainPiectElement> board = MakeTestData();
//    SixPiece test;
//    test.MakeChampion(board);
//    FixTempory();
//    TestParallelCal();
//    TestGetPiece();
//    TestGetPieceNum();
    TestSingleContest();
    return 0;
}
