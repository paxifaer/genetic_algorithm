#include "SixPiece.h"
#include <memory>


void
SixPiece::Record(std::vector<std::vector<int>> &checkerboard, std::vector<std::vector<int>> &checkerboard_piece_num,
                 const int player, int x_position,
                 int y_position) //�ĸ��������̷���
{
    checkerboard[x_position][y_position] = player;

    int enemy = 1;
    int quadrant1 = (y_position - 1) * 19 + x_position,
            quadrant2 = 19 * (y_position - 1) + x_position + 400,
            quadrant3 = 19 * (y_position - 1) + x_position + 800,
            quadrant4 = 19 * (y_position - 1) + x_position + 1200;
    (enemy == player) ? (enemy = 2) : (enemy = 1);

    checkerboard_piece_num[player][(y_position - 1) * 19 + x_position] = 1;
    checkerboard_piece_num[player][19 * (y_position - 1) + x_position + 400] = 1;
    checkerboard_piece_num[player][19 * (y_position - 1) + x_position + 800] = 1;
    checkerboard_piece_num[player][19 * (y_position - 1) + x_position + 1200] = 1;
    checkerboard_piece_num[enemy][quadrant1] = -1;
    checkerboard_piece_num[enemy][quadrant2] = -1;
    checkerboard_piece_num[enemy][quadrant3] = -1;
    checkerboard_piece_num[enemy][quadrant4] = -1;

    int left_piece_num = 0, right_piece_num = 0; //����
    if (quadrant1 - 1 > 0)
        left_piece_num =
                checkerboard_piece_num[player][quadrant1 - 1] > 0 ? checkerboard_piece_num[player][quadrant1 - 1] : 0;
    if (quadrant1 + 1 <= 361)
        right_piece_num =
                checkerboard_piece_num[player][quadrant1 + 1] > 0 ? checkerboard_piece_num[player][quadrant1 + 1] : 0;;

    checkerboard_piece_num[player][quadrant1] += left_piece_num + right_piece_num;

    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++) {
            checkerboard_piece_num[player][quadrant1 - sd] = checkerboard_piece_num[player][quadrant1];
            // printf("\ncheckerboard_piece_num[player][quadrant-sd]=%d",checkerboard_piece_num[player][quadrant1-sd]);
        }
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++) {
            checkerboard_piece_num[player][quadrant1 + sd] = checkerboard_piece_num[player][quadrant1];
            // printf("\n%d",checkerboard_piece_num[player][quadrant1]);
        }
    // printf("\n l1=%d r1=%d",l,r);

    left_piece_num = 0, right_piece_num = 0; //����
    if (y_position - 1 > 0)
        left_piece_num = checkerboard_piece_num[player][quadrant2 - 19];
    if (y_position + 1 <= 19)
        right_piece_num = checkerboard_piece_num[player][quadrant2 + 19];

    if (left_piece_num >= 0)
        checkerboard_piece_num[player][quadrant2] += left_piece_num;
    if (right_piece_num >= 0)
        checkerboard_piece_num[player][quadrant2] += right_piece_num;

    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++)
            checkerboard_piece_num[player][quadrant2 - sd * 19] = checkerboard_piece_num[player][quadrant2];
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++)
            checkerboard_piece_num[player][quadrant2 + sd * 19] = checkerboard_piece_num[player][quadrant2];
    // printf("\n l2=%d r2=%d",l,r);

    left_piece_num = 0, right_piece_num = 0; //��б��
    if (quadrant3 - 19 - 1 > 800)
        left_piece_num = checkerboard_piece_num[player][quadrant3 - 19 - 1];
    if (quadrant3 + 19 + 1 <= 1161)
        right_piece_num = checkerboard_piece_num[player][quadrant3 + 19 + 1];

    if (left_piece_num >= 0)
        checkerboard_piece_num[player][quadrant3] += left_piece_num;
    if (right_piece_num >= 0)
        checkerboard_piece_num[player][quadrant3] += right_piece_num;

    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++)
            checkerboard_piece_num[player][quadrant3 - sd * 19 - sd] = checkerboard_piece_num[player][quadrant3];
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++)
            checkerboard_piece_num[player][quadrant3 + sd * 20] = checkerboard_piece_num[player][quadrant3];
    // printf("\n l3=%d r3=%d",l,r);

    left_piece_num = 0, right_piece_num = 0; //��б��
    if (quadrant4 - 19 + 1 > 1200)
        left_piece_num = checkerboard_piece_num[player][quadrant4 - 19 + 1];
    if (quadrant4 + 19 - 1 <= 1560)
        right_piece_num = checkerboard_piece_num[player][quadrant4 + 19 - 1];
    if (left_piece_num >= 0)
        checkerboard_piece_num[player][quadrant4] += left_piece_num;
    if (right_piece_num >= 0)
        checkerboard_piece_num[player][quadrant4] += right_piece_num;

    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++)
            checkerboard_piece_num[player][quadrant4 - sd * 19 + sd] = checkerboard_piece_num[player][quadrant4];
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++)
            checkerboard_piece_num[player][quadrant4 + sd * 18] = checkerboard_piece_num[player][quadrant4];

    // printf("\n l4=%d r4=%d\n",l,r);//
}

