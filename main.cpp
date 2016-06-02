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
#include <limits>

#define COMMANDS_BUFFER_SIZE 256
#define MESSAGE_BUFFER_SIZE 1024


/*
 * O enum Commands e o map mapCommand são criado para fácil
 * identificação dos comandos a serem digitados pelo usuário
 */
enum Commands
{
    HELP,
    EXIT,
    LOOGING_HOUR,
    MY_IP,
    SERVER_HOUR,
    SERVER_MEMORY,
    SERVER_HD,
    SERVER_TIME,
    SERVER_IP,
    SERVER_PORT,
    SERVER_PRO,
    SERVER_OPEN_PORTS
};

std::map<std::string, Commands> mapCommand = {
    {"/help", Commands::HELP},
    {"/exit", Commands::EXIT},
    {"/loggin_hour", Commands::LOOGING_HOUR},
    //{"/server_ip",     Commands::SERVER_IP},
    {"/my_ip", Commands::MY_IP},
    {"/server_hour", Commands::SERVER_HOUR},
    {"/server_memory", Commands::SERVER_MEMORY},
    {"/server_hd", Commands::SERVER_HD},
    {"/server_time", Commands::SERVER_TIME},
    {"/server_pro", Commands::SERVER_PRO},
    {"/server_open_ports", Commands::SERVER_OPEN_PORTS}
};

/*
 * mostra na tela os comandos disponíveis
 */
void printHelp()
{
    std::cout << "Available commands: " << std::endl;
    std::cout << "/help,\tFor help." << std::endl;
    std::cout << "/exit,\tTo exit." << std::endl;
    std::cout << "/loggin_hour,\tFor this client login hour." << std::endl;
    std::cout << "/server_ip,\tFor server Ip.     " << std::endl;
    std::cout << "/my_ip,\tFor this client Ip.        " << std::endl;
    std::cout << "/server_hour,\tFor server actual hour." << std::endl;
    std::cout << "/server_memory\tFor server available memory.  " << std::endl;
    std::cout << "/server_hd,\tFor server disck partitions." << std::endl;
    std::cout << "/server_pro,\tFor server process info." << std::endl;
    std::cout << "/server_open_ports,\tFor server available ports." << std::endl;
}

/*
 *
 */
int main(int argc, char** argv)
{

    /*
     *Variavel para realizar interrupção do programa 
     *caso haja erro ou termino da conexao
     */
    bool finaliza = false;

    //atribuindo valores padrao para ip e porta do servidor
    char* ip = "127.0.0.1";
    int port = 6969;

    /*
     * declarando buffers
     * 
     * bufferCommand ( Buffer que envia os comandos. Pequeno com 256bytes )
     * 
     * bufferMessage ( Buffer que envia recebe as mensagens. Maior com 1024bytes )
     * 
     */
    char bufferCommand[COMMANDS_BUFFER_SIZE];
    char bufferMessage[MESSAGE_BUFFER_SIZE];

    /*
     * Recuperando ip de conexão dos args 
     * 
     * Caso nçao receba nenhum argumento
     * será usado valores padrões
     * 
     */
    if ( argc > 1 )
    {
        ip = argv[1];
        port = atoi(argv[2]);
    }

    
    /*
     *Declarando descritor de arquivo do cliente
     * e suas variaveis de endereço
     */
    int thisClient;
    struct sockaddr_in socketAddres;
    int server;

    socketAddres.sin_family = AF_INET;
    socketAddres.sin_port = htons(port);
    socketAddres.sin_addr.s_addr = inet_addr(ip);

    /*
     * criando socket e verificando erro
     */
    thisClient = socket(AF_INET, SOCK_STREAM, 0); //IPPROTO_TCP);
    if ( thisClient < 0 )
    {
        perror("Socket");
        finaliza = true;
    }

    if ( !finaliza )
    {
        std::cout << "Connecting to: " << ip << " port: " << port << std::endl;

        /*
        * Realizando conexão com servidor e verificando erro
        */
        server = connect(thisClient, ( struct sockaddr * ) &socketAddres, sizeof (socketAddres));
        if ( server < 0 )
        {
            perror("connect");
            finaliza = true;
        }
        
        if ( !finaliza )
        {
            std::cout << "Connected!" << std::endl;

            /*
             *Recebendo mensagem de confirmação
             *Assim q conectado servidor manda mensagem da data/hora de conexão
             */
            if ( recv(thisClient, bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
            {
                perror("recv");
            }
            std::cout << bufferMessage << std::endl;
            std::cout << std::endl << "Type /help to show available commands" << std::endl;
            bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

            /*
             *Declarando variável que armazenará comandos do teclado
             **/
            std::string com;
            do
            {
                
                /*
                 *Digitar comando
                 */
                std::cin>>com;

                
                /*
                 * O programa só enviará ao servidor commandos listados
                 * no procedimento printHelp().
                 * Os comandos tem obrigatoriamente o caractere '/' no inicio
                 * O codigo a seguir verifica o comando digitado e mostra dicas
                 * caso não seja um comando válido
                 */
                if ( com[0] != '/' )
                {
                    std::cout << "Not a valid command: " << com << std::endl;
                    std::cout << "Type \"/help\" to show commands. " << std::endl;
                    continue;
                } else if ( mapCommand.find(com) == mapCommand.end() )
                {
                    std::cout << "Not a valid command: " << com << std::endl;
                    std::cout << "Type \"/help\" to show commands. " << std::endl;
                    continue;
                } else if ( com.compare("/exit") == 0 )
                {
                    std::cout << "Exit command" << std::endl;
                    finaliza = true;
                } else if ( com.compare("/help") == 0 )
                {
                    printHelp();
                } else
                {
                    /*
                     *Comando válido é copiado para buffer de comando
                     */
                    strcpy(bufferCommand, com.c_str());

                    std::cout << "sending: " << bufferCommand << std::endl;

                    /*
                     * Comando é enviado para servidor
                     */
                    if ( send(thisClient, bufferCommand, COMMANDS_BUFFER_SIZE,0) < 0 )
                    {
                        perror("write");
                        finaliza = false;
                    }
                    /*
                     * Escreve zeros no buffer(previne erros)
                     */
                    bzero(bufferCommand, COMMANDS_BUFFER_SIZE);

                    /*
                     * Recebe mensgem do servidor e printa na tela
                     */
                    if ( recv(thisClient, bufferMessage, MESSAGE_BUFFER_SIZE, 0) < 0 )
                    {
                        perror("recv");
                        finaliza = false;
                    }
                    /*
                     * Escreve zeros no buffer(previne erros)
                     */
                    std::cout << "Response:"<< std::endl << bufferMessage;
                    bzero(bufferMessage, MESSAGE_BUFFER_SIZE);

                }
                
                std::cout << std::endl;
                
                /*
                 *Repete até ocorrer erro ou desconexão
                 */
            } while ( !finaliza );
        }
    }

    /*
     * Fecha descritores do arquivo socket
     * Encerra conexão
     */
    close(thisClient);
    close(server);

    std::cout << std::endl << "Good Bye" << std::endl;

    return 0;
}

