//
// Created by Parsifal on 2022/10/13.
//

#include "SixInitialize.h"

void InitParameter::InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board) {
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

    for (int j1 = 0; j1 < 8; j1++) {
        for (int j2 = 0; j2 < 8; j2++) {
            for (int j3 = 0; j3 < 4; j3++) {
                for (int j4 = 0; j4 < 4; j4++) {
                    for (int j5 = 0; j5 < 4; j5++) {
                        for (int j6 = 0; j6 < 4; j6++) {
                            for (int j7 = 0; j7 < 2; j7++) {
                                for (int j8 = 0; j8 < 2; j8++) {
                                    board->population.push_back({
                                                                        huowu[j1], chongwu[j2], shuanghuosi[j3],
                                                                        danhuosi[j4], miansi[j5], huosan[j6],
                                                                        miansan[j7], huoer[j8]
                                                                });
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}



void InitParameter::InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board) {
    int i1 = 1500, i2 = 400, i3 = 300, i4 = 150, i5 = 75, i6 = 30, i7 = 6, i8 = 4;
    int i1_step = 200, i2_step = 100, i3_step = 80, i4_step = 40, i5_step = 20, i6_step = 8, i7_step = 3, i8_step = 2;
    std::vector<int> huowu, chongwu, shuanghuosi, danhuosi, miansi, huosan, miansan{i7, i7 - i7_step}, huoer{i8, i8 -
                                                                                                                 i8_step};
    for (int i = 0; i <= 1; i++) {
        huowu.emplace_back(i1 - i * i1_step);
        chongwu.emplace_back(i2 - i * i2_step);
    }
    for (int i = 1; i <= 2; i++) {
        huowu.emplace_back(i1 + i * i1_step);
        chongwu.emplace_back(i2 + i * i2_step);
    }
    for (int i = 0; i <= 1; i++) {
        shuanghuosi.emplace_back(i3 - i * i3_step);
        danhuosi.emplace_back(i4 - i * i4_step);
        miansi.emplace_back(i5 - i * i5_step);
        huosan.emplace_back(i6 - i * i6_step);
    }


    for (int j1 = 0; j1 < 4; j1++) {
        for (int j2 = 0; j2 < 4; j2++) {
            for (int j3 = 0; j3 < 2; j3++) {
                for (int j4 = 0; j4 < 2; j4++) {
                    for (int j5 = 0; j5 < 2; j5++) {

                        for (int j6 = 0; j6 < 2; j6++) {
                            for (int j7 = 0; j7 < 2; j7++) {
                                for (int j8 = 0; j8 < 2; j8++) {
                                    board->population.push_back({
                                                                        huowu[j1], chongwu[j2], shuanghuosi[j3],
                                                                        danhuosi[j4], miansi[j5], huosan[j6],
                                                                        miansan[j7], huoer[j8]
                                                                });
                                }
                            }
                        }
                    }
                }
            }
        }
    }

}



void InitParameter::InitializePieceDirectionSpace(std::shared_ptr<TemporaryData> tem) {
    if (tem->direction_checkerboard[0][0].direction_piece_num.empty()) {
        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                tem->direction_checkerboard[i][j].direction_piece_num.resize(8);
                tem->direction_checkerboard[i][j].direction_piece_type.resize(8);
            }
        }
    }
}


void InitParameter::InitializeDirectionBoard(int &i, int &j, std::shared_ptr<TemporaryData> tem) {
    if (i > 0 && tem->general_checkerboard[i - 1][j] == tem->now_player) {
        int num = tem->direction_checkerboard[i -
                                              1][j].direction_piece_num[static_cast<int>(Direction::Left)].num;//迭代每一步棋子数量
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)].num = real_num;
        while (--num && (i - num) >= 0) {
            tem->direction_checkerboard[i -
                                        num][j].direction_piece_num[static_cast<int>(Direction::Left)].num = real_num;
        }
    } else if (i == 0 || (i > 0 && tem->general_checkerboard[i - 1][j] != tem->now_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)].num = 1;
    }

    if (j > 0 && tem->general_checkerboard[i][j - 1] == tem->now_player) {
        int num = tem->direction_checkerboard[i][j -
                                                 1].direction_piece_num[static_cast<int>(Direction::Up)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)].num = real_num;
        while (--num && (j - num) >= 0) {
            tem->direction_checkerboard[i][j -
                                           num].direction_piece_num[static_cast<int>(Direction::Up)].num = real_num;
        }
    } else if (j == 0 || (j > 0 && tem->general_checkerboard[i][j - 1] != tem->now_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)].num = 1;
    }

    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == tem->now_player) {
        int num = tem->direction_checkerboard[i - 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::LeftUp)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)].num = real_num;
        while (--num && (i - num) >= 0 && (j - num) >= 0) {
            tem->direction_checkerboard[i - num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::LeftUp)].num = real_num;
        }
    } else if (j == 0 || i == 0 || (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] != tem->now_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)].num = 1;
    }

    if (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] == tem->now_player) {
        int num = tem->direction_checkerboard[i + 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::RightUp)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)].num = real_num;
        while (--num && (i + num) < tem->len && (j - num) >= 0) {
            tem->direction_checkerboard[i + num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::RightUp)].num = real_num;
        }
    } else if (j == 0 || i == tem->len - 1 ||
               (i < tem->len - 1 && j > 0 && tem->general_checkerboard[i + 1][j - 1] != tem->now_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)].num = 1;
    }

}

