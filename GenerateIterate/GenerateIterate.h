//
// Created by Parsifal on 2022/5/31.
//

#ifndef GENETIC_ALGORITHM_GENETICITERATE_H
#define GENETIC_ALGORITHM_GENETICITERATE_H

#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>


class General
{

public:

    struct GeneVariate
            {
        std::vector<std::vector<int>> population;
        int child_num;
        std::vector<int> global_chromosome[21];
        std::vector<std::vector<int>> champion;
        int  fitness_standard;
        int  fitness_max;

        int sum;
        GeneVariate(): child_num(0),fitness_standard(0),fitness_max(0),sum(0){};
    };


    int VariateMasker(std::shared_ptr<GeneVariate> data_muster);
    void Variate(std::shared_ptr<GeneVariate> data_muster,int &pos);

//    void Variation(std::vector<int> &individual, int fitness_standard, int fitness_max);

    int CrossingOverJudge(std::shared_ptr<GeneVariate> data_muster,int &pos_x,int &pos_y);

    void CrossingOver(std::shared_ptr<GeneVariate> data_muster,int &pos_x,int &pos_y);

    void RecombinationOfGrne(std::shared_ptr<GeneVariate> data_muster);

    int FindMaxValue(std::shared_ptr<GeneVariate> data_muster);

    void CrossingOverPrePare(std::shared_ptr<GeneVariate> data_muster);

private:

    std::vector<int> RandomPairing(int &num);
};

#endif // GENETIC_ALGORITHM_GENETICITERATE_H
