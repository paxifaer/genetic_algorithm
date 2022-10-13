#include "SixPiece.h"
#include <memory>
#include <chrono>
#include <atomic>
void SixPiece::InitPopulationForTrain(std::shared_ptr<TrainPiectElement> board) {
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

void SixPiece::InitPopulationForPlay(std::shared_ptr<TrainPiectElement> board) {
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


void SixPiece::CacheTemporaryDate(std::shared_ptr<TrainPiectElement> board, std::shared_ptr<TemporaryData> tem,
                                  const int &player_gene_pos) {

    tem->general_checkerboard = board->general_checkerboard;
    tem->gene = board->population[player_gene_pos];
}

long long int SixPiece::GetScore(std::shared_ptr<TemporaryData> tem, int &x, int &y, int direction) {
    switch (tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(direction)].num) {
        case 2: {
            switch (tem->direction_checkerboard[x][y].direction_piece_type[static_cast<int>(direction)]) {
                case 0:
                    return tem->gene[static_cast<int>(Gene::huoer)];
                case 1:
                    return tem->gene[static_cast<int>(Gene::mianer)];
                default:
                    return 0;

            }
        }
        case 3: {
            switch (tem->direction_checkerboard[x][y].direction_piece_type[static_cast<int>(direction)]) {
                case 0:
                    return tem->gene[static_cast<int>(Gene::huosan)];
                case 1:
                    return tem->gene[static_cast<int>(Gene::miansan)];
                default:
                    return 0;
            }
        }

        case 4: {
            switch (tem->direction_checkerboard[x][y].direction_piece_type[static_cast<int>(direction)]){
                case 0:
                    return tem->gene[static_cast<int>(Gene::huosi)];
                case 1:
                    return tem->gene[static_cast<int>(Gene::miansi)];
                default:
                    0;
            }
        }
        case 5: {
            switch (tem->direction_checkerboard[x][y].direction_piece_type[static_cast<int>(direction)]) {
                case 0:
                    return tem->gene[static_cast<int>(Gene::huowu)];
                case 1:
                    return tem->gene[static_cast<int>(Gene::mianwu)];
                default:
                    return 0;
            }
        }
    }
    return 0;
}

void SixPiece::FindMaxAndAddScore(std::shared_ptr<TemporaryData> tem, int &x, int &y) {
    if (tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Left)].num >= 6 ||
        tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::LeftUp)].num >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Up)].num >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::RightUp)].num >= 6) {
        if (tem->now_player == tem->real_player)
            tem->real_six = {x, y};
        else
            tem->opponent_six = {x, y};
    }
    tem->direction_checkerboard[x][y].score +=
            GetScore(tem, x, y, 0) + GetScore(tem, x, y, 1) + GetScore(tem, x, y, 2) + GetScore(tem, x, y, 3) +
            GetScore(tem, x, y, 4) + GetScore(tem, x, y, 5) + GetScore(tem, x, y, 6) + GetScore(tem, x, y, 7);

    if (tem->direction_checkerboard[x][y].score > tem->max_score) {

        tem->max_score = tem->direction_checkerboard[x][y].score;
        tem->max_pos = {x, y};
    }

}

void SixPiece::GetStepXStepY( int &step_x, int &step_y ,int &type)
{
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
    }
}

int  SixPiece::GetPieceTypeForLeft(std::shared_ptr<TemporaryData> tem, int &player, int type,const int &x,const int &y) {
    int sum1 = 1;
    int step_x = 0, step_y = 0;
    int res = 0;
    int opponent_player = player == 1 ? 2 : 1;
    GetStepXStepY(step_x,step_y,type);
    if ((x + step_x) >= 0 && (y + step_y) >= 0 && (x + step_x) < tem->len && (y + step_y) < tem->len) {
        sum1 += tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type].num;
    }
    int num1 = tem->target_num - sum1;

    tem->direction_checkerboard[x][y].direction_piece_num[type].left_enemy = 0;
    int left_enemy = 0;
    if ((x - step_x) >= 0 && (y - step_y) >= 0 && (x - step_x) < tem->len && (y - step_y) < tem->len)
         left_enemy = tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type].left_enemy;
    if(left_enemy==0)
        return 0;
    if ((x - step_x) >= 0 && (y - step_y) >= 0 && (x - step_x) < tem->len && (y - step_y < tem->len) &&
        left_enemy > 0&&
        left_enemy < num1) {
        tem->direction_checkerboard[x ][y].direction_piece_num[type].left_enemy = left_enemy + 1 ;
        res++;
    }
    else if(left_enemy<0)
    {
        int target_num=0;
        while (++target_num<=num1) {
            if (x - step_x >= 0 && x - step_x < tem->len && y - step_y >= 0 && y - step_y < tem->len) {
                int find_move_x =
                        step_x * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type].num +
                                target_num);
                int find_move_y =
                        step_y *
                        (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type].num + target_num);
                if ((x - find_move_x) >= 0 && (y - find_move_y) >= 0 && (x - find_move_x) < tem->len &&
                    (y - find_move_y) < tem->len &&
                    tem->general_checkerboard[x - find_move_x][y - find_move_y] != opponent_player) {
                    continue;
                } else {
                    res++;
                    tem->direction_checkerboard[x][y].direction_piece_num[type].left_enemy = target_num;
                    break;
                }
            }
        }
    }

    return res;
}



