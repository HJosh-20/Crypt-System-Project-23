#include <iostream>
#include <string>
using namespace std;
const int eAddKeyOne = 23; //add 1
const int eMultiKeyOne = 5; //multiply 1
const int eMultiKeyTwo = 13; //multiply 2
const int eAddKeyTwo = 7; //add 2
const int dAddKeyOne = 14; //add 1
const int dMultiKeyOne = 15; //multiply 1
const int dMultiKeyTwo = 20; //multiply 2
const int dAddKeyTwo = 30; //add 2
const int modulus = 37;

//Function Prototype
string message(string str);

//Validates the characters of a message
int validateCharacters(string message) {  //validates the characters used within the message the user inputs, returns 1 for true and 0 for false
	//Valid Characters a, b, c...y, z, 0, 1, 2....8, 9, ' ', (ascii 97-122) (ascii 48 - 57) (ascii 32)
	for (int i = 0; i < size(message); i++) {
		if (message[i] >= 97 && message[i] <= 122) { //checking a, b, c...y, z
		}
		else if (message[i] >= 48 && message[i] <= 57) { //checking 0, 1, 2...8, 9
		}
		else if (message[i] == 32) {//checking if it's a space
		}
		else {
			return 0;
		}
	}
	return 1;
}

//We do not need this function anymore. But it is here just incase we need it for some reason
int validCharacters(string str) {  //takes the input from the user and gets the message, passing it to validateCharacters to validate them, then returns 1 for true and 0 for false
	string message; //to store the message form the user
	int start = str.find("\'") + 1; //returns where the ' is plus 1 (plus 1 to get rid of ')
	int length = size(str) - start - 1;  //Gets the length of the substring (minus 1 to get rid of ')
	message = str.substr(start, length);  //gets the "message" part of the string
	return validateCharacters(message);  //sends the message to be validated and returns the results to main
}

//turns the string message into numbers based on our crypto system
int* translator(string message) {  //translates the message from characters to numbers
	static int numArray[1];
	for (int i = 0; i < size(message); i++) {
		if (message[i] >= 97 && message[i] <= 122) { //a, b, c...y, z
			numArray[i] = message[i] - 97;
		}
		else if (message[i] >= 48 && message[i] <= 57) { //0, 1, 2...8, 9
			numArray[i] = int(message[i]) - 22;
		}
		else if (message[i] == 32) { //space shcaracter
			numArray[i] = message[i] + 4;
		}
	}
	return numArray;
}

//turns the crypto numbers back into characters
string translator(int numMessage[], int length) {  //translates the message from numbers to characters (this function is acting as an overloaded function)
	string strArray;

	for (int i = 0; i < length; i++) {
		if (numMessage[i] >= 0 && numMessage[i] <= 25) { //a, b, c...y, z
			strArray += char(numMessage[i] + 97);
		}
		else if (numMessage[i] >= 26 && numMessage[i] <= 35) { //0, 1, 2...8, 9
			strArray += char(numMessage[i] + 22);
		}
		else if (numMessage[i] == 36) { //space shcaracter
			strArray += char(numMessage[i] - 4);
		}
	}
	return strArray;
}

//Gets the "message" part of the string
string getMessage(string str) {
	string message; //to store the message form the user
	if (int(str.find('\(')) > -1 && int(str.find('\)')) > -1) {  //return if the user wants to encode or decode
		int start = str.find("\(") + 1; //returns where the ' is plus 1 (plus 1 to get rid of ')
		int length = size(str) - start - 1;  //Gets the length of the substring (minus 1 to get rid of ')
		message = str.substr(start, length);  //gets the "message" part of the string
		return message;
	}
	else {
		return "**error";
	}
}

//encrypts the message
string encode(string message) {
	int* numArray = translator(message);  //turns the message to numbers
	for (int i = 0; i < size(message); i++) {  //performs calculations on each number
		numArray[i] = (numArray[i] + eAddKeyOne) % modulus;
		numArray[i] = (numArray[i] * eMultiKeyOne) % modulus;
		numArray[i] = (numArray[i] * eMultiKeyTwo) % modulus;
		numArray[i] = (numArray[i] + eAddKeyTwo) % modulus;
	}
	message = translator(numArray, size(message));  //translates the numbers back to characters
	return message;
}

//decrypts the message
string decode(string message) {
	int* numArray = translator(message);  //turns the message to numbers
	for (int i = 0; i < size(message); i++) {  //performs calculations on each number
		numArray[i] = (numArray[i] + dAddKeyTwo) % modulus;
		numArray[i] = (numArray[i] * dMultiKeyTwo) % modulus;
		numArray[i] = (numArray[i] * dMultiKeyOne) % modulus;
		numArray[i] = (numArray[i] + dAddKeyOne) % modulus;
	}
	message = translator(numArray, size(message));  //translates the numbers back to characters
	return message;
}

//repots back any errors, or calls the encode/decode functions to execute, or reutnrs a message if there is no encoding or decoding that needs to happen
string crypt(string crypt, string message) {
	if (message == "*error" || message == "**error" || message == "***error") {
		return message;
	}
	else if (crypt != "encode" && crypt != "decode") {
		return "***error";
	}
	else if (crypt == "encode") {
		return encode(message);
	}
	else if (crypt == "decode") {
		return decode(message);
	}
	else {
		return message;
	}
}

//Breaks userinput apart into the crypt and message parts
string userInput(string str) {
	return crypt(str.substr(0, 6), message(getMessage(str)));
}

//checks the message portion of the user input to see if there needs to be another call to userInput. If not the message is evaluated and checked
string message(string str) {
	if (int(str.find('\(')) > -1 || int(str.find('\)')) > -1) {  //return if the user wants to encode or decode
		return userInput(str);
	}
	else {  //return the message or the error
		if (validateCharacters(str)) {
			return str;
		}
		else if (str == "**error") {
			return str;
		}
		else {
			return "*error";
		}
	}
}

int main() {
	string input;

	//Asks the user for their message and if they want to encrypt or decrypt it
	while (true) {
		cout << "Specify whether you want to decode or encode followed by your message encapsulated with ().\n";
		getline(cin, input);
		if (input == "exit") {  //ends the loop
			break;
		}
		else {
			string cryptMessage = userInput(input);
			if (cryptMessage == "*error") {  //used to show errors to the user or their output
				cout << "There are invalid characters in your message.";
			}
			else if (cryptMessage == "**error") {
				cout << "You are missing parenthesis.";
			}
			else if (cryptMessage == "***error") {
				cout << "There is a problem understanding if you want to encode or decode your message.";
			}
			else {
				cout << userInput(input);
			}
			cout << "\n\n";
		}
	}

	return 0;
}