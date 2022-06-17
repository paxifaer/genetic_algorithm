#include "SixPiece.h"
void SixPiece::Init(int checkerboard[][20], int checkerboard_piece_num[][1700])                //初始化函数，将记录棋子的数组初始化
{
    int i, j;

    for (i = 1; i <= 19; i++) {//初始换棋盘状态
        for (j = 1; j <= 19; j++) {
            checkerboard[i][j] = 0;
        }
    }

    for (i = 0; i < 3; i++) {
        for (j = 1; j <= 361; j++) {
            checkerboard_piece_num[i][j] = 0;
        }
    }


}




/***********************************************************************************************/   //六子棋核心部分（先后手，胜负判定，棋盘记录）


void SixPiece::Record(int checkerboard[][20], int checkerboard_piece_num[3][1700], const int player, int x_position,
            int y_position)              //记录棋子、棋手的情况
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

    int left_piece_num = 0, right_piece_num = 0;//横连
    if (quadrant1 - 1 > 0)
        left_piece_num = checkerboard_piece_num[player][quadrant1 - 1];
    if (quadrant1 + 1 <= 361)
        right_piece_num = checkerboard_piece_num[player][quadrant1 + 1];


    if (left_piece_num >= 0)
        checkerboard_piece_num[player][quadrant1] += left_piece_num;
    if (right_piece_num >= 0)
        checkerboard_piece_num[player][quadrant1] += right_piece_num;


    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++) {
            checkerboard_piece_num[player][quadrant1 - sd] = checkerboard_piece_num[player][quadrant1];
//printf("\ncheckerboard_piece_num[player][quadrant-sd]=%d",checkerboard_piece_num[player][quadrant1-sd]);
        }
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++) {
            checkerboard_piece_num[player][quadrant1 + sd] = checkerboard_piece_num[player][quadrant1];
//printf("\n%d",checkerboard_piece_num[player][quadrant1]);
        }
//printf("\n l1=%d r1=%d",l,r);


    left_piece_num = 0, right_piece_num = 0;//纵连
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
//printf("\n l2=%d r2=%d",l,r);


    left_piece_num = 0, right_piece_num = 0;//左斜连
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
//printf("\n l3=%d r3=%d",l,r);

    left_piece_num = 0, right_piece_num = 0;//右斜连
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

//printf("\n l4=%d r4=%d\n",l,r);

}

int SixPiece::WhoIsWinner(int checkerboard_piece_num[][1700], const int player)                   //胜负判断
{
    int i;
    int temp;
    int enemy = 1;
    enemy == player ? enemy = 2 : enemy = 1;
    temp = 0;
    for (i = 1; i <= 1600; i++) {
        if (checkerboard_piece_num[player][i] >= 0) {
            temp++;
            if (checkerboard_piece_num[player][i] >= 6) {
                return player;
            }
        }
    }
}



/*****************************************************************************************************/           //AI核心

void SixPiece::Grade(const int checkerboard[][20], const int checkerboard_piece_num[][1700], int table[][20], const int ply,
           chromosome gene)         //棋盘评分的程序，给予棋盘每个点一定的分数
{
    int x, y, k, r = 0, l = 0, quadrant1, quadrant2, quadrant3, quadrant4;
    int temp = 0;
    int enemy = 1;
    int player = ply;
    int heng, zong, zuo, you;
    (enemy == ply) ? (enemy = 2) : (enemy = 1);


    for (x = 1; x <= 19; x++) {

        for (y = 1; y <= 19; y++) {

            heng = 1, zong = 1, zuo = 1, you = 1;

            if (checkerboard[x][y] == 0) {
                quadrant1 = (y - 1) * 19 + x, quadrant2 = 19 * (y - 1) + x + 400, quadrant3 =
                        19 * (y - 1) + x + 800, quadrant4 =
                        19 * (y - 1) + x + 1200;

                l = 0, r = 0;//横连
                if (x - 1 > 0)
                    l = checkerboard_piece_num[ply][quadrant1 - 1];
                if (x + 1 <= 19)
                    r = checkerboard_piece_num[player][quadrant1 + 1];
                if (l > 0)
                    heng += l;
                if (r > 0)
                    heng += r;

                temp = 0;
                int sub = 0;
                for (int k = 1; k <= 6 - heng; k++) {
                    if (l >= 0)
                        if ((checkerboard_piece_num[player][quadrant1 - l - k] < 0 || (x - l - k) == 0))//左边界
                        {
                            sub++;
                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant1 + k + r] < 0 || (x + r + k) == 19)//右边界
                        {
                            sub++;
                        }

                    if (sub == 0) {
                        temp = 0;
                    } else if (sub == 1)
                        temp = 1;
                    else temp = 9;
                }

                if (heng <= 6)
                    switch (heng) {
                        case 1:
                            table[x][y] += 0;
                            break;
                        case 2:
                            if (temp == 0)
                                table[x][y] += gene.huoer;
                            else if (temp == 1)
                                table[x][y] += 1;
                            else if (temp == 9)
                                table[x][y] += -10;

                            break;
                        case 3:
                            if (temp == 0)
                                table[x][y] += gene.huosan;
                            else if (temp == 1)
                                table[x][y] += gene.miansan;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 4:
                            if (temp == 0) {
                                table[x][y] += gene.shuanghuosi;
                                break;
                            }
                            if (temp == 1) {
                                table[x][y] += gene.danhuosi;
                                break;
                            } else if (temp == 9) {
                                table[x][y] += -10;
                                break;
                            }
                            break;
                        case 5:
                            if (temp == 0)
                                table[x][y] += gene.huowu;
                            else if (temp == 1)
                                table[x][y] += gene.chongwu;
                            else if (temp == 9) {
                                table[x][y] += -10;
                            }
                            break;
                        case 6:
                            table[x][y] += 8888888;
                            break;
                        default:;
                    }

                if (heng >= 7) table[x][y] += 8888888;

                l = 0, r = 0;//纵连
                if (y - 1 > 0)
                    l = checkerboard_piece_num[player][quadrant2 - 19];
                if (y + 1 < 20)
                    r = checkerboard_piece_num[player][quadrant2 + 19];

                if (l >= 0)
                    zong += l;
                if (r >= 0)
                    zong += r;

                sub = 0;
                for (int k = 1; k <= 6 - zong; k++)
                    if ((6 - zong) > 0) {

                        if (l >= 0)
                            if ((checkerboard_piece_num[player][quadrant2 - l * 19 - k * 19] < 0 ||
                                 (y - l - k) == 0))//左边界
                            {
                                sub++;

                            }
                        if (r >= 0)
                            if (checkerboard_piece_num[player][quadrant2 + k * 19 + r * 19] < 0 ||
                                (y + r + k) == 19)//右边界
                            {
                                sub++;

                            }

                        if (sub == 0) {
                            temp = 0;
                        } else if (sub == 1)
                            temp = 1;
                        else temp = 9;

                    }

                if (zong <= 6)
                    switch (zong) {
                        case 1:
                            table[x][y] += 0;
                            break;
                        case 2:
                            if (temp == 0)
                                table[x][y] += gene.huoer;
                            else if (temp == 1)
                                table[x][y] += 1;
                            else if (temp == 9)
                                table[x][y] += -10;

                            break;
                        case 3:
                            if (temp == 0)
                                table[x][y] += gene.huosan;
                            else if (temp == 1)
                                table[x][y] += gene.miansan;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 4:
                            if (temp == 0) {
                                table[x][y] += gene.shuanghuosi;
                                break;
                            }
                            if (temp == 1) {
                                table[x][y] += gene.danhuosi;
                                break;
                            } else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 5:
                            if (temp == 0)
                                table[x][y] += gene.huowu;
                            else if (temp == 1)
                                table[x][y] += gene.chongwu;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;

                        case 6:
                            table[x][y] += 8888888;
                            break;
                        default:;
                    }
                if (zong >= 7) table[x][y] += 8888888;

                l = 0, r = 0;//左斜连
                if ((x - 1) > 0 && (y - 1) > 0)
                    l = checkerboard_piece_num[player][quadrant3 - 19 - 1];
                if ((x + 1) <= 19 && (y + 1) <= 19)
                    r = checkerboard_piece_num[player][quadrant3 + 19 + 1];
                if (l >= 0)
                    zuo += l;
                if (r >= 0)
                    zuo += r;


                sub = 0;
                for (int k = 1; k <= 6 - zuo; k++) {

                    if (l >= 0)
                        if (checkerboard_piece_num[player][quadrant3 - l * 20 - k * 20] < 0 ||
                            ((y - l - k) == 0 && (x - l - k) == 0))//左边界
                        {
                            sub++;

                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant3 + k * 20 + r * 20] < 0 ||
                            ((y + r + k) == 0 && (x + r + k) == 0))//右边界
                        {
                            sub++;

                        }

                    if (sub == 0) {
                        temp = 0;
                    } else if (sub == 1)
                        temp = 1;
                    else temp = 9;

                }

                if (zuo <= 6) {
                    switch (zuo) {
                        case 1:
                            table[x][y] += 0;
                            break;
                        case 2:
                            if (temp == 0)
                                table[x][y] += gene.huoer;
                            else if (temp == 1)
                                table[x][y] += 1;
                            else if (temp == 9)
                                table[x][y] += -10;

                            break;
                        case 3:
                            if (temp == 0)
                                table[x][y] += gene.huosan;
                            else if (temp == 1)
                                table[x][y] += gene.miansan;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 4:
                            if (temp == 0) {
                                table[x][y] += gene.shuanghuosi;
                                break;
                            }
                            if (temp == 1) {
                                table[x][y] += gene.danhuosi;
                                break;
                            } else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 5:
                            if (temp == 0)
                                table[x][y] += gene.huowu;
                            else if (temp == 1)
                                table[x][y] += gene.chongwu;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 6:
                            table[x][y] += 8888888;
                            break;
                        default:;
                    }

                }
                if (zuo >= 7) table[x][y] += 8888888;


                l = 0, r = 0;//右斜连
                if (quadrant4 - 19 + 1 > 1200) {

                    l = checkerboard_piece_num[player][quadrant4 - 18];
                }
                if (quadrant4 + 19 - 1 < 1560) {
                    r = checkerboard_piece_num[player][quadrant4 + 18];
                }
                if (l >= 0)
                    you += l;
                if (r >= 0)
                    you += r;


                sub = 0;
                for (int k = 1; k <= 6 - you; k++) {

                    if (l >= 0)
                        if (checkerboard_piece_num[player][quadrant4 - l * 18 - k * 18] < 0 ||
                            ((y - l - k) == 0 && (x + l + k) == 0))//左边界
                        {
                            sub++;

                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant4 + k * 18 + r * 18] < 0 ||
                            ((y + r + k) == 0 && (x - r - k) == 0))//右边界
                        {
                            sub++;

                        }

                    if (sub == 0) {
                        temp = 0;
                    } else if (sub == 1)
                        temp = 1;
                    else temp = 9;

                }

                if (you <= 6)
                    switch (you) {
                        case 1:
                            table[x][y] += 0;
                            break;
                        case 2:
                            if (temp == 0)
                                table[x][y] += gene.huoer;
                            else if (temp == 1)
                                table[x][y] += 1;
                            else if (temp == 9)
                                table[x][y] += -10;

                            break;
                        case 3:
                            if (temp == 0)
                                table[x][y] += gene.huosan;
                            else if (temp == 1)
                                table[x][y] += gene.miansan;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 4:
                            if (temp == 0) {
                                table[x][y] += gene.shuanghuosi;
                                break;
                            }
                            if (temp == 1) {
                                table[x][y] += gene.danhuosi;
                                break;
                            } else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 5:
                            if (temp == 0)
                                table[x][y] += gene.huowu;
                            else if (temp == 1)
                                table[x][y] += gene.chongwu;
                            else if (temp == 9)
                                table[x][y] += -10;
                            break;
                        case 6:
                            table[x][y] += 8888888;
                            break;
                        default:;
                    }

                if (you >= 7) table[x][y] += 8888888;

            }
        }
    }

}