int SixPiece::GetPieceTypeForRight(std::shared_ptr<TemporaryData> tem, int &player, int type,const int &x,const int &y) {
    int  sum2 = 1;
    int step_x = 0, step_y = 0;
    int res = 0;
    int opponent_player = player == 1 ? 2 : 1;

    GetStepXStepY(step_x,step_y,type);

    if ((x - step_x) >= 0 && (y - step_y >= 0) && (x - step_x) < tem->len && (y - step_y < tem->len)) {
        sum2 += tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type].num;
    }

    int num2 = tem->target_num - sum2;
    tem->direction_checkerboard[x][y].direction_piece_num[type].right_enemy = 0;
    int right_enemy = 0;
    if ((x + step_x) >= 0 && (y + step_y) >= 0 && (x + step_x) < tem->len && (y + step_y < tem->len))
        right_enemy = tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type].right_enemy;
    if(right_enemy==0)
        return 0;
    if ((x + step_x) >= 0 && (y + step_y) >= 0 && (x + step_x) < tem->len && (y + step_y < tem->len) &&
            right_enemy > 0&&
            right_enemy < num2)
    {
        tem->direction_checkerboard[x ][y].direction_piece_num[type].right_enemy = right_enemy + 1;
        res++;
    }
    else if(right_enemy<0)
    {
        int target_num = 0;
        while (++target_num<=num2)
        {
            if ((x + step_x) >= 0 && (y + step_y) >= 0 && (x + step_x) < tem->len && (y + step_y < tem->len)) {
                int find_move_x =
                        step_x * (tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type].num + target_num);
                int find_move_y =
                        step_y * (tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type].num + target_num);
                if ((x + find_move_x) < tem->len && (y + find_move_y) < tem->len && (x + find_move_x) >= 0 &&
                    (y + find_move_y) >= 0 &&
                    tem->general_checkerboard[x + find_move_x][y + find_move_y] != opponent_player) {
                    continue;
                } else {
                    tem->direction_checkerboard[x][y].direction_piece_num[type].right_enemy = target_num;
                    res++;
                    break;
                }
            }
        }

    }
    return res;
}



int SixPiece::GetPieceType(std::shared_ptr<TemporaryData> tem, int &player, int type,const  int &x,const int &y) {

    int res = 0;
    res+= GetPieceTypeForLeft(tem,player,type,x,y);
    res+GetPieceTypeForRight(tem,player,type,x,y);
    return res;
}

int SixPiece::GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player, int type, int &x, int &y) {
    int sum = 1;

    switch (type) {
        case static_cast<int>(Direction::Left):
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                sum += tem->direction_checkerboard[x - 1][y].direction_piece_num[static_cast<int>(Direction::Left)].num;
            }
            if (x < tem->len - 1 && tem->general_checkerboard[x + 1][y] == player) {
                sum += tem->direction_checkerboard[x + 1][y].direction_piece_num[static_cast<int>(Direction::Left)].num;
            }
            break;
        case static_cast<int>(Direction::Up):
            if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                sum += tem->direction_checkerboard[x][y - 1].direction_piece_num[static_cast<int>(Direction::Up)].num;
            }
            if (y < tem->len - 1 && tem->general_checkerboard[x][y + 1] == player) {
                sum += tem->direction_checkerboard[x][y + 1].direction_piece_num[static_cast<int>(Direction::Up)].num;
            }
            break;
        case static_cast<int>(Direction::LeftUp):
            if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)].num;
            }
            if (y < tem->len - 1 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)].num;
            }
            break;
        case static_cast<int>(Direction::RightUp):
            if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)].num;
            }
            if (y < tem->len - 1 && x > 0 && tem->general_checkerboard[x - 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)].num;
            }
            break;
        case static_cast<int>(Direction::OpponentLeft):
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                sum += tem->direction_checkerboard[x -
                                                   1][y].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num;
            }
            if (x < tem->len - 1 && tem->general_checkerboard[x + 1][y] == player) {
                sum += tem->direction_checkerboard[x +
                                                   1][y].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num;
            }
            break;
        case static_cast<int>(Direction::OpponentUp):
            if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                sum += tem->direction_checkerboard[x][y -
                                                      1].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num;
            }
            if (y < tem->len - 1 && tem->general_checkerboard[x][y + 1] == player) {
                sum += tem->direction_checkerboard[x][y +
                                                      1].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num;
            }
            break;
        case static_cast<int>(Direction::OpponentLeftUp):
            if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num;
            }
            if (y < tem->len - 1 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num;
            }
            break;
        case static_cast<int>(Direction::OpponentRightUp):
            if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num;
            }
            if (y < tem->len - 1 && x > 0 && tem->general_checkerboard[x - 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num;
            }
            break;
    }
    return sum;
}


