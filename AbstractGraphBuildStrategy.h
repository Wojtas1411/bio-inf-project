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
protected:
    std::queue<int> priorityQueue = std::queue<int>();
    int numOfEdges = 0;
public:
    virtual std::vector<std::vector<int>> getListOfNeighbours(std::vector<Element> * elements)=0;

    std::queue<int> getPriorityQueue(){
        return priorityQueue;
    }

    int getNumOfEdges(){
        return numOfEdges;
    }
};

#endif //BIOINF_ABSTRACTGRAPHBUILDSTRATEGY_H