void SixPiece::Search(int table[][20], int player, int &x, int &y, int checkerboard[][20])       //搜索函数 找出评分表中分值最大的位置
{
    int i, j;
    int max;
    int num = 0, time = 0;

    max = 0;
    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            if (!checkerboard[i][j] && table[i][j] && table[i][j] > max) {
                max = table[i][j];
            }
        }
    }

    if (!checkerboard[7][7] && !max) {
        x = 7;
        y = 7;
        return;
    }

    for (i = 1; i <= 19; i++) {
        for (j = 1; j <= 19; j++) {
            if (!checkerboard[i][j] && table[i][j] == max) {

                x = i;
                y = j;
                break;
            }
        }
    }
//	printf("\nmax=%d %c%c \n",max,i+'A'-1,j+'A'-1);

}

Point SixPiece::AI(int checkerboard[][20], int checkerboard_piece_num[][1700], int player, int &winner,
         chromosome r1)          //AI函数 先调用评分函数，对双方棋盘评分， 再调用搜索函数，找出最优位置
{
    int x1_max, y1_max;
    int x2_max, y2_max;
    int table_cmp[20][20] = {0};
    int table_ply[20][20] = {0};
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

//	printf("\n player==%d  的最大table值为 %d %d\n",player,table_ply[x2_max][y2_max],table_cmp[x1_max][y1_max]) ;
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

int SixPiece::PopulationPlayAGame(chromosome population1, chromosome population2, int checkerboard[][20],
                        int checkerboard_piece_num[][1700]) {
    int convergence_limit = 50;
    int flag = 0;
    int checkerboard1[20][20], checkerboard_piece_num1[3][1700], checkerboard_piece_num2[3][1700];
    ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num1);
    ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num2);
    int winner1 = 0, winner2 = 0;

    while (convergence_limit--) {
        int winner1 = 0, winner2 = 0;
        Point pos1, pos2;
        pos1 = AI(checkerboard1, checkerboard_piece_num1, 1, winner1, population1);
        //	printf("\n%d ",winner1);
        Record(checkerboard1, checkerboard_piece_num1, 1, pos1.x, pos1.y);
        if (winner1) {
            return 1;//population1赢
        }
        pos2 = AI(checkerboard1, checkerboard_piece_num2, 2, winner2, population2);
        Record(checkerboard1, checkerboard_piece_num2, 2, pos2.x, pos2.y);
        if (winner2) {
            return 2;//population2赢
        }
    }
    return 0;//平局
}

