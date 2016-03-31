#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;




string decrypt(string hash, string length, string type)
{

	vector<char> symbols;
	symbols.resize(62);
	//Add Numbers to the symbols set
	for (int i = 0; i < 10; ++i)
	{
		symbols[i]='0' + i;
	}
	//Add Lowercase letters to the symbols set
	for (int i = 0; i < 26; i++)
	{
		symbols[i+10]= 'a' + i;
	}
	//Add Uppercase letters to the symbols set
	for (int i = 0; i < 26; ++i)
	{
		symbols[i+36] = 'A' + i;
	}

	int len = atoi(length);
	int t1 = 


	return string("YO_Sexy");
}

int main()
{
	decrypt("a","b","c");
}