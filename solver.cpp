//
// Created by wojtek on 23.03.19.
//

#include "solver.h"

//setting output csv header and delimiter
std::string solver::delimiter = ";";
std::string solver::header_line = "id" + solver::delimiter + "\n";

std::string solver::getResult() {
    //TODO build csv string with output data
    return this->filename;
}

void solver::solve() {
    int li = solver::L -1;

    //start timer
    auto start = std::chrono::system_clock::now();

    //TODO use strategies to solve the graph

    //end timer
    auto end = std::chrono::system_clock::now();
    //save time
    this->time = (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000;

    //TODO fill chain size
    this->chain_size = 0;
    //TODO fill used elements
    this->used_elements = 0;
}

solver::solver(int id, const char *filename, AbstractGraphBuildStrategy *graphBuildStrategy, AbstractGraphGoThroughStrategy *goThroughStrategy) {
    this->id = id;
    this->filename = filename;
    this->buildStrategy = graphBuildStrategy;
    this->goThroughStrategy = goThroughStrategy;

    this->instance = new std::vector<Element>();

    std::ifstream in;
    in.open(filename);

    while(!in.eof()){
        std::string temp;
        in >> temp;

        this->instance->emplace_back(Element(temp));
    }

    in.close();

    this->filename = this->filename.substr(13);

    number_of_elements_real = this->instance->size();

    //
    //---parsing filename
    //

    // checking the instance filename to know if instance has positive or negative mistakes
    this->error_type = solver::UNDEFINED_ERROR;

    unsigned long dotPos = this->filename.find('.');
    if(dotPos == std::string::npos) std::cout << "Fatal error" << std::endl;
    unsigned long signPos = 0;

    if(this->filename.find('+') != std::string::npos){
        this->error_type = solver::POSITIVE_ERROR;          //get error type
        signPos = this->filename.find('+');
    }
    else if(this->filename.find('-') != std::string::npos){
        this->error_type = solver::NEGATIVE_ERROR;          //get error type
        signPos = this->filename.find('-');
    }

    this->error_size = std::strtol(this->filename.substr(signPos+1).c_str(), nullptr, 10); //get error size
    //std::cout << this->error_size <<std::endl;

    this->number_of_elements = std::strtoul(this->filename.substr(dotPos+1, signPos-dotPos-1).c_str(), nullptr, 10); //get number of elements in instance definition
    //std::cout << this->required_size << std::endl;

    this->required_size = this->number_of_elements + solver::L-1;

}

solver::~solver() {
    //TODO destroy shit
    instance->clear();
    instance->shrink_to_fit();
    delete instance;

    delete buildStrategy;
    delete goThroughStrategy;
}


