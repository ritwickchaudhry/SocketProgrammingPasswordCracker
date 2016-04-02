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

string check = "Who are you?";
string  ask_hash = "Send Hash to Crack";
string  ask_pwd_length =  "Send Password Length";
string  ask_pwd_type  = "Send Password Type";


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
	char password_length[password_length1.size()+1];
	char hash[hash1.size()+1];
	char password_type[password_type1.size()+1];
	strcpy(password_length, password_length1.c_str());
	strcpy(password_type,password_type1.c_str());
	strcpy(hash,hash1.c_str());

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
	int number_of_chars;
	memset(buffer,0,1024);
	string response;
	//#######################################################
	//-------------------Server asks identity----------------
	//#######################################################
	number_of_chars = recv(socket_fd,buffer,1024,0);
    if(number_of_chars < 0)
    {
   		cout<<"Error in Receiving question from server about identity"<<endl;
     	return 8;
    }
    buffer[number_of_chars] = '\0';
    response = string(buffer);
   	// cout<<check;
   	// cout<<number_of_chars;
   	// cout<<"Response from Server is "<<response<<endl;
    if (response == check)
    {	
    	//cout<<"Hi";
    	//Checked Till Here
    	send_error = send(socket_fd,"User",4,0);
		if(send_error == -1)
		{
			cout<<"Error in Sending Identity"<<endl;
			return 8;
		}
		memset(buffer,0,1024);
		number_of_chars = recv(socket_fd,buffer,1024,0);
	    if(number_of_chars < 0)
	    {
	   		cout<<"Error in Receiving question from server about hash"<<endl;
	     	return 8;
	    }
	    buffer[number_of_chars] = '\0';
	    response = string(buffer);
	    // cout<<response<<endl;
	    // cout<<ask_hash<<endl;
	    if (response == ask_hash)
	    {
	    	// cout<<"Hi1"<<endl;
	    	send_error = send(socket_fd,hash,hash1.size(),0);
			if(send_error == -1)
			{
				cout<<"Error in Sending Hash"<<endl;
				return 8;
			}
			memset(buffer,0,1024);
			number_of_chars = recv(socket_fd,buffer,1024,0);
		    if(number_of_chars < 0)
		    {
		   		cout<<"Error in Receiving question from server about length"<<endl;
		     	return 8;
		    }
		    buffer[number_of_chars] = '\0';
		    response = string(buffer);
		    if (response == ask_pwd_length)
		    {
		    	send_error = send(socket_fd,password_length,password_length1.size(),0);
				if(send_error == -1)
				{
					cout<<"Error in Sending Password length"<<endl;
					return 8;
				}
				memset(buffer,0,1024);
				number_of_chars = recv(socket_fd,buffer,1024,0);
			    if(number_of_chars < 0)
			    {
			   		cout<<"Error in Receiving question from server about type"<<endl;
			     	return 8;
			    }
			    buffer[number_of_chars] = '\0';
			    response = string(buffer);
			    if (response == ask_pwd_type)
			    {
			    	send_error = send(socket_fd,password_type,password_type1.size(),0);
					if(send_error == -1)
					{
						cout<<"Error in Sending Password type"<<endl;
						return 8;
					}
					else cout<<"EVERYTHING SENT SUCCESSFULLY"<<endl;
			    }
			    
		    }
	    }
    }


	close(socket_fd);
	return 0;

}	
