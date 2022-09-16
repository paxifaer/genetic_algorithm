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





void SixPiece::CacheTemporaryDate(const std::shared_ptr<TrainPiectElement> board, std::shared_ptr<TemporaryData> tem,const int &player_gene_pos) {
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
        tem->direction_checkerboard[x][y].score += GetScore(tem,x,y,0)+GetScore(tem,x,y,1)+GetScore(tem,x,y,2)+GetScore(tem,x,y,3);
        if(tem->direction_checkerboard[x][y].score > tem->max_score)
        {
            tem->max_score = tem->direction_checkerboard[x][y].score;
            tem->max_pos = {x,y};
        }

}


int SixPiece::GetPieceType(std::shared_ptr<TemporaryData> tem, int &player, int type, int &x, int &y) {
    int sum = 1;
    int step_x = 0, step_y = 0;
    int res = 0;
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
    };

    if ((x - step_x) >= 0 && (y - step_y) >= 0) {
        sum += tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type];
    }
    if ((x + step_x) < tem->len && (y + step_y < tem->len)) {
        sum += tem->direction_checkerboard[x + step_x][y + step_y].direction_piece_num[type];
    }
    int num1 = tem->target_num - sum;
    int num2 = tem->target_num - sum;
    while (num1--) {
        int find_move_x =
                step_x * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num1);
        int find_move_y =
                step_y * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num1);
        if ((x - find_move_x) >= 0 && (y - find_move_y) >= 0 &&
            tem->general_checkerboard[find_move_x][find_move_y] != player) {
            continue;
        } else {
            res++;
            break;
        }
    }
    while (num2--) {
        int find_move_x =
                step_x * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num2);
        int find_move_y =
                step_y * (tem->direction_checkerboard[x - step_x][y - step_y].direction_piece_num[type] + num2);
        if ((x + find_move_x) < tem->len && (y - find_move_y) < tem->len &&
            tem->general_checkerboard[find_move_x][find_move_y] != player) {
            continue;
        } else {
            res++;
            break;
        }
    }
    return res;
}
int SixPiece::GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int type,int &x,int &y)
{
    int sum =1;
    switch(type)
    {
        case 0:
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                sum += tem->direction_checkerboard[x - 1][y].direction_piece_num[static_cast<int>(Direction::Left)];
            }
            if (x < tem->len - 1 && tem->general_checkerboard[x + 1][y] == player) {
                sum += tem->direction_checkerboard[x + 1][y].direction_piece_num[static_cast<int>(Direction::Left)];
            }
            break;
        case 1:
            if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                sum += tem->direction_checkerboard[x][y - 1].direction_piece_num[static_cast<int>(Direction::Up)];
            }
            if (y < tem->len - 1 && tem->general_checkerboard[x][y + 1] == player) {
                sum += tem->direction_checkerboard[x][y + 1].direction_piece_num[static_cast<int>(Direction::Up)];
            }
            break;
        case 2:
            if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
            }
            if (y < tem->len - 1 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
            }
            break;
        case 3:
            if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                sum += tem->direction_checkerboard[x + 1][y -
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)];
            }
            if (y < tem->len - 1 && x > 0 && tem->general_checkerboard[x - 1][y + 1] == player) {
                sum += tem->direction_checkerboard[x - 1][y +
                                                          1].direction_piece_num[static_cast<int>(Direction::RightUp)];
            }
            break;
    }
    return sum;
}
void SixPiece::UpdatePieceTypeAndNum(std::shared_ptr<TemporaryData> tem) {
    int len = tem->general_checkerboard.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (tem->general_checkerboard[i][j] == 0) {

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
                tem->direction_checkerboard[i][j].direction_piece_num.resize(4);
                tem->direction_checkerboard[i][j].direction_piece_type.resize(4);
            }
        }
    }
};;

