#ifndef CClient_hpp
#define CClient_hpp

#include "data.h"
#include <string>
#include <mutex>

class CClient{
private:
    std::string cliente;
    bool state;
    std::mutex mtx;
public:
    CClient();
    void clisend(int sock);
    void envia(int sock, std::string buffer, size_t size);
    void clirec(int sock);
    void clid(int sock);
    ssize_t readn(int fd, std::string *vptr, size_t n);
    void gui(int sock);
    std::string modf();
    ~CClient();
};

#endif //CClient_hpp