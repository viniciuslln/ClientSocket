/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Commands.hpp
 * Author: vinih
 *
 * Created on 23 de Maio de 2016, 15:40
 */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define COMMANDS_BUFFER_SIZE 256
#define MESSAGE_BUFFER_SIZE 1024

    enum Commands {
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
    
    


#ifdef __cplusplus
}
#endif

#endif /* COMMANDS_HPP */

