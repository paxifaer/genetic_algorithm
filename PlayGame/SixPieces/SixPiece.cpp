#include "SixPiece.h"
#include <memory>


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





void SixPiece::CacheTemporaryDate(std::shared_ptr<TrainPiectElement> board, std::shared_ptr<TemporaryData> tem,const int &player_gene_pos) {

    tem->general_checkerboard = board->general_checkerboard;
    tem->gene = board->population[player_gene_pos];
}

long long int SixPiece::GetScore(std::shared_ptr<TemporaryData> tem, int &x, int &y,int direction) {
    switch (tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(direction)]) {
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
            switch (tem->direction_checkerboard[x][y].direction_piece_type[static_cast<int>(direction)]) {
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
    if (tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Left)] >= 6 ||
        tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::LeftUp)] >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Up)] >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::RightUp)] >= 6) {
        if(tem->now_player==tem->real_player)
            tem->real_six = {x, y};
        else
            tem->opponent_six = {x, y};
    }
    tem->direction_checkerboard[x][y].score +=
            GetScore(tem, x, y, 0) + GetScore(tem, x, y, 1) + GetScore(tem, x, y, 2) + GetScore(tem, x, y, 3) +
            GetScore(tem, x, y, 4) + GetScore(tem, x, y, 5) + GetScore(tem, x, y, 6) + GetScore(tem, x, y, 7);

//        cout<<" posx is "<<x<<"  posy is "<<y<<endl;
    if (tem->direction_checkerboard[x][y].score > tem->max_score) {

        tem->max_score = tem->direction_checkerboard[x][y].score;
        tem->max_pos = {x, y};
//        cout << " aaaa  max_score is : " << tem->max_score << endl;
//        cout << "pos is " << x << "  " << y << endl;
    }

}



int SixPiece::GetPieceType(std::shared_ptr<TemporaryData> tem, int &player, int type, int &x, int &y) {
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
                tem->general_checkerboard[x + find_move_x][y + find_move_y] != opponent_player) {
                continue;
            } else {
                res++;
                break;
            }
        }
    }
    return res;
}
int SixPiece::GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int type,int &x,int &y)
{
    int sum =1;

    switch(type)
    {
        case static_cast<int>(Direction::Left):
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                sum += tem->direction_checkerboard[x - 1][y].direction_piece_num[static_cast<int>(Direction::Left)];
            }
            if (x < tem->len - 1 && tem->general_checkerboard[x + 1][y] == player) {
                sum += tem->direction_checkerboard[x + 1][y].direction_piece_num[static_cast<int>(Direction::Left)];
            }
            break;
        case static_cast<int>(Direction::Up):
            if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                sum += tem->direction_checkerboard[x][y - 1].direction_piece_num[static_cast<int>(Direction::Up)];
            }
            if (y < tem->len - 1 && tem->general_checkerboard[x][y + 1] == player) {
                sum += tem->direction_checkerboard[x][y + 1].direction_piece_num[static_cast<int>(Direction::Up)];
            }
            break;
        case static_cast<int>(Direction::LeftUp):
            if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
            }
            if (y < tem->len - 1 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
            }
            break;
        case static_cast<int>(Direction::RightUp):
            if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)];
            }
            if (y < tem->len - 1 && x > 0 && tem->general_checkerboard[x - 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)];
            }
            break;
        case static_cast<int>(Direction::OpponentLeft):
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                sum += tem->direction_checkerboard[x - 1][y].direction_piece_num[static_cast<int>(Direction::OpponentLeft)];
            }
            if (x < tem->len - 1 && tem->general_checkerboard[x + 1][y] == player) {
                sum += tem->direction_checkerboard[x + 1][y].direction_piece_num[static_cast<int>(Direction::OpponentLeft)];
            }
            break;
        case static_cast<int>(Direction::OpponentUp):
            if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                sum += tem->direction_checkerboard[x][y - 1].direction_piece_num[static_cast<int>(Direction::OpponentUp)];
            }
            if (y < tem->len - 1 && tem->general_checkerboard[x][y + 1] == player) {
                sum += tem->direction_checkerboard[x][y + 1].direction_piece_num[static_cast<int>(Direction::OpponentUp)];
            }
            break;
        case static_cast<int>(Direction::OpponentLeftUp):
            if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)];
            }
            if (y < tem->len - 1 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)];
            }
            break;
        case static_cast<int>(Direction::OpponentRightUp):
            if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)];
            }
            if (y < tem->len - 1 && x > 0 && tem->general_checkerboard[x - 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)];
            }
            break;
    }
    return sum;
}


