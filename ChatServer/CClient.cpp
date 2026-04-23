#include "CClient.hpp"
#include <iostream>

#define Buffer 1024
#define namebuf 128

CClient::CClient(){
    state = true;
}

void CClient::clisend(int sock){
    std::string sendbuf;

    while(std::getline(std::cin, sendbuf, '\n')){
        if(mtx.try_lock()){
            if(sendbuf == "<exit>") {state = false; break;}
            mtx.unlock();
        }

        if(sendbuf == "<change>"){
            envia(sock, sendbuf.c_str(), sendbuf.size());
            sendbuf.clear();
        }else{
            if(sendbuf.length() > 896){
                std::cout << "Message exceeds the max size supported" << "\n";
            }else{
                envia(sock, sendbuf.c_str(), sendbuf.size());
            }
        }
        sendbuf.clear();
        Dreams(10);
    }
    closesocket(sock);
}

void CClient::envia(int sock, std::string buffer, size_t size){
    int sizeb;
    sizeb = send(sock, buffer.c_str(), size, 0);
    if(sizeb < 0) state = false;
}

void CClient::clirec(int sock){
    std::string recbuffer;
    int data;
    bool runing = state;

    while(runing){
        if((data = readn(sock, &recbuffer, Buffer)) > 0){
            std::cout << recbuffer << "\n";
        } 
        
        if(!state) runing = false;
       
        Dreams(10);
    }
}

void CClient::clid(int sock){
    gui(sock);

    std::thread sendata(clisend, this, sock);
    std::thread recdata(clirec, this, sock);

    sendata.join();
    recdata.join();
}

ssize_t CClient::readn(int fd, std::string *vptr, size_t n){}

void CClient::gui(int sock){
    std::string other;
    std::cout << "Write your name: \n";
    cliente = modf();
    envia(sock, cliente.c_str(), cliente.size());

    std::cout << "Write your friends name: \n";
    other = modf();
    envia(sock, other.c_str(), other.size());
}

std::string CClient::modf(){
    std::string name;
    std::cin >> name;

    if(name.size() > namebuf){
        return name = name.substr(0, namebuf-1);    
    }

    return name;
}

CClient::~CClient(){}