int SixPiece::WhoIsWinner(const std::vector<std::vector<int>> &checkerboard_piece_num, const int &player) //ʤ���ж�
{
    int i;
    int enemy = 1;
    enemy == player ? enemy = 2 : enemy = 1;
    for (i = 1; i <= 1600; i++) {
        if (checkerboard_piece_num[player][i] >= 0) {
            if (checkerboard_piece_num[player][i] >= 6) {
                return player;
            }
        }
    }
}

int SixPiece::CheckCheckerBoard(const std::vector<std::vector<int>> &checkerboard_piece_num, const int &step,
                                const int &quadrant, const int &player, const int &emeny, const Point &point) {

    int l = 0, r = 0; //����
    int heng = checkerboard_piece_num[player][quadrant];
    int sub = 0, l_sub = 0, r_sub = 0;
    for (int k = 1; k <= 6; k++) { //�ж��Ƿ��ео�����
        if (point.x - k > 0) {
            if (checkerboard_piece_num[player][quadrant - k * step] < 0) {
                l_sub++;
            }
        } else if (point.x - k == 0) {
            l_sub++;
        }

        if (point.x + k < 19) {
            if (checkerboard_piece_num[player][quadrant + k * step] < 0) {
                r_sub++;
            }
        } else if (point.x + k == 19) {
            r_sub++;
        }
    }
    if (l_sub > 0)
        sub++;
    if (r_sub > 0)
        sub++;
    if (sub == 0)
        return 0;
    else if (sub == 1)
        return 1;
    else
        return 9;
}
/*****************************************************************************************************/ // AI����

void SixPiece::CalculatQuardrantScore(std::vector<std::vector<int>> &table, const chromosome &gene, const int &temp,
                                      const int &num, const Point &point) {
    if (num <= 6)
        switch (num) {
            case 1:
                table[point.x][point.y] += 0;
                break;
            case 2:
                if (temp == 0)
                    table[point.x][point.y] += gene.huoer;
                else if (temp == 1)
                    table[point.x][point.y] += 1;
                else if (temp == 9)
                    table[point.x][point.y] += -10;

                break;
            case 3:
                if (temp == 0)
                    table[point.x][point.y] += gene.huosan;
                else if (temp == 1)
                    table[point.x][point.y] += gene.miansan;
                else if (temp == 9)
                    table[point.x][point.y] += -10;
                break;
            case 4:
                if (temp == 0) {
                    table[point.x][point.y] += gene.shuanghuosi;
                    break;
                }
                if (temp == 1) {
                    table[point.x][point.y] += gene.danhuosi;
                    break;
                } else if (temp == 9) {
                    table[point.x][point.y] += -10;
                    break;
                }
                break;
            case 5:
                if (temp == 0)
                    table[point.x][point.y] += gene.huowu;
                else if (temp == 1)
                    table[point.x][point.y] += gene.chongwu;
                else if (temp == 9) {
                    table[point.x][point.y] += -10;
                }
                break;
            case 6:
                table[point.x][point.y] += 8888888;
                break;
            default:;
        }
    else
        table[point.x][point.y] += 8888888;
}

void SixPiece::Grade(const std::vector<std::vector<int>> &checkerboard,
                     const std::vector<std::vector<int>> &checkerboard_piece_num, std::vector<std::vector<int>> &table,
                     const int ply,
                     const chromosome &gene) //grade
{
    int x, y, k, quadrant1, quadrant2, quadrant3, quadrant4;
    int enemy = 1;
    int player = ply;
    int heng, zong, zuo, you;
    (enemy == ply) ? (enemy = 2) : (enemy = 1);

    for (x = 1; x <= 19; x++) {
        for (y = 1; y <= 19; y++) {
            heng = 1, zong = 1, zuo = 1, you = 1;

            if (checkerboard[x][y] == 0) {
                int l_heng = 0, l_zong = 0, l_zuo = 0, l_you = 0, r_heng = 0, r_zong = 0, r_zuo = 0, r_you = 0;
                quadrant1 = (y - 1) * 19 + x, quadrant2 = 19 * (y - 1) + x + 400, quadrant3 =
                        19 * (y - 1) + x + 800, quadrant4 = 19 * (y - 1) + x + 1200;

                int temp = CheckCheckerBoard(checkerboard_piece_num, 1, quadrant1, player, enemy, {x, y});
                int temp2 = CheckCheckerBoard(checkerboard_piece_num, 19, quadrant2, player, enemy, {x, y});
                int temp3 = CheckCheckerBoard(checkerboard_piece_num, 20, quadrant3, player, enemy, {x, y});
                int temp4 = CheckCheckerBoard(checkerboard_piece_num, 18, quadrant4, player, enemy, {x, y});
                if (x - 1 > 0) {
                    l_heng = checkerboard_piece_num[ply][quadrant1 - 1];
                    l_zong = checkerboard_piece_num[ply][quadrant2 - 19];
                    l_zuo = checkerboard_piece_num[ply][quadrant3 - 20];
                    l_you = checkerboard_piece_num[ply][quadrant4 - 18];
                }
                if (x + 1 <= 19) {
                    r_heng = checkerboard_piece_num[ply][quadrant1 + 1];
                    r_zong = checkerboard_piece_num[ply][quadrant2 + 19];
                    r_zuo = checkerboard_piece_num[ply][quadrant3 + 20];
                    r_you = checkerboard_piece_num[ply][quadrant4 + 18];
                }
                CalculatQuardrantScore(table, gene, temp, l_heng + r_heng, {x, y});
                CalculatQuardrantScore(table, gene, temp2, l_zong + r_zong, {x, y});
                CalculatQuardrantScore(table, gene, temp3, l_zuo + r_zuo, {x, y});
                CalculatQuardrantScore(table, gene, temp4, l_you + r_you, {x, y});
            }
        }
    }
}

void SixPiece::Search(const std::vector<std::vector<int>> &table, const int &player, int &x, int &y,
                      const std::vector<std::vector<int>> &checkerboard)   //搜索函数 找出评分表中分值最大的位置
{
    int i, j;
    int max, max_x, max_y;
    int num = 0, time = 0;

    max = 0;
    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            if (!checkerboard[i][j] && table[i][j] && table[i][j] > max) {
                max = table[i][j];
                max_x = i;
                max_y = j;
            }
        }
    }
    x = max_x;
    y = max_y;
    if (!checkerboard[7][7] && !max) {
        x = 7;
        y = 7;
        return;
    }
    //	printf("\nmax=%d %c%c \n",max,i+'A'-1,j+'A'-1);
}

