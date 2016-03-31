#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/types.h> 
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/un.h>

using namespace std;

int main(int argc, char *argv[])
{
	struct sockaddr_in server;
	struct sockaddr_in my_address;

	if(argc < 2)
	{
		cout<<"Use the correct usage:./Server <server-port>"<<endl;
		return 0;
	}

	int port_no = atoi(argv[1]);

	// int password_length = atoi(argv[4]);
	// string hash = argv[3];
	// string password_type = argv[5];

	int socket_fd = socket(AF_INET,SOCK_STREAM,0);

	if(socket_fd == -1)
	{
		cout<<"Socket not Opened : ERROR"<<endl;
		return 0;
	}

	//Populate Server Struct Info
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr.s_addr = INADDR_ANY;
	// memcpy(&server.sin_addr, server_host->h_addr_list[0], server_host->h_length);
	memset(&(server.sin_zero),'\0',8);

	// //Populate My Struct Info
	// my_address.sin_family = AF_INET;
	// my_address.sin_port = htons(port_no);
	// my_address.sin_addr.s_addr = INADDR_ANY;
	// memset(&(my_address.sin_zero),'\0',0);


	// struct in_addr** ip_list;
	// ip_list = (struct in_addr **)server_host->h_addr_list;
	// server.sin_addr.s_addr = *((unsigned long*)server->h_addr);
	


	// for (int i = 0; ip_list[i]!= NULL; i++)
	// {
	// 	cout<<inet_ntoa(*ip_list[i]);
	// }
	
	// int i=0;
	// while(ip_list[0][i] != '\0')
	// {
	// 	cout<<ip_list[0][i];
	// 	i++;
	// }

	struct sockaddr_in client;

     int bind_error = bind(socket_fd, (struct sockaddr *) &server, sizeof(server)) < 0) 			
	{
		cout<<"ERROR on binding"<<endl;
		return 8;
	}

     socklen_t size_struct;
     size_struct=sizeof(struct sockaddr_in);
    
    listen(socket_fd,);
    
    int client_socket_fd = accept(socket_fd, (struct sockaddr *) &client, &size_struct);

     if(client_socket_fd  < 0)
     {
     	cout<<"Error in Connection"<<endl;
     	return 8;
     }

	//Setup Connection
	// int connect_error = connect(socket_fd,(sockaddr*)&server,sizeof(sockaddr));
	// if(connect_error == -1)
	// {
	// 	cout<< "Connection Failed"<<endl;
	// 	return 8;
	// }
	// int send_error = send(socket_fd,"Yo Dude :*",10,0);
	// if(send_error == -1)
	// {
	// 	cout<<"Error in Sending"<<endl;
	// 	return 8;
	// }

     char buffer[1024];
     // cout<<"Yo"<<endl;

     int number_of_chars = recv(client_socket_fd,buffer,1024,0);
     
     if(number_of_chars < 0)
     {
     	cout<<"Error in Receiving Message"<<endl;
     	return 8;
     }

     // cout<<"Buffer is"<<buffer<<endl;
     buffer[number_of_chars] = '\0';

     cout<<buffer;

     // for (int i = 0; buffer[i]!='\0'; ++i)
     // {
     // 	cout<<buffer[i]<<" ";
     // }

     close(client_socket_fd);
     close(socket_fd);
	return 0;

}	
