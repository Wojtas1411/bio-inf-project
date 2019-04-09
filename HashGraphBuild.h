//
// Created by wojtek on 28.03.19.
//

#ifndef BIOINF_HASHGRAPHBUILD_H
#define BIOINF_HASHGRAPHBUILD_H

#include "Define.h"
#include "AbstractGraphBuildStrategy.h"

class HashGraphBuild : public AbstractGraphBuildStrategy{
protected:
    void generatePriorityQueue(std::vector<Element> & elements);
public:
    std::vector<std::vector<int>> * getListOfNeighbours(std::vector<Element> & elements) override ;

};


#endif //BIOINF_HASHGRAPHBUILD_H