Point SixPiece::AI(std::shared_ptr<TemporaryData> tem)  //AI函数 先调用评分函数，对双方棋盘评分， 再调用搜索函数，找出最优位置
{
    int x1_max, y1_max;
    int x2_max, y2_max;
    std::vector<std::vector<int>> table_cmp(20, std::vector<int>(20));
    std::vector<std::vector<int>> table_ply(20, std::vector<int>(20));
    int player2;

    if (player == 1)
        player2 = 2;
    else
        player2 = 1;
    winner = 0;
    /*printf("checkerboard=\n");
    for(int i=1;i<=19;i++)
    {printf("\n");
        for(int j=1;j<=19;j++)
        {
            printf("%d ",checkerboard[i][j]);
        }
    }*/
    Grade(checkerboard, checkerboard_piece_num, table_cmp, player, r1);
    Grade(checkerboard, checkerboard_piece_num, table_ply, player2, r1);

    Search(table_cmp, player, x1_max, y1_max, checkerboard);
    Search(table_ply, player2, x2_max, y2_max, checkerboard);

    //	printf("\n player==%d  �����tableֵΪ %d %d\n",player,table_ply[x2_max][y2_max],table_cmp[x1_max][y1_max]) ;
    winner = WhoIsWinner(checkerboard_piece_num, player);

    if (table_cmp[x1_max][y1_max] >= table_ply[x2_max][y2_max]) {
        {
            return {x1_max, y1_max};
        }
        // Record(checkerboard,checkerboard_piece_num,player,x1_max,y1_max);//
    } else {
        return {x2_max, y2_max};
        //	  Record(checkerboard,checkerboard_piece_num,player,x2_max,y2_max);
    }
}

void SixPiece::SelectionOfChampions(const std::vector<std::vector<int>> &population) {
    std::vector<int> a[20];
    std::vector<int> b, c;

    for (int i = 1; i < 20; i++) {
        a[i] = population[i];
    }
    for (int i = 1; i <= 20; i++) {
        for (int j = i + 1; j <= 20; j++) {
            if (a[i].back() < a[j].back()) {
                swap(a[i], a[j]);
            }
        }
    }
    for (int j = 1; j <= 5; j++)
        champion[j] = a[j];
}

chromosome SixPiece::ChromosomeSwitch(const std::vector<int> &population) {
    chromosome popu;
    popu.chongwu = population[Gene::chongwu];
    popu.danhuosi = population[Gene::danhuosi];
    popu.huoer = population[Gene::huoer];
    popu.huosan = population[Gene::huosan];
    popu.huowu = population[Gene::huowu];
    popu.miansan = population[Gene::miansan];
    popu.miansi = population[Gene::miansi];
    popu.shuanghuosi = population[Gene::shuanghuosi];
    popu.adaptability = population[Gene::adaptability];
    return popu;
}

void SixPiece::CacheTemporaryDate(const std::shared_ptr<TrainPiectElement> board, std::shared_ptr<TemporaryData> tem) {
    tem->general_checkerboard = board->general_checkerboard;
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
}

void SixPiece::FindMaxAndAddScore(std::shared_ptr<TemporaryData> tem, int &x, int &y) {
    long long int sum_score = 0;
    if (tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Left)] >= 6 ||
        tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::LeftUp)] >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Up)] >= 6
        || tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::RightUp)] >= 6) {
        tem->six = {x, y};
    }
        sum_score = GetScore(tem,x,y,0)+GetScore(tem,x,y,1)+GetScore(tem,x,y,2)+GetScore(tem,x,y,3);


}

