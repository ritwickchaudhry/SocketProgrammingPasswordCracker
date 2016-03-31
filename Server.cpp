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
#include<vector>
#include<string>

using namespace std;

struct user_struct
{
	int sock_fd;
	string hash;
	int length;
	string type;
	user_struct(){}
	user_struct(int a, string b, int c, string d)
	{
		sock_fd = a;
		hash = b;
		length = c;
		type = d;
	}
};

vector<user_struct> users;
vector<int> workers;

#define  check  "Who are you?"
#define  ask_hash  "Send Hash to Crack"
#define  ask_pwd_length  "Send Password Length"
#define  ask_pwd_type  "Send Password Type"

int main(int argc, char *argv[])
{
	struct sockaddr_in server;

	if(argc < 2)
	{
		cout<<"Use the correct usage:./Server <server-port>"<<endl;
		return 0;
	}
	int port_no = atoi(argv[1]);
	
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
	memset(&(server.sin_zero),'\0',8);

	
	struct sockaddr_in client;
    int bind_error = bind(socket_fd, (struct sockaddr *) &server, sizeof(server));			
	if(bind_error == -1)
	{
		cout<<"ERROR on binding"<<endl;
		return 8;

	}
     socklen_t size_struct;
     size_struct=sizeof(struct sockaddr_in);
    
   



    while(true)
    { 
	   	listen(socket_fd,size_struct);
	    int new_socket_fd = accept(socket_fd, (struct sockaddr *) &client, &size_struct);
	    
	    if(new_socket_fd  < 0)
	     {
	     	cout<<"Error in Connection with client"<<endl;
	     	return 8;
	     }
	    
	    int send_error = send(new_socket_fd,check,11,0);
		if(send_error == -1)
		{
			cout<<"Error in Sending"<<endl;
			return 8;
		}

	    char buffer[1024];
	    int number_of_chars = recv(new_socket_fd,buffer,1024,0);
	    if(number_of_chars < 0)
	    {
	   		cout<<"Error in Receiving Message from client"<<endl;
	     	return 8;
	    }
	    buffer[number_of_chars] = '\0';
	    string response = string(buffer);

	    if(response == "User" || response == "user")
	    {
	    	user_struct temp;
	    	temp.sock_fd = new_socket_fd;

	    	int send_error;
		    
		    char buffer[1024];
		    int number_of_chars;
			string response;

	    	//#######################################################
	    	//-------------------ASK FOR HASH------------------------
	    	//#######################################################
			send_error = send(new_socket_fd,ask_hash,11,0);
			if(send_error == -1)
			{
				cout<<"Error in Sending Ask Hash"<<endl;
				return 8;
			}

			memset(buffer,0,1024);

		    number_of_chars = recv(new_socket_fd,buffer,1024,0);
		    //Check for errors
		    if(number_of_chars < 0)
		    {
		   		cout<<"Error in Receiving Hash from User"<<endl;
		     	return 8;
		    }

		    buffer[number_of_chars] = '\0';
		    response = string(buffer);
		    temp.hash = response;

	    	//#######################################################
	    	//--------------ASK FOR PASSWORD LENGTH------------------
	    	//#######################################################
			send_error = send(new_socket_fd,ask_pwd_length,11,0);
			if(send_error == -1)
			{
				cout<<"Error in Sending Ask Password Length"<<endl;
				return 8;
			}

			memset(buffer,0,1024);

		    number_of_chars = recv(new_socket_fd,buffer,1024,0);
		    //Check for errors
		    if(number_of_chars < 0)
		    {
		   		cout<<"Error in Receiving Password Length from User"<<endl;
		     	return 8;
		    }

		    buffer[number_of_chars] = '\0';
		    temp.length = atoi(buffer);

	    	//#######################################################
	    	//--------------ASK FOR PASSWORD TYPE--------------------
	    	//#######################################################
			send_error = send(new_socket_fd,ask_pwd_type,11,0);
			if(send_error == -1)
			{
				cout<<"Error in Sending Ask Password Type"<<endl;
				return 8;
			}

			memset(buffer,0,1024);

		    number_of_chars = recv(new_socket_fd,buffer,1024,0);
		    //Check for errors
		    if(number_of_chars < 0)
		    {
		   		cout<<"Error in Receiving Password Type from User"<<endl;
		     	return 8;
		    }

		    buffer[number_of_chars] = '\0';
		    response = string(buffer);
		    temp.type = response;


	    	//#######################################################
	    	//-----------------PASSWORD OBTAINED---------------------
	    	//#######################################################
		    send_error = send(new_socket_fd,"Cracking Password",11,0);
			if(send_error == -1)
			{
				cout<<"Error in Sending Confirmation"<<endl;
				return 8;
			}
    		users.push_back(temp);	    
    		cout<<temp.hash<<endl;
    		cout<<temp.length<<endl;
    		cout<<temp.type<<endl;
    		cout<<"CHECK"<<endl;
	    }
	    
	    if(response == "Worker" || response == "worker")
	    {
	    	
	    	workers.push_back(new_socket_fd);
	    }
	 
    }

    close(socket_fd);
	return 0;

}	