void InitParameter::InitializeDirectionBoardForOpponent(int &i, int &j, std::shared_ptr<TemporaryData> tem) {
    if (i > 0 && tem->general_checkerboard[i - 1][j] == tem->opponent_player) {
        int num = tem->direction_checkerboard[i -
                                              1][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num;//迭代每一步棋子数量
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num = real_num;
        while (--num && (i - num) >= 0) {
            tem->direction_checkerboard[i -
                                        num][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num = real_num;
        }
    } else if (i == 0 || (i > 0 && tem->general_checkerboard[i - 1][j] != tem->opponent_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num = 1;
    }

    if (j > 0 && tem->general_checkerboard[i][j - 1] == tem->opponent_player) {
        int num = tem->direction_checkerboard[i][j -
                                                 1].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num = real_num;
        while (--num && (j - num) >= 0) {
            tem->direction_checkerboard[i][j -
                                           num].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num = real_num;
        }
    } else if (j == 0 || (j > 0 && tem->general_checkerboard[i][j - 1] != tem->opponent_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num = 1;
    }

    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == tem->opponent_player) {
        int num = tem->direction_checkerboard[i - 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num = real_num;
        while (--num && (j - num) >= 0 && (i - num) >= 0) {
            tem->direction_checkerboard[i - num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num = real_num;
        }
    } else if (j == 0 || i == 0 ||
               (i > 0 && j > 0 && tem->general_checkerboard[i - 1][j - 1] != tem->opponent_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num = 1;
    }

    if (j > 0 && i < tem->len - 1 && (tem->general_checkerboard[i + 1][j - 1] == tem->opponent_player)) {
        int num = tem->direction_checkerboard[i + 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num = real_num;
        while (--num && (i + num) < tem->len && (j - num) >= 0) {
            tem->direction_checkerboard[i + num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num = real_num;
        }
    } else if (j == 0 || i == tem->len - 1 ||
               (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] != tem->opponent_player)) {
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num = 1;
    }
}
void InitParameter::InitializeDirectionBoardOfEnemyNum(int &position_x,int &position_y,std::shared_ptr<TemporaryData> tem)
{
    for(int i=0;i<=7;i++)
    {
        tem->direction_checkerboard[position_x][position_y].direction_piece_num[i].right_enemy = -1;
        tem->direction_checkerboard[position_x][position_y].direction_piece_num[i].left_enemy = -1;
    }
}



void InitParameter::InitPopulation(std::shared_ptr<TrainPiectElement> board) {
    switch (board->iterate_type) {
        case static_cast<int> (IterateType::ForPlay):
            InitPopulationForPlay(board);
            break;
        case static_cast<int> (IterateType::ForTrain):
            InitPopulationForTrain(board);
            break;
        default:
            break;
    }
}
