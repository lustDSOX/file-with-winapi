#include "Header.h"
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	DWORD dwBytesRead = 0;
	char ReadBuffer[20];
	HANDLE file = CreateFile(L"1.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file != INVALID_HANDLE_VALUE)
    {
        DWORD size = 100, bytes;
        char* text = calloc(size+1,1);
        ReadFile(file, text, size, &bytes, NULL);
        CloseHandle(file);

        file = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file != INVALID_HANDLE_VALUE) {
            WriteFile(file, text, bytes, &bytes, NULL);
        }
    }
}