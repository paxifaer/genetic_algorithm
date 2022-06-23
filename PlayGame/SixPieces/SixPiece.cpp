#include "SixPiece.h"
void SixPiece::Init() //��ʼ������������¼���ӵ������ʼ��?
{
    checkerboard.clear();
    checkerboard_piece_num.clear();
    checkerboard.resize(20,std::vector<int>(20));
    checkerboard_piece_num.resize(3,std::vector<int>(1700));
}

/***********************************************************************************************/ //��¼

void SixPiece::Record(std::vector<std::vector<int>> &checkerboard, std::vector<std::vector<int>> &checkerboard_piece_num, const int player, int x_position,
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
        left_piece_num = checkerboard_piece_num[player][quadrant1 - 1] > 0 ? checkerboard_piece_num[player][quadrant1 - 1] : 0;
    if (quadrant1 + 1 <= 361)
        right_piece_num = checkerboard_piece_num[player][quadrant1 + 1] > 0 ? checkerboard_piece_num[player][quadrant1 + 1] : 0;
    ;

    checkerboard_piece_num[player][quadrant1] += left_piece_num + right_piece_num;

    if (left_piece_num > 0)
        for (int sd = 1; sd <= left_piece_num; sd++)
        {
            checkerboard_piece_num[player][quadrant1 - sd] = checkerboard_piece_num[player][quadrant1];
            // printf("\ncheckerboard_piece_num[player][quadrant-sd]=%d",checkerboard_piece_num[player][quadrant1-sd]);
        }
    if (right_piece_num > 0)
        for (int sd = 1; sd <= right_piece_num; sd++)
        {
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
    for (i = 1; i <= 1600; i++)
    {
        if (checkerboard_piece_num[player][i] >= 0)
        {
            if (checkerboard_piece_num[player][i] >= 6)
            {
                return player;
            }
        }
    }
}

int SixPiece::CheckCheckerBoard(const std::vector<std::vector<int>> &checkerboard_piece_num, const int &step, const int &quadrant, const int &player, const int &emeny, const Point &point)
{

    int l = 0, r = 0; //����
    int heng = checkerboard_piece_num[player][quadrant];
    int sub = 0, l_sub = 0, r_sub = 0;
    for (int k = 1; k <= 6; k++)
    { //�ж��Ƿ��ео�����
        if (point.x - k > 0)
        {
            if (checkerboard_piece_num[player][quadrant - k * step] < 0)
            {
                l_sub++;
            }
        }
        else if (point.x - k == 0)
        {
            l_sub++;
        }

        if (point.x + k < 19)
        {
            if (checkerboard_piece_num[player][quadrant + k * step] < 0)
            {
                r_sub++;
            }
        }
        else if (point.x + k == 19)
        {
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

void SixPiece::CalculatQuardrantScore(std::vector<std::vector<int>> &table, const chromosome &gene, const int &temp, const int &num, const Point &point)
{
    if (num <= 6)
        switch (num)
        {
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
            if (temp == 0)
            {
                table[point.x][point.y] += gene.shuanghuosi;
                break;
            }
            if (temp == 1)
            {
                table[point.x][point.y] += gene.danhuosi;
                break;
            }
            else if (temp == 9)
            {
                table[point.x][point.y] += -10;
                break;
            }
            break;
        case 5:
            if (temp == 0)
                table[point.x][point.y] += gene.huowu;
            else if (temp == 1)
                table[point.x][point.y] += gene.chongwu;
            else if (temp == 9)
            {
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

void SixPiece::Grade(const std::vector<std::vector<int>> &checkerboard, const std::vector<std::vector<int>> &checkerboard_piece_num, std::vector<std::vector<int>> &table, const int ply,
                     const chromosome &gene) //grade
{
    int x, y, k, quadrant1, quadrant2, quadrant3, quadrant4;
    int enemy = 1;
    int player = ply;
    int heng, zong, zuo, you;
    (enemy == ply) ? (enemy = 2) : (enemy = 1);

    for (x = 1; x <= 19; x++)
    {

        for (y = 1; y <= 19; y++)
        {

            heng = 1, zong = 1, zuo = 1, you = 1;

            if (checkerboard[x][y] == 0)
            {
                int l_heng = 0,l_zong = 0,l_zuo = 0,l_you = 0, r_heng = 0,r_zong = 0,r_zuo = 0,r_you = 0;
                quadrant1 = (y - 1) * 19 + x, quadrant2 = 19 * (y - 1) + x + 400, quadrant3 = 19 * (y - 1) + x + 800, quadrant4 = 19 * (y - 1) + x + 1200;

                int temp = CheckCheckerBoard(checkerboard_piece_num, 1, quadrant1, player, enemy, {x, y});
                int temp2 = CheckCheckerBoard(checkerboard_piece_num, 19, quadrant2, player, enemy, {x, y});
                int temp3 = CheckCheckerBoard(checkerboard_piece_num, 20, quadrant3, player, enemy, {x, y});
                int temp4 = CheckCheckerBoard(checkerboard_piece_num, 18, quadrant4, player, enemy, {x, y});
                if (x - 1 > 0)
                { 
                    l_heng = checkerboard_piece_num[ply][quadrant1 - 1];
                    l_zong = checkerboard_piece_num[ply][quadrant2 - 19];
                    l_zuo = checkerboard_piece_num[ply][quadrant3 - 20];
                    l_you = checkerboard_piece_num[ply][quadrant4 - 18];
                }
                if (x + 1 <= 19)
                    {
                        r_heng = checkerboard_piece_num[ply][quadrant1 + 1];
                        r_zong = checkerboard_piece_num[ply][quadrant2 + 19];
                        r_zuo = checkerboard_piece_num[ply][quadrant3 + 20];
                        r_you = checkerboard_piece_num[ply][quadrant4 + 18];
                    }
                CalculatQuardrantScore(table,gene,temp,l_heng+r_heng,{x,y});
                CalculatQuardrantScore(table,gene,temp2,l_zong+r_zong,{x,y});
                CalculatQuardrantScore(table,gene,temp3,l_zuo+r_zuo,{x,y}); 
                CalculatQuardrantScore(table,gene,temp4,l_you+r_you,{x,y});          
            }
        }
    }
}

void SixPiece::Search(const std::vector<std::vector<int>>& table, const int &player, int &x, int &y, const std::vector<std::vector<int>> &checkerboard)   //搜索函数 找出评分表中分值最大的位置
{
    int i, j;
    int max,max_x,max_y;
    int num = 0, time = 0;

    max = 0;
    for (i = 1; i <= 19; i++)
    {
        for (j = 1; j <= 19; j++)
        {
            if (!checkerboard[i][j] && table[i][j] && table[i][j] > max)
            {
                max = table[i][j];
                max_x = i;
                max_y = j;
            }
        }
    }
    x = max_x;
    y = max_y;
    if (!checkerboard[7][7] && !max)
    {
        x = 7;
        y = 7;
        return;
    }

    //	printf("\nmax=%d %c%c \n",max,i+'A'-1,j+'A'-1);
}

Point SixPiece::AI(const std::vector<std::vector<int>> &checkerboard, const std::vector<std::vector<int>> &checkerboard_piece_num, int player, int &winner,
                   chromosome r1)  //AI函数 先调用评分函数，对双方棋盘评分， 再调用搜索函数，找出最优位置
{
    int x1_max, y1_max;
    int x2_max, y2_max;
    std::vector<std::vector<int>> table_cmp(20,std::vector<int>(20));
    std::vector<std::vector<int>> table_ply(20,std::vector<int>(20));
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

    if (table_cmp[x1_max][y1_max] >= table_ply[x2_max][y2_max])
    {
        {
            return {x1_max, y1_max};
        }
        // Record(checkerboard,checkerboard_piece_num,player,x1_max,y1_max);//
    }
    else
    {
        return {x2_max, y2_max};
        //	  Record(checkerboard,checkerboard_piece_num,player,x2_max,y2_max);
    }
}

void SixPiece::SelectionOfChampions(const std::vector<std::vector<int>>  &population)
{
    std::vector<int> a[20];
    std::vector<int> b, c;

    for (int i = 1; i < 20; i++)
    {
        a[i] = population[i];
    }
    for (int i = 1; i <= 20; i++)
    {
        for (int j = i + 1; j <= 20; j++)
        {
            if (a[i].back() < a[j].back())
            {
                swap(a[i], a[j]);
            }
        }
    }
    for (int j = 1; j <= 5; j++)
        champion[j] = a[j];
}

 chromosome SixPiece::ChromosomeSwitch(const std::vector<int> &population)
 {
    chromosome popu;
    popu.chongwu = population[Gene::chongwu];
    popu.danhuosi = population[Gene::danhuosi];
    popu.huoer = population[Gene::huoer];
    popu.huosan = population[Gene::huosan];
    popu.huowu = population[Gene::huowu];
    popu.miansan = population[Gene::miansan];
    popu.miansi = population[Gene::miansi];
    popu.shuanghuosi = population[Gene::shuanghuosi];
    popu.adaptability =  population[Gene::adaptability];
    return popu;
 }

int SixPiece::PopulationPlayAGame(std::vector<int> population1, std::vector<int> population2, const std::vector<std::vector<int>> &checkerboard, 
                                    const std::vector<std::vector<int>> &checkerboard_piece_num)
{
    int convergence_limit = 50;
    int flag = 0;
    // int checkerboard1[20][20], checkerboard_piece_num1[3][1700], checkerboard_piece_num2[3][1700];
    // ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num1);
    // ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num2);
    std::vector<std::vector<int>> checkerboard1, checkerboard_piece_num1, checkerboard_piece_num2;

    checkerboard1 = checkerboard;
    checkerboard_piece_num1 = checkerboard_piece_num;
    checkerboard_piece_num2 = checkerboard_piece_num;

    int winner1 = 0, winner2 = 0;

    while (convergence_limit--)
    {
        int winner1 = 0, winner2 = 0;
        Point pos1, pos2;
        chromosome chro1,chro2;
        chro1 = ChromosomeSwitch(population1);
        chro2 = ChromosomeSwitch(population2);
        pos1 = AI(checkerboard1, checkerboard_piece_num1, 1, winner1, chro1);
        //	printf("\n%d ",winner1);
        Record(checkerboard1, checkerboard_piece_num1, 1, pos1.x, pos1.y);
        if (winner1)
        {
            return 1; // population1赢
        }
        pos2 = AI(checkerboard1, checkerboard_piece_num2, 2, winner2, chro2);
        Record(checkerboard1, checkerboard_piece_num2, 2, pos2.x, pos2.y);
        if (winner2)
        {
            return 2; // population2赢
        }
    }
    return 0;//平局
}

void SixPiece::CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard)
{
    int nu = 0;
    int max_value = FindMaxValue(champion); //�ҵ���Ӧ������?
    for (int i = 1; i <= 5; i++)            //�ھ�Ⱦɫ�忪ʼ����
    {
        Variation(champion[i], fitness_standard, max_value);
        GeneticRecombination(champion, fitness_standard, i, max_value); //��������
        //	printf("%d ",nu++);
    }

    for (int i = 1; i <= 20; i++) //������һ��Ⱦɫ��
    {
        population[i] = global_chromosome[i];
    }
}

void SixPiece::Championships(std::vector<std::vector<int>>  &checkerboard1, std::vector<std::vector<int>> & checkerboard_piece_num1, int player)
{
    int black_winner = 0, white_winner = 0;
    for (int population_sequence = 1; population_sequence <= 4; population_sequence++) // 20��Ⱦɫ��ֳ����飬ÿ���ĸ������ĸ�Ⱦɫ����бȽϡ�
    {
        for (int population_of_self = population_sequence; population_of_self <= 20; population_of_self += 4)
        {
            for (int population_of_enemy = population_of_self + 1;
                 population_of_enemy <= population_of_self + 3; population_of_enemy++)
            {

                black_winner = PopulationPlayAGame(population[population_of_self], population[population_of_enemy],
                                                   checkerboard1,
                                                   checkerboard_piece_num1);
                white_winner = PopulationPlayAGame(population[population_of_enemy], population[population_of_self],
                                                   checkerboard1,
                                                   checkerboard_piece_num1);
                if (black_winner == 0)
                {
                    population[population_of_self].back() += 25;
                    population[population_of_enemy].back() += 25;
                }
                else if (black_winner == 1)
                {
                    population[population_of_self].back() += 50;
                    population[population_of_enemy].back() += 0;
                }
                else if (black_winner == 2)
                {
                    population[population_of_enemy].back() += 50;
                    population[population_of_self].back() += 0;
                }
                if (white_winner == 0)
                {
                    population[population_of_self].back() += 25;
                    population[population_of_enemy].back() += 25;
                }
                else if (white_winner == 1)
                {
                    population[population_of_self].back() += 50;
                    population[population_of_enemy].back() += 0;
                }
                else if (white_winner == 2)
                {
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
    SelectionOfChampions(population);                //�ó��ھ���������У�?
    CrossingOverPrePare(champion, fitness_standard); //
}

// void SixPiece::ResultCopy(int checkerboard[][20], int checkerboard1[][20], int checkerboard_piece_num[][1700],
//                           int checkerboard_piece_num1[][1700])
// {
//     memcpy(checkerboard1, checkerboard, sizeof(int) * 20 * 20);
//     memcpy(checkerboard_piece_num1, checkerboard_piece_num, sizeof(int) * 3 * 1700);
// }

void SixPiece::Train(std::vector<std::vector<int>> & checkerboard, std::vector<std::vector<int>> & checkerboard_piece_num,  int & train_time, const int & winner, const int & player)
{
    std::vector<std::vector<int>> checkerboard_piece_num1;
    std::vector<std::vector<int>> checkerboard1;
    checkerboard1 = checkerboard;
    checkerboard_piece_num1 = checkerboard_piece_num;
    // ResultCopy(checkerboard, checkerboard1, checkerboard_piece_num, checkerboard_piece_num1); //�������̼�¼
    while (train_time--)                                                                      //�������ٴ�
    {
        Championships(checkerboard1, checkerboard_piece_num1, player);
    }
}

void SixPiece::SignalCommunication()
{
    int winner = 0;
    char message[256];
    int player = 0; //���� 1��ʾ�� 2��ʾ��
    // int step_num = 0; //������¼
    std::vector<std::vector<int>> checkerboard(20,std::vector<int>(20)); //���̼�¼
    std::vector<std::vector<int>> checkerboard_piece_num(3,std::vector<int>(1700));
    int enemy = 0;

    int train_time = 50;
    chromosome r;
    int x_position1, y_position1, x_position2, y_position2;
    char x_position_string_1, x_position_string_2, y_position_string_1, y_position_string_2;
    while (1)
    {
        fflush(stdout);
        scanf("%s", message);
        if (strcmp(message, "move") == 0)
        {
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
        }
        else if (strcmp(message, "new") == 0)
        {
            scanf("%s", message);
            fflush(stdin);
            if (strcmp(message, "black") == 0)
            {
                enemy = 2;
                player = 1;
            }
            else
            {
                player = 2;
                enemy = 1;
            }
            Init();
            if (player == 1)
            {
                char s1 = 'A' + 7, s2 = 'A' + 7;
                Record(checkerboard, checkerboard_piece_num, player, 7, 7);
                printf("\n");
                printf("move GG@@\n");
            }
        }
        else if (strcmp(message, "error") == 0) //�ŷ�����?
        {
            fflush(stdin);
        }
        else if (strcmp(message, "name?") == 0) //ѯ����������
        {
            fflush(stdin);
            printf("name Parsifal\n");
        }
        else if (strcmp(message, "end") == 0) //�Ծֽ���
        {
            fflush(stdin);
        }
        else if (strcmp(message, "quit") == 0)
        {
            fflush(stdin);
            printf("Quit!\n");
            break;
        }

        // printf("\n%d ",winner);
    }
}

/**************************************************************************************************************/
int main() //������
{
    srand((unsigned)time(NULL));
    for (int i = 1; i <= 20; i++) //��20��Ⱦɫ�嶨��ֵ
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