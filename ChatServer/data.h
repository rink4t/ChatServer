#define _WIN32_WINNT _WIN32_WINNT_WIN10 _WINSOCK2API_ 

#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <mutex>
#include <chrono>

#define Dreams(ms) (std::this_thread::sleep_for(std::chrono::milliseconds(ms)))

