#include<iostream>
#include<WinSock2.h>
#include<ws2tcpip.h>
#include<thread>
#include<string>
#include<Windows.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

/*
Steps Involved in Client Creation
 create Socket
 connect to the server
 send/recv
 Close the  Socket

*/
bool Initialize()
{
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}
void PrintHeader() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "**************************************************" << endl;
    cout << "*              Welcome to Chat Client             *" << endl;
    cout << "**************************************************" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
void PrintDivider() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "--------------------------------------------------" << endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
void SendMsg(SOCKET s)
{

    cout << "Enter Your Nick Name: "<<endl;

    string name;
    getline(cin, name);
    string message;

    while (true)
    {
        getline(cin, message);
        string msg = name + " : " + message;
        int bytesent = send(s, msg.c_str(), msg.length(), 0);
        if (bytesent == SOCKET_ERROR)
        {
            cout << "ERROR IN SENDING MESSAGE" << endl;
            break;
        }

        if (message == "quit")
        {
            cout << "STOPPING THE Application ........" << endl;
            break;
        }
    }
    closesocket(s);
    WSACleanup();
}

void ReceiveMsg(SOCKET s)
{
    char buffer[4096];
    int recvlength = 0;

    while (true)
    {
        recvlength = recv(s, buffer, sizeof(buffer), 0);
        if (recvlength <= 0)
        {
            cout << "DISCONNECTED FROM THE SERVER" << endl;
            break;
        }
        cout << "Server: " << string(buffer, recvlength) << endl;
    }
    closesocket(s);
    WSACleanup();
}

int main()
{
    PrintHeader();
    cout << "Client program started" << endl;

    if (!Initialize())
    {
        cout << "Initialize winsock Failed" << endl;
        return 1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        cout << "INVALID SOCKET CREATED" << endl;
        return 1;
    }

    int port = 12345;
    string serveraddress = "127.0.0.1";
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET, serveraddress.c_str(), &(serveraddr.sin_addr));

    if (connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
    {
        cout << "NOT ABLE TO CONNECT TO SERVER" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }

    cout << "SUCCESSFULLY CONNECTED TO SERVER" << endl;

    thread senderthread(SendMsg, s);
    thread receiver(ReceiveMsg, s);

    senderthread.join();
    receiver.join();

    return 0;
}