void SixPiece::UpdateGrade(std::shared_ptr<TemporaryData> tem, int &player) {
    for (int i = 0; i < tem->len; i++) {
        for (int j = 0; j < tem->len; j++) {
            if (tem->general_checkerboard[i][j] == 0) {
                CheckAndAddScore(tem, player, i, j);
            }
        }
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
            step_x = -1;
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
int SixPiece::GetPieceNum(std::shared_ptr<TemporaryData> tem, int &player,int &x,int &y,int type)
{

    switch(type)
    {
        case 0:
            if (x > 0 && tem->general_checkerboard[x - 1][y] == player) {
                int num = tem->direction_checkerboard[x -
                                                      1][y].direction_piece_num[static_cast<int>(Direction::Left)];
                int real_num = num + 1;
                tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                while (--num) {
                    tem->direction_checkerboard[x -
                                                num][y].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                }
            } else if (x == 0 || tem->general_checkerboard[x - 1][y] != player) {
                tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Left)] = 1;
            }
            case 1:
                if (y > 0 && tem->general_checkerboard[x][y - 1] == player) {
                    int num = tem->direction_checkerboard[x][y -
                                                             1].direction_piece_num[static_cast<int>(Direction::Up)];
                    int real_num = num + 1;
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                    while (--num) {
                        tem->direction_checkerboard[x][y -
                                                       num].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                    }
                } else if (y == 0 || tem->general_checkerboard[x][y - 1] != player) {
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::Up)] = 1;
                }
            case 2:
                if (y > 0 && x > 0 && tem->general_checkerboard[x - 1][y - 1] == player) {
                    int num = tem->direction_checkerboard[x - 1][y -
                                                                 1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
                    int real_num = num + 1;
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                    while (--num) {
                        tem->direction_checkerboard[x - num][y -
                                                             num].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                    }
                } else if (y == 0 || x == 0 || tem->general_checkerboard[x - 1][y - 1] != player) {
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::LeftUp)] = 1;
                }
            case 3:
                if (y > 0 && x < tem->len - 1 && tem->general_checkerboard[x + 1][y - 1] == player) {
                    int num = tem->direction_checkerboard[x + 1][y -
                                                                 1].direction_piece_num[static_cast<int>(Direction::RightUp)];
                    int real_num = num + 1;
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                    while (--num) {
                        tem->direction_checkerboard[x + num][y -
                                                             num].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                    }
                } else if (y == 0 || x == tem->len - 1 || tem->general_checkerboard[x + 1][y - 1] != player) {
                    tem->direction_checkerboard[x][y].direction_piece_num[static_cast<int>(Direction::RightUp)] = 1;
                }
    }


}
void SixPiece::UpdatePieceType(std::shared_ptr<TemporaryData> tem, int &player) {
    int len = tem->general_checkerboard.size();
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (tem->general_checkerboard[i][j] == 0) {

                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Left)] = GetPieceType(
                        tem, player, static_cast<int>(Direction::Left), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::Up)] = GetPieceType(
                        tem, player, static_cast<int>(Direction::Up), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::LeftUp)] = GetPieceType(
                        tem, player, static_cast<int>(Direction::LeftUp), i, j);
                tem->direction_checkerboard[i][j].direction_piece_type[static_cast<int>(Direction::RightUp)] = GetPieceType(
                        tem, player, static_cast<int>(Direction::RightUp), i, j);

            }
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
}

