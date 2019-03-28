//
// Created by wojtek on 28.03.19.
//

#include "HashGraphBuild.h"

void HashGraphBuild::generatePriorityQueue(std::vector<Element> *elements) {
    //inverted index
    std::unordered_map<std::string, std::vector<int>> ii;
    for(unsigned long i=0; i<elements->size(); i++){
        ii[elements->at(i).getHead(this->li)].push_back(i);
    }

    this->priorityQueue = std::queue<int>();

    for(unsigned long i=0; i<elements->size(); i++){
        if(ii[elements->at(i).getTail(this->li)].empty()){
            this->priorityQueue.push((int)i);
        }
    }
}

std::vector<std::vector<int>> HashGraphBuild::getListOfNeighbours(std::vector<Element> *elements) {

    this->generatePriorityQueue(elements);

    this->numOfEdges = 0;

    //inverted index
    std::unordered_map<std::string, std::vector<int>> ii;
    for(unsigned long i=0; i<elements->size(); i++){
        ii[elements->at(i).getTail(this->li)].push_back(i);
    }

    std::vector<std::vector<int>> ln = std::vector<std::vector<int>>(); //list of neighbours

//    for(unsigned long i=0; i<elements->size(); i++){
//        ln.push_back(ii[elements->at(i).getHead(this->li)]);
//    }

    for(auto& a: *elements){
        ln.push_back(ii[a.getHead(this->li)]);
        numOfEdges += ii[a.getHead(this->li)].size(); //count edges
    }

    return ln;
}
