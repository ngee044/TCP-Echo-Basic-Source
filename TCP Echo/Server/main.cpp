#include <iostream>
#include <string>
#include <winsock2.h>

using namespace std;

void ShowErrorMessage(string message)
{
	cout << "[���� �߻�]: " << message << '\n';
	system("pause");
	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAddress, clientAddress;

	int serverPort = 9876;
	char received[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //winsock�� �ʱ�ȭ �մϴ�.
	{
		ShowErrorMessage("WSAstartup()");
	}

	serverSocket = socket(PF_INET, SOCK_STREAM, 0); //TCP ������ ����

	if (serverSocket == INVALID_SOCKET)
	{
		ShowErrorMessage("socket()");
	}

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // 4����Ʈ ������ ��Ʈ��ũ ����Ʈ ��������...
	serverAddress.sin_port = htons(serverPort); // 2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������...

	if (bind(serverSocket, (SOCKADDR*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
		ShowErrorMessage("bind()");
	cout << "[Current Status] bind() \n";

	if(listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErrorMessage("listen()");
	cout << "[Current Status] listen() \n";

	int sizeClientAddress = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAddress, &sizeClientAddress);
	cout << "[Current Status] accpet() \n";

	while (1)
	{
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL;
		cout << "[Client Msg] : " << received << "\n";
		cout << "[Msg Send] : " << received << "\n";

		if (strcmp(received, "[exit]") == 0)
		{
			send(clientSocket, received, sizeof(received) -1, 0);
			cout << "[Server Exit]\n";
			break;
		}
		send(clientSocket, received, sizeof(received) -1, 0);
	}

	closesocket(clientSocket);
	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}


