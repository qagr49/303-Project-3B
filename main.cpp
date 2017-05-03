#include <iostream>
#include <fstream>
#include "morse_tree.h"
using namespace std;

int main()
{
	ifstream fin("alphabet.txt");
	morse_tree morse_tree(fin);

	cout << morse_tree.encode("sos") << endl;
	cout << morse_tree.decode("... ___ ...") << endl;
	cout << morse_tree.decode(morse_tree.encode("The quick brown fox jumps over the lazy dog")) << endl; // check for all letters in the alphabet

	system("pause");
}
