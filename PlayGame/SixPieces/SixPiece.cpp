#include "SixPiece.h"
void SixPiece::Init()                //ï¿½ï¿½Ê¼ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â¼ï¿½ï¿½ï¿½Óµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ê¼ï¿½ï¿?
{

    for(int i=0;i<20;i++)
    {
        checkerboard.resize(20);
    }
     for(int i=0;i<3;i++)
    {
        checkerboard_piece_num.resize(1700);
    }

}

/***********************************************************************************************/   //¼ÇÂ¼


void SixPiece::Record(std::vector<std::vector<int>> &checkerboard, std::vector<std::vector<int>> &checkerboard_piece_num, const int player, int x_position,
            int y_position)              //ËÄ¸ö·½ÏòÆåÅÌ·ÖÊý
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

    int left_piece_num = 0, right_piece_num = 0;//ºáÁ¬
    if (quadrant1 - 1 > 0)
        left_piece_num = checkerboard_piece_num[player][quadrant1 - 1]>0?checkerboard_piece_num[player][quadrant1 - 1] : 0 ;
    if (quadrant1 + 1 <= 361)
        right_piece_num = checkerboard_piece_num[player][quadrant1 + 1]>0?checkerboard_piece_num[player][quadrant1 + 1]:0;;

    checkerboard_piece_num[player][quadrant1] += left_piece_num + right_piece_num;

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


    left_piece_num = 0, right_piece_num = 0;//×ÝÁ¬
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


    left_piece_num = 0, right_piece_num = 0;//×óÐ±Á¬
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

    left_piece_num = 0, right_piece_num = 0;//ÓÒÐ±Á¬
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

int SixPiece::WhoIsWinner(const std::vector<std::vector<int>> &checkerboard_piece_num, const int &player)                   //Ê¤ï¿½ï¿½ï¿½Ð¶ï¿½
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


int CheckCheckerBoard(const std::vector<std::vector<int>> &checkerboard_piece_num,const int &step,const int &quadrant,const int &player,const int &emeny,const Point & point)
{

    int l = 0, r = 0;//ºáÁ¬
    int heng = checkerboard_piece_num[player][quadrant];
    int sub = 0,l_sub=0,r_sub=0;
    for (int k = 1; k <= 6 ; k++) 
    {//ÅÐ¶ÏÊÇ·ñÓÐµÐ¾üµ²×Å
        if(point.x-k>0)
        {
            if(checkerboard_piece_num[player][quadrant-k*step]<0)
            {
                l_sub++;
            } 
        } else if(point.x-k == 0)
        {
            l_sub++;
        }

        if(point.x+k<19)
        {
            if(checkerboard_piece_num[player][quadrant+k*step]<0)
            {
                r_sub++;
            } 
        } else if(point.x+k == 19)
        {
            r_sub++;
        }
    }
    if(l_sub>0)
        sub++;
    if(r_sub>0)
        sub++;
    if(sub==0)
        return 0;
    else if(sub==1)
        return 1;
    else return 9;

}
/*****************************************************************************************************/           //AIºËÐÄ

void SixPiece::Grade(const std::vector<std::vector<int>> &checkerboard, const std::vector<std::vector<int>> &checkerboard_piece_num, std::vector<std::vector<int>> &table, const int ply,
           const chromosome &gene)         //ÆåÅÌÆÀ·ÖµÄ³ÌÐò£¬¸øÓèÆåÅÌÃ¿¸öµãÒ»¶¨µÄ·ÖÊý
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

                temp = CheckCheckerBoard(checkerboard_piece_num,1,quadrant1,player,enemy,{x,y});
                l = 0, r = 0;//ºáÁ¬
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
                for (int k = 1; k <= 6 - heng; k++) {//ÅÐ¶ÏÊÇ·ñÓÐµÐ¾üµ²×Å
                    if (l >= 0)
                        if ((checkerboard_piece_num[player][quadrant1 - l - k] < 0 || (x - l - k) == 0))//×ó±ß½ç
                        {
                            sub++;
                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant1 + k + r] < 0 || (x + r + k) == 19)//ÓÒ±ß½ç
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

                l = 0, r = 0;//ï¿½ï¿½ï¿½ï¿½
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
                                 (y - l - k) == 0))//ï¿½ï¿½ß½ï¿?
                            {
                                sub++;

                            }
                        if (r >= 0)
                            if (checkerboard_piece_num[player][quadrant2 + k * 19 + r * 19] < 0 ||
                                (y + r + k) == 19)//ï¿½Ò±ß½ï¿½
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

                l = 0, r = 0;//ï¿½ï¿½Ð±ï¿½ï¿½
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
                            ((y - l - k) == 0 && (x - l - k) == 0))//ï¿½ï¿½ß½ï¿?
                        {
                            sub++;

                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant3 + k * 20 + r * 20] < 0 ||
                            ((y + r + k) == 0 && (x + r + k) == 0))//ï¿½Ò±ß½ï¿½
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


                l = 0, r = 0;//ï¿½ï¿½Ð±ï¿½ï¿½
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
                            ((y - l - k) == 0 && (x + l + k) == 0))//ï¿½ï¿½ß½ï¿?
                        {
                            sub++;

                        }
                    if (r >= 0)
                        if (checkerboard_piece_num[player][quadrant4 + k * 18 + r * 18] < 0 ||
                            ((y + r + k) == 0 && (x - r - k) == 0))//ï¿½Ò±ß½ï¿½
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

