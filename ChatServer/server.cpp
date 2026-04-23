#include "Serv.hpp"
#include <iostream>

int main(void){
    const auto start = std::chrono::high_resolution_clock::now();
    std::string host = "127.0.0.1";

    Serv *serv = new Serv(host, AF_INET, 10);

    serv->InitServ();
    serv->Runt();
    serv->Clean();

    const auto finish = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = finish - start;

    std::cout << "Time " << elapsed.count() << "\n";

    return 0;
}