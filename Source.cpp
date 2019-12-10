#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include<algorithm>
using namespace std;
string alphabet[27]={ "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z","_" };
string solver[27][27];
void setup();
void encode();
void decode();
int main() {
	setup();
	string answer = "";
	while (true) {
		cout << "Would you like to encode or decode?" << endl;
		cin >> answer;
		if (answer.substr(0, 1).compare("e") == 0) {
			encode();
			break;
		}
		if (answer.substr(0, 1).compare("d") ==0) {
			decode();
			break;
		}
	}
	cout << endl<< " done" << endl;
	return 0;
}
void setup() {
	//sets up 27x27 alphabet solver matrix
	int count;
	for (int i = 0; i < 27; ++i) {
		count = 0;
		for (int j = i; j < 27; ++j) {
			solver[i][count] = alphabet[j];
			count++;
		}
		count = 0;
		for (int k = (27 - i); k < 27; ++k) {
			solver[i][k] = alphabet[count];
			count++;
		}
	}
	//test prints solver array
	for (int row = 0; row < 27; ++row) {
		for (int col = 0; col < 27; ++col) {
			cout << solver[row][col];
		}
		cout << endl;
	}
}
void encode() {
	vector<string> finish;
	string word, key;
	cout << "Enter word to be encrypted" << endl;
	cin >> word;
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	cout << "Enter key to encrypt word with" << endl;
	cin >> key;
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	cout << "Encrypting: " << word << " with key: " << key << endl;
	unsigned int keyIndex, vertIndex, horIndex;
	keyIndex = 0;
	vertIndex = 0;
	horIndex = 0;
	//begins encoding
	for (unsigned int i = 0; i < word.length(); ++i) {
		if (keyIndex >= key.length()) { keyIndex = 0; } //simulates keystream
		for (int k = 0; k < 27; k++) {
			if ((word.substr(i, 1)).compare(alphabet[k]) == 0) {
				vertIndex = k;
				break;
			}
		}
		for (int j = 0; j < 27; ++j) {
			if (((key.substr(keyIndex, 1)).compare(solver[j][0])) == 0) {
				horIndex = j;
				keyIndex++;
				break;
			}
		}
		cout << "horizontal: " << horIndex << " vertical: " << vertIndex << " keyindex: " << keyIndex << endl;
		finish.push_back(solver[horIndex][vertIndex]);
		//print progress
		for (int f = 0; f < finish.size(); ++f) {
			cout << finish.at(f);
		}
		cout << endl;
	
}
		

	
	
	cout << "finish: ";
	for (int f = 0; f < finish.size(); ++f) {
		cout << finish.at(f);
	}

}
void decode() {
	string word, key;
	vector<string> finish;
	cout << "Enter encrypted word" << endl;
	cin >> word;
	transform(word.begin(), word.end(), word.begin(), ::toupper);
	cout << "Enter key" << endl;
	cin >> key;
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	cout << "encrypted word: " << word << endl;
	cout << "key: " << key << endl;
	unsigned int keyIndex, vertIndex, horIndex;
	keyIndex = 0;
	vertIndex = 0;
	horIndex = 0;
	for (int i = 0; i < word.length(); i++) {
		if (keyIndex >= key.length()) { keyIndex = 0; }
		for (int j = 0; j < 27; ++j) {
			if (key.substr(keyIndex, 1).compare(solver[j][0]) == 0) {
				horIndex = j;
				keyIndex++;
				break;
			}
		}
		for (int k = 0; k < 27; ++k) {
			if (word.substr(i, 1).compare(solver[horIndex][k]) == 0) {
				vertIndex = k;
				break;
			}
		}
		finish.push_back(alphabet[vertIndex]);
		for (int f = 0; f < finish.size(); ++f) {
			cout << finish.at(f);
		}
		cout << endl;
	}
	cout << "finished: ";
	for (int f = 0; f < finish.size(); ++f) {
		cout << finish.at(f);
	}
	cout << endl;
}



