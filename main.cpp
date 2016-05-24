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
#include "Commands.hpp"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    char* ip = "127.0.0.1";
    int port = 6969;
    if(argc > 1){
        ip = argv[1];
        port = atoi(argv[2]);
    }

    int Meusocket;
    struct sockaddr_in vitima;
    int Conector;

    Meusocket = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);
    if ( Meusocket < 0 ) /* Aqui faz-se uma simples checagem de erro */
    {
        perror("Socket");
        exit(1);
    }

    vitima.sin_family = AF_INET;
    vitima.sin_port = htons(port);
    vitima.sin_addr.s_addr = inet_addr(ip);

    std::cout<< "Connecting to: " << ip << " port: " << port << std::endl;

    Conector = connect(Meusocket, ( struct sockaddr * ) &vitima, sizeof (vitima));
    if ( Conector < 0 ) /* Mais uma checagem de erro */
    {
        handle_error("connect");
    }
    
    std::cout<< "Connected!" << std::endl;


    char bufferCommand[COMMANDS_BUFFER_SIZE];
    char bufferMessage[MESSAGE_BUFFER_SIZE];
    int ind = 0;

    bool finaliza = false;
    std::string com;
    do
    {
        cin>>com;
        if ( com[0] != '/' )
        {
            std::cout << "Not a valid command: " << com << std::endl;
            continue;
        } else if ( com.compare("/exit") == 0 )
        {
            std::cout << "Exit command" << std::endl;
            finaliza = true;
        } else
        {
            strcpy(bufferCommand, com.c_str());

            std::cout << "sending: " << bufferCommand << std::endl;

            if ( write(Meusocket, bufferCommand, COMMANDS_BUFFER_SIZE) < 0 )
            {
                perror("write");
            }
            bzero(bufferCommand, COMMANDS_BUFFER_SIZE);


            if ( recv(Meusocket, bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
            {
                perror("recv");
            }
            cout << bufferMessage;
            bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

        }

    } while ( !finaliza );

    close(Meusocket);

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

