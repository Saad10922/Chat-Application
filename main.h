


#pragma once

int main()
{
	if (!Initilize())
	{
		cout << "winsock initilization failed" << endl;
	}



	cout << "Server Program";
	SOCKET listenSocket = socket(AF_INET /*Uusing ipv4*/, SOCK_STREAM/*TCP*/, 0);
	if (listenSocket == INVALID_SOCKET)
	{
		cout << "socket creation failed" << endl;
		return 1;
	}
	//create address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	//Convert the ip address (0.0.0.0) put it inside the sin_family in binary Format
	;
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "Setting address structure failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;

	}

	//bind code
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR)
	{
		cout << "bind filed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	//listern
	if(listen(listenSocket, SOMAXCONN/*amount of request it will put in the queue*/) == SOCKET_ERROR)
	{
		cout << "listen failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}
	cout << "server has stated listening on port :v" << port << endl;
	//Accept connection from client
	SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "invalid client socket " << endl;
	}
	char buffer[4096];
	int bytesrecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
	string message(buffer, bytesrecvd);
	cout << "Message from client : " << message << endl;

	closesocket(clientSocket);
	closesocket(listenSocket);
	WSACleanup();
	return 0;
}
