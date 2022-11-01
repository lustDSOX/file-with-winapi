#include "Header.h"
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	DWORD dwBytesRead = 0;
	char ReadBuffer[20];
	int bool = 0;
	int counter = 0;
	int counter_space = 0;
	float a, b, c;
	HANDLE file = CreateFile(L"1.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

    if (file != INVALID_HANDLE_VALUE)
    {
        DWORD size = 100, bytes;
        char* text = calloc(size+1,1);
        ReadFile(file, text, size, &bytes, NULL);
        CloseHandle(file);

		for (size_t i = 0; i < bytes; i++)
		{
			if (text[i] == '\n') {
				bool = 1;
			}
			if (text[i] < -1 || text[i] >96) {
				file = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				if (file != INVALID_HANDLE_VALUE) {
					WriteFile(file, "Введены не корректные данные", size, &bytes, NULL);
				}
				return 1;
			}
		}
		if (bool == 1) {
			for (size_t i = 0; i <= bytes; i++)
			{
				if (text[i] == '\r' && text[i + 1] == '\n') {
					counter_space++;
					char* f = calloc(counter+1, 1);
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];
					}
					counter = 0;
					switch (counter_space)
					{
					case 1:
						a = atof(f);
						break;
					case 2:
						b = atof(f);
						break;
					}
					i++;
					continue;
				}
				if (i == bytes) {
					char* f = calloc(counter, 1);
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];
					}
					c = atof(f);
				}
				counter++;
			}

		}
		else
		{
			for (size_t i = 0; i <= bytes; i++)
			{
				if (text[i] == ' ') {
					counter_space++;
					char* f = calloc(counter + 1, 1);
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];
					}
					counter = 0;
					switch (counter_space)
					{
					case 1:
						a = atof(f);
						break;
					case 2:
						b = atof(f);
						break;
					}
					continue;
				}
				if (i == bytes) {
					char* f = calloc(counter, 1);
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];
					}
					c = atof(f);
				}
				counter++;
			}

		}
  
    }
	QuadraticEquation(a, b, c);
}
void QuadraticEquation(float a, float b, float c)
{
	HANDLE file = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char answer_text[300];
	DWORD bytes;
	int size = 0;
	

	float x1, x2, discriminant;
	discriminant = powf(b, 2.0) - 4 * a * c;
	if (discriminant < 0 || a == 0)
	{
		WriteFile(file, "Решения нет", 11, &bytes, NULL);
		return 1;
	}
	if (discriminant == 0)
	{
		x1 = (-b) / (2 * a);
		sprintf(answer_text, "Дискриминант равен %f\nx1 = %f", discriminant,x1);
		while (answer_text[size] != 0)
		{
			size++;
		}
		WriteFile(file, answer_text, size, &bytes, NULL);
	}
	if (discriminant > 0)
	{
		x1 = ((-b) - sqrt(discriminant)) / (2 * a);
		x2 = ((-b) + sqrt(discriminant)) / (2 * a);
		sprintf(answer_text, "Дискриминант равен %f\nx1 = %f, x2 = %f", discriminant, x1, x2);
		while (answer_text[size] != 0)
		{
			size++;
		}
		WriteFile(file, answer_text, size, &bytes, NULL);
	}
}