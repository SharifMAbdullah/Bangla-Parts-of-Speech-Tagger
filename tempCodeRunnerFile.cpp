#include <bits/stdc++.h>
using namespace std;

int main() 
{
	fstream my_file,another_file;
	my_file.open("my_file.txt", ios::out);
	if (!my_file) {
		cout << "File not created!";
	}
	else {
		//cout << "File created successfully!";
		my_file << "হইত্তেসে কি আরে আরে কিরে ভাই";
		my_file.close();
	}
	
	my_file.open("my_file.txt", ios::in);
	another_file.open("another_file.txt", ios::out);
	if (!another_file) {
		cout << "No such file";
	}
	else {
		char ch;

		while (1) {
			my_file >> ch;
			if (my_file.eof())
				break;

			another_file << ch;
		}

	}
	another_file.close();
	my_file.close();
	return 0;
}