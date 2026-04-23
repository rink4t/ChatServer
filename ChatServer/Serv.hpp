#ifndef Serv_hpp
#define Serv_hpp

#include "data.h"
#include "Cliente.hpp"
#include <vector>
#include <string>

#define SA struct sockaddr *

class Serv{
private:
    std::string host;
    struct sockaddr_in server, client;
    struct sockaddr_in6 serverv6;
    int family_option, maxclients, sockid;

    std::vector<Cliente*> Vclients;
    std::vector<std::thread> hilos;
    std::mutex tx;
    
    ssize_t readn(int fd, std::string *vptr, size_t n);
    void AcceptInCon();
    void recdata(int sock);
    void createThreath(int sock);
    void sendbyname(std::string obj, std::string streambuff, std::string thname);
    Cliente* setEm(int s);

public:
    Serv(std::string name, int family, int cliadmit);
    void InitServ();
    void Runt();
    void Clean();
    ~Serv();
};

#endif //Serv_hpp