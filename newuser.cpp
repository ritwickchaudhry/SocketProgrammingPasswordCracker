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
#include<string>

using namespace std;

string user="User";
string check = "Who are you?";
string  ask_hash = "Send Hash to Crack";
string  ask_pwd_length =  "Send Password Length";
string  ask_pwd_type  = "Send Password Type";
string space=" ";

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

	string password_length1 = argv[4];
	string hash1 = argv[3];
	string password_type1 = argv[5];
	//char password_length[password_length1.size()+1];
	//char hash[hash1.size()+1];
	//char password_type[password_type1.size()+1];
	//strcpy(password_length, password_length1.c_str());
	//strcpy(password_type,password_type1.c_str());
	//strcpy(hash,hash1.c_str());

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
	memset(&(server.sin_zero),'\0',8);
	//Populate My Struct Info
	my_address.sin_family = AF_INET;
	my_address.sin_port = htons(port_no);
	my_address.sin_addr.s_addr = INADDR_ANY;
	memset(&(my_address.sin_zero),'\0',8);
	//Setup Connection
	int connect_error = connect(socket_fd,(sockaddr*)&server,sizeof(sockaddr));
	if(connect_error == -1)
	{
		cout<< "Connection Failed"<<endl;
		return 8;
	}
	char buffer[1024];
	int send_error;
	string message;
	message=user + space + hash1 + space +password_length1 +space + password_type1; 
	char message_str[message.size()+1];
	strcpy(message_str, message.c_str());
	send_error = send(socket_fd,message_str,message.size(),0);
	if(send_error == -1)
	{
		cout<<"Error in Sending Identity"<<endl;
		return 8;
	}

	int number_of_chars = recv(socket_fd,buffer,1024,0);
    if(number_of_chars < 0)
    {
   		cout<<"Error in receiving HALO from server"<<endl;
     	return 8;
    }
    buffer[number_of_chars] = '\0';
    string response = string(buffer);
    cout<<"response is "<<response<<endl;

	close(socket_fd);
	return 0;

}	