void SixPiece::UpdateQuadrantStatus(std::shared_ptr<TemporaryData> tem, int &player) {

    tem->len = tem->general_checkerboard.size();
    int zong_len = tem->general_checkerboard[0].size();
    tem->direction_checkerboard.resize(tem->len, std::vector<PieceDirection>(tem->len));
    InitializePieceDirectionSpace(tem);
    if (tem->direction_checkerboard.empty())
        for (int i = 0; i < tem->len; i++) {
            for (int j = 0; j < tem->len; j++) {
                if (tem->general_checkerboard[i][j] == player) {
                    if (i > 0 && tem->general_checkerboard[i - 1][j] == player) {
                        int num = tem->direction_checkerboard[i -
                                                              1][j].direction_piece_num[static_cast<int>(Direction::Left)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i -
                                                        num][j].direction_piece_num[static_cast<int>(Direction::Left)] = real_num;
                        }
                    } else if (i == 0 || tem->general_checkerboard[i - 1][j] != player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Left)] = 1;
                    }

                    if (j > 0 && tem->general_checkerboard[i][j - 1] == player) {
                        int num = tem->direction_checkerboard[i][j -
                                                                 1].direction_piece_num[static_cast<int>(Direction::Up)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i][j -
                                                           num].direction_piece_num[static_cast<int>(Direction::Up)] = real_num;
                        }
                    } else if (j == 0 || tem->general_checkerboard[i][j - 1] != player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::Up)] = 1;
                    }

                    if (j > 0 && i > 0 && tem->general_checkerboard[i - 1][j - 1] == player) {
                        int num = tem->direction_checkerboard[i - 1][j -
                                                                     1].direction_piece_num[static_cast<int>(Direction::LeftUp)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i - num][j -
                                                                 num].direction_piece_num[static_cast<int>(Direction::LeftUp)] = real_num;
                        }
                    } else if (j == 0 || i == 0 || tem->general_checkerboard[i - 1][j - 1] != player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::LeftUp)] = 1;
                    }

                    if (j > 0 && i < tem->len - 1 && tem->general_checkerboard[i + 1][j - 1] == player) {
                        int num = tem->direction_checkerboard[i + 1][j -
                                                                     1].direction_piece_num[static_cast<int>(Direction::RightUp)];
                        int real_num = num + 1;
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                        while (--num) {
                            tem->direction_checkerboard[i + num][j -
                                                                 num].direction_piece_num[static_cast<int>(Direction::RightUp)] = real_num;
                        }
                    } else if (j == 0 || i == tem->len - 1 || tem->general_checkerboard[i + 1][j - 1] != player) {
                        tem->direction_checkerboard[i][j].direction_piece_num[static_cast<int>(Direction::RightUp)] = 1;
                    }

                }
            }
        }
}

