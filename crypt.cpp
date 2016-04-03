#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<crypt.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

vector<char> symbols_111;
vector<char> symbols_100;
vector<char> symbols_010;
vector<char> symbols_001;
vector<char> symbols_101;
vector<char> symbols_011;
vector<char> symbols_110;

string final;

int num,u_let,l_let;
string temp_hash;
bool flag=0;

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
	if(!flag)
	{
		if(i == length)
		{
			if(check_hash(test_string,length)) 
			{
				// print(test_string,length);
				// exit(EXIT_SUCCESS);
				flag = 1;
				final = "T ";
				// final = final + " ";
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

int main()
{
	decrypt("aaY/hGUxA42QE","6","001","0","9");
	cout<<final;
	// cout<<crypt("Ritwick","a")<<endl;
}