void SixPiece::CalCulateScoreForNowPlayer(std::shared_ptr<TemporaryData> tem, int &i, int &j) {
    for(int i=0;i<tem->len;i++) {
        for(int j=0;j<tem->len;j++) {
            if (tem->general_checkerboard[i][j] == 0)
            for(int type =0;type<4;type++)
            {

                tem->direction_checkerboard[i][j].direction_piece_type[type] = GetPieceTypeForLeft(
                        tem, tem->now_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }


    for(int i=tem->len-1;i>=0;i--) {
        for(int j=tem->len-1;j>=0;j--) {
            if (tem->general_checkerboard[i][j] == 0)
            for(int type =0;type<4;type++)
            {

                tem->direction_checkerboard[i][j].direction_piece_type[type] = GetPieceTypeForRight(
                        tem, tem->now_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }

    for (int i = tem->len - 1; i >= 0; i--) {
        for (int j = tem->len - 1; j >= 0; j--) {
            if (tem->general_checkerboard[i][j] == 0)
            for (int type = 0; type < 4; type++) {

                tem->direction_checkerboard[i][j].direction_piece_num[type].num = GetPieceNum(
                        tem, tem->now_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }
}


void SixPiece::CalCulateScoreForOppoNentPlayer(std::shared_ptr<TemporaryData> tem, int &i, int &j) {
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentLeft)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeft), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentLeftUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentRightUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentRightUp), i, j);

    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)].num = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeft), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)].num = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)].num = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)].num = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentRightUp), i, j);


    for(int i=0;i<tem->len;i++) {
        for(int j=0;j<tem->len;j++) {
            if (tem->general_checkerboard[i][j] == 0)
            for(int type =4;type<8;type++)
            {
                tem->direction_checkerboard[i][j].direction_piece_type[type] = GetPieceTypeForLeft(
                        tem, tem->opponent_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }


    for(int i=tem->len-1;i>=0;i--) {
        for(int j=tem->len-1;j>=0;j--) {
            if (tem->general_checkerboard[i][j] == 0)
            for(int type =4;type<8;type++)
            {
                tem->direction_checkerboard[i][j].direction_piece_type[type] = GetPieceTypeForRight(
                        tem, tem->opponent_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }

    for (int i = tem->len - 1; i >= 0; i--) {
        for (int j = tem->len - 1; j >= 0; j--) {
            if (tem->general_checkerboard[i][j] == 0)
            for (int type = 4; type < 8; type++) {
                tem->direction_checkerboard[i][j].direction_piece_num[type].num = GetPieceNum(
                        tem, tem->opponent_player, type, i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)].num = GetPieceNum(
                        tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
            }
        }
    }

}


void SixPiece::UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem) {
    for (int i = 0; i < tem->len; i++) {
        for (int j = 0; j < tem->len; j++) {
            if (tem->general_checkerboard[i][j] == 0) {

//int s=0,ss=0;
                CalCulateScoreForNowPlayer(tem,i, j);

                CalCulateScoreForOppoNentPlayer(tem, i, j);

    for(int i=0;i<tem->len;i++) {
        for(int j=0;j<tem->len;j++) {
            if (tem->general_checkerboard[i][j] == 0)
                FindMaxAndAddScore(tem, i, j);
        }}

            }
            if (tem->real_six.x != -1 || tem->opponent_six.x != -1)
                break;
        }
    }

}

void SixPiece::InitializePieceDirectionSpace(std::shared_ptr<TemporaryData> tem) {
    if (tem->direction_checkerboard[0][0].direction_piece_num.empty()) {
        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                tem->direction_checkerboard[i][j].direction_piece_num.resize(8);
                tem->direction_checkerboard[i][j].direction_piece_type.resize(8);
            }
        }
    }
}


void SixPiece::InitializeDirectionBoard(int &i, int &j, std::shared_ptr<TemporaryData> tem) {
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

void SixPiece::InitializeDirectionBoardForOpponent(int &i, int &j, std::shared_ptr<TemporaryData> tem) {
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
void SixPiece::InitializeDirectionBoardOfEnemyNum(int &position_x,int &position_y,std::shared_ptr<TemporaryData> tem)
{
    for(int i=0;i<=7;i++)
    {
        tem->direction_checkerboard[position_x][position_y].direction_piece_num[i].right_enemy = -1;
        tem->direction_checkerboard[position_x][position_y].direction_piece_num[i].left_enemy = -1;
    }
}

void SixPiece::UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem) {

    tem->len = tem->general_checkerboard.size();
    if (!tem->direction_checkerboard.size()) {
        tem->direction_checkerboard.resize(tem->len, std::vector<PieceDirection>(tem->len));
        InitializePieceDirectionSpace(tem);
    }

    if (!tem->direction_checkerboard.empty()) {

        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                InitializeDirectionBoardOfEnemyNum(i,j,tem);
                if (tem->general_checkerboard[i][j] == tem->now_player) {
                    InitializeDirectionBoard(i, j, tem);
                }
                if (tem->general_checkerboard[i][j] == tem->opponent_player) {
                    InitializeDirectionBoardForOpponent(i, j, tem);
                }
            }
        }

        UpdatePieceTypeAndNum(tem);

    }


//    }

}

void SixPiece::SetRecord(Point &pos, std::shared_ptr<TemporaryData> tem_player1,
                         std::shared_ptr<TemporaryData> tem_player2) {
    if (pos.x < 0 || pos.y < 0) {
        return;
    }
    tem_player1->general_checkerboard[pos.x][pos.y] = tem_player1->now_player;

    tem_player2->general_checkerboard[pos.x][pos.y] = tem_player1->now_player;
}


int
SixPiece::PopulationPlayAGame(const int &player_gene_pos1, const int &player_gene_pos2,
                              const std::shared_ptr<TrainPiectElement> board) {
    std::shared_ptr<TemporaryData> ply_1st = std::make_shared<TemporaryData>();
    std::shared_ptr<TemporaryData> ply_2nd = std::make_shared<TemporaryData>();
    ply_1st->now_player = 1;
    ply_1st->opponent_player = 2;
    ply_2nd->now_player = 2;
    ply_2nd->opponent_player = 1;
    CacheTemporaryDate(board, ply_1st, player_gene_pos1);
    CacheTemporaryDate(board, ply_2nd, player_gene_pos2);

    int times = board->convergence_step;
    ply_1st->real_player = 1;
    ply_2nd->real_player = 2;

    while (times--) {

        for (int i = 0; i < 2; i++) {
            UpdateQuadrantStatus(ply_1st);

            if (ply_1st->real_six.x > 0)
                return 1;
            if (ply_1st->opponent_six.x > 0)
                SetRecord(ply_1st->opponent_six, ply_1st, ply_2nd);
            else
                SetRecord(ply_1st->max_pos, ply_1st, ply_2nd);
        }


        for (int i = 0; i < 2; i++) {

            UpdateQuadrantStatus(ply_2nd);
            if (ply_2nd->real_six.x > 0)
                return 2;
            if (ply_2nd->opponent_six.x > 0)
                SetRecord(ply_2nd->opponent_six, ply_2nd, ply_1st);
            else
                SetRecord(ply_2nd->max_pos, ply_2nd, ply_1st);

        }

    }


    return 0;//平局
}

void SixPiece::MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board) {

    std::shared_ptr<GeneVariate> variate = std::make_shared<GeneVariate>(board->population,
                                                                         board->population_num / board->champaion_num,
                                                                         board->champion, 0, 0, 0);

    cout<<variate->child_num<<variate->champaion_num;
    CrossingOverPrePare(variate);
    board->population = variate->population;

}

void SixPiece::InitPopulation(std::shared_ptr<TrainPiectElement> board) {
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


void SixPiece::GetPKQueue(std::vector<int> &pk_queue) {
    for (int i = 0; i < pk_queue.size(); i++) {
        pk_queue[i] = i;
    }
    std::random_shuffle(pk_queue.begin(), pk_queue.end());
}

void SixPiece::UpdateNextRoundQueue(std::vector<int> &pk_queue, std::unordered_map<int, int> &ma) {
    pk_queue.clear();

    for (std::unordered_map<int, int>::iterator it = ma.begin(); it != ma.end(); it++)//find winner,save into pk_queue
    {
        if (it->second == 1)
            pk_queue.emplace_back(it->first);
    }
    std::random_shuffle(pk_queue.begin(), pk_queue.end());//random opponent
}

void SixPiece::SelectChampion(std::shared_ptr<TrainPiectElement> board,
                              std::vector<int> &pk_queue)//del old champion,and update new champion
{
    board->champion.clear();
    for (int i = 0; i < pk_queue.size(); i++) {
        board->champion.emplace_back(board->population[pk_queue[i]]);
    }
}

void SixPiece::PopulationContest(std::shared_ptr<TrainPiectElement> board)//contest and make new champion
{

    std::vector<int> pk_queue;
    pk_queue.resize(board->population_num);
    GetPKQueue(pk_queue);

    for(int i=0;i<pk_queue.size();i++)

    while (--board->contest_round) {
        ParallelCalculate pool{3};
        std::unordered_map<int, int> ma;//contest use  multiple threads

        auto CalCulate = [&](int player1,int player2){
            SingleContest(player1, player2, board, ma);
        };

        for (int i = 0; i < pk_queue.size(); i += 2) {
            int player1 = pk_queue[i], player2 = pk_queue[i + 1];
            pool.commit(CalCulate,player1,player2);

        }
        int i = 1;
        pool.ParallelAccum(i);
        UpdateNextRoundQueue(pk_queue, ma);
    }
    DisPlayBoard(board->general_checkerboard);
    SelectChampion(board, pk_queue);
}


void SixPiece::SingleContest(const int player_gene_pos1, const int player_gene_pos2, std::shared_ptr<TrainPiectElement> board,
                             std::unordered_map<int, int> &ma) {
    int win_player;
    for (int i = 0; i < board->match_times; i++) {
        int black_winner = PopulationPlayAGame(player_gene_pos1, player_gene_pos2, board);

        int white_winner = PopulationPlayAGame(player_gene_pos2, player_gene_pos1, board);

        switch (black_winner) {
            case 0:
                board->population[player_gene_pos1].back() += 25;
                board->population[player_gene_pos2].back() += 25;
                break;
            case 1:
                board->population[player_gene_pos1].back() += 50;
                break;
            case 2:
                board->population[player_gene_pos2].back() += 50;
                break;
        }
        switch (white_winner) {
            case 0:
                board->population[player_gene_pos1].back() += 25;
                board->population[player_gene_pos2].back() += 25;
                break;
            case 1:
                board->population[player_gene_pos1].back() += 50;
                break;
            case 2:
                board->population[player_gene_pos2].back() += 50;
                break;
        }


    }
    win_player =
            board->population[player_gene_pos1].back() < board->population[player_gene_pos2].back() ? player_gene_pos2
                                                                                                    : player_gene_pos1;
    ma[win_player] = 1;
}

void SixPiece::DisPlayBoard(std::vector<std::vector<int>> general_checkerboard) {
    for (int i = 0; i < general_checkerboard.size(); i++) {
        cout << endl;
        for (int j = 0; j < general_checkerboard[0].size(); j++)
            cout << general_checkerboard[i][j] << " ";
    }
    cout << endl;
}

void SixPiece::DisplayScore(std::shared_ptr<TemporaryData> tem) {
    for (int i = 0; i < tem->len; i++) {

        for (int j = 0; j < tem->len; j++) {
            cout << "  " << tem->direction_checkerboard[i][j].score << " ";

        }
        cout << endl;
    }
}


void SixPiece::ShowChampion(std::shared_ptr<TrainPiectElement> board) {
    for (int i = 0; i < board->champaion_num; i++) {
        cout << "number " << i << " is ";
        for (int j = 0; j < board->champion[i].size(); j++) {
            cout << " " << board->champion[i][j];
        }
        cout << endl;
    }
}

void SixPiece::MakeChampion(std::shared_ptr<TrainPiectElement> board) {
    PopulationContest(board);
    MakePopulationWhenTrain(board);
}






