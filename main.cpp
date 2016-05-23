/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: vinih
 *
 * Created on 22 de Maio de 2016, 10:03
 */

#include <cstdlib>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define buf_size 256
#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    int Meusocket;
	struct sockaddr_in vitima;
	int Conector;

	Meusocket = socket(AF_INET,SOCK_STREAM,  0);//IPPROTO_TCP);
	if(Meusocket < 0) /* Aqui faz-se uma simples checagem de erro */
	{
		perror("Socket");
		exit(1);
	}

	vitima.sin_family = AF_INET;
	vitima.sin_port = htons(6969);
	vitima.sin_addr.s_addr =  inet_addr("127.0.0.1");

	Conector = connect(Meusocket,(struct sockaddr * )&vitima, sizeof(vitima));
	if(Conector < 0) /* Mais uma checagem de erro */
	{
            handle_error("connect");
	}
        
        char buffer[buf_size];
        int ind = 0 ;

        do
        {
            recv(Meusocket, buffer, buf_size, 0);
            cout << buffer;
            
            
            
            strcpy(buffer, "=> Client response... no: ");        
            sprintf(buffer,"%s%d",buffer, ind);
            strcat(buffer, "\n");

            write(Meusocket, buffer, buf_size);
            
            ind++;
        }while(1);

//        for(ind = 0; ; ind++)
//        {
//
//            int n = recv(Meusocket, buffer, buf_size, MSG_WAITALL );
//            
//            if (n < 0)
//               cout << "ERROR reading from socket\n";
//
//            
//            cout << "Here is the message: \n" <<  buffer << endl;
//
//            strcpy(buffer, "=> Client response... no: ");        
//            sprintf(buffer,"%s%d",buffer, ind);
//            strcat(buffer, "\n");
//            
//            n = write(Meusocket, buffer, buf_size);
//
//           if (n < 0)
//               cout << "ERROR writing to socket\n";            
//            
//            
//        }

        
        
        
    return 0;
}

