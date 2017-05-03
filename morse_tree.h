#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/** A node for a Binary Tree. Part of the code on blackboard*/
template<typename Item_Type>
struct BTNode
{
	// Data Fields
	Item_Type data;
	BTNode<Item_Type>* left;
	BTNode<Item_Type>* right;

	// Constructor
	BTNode(const Item_Type& the_data,
		BTNode<Item_Type>* left_val = NULL,
		BTNode<Item_Type>* right_val = NULL) :
		data(the_data), left(left_val), right(right_val) {}

	// Destructor (to avoid warning message)
	virtual ~BTNode() {}


}; // End BTNode


class morse_tree {
private:
	BTNode<char> *root;
	vector<pair<char, string>> alphabet; // this vector will behave like a map because I insert items in alphabetical order, but I can access elements by index which is faster than a map


	void buildFromAlphabet(BTNode<char>* node,  string current_code) {
		char cl = '0', cr = '0';
		string left_code = current_code + '.';
		string right_code = current_code + '_';

		for (int i = 0; i < alphabet.size(); i++) { // linear search for a corresponding code
			if (alphabet[i].second == left_code) {
				cl = alphabet[i].first;
			}
			if (alphabet[i].second == right_code) {
				cr = alphabet[i].first;
			}
		}

		if (cl != '0') { // we insert the letter in the left place then continue traversing
			node->left = new BTNode<char>(cl);
			buildFromAlphabet(node->left, left_code);
		}

		if (cr != '0') { // we insert the letter in the right place then continue traversing
			node->right = new BTNode<char>(cr);
			buildFromAlphabet(node->right, right_code);
		}
	}

	// decode a letter, do not enter and invalide morse code
	string decodeLetter(string s) {
		BTNode<char> * current = root;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '.') current = current->left;
			if (s[i] == '_') current = current->right;
		}
		stringstream ss;
		string to_return;
		ss << current->data;
		ss >> to_return; // without this operation, the char would be read as its ascii code: e would be printed "101"
		return to_return;
	}

public: 
	BTNode<char> * getRoot() {
		return root;
	}

	morse_tree(ifstream& fin)  {

		// create root
		root = new BTNode<char>('0'); // '0' for dummy node
		

		// extract alphabet from file
		while (fin.good()) {
			string line;
			getline(fin, line);
			if (line != "") {
				alphabet.push_back(pair<char, string>(line[0], line.substr(1))); // extract alphabet, a._ is read (a, ._)
			}
		}

		// create tree
		buildFromAlphabet(root, "");
	}

	string encode(string s) {
		string result = "";
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != ' ') { 
				int current = tolower(s[i]);
				result = result + alphabet.at(current - 97).second + " "; // ASCII a is 97 and its index is 0 in our alphabet, and so on to z 122 with index 25 (= 122 - 97)
			}
		}
		return result;
	}

	string decode(string s) {
		string coded_letter = "", result = "";
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != ' ') {
				coded_letter += s[i]; // build a letter code until space
			}
			else {
				result += decodeLetter(coded_letter) + " "; // decode and reset letter code
				coded_letter = "";
			}
		}
		if (s[s.size() - 1] != ' ') { // if s doesnt end with space character
			result += decodeLetter(coded_letter) + " ";
		}
		return result;
	}


};