void SixPiece::UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem) {

    tem->len = tem->general_checkerboard.size();
    tem->direction_checkerboard.resize(tem->len, std::vector<PieceDirection>(tem->len));
    InitializePieceDirectionSpace(tem);
    if (tem->direction_checkerboard.empty())
    {
        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                if (tem->general_checkerboard[i][j] == tem->real_player) {
                    if (i > 0 && tem->general_checkerboard[i - 1][j] == tem->real_player) {
                        int num = tem->direction_checkerboard[i -
                                                              1][j].direction_piece_num[static_cast<int>(Direction::Left)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i -
                                                        num][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                        }
                    } else if (i == 0 || tem->general_checkerboard[i - 1][j] != tem->real_player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = 1;
                    }

                    if (j > 0 && tem->general_checkerboard[i][j - 1] == tem->real_player) {
                        int num = tem->direction_checkerboard[i][j -
                                                                 1].direction_piece_num[static_cast<int>(Direction::Up)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i][j -
                                                           num].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                        }
                    } else if (j == 0 || tem->general_checkerboard[i][j - 1] != tem->real_player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = 1;
                    }

                    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == tem->real_player) {
                        int num = tem->direction_checkerboard[i - 1][j -
                                                                     1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i - num][j -
                                                                 num].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                        }
                    } else if (j == 0 || i == 0 || tem->general_checkerboard[i - 1][j - 1] != tem->real_player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = 1;
                    }

                    if (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] == tem->real_player) {
                        int num = tem->direction_checkerboard[i + 1][j -
                                                                     1].direction_piece_num[static_cast<int>(Direction::RightUp)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i + num][j -
                                                                 num].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                        }
                    } else if (j == 0 || i == tem->len - 1 || tem->general_checkerboard[i + 1][j - 1] != tem->real_player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = 1;
                    }

                }
            }
        }
        UpdatePieceTypeAndNum(tem);
    }

}

void SixPiece::SetRecord(Point &pos,std::shared_ptr<TemporaryData> tem)
{
    tem->general_checkerboard[pos.x][pos.y]=tem->real_player;
}

int
SixPiece::PopulationPlayAGame(const int &player_gene_pos1, const int &player_gene_pos2, const std::shared_ptr<TrainPiectElement> board) {

    std::shared_ptr<TemporaryData> ply_1st, ply_2nd;
    CacheTemporaryDate(board, ply_1st,player_gene_pos1);
    CacheTemporaryDate(board, ply_2nd,player_gene_pos2);

    int times = board->convergence_step;
    ply_1st->real_player = 0;
    ply_2nd->real_player = 1;
    while (times--)
    {
        for(int i=0;i<2;i++)
        {
            UpdateQuadrantStatus(ply_1st);
            if (ply_1st->real_six.x)
                return 1;
            UpdateQuadrantStatus(ply_1st);
            if (ply_1st->opponent_six.x)
                SetRecord(ply_1st->opponent_six, ply_1st);
            else
                SetRecord(ply_1st->max_pos, ply_1st);
        }
//            return 1;
        for(int i=0;i<2;i++)
        {
            UpdateQuadrantStatus(ply_2nd);
            if (ply_2nd->real_six.x)
                return 2;
            UpdateQuadrantStatus(ply_2nd);
            if (ply_2nd->opponent_six.x)
                SetRecord(ply_2nd->opponent_six, ply_2nd);
            else
                SetRecord(ply_2nd->max_pos, ply_2nd);
        }
    }
    return 0;//平局
}


void SixPiece::MakePopulationWhenTrain(std::shared_ptr<TrainPiectElement> board) {
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
        pk_queue.emplace_back(i);
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

    std::vector<int> pk_queue{board->population_num};
    iota(pk_queue.begin(), pk_queue.end(), 0);
    GetPKQueue(pk_queue);
    while (--board->contest_round) {
        ParallelCalculate pool{3};
        std::unordered_map<int, int> ma;//contest use  multiple threads
        for (int i = 0; i < pk_queue.size(); i += 2) {
            pool.commit([&](){SingleContest( pk_queue[i], pk_queue[i + 1], board, ma);});
        }
        int i=1;
        pool.ParallelAccum(i);
        UpdateNextRoundQueue(pk_queue, ma);
    }
    SelectChampion(board, pk_queue);
}


void SixPiece::SingleContest(int player_gene_pos1, int player_gene_pos2, std::shared_ptr<TrainPiectElement> board,
                             std::unordered_map<int, int> ma) {
    int win_player;
    for (int i = 0; i < board->match_times; i++) {
        int black_winner = PopulationPlayAGame(player_gene_pos1,player_gene_pos2,board);
        int white_winner = PopulationPlayAGame(player_gene_pos2,player_gene_pos1,board);
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


void SixPiece::MakeChampion(std::shared_ptr<TrainPiectElement> board) {
    PopulationContest(board);
    MakePopulationWhenTrain(board);
}






