#include<iostream>
#include<string>
#include<crypt.h>


using namespace std;

int main()
{
	cout<<string(crypt("B2eR","aa"));
}