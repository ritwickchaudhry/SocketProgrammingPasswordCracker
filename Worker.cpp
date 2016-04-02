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

string check = "Who are you?";

//#######################################################################################
//--------------------------------DECRYPT FUNCTIONS--------------------------------------
//#######################################################################################


vector<char> symbols;
int num,u_let,l_let;
string temp_hash;

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

void Generate(char* test_string, int i, int length, int number_of_workers, int index_worker)
{
	if(i == length)
	{
		if(check_hash(test_string,length)) 
		{
			print(test_string,length);
			exit(EXIT_SUCCESS);
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
		if(i != 0)
		{
			if(num == 1)
			{
				if(u_let == 1)
				{
					if(l_let == 1)
					{
						//num = 1 u_let = 1 l_let=1
						for(int j=0; j<62;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}		
					}
					else
					{
						//num = 1 u_let = 1 l_let=0
						for(int j=0; j<35;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}		
					}
				}
				else
				{
					if(l_let == 1)
					{
						// cout<<"YOOO"<<endl;
						//num = 1 u_let = 0 l_let=1
						for(int j=0; (j<10) ;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							// cout<<symbols[j];					
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}
						for (int j = 36; j <62 ; j++)
						{
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}	

					}
					else
					{
						//num = 1 u_let = 0 l_let=0
						for(int j=0; j<10;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
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
						for(int j=10 ; j<62;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}		
					
					}
					else
					{
						//num = 0 u_let = 1 l_let=0
						for(int j=10; j<36;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}		
					
					}
				}
				else
				{
					if(l_let == 1)
					{
						//num = 0 u_let = 0 l_let=1
						for(int j=36; j<62;j++)
						{
							// cout<<"yo"<<" "<<i<<" "<<length<<endl;
							test_string[i] = symbols[j];
							Generate(test_string,i+1,length,number_of_workers,index_worker);
						}		
					
					}
				}			
			}
		}

		//####################################################################################
		//------------------------------POPULATE FIRST LETTER---------------------------------
		//####################################################################################
		else
		{
			if(num == 1)
			{
				if(u_let == 1)
				{
					if(l_let == 1)
					{
						//num = 1 u_let = 1 l_let=1
						if(number_of_workers == 1)
						{
							for(int j=0; j<62;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=0; j<30;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}								
							}
							else
							{
								for(int j=30; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=0; j<20;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}								
							}
							else if(index_worker == 2)
							{
								for(int j=20; j<40;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=40; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
							}
						}	
					}
					else
					{
						//num = 1 u_let = 1 l_let=0
						
						if(number_of_workers == 1)
						{
							for(int j=0; j<35;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=0; j<17;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}								
							}
							else
							{
								for(int j=17; j<35;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=0; j<12;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}								
							}
							else if(index_worker == 2)
							{
								for(int j=12; j<24;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=24; j<35;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
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

						if(number_of_workers == 1)
						{
							for(int j=0; (j<10) ;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								// cout<<symbols[j];					
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}
							for (int j = 36; j <62 ; j++)
							{
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}	
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=0; j<10;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}								
								for(int j=36; j<44;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}							
							}
							else
							{
								for(int j=44; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=0; j<10;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}
								for(int j=36; j<38;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}																
							}
							else if(index_worker == 2)
							{
								for(int j=38; j<50;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=50; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
							}
						}	
					}
					else
					{
						//num = 1 u_let = 0 l_let=0
						if(number_of_workers == 1)
						{
							for(int j=0; (j<10) ;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								// cout<<symbols[j];					
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}	
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=0; j<5;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}														
							}
							else
							{
								for(int j=5; j<10;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=0; j<3;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}												
							}
							else if(index_worker == 2)
							{
								for(int j=3; j<6;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=6; j<10;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
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
						if(number_of_workers == 1)
						{
							for(int j=10; (j<62) ;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								// cout<<symbols[j];					
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}	
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=10; j<36;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}														
							}
							else
							{
								for(int j=36; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=10; j<27;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}												
							}
							else if(index_worker == 2)
							{
								for(int j=27; j<44;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=44; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
							}
						}				
					}
					else
					{
						//num = 0 u_let = 1 l_let=0
						if(number_of_workers == 1)
						{
							for(int j=10; (j<36) ;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								// cout<<symbols[j];					
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}	
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=10; j<23;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}														
							}
							else
							{
								for(int j=23; j<36;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=10; j<19;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}												
							}
							else if(index_worker == 2)
							{
								for(int j=19; j<28;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=28; j<36;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
							}
						}		
					}
				}
				else
				{
					if(l_let == 1)
					{
						//num = 0 u_let = 0 l_let=1
						
						if(number_of_workers == 1)
						{
							for(int j=36; (j<62) ;j++)
							{
								// cout<<"yo"<<" "<<i<<" "<<length<<endl;
								// cout<<symbols[j];					
								test_string[i] = symbols[j];
								Generate(test_string,i+1,length,number_of_workers,index_worker);
							}	
						}
						else if(number_of_workers == 2)
						{
							if(index_worker == 1)
							{
								for(int j=36; j<49;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}														
							}
							else
							{
								for(int j=49; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
						}
						else
						{
							if(index_worker == 1)
							{
								for(int j=36; j<45;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}												
							}
							else if(index_worker == 2)
							{
								for(int j=45; j<54;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}									
							}
							else
							{
								for(int j=54; j<62;j++)
								{
									// cout<<"yo"<<" "<<i<<" "<<length<<endl;
									test_string[i] = symbols[j];
									Generate(test_string,i+1,length,number_of_workers,index_worker);
								}	
							}
						}		
					}
				}			
			}
		}
	}
}

string decrypt(string hash, string length, string type, int number_of_workers, int index_worker)
{

	temp_hash = hash;
	symbols.resize(62);
	//Add Numbers to the symbols set
	for (int i = 0; i < 10; ++i)
	{
		symbols[i]='0' + i;
	}
	//Add Uppercase letters to the symbols set
	for (int i = 0; i < 26; ++i)
	{
		symbols[i+10] = 'A' + i;
	}
	//Add Lowercase letters to the symbols set
	for (int i = 0; i < 26; i++)
	{
		symbols[i+36]= 'a' + i;
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
	// cout<<"num "<<num<<"\n";
	// cout<<"u_let"<<u_let<<"\n";
	// cout<<"l_let"<<l_let<<"\n";
	// cout<<t1<<endl;
	// cout<<t2<<endl;
	// cout<<t3<<endl;
	// cout<<len<<endl;
	// cout<<len;
	char test_string[len];
	// test_string.resize(0,len);
	// cout<<"Generate"<<endl;
	Generate(test_string,0,len,number_of_workers,index_worker);
	
	
	return string("YO_Sexy");
}


//#######################################################################################


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
    	send_error = send(socket_fd,"Worker",6,0);
		if(send_error == -1)
		{
			cout<<"Error in Sending Identity"<<endl;
			return 8;
		}
	}

	while(true)
	{
		number_of_chars = recv(socket_fd,buffer,1024,0);
	    if(number_of_chars < 0)
	    {
	   		cout<<"Error in Receiving password to be decrypted from Server"<<endl;
	     	return 8;
	    }
	    buffer[number_of_chars] = '\0';
	    response = string(buffer);
	    cout<<"RESPONSE is :::"<<response<<endl;
	    string hash;
	    string length;
	    string type;
	    int i=0;
	   	for(;i<response.size();i++)
	   	{
	   		if (response[i]==' ')
	   		{
	   			hash=response.substr(0,i);
	   			break;
	   		}
	   	}
	   	int j=i+1;
	   	for(;j<response.size();j++)
	   	{
	   		if (response[j]==' ')
	   		{
	   			length=response.substr(i+1,j-i);
	   			break;
	   		}
	   	}
	   	int k = j;
		j=j+1;
	   	for(;j<response.size();j++)
	   	{
	   		if (response[j]==' ')
	   		{
	   			type=response.substr(k,j-i);
	   			break;
	   		}
	   	}	   	
		string encoded_traffic = response.substr(j+1);
	   	cout<<hash<<endl;
	   	cout<<length<<endl;
	   	cout<<type<<endl;
	   	cout<<encoded_traffic<<endl;

	   	char encoded_traffic_str[encoded_traffic.size() + 1];
	   	strcpy(encoded_traffic_str,encoded_traffic.c_str());
	   	int temp_number = atoi(encoded_traffic_str);
	   	int number_of_workers = temp_number/10;
	   	int index_worker = temp_number%10;

	   	decrypt(hash,length,type,number_of_workers,index_worker);
	}


	close(socket_fd);
	return 0;

}
