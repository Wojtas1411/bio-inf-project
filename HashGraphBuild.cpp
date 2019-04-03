//
// Created by wojtek on 28.03.19.
//

#include "HashGraphBuild.h"

void HashGraphBuild::generatePriorityQueue(std::vector<Element> &elements) {
    //inverted index
    std::unordered_map<std::string, std::vector<int>> ii;
    for(unsigned long i=0; i<elements.size(); i++){
        ii[elements.at(i).getTail(this->li)].push_back(i);
    }

    this->priorityQueue = std::queue<int>();

    for(unsigned long i=0; i<elements.size(); i++){
        if(ii[elements.at(i).getHead(this->li)].empty()){
            this->priorityQueue.push((int)i);
        }
    }
}

std::vector<std::vector<int>> * HashGraphBuild::getListOfNeighbours(std::vector<Element> &elements) {

    //std::cout<<"Start hash build"<<std::endl;
    this->generatePriorityQueue(elements);
    //std::cout<<"Queue finished"<<std::endl;

    this->numOfEdges = 0;

    //inverted index
    std::unordered_map<std::string, std::vector<int>> ii;
    for(unsigned long i=0; i<elements.size(); i++){
        ii[elements.at(i).getHead(this->li)].push_back(i);
    }

    //std::cout<<"Inverted index finished"<<std::endl;

    auto* ln = new std::vector<std::vector<int>>(); //list of neighbours

    for(unsigned long i=0; i<elements.size(); i++){
        auto temp = ii[elements[i].getTail(this->li)];
        for(unsigned long j=0; j<temp.size(); j++){ //avoid situations where vertex points to itself
            if(temp[j] == i){
                temp.erase(temp.begin()+j);
                break;
            }
        }
        ln->push_back(temp);
        numOfEdges += temp.size(); //count edges
    }

//    for(auto& a: elements){
//        ln->push_back(ii[a.getTail(this->li)]);
//        numOfEdges += ii[a.getTail(this->li)].size(); //count edges
//    }

    std::cout<<"Graph finished"<<std::endl;

    return ln;
}
