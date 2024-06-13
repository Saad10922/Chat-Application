#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
#include<vector>
#include<mutex>
#include<algorithm>
#include<Windows.h>

using namespace std;
#pragma comment(lib,"ws2_32.lib")//for linking window Socket Library
/*
<==Steps for Writting Server Code==>

//Initilize winsock library
//create the socket
//get the ip and port
//bind the ip/port in socket
//listen on the socket
//accept
//receive and send
//close the socket
// cleanup the winsock




*/
bool Initilize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0; //Version 2.2
}
void PrintHeader() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "**************************************************" << endl;
    cout << "*              Welcome to Chat Server             *" << endl;
    cout << "**************************************************" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void PrintDivider() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "--------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}

void IntractWithClient(SOCKET clientSocket, vector<SOCKET>& clients, mutex& mtx) {
    cout << "Client Connected" << endl;
    char buffer[4096];

    while (true) {
        int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesrecvd <= 0) {
            cout << "Client Disconnected" << endl;
            break;
        }
        string message(buffer, bytesrecvd);
        cout << "Message from client: " << message << endl;

        lock_guard<mutex> lock(mtx); // Lock the mutex for safe access to clients
        for (auto client : clients) {
            if (client != clientSocket) {
                send(client, message.c_str(), message.length(), 0);
            }
        }
    }

    {
        lock_guard<mutex> lock(mtx); // Lock the mutex for safe access to clients
        auto it = find(clients.begin(), clients.end(), clientSocket);
        if (it != clients.end())
            clients.erase(it);
    }
    closesocket(clientSocket);
}

int main() {
    PrintHeader();

    if (!Initilize()) {
        cout << "winsock initilization failed" << endl;
        return 1;
    }

    cout << "Server Program Started" << endl;
    SOCKET listenSocket = socket(AF_INET /*Using ipv4*/, SOCK_STREAM/*TCP*/, 0);
    if (listenSocket == INVALID_SOCKET) {
        cout << "socket creation failed" << endl;
        return 1;
    }

    int port = 12345;
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
        cout << "Setting address structure failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        cout << "bind failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN /*amount of request it will put in the queue*/) == SOCKET_ERROR) {
        cout << "listen failed" << endl;
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    cout << "server has started listening on port: " << port << endl;
    vector<SOCKET> clients;
    mutex mtx;

    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            cout << "invalid client socket " << endl;
            continue;
        }

        {
            lock_guard<mutex> lock(mtx); // Lock the mutex for safe access to clients
            clients.push_back(clientSocket);
        }

        thread t1(IntractWithClient, clientSocket, ref(clients), ref(mtx));
        t1.detach();
    }

    closesocket(listenSocket);
    WSACleanup();
    return 0;
}