void SixPiece::Championships(int checkerboard1[][20], int checkerboard_piece_num1[][1700], int player) {
    int black_winner = 0, white_winner = 0;
    for (int population_sequence = 1; population_sequence <= 4; population_sequence++)//20组染色体分成五组，每组四个，这四个染色体进行比较。
    {
        for (int population_of_self = population_sequence; population_of_self <= 20; population_of_self += 4) {
            for (int population_of_enemy = population_of_self + 1;
                 population_of_enemy <= population_of_self + 3; population_of_enemy++) {

                black_winner = PopulationPlayAGame(population[population_of_self], population[population_of_enemy],
                                                   checkerboard1,
                                                   checkerboard_piece_num1);
                white_winner = PopulationPlayAGame(population[population_of_enemy], population[population_of_self],
                                                   checkerboard1,
                                                   checkerboard_piece_num1);
                if (black_winner == 0) {
                    population[population_of_self].adaptability += 25;
                    population[population_of_enemy].adaptability += 25;
                } else if (black_winner == 1) {
                    population[population_of_self].adaptability += 50;
                    population[population_of_enemy].adaptability += 0;
                } else if (black_winner == 2) {
                    population[population_of_enemy].adaptability += 50;
                    population[population_of_self].adaptability += 0;
                }
                if (white_winner == 0) {
                    population[population_of_self].adaptability += 25;
                    population[population_of_enemy].adaptability += 25;
                } else if (white_winner == 1) {
                    population[population_of_self].adaptability += 50;
                    population[population_of_enemy].adaptability += 0;
                } else if (white_winner == 2) {
                    population[population_of_enemy].adaptability += 50;
                    population[population_of_self].adaptability += 0;
                }

            }
        }
    }

    int fitness_standard = 0, score_sum = 0;
    for (int i = 1; i <= 20; i++)
        score_sum += population[i].adaptability;
    fitness_standard = score_sum / 20;
    SelectionOfChampions(population);//得出冠军的五个序列；
    CrossingOverPrepare(champion, fitness_standard); //

}

void SixPiece::ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
                int checkerboard_piece_num1[][1700]) {
    memcpy(checkerboard1, checkerboard, sizeof(int) * 20 * 20);
    memcpy(checkerboard_piece_num1, checkerboard_piece_num, sizeof(int) * 3 * 1700);
}