void SixPiece::Search(int table[][20], int player, int &x, int &y, int checkerboard[][20])       //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½Ò³ï¿½ï¿½ï¿½ï¿½Ö±ï¿½ï¿½Ð·ï¿½Öµï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
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
         chromosome r1)          //AIï¿½ï¿½ï¿½ï¿½ ï¿½Èµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Öºï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ë«ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ö£ï¿½ ï¿½Ùµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò³ï¿½ï¿½ï¿½ï¿½ï¿½Î»ï¿½ï¿½
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

//	printf("\n player==%d  ï¿½ï¿½ï¿½ï¿½ï¿½tableÖµÎª %d %d\n",player,table_ply[x2_max][y2_max],table_cmp[x1_max][y1_max]) ;
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

void SixPiece::SelectionOfChampions(std::vector<int> population[20]) {
    std::vector<int> a[20];
    std::vector<int> b, c;
   
    for (int i = 1; i < 20; i++) {
       a[i] = population[i];
    }
    for (int i = 1; i <= 20; i++) {
        for (int j = i + 1; j <= 20; j++) {
            if (a[i].back() < a[j].back()) {
                swap(a[i],a[j]);
            }
        }
    }
    for (int j = 1; j <= 5; j++)
        champion[j] = a[j];
}

int SixPiece::PopulationPlayAGame(std::vector<int> population1, std::vector<int> population2, int checkerboard[][20],
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
            return 1;//population1Ó®
        }
        pos2 = AI(checkerboard1, checkerboard_piece_num2, 2, winner2, population2);
        Record(checkerboard1, checkerboard_piece_num2, 2, pos2.x, pos2.y);
        if (winner2) {
            return 2;//population2Ó®
        }
    }
    return 0;//Æ½ï¿½ï¿½
}

void SixPiece::CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) {
    int nu = 0;
    int max_value = FindMaxValue(champion);//ï¿½Òµï¿½ï¿½ï¿½Ó¦ï¿½ï¿½ï¿½ï¿½ï¿½Ö?
    for (int i = 1; i <= 5; i++)//ï¿½Ú¾ï¿½È¾É«ï¿½å¿ªÊ¼ï¿½ï¿½ï¿½ï¿½
    {
        Variation(champion[i], fitness_standard, max_value);
        GeneticRecombination(champion, fitness_standard, i, max_value);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
        //	printf("%d ",nu++);
    }

    for (int i = 1; i <= 20; i++)//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½È¾É«ï¿½ï¿½
    {
        population[i] = global_chromosome[i];
    }
}

