# ClientSocket
Trabalho de Redes1, um cliente que recebe informações do servidor na rede

Cliente para servidor https://github.com/viniciuslln/ServerSocket/tree/thread_for_each_client.
O programa se conecta ao servidor e recebe comandos do usuário aos quais serão envidados e processados no servidor. O servidor retornará mensagens correspondentes aos comandos recebidos.

Compilando: g++ -std=c++11 main.cpp -o nome_do_executavel

Executando: 
./nome_do_executavel 
Executará conectando ao servidor no ip 127.0.0.0 e porta 6969
ou 
caso deseje informar a ip e porta a ser usada
./nome_do_executavel xxx.xxx.xxx.xxx xxxx
xxx.xxx.xxx.xxx{ipv4} xxxx{porta}
