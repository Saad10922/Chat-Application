# Chat Application using Socket Programming
This repository contains the implementation of a chat application using socket programming in C++. The application allows multiple clients to communicate with each other in real-time over a network connection. The project demonstrates the use of socket programming concepts and provides a practical example of client-server communication.

## Project Description

The chat application consists of a server program and a client program. The server listens for incoming client connections and facilitates message exchange between connected clients. Each client can send messages to the server, which then broadcasts the messages to all connected clients. The application supports multiple clients and provides a basic chat room functionality.

## How to Run
**First of all extract these three zip files**
1.Server
2.Client
3.Client2

Then open the server folder and run server.sln Now similarly open client one folder And run the client.sln file similarly open the second client folder and run its client.sln file now as server is running both of the clients get connected to the server and when we type a message from one client it gets sent to the server and make sure that you have written the user name on each client program.

### Prerequisites
1.**Visual Studio 2022**
Alternatives
1. Ensure you have a C++ compiler installed (e.g., GCC, MinGW, Visual Studio).
2. Ensure you have Git installed to clone the repository.
3. Install Windows Sockets 2 (Winsock) if not already installed.

### Step-by-Step Instructions

1. **Clone the Repository**
   git clone https://github.com/your-username/ChatApplication.git
   cd ChatApplication
 2.  **Compile the Server Program**

On Windows using Command Prompt
cl /EHsc server.cpp /link ws2_32.lib

On Linux or macOS (modify appropriately for cross-platform compatibility if needed):
g++ server.cpp -o server -lws2_32


g++ server.cpp -o server -lws2_32
cl /EHsc client.cpp /link ws2_32.lib


3. **Compile the Client Program**

On Windows using Command Prompt
cl /EHsc client.cpp /link ws2_32.lib

On Linux or macOS (modify appropriately for cross-platform compatibility if needed):
g++ client.cpp -o client -lws2_32


4.**Run the Server**

On Windows:
server.exe

On Linux or macOS:
./server

5. **Run the Client**
On Windows:
client.exe

On Linux or macOS:
./client

6. **Connect Multiple Clients**

Repeat step 5 on different terminals or machines to connect multiple clients to the server.
**Dependencies**
Winsock2 library (Windows only)
A C++ compiler that supports C++11 or later
Git


**Additional Information**
For detailed code and documentation, refer to the source files: server.cpp and client.cpp. Ensure that the server is running before starting any client instances. The server will handle client connections and facilitate message broadcasting.

If you encounter any issues or have questions, feel free to open an issue in the repository.







6. 
