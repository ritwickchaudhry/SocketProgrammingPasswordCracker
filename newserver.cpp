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
                        char buffer[1024];
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax)   // keep track of the maximum
                        {
                            fdmax = newfd;
                        }
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
                            outstanding_users.push_back(temp);
                        }
                        if (client=="Worker")
                        {
                            freeworkers.push_back(newfd);
                        }  
                    }
                }
                else
                {
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
                                // except the listener and ourselves
                                if (j != listener && j != i)
                                {
                                    int a=outstanding_users[0].sock_fd;
                                    cout<<"lalala"<<endl;
                                    if (send(j, "HALO", nbytes, 0) == -1)
                                    {
                                        perror("send");
                                    }

                                }
                            }
                        }
                    }
                } // it’s SO UGLY!
            }
        }
    }
    return 0;

}
