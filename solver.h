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
    std::vector<Element> instance;
    int id;                 //identifier
    int error_type;         //positive/negative
    std::string filename;   //name of file
    double time;            //time of execution
    unsigned long number_of_elements_real;  //total number of elements in instance (at read)
    unsigned long number_of_elements;       //size of instance (from filename)
    long error_size;         //size of error (from filename)
    long required_size;      //required size of chain
    AbstractGraphBuildStrategy *buildStrategy;
    AbstractGraphGoThroughStrategy *goThroughStrategy;

    long chain_size;        //total length of chain
    long used_elements;     //number of used input elements

public:
    solver(int id, const char * filename, AbstractGraphBuildStrategy *graphBuildStrategy, AbstractGraphGoThroughStrategy *goThroughStrategy);
    ~solver();

    void solve();

    std::string getResult();

    //setting output csv header and delimiter
    static const std::string delimiter;
    static const std::string header_line;

    static const int NEGATIVE_ERROR = 0;
    static const int POSITIVE_ERROR = 1;
    static const int UNDEFINED_ERROR = -1;

    static const int L = 10;

    static const unsigned long treshold = 20;

    static unsigned long indexOfMaxElement(std::vector<Element> & input);

};


#endif //BIOINF_SOLVER_H
