//
// Created by wojtek on 27.03.19.
//

#include "StandardGraphGoThrough.h"

Element StandardGraphGoThrough::onePathTrip(int start_index, bool* visited, std::vector<std::vector<int>> &neighbourList, std::vector<Element> &elements){
    int current_index = start_index;

    visited[current_index] = true; //visit this vertex

    Element result = elements[current_index];

    while(!neighbourList[current_index].empty()){
        if(neighbourList[current_index].size() == 1){
            if(!visited[neighbourList[current_index][0]]){
                current_index = neighbourList[current_index][0];
                if(!result.appendElement(elements[current_index], this->li)) std::cout<<"help!"<<std::endl;
                visited[current_index] = true; //make it visited
            } else {
                //std::cout<<"Single child break"<<std::endl;
                break; //if this single child, is already visited
            }
        } else if(neighbourList[current_index].size() > 1){
            if(this->first_iteration){
                //std::cout<<"First iteration break"<<std::endl;
                break;
            }
            long max_index = -1;
            long max_value = -1;
            for(unsigned long i=0; i<neighbourList[current_index].size(); i++){
                if(!visited[neighbourList[current_index][i]]){
                    if(elements[visited[neighbourList[current_index][i]]].getSize() > max_value){
                        max_index = i;
                        max_value = elements[visited[neighbourList[current_index][i]]].getSize(); //get value of this element
                    }
                }
            }
            if(max_index != -1){
                current_index = neighbourList[current_index][max_index];
                if(!result.appendElement(elements[current_index], this->li)) std::cout<<"help!"<<std::endl;
                visited[current_index] = true; //make it visited
            } else {
                //std::cout<<"all visited break"<<std::endl;
                break; //none of descendants of this vertice has
            }
        } else {
            //std::cout<<"random break"<<std::endl;
            break;
        }
    }

    //std::cout<<result.getSize()<<std::endl;

    return result;
    
}

std::vector<Element> StandardGraphGoThrough::goThrough(std::vector<Element> &element,
                                                       std::vector<std::vector<int>> &neighbourList,
                                                       std::queue<int> *priorityQueue) {
    //TODO go through
    unsigned long size = element.size();

    std::vector<Element> result = std::vector<Element>();

    //create visited table
    auto *visited = new bool[size];
    for(unsigned long i=0; i<size; i++){
        visited[i] = false;
    }

    //std::cout<<"Prioirity queue size:\t" << priorityQueue->size() <<std::endl;
    //std::cout<<"Go priority"<<std::endl;
    //go through priority queue
    while(!priorityQueue->empty()){
        int current_index = priorityQueue->front();
        priorityQueue->pop();

        Element e = onePathTrip(current_index, visited, neighbourList, element);

        result.push_back(e);
    }

    //std::cout<<"Go rest polite"<<std::endl;
    //polite go rest
    for(unsigned long i=0; i<size; i++){
        if(!visited[i]){
            for(const auto & j: neighbourList[i]){
                if(!visited[j]){
                    Element e = onePathTrip(i, visited, neighbourList, element);
                    result.push_back(e);
                    break;
                }
            }
        }
    }

    //std::cout<<"Go rest"<<std::endl;
    //go through remaining vertices
    unsigned long last_used = 0;
    while(last_used < size-1){
        for(unsigned long i=last_used; i<size; i++){
            if(!visited[i]){
                Element e = onePathTrip(i, visited, neighbourList, element);
                result.push_back(e);
                last_used = i;
                break;
            }
            last_used = i;
        }
    }
    //std::cout<<"result size\t"<<result.size()<<std::endl;

    return result;
}
