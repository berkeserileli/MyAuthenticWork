#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")


int main() {
	WSADATA wsadata;
	WORD wVersionRequested = MAKEWORD(2, 2); //WORD, a� s�n�f�ndan 16 bitlik bir tamsay� tutan veri t�r�d�r, A� paketlerinde ba�l�k b�l�m�ndeki de�erleri temsil etmek i�in kullan�l�r.Bu de�erler, paketin uzunlu�u, protokol numaras�, hata denetimi gibi bilgileri i�erebilir.
	int wsaerr = WSAStartup(wVersionRequested, &wsadata);
	if (wsaerr != 0) {
		std::cout << "Windows Server sockets are not found!" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Windows Server sockets are found!" << std::endl;
	}

	SOCKET myServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //SOCK_DGRAM g�nderilen UDP dosyalar�n� temsil eder, SOCK_DGRAM herhangi bir socket nesnesine atanmal�d�r.
	if (myServerSocket == -1) {
		std::cout << "Server socket is not available!" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Server socket is available!" << std::endl;
		//std::cout << "Server port is: " << getservbyport << std::endl;
	}

	struct sockaddr_in servaddr; //sockaddr_in yap�s� IPv4 tabanl� soket adreslerini temsil eder.Struct�n i�erisinde IP adresi, port numaras� ve IPv4 adresi yer al�r.
	servaddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &(servaddr.sin_addr));
	servaddr.sin_port = htons(8000);

	if (bind(myServerSocket, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) {
		std::cout << "Binding has crashed! " << WSAGetLastError() << std::endl;
		closesocket(myServerSocket);
	}
	else {
		std::cout << "Binding is successful!" << std::endl;
	}


	char buffer[128];
	struct sockaddr_in clientaddr;
	int client_addr_len = sizeof(clientaddr);
	int receivedData = 0;
	//int receivedData 
	//= recvfrom(myServerSocket,(char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &client_addr_len); //recvfrom() , al�nan verinin uzunlu�unu byte cinsinden d�nd�r�r.

	//if (accept(myServerSocket, (struct sockaddr*)&servaddr, &clientMessageLength) == -1) { //server ba�lant� gerektirmedi�inden dolay� UDP i�in, accept kullan�lmaz.
		//std::cout << "Connection is not accepted!" << WSAGetLastError() << std::endl;
	//}
	//else {
		//std::cout << "Connection accepted by the server!" << std::endl;
	//}

	while (true) {
		//if (listen(myServerSocket, 5) == 0)  //listen() fonksiyonu, server soketinin ba�lant�y� kabul etmeye haz�r olup olmad���n� kontrol eder fakat UDP soketleri ba�lant� gerektirmezler! TCP ba�lant�lar� i�in kullan�l�r.
		
		//memset(buffer, 0, 1024);
		receivedData = recvfrom(myServerSocket,buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &client_addr_len);
		buffer[receivedData] = '\0';
		if (receivedData > 0) {
			std::cout << "Data successfully received!" << std::endl;
			std::cout << receivedData << " bytes received!" << std::endl;
			std::cout << buffer << std::endl;
		}

	};

	closesocket(myServerSocket);
	WSACleanup();
};



