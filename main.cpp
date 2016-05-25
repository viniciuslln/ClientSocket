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
#include <map>
#include "Commands.hpp"

#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

using namespace std;


std::map<std::string, Commands> mapCommand = {
        {"/help",          Commands::HELP},
        {"/exit",          Commands::EXIT},
        {"/loggin_hour",   Commands::LOOGING_HOUR},
        {"/server_ip",     Commands::SERVER_IP},
        {"/my_ip",         Commands::MY_IP},
        {"/server_hour",   Commands::SERVER_HOUR},
        {"/server_memory", Commands::SERVER_MEMORY},
        {"/server_hd",     Commands::SERVER_HD},
        {"/server_time",   Commands::SERVER_TIME},
        {"/server_pro", Commands::SERVER_PRO},
        {"/server_open_ports", Commands::SERVER_OPEN_PORTS}
    };

/*
 * 
 */
int main(int argc, char** argv)
{
    char* ip = "127.0.0.1";
    int port = 6969;
    char bufferCommand[COMMANDS_BUFFER_SIZE];
    char bufferMessage[MESSAGE_BUFFER_SIZE];
    
    //Recuperando ip de conexão dos args ------------------------------------
    if(argc > 1){
        ip = argv[1];
        port = atoi(argv[2]);
    }

    int thisClient;
    struct sockaddr_in socketAddres;
    int server;

    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(port);
    socketAddres.sin_addr.s_addr = inet_addr(ip);
    
    thisClient = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);
    if ( thisClient < 0 ) 
    {
        perror("Socket");
        exit(1);
    }

    std::cout<< "Connecting to: " << ip << " port: " << port << std::endl;

    server = connect(thisClient, ( struct sockaddr * ) &socketAddres, sizeof (socketAddres));
    if ( server < 0 ) 
    {
        handle_error("connect");
    }
    
    std::cout<< "Connected!" << std::endl;

    bool finaliza = false;
    std::string com;
    do
    {
        //digitar comando
        cin>>com;
        
        if ( com[0] != '/' )
        {
            std::cout << "Not a valid command: " << com << std::endl;
            std::cout << "Type \"/help\" to show commands. " << std::endl;
            continue;
        } else if(mapCommand.find(com) == mapCommand.end())
        {
            std::cout << "Not a valid command: " << com << std::endl;
            std::cout << "Type \"/help\" to show commands. " << std::endl;
            continue;
        } else if ( com.compare("/exit") == 0 )
        {
            std::cout << "Exit command" << std::endl;
            finaliza = true;
        } else if(com.compare("/help") == 0)
        {
            std::cout << "Available commands: " << std::endl;
            std::cout << "/help,\tFor help." << std::endl;
            std::cout << "/exit,\tTo exit."  << std::endl;
            std::cout << "/loggin_hour,\tFor this client login hour." << std::endl;
            std::cout << "/server_ip,\tFor server Ip.     " << std::endl;
            std::cout << "/my_ip,\tFor this client Ip.        " << std::endl;
            std::cout << "/server_hour,\tFor server actual hour." << std::endl;
            std::cout << "/server_memory\tFor server available memory.  " << std::endl;
            std::cout << "/server_hd,\tFor server disck partitions."  << std::endl;  
            std::cout << "/server_pro,\tFor server process info."  << std::endl;  
            std::cout << "/server_open_ports,\tFor server available ports."  << std::endl;  
        }
        else
        {
            strcpy(bufferCommand, com.c_str());

            std::cout << "sending: " << bufferCommand << std::endl;

            if ( write(thisClient, bufferCommand, COMMANDS_BUFFER_SIZE) < 0 )
            {
                perror("write");
            }
            bzero(bufferCommand, COMMANDS_BUFFER_SIZE);


            if ( recv(thisClient, bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
            {
                perror("recv");
            }
            cout << bufferMessage;
            bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

        }
        std::cout << std::endl;  
    } while ( !finaliza );

    close(thisClient);

    return 0;
}

