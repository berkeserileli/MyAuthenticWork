#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")


int main() {
	WSADATA wsadata;
	WORD wVersionRequested = MAKEWORD(2, 2); //WORD, að sýnýfýndan 16 bitlik bir tamsayý tutan veri türüdür, Að paketlerinde baþlýk bölümündeki deðerleri temsil etmek için kullanýlýr.Bu deðerler, paketin uzunluðu, protokol numarasý, hata denetimi gibi bilgileri içerebilir.
	int wsaerr = WSAStartup(wVersionRequested, &wsadata);
	if (wsaerr != 0) {
		std::cout << "Windows Server sockets are not found!" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Windows Server sockets are found!" << std::endl;
	}

	SOCKET myServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //SOCK_DGRAM gönderilen UDP dosyalarýný temsil eder, SOCK_DGRAM herhangi bir socket nesnesine atanmalýdýr.
	if (myServerSocket == -1) {
		std::cout << "Server socket is not available!" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "Server socket is available!" << std::endl;
		//std::cout << "Server port is: " << getservbyport << std::endl;
	}

	struct sockaddr_in servaddr; //sockaddr_in yapýsý IPv4 tabanlý soket adreslerini temsil eder.Structýn içerisinde IP adresi, port numarasý ve IPv4 adresi yer alýr.
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
	//= recvfrom(myServerSocket,(char*)buffer, sizeof(buffer), 0, (struct sockaddr*)&clientaddr, &client_addr_len); //recvfrom() , alýnan verinin uzunluðunu byte cinsinden döndürür.

	//if (accept(myServerSocket, (struct sockaddr*)&servaddr, &clientMessageLength) == -1) { //server baðlantý gerektirmediðinden dolayý UDP için, accept kullanýlmaz.
		//std::cout << "Connection is not accepted!" << WSAGetLastError() << std::endl;
	//}
	//else {
		//std::cout << "Connection accepted by the server!" << std::endl;
	//}

	while (true) {
		//if (listen(myServerSocket, 5) == 0)  //listen() fonksiyonu, server soketinin baðlantýyý kabul etmeye hazýr olup olmadýðýný kontrol eder fakat UDP soketleri baðlantý gerektirmezler! TCP baðlantýlarý için kullanýlýr.
		
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



