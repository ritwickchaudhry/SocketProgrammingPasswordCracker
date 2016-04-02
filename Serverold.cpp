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
	string length;
	string type;
	user_struct(){}
	user_struct(int a, string b, string c, string d)
	{
		sock_fd = a;
		hash = b;
		length = c;
		type = d;
	}
};

vector<user_struct> busyusers;
vector<int> busyworkers;

vector<user_struct> outstanding_users;
vector<int> freeworkers;

string encoded="";
string space=" ";
string  check = "Who are you?";
string  ask_hash = "Send Hash to Crack";
string  ask_pwd_length = "Send Password Length";
string  ask_pwd_type = "Send Password Type";

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
    
     //#################################################################
    while(true)
    { 
	   	listen(socket_fd,size_struct);
	    int new_socket_fd = accept(socket_fd, (struct sockaddr *) &client, &size_struct);
	    
	    if(new_socket_fd  < 0)
	     {
	     	cout<<"Error in Connection with client"<<endl;
	     	return 8;
	     }

		char check_str[check.size()+1];
		strcpy(check_str,check.c_str());
	
	    int send_error = send(new_socket_fd,check_str,check.size(),0);
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
			char ask_hash_str[ask_hash.size()+1];
			strcpy(ask_hash_str,ask_hash.c_str());

			send_error = send(new_socket_fd,ask_hash_str,ask_hash.size(),0);
			
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
			
		    char ask_pwd_length_str[ask_pwd_length.size()+1];
		    strcpy(ask_pwd_length_str,ask_pwd_length.c_str());

			send_error = send(new_socket_fd,ask_pwd_length_str,ask_pwd_length.size(),0);
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
		    temp.length = string(buffer);

	    	//#######################################################
	    	//--------------ASK FOR PASSWORD TYPE--------------------
	    	//#######################################################
			char ask_pwd_type_str[ask_pwd_type.size()+1];
			strcpy(ask_pwd_type_str,ask_pwd_type.c_str());
			
			send_error = send(new_socket_fd,ask_pwd_type_str,ask_pwd_type.size(),0);
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

			//cout<<"bdvkqdhbfvqdkvbqdvkbqdvkqdhvbqd"<<endl;
			//no worker is free
			if(freeworkers.size()<1)
			{	
				cout<<"hahaha"<<endl;
				outstanding_users.push_back(temp);
			}
			else
			{	
				//cout<<"bababa"<<endl;
				busyusers.push_back(temp);
				//now send a free worker the pasword to be decoded

				encoded=temp.hash + space + temp.length + space + temp.type;

				cout<<"Encoded is "<<encoded<<endl;

				int number_of_free_workers = freeworkers.size();
				{	
					cout<<"Number of free workers is "<<number_of_free_workers<<endl;
					if(number_of_free_workers == 1)
					{
						cout<<"dadadada"<<endl;
						encoded = encoded + space + "11";
						char encoded_str[encoded.size()+1];
						strcpy(encoded_str,encoded.c_str());
						send_error = send(freeworkers[0],encoded_str,encoded.size(),0);
						cout<<"bababa"<<endl;
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker"<<endl;
							return 8;
						}
						freeworkers.clear();
					}
					if(number_of_free_workers == 2)
					{
						//Send To Worker 1
						string encoded1 = encoded + space + "21";
						char encoded1_str[encoded1.size()+1];
						strcpy(encoded1_str,encoded1.c_str());						
						send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker 1"<<endl;
							return 8;
						}
						//Send To Worker 2
						string encoded2 = encoded + space + "22";
						char encoded2_str[encoded2.size()+1];
						strcpy(encoded2_str,encoded2.c_str());						
						send_error = send(freeworkers[1],encoded2_str,encoded2.size(),0);
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker 2"<<endl;
							return 8;
						}
						freeworkers.clear();
					}
					if(number_of_free_workers == 3)
					{
						//Send To Worker 1
						string encoded1 = encoded + space + "31";
						char encoded1_str[encoded1.size()+1];
						strcpy(encoded1_str,encoded1.c_str());						
						send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker 1"<<endl;
							return 8;
						}
						//Send To Worker 2
						string encoded2 = encoded + space + "32";
						char encoded2_str[encoded2.size()+1];
						strcpy(encoded2_str,encoded2.c_str());						
						send_error = send(freeworkers[1],encoded2_str,encoded2.size(),0);
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker 2"<<endl;
							return 8;
						}	
						//Send To Worker 3
						string encoded3 = encoded + space + "33";
						char encoded3_str[encoded3.size()+1];
						strcpy(encoded3_str,encoded3.c_str());						
						send_error = send(freeworkers[2],encoded3_str,encoded3.size(),0);
						if(send_error == -1)
						{
							cout<<"Error in Sending password to be broken to the worker 3"<<endl;
							return 8;
						}	
						freeworkers.clear();
					}

				}

			}

    		cout<<"CHECK"<<endl;
	    	
	    }
	    
	    if(response == "Worker" || response == "worker")
	    {
	    	cout<<response<<endl;
	    	cout<<new_socket_fd<<endl;
	    	if(!outstanding_users.empty())
	    	{
				encoded=outstanding_users[0].hash + space + outstanding_users[0].length + space + outstanding_users[0].type + "11";
				char encoded_str[encoded.size()+1];
				strcpy(encoded_str,encoded.c_str());
				send_error = send(new_socket_fd,encoded_str,encoded.size(),0);
				if(send_error == -1)
				{
					cout<<"Error in Sending password to be broken to the worker"<<endl;
					return 8;
				}
				outstanding_users.erase(outstanding_users.begin());
	    	}
	    	else
	    	{
		    	freeworkers.push_back(new_socket_fd);
	    	}
	    }
	 
    }

    close(socket_fd);
	return 0;

}	
