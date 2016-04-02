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

void Generate(char* test_string, int i, int length)
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
						Generate(test_string,i+1,length);
					}		
				}
				else
				{
					//num = 1 u_let = 1 l_let=0
					for(int j=0; j<35;j++)
					{
						// cout<<"yo"<<" "<<i<<" "<<length<<endl;
						test_string[i] = symbols[j];
						Generate(test_string,i+1,length);
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
						Generate(test_string,i+1,length);
					}
					for (int j = 36; j <62 ; j++)
					{
						test_string[i] = symbols[j];
						Generate(test_string,i+1,length);
					}	

				}
				else
				{
					//num = 1 u_let = 0 l_let=0
					for(int j=0; j<10;j++)
					{
						// cout<<"yo"<<" "<<i<<" "<<length<<endl;
						test_string[i] = symbols[j];
						Generate(test_string,i+1,length);
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
						Generate(test_string,i+1,length);
					}		
				
				}
				else
				{
					//num = 0 u_let = 1 l_let=0
					for(int j=10; j<36;j++)
					{
						// cout<<"yo"<<" "<<i<<" "<<length<<endl;
						test_string[i] = symbols[j];
						Generate(test_string,i+1,length);
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
						Generate(test_string,i+1,length);
					}		
				
				}
			}			
		}
	}
}

string decrypt(string hash, string length, string type)
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
	Generate(test_string,0,len);
	

	return string("YO_Sexy");
}

int main()
{
	decrypt("aaCgzzoaUE85w","4","111");
	// cout<<crypt("Ritwick","a")<<endl;
}