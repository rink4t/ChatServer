#include "data.h"
#include "CClient.hpp"
#include <iostream>
#include <string>

#define SA struct sockaddr *

int main(){
    CClient *dur = new CClient();
    WSADATA wsa;
    int sock;
    std::string host = "127.0.0.1";
    struct sockaddr_in servl;

    if(WSAStartup(MAKEWORD(2,2), &wsa)){
        std::cout << "Error: " << "WSA not startup" << "\n";
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&servl, 0, sizeof(servl));
    servl.sin_port = htons(9877);
    servl.sin_family = AF_INET;
    if(inet_pton(AF_INET, host.c_str(), &servl.sin_addr) <= 0){
        return 1;
    }

    connect(sock, reinterpret_cast<SA>(&servl), sizeof(servl));

    dur->clid(sock);
    dur->~CClient();
    WSACleanup();

    return 0;
}



