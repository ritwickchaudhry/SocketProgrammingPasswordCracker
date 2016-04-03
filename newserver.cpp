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
#include<cstring>

using namespace std;

struct user_struct
{
    int sock_fd;
    string hash;
    string length;
    string type;
    user_struct() {}
    user_struct(int a, string b, string c, string d)
    {
        sock_fd = a;
        hash = b;
        length = c;
        type = d;
    }
};

int lengtharr(string a)
{
    if(a=="111") return 62;
    else if (a=="101" || a=="011") return 36;
    else if (a=="100" || a=="010") return 26;
    else if (a=="001") return 10;
    else if (a=="110") return 52;
    else return 0;
}
vector<user_struct> busyusers;
vector<int> busyworkers;

vector<user_struct> outstanding_users;
vector<int> freeworkers;

string encoded="";
string space=" ";

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout<<"Use the correct usage:./Server <server-port>"<<endl;
        return 0;
    }
    int port_no = atoi(argv[1]);
    fd_set master; // master file descriptor list
    fd_set read_fds; // temp file descriptor list for select()
    struct sockaddr_in myaddr; // server address
    struct sockaddr_in remoteaddr; // client address
    int fdmax; // maximum file descriptor number
    int listener; // listening socket descriptor
    int newfd; // newly accept()ed socket descriptor
    char buf[256]; // buffer for client data
    int nbytes;
    int yes=1; // for setsockopt() SO_REUSEADDR, below
    int addrlen;
    int i, j;
    FD_ZERO(&master); // clear the master and temp sets
    FD_ZERO(&read_fds);
    // get the listener
    if ((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // lose the pesky "address already in use" error message
    if (setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes,
                   sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    // bind
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = INADDR_ANY;
    myaddr.sin_port = htons(port_no);
    memset(&(myaddr.sin_zero), '\0', 8);
    if (bind(listener, (struct sockaddr *)&myaddr, sizeof(myaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // listen
    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(1);
    }
    // add the listener to the master set
    FD_SET(listener, &master);
    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it’s this one
    // main loop
    for(;;)
    {
        if (outstanding_users.size()!=0)
        {
        	cout<<"Outstanding users remaining"<<endl;
        	if (freeworkers.size()!=0)
        	{
        		//divide the work amongst workers
        		busyusers.push_back(outstanding_users[0]);
        		outstanding_users.erase(outstanding_users.begin(),outstanding_users.begin()+1);
        	}
        }

        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("select");
            exit(1);
        }
        // run through the existing connections looking for data to read
        for(i = 0; i <= fdmax; i++)
        {
            if (FD_ISSET(i, &read_fds))   // we got one!!
            {
                if (i == listener)
                {
                    // handle new connections
                    addrlen = sizeof(remoteaddr);
                    if ((newfd = accept(listener, (sockaddr*) &remoteaddr, (socklen_t*)&addrlen)) == -1)
                    {
                        perror("accept");
                    }
                    else
                    {   
                        
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax)   // keep track of the maximum
                        {
                            fdmax = newfd;
                        }
                        char buffer[1024];
                        int number_of_chars = recv(newfd,buffer,1024,0);
                        if(number_of_chars < 0)
                        {
                            cout<<"Error in Receiving Message from client"<<endl;
                            return 8;
                        }
                        buffer[number_of_chars] = '\0';
                        string response = string(buffer);
                        cout<<"Response "<<response<<endl;
                        string client;
                        string hash;
                        string length;
                        string type;                        
                        int i=0;
                        for(;i<response.size();i++)
                        {
                            if (response[i]==' ')
                            {
                                client=response.substr(0,i);
                                break;
                            }
                        }
                        cout<<i<<endl;
                   		if (i==response.size()) client = "Worker";
                        cout<<"Client is "<<client<<endl;
                        if (client=="User")
                        {
                            int j=i+1;
                            for(;j<response.size();j++)
                            {
                                if (response[j]==' ')
                                {
                                    hash=response.substr(i+1,j-i);
                                    break;
                                }
                            }
                            int k = j;
                            j=j+1;
                            for(;j<response.size();j++)
                            {
                                if (response[j]==' ')
                                {
                                    length=response.substr(k+1,j-k);
                                    break;
                                }
                            }
                            type=response.substr(j+1,3);
                            //cout<<"Client is "<<client<<endl;
                            //cout<<"Hash is "<<hash<<endl;
                            //cout<<"Length is "<<length<<endl;
                            //cout<<"Type is "<<type<<endl;  
                            user_struct temp;
                            temp.sock_fd = newfd;
                            temp.hash=hash;
                            temp.length=length;
                            temp.type=type;
							string a,b;
							int send_error;
                            if(freeworkers.size()<1)
							{	
								cout<<"hahaha"<<endl;
								outstanding_users.push_back(temp);
							}
							else
							{	
								cout<<"bababa"<<endl;
								busyusers.push_back(temp);
								//now send a free worker the pasword to be decoded

								encoded=temp.hash + temp.length + temp.type;

								cout<<"Encoded is "<<encoded<<endl;

								int number_of_free_workers = freeworkers.size();
								{	
									cout<<"Number of free workers is "<<number_of_free_workers<<endl;
									if(number_of_free_workers == 1)
									{
										cout<<"dadadada"<<endl;
										int len=lengtharr(temp.type);
										i=0;
										j=len-1;
										a=to_string(i);
										b=to_string(j);
										encoded = encoded + space + a + space + b;
										cout<<"ENCODED "<<encoded<<endl;
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
										int len=lengtharr(temp.type);
										i=0;
										j=len/2;
										a=to_string(i);
										b=to_string(j);
										string encoded1 = encoded + space + a +space+b;
										char encoded1_str[encoded1.size()+1];
										strcpy(encoded1_str,encoded1.c_str());						
										send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 1"<<endl;
											return 8;
										}
										//Send To Worker 2
										i=len/2+1;
										j=len-1;
										a=to_string(i);
										b=to_string(j);
										string encoded2 = encoded + space + a + space+ b;
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
										int len=lengtharr(temp.type);
										i=0;
										j=len/3;
										a=to_string(i);
										b=to_string(j);
										string encoded1 = encoded + space + a + space+ b;
										char encoded1_str[encoded1.size()+1];
										strcpy(encoded1_str,encoded1.c_str());						
										send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 1"<<endl;
											return 8;
										}
										//Send To Worker 2
										i=len/3 +1;
										j=2*len/3;
										a=to_string(i);
										b=to_string(j);
										string encoded2 = encoded + space + a + space+ b;
										char encoded2_str[encoded2.size()+1];
										strcpy(encoded2_str,encoded2.c_str());						
										send_error = send(freeworkers[1],encoded2_str,encoded2.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 2"<<endl;
											return 8;
										}	
										//Send To Worker 3
										i=2*len/3 +1;
										j=len-1;
										a=to_string(i);
										b=to_string(j);
										string encoded3 = encoded + space + a + space+ b;
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
									if(number_of_free_workers == 4)
									{
										//Send To Worker 1
										int len=lengtharr(temp.type);
										i=0;
										j=len/4;
										a=to_string(i);
										b=to_string(j);
										string encoded1 = encoded + space + a + space+ b;
										char encoded1_str[encoded1.size()+1];
										strcpy(encoded1_str,encoded1.c_str());						
										send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 1"<<endl;
											return 8;
										}
										//Send To Worker 2
										i=len/4 +1;
										j=2*len/4;
										a=to_string(i);
										b=to_string(j);
										string encoded2 = encoded + space + a + space+ b;
										char encoded2_str[encoded2.size()+1];
										strcpy(encoded2_str,encoded2.c_str());						
										send_error = send(freeworkers[1],encoded2_str,encoded2.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 2"<<endl;
											return 8;
										}	
										//Send To Worker 3
										i=2*len/4 +1;
										j=3*len/4;
										a=to_string(i);
										b=to_string(j);
										string encoded3 = encoded + space + a + space+ b;
										char encoded3_str[encoded3.size()+1];
										strcpy(encoded3_str,encoded3.c_str());						
										send_error = send(freeworkers[2],encoded3_str,encoded3.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 3"<<endl;
											return 8;
										}	
										i=3*len/4 +1;
										j=len-1;
										a=to_string(i);
										b=to_string(j);
										string encoded4 = encoded + space + a + space+ b;
										char encoded4_str[encoded4.size()+1];
										strcpy(encoded4_str,encoded4.c_str());						
										send_error = send(freeworkers[3],encoded4_str,encoded4.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 4"<<endl;
											return 8;
										}	
										freeworkers.clear();
									}
									if(number_of_free_workers == 5)
									{
										//Send To Worker 1
										int len=lengtharr(temp.type);
										i=0;
										j=len/5;
										a=to_string(i);
										b=to_string(j);
										string encoded1 = encoded + space + a + space+ b;
										char encoded1_str[encoded1.size()+1];
										strcpy(encoded1_str,encoded1.c_str());						
										send_error = send(freeworkers[0],encoded1_str,encoded1.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 1"<<endl;
											return 8;
										}
										//Send To Worker 2
										i=len/5 +1;
										j=2*len/5;
										a=to_string(i);
										b=to_string(j);
										string encoded2 = encoded + space + a + space+ b;
										char encoded2_str[encoded2.size()+1];
										strcpy(encoded2_str,encoded2.c_str());						
										send_error = send(freeworkers[1],encoded2_str,encoded2.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 2"<<endl;
											return 8;
										}	
										//Send To Worker 3
										i=2*len/5 +1;
										j=3*len/5;
										a=to_string(i);
										b=to_string(j);
										string encoded3 = encoded + space + a + space+ b;
										char encoded3_str[encoded3.size()+1];
										strcpy(encoded3_str,encoded3.c_str());						
										send_error = send(freeworkers[2],encoded3_str,encoded3.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 3"<<endl;
											return 8;
										}	
										i=3*len/5 +1;
										j=4*len/5;
										a=to_string(i);
										b=to_string(j);
										string encoded4 = encoded + space + a + space+ b;
										char encoded4_str[encoded4.size()+1];
										strcpy(encoded4_str,encoded4.c_str());						
										send_error = send(freeworkers[3],encoded4_str,encoded4.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 4"<<endl;
											return 8;
										}
										i=4*len/5 +1;
										j=len-1;
										a=to_string(i);
										b=to_string(j);
										string encoded5 = encoded + space + a + space+ b;
										char encoded5_str[encoded5.size()+1];
										strcpy(encoded5_str,encoded5.c_str());						
										send_error = send(freeworkers[4],encoded5_str,encoded5.size(),0);
										if(send_error == -1)
										{
											cout<<"Error in Sending password to be broken to the worker 4"<<endl;
											return 8;
										}	
										freeworkers.clear();
									}

								}

							}
                        }
                        else if (client=="Worker")
                        {
                            cout<<"Worker received "<<endl;
                            freeworkers.push_back(newfd);
                        }  
                        
                    }
                }
                else
                {	
                	memset(buf, '\0', 1024);
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof(buf), 0)) <= 0)
                    {
                        // got error or connection closed by client
                        if (nbytes == 0)
                        {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        }
                        else
                        {
                            perror("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    }
                    else
                    {   
                        // we got some data from a client
                        for(j = 0; j <= fdmax; j++)
                        {
                            // send to everyone!
                            if (FD_ISSET(j, &master))
                            {   
                            	cout<<"finally entered this loop "<<endl;
                            	string answer;
                            	int x=0;
                                for(;x<busyworkers.size();x++)
                                {
                                	if (j==busyworkers[x]) break;
                                }
                                cout<<"Socket at server is "<<j<<endl;
                                //we get which worker replied for the answer
                                //char buffer[1024];
                                //memset(buffer, '\0', 1024);
                                cout<<"came till here"<<endl;
		                        //int number_of_chars = recv(j,buffer,1024,0);
		                        //printf("Buffer : %s\n", buffer);
		                        //cout<<"Number of chars is "<<number_of_chars<<endl;
		                        if(nbytes < 0)
		                        {
		                            cout<<"Error in Receiving Message from client"<<endl;
		                            return 8;
		                        }
		                        //buffer[number_of_chars] = '\0';
		                        string response = string(buf);
		                        cout<<"Response "<<response<<endl;
		                        if(buf[0]=='T')
		                        {
		                        	answer=response.substr(2,response.size()-2);
		                        	char answer_str[answer.size()+1];
		                        	strcpy(answer_str,answer.c_str());
		                        	cout<<"Answer "<<answer<<endl;
		                        	int usersock= busyusers[0].sock_fd;
		                        	int send_error = send(usersock,answer_str,answer.size(),0);
									if(send_error == -1)
									{
										cout<<"Error in Sending Identity"<<endl;
										return 8;
									}
									else cout<<"Answer sent to user"<<endl;
									//now to send the abort signal to the other worker
									for(int p=0;p<busyworkers.size();p++)
	                                {
	                                	if (p!=j)
	                                	{
	                                		send_error = send(p,"complete",8,0);
											if(send_error == -1)
											{
												cout<<"Error in Sending Identity"<<endl;
												return 8;
											}	
	                                	}
	                                }
	                                //Also putting all the workers now in the freeworkers vector
	                                for (int p=0; p<busyworkers.size();p++)
	                                {
	                                	freeworkers.push_back(busyworkers[p]);
	                                }
	                                busyworkers.clear();	              
		                        }
                                /* except the listener and ourselves
                                if (j != listener && j != i)
                                {
                                    int a=outstanding_users[0].sock_fd;
                                    cout<<"lalala"<<endl;
                                    if (send(j, "HALO", nbytes, 0) == -1)
                                    {
                                        perror("send");
                                    }

                                }*/

		                    }
		                }
                    }
                } 
            }
        }
    }
    return 0;

}