void SixPiece::Train(int checkerboard[][20], int checkerboard_piece_num[][1700], int train_time, int winner, int player) {
    int checkerboard_piece_num1[3][1700];
    int checkerboard1[20][20];
    ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num1);//拷贝棋盘记录
    while (train_time--)//进化多少代
    {
        Championships(checkerboard1, checkerboard_piece_num1, player);
    }
}

void SixPiece::renji() {
    int winner = 0;
    char message[256];
    int player = 0;          //棋手 1表示甲 2表示乙
    //int step_num = 0; //步数记录
    int checkerboard[20][20] = {{0}};        //棋盘记录
    int checkerboard_piece_num[3][1700] = {{0}};
    int enemy = 0;

    int train_time = 50;
    chromosome r;
    int x_position1, y_position1, x_position2, y_position2;
    char x_position_string_1, x_position_string_2, y_position_string_1, y_position_string_2;
    while (1) {
        fflush(stdout);
        //记录游戏中的胜者  0表示无胜者 1表示甲胜 2表示乙胜 3表示平局
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

            //	memcpy(&r,&population[1],sizeof(r));
            memcpy(&r, &champion[2], sizeof(r));
            Point pos1, pos2;
            pos1 = AI(checkerboard, checkerboard_piece_num, player, winner, r);//待定
            Record(checkerboard, checkerboard_piece_num, player, pos1.x, pos1.y);
            x_position_string_1 = pos1.x + 'A' - 1;
            y_position_string_1 = pos1.y + 'A' - 1;
            pos2 = AI(checkerboard, checkerboard_piece_num, player, winner, r);//待定
            Record(checkerboard, checkerboard_piece_num, player, pos2.x, pos2.y);
            x_position_string_2 = pos2.x + 'A' - 1;
            y_position_string_2 = pos2.y + 'A' - 1; //printf(" %d",num++);
            //	printf("\n冠军数组 染色体值为：%d %d %d %d %d %d  \n",champion[2].huowu,champion[2].chongwu,champion[2].shuanghuosi,champion[2].huosan,champion[2].huoer,champion[2].adaptability);
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
            Init(checkerboard, checkerboard_piece_num);
            if (player == 1) {
                char s1 = 'A' + 7, s2 = 'A' + 7;
                Record(checkerboard, checkerboard_piece_num, player, 7, 7);
                printf("\n");
                printf("move GG@@\n");

            }
        } else if (strcmp(message, "error") == 0)//着法错误?
        {
            fflush(stdin);
        } else if (strcmp(message, "name?") == 0)//询问引擎名称
        {
            fflush(stdin);
            printf("name Parsifal\n");

        } else if (strcmp(message, "end") == 0)//对局结束
        {
            fflush(stdin);
        } else if (strcmp(message, "quit") == 0) {
            fflush(stdin);
            printf("Quit!\n");
            break;
        }

        //printf("\n%d ",winner);

    }
}

/**************************************************************************************************************/
int main()   //主函数
{
    srand((unsigned) time(NULL));
    for (int i = 1; i <= 20; i++)//给20组染色体定初值
    {
        i1 += 100;
        i2 += 20;
        i1 += 16;
        i1 += 8;
        i1 += 4;
        i1 += 2;
        i1 += 1;
        i1 += 1;
        huowu[i] = i1;
        chongwu[i] = i2;
        shuanghuosi[i] = i3;
        danhuosi[i] = i4;
        miansi[i] = i5;
        huosan[i] = i6;
        miansan[i] = i7;
        huoer[i] = i8;
        population[i].chongwu = chongwu[i];
        population[i].huowu = huowu[i];
        population[i].shuanghuosi = shuanghuosi[i];
        population[i].danhuosi = danhuosi[i];
        population[i].miansi = miansi[i];
        population[i].huoer = huoer[i];
        population[i].huosan = huosan[i];
        population[i].miansan = miansan[i];
    }

    memcpy(&champion[1], &population[1], sizeof(population[1]));
    memcpy(&champion[2], &population[2], sizeof(population[2]));
    memcpy(&champion[3], &population[3], sizeof(population[3]));
    memcpy(&champion[4], &population[4], sizeof(population[4]));
    memcpy(&champion[5], &population[5], sizeof(population[5]));
    renji();

}