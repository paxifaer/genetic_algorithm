#include "GeneticIterate.h"
//     0 huowu;
//    1 chongwu;
//    2 shuanghuosi;
//    3 danhuosi, 4 miansi, 5 huosan,6 miansan,7 huoer;
//   8 adaptability = 0;


int General::VariateMasker(std::vector<int> champion, int fitness_standard, int fitness_max)//基因变异概率
{
    float mutation_probability;
    if (champion.back() < fitness_standard) {
        mutation_probability = 0.1;
    } else if (fitness_max != fitness_standard) {
        mutation_probability = 0.1 - (0.1 - 0.01) * ((float) fitness_max - (float) champion.back()) / (fitness_max - fitness_standard);
    }
    float variate_judge = (rand() % 100) * mutation_probability;
    if (variate_judge >= 1)
        return 1;
    else return 0;

}// huowu 12  chongwu 9 shuanghuosi 9  danhuosi 8 miansi 7  huosan 6 miansan 4  huoer 3
void General::Variate(std::vector<int> &individual, int fitness_standard, int fitness_max) {
    int probability, masker = 0;
   for(int j=0;j<individual.size()-1;j++)
   {
       masker = 0;
       for (int i = 0; i < 12; i++) {
           probability = VariateMasker(individual, fitness_standard, fitness_max);
           masker += probability;
           masker << 1;
       }
       masker >> 1;
       individual[j]= individual[j] ^ masker;//实现基因突变，借用了子网掩码的方式,  掩码（）：1011111  ，掩码计算方式，对应位掩码值为0，则该位的值取反(0代表变异，1代表不变异)      （111）10 = (1110001)2      (1110001)2     varite->  (1010001)2 = (79)10
   }

}

void General::Variation(std::vector<int> &individual, int fitness_standard, int fitness_max)//基因变异
{
    Variate(individual, fitness_standard, fitness_max);
}

int General::CrossingOverJudge(int fitness_standard, int fitness_max, int f)//每条染色体的基因是否发生交叉互换
{
    float probability = 0.7;
    if (f < fitness_standard)
        probability = 0.9;
    else if (fitness_max != fitness_standard)
        probability = 0.9 - (float) (0.9 - 0.6) * (f - fitness_standard) / (fitness_max - fitness_standard);
    float judge;
    int x = rand() % 11;
    judge = probability * x;
    if (judge >= 1)
        return 1;
    else return 0;
}



void General::CrossingOver(std::vector<int> & chromosome_x, std::vector<int> & chromosome_y, int &num, int fitness_standard, int fitness_max) {//染色体交叉互换
    int n = num;
    int nu = 0;

    for(int j=0;j<chromosome_x.size()-1;j++)
    {
        int judge = CrossingOverJudge(fitness_standard, fitness_max, chromosome_x.back());
        if (judge == 1) {
            global_chromosome[n][j] = chromosome_y[j];
            global_chromosome[++n][j] = chromosome_x[j];
        } else {
            global_chromosome[n][j] = chromosome_x[j];
            global_chromosome[++n][j] = chromosome_y[j];
        }
        n -= 1;
    }
    num = n;
}

void General::GeneticRecombination(std::vector<std::vector<int>> champion, int fitness_standard, int i, int fitness_max)//开始基因重组
{
    int num = 1;
    int nu = 0;
    for (int i = 1; i <= 5; i++) {
        for (int j = i + 1; j <= 5; j++) {
            CrossingOver(champion[i], champion[j], num, fitness_standard, fitness_max);//每两个不同的染色体开始交叉
        }
    }
}

int General::FindMaxValue(std::vector<std::vector<int>> population) {
    int ma = 0;
    for (int i = 1; i <= 5; i++) {
        if (ma <= population[i].back()) {
            ma = population[i].back();
        }
    }
    return ma;
}


void General::CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard) {
    int nu = 0;
    int max_value = FindMaxValue(champion);//找到适应度最大值
    for (int i = 1; i <= 5; i++)//冠军染色体开始变异
    {
        Variation(champion[i], fitness_standard, max_value);
        GeneticRecombination(champion, fitness_standard, i, max_value);//基因重组
        //	printf("%d ",nu++);
    }

    for (int i = 1; i <= 20; i++)//生成新一代染色体
    {
        population[i] = global_chromosome[i];
    }
}

