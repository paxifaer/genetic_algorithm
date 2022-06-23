//
// Created by Parsifal on 2022/5/31.
//

#ifndef GENETIC_ALGORITHM_GENETICITERATE_H
#define GENETIC_ALGORITHM_GENETICITERATE_H

#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <mmsystem.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

std::vector<std::vector<int>> population;
std::vector<std::vector<int>> champion; //冠军序列
std::vector<int> global_chromosome[21];

class General
{
public:
    int VariateMasker(std::vector<int> champion, int fitness_standard, int fitness_max);
    void Variate(std::vector<int> &individual, int fitness_standard, int fitness_max);

    void Variation(std::vector<int> &individual, int fitness_standard, int fitness_max);

    int CrossingOverJudge(int fitness_standard, int fitness_max, int f);

    void CrossingOver(std::vector<int> &chromosome_x, std::vector<int> &chromosome_y, int &num, int fitness_standard, int fitness_max);

    void GeneticRecombination(std::vector<std::vector<int>> champion, int fitness_standard, int i, int fitness_max);

    int FindMaxValue(std::vector<std::vector<int>> population);

    void CrossingOverPrePare(std::vector<std::vector<int>> champion, int fitness_standard);

private:
};

#endif // GENETIC_ALGORITHM_GENETICITERATE_H