void SixPiece::CalCulateScoreForNowPlayer(std::shared_ptr<TemporaryData> tem,int &i,int &j)
{
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Left)] = GetPieceType(
            tem, tem->now_player, static_cast<int>(Direction::Left), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
            tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
            tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
            tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);

    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = GetPieceNum(
            tem, tem->now_player, static_cast<int>(Direction::Left), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = GetPieceNum(
            tem, tem->now_player, static_cast<int>(Direction::Up), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = GetPieceNum(
            tem, tem->now_player, static_cast<int>(Direction::LeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = GetPieceNum(
            tem, tem->now_player, static_cast<int>(Direction::RightUp), i, j);
}


void SixPiece::CalCulateScoreForOppoNentPlayer(std::shared_ptr<TemporaryData> tem,int &i,int &j)
{
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentLeft)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeft), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentLeftUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::OpponentRightUp)] = GetPieceType(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentRightUp), i, j);

    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)] = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeft), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)] = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)] = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentLeftUp), i, j);
    tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)] = GetPieceNum(
            tem, tem->opponent_player, static_cast<int>(Direction::OpponentRightUp), i, j);
}


void SixPiece::UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem) {
    for (int i = 0; i < tem->len; i++) {
        for (int j = 0; j < tem->len; j++) {
            if (tem->general_checkerboard[i][j] == 0) {

                CalCulateScoreForNowPlayer(tem,i,j);
                CalCulateScoreForOppoNentPlayer( tem,i,j);
                FindMaxAndAddScore(tem, i, j);
            }
            if(tem->real_six.x!=-1||tem->opponent_six.x!=-1)
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
//    else
//        cout<<"it is not empty,Won't initialize"<<endl;
}


void SixPiece::InitializeDirectionBoard(int &i,int &j,std::shared_ptr<TemporaryData> tem)
{
//    cout<<"InitializeDirectionBoard"<<endl;
    if (i > 0 && tem->general_checkerboard[i - 1][j] == tem->now_player) {
//        cout<<"111  "<<endl;
        int num = tem->direction_checkerboard[i -
                                              1][j].direction_piece_num[static_cast<int>(Direction::Left)];//迭代每一步棋子数量
//        cout<<"111  "<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
//        cout<<"111  "<<endl;
        while (--num&&(i-num)>=0) {
            tem->direction_checkerboard[i -
                                        num][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
        }
//        cout<<"111  "<<endl;
    } else if (i == 0 ||(i>0&& tem->general_checkerboard[i - 1][j] != tem->now_player)) {
//        cout<<"222  "<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = 1;
//        cout<<"222  "<<endl;
    }

    if (j > 0 && tem->general_checkerboard[i][j - 1] == tem->now_player) {
//        cout<<"333  "<<endl;
        int num = tem->direction_checkerboard[i][j -
                                                 1].direction_piece_num[static_cast<int>(Direction::Up)];
//        cout<<"333  "<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
//        cout<<"333  "<<endl;
        while (--num&&(j-num)>=0) {
            tem->direction_checkerboard[i][j -
                                           num].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
        }
    } else if (j == 0 || (j>0&&tem->general_checkerboard[i][j - 1] != tem->now_player)) {
//        cout<<"444  "<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = 1;
//        cout<<"444  "<<endl;
    }

    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == tem->now_player) {
//        cout<<"555  "<<endl;
        int num = tem->direction_checkerboard[i - 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
//        cout<<"555  "<<endl;
        while (--num&&(i-num)>=0&&(j-num)>=0) {
            tem->direction_checkerboard[i - num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
        }
//        cout<<"555  "<<endl;
    } else if (j == 0 || i == 0 || (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] != tem->now_player)) {
//        cout<<"666  "<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = 1;
//        cout<<"666  "<<endl;
    }

    if (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] == tem->now_player) {
//        cout<<"777  "<<endl;
        int num = tem->direction_checkerboard[i + 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::RightUp)];
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
        while (--num&&(i+num)<tem->len&&(j-num)>=0) {
            tem->direction_checkerboard[i + num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
        }
//        cout<<"777  "<<endl;
    } else if (j == 0 || i == tem->len - 1 ||(i<tem->len-1&&j>0&& tem->general_checkerboard[i + 1][j - 1] != tem->now_player)) {
//        cout<<888<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = 1;
//        cout<<888<<endl;
    }

}

void SixPiece::InitializeDirectionBoardForOpponent(int &i,int &j,std::shared_ptr<TemporaryData> tem)
{
//    cout<<"InitializeDirectionBoardForOpponent"<<endl;
    if (i > 0 && tem->general_checkerboard[i - 1][j] == tem->opponent_player) {
//        cout<<1111<<endl;
        int num = tem->direction_checkerboard[i -
                                              1][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)];//迭代每一步棋子数量
//        cout<<1111<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)] = real_num;
//        cout<<1111<<endl;
        while (--num&&(i-num)>=0) {
            tem->direction_checkerboard[i -
                                        num][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)] = real_num;
        }
//        cout<<1111<<endl;
    } else if (i == 0 ||( i>0&&tem->general_checkerboard[i - 1][j] != tem->opponent_player)) {
//        cout<<2222<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeft)] = 1;
//        cout<<2222<<endl;
    }

    if (j > 0 && tem->general_checkerboard[i][j - 1] == tem->opponent_player) {
//        cout<<3333<<endl;
        int num = tem->direction_checkerboard[i][j -
                                                 1].direction_piece_num[static_cast<int>(Direction::OpponentUp)];
//        cout<<3333<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)] = real_num;
//        cout<<3333<<endl;
        while (--num&&(j-num)>=0) {
            tem->direction_checkerboard[i][j -
                                           num].direction_piece_num[static_cast<int>(Direction::OpponentUp)] = real_num;
        }
//        cout<<3333<<endl;
    } else if (j == 0 ||( j>0&&tem->general_checkerboard[i][j - 1] != tem->opponent_player)) {
//        cout<<4444<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentUp)] = 1;
//        cout<<4444<<endl;
    }

    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == tem->opponent_player) {
//        cout<<5555<<endl;
        int num = tem->direction_checkerboard[i - 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)];
