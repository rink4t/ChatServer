#ifndef Cliente_hpp
#define Cliente_hpp

#include "data.h"

class Cliente{
private:
    struct sockaddr_in client;
    int clientsockid;
    std::string name;
public:
    Cliente();

    inline int getSockid() const{return clientsockid;}
    inline std::string getName() const{return name;}

    void setclientaddr(struct sockaddr_in *c);
    void setsockid(int sock);
    void setname(std::string n);

    ~Cliente();
};

#endif //Cliente_hpp