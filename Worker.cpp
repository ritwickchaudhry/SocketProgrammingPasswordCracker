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
	if(argc < 3)
	{
		cout<<"Use the correct usage:./worker <server ip/host-name> <server-port>"<<endl;
		return 0;
	}

	struct sockaddr_in server;
	struct sockaddr_in worker_address;

	int port_no = atoi(argv[2]);
	string server_name = argv[1];

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

	server.sin_family = AF_INET;
	server.sin_port = htons(port_no);
	server.sin_addr = *((struct in_addr*)server_host->h_addr);
	memset(&(server.sin_zero),'\0',8);

	worker_address.sin_family = AF_INET;
	worker_address.sin_port = htons(port_no);
	worker_address.sin_addr.s_addr = INADDR_ANY;
	memset(&(worker_address.sin_zero),'\0',8);

	int connect_error = connect(socket_fd,(sockaddr*)&server,sizeof(sockaddr));
	if(connect_error == -1)
	{
		cout<< "Connection Failed"<<endl;
		return 8;
	}

	int send_error = send(socket_fd,"hello",2,0);
	if(send_error == -1)
	{
		cout<<"Error in Sending"<<endl;
		return 8;
	}


	close(socket_fd);
	return 0;

}