//        cout<<5555<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)] = real_num;
//        cout<<5555<<endl;
        while (--num&&(j-num)>=0&&(i-num)>=0) {
            tem->direction_checkerboard[i - num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)] = real_num;
        }
//        cout<<5555<<endl;
    } else if (j == 0 || i == 0 || (i>0&&j>0&&tem->general_checkerboard[i - 1][j - 1] != tem->opponent_player)) {
//        cout<<6666<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentLeftUp)] = 1;
//        cout<<6666<<endl;
    }

    if (j > 0 && i < tem->len - 1 && (tem->general_checkerboard[i + 1][j - 1] == tem->opponent_player)) {
//        cout<<7777<<endl;
        int num = tem->direction_checkerboard[i + 1][j -
                                                     1].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)];
//        cout<<7777<<endl;
        int real_num = num + 1;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)] = real_num;
//        cout<<7777<<endl;
        while (--num&&(i+num)<tem->len&&(j-num)>=0) {
            tem->direction_checkerboard[i + num][j -
                                                 num].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)] = real_num;
        }
//        cout<<7777<<endl;
    } else if (j == 0 || i == tem->len - 1 || (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] != tem->opponent_player)) {
//        cout<<9999<<endl;
        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::OpponentRightUp)] = 1;
//        cout<<9999<<endl;
    }
}


void SixPiece::UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem) {

    tem->len = tem->general_checkerboard.size();
    tem->direction_checkerboard.resize(tem->len, std::vector<PieceDirection>(tem->len));
    InitializePieceDirectionSpace(tem);//if is not empty,Won't initialize ;
//    cout<<"UpdateQuadrantStatus  player is "<<tem->now_player<<endl;
    if (!tem->direction_checkerboard.empty())
    {
        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                if (tem->general_checkerboard[i][j] == tem->now_player) {
                    InitializeDirectionBoard(i,j,tem);
                }
                if (tem->general_checkerboard[i][j] == tem->opponent_player) {
                    InitializeDirectionBoardForOpponent(i,j,tem);
                }
            }
        }
//        cout<<"UpdatePieceTypeAndNum"<<endl;
        UpdatePieceTypeAndNum(tem);
//        cout<<"UpdatePieceTypeAndNum"<<endl;
    }

}

void SixPiece::SetRecord(Point &pos,std::shared_ptr<TemporaryData> tem_player1,std::shared_ptr<TemporaryData> tem_player2)
{
//    cout<<"setboard  pos _x"<<pos.x<<"  pos _y "<<pos.y<<endl;
    tem_player1->general_checkerboard[pos.x][pos.y]=tem_player1->now_player;
    tem_player2->general_checkerboard[pos.x][pos.y]=tem_player1->now_player;
}



