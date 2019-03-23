//
// Created by wojtek on 23.03.19.
//

#ifndef BIOINF_ABSTRACTGRAPHBUILDSTRATEGY_H
#define BIOINF_ABSTRACTGRAPHBUILDSTRATEGY_H

#include "Define.h"

/*
 * to implement new build strategy inherit from this class
 */

class AbstractGraphBuildStrategy{
public:
    virtual std::vector<std::vector<int>> getListOfNeighbours(std::vector<Element> * elements)=0;
};

#endif //BIOINF_ABSTRACTGRAPHBUILDSTRATEGY_H
