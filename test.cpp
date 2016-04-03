#include<iostream>
#include<string>
#include<crypt.h>
#include<fstream>

using namespace std;

int main()
{
	int i=0;
	ofstream write_file;
	ifstream read_file;
	write_file.open("hashed_random.txt");
	read_file.open("random_numbers.txt");
	char out[88];
	if(read_file.is_open())
	{
		// cout<<"Yo";
		while(!read_file.eof() && i<10)
		{
			read_file >> out;
			// cout<<out;
			string a;
			a = string(crypt(out,"aa"));
			a = a + "\n";
			// cout<<a;
			write_file << a.c_str();
			i++;
		}
	}
	read_file.close();
	write_file.close();
	return 0;
}
