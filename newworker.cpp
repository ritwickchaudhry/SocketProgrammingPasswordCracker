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
#include<pthread.h>

using namespace std;
int socket_fd;
string check = "Who are you?";
bool aborted=false;

vector<char> symbols_111;
vector<char> symbols_100;
vector<char> symbols_010;
vector<char> symbols_001;
vector<char> symbols_101;
vector<char> symbols_011;
vector<char> symbols_110;

string id;
int num,u_let,l_let;
string temp_hash;
string response;
char buffer[1024];
int send_error;
int number_of_chars;

bool flag=0;
string final;

void printvec(vector<char> v)
{
	for (int i = 0; i < v.size(); ++i)
	{
		cout<<v[i];
	}
	cout<<endl;
	return;
}

void print(char* str, int length)
{
	for(int i=0;i<length;i++)cout<<str[i];
	cout<<endl;
}

bool check_hash(char* str, int length)
{
	// cout<<str<<endl;
	if(string(crypt(str,"aa")) == temp_hash)return true;
	return false;
}

void Generate(char* test_string, int i, int length, int first, int second)
{
	if(!flag || !aborted)
	{
		if(i == length)
		{
			if(check_hash(test_string,length)) 
			{
				// print(test_string,length);
				// exit(EXIT_SUCCESS);
				flag = 1;
				final = "T ";
				final = final + id + " ";
				for(int j=0;j<length;j++)
				{
					final = final + test_string[j];
				}
				// cout<<final;
			}
			// for(int j=0;j<length;j++)
			// {
			// 	cout<<test_string[j];
			// }
			// cout<<endl;
			return; 
		}
		else
		{
				if(num == 1)
				{
					if(u_let == 1)
					{
						if(l_let == 1)
						{
							//num = 1 u_let = 1 l_let=1
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_111[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_111.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_111[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
						}
						else
						{
							//num = 1 u_let = 1 l_let=0
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_110[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_110.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_110[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
						}
					}
					else
					{
						if(l_let == 1)
						{
							// cout<<"YOOO"<<endl;
							//num = 1 u_let = 0 l_let=1
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_101[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_101.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_101[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
						}
						else
						{
							//num = 1 u_let = 0 l_let=0
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_100[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_100.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_100[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
						}				
					}
				}
				else
				{
					if(u_let == 1)
					{
						if(l_let == 1)
						{
							//num = 0 u_let = 1 l_let=1
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_011[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_011.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_011[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
						}
						else
						{
							//num = 0 u_let = 1 l_let=0	
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_010[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_010.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_010[j];
									Generate(test_string,i+1,length,first,second);
								}
							}				
						}
					}
					else
					{
						if(l_let == 1)
						{
							//num = 0 u_let = 0 l_let=1	
							if(i==0)
							{
								for(int j=first; j<=second;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_001[j];
									Generate(test_string,i+1,length,first,second);
								}
							}
							else
							{
								for(int j=0; j<symbols_001.size();j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols_001[j];
									Generate(test_string,i+1,length,first,second);
								}
							}				
						}
					}			
				}
		}
	}
	else return;
}

void decrypt(string hash, string length, string type, string first, string second)
{
	final = "";
	temp_hash = hash;
	symbols_111.resize(62);
	symbols_100.resize(10);
	symbols_010.resize(26);
	symbols_001.resize(26);
	symbols_101.resize(36);
	symbols_011.resize(52);
	symbols_110.resize(36);
	//Add Numbers to the symbols set
	for (int i = 0; i < 10; ++i)
	{
		symbols_111[i]='0' + i;
		symbols_100[i]='0' + i;
		symbols_101[i]='0' + i;
		symbols_110[i]='0' + i;
	}
	//Add Uppercase letters to the symbols set
	for (int i = 0; i < 26; ++i)
	{
		symbols_111[i+10] = 'A' + i;
		symbols_010[i] = 'A' + i;
		symbols_011[i] = 'A' + i;
		symbols_110[i+10] = 'A' + i;
	}
	//Add Lowercase letters to the symbols set
	for (int i = 0; i < 26; i++)
	{
		symbols_111[i+36] = 'a' + i;
		symbols_001[i] = 'a' + i;
		symbols_011[i+26] = 'a' + i;
		symbols_101[i+10] = 'a' + i;
	}

	char length_str[length.size() + 1];
	strcpy(length_str,length.data());
	int len = atoi(length_str);
	
	char temp_num_str[type.size()+1];
	strcpy(temp_num_str,type.data());
	int temp_num = atoi(temp_num_str);	

	l_let = temp_num/100;
	u_let = temp_num/10 - (l_let*10);
	num = temp_num%10;

	char first_str[first.size()+1];
	strcpy(first_str,first.data());

	char second_str[second.size()+1];
	strcpy(second_str,second.data());

	int start = atoi(first_str);
	int end = atoi(second_str);

	
	char test_string[len];
	// test_string.resize(0,len);
	// cout<<"Generate"<<endl;
	Generate(test_string,0,len,start,end);

	// return string("YO_Sexy");
	if(!flag) final = "F ";
	return;
}

void *func(void *)
{
	response = string(buffer);
    //cout<<"RESPONSE is ----- "<<response<<endl;
    string hash;
    string length;
    string type;
    string start;
   	string end;
    int i=0;
   	for(;i<response.size();i++)
   	{
   		if (response[i]==' ')
   		{
   			hash=response.substr(0,i);
   			break;
   		}
   	}
   	//cout<<"Hash is "<<hash<<" "<<hash.size()<<endl;
   	int j=i+1;
   	for(;j<response.size();j++)
   	{
   		if (response[j]==' ')
   		{
   			length=response.substr(i+1,j-i-1);
   			break;
   		}
   	}
   	//cout<<"Length is "<<length<<" "<<length.size()<<endl;
   	int k = j;
	j=j+1;
   	for(;j<response.size();j++)
   	{
   		if (response[j]==' ')
   		{
   			type=response.substr(k+1,3);
   			break;
   		}
   	}
   	//cout<<"Type is "<<type<<" "<<type.size()<<endl;
   	k=j;
   	j=j+1;
   	//cout<<"hi"<<endl;
   	///cout<<j<<endl;
   	//cout<<"ABC "<<response[k+1]<<endl;
   	for(;j<response.size();j++) 
   	{	
   		//cout<<j<<" "<<response[j]<<endl;
   		if (response[j]==' ')
   		{
   			start=response.substr(k+1,j-k-1);
   			break;
   		}
   	}
   	k=j;
   	j=j+1;
   	//cout<<"hi"<<endl;
   	///cout<<j<<endl;
   	//cout<<"ABC "<<response[k+1]<<endl;
   	for(;j<response.size();j++) 
   	{	
   		//cout<<j<<" "<<response[j]<<endl;
   		if (response[j]==' ')
   		{
   			end=response.substr(k+1,j-k-1);
   			break;
   		}
   	}
   	//cout<<"Start is "<<start<<" "<<start.size()<<endl;
   	k=j;
   	j=j+1;
   	for(;j<response.size();j++)
   	{
   			id=response.substr(k+1,j-k);

   	}
   	//cout<<start<<" "<<end<<"a a a"<<id<<"a"<<endl;	   	   	
   	//cout<<"End is "<<end<<" "<<end.size()<<endl;
   	//cout<<"Entering DECRYPT"<<endl;

   	decrypt(hash,length,type,start,end);
   	//cout<<"Broken password is "<<final<<endl;
   	char final_str[final.size()+1];
   	memset(final_str,'\0',final.size()+1);
   	strcpy(final_str,final.c_str());
   	int send_error = send(socket_fd, final_str, final.size(),0);
	//cout<<"Socket at worker is "<<socket_fd<<endl;
	if(send_error == -1)
	{
		cout<<"Error in Sending 1"<<endl;
	}
	//else cout<<"abcdefghijklom"<<endl;
}

//#######################################################################################


int main(int argc, char *argv[])
{
	aborted=false;
	if(argc < 3)
	{
		cout<<"Use the correct usage:./worker <server ip/host-name> <server-port>"<<endl;
		return 0;
	}

	struct sockaddr_in server;
	struct sockaddr_in worker_address;

	int port_no = atoi(argv[2]);
	string server_name = argv[1];

	socket_fd = socket(AF_INET,SOCK_STREAM,0);
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
	
	memset(buffer,0,1024);
	cout<<"BOLA"<<endl;
	//-------------------Server asks identity----------------
	send_error = send(socket_fd,"Worker",6,0);
	if(send_error == -1)
	{
		cout<<"Error in Sending Identity"<<endl;
		return 8;
	}
	cout<<"HOLA"<<endl;

	//######################################################
	int x=0;
	string aborteduser;
	while(true)
	{
		number_of_chars = recv(socket_fd,buffer,1024,0);
	    if(number_of_chars < 0)
	    {
	   		cout<<"Error in Receiving password to be decrypted from Server"<<endl;

	    }
	    buffer[number_of_chars] = '\0';
	    string buffer_str=buffer;
	    int i=0;
	    cout<<"HAHAHAH"<<endl;
	    cout<<buffer_str<<endl;
	    for(;i<number_of_chars;i++)
	    {
	    	if(buffer_str[i]==' ')
	    	{	
	    		aborteduser=buffer_str.substr(i+1,buffer_str.size()-i);		
	    		break;
	    	}
	    }
	    buffer_str=buffer_str.substr(0,i);	    
	    cout<<buffer_str<<endl;
	    cout<<"id "<<id<<endl;
	    cout<<"aborted user "<<aborteduser<<endl;
	    if(buffer_str=="complete")
	    {
	    	cout<<"AAA"<<endl;
	    	if(aborteduser==id)
	    	{
	    		aborted=true;
	    		cout<<"ABORTED"<<endl;	
	    		//send_error = send(socket_fd,"----",4,0);
				//if(send_error == -1)
				//{
				//	cout<<"Error"<<endl;
				//}
	    	}
	    	
	    }
	    else
	    {
	    	pthread_t my_thread;
	    	//cout<<"BBB"<<endl;
	    	int a= pthread_create(&my_thread, NULL, &func, NULL);
	    	if(a != 0) {
                        cout<<"Error in creating pthread"<<endl;
                        return 0;
            }
            pthread_detach(my_thread);
	    }

	}

	close(socket_fd);
	return 0;

}
