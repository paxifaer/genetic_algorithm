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
   virtual ~General(){};
    struct GeneVariate
            {
        std::vector<std::vector<int>> population;
        int child_num;
        std::vector<std::vector<int>> champion;
        int  fitness_standard;
        int  fitness_max;
        int champaion_num;
        GeneVariate(std::vector<std::vector<int>> vector, int i, std::vector<std::vector<int>> vector1, int i1, int i2,
                    int i3) :population(vector), child_num(i),champion(vector1), fitness_standard(i1), fitness_max(i2), champaion_num(i3){};
    };

    void CalculateFitnessMaxAndFitnessStandard(std::shared_ptr<GeneVariate> data_muster);

    void CrossingOverPrePare(std::shared_ptr<GeneVariate> data_muster);

private:

    std::vector<int> RandomPairing(int &num);
    int VariateMasker(std::shared_ptr<GeneVariate> data_muster,int &pos);
    void Variate(std::shared_ptr<GeneVariate> data_muster,int &pos);

//    void Variation(std::vector<int> &individual, int fitness_standard, int fitness_max);

    int CrossingOverJudge(std::shared_ptr<GeneVariate> data_muster,int &pos_x,int &pos_y);

    void CrossingOver(std::shared_ptr<GeneVariate> data_muster,int &pos_x,int &pos_y);

    void RecombinationOfGrne(std::shared_ptr<GeneVariate> data_muster);
};

#endif // GENETIC_ALGORITHM_GENETICITERATE_H
