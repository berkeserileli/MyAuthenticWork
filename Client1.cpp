#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")


int main() {

    WSADATA wsadata2;
    WORD Request = MAKEWORD(2, 2); //WORD, að sýnýfýndan 16 bitlik bir tamsayý tutan veri türüdür, Að paketlerinde baþlýk bölümündeki deðerleri temsil etmek için kullanýlýr.Bu deðerler, paketin uzunluðu, protokol numarasý, hata denetimi gibi bilgileri içerebilir.
    int wsaerr2 = WSAStartup(Request, &wsadata2);
    if (wsaerr2 != 0) {
        std::cout << "Windows Server sockets are not found!" << std::endl;
        WSACleanup();
    }
    else {
        std::cout << "Windows Server sockets are found!" << std::endl;
    }


    SOCKET myClientServer = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (myClientServer == -1) {
        std::cout << "Client Socket was not created!" << std::endl;
        return 1;
    }
    else {
        std::cout << "Client socket was created!" << std::endl;
    }

    const char* message = "Merhaba bu bir test mesaji.";

    sockaddr_in destinationAdress{};
    destinationAdress.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &(destinationAdress.sin_addr));
    destinationAdress.sin_port = htons(8000);

    int sent_bytes = sendto(myClientServer, message, strlen(message), 0, (struct sockaddr*)&destinationAdress, sizeof(destinationAdress));
    if (sent_bytes == -1) {
        std::cout << "Data was not sent!" << std::endl;
        closesocket(myClientServer);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Data sent: " << sent_bytes << std::endl;
    }
    
    closesocket(myClientServer);
    return 0;
}
