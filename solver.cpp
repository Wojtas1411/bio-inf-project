//
// Created by wojtek on 23.03.19.
//

#include "solver.h"

//setting output csv header and delimiter
const std::string solver::delimiter = ";";
const std::string solver::header_line =
        "id" + solver::delimiter +
        "filename" + solver::delimiter +
        "time" + solver::delimiter +
        "error type" + solver::delimiter +
        "number of elements" + solver::delimiter +
        "number of elements real" + solver::delimiter +
        "error size" + solver::delimiter +
        "used elements" + solver::delimiter +
        "chain size" + solver::delimiter +
        "required size" + "\n";

std::string solver::getResult() {
    //TODO build csv string with output data
    std::stringstream ss = std::stringstream();
    ss << this->id << solver::delimiter;
    ss << this->filename << solver::delimiter;
    ss << this->time << solver::delimiter;
    ss << this->error_type << solver::delimiter;
    ss << this->number_of_elements << solver::delimiter;
    ss << this->number_of_elements_real << solver::delimiter;
    ss << this->error_size << solver::delimiter;
    ss << this->used_elements << solver::delimiter;
    ss << this->chain_size << solver::delimiter;
    ss << this->required_size << std::endl;

    return ss.str();
}

void solver::solve() {
    int li = solver::L -1;

    std::vector<Element> result = this->instance;

    //std::cout<<"Start"<<std::endl;

    //start timer
    auto start = std::chrono::system_clock::now();

    while(li > 0){
        this->buildStrategy->setLi(li);
        this->goThroughStrategy->setLi(li);
        //std::cout<<this->filename + "\t"<<li<<std::endl;

        std::vector<std::vector<int>> * graph = buildStrategy->getListOfNeighbours(result);
        //std::cout<<"Number of edges:\t"<<this->buildStrategy->getNumOfEdges()<<std::endl;
        if(this->buildStrategy->getNumOfEdges() == 0){
            li--;
        }

        //std::cout<<"Graph size:\t " << graph->size()<<std::endl;
        if(graph->size() == 1){
            break;
        }

        result = goThroughStrategy->goThrough(result, *graph, buildStrategy->getPriorityQueue());
    }

    //end timer
    auto end = std::chrono::system_clock::now();
    //save time
    this->time = (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000;

    //TODO sort or merge result

    //fill chain size
    this->chain_size = result[0].getValue().size();
    //fill used elements
    this->used_elements = result[0].getSize();

    if(result.size() != 1) std::cout<<"Too big result"<<std::endl;
}

solver::solver(int id, const char *filename, AbstractGraphBuildStrategy *graphBuildStrategy, AbstractGraphGoThroughStrategy *goThroughStrategy) {
    this->id = id;
    this->filename = filename;
    this->buildStrategy = graphBuildStrategy;
    this->goThroughStrategy = goThroughStrategy;

    this->instance =  std::vector<Element>();

    this->time = -1.0;
    this->chain_size = 0;
    this->used_elements = 0;

    std::ifstream in;
    in.open(filename);

    while(!in.eof()){
        std::string temp;
        in >> temp;
        if(!temp.empty()) this->instance.emplace_back(Element(temp));
    }

    in.close();

    this->filename = this->filename.substr(13);

    number_of_elements_real = this->instance.size();

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
    instance.clear();
    instance.shrink_to_fit();
    //delete instance;

    delete buildStrategy;
    delete goThroughStrategy;
}


