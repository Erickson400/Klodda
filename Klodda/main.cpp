#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;
string CheckDigit(char num);
string Decision;
void toClipboard(HWND hwnd, const std::string &s);
void Translator(); 
void Decoder();

int main() {
	SetConsoleTitle("Klodda");
	MENU: system("cls");
	#pragma region Title
	system("color 0c");
	cout << "	                     ___                  \n\
	  | | _ | _ _ __  _   | _  |/| _  _| _| _ \n\
	  |^|(/_|(_(_)|||(/_  |(_) |\\|(_)(_|(_|(_| \n\
			" << endl;

	//                     ___                  
	//  | | _ | _ _ __  _   | _  |/| _  _| _| _ 
	//  |^|(/_|(_(_)|||(/_  |(_) |\|(_)(_|(_|(_|

	#pragma endregion
	cout << "_____________________________________" << endl;
	cout << "| Welcome To The C++ Port of Klodda  |" << endl;
	cout << "|              By:Erickson Munoz     |" << endl;
	cout << "|                                    |" << endl;
	cout << "|What would you like to do ?         |" << endl;
	cout << "|____________________________________|" << endl;
	cout << "  1.Translate                         " << endl;
	cout << "  2.Decode                          \n" << endl;
	cout << "Enter Number: ";

	cin >> Decision;
	if (Decision!="1"&& Decision != "2") goto MENU;
	if (Decision=="1") {
		Translator();
		goto MENU;
	}
	else if (Decision=="2") {
		Decoder();
		goto MENU;
	}
	system("pause");
	return 0;
}

void Translator() {
	string Statement;
	string TranslatedStatement;
	TRANSLATE:
	system("cls");
	cout << "_____________________________________ " << endl;
	cout << "| Enter the Statement you  would     |" << endl;
	cout << "|  like to translate into Klodda     |" << endl;
	cout << "|____________________________________|" << endl;
	cout << "Enter Statement:\n";
	getline(cin, Statement);
	if (Statement.length() < 1) goto TRANSLATE;
	TranslatedStatement = "X";
	char lastLetter=0;
	for (unsigned int i=0; i < Statement.length(); i++) {
		char letter = Statement.substr(i).c_str()[0];
		if (letter > 96 && letter < 123) { // Lower
			if (lastLetter > 47 && lastLetter < 58) {
				TranslatedStatement += "0%";
			}
			letter -= 96;
			TranslatedStatement += CheckDigit(letter);
		}
		else if (letter > 64 && letter < 91) { // Upper
			if (lastLetter > 47 && lastLetter < 58) {
				TranslatedStatement += "0%";
			}
			letter -= 64;
			TranslatedStatement += CheckDigit(letter);
		}
		else if (letter > 47 && letter < 58) { //Number
			if (lastLetter > 47 && lastLetter < 58) {
				TranslatedStatement += letter;
			}
			else {
				TranslatedStatement += "0%";
				TranslatedStatement += letter;
			}
		} 
		else if (letter ==32) {
			if (lastLetter > 47 && lastLetter < 58) {
				TranslatedStatement += "0%";
			}
			TranslatedStatement += "00";
		}
		else {
			if (lastLetter > 47 && lastLetter < 58) {
				TranslatedStatement += "0%";
			}
			TranslatedStatement += "XX";
		}
		lastLetter = letter;
	}
	if (lastLetter > 47 && lastLetter < 58) {
		TranslatedStatement += "0%";
	}
	cout << "\nTranslation: \n" << TranslatedStatement << endl;
	toClipboard(GetDesktopWindow(), TranslatedStatement);
	cout << "\nTranslation Copied to Clipboard.." << endl;
	system("pause");
}
void Decoder() {
	string Code;
	string DecodedCode;
DECODER:
	system("cls");
	cout << "________________________________ " << endl;
	cout << "| Enter the Klodda Statement    |" << endl;
	cout << "|  you would like to Decode     |" << endl;
	cout << "|_______________________________|" << endl;
	cout << "Write/Past the code:\n";
	getline(cin, Code);
	if (Code.length() < 1) goto DECODER;
	Code = Code.substr(1);
	string lastCode = "";
	bool NumMode = false;

	for (unsigned int i = 0; i < Code.length(); i+=2) {
		NumMode = (Code.substr(i, 2) == "0%") ? true : false;

		if (NumMode) {
			string newCode = Code.substr(i+2);
			unsigned int number = 0;
			while (NumMode) {
				if (newCode.substr(number, 2) == "0%") {
					i += 2;
					NumMode = false;
				}
				else {
					DecodedCode += newCode.substr(number, 1);
					number++;
					i++;
				}
			}
		}
		else { //X192119250112120012151200130%80%002404
			if (Code.substr(i, 2)=="XX") {
				DecodedCode += "XX";
			}else
			if ((stoi(Code.substr(i, 2), nullptr, 10) + 96)==96) {
				DecodedCode += 32;
			}
			else if ((stoi(Code.substr(i, 2), nullptr, 10) + 96)>96&&(stoi(Code.substr(i, 2), nullptr, 10) + 96)<122) {
				DecodedCode += (stoi(Code.substr(i, 2), nullptr, 10) + 96);
			}
		}
	}
	cout << "\nDecoded: \n" << DecodedCode << "\n\n";
	system("pause");
}

void toClipboard(HWND hwnd, const std::string &s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

string CheckDigit(char num) {
	if (num < 10) {
		return "0"+to_string(num);
	}
	else {
		return to_string(num);
	}
}

