#include "Cliente.hpp"

Cliente::Cliente(){
    memset(&client, 0, sizeof(client));
    clientsockid = 0;
    name = "default";
}

void Cliente::setclientaddr(sockaddr_in *c){
    memcpy(&client, c, sizeof(client));
}

void Cliente::setsockid(int sock){
    clientsockid = sock;
}

void Cliente::setname(std::string n){
    name = n;
}

Cliente::~Cliente(){}
