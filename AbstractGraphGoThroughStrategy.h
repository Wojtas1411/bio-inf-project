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
public:
    virtual std::vector<Element> goThrough(std::vector<Element> *element, std::vector<std::vector<int>> *neighbourList)=0;
};

#endif //BIOINF_ABSTRACTGRAPHGOTHROUGHSTRATEGY_H
