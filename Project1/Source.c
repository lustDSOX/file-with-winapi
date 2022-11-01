#include "Header.h"
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
	int bool = 0; //шоб знать, разделитель пробел или унтер
	int counter = 0;//счетчик знаков в числе
	int counter_space = 0;//счетчик разделителей
	float a, b, c;//ну бля, переменные
	HANDLE file = CreateFile(L"1.txt", GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//открываем для чтения

    if (file != INVALID_HANDLE_VALUE) //если файл есть
    {
        DWORD size = 100,//кол-во символов которые надо прочитать
			bytes;//типо счетчик реально прочитанных символов
        char* text = calloc(size+1,1);//буфер куда записывается прочитанное 
        ReadFile(file, text, size, &bytes, NULL);//читаем ебать
        CloseHandle(file);//закрываем нахуй ибо нахуй он нам нужен теперь

		for (size_t i = 0; i < bytes; i++)//проходимся по каждому символу из прочитанного 
		{
			if (text[i] == '\n') //если есть ентур
			{
				bool = 1;
			}
			if (text[i] < -1 || text[i] >96) //если символ(хз, вроде кириллица сюда не попадает, не помню)
			{
				file = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, 
					CREATE_ALWAYS, //если нет файла создаст, если есть перезапишет(удалит и создаст заново)
					FILE_ATTRIBUTE_NORMAL, NULL);//открываем для записи
					WriteFile(file, "Введены не корректные данные", size, &bytes, NULL);//записываем (size и bytes как и при чтении)
				return 1;//дальше нам работать не с чем, тк что вырубаем все нахой
			}
		}
		if (bool == 1) {//если через антеры
			for (size_t i = 0; i <= bytes; i++)
			{
				if (text[i] == '\r' && text[i + 1] == '\n') //если символ эта вот эти хуйни, по сути разделитель(по сути когда закончилось число)
				{
					counter_space++;//+ разделитель
					char* f = calloc(counter+1, 1);//массив символов размером counter+1
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];//заполняем массив знаками до разделителя(ну или между разделителями)
					}
					counter = 0;
					switch (counter_space)//так нахуй не делайте никогда
					{
					case 1://если это первый разделитель (первое число)
						a = atof(f);
						break;
					case 2://если второе число (вот охуесть)
						b = atof(f);
						break;
					}
					i++;//это чтобы через ентер перескочить
					continue;//скипаем следующее условие
				}
				if (i == bytes)//в конце нет разделителей, тк что заместо него конец текста
				{
					char* f = calloc(counter, 1);
					for (size_t l = 0; l < counter; l++)
					{
						f[l] = text[i - (counter - l)];
					}
					c = atof(f);
				}
				counter++;//счетчик кол-ва символов в числе
			}

		}
		else//если через space(не путать со спайсом)
		{
			//тут та-же хуйня так что идите нахуй я это и так почти 10 мин пишу
			// 
			// 
			//так тоже нахуй не пишите 
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
	QuadraticEquation(a, b, c);//у коли давно спиздил(считаем корни)
}
void QuadraticEquation(float a, float b, float c)
{
	HANDLE file = CreateFile(L"answer.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	char answer_text[300];//сюда будем писать текст который потом в файл запишем
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
		sprintf(answer_text, "Дискриминант равен %f\nx1 = %f", discriminant,x1);//крч эта хуйня засовывает текст с переменными так сказать(иди нахуй O_o) в массив символов
		while (answer_text[size] != 0)//считаем сколько букавак у нас получилось чтобы -52 в файл не записать
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
//чет я много "хуй" написал
