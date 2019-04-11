//
// Created by wojtek on 27.03.19.
//

#ifndef BIOINF_STANDARDGRAPHGOTHROUGH_H
#define BIOINF_STANDARDGRAPHGOTHROUGH_H

#include "Define.h"
#include "AbstractGraphGoThroughStrategy.h"


class StandardGraphGoThrough : public AbstractGraphGoThroughStrategy{
protected:
    Element onePathTrip(int start_index, bool* visited, std::vector<std::vector<int>> &neighbourList, std::vector<Element> &elements);

    int old_graph_size = -1;
    bool go_with_stopping = true;
public:
    std::vector<Element> goThrough(std::vector<Element> &element,
            std::vector<std::vector<int>> &neighbourList,
            std::queue<int> *priorityQueue,
            std::queue<int> *secondPriorityQueue);
};


#endif //BIOINF_STANDARDGRAPHGOTHROUGH_H
