//
// Created by wojtek on 23.03.19.
//

#include "solver.h"

bool operator < (const Element& element1, const Element& element2)
{
    return (element1.size < element2.size);
}

bool operator > (const Element& element1, const Element& element2)
{
    return (element1.size > element2.size);
}

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

unsigned long solver::indexOfMaxElement(std::vector<Element> &input) {
    unsigned long max_index = 0;
    unsigned long max_current = 0;
    for(unsigned long  i=0; i<input.size(); i++){
        if(input[i].getSize() > max_current){
            max_current = input[i].getSize();
            max_index = i;
        }
    }
    return max_index;
}

void solver::solve() {
    int li = solver::L -1;

    std::vector<Element> result = this->instance;

    //std::cout<<this->id<<"\t"<<this->filename<<std::endl;

    //start timer
    auto start = std::chrono::system_clock::now();

    while(li > 3){
        this->buildStrategy->setLi(li);
        this->goThroughStrategy->setLi(li);
        //std::cout<<this->filename + "\t"<<li<<std::endl;

        //sort before each restart
        //std::sort(result.begin(), result.end());

        std::vector<std::vector<int>> * graph = buildStrategy->getListOfNeighbours(result);
        //std::cout<<"Number of edges:\t"<<this->buildStrategy->getNumOfEdges()<<std::endl;
        if(this->buildStrategy->getNumOfEdges() == 0){
            li--;       //decrease li parameter
            continue;   //continue
        }

        //std::cout<<"Graph size:\t " << graph->size()<<std::endl;
        if(graph->size() == 1) break; //if there is single element in graph -> could be result size equals 1

        result = goThroughStrategy->goThrough(result, *graph,
                buildStrategy->getPriorityQueue(),
                buildStrategy->getSiblingPriorityQueue());

        unsigned long current_best = this->indexOfMaxElement(result);

        //std::cout<<li<<"\t"<<result[current_best].getSize()<<"\t"<<result[current_best].getValue().size()<<std::endl;

        if(result[current_best].getSize() >= this->number_of_elements) {
            std::cout << "Solution limit reached" << std::endl;
            break;
        }

            //debug output

//        if(result.size() != 1) std::cout << this->filename << "\tToo big result\t" << li << std::endl;
//        for(auto & a : result){
//            std::cout<<a.getSize()<<"\t"<<a.getParts()->size()<<"\t"<<a.getValue().size()<<"\t"<<a.calculateTotalLengthOfParts()<<"\t";
//            std::cout<<a.getValue()<<"\t";
//            for(auto & b : *a.getParts()){
//                std::cout<<b.getValue()<<"\t";
//            }
//            std::cout<<std::endl;
//        }
    }

    std::sort(result.begin(), result.end(), std::greater<Element>());

    //unsigned long max_element = this->indexOfMaxElement(result);

    Element best_result = result[0];

    //pack with best fit
    if(best_result.getSize() < required_size){
        for(unsigned long i = 1; i<result.size(); i++){
            if(best_result.getValue().size() + result[i].getValue().size() - best_result.appendSize(result[i]) < required_size + treshold){
                best_result.appendElement(result[i], best_result.appendSize(result[i]));
            }
        }
    }

    //end timer
    auto end = std::chrono::system_clock::now();
    //save time
    this->time = (double) std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()/1000;

    best_result.trimToSize(this->number_of_elements);

    //fill chain size
    this->chain_size = best_result.getValue().size();
    //fill used elements
    this->used_elements = best_result.getSize();

    //debug output

//    for(auto & a : result){
//        std::cout<<a.getSize()<<"\t"<<a.getParts()->size()<<"\t"<<a.getValue().size()<<"\t"<<a.calculateTotalLengthOfParts()<<"\t";
//        std::cout<<a.getValue()<<"\t";
//        for(auto & b : *a.getParts()){
//            std::cout<<b.getValue()<<"\t";
//        }
//        std::cout<<std::endl;
//    }

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
    //TODO destroy stuff
    instance.clear();
    instance.shrink_to_fit();
    //delete instance;

    delete buildStrategy;
    delete goThroughStrategy;
}


