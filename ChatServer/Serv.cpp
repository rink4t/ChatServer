#include "Serv.hpp"
#include <iostream>
#include <algorithm>

#define Buffer 1024

ssize_t Serv::readn(int fd, std::string *vptr, size_t n){
	
	ssize_t nread;
	char ptr[n];

 	if ( (nread = recv(fd, ptr, n, 0)) < 0) {
 		if (errno == EINTR)
			nread = 0; 
		else
		return (-1);
	} 
    ptr[nread] = '\0';
    *vptr = std::string(ptr);
    memset(ptr, 0, sizeof (ptr));
	return (n - nread); 
}

void Serv::AcceptInCon(){
    int cliIdsock;
    int clientsize = sizeof(client);
    std::cout << "IM here\n";

    while(1){
        if((cliIdsock = accept(sockid, reinterpret_cast<SA>(&client), &clientsize)) != 0){
            Cliente *clien = new Cliente;
            clien->setsockid(cliIdsock);
            clien->setclientaddr(&client);
            Vclients.push_back(clien);
            createThreath(clien->getSockid());
        }
        Dreams(10);
    }
    closesocket(sockid);
}

void Serv::recdata(int sock){
    int clit, n = 0;
    bool change = false, connf = true;
    std::string stream;
    std::string setn;
    Cliente *cli;
    
    cli = setEm(sock);

    while(1){
        n = readn(cli->getSockid(), &stream, Buffer);
        if(n > 0){
           if(connf){
                setn = stream;
                stream.clear();
                connf = false;
                continue;
            }else{
                if(stream == "<change>"){
                    change = true;
                    stream.clear();
                    continue;
                }

                if(change){
                    setn = stream;
                    stream.clear();
                    change = false;
                }else{
                    std::cout << stream << "\n";
                    sendbyname(setn, stream, cli->getName());
                    stream.clear();
                }
            }
        }
        if(n == 0) break;
        Dreams(1);
    }

    closesocket(cli->getSockid());
    clit = Vclients.size();
    for(int x = 0; x < clit; x++){
        if(Vclients[x]->getSockid() == cli->getSockid()){
            cli->~Cliente();
            Vclients.erase(Vclients.begin() + x);
        }
    } 
}

void Serv::createThreath(int sock){
    std::thread(recdata, this, sock).detach();
}

void Serv::sendbyname(std::string obj, std::string streambuff,  std::string thname){
    std::string data = obj, temp = thname;
    int clit = Vclients.size();

    for(int x = 0; x < clit; x++){
        if(Vclients[x]->getName() == data ){
            temp.append(": " + streambuff);
            send(Vclients[x]->getSockid(), temp.c_str(), temp.size(), 0);
        }
    } 
}

Cliente* Serv::setEm(int s){
    std::string setn; int h, clit;
    clit = Vclients.size();
    readn(s, &setn, Buffer);
    for(int x = 0; x < clit; x++){
        if((h = Vclients[x]->getSockid()) == s){
            Vclients[x]->setname(setn);
            return Vclients[x];
        }
    } 
    return NULL;
}

Serv::Serv(std::string name, int family, int cliadmit){
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
    hilos.reserve(cliadmit);
    family_option = family;
    maxclients = cliadmit;
    host = name;
}

void Serv::InitServ(){
    switch(family_option){
    case AF_INET:
            sockid = socket(AF_INET, SOCK_STREAM, 0);
            memset(&server, 0, sizeof(server));
            server.sin_port = htons(9877);
            server.sin_family = AF_INET;
            inet_pton(AF_INET, host.c_str(), &server.sin_addr.S_un.S_addr);
            bind(sockid, reinterpret_cast<SA>(&server), sizeof(server));
            listen(sockid, maxclients);
        break;
    case AF_INET6:
            sockid = socket(AF_INET6, SOCK_STREAM, 0);
            memset(&serverv6, 0, sizeof(serverv6));
            serverv6.sin6_port = htons(9877);
            serverv6.sin6_family = AF_INET6;
            inet_pton(AF_INET6, host.c_str(), &serverv6.sin6_addr);
            bind(sockid, reinterpret_cast<SA>(&serverv6), sizeof(serverv6));
            listen(sockid, maxclients);
        break;
    default:
        break;
    }
}

void Serv::Runt(){
    std::cout << "IM here\n";
    AcceptInCon();
}

void Serv::Clean(){
    WSACleanup();
}

Serv::~Serv(){}
