//
// Created by wojtek on 23.03.19.
//

#include "solver.h"

//setting output csv header and delimiter
std::string solver::delimiter = ";";
std::string solver::header_line = "id" + solver::delimiter + "\n";

std::string solver::getResult() {
    //TODO
    return "";
}

void solver::solve() {
    //TODO use strategies to solve the graph
}

solver::solver(int id, const char *filename, AbstractGraphBuildStrategy *graphBuildStrategy, AbstractGraphGoThroughStrategy *goThroughStrategy) {
    this->id = id;
    this->filename = filename;
    this->buildStrategy = graphBuildStrategy;
    this->goThroughStrategy = goThroughStrategy;

    this->instance = new std::vector<std::string>();

    //TODO read instance and prepare everything
}

solver::~solver() {
    //TODO destroy shit
    instance->clear();
    instance->shrink_to_fit();
    delete instance;

    delete buildStrategy;
    delete goThroughStrategy;
}


