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

	if(argc < 6)
	{
		cout<<"Use the correct usage:./Client <server ip/host-name> <server-port> <hash> <passwd-length> <binary-string>"<<endl;
		return 0;
	}

	int port_no = atoi(argv[2]);
	string server_name = argv[1];

	int password_length = atoi(argv[4]);
	string hash = argv[3];
	string password_type = argv[5];

	int socket_fd = socket(AF_INET,SOCK_STREAM,0);
	if(socket_fd == -1)
	{
		cout<<"Socket not Opened : ERROR"<<endl;
		return 0;
	}

	struct hostent *server_host;
	server_host = gethostbyname(argv[1]);
	
	if(server_host == NULL)
	{
		cout<<"No Server found by this host name"<<endl;
		return 0;
	}

 
	//Populate Server Struct Info
	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);

	server.sin_addr = *((struct in_addr*)server_host->h_addr);
	// memcpy(&server.sin_addr, server_host->h_addr_list[0], server_host->h_length);
	memset(&(server.sin_zero),'\0',8);

	//Populate My Struct Info
	my_address.sin_family = AF_INET;
	my_address.sin_port = htons(port_no);
	my_address.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_address.sin_zero),'\0',8);


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

	//Setup Connection
	int connect_error = connect(socket_fd,(sockaddr*)&server,sizeof(sockaddr));

	if(connect_error == -1)
	{
		cout<< "Connection Failed"<<endl;
		return 8;
	}

	int send_error = send(socket_fd,"ab",2,0);
	
	if(send_error == -1)
	{
		cout<<"Error in Sending"<<endl;
		return 8;
	}

	close(socket_fd);
	return 0;

}	
