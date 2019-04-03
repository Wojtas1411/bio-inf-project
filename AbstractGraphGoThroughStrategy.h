//
// Created by wojtek on 23.03.19.
//

#ifndef BIOINF_ABSTRACTGRAPHGOTHROUGHSTRATEGY_H
#define BIOINF_ABSTRACTGRAPHGOTHROUGHSTRATEGY_H

#include "Define.h"

/*
 * to implement new go-through graph strategy inherit from this class
 */

class AbstractGraphGoThroughStrategy{
protected:
    unsigned long li = 0;
    bool first_iteration = true;
public:
    virtual std::vector<Element> goThrough(std::vector<Element> &element, std::vector<std::vector<int>> &neighbourList, std::queue<int> *priorityQueue)=0;

    void setLi(unsigned long nli){
        if(nli != this->li){
            first_iteration = true;
        } else {
            first_iteration = false;
        }
        this->li = nli;
    }
};

#endif //BIOINF_ABSTRACTGRAPHGOTHROUGHSTRATEGY_H
