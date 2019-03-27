//
// Created by wojtek on 27.03.19.
//

#ifndef BIOINF_STANDARDGRAPHBUILD_H
#define BIOINF_STANDARDGRAPHBUILD_H


#include "AbstractGraphBuildStrategy.h"
#include "Define.h"

class StandardGraphBuild : public AbstractGraphBuildStrategy {
public:
    std::vector<std::vector<int>> getListOfNeighbours(std::vector<Element> * elements);
};


#endif //BIOINF_STANDARDGRAPHBUILD_H