int
SixPiece::PopulationPlayAGame(const int &player1, const int &player2, const std::shared_ptr<TrainPiectElement> board) {

    std::shared_ptr<TemporaryData> ply_1st, ply_2nd;
    CacheTemporaryDate(board, ply_1st);
    CacheTemporaryDate(board, ply_2nd);

    int times = board->convergence_step;

    while (times--) {
        int winner1 = 0, winner2 = 0;
        Point pos1, pos2;
        chromosome chro1, chro2;

        pos1 = ply_1st->ma.begin()->second;
        //	printf("\n%d ",winner1);
        Record(checkerboard1, checkerboard_piece_num1, 1, pos1.x, pos1.y);
        if (winner1) {
            return 1; // population1赢
        }
        pos2 = ply_2nd->ma.begin()->second;
        Record(checkerboard1, checkerboard_piece_num2, 2, pos2.x, pos2.y);
        if (winner2) {
            return 2; // population2赢
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
        easythreadpool pool{2};
        std::unordered_map<int, int> ma;//contest use  multiple threads
        for (int i = 0; i < pk_queue.size(); i += 2) {
            pool.enqueue(SingleContest, pk_queue[i], pk_queue[i + 1], board, ma);
        }
        UpdateNextRoundQueue(pk_queue, ma);
    }
    SelectChampion(board, pk_queue);
}


void SixPiece::SingleContest(int &player1, int &player2, std::shared_ptr<TrainPiectElement> board,
                             std::unordered_map<int, int> &ma) {
    int win_player;
    for (int i = 0; i < 3; i++) {
        int black_winner = PopulationPlayAGame(board);
        int white_winner = PopulationPlayAGame(board);
        switch (black_winner) {
            case 0:
                board->population[player1].back() += 25;
                board->population[player2].back() += 25;
                break;
            case 1:
                board->population[player1].back() += 50;
                break;
            case 2:
                board->population[player2].back() += 50;
                break;
        }
        switch (white_winner) {
            case 0:
                board->population[player1].back() += 25;
                board->population[player2].back() += 25;
                break;
            case 1:
                board->population[player1].back() += 50;
                break;
            case 2:
                board->population[player2].back() += 50;
                break;
        }
    }
    win_player = board->population[player1].back() < board->population[player2].back() ? player2 : player1;
    ma[win_player] = 1;
}

//void SixPiece::ReproduceTheNextGeneration(std::shared_ptr<TrainPiectElement> board)
//{
//
//}

void SixPiece::MakeChampion(std::shared_ptr<TrainPiectElement> board) {
    PopulationContest(board);
    MakePopulationWhenTrain(board);
}

// void SixPiece::ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
//                           int checkerboard_piece_num1[][1700])
// {
//     memcpy(checkerboard1, checkerboard, sizeof(int) * 20 * 20);
//     memcpy(checkerboard_piece_num1, checkerboard_piece_num, sizeof(int) * 3 * 1700);
// }

void SixPiece::Train(std::shared_ptr<TrainPiectElement> &board) {


    while (board->train_time--)                                                                      //�������ٴ�
    {
        MakeChampion(board);
    }
}

void SixPiece::SignalCommunicationThread(std::vector<int> Chromosome, std::string str) {
    int winner = 0;
    char message[256];
    int player = 0; //���� 1��ʾ�� 2��ʾ��
    // int step_num = 0; //������¼
    std::vector<std::vector<int>> checkerboard(20, std::vector<int>(20)); //���̼�¼
    std::vector<std::vector<int>> checkerboard_piece_num(3, std::vector<int>(1700));
    int enemy = 0;

    int train_time = 50;
    chromosome r;
    int x_position1, y_position1, x_position2, y_position2;
    char x_position_string_1, x_position_string_2, y_position_string_1, y_position_string_2;
    std::cout << "aa" << std::endl;
    while (1) {
        fflush(stdout);
        scanf("%s", message);
        if (strcmp(message, "move") == 0) {
            scanf("%s", message);
            fflush(stdin);
            x_position1 = message[0] - 'A' + 1;
            y_position1 = message[1] - 'A' + 1;
            x_position2 = message[2] - 'A' + 1;
            y_position2 = message[3] - 'A' + 1;

            Record(checkerboard, checkerboard_piece_num, enemy, x_position1, y_position1);
            Record(checkerboard, checkerboard_piece_num, enemy, x_position2, y_position2);
            Train(checkerboard, checkerboard_piece_num, train_time, winner, enemy);

            memcpy(&r, &champion[2], sizeof(r));
            Point pos1, pos2;
            pos1 = AI(checkerboard, checkerboard_piece_num, player, winner, r);
            Record(checkerboard, checkerboard_piece_num, player, pos1.x, pos1.y);
            x_position_string_1 = pos1.x + 'A' - 1;
            y_position_string_1 = pos1.y + 'A' - 1;
            pos2 = AI(checkerboard, checkerboard_piece_num, player, winner, r);
            Record(checkerboard, checkerboard_piece_num, player, pos2.x, pos2.y);
            x_position_string_2 = pos2.x + 'A' - 1;
            y_position_string_2 = pos2.y + 'A' - 1; // printf(" %d",num++);
            printf("\n");
            printf("move %c%c%c%c\n", x_position_string_1, y_position_string_1, x_position_string_2,
                   y_position_string_2);
        } else if (strcmp(message, "new") == 0) {
            scanf("%s", message);
            fflush(stdin);
            if (strcmp(message, "black") == 0) {
                enemy = 2;
                player = 1;
            } else {
                player = 2;
                enemy = 1;
            }
            Init();
            if (player == 1) {
                char s1 = 'A' + 7, s2 = 'A' + 7;
                Record(checkerboard, checkerboard_piece_num, player, 7, 7);
                printf("\n");
                printf("move GG@@\n");
            }
        } else if (strcmp(message, "error") == 0) //�ŷ�����?
        {
            fflush(stdin);
        } else if (strcmp(message, "name?") == 0) //ѯ����������
        {
            fflush(stdin);
            printf("name Parsifal\n");
        } else if (strcmp(message, "end") == 0) //�Ծֽ���
        {
            fflush(stdin);
        } else if (strcmp(message, "quit") == 0) {
            fflush(stdin);
            printf("Quit!\n");
            break;
        }

        // printf("\n%d ",winner);
    }
}

void SixPiece::Play(int &type, std::shared_ptr<TrainPiectElement> board) {
    Train(board);
}

/**************************************************************************************************************/
//int main() //������
//{
//  SixPiece a;
//  a.SignalCommunication();
//}