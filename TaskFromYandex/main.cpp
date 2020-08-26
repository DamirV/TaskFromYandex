#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
string ABC = "abcdefghijklmnopqrstuvwxyz";

int FindOffset(char encodedWord, char key) {
	int offset = key - encodedWord;
	if (offset < 0) {
		offset += 26;
	}
	return offset;
}

bool IsKeyFound(string encodedWord, string key) {
	if (encodedWord.length() != key.length()) {
		return false;
	}

	int offset = FindOffset(encodedWord[0], key[0]);
	int lengthWord = encodedWord.length();

	for (int i = 1; i < lengthWord; ++i) {
		if (ABC[(encodedWord[i] - 97 + offset) % 26] != key[i]) {
			return false;
		}
	}
	return true;
}

int main()
{
	ios_base::sync_with_stdio(false);
	ifstream input("input.txt");
	ofstream output("output.txt");

	string text;
	string outputText = "";
	int numberOfEncodedWords = 0;

	vector<string> keys;
	string* encodedWords;

	if (input.is_open())
	{
		getline(input, text);

		string numberOfEncodedWordsString;
		getline(input, numberOfEncodedWordsString);
		numberOfEncodedWords = stoi(numberOfEncodedWordsString);
		encodedWords = new string[numberOfEncodedWords];

		for (int i = 0; i < numberOfEncodedWords; ++i) {
			getline(input, encodedWords[i]);
		}
		input.close();
	}
	else {
		return -1;
	}

	stringstream ss(text);
	while (!ss.eof()) {
		string tempWord;
		ss >> tempWord;
		keys.push_back(tempWord);
	}

	int numberOfKeys = keys.size();
	for (int i = 0; i < numberOfEncodedWords; ++i) {
		for (int j = 0; j < numberOfKeys; ++j) {
			if (IsKeyFound(encodedWords[i], keys[j])) {
				outputText += keys[j] + "\n";
				break;
			}
		}
	}

	if (output.is_open()) {
		output << outputText;
		output.close();
	}
	else {
		return -1;
	}

	return 0;
}
