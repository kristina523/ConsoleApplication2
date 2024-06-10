#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

typedef bool (*ContainsAllCharsFunc)(const char*, const char*);

int main() {
	setlocale(LC_ALL, "");
	string inputStr;
	string inputChars;

	cout << "������� ������: ";
	getline(cin, inputStr);

	cout << "������� ������� ��� ������: ";
	getline(cin, inputChars);

	HINSTANCE hLib = LoadLibrary(L"DynamicLib.dll");
	if (!hLib) {
		cerr << "�� ������� ��������� ����������!" << endl;
		return 1;
	}

	ContainsAllCharsFunc contains_all_chars = (ContainsAllCharsFunc)GetProcAddress(hLib, "contains_all_chars");
	if (!contains_all_chars) {
		cerr << "�� ������� �������� ����� �������!" << endl;
		FreeLibrary(hLib);
		return 1;
	}

	bool result = contains_all_chars(inputStr.c_str(), inputChars.c_str());

	if (result) {
		cout << "��� ������� ������� � ������." << endl;
	}
	else {
		cout << "�� ��� ������� ������� � ������." << endl;
	}

	FreeLibrary(hLib);
	return 0;
}
