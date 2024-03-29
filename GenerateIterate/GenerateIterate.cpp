#include "GenerateIterate.h"
#include <iostream>
//     0 huowu;
//    1 chongwu;
//    2 shuanghuosi;
//    3 danhuosi, 4 miansi, 5 huosan,6 miansan,7 huoer;
//   8 adaptability = 0;


int General::VariateMasker(std::shared_ptr<GeneVariate> data_muster, int &pos) {
    float mutation_probability;
    if (data_muster->champion[pos].back() < data_muster->fitness_standard) {
        mutation_probability = 0.1;
    } else if (data_muster->fitness_max != data_muster->fitness_standard) {
        mutation_probability = 0.1 - (0.1 - 0.01) *
                                     ((float) data_muster->fitness_max - (float) data_muster->champion[pos].back()) /
                                     (data_muster->fitness_max - data_muster->fitness_standard);
    }
    float variate_judge = (rand() % 1000) * mutation_probability;
    if (variate_judge >= 1)
        return 1;
    else
        return 0;

}// huowu 12  chongwu 9 shuanghuosi 9  danhuosi 8 miansi 7  huosan 6 miansan 4  huoer 3
void General::Variate(std::shared_ptr<GeneVariate> data_muster, int &pos)
{
    int probability, masker = 0;
    for(int y=0;y<data_muster->child_num;y++)
    {
        std::vector<int>vec{data_muster->champion[pos]};
        for (int j = 0; j < data_muster->champion[pos].size() - 1; j++)
        {

            masker = 0;
            for (int i = 0; i < vec.size()-1; i++)
            {
                probability = VariateMasker(data_muster, pos);
                masker += probability;
                masker << 1;
            }
            masker >> 1;
            vec[j] = data_muster->champion[pos][j] ^
                                            masker;
        }
        data_muster->population.emplace_back(vec);
    }

}

//void General::Variation(std::vector<int> &individual, int fitness_standard, int fitness_max)
//{
//    Variate(individual, fitness_standard, fitness_max);
//}

int General::CrossingOverJudge(std::shared_ptr<GeneVariate> data_muster, int &pos_x, int &pos_y)
{
    float f = std::max(data_muster->champion[pos_x].back(), data_muster->champion[pos_y].back());
    float probability = 0.7;
    if (f < data_muster->fitness_standard)
        probability = 0.9;
    else if (data_muster->fitness_max != data_muster->fitness_standard)
        probability = 0.9 - (float) (0.9 - 0.6) * (f - data_muster->fitness_standard) /
                            (data_muster->fitness_max - data_muster->fitness_standard);
    float judge;
    int x = rand() % 11;
    judge = probability * x;
    if (judge >= 1)
        return 1;
    else
        return 0;
}


void General::CrossingOver(std::shared_ptr<GeneVariate> data_muster, int &pos_x, int &pos_y)
{
    for (int j = 0; j < data_muster->champion[pos_x].size() - 1; j++)
    {
        int judge = CrossingOverJudge(data_muster,pos_x,pos_y);
        if (judge)
        {
            std::swap(data_muster->champion[pos_x][j] , data_muster->champion[pos_y][j]);
        }
    }
}


std::vector<int> General::RandomPairing(int &num) {
    std::vector<int> numbers;
    for (int i = 0; i < num; i++) {
        numbers.emplace_back(i);
    }
    std::random_shuffle(numbers.begin(), numbers.end());
    return numbers;
}

void General::RecombinationOfGrne(std::shared_ptr<GeneVariate> data_muster)
{
    std::vector<int> random = RandomPairing(data_muster->champaion_num);
    for (int i = 0; i < data_muster->champaion_num; i += 2) {
        int pos_y = i + 1;
        CrossingOver(data_muster, i, pos_y);
    }
}

void General::CalculateFitnessMaxAndFitnessStandard(std::shared_ptr<GeneVariate> data_muster) {
    int ma = 0;
    int sum=0;
    for (int i = 0; i < data_muster->child_num; i++) {
        if (ma <= data_muster->champion[i].back()) {
            ma = data_muster->champion[i].back();
        }
        sum+=data_muster->champion[i].back();
    }
    data_muster->fitness_max = ma;
    data_muster->fitness_standard = sum/data_muster->child_num;

}


void General::CrossingOverPrePare(std::shared_ptr<GeneVariate> data_muster) {
    CalculateFitnessMaxAndFitnessStandard(data_muster);
    RecombinationOfGrne(data_muster);
    for (int i = 1; i <= data_muster->champaion_num; i++)
    {
        Variate(data_muster, i);
        //	printf("%d ",nu++);
    }
}


