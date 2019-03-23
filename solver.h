//
// Created by wojtek on 23.03.19.
//

#ifndef BIOINF_SOLVER_H
#define BIOINF_SOLVER_H

#include "Define.h"
#include "AbstractGraphBuildStrategy.h"
#include "AbstractGraphGoThroughStrategy.h"


class solver {
private:
    std::vector<std::string> *instance;
    int id;                 //identifier
    int error_type;         //positive/negative
    std::string filename;   //name of file
    double time;            //time of execution
    int number_of_elements_real; //total number of elements in instance (at read)
    int number_of_elements; //size of instance (from filename)
    int error_size;         //size of error (from filename)
    int required_size;      //required size of chain
    AbstractGraphBuildStrategy *buildStrategy;
    AbstractGraphGoThroughStrategy *goThroughStrategy;

public:
    solver(int id, const char * filename, AbstractGraphBuildStrategy *graphBuildStrategy, AbstractGraphGoThroughStrategy *goThroughStrategy);
    ~solver();

    void solve();

    std::string getResult();

    static std::string header_line;
    static std::string delimiter;

    static const int NEGATIVE_ERROR = 0;
    static const int POSITIVE_ERROR = 1;

    static const int L = 10;
};


#endif //BIOINF_SOLVER_H
