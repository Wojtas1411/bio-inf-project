#include <iostream>
#include <string>
#include <filesystem>
#include <thread>
#include "Define.h"

//g++ -std=c++17 -Wall main.cpp -o ./cmake-build-debug/test -lstdc++fs --compile with gcc :)))

void solve(std::string filename){
    std::cout << filename << std::endl;
    //TODO
}

int main() {
    std::string input_path = "../instances";

    // vector of filenames
    auto *filenames = new std::vector<std::string>();

    for(const auto & entry : std::filesystem::directory_iterator(input_path)){
        filenames->push_back(entry.path());
    }

    //number of instances
    size_t number_of_instances = filenames->size();

    //tab of threads - one per instance
    auto *threads = new std::thread[number_of_instances];

    //iterator for thread dispatch
    size_t iter = 0;

    //thread dispatch - max THREAD_NUM threads at once
    for(const auto & a : *filenames){

        if(iter >= THREAD_NUM){
            threads[iter-THREAD_NUM].join();
        }

        if(iter < number_of_instances){
            threads[iter] = std::thread(solve, a);
        }

        iter++;
    }

    //close remaining threads
    for(size_t i=iter-THREAD_NUM; i<iter; i++){
        threads[i].join();
    }

    return 0;
}