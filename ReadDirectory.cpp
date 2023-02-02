#include <Windows.h>
#include <iostream>

const wchar_t lpFormatFile[][6] = {
	L".txt", L".mp3", L".png",
	L".exe", L".pdf", L".ini",
	L".url", L".lnk", L".cpp",
	L".zip", L".jpg", L".user",
	};
wchar_t szPathBegin[] = L"C:\\Users\\Professional\\Desktop\\*";

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

bool haveFormat(wchar_t* szNameFile) {
	for (const auto format : lpFormatFile) 
		if (wcsstr(szNameFile, format) != NULL)
			return true;
	return false;
}

void printFilesInDirect(WIN32_FIND_DATA* ahFileFind, HANDLE ahFile, wchar_t aszPathTo[] = NULL) {
	if (aszPathTo != NULL) {
		ahFile = FindFirstFile(aszPathTo, ahFileFind);
		if (ahFile != INVALID_HANDLE_VALUE) {
			std::wcout << ahFileFind->cFileName << "\n";
			return printFilesInDirect(ahFileFind, ahFile);
		}
	}
	bool bProcessEnd = FindNextFile(ahFile, ahFileFind);
	if (!bProcessEnd) return;
	if (!haveFormat(ahFileFind->cFileName)) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		std::wcout << L"Folder: ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
	}
	std::wcout << ahFileFind->cFileName << "\n";
	return printFilesInDirect(ahFileFind, ahFile);
}
int main(int argc, char* argv[]) {
	WIN32_FIND_DATA hFileFind;
	HANDLE hFile;
	printFilesInDirect(&hFileFind, &hFile, szPathBegin);
	FindClose(hFile);
	return 0;
}