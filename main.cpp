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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{

    int client;
    int portNum = 1500; // NOTE that the port number is same for both client and server
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char* ip = "127.0.0.1";
 
    struct sockaddr_in server_addr;
 
    client = socket(AF_INET, SOCK_STREAM, 0);
    
    if (client < 0)
    {
        cout << "\nError establishing socket..." << endl;
        exit(1);
    }
    
    cout << "\n=> Socket client has been created..." << endl;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);
   
    if (connect(client,(struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cerr << "=> Connection to the server FAIL " << endl;
        exit(1);
    }
            
    cout << "=> Connection to the server port number: " << portNum << endl;

    cout << "=> Awaiting confirmation from the server..." << endl; //line 40
    recv(client, buffer, bufsize, 0);
    cout << "=> Connection confirmed, you are good to go...";
 
    cout << "\n\n=> Enter # to end the connection\n" << endl;
    
    
    return 0;
}