void SixPiece::Championships(int checkerboard1[][20], int checkerboard_piece_num1[][1700], int player) {
    int black_winner = 0, white_winner = 0;
    for (int population_sequence = 1; population_sequence <= 4; population_sequence++)//20ï¿½ï¿½È¾É«ï¿½ï¿½Ö³ï¿½ï¿½ï¿½ï¿½é£¬Ã¿ï¿½ï¿½ï¿½Ä¸ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä¸ï¿½È¾É«ï¿½ï¿½ï¿½ï¿½Ð±È½Ï¡ï¿½
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
                    population[population_of_self].back() += 25;
                    population[population_of_enemy].back() += 25;
                } else if (black_winner == 1) {
                    population[population_of_self].back() += 50;
                    population[population_of_enemy].back() += 0;
                } else if (black_winner == 2) {
                    population[population_of_enemy].back() += 50;
                    population[population_of_self].back() += 0;
                }
                if (white_winner == 0) {
                    population[population_of_self].back() += 25;
                    population[population_of_enemy].back() += 25;
                } else if (white_winner == 1) {
                    population[population_of_self].back() += 50;
                    population[population_of_enemy].back() += 0;
                } else if (white_winner == 2) {
                    population[population_of_enemy].back() += 50;
                    population[population_of_self].back() += 0;
                }

            }
        }
    }

    int fitness_standard = 0, score_sum = 0;
    for (int i = 1; i <= 20; i++)
        score_sum += population[i].back();
    fitness_standard = score_sum / 20;
    SelectionOfChampions(population);//ï¿½Ã³ï¿½ï¿½Ú¾ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð£ï¿?
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
    ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num1);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ì¼ï¿½Â¼
    while (train_time--)//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ù´ï¿½
    {
        Championships(checkerboard1, checkerboard_piece_num1, player);
    }
}

void SixPiece::renji() {
    int winner = 0;
    char message[256];
    int player = 0;          //ï¿½ï¿½ï¿½ï¿½ 1ï¿½ï¿½Ê¾ï¿½ï¿½ 2ï¿½ï¿½Ê¾ï¿½ï¿½
    //int step_num = 0; //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Â¼
    int checkerboard[20][20] = {{0}};        //ï¿½ï¿½ï¿½Ì¼ï¿½Â¼
    int checkerboard_piece_num[3][1700] = {{0}};
    int enemy = 0;

    int train_time = 50;
    chromosome r;
    int x_position1, y_position1, x_position2, y_position2;
    char x_position_string_1, x_position_string_2, y_position_string_1, y_position_string_2;
    while (1) {
        fflush(stdout);
        //ï¿½ï¿½Â¼ï¿½ï¿½Ï·ï¿½Ðµï¿½Ê¤ï¿½ï¿½  0ï¿½ï¿½Ê¾ï¿½ï¿½Ê¤ï¿½ï¿½ 1ï¿½ï¿½Ê¾ï¿½ï¿½Ê¤ 2ï¿½ï¿½Ê¾ï¿½ï¿½Ê¤ 3ï¿½ï¿½Ê¾Æ½ï¿½ï¿½
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
            pos1 = AI(checkerboard, checkerboard_piece_num, player, winner, r);//ï¿½ï¿½ï¿½ï¿½
            Record(checkerboard, checkerboard_piece_num, player, pos1.x, pos1.y);
            x_position_string_1 = pos1.x + 'A' - 1;
            y_position_string_1 = pos1.y + 'A' - 1;
            pos2 = AI(checkerboard, checkerboard_piece_num, player, winner, r);//ï¿½ï¿½ï¿½ï¿½
            Record(checkerboard, checkerboard_piece_num, player, pos2.x, pos2.y);
            x_position_string_2 = pos2.x + 'A' - 1;
            y_position_string_2 = pos2.y + 'A' - 1; //printf(" %d",num++);
            //	printf("\nï¿½Ú¾ï¿½ï¿½ï¿½ï¿½ï¿½ È¾É«ï¿½ï¿½ÖµÎªï¿½ï¿½%d %d %d %d %d %d  \n",champion[2].huowu,champion[2].chongwu,champion[2].shuanghuosi,champion[2].huosan,champion[2].huoer,champion[2].adaptability);
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
        } else if (strcmp(message, "error") == 0)//ï¿½Å·ï¿½ï¿½ï¿½ï¿½ï¿½?
        {
            fflush(stdin);
        } else if (strcmp(message, "name?") == 0)//Ñ¯ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
        {
            fflush(stdin);
            printf("name Parsifal\n");

        } else if (strcmp(message, "end") == 0)//ï¿½Ô¾Ö½ï¿½ï¿½ï¿½
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
int main()   //ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½
{
    srand((unsigned) time(NULL));
    for (int i = 1; i <= 20; i++)//ï¿½ï¿½20ï¿½ï¿½È¾É«ï¿½å¶¨ï¿½ï¿½Öµ
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