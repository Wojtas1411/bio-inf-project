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
            //---if any child has more than one descendant---///
//            if(go_with_stopping){
//                bool should_i_break = false;
//                for(unsigned long i=0; i<neighbourList[current_index].size(); i++){
//                    if(neighbourList[i].size()>1) {
//                        should_i_break = true;
//                        break;
//                    }
//                }
//                if(should_i_break) {
//                    //std::cout<<"Tactic break"<<std::endl;
//                    break;
//                }
//            }

            //---choose longest, not visited descendant of the vertex---//
            long max_index = -1;
            long max_value = -1;
            for(unsigned long i=0; i<neighbourList[current_index].size(); i++){
                if(!visited[neighbourList[current_index][i]]){
                    if(elements[neighbourList[current_index][i]].getSize() > max_value){
                        max_index = i;
                        max_value = elements[neighbourList[current_index][i]].getSize(); //get value of this element
                    }
                }
            }
            if(max_index != -1){
                current_index = neighbourList[current_index][max_index];
                if(!result.appendElement(elements[current_index], this->li)) std::cout<<"help!"<<std::endl;
                visited[current_index] = true; //make it visited
            } else {
                //std::cout<<"all visited break"<<std::endl;
                break; //none of descendants of vertex is available
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
                                                       std::queue<int> *priorityQueue,
                                                       std::queue<int> *secondPriorityQueue) {
    unsigned long size = element.size();

    if(old_graph_size == neighbourList.size()) {
        //std::cout<<"No changes\t"<<this->li<<std::endl;
        go_with_stopping = false;
    } else {
        go_with_stopping = true;
    }
    if(this->first_iteration) go_with_stopping = true;

    old_graph_size = neighbourList.size();

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

    if(this->first_iteration){
        while(!secondPriorityQueue->empty()){
            int current_index = secondPriorityQueue->front();
            secondPriorityQueue->pop();
            if(!visited[current_index]){
                for(const auto & j: neighbourList[current_index]){
                    if(!visited[j]){
                        Element e = onePathTrip(current_index, visited, neighbourList, element);
                        result.push_back(e);
                        break;
                    }
                }
            }
        }
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

    delete[] visited;
    return result;
}