int
SixPiece::PopulationPlayAGame(const int &player_gene_pos1, const int &player_gene_pos2, const std::shared_ptr<TrainPiectElement> board) {
//    cout << "PopulationPlayAGame" << endl;
//    cout << "player_gene_pos1 ia " << player_gene_pos1 << " player_gene_pos2" << player_gene_pos2 << endl;
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

//        cout << "  is nowPlayer" << endl;
        for (int i = 0; i < 2; i++) {
            UpdateQuadrantStatus(ply_1st);
            if (ply_1st->real_six.x > 0)
                return 1;
            if (ply_1st->opponent_six.x > 0)
                SetRecord(ply_1st->opponent_six, ply_1st, ply_2nd);
            else
                SetRecord(ply_1st->max_pos, ply_1st, ply_2nd);
        }

//        DisPlayBoard(ply_1st->general_checkerboard);
//            return 1;

//        cout << "  is opponentPlayer" << endl;
        for (int i = 0; i < 2; i++) {

                UpdateQuadrantStatus(ply_2nd);
                if (ply_2nd->real_six.x > 0)
                    return 2;
                UpdateQuadrantStatus(ply_2nd);
                if (ply_2nd->opponent_six.x > 0)
                    SetRecord(ply_2nd->opponent_six, ply_2nd, ply_1st);
                else
                    SetRecord(ply_2nd->max_pos, ply_2nd, ply_1st);

        }
//        DisPlayBoard(ply_2nd->general_checkerboard);

    }
    return 0;//平局
}

void SixPiece::MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board) {
//    cout<<"MakePopulationWhenTrain"<<endl;
    std::shared_ptr<GeneVariate> variate = std::make_shared<GeneVariate>(board->population,
                                                                         board->population_num / board->champaion_num,
                                                                         board->champion, 0, 0, 0);
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
        pk_queue[i]=i;
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
        cout<<"冠军是 : "<<i<<endl;
    }
}

void SixPiece::PopulationContest(std::shared_ptr<TrainPiectElement> board)//contest and make new champion
{

    std::vector<int> pk_queue;
    pk_queue.resize(board->population_num);
    GetPKQueue(pk_queue);


    while (--board->contest_round) {
        ParallelCalculate pool{3};
        std::unordered_map<int, int> ma;//contest use  multiple threads
        for (int i = 0; i < pk_queue.size(); i += 2) {
            int player1 =pk_queue[i],player2 = pk_queue[i + 1];
            pool.commit([&](){SingleContest( player1, player2, board, ma);});
        }
        int i=1;
        pool.ParallelAccum(i);
        UpdateNextRoundQueue(pk_queue, ma);
    }
    DisPlayBoard(board->general_checkerboard);
    SelectChampion(board, pk_queue);
}


void SixPiece::SingleContest(int &player_gene_pos1, int &player_gene_pos2, std::shared_ptr<TrainPiectElement> board,
                             std::unordered_map<int, int> ma) {
    int win_player;
    for (int i = 0; i < board->match_times; i++) {
        int black_winner = PopulationPlayAGame(player_gene_pos1,player_gene_pos2,board);
        cout<<"black_winer is "<<black_winner<<endl;
        cout<<"general_checkerboard size is "<<board->general_checkerboard.size()<<endl;

        int white_winner = PopulationPlayAGame(player_gene_pos2,player_gene_pos1,board);
        cout<<"white_winer is "<<white_winner<<endl;
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
    win_player = board->population[player_gene_pos1].back() < board->population[player_gene_pos2].back() ? player_gene_pos2 : player_gene_pos1;
    ma[win_player] = 1;
}

void SixPiece::DisPlayBoard(std::vector<std::vector<int>> general_checkerboard)
{
    for(int i=0;i<general_checkerboard.size();i++)
    {
        cout<<endl;
        for(int j=0;j<general_checkerboard[0].size();j++)
            cout<<general_checkerboard[i][j]<<" ";
    }
    cout<<endl;
}

void SixPiece::DisplayScore(std::shared_ptr<TemporaryData> tem) {
    for (int i = 0; i < tem->len; i++) {

        for (int j = 0; j < tem->len; j++) {
            cout << "  " << tem->direction_checkerboard[i][j].score << " ";

        }
        cout << endl;
    }
}




void SixPiece::MakeChampion(std::shared_ptr<TrainPiectElement> board) {
    PopulationContest(board);
    MakePopulationWhenTrain(board);
}






