#include <iostream> // эта библиотека содержит файлы программ, предназначенных для ввода и вывода информации
#include <time.h> // эта библиотека необходима для подключения функции time, которая в результате своей работы возвращает количество секунд, прошедших с 1.01.1970 - это количество необходимо для создания случайных чисел
#include <windows.h> // без этой функции не будут работать некоторые функции (например SetConsoleTextAttribute)
#include <conio.h> // эта библиотека подключается для вызова функции _getch, которая возвращает код нажатой клавиши
using namespace std;

void main();  //  для удобства обращения к функциям созданы их прототипы
void Massive();  // описание функций - ниже в коде
void DarkMassive();
void Massive_2();
void DarkMassive_2();
void Table(int xposit, int yposit, int color);

HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE); //переменная с этим типом данных хранит в себе дескриптор того окна, в котором выполняется программа
COORD c; //переменная с этим типом данных хранит в себе координаты курсора

int gat1, gat2; // переменные запоминают координаты курсора

const int trainsize = 19; // таблица - игровое поле имеет высоту и ширину, равную 19
int traintable[trainsize][trainsize];  // массив - игровое поле

const int massivsize = 81; // одномерный массив, содержащий 81 элемент
int mass[massivsize]; // массив, невидимые значения которого нужно отгадать
int mess[massivsize]; // массив необходим для определения невидимых клеток
int most[massivsize]; // массив, невидимые значения которого нужно отгадать (2 игрока)
int dame[massivsize]; // массив необходим для определения невидимых клеток (2 игрока)

int fortimer = 0; // эта переменная служит для включения и отключения таймера в необходимое время 
int sec = 0; // хранит количество прошедших (оставшихся) секунд
int breaktimer = 0;  // эта переменная используется для захватывающей анимации в обучающей игре(перемещения таймера по экрану)

char name1[255];    // перед началом многопользовательской игры пользователи должны представиться
char name2[255];

void Stand(int wait, int xposition, int yposition, int textcolor) { //функция
	Sleep(wait);    //определяет, сколько при необходимости придётся ждать времени перед 
	c.X = xposition;  // установкой координат курсора и окрашиванием текста в нужный цвет
	c.Y = yposition;
	SetConsoleCursorPosition(H, c);
	SetConsoleTextAttribute(H, textcolor);
}

DWORD WINAPI
timerplus(void* p) {  //функция - таймер (сек+)
	sec = 0; // обнулить количество секунд (если тренировка будет запущена более 1 раза)
	int s, m; // секунды и минуты
	COORD c111 = { 70,5 };  // координаты прорисовки минут и секунд
	while (fortimer == 0) {  // до тех пор, пока таймер не будет остановлен
		s = sec % 60;     // отображать секунды  (если sec=68, то s=8)
		m = sec / 60;     // и минуты      (если sec=68, то m=1)
		SetConsoleCursorPosition(H, c111);  // установить курсор для показа таймера
		SetConsoleTextAttribute(H, 10);    // зелёного цвета 
		if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;  // оформление отображения
		if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
		if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
		if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
		Stand(0, 75, 5, 0); // если в процессе одновременной прорисовки что-то вдруг появится рядом с таймером, оно будет закрашено чёрным
		//FillConsoleOutputAttribute(H, 0, 83, c, 0);
		Stand(5, gat1, gat2, 7);   // вернуть курсор в игровую функцию
		Sleep(995);
		sec++;
	}
	if (breaktimer == 1) { // когда таймер остановлен, начинается "анимация"
		int checkitnow = 33;  // на сколько строк опускаться
		int coordybt = 5;    // координата по y
		while (checkitnow--) {
			Stand(0, 70, coordybt, 10);
			if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;
			if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
			if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
			if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
			Stand(15, 70, coordybt, 0);
			if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;
			if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
			if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
			if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
			coordybt++;
		}
		checkitnow = 24;   // на сколько стобцов переместиться влево
		coordybt = 70;    // координата по х
		while (checkitnow--) {
			Stand(0, coordybt, 37, 10);
			if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;
			if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
			if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
			if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
			Stand(15, coordybt, 37, 0);
			if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;
			if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
			if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
			if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
			coordybt--;
		}
		Stand(0, 46, 37, 10);  // показ таймера после остановки
		if (sec < 600 && sec % 60 < 10) cout << "0" << m << ":0" << s;
		if (sec < 600 && sec % 60 >= 10) cout << "0" << m << ":" << s;
		if (sec >= 600 && sec % 60 < 10) cout << m << ":0" << s;
		if (sec >= 600 && sec % 60 >= 10) cout << m << ":" << s;
		Sleep(5000);
	}
	return 0;
}

DWORD WINAPI
timerminus(void* p) {  //функция - таймер (сек-)
	int* secnd = (int*)p;  // передаётся количество секунд для игры
	int s, m; // секунды и минуты
	COORD c111 = { 70,5 };  // координаты прорисовки минут и секунд
	while (fortimer == 0) {  // до тех пор, пока таймер не будет остановлен
		s = (*secnd) % 60;     // отображать секунды  (если sec=68, то s=8)
		m = (*secnd) / 60;     // и минуты      (если sec=68, то m=1)
		SetConsoleCursorPosition(H, c111);  // установить курсор для показа таймера
		SetConsoleTextAttribute(H, 10);    // зелёного цвета 
		if ((*secnd) < 600 && (*secnd) % 60 < 10) cout << "0" << m << ":0" << s;  // оформление отображения
		if ((*secnd) < 600 && (*secnd) % 60 >= 10) cout << "0" << m << ":" << s;
		if ((*secnd) >= 600 && (*secnd) % 60 < 10) cout << m << ":0" << s;
		if ((*secnd) >= 600 && (*secnd) % 60 >= 10) cout << m << ":" << s;
		Stand(0, 75, 5, 0); // если в процессе одновременной прорисовки что-то вдруг появится рядом с таймером, оно будет закрашено чёрным
		//FillConsoleOutputAttribute(H, 0, 3, c, 0);
		Stand(5, gat1, gat2, 7);    // вернуть курсор в игровую функцию
		Sleep(995);
		(*secnd)--;
		sec = (*secnd);
	}
	return 0;
}

DWORD WINAPI
primitivetimer(void* p) {  // обычный таймер, который не выводится на экран, но отсчитывает секунды
	int* secnd = (int*)p;  // передаётся количество секунд для игры
	while (sec != 0) {
		Sleep(1000);
		(*secnd)--;
		sec = (*secnd);
	}
	return 0;
}

DWORD WINAPI // музыка для оконченной игры 
gameoverm(void* p) {
	int temp = 400;
	Beep(865, temp); Sleep(temp / 60); Beep(865, temp); Sleep(temp / 60); Beep(865, temp);
	Sleep(temp / 60); Beep(700, 2 * temp / 3); Sleep(temp / 120); Beep(1050, temp / 3); Sleep(temp / 120);
	Beep(865, temp); Sleep(temp / 60); Beep(700, 2 * temp / 3); Sleep(temp / 120); Beep(1050, temp / 3);
	Sleep(temp / 120); Beep(865, temp + temp / 6); Sleep(temp - temp / 6); Beep(1320, temp);
	Sleep(temp / 60); Beep(1320, temp); Sleep(temp / 60); Beep(1320, temp); Sleep(temp / 60);
	Beep(1390, 2 * temp / 3); Sleep(temp / 120); Beep(1050, temp / 3); Sleep(temp / 120); Beep(820, temp);
	Sleep(temp / 60); Beep(700, 2 * temp / 3); Sleep(temp / 120); Beep(1050, temp / 3);
	Sleep(temp / 120); Beep(865, temp + temp / 6); Sleep(temp - temp / 6);
	return 0;
}

DWORD WINAPI  // музыка для таблицы рекордов 
hsm(void* p) {
	int t = 120;
	int s = 35;
	Beep(865, t); Beep(1320, t); Beep(865, t - s); Sleep(s); Beep(1320, t); Beep(865, t);
	Beep(1320, t - s); Sleep(s); Beep(865, t); Beep(1320, t); Beep(865, t - s); Sleep(s);
	Beep(1320, t); Beep(865, t); Beep(1320, t - s); Sleep(s); Beep(690, t); Beep(1320, t);
	Beep(690, t); Beep(1320, t); Beep(690, t); Beep(1320, t); Beep(690, t); Beep(1170, t);
	Beep(690, t); Beep(1170, t); Beep(690, t); Beep(1170, t); Beep(777, t); Beep(1170, t);
	Beep(777, t - s); Sleep(s); Beep(1170, t); Beep(777, t); Beep(1170, t - s); Sleep(s);
	Beep(777, t); Beep(1170, t); Beep(777, t - s); Sleep(s); Beep(1170, t); Beep(777, t);
	Beep(1170, t - s); Sleep(s); Beep(655, t); Beep(1170, t); Beep(655, t); Beep(1170, t);
	Beep(655, t); Beep(1170, t); Beep(655, t); Beep(1050, t); Beep(655, t); Beep(1050, t);
	Beep(655, t); Beep(1050, t); Beep(690, t); Beep(1050, t); Beep(690, t - s); Sleep(s);
	Beep(1050, t); Beep(690, t); Beep(1050, t - s); Sleep(s); Beep(690, t); Beep(1050, t);
	Beep(690, t); Beep(650, t); Beep(1050, t); Beep(650, t); Beep(580, t); Beep(1050, t);
	Beep(580, t); Beep(1050, t); Beep(580, t); Beep(1050, t); Beep(580, t); Beep(1000, t);
	Beep(580, t); Beep(1000, t); Beep(580, t); Beep(1000, t); Beep(500, t); Beep(1000, t);
	Beep(500, t); Beep(1000, t); Beep(500, t); Beep(1000, t); Beep(500, t); Beep(865, t);
	Beep(500, t); Beep(865, t); Beep(500, t); Beep(865, t); Beep(650, t); Beep(865, t);
	Beep(650, t); Beep(865, t); Beep(650, t); Beep(865, t); Beep(650, t); Beep(825, t);
	Beep(650, t); Beep(825, t); Beep(650, t); Beep(825, t); Beep(865, 2 * t);
	return 0;
}

void Head() {  //когда запущено меню, при помощи псевдографики отображается заголовок игры
	system("cls");
	int headwidth = 74, headheight = 15, headcolor = 10;
	int xplace, yplace = 3;
	char headsymbol = 218;
	for (int y = 0; y < headheight; y++) {
		xplace = 3;
		for (int x = 0; x < headwidth; x++) {
			Stand(0, xplace, yplace, headcolor);
			if (y == 0 && (x > 3 && x < 10 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 34 || x>39 && x < 46 || x>49 && x < 53 || x>56 && x < 60 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 1 && (x > 2 && x < 11 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 35 || x>38 && x < 47 || x>49 && x < 53 || x>56 && x < 60 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 2 && (x > 1 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 36 || x>37 && x < 48 || x>49 && x < 53 || x>55 && x < 59 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 3 && (x > 1 && x < 6 || x>7 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>31 && x < 36 || x>37 && x < 42 || x>43 && x < 48 || x>49 && x < 53 || x>55 && x < 59 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 4 && (x > 1 && x < 5 || x>8 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 5 && (x > 1 && x < 6 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 6 && (x > 1 && x < 10 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 7 && (x > 2 && x < 11 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>52 && x < 56 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 8 && (x > 3 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>52 && x < 56 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 9 && (x > 7 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 10 && (x > 1 && x < 5 || x>8 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 11 && (x > 1 && x < 6 || x>7 && x < 12 || x>13 && x < 18 || x>19 && x < 24 || x>25 && x < 29 || x>31 && x < 36 || x>37 && x < 42 || x>43 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 66 || x>67 && x < 72)) cout << headsymbol;
			else if (y == 12 && (x > 1 && x < 12 || x>13 && x < 24 || x>25 && x < 36 || x>37 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>58 && x < 60 || x>61 && x < 72)) cout << headsymbol;
			else if (y == 13 && (x > 2 && x < 11 || x>14 && x < 24 || x>25 && x < 35 || x>38 && x < 47 || x>49 && x < 53 || x>55 && x < 60 || x>62 && x < 72)) cout << headsymbol;
			else if (y == 14 && (x > 3 && x < 10 || x>15 && x < 20 || x>20 && x < 24 || x>25 && x < 34 || x>39 && x < 46 || x>49 && x < 53 || x>56 && x < 59 || x>63 && x < 68 || x>68 && x < 72)) cout << headsymbol;
			else { SetConsoleTextAttribute(H, 0); cout << " "; }
			xplace++;
		}
		yplace++;
	}
}

void ShockHead(char headsymbol, int headcolor) {  //функция при помощи псевдографики отображает на экране заголовок игры на таблице рекордов
	c.X = 0;
	c.Y = 0;
	SetConsoleCursorPosition(H, c);
	int headwidth = 74, headheight = 15;
	int xplace, yplace = 3;
	for (int y = 0; y < headheight; y++) {
		xplace = 3;
		for (int x = 0; x < headwidth; x++) {
			Stand(0, xplace, yplace, headcolor);
			if (y == 0 && (x > 3 && x < 10 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 34 || x>39 && x < 46 || x>49 && x < 53 || x>56 && x < 60 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 1 && (x > 2 && x < 11 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 35 || x>38 && x < 47 || x>49 && x < 53 || x>56 && x < 60 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 2 && (x > 1 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 36 || x>37 && x < 48 || x>49 && x < 53 || x>55 && x < 59 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 3 && (x > 1 && x < 6 || x>7 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>31 && x < 36 || x>37 && x < 42 || x>43 && x < 48 || x>49 && x < 53 || x>55 && x < 59 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 4 && (x > 1 && x < 5 || x>8 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 5 && (x > 1 && x < 6 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 6 && (x > 1 && x < 10 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 7 && (x > 2 && x < 11 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>52 && x < 56 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 8 && (x > 3 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>52 && x < 56 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 9 && (x > 7 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 10 && (x > 1 && x < 5 || x>8 && x < 12 || x>13 && x < 17 || x>20 && x < 24 || x>25 && x < 29 || x>32 && x < 36 || x>37 && x < 41 || x>44 && x < 48 || x>49 && x < 53 || x>53 && x < 57 || x>61 && x < 65 || x>68 && x < 72)) cout << headsymbol;
			else if (y == 11 && (x > 1 && x < 6 || x>7 && x < 12 || x>13 && x < 18 || x>19 && x < 24 || x>25 && x < 29 || x>31 && x < 36 || x>37 && x < 42 || x>43 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>61 && x < 66 || x>67 && x < 72)) cout << headsymbol;
			else if (y == 12 && (x > 1 && x < 12 || x>13 && x < 24 || x>25 && x < 36 || x>37 && x < 48 || x>49 && x < 53 || x>54 && x < 58 || x>58 && x < 60 || x>61 && x < 72)) cout << headsymbol;
			else if (y == 13 && (x > 2 && x < 11 || x>14 && x < 24 || x>25 && x < 35 || x>38 && x < 47 || x>49 && x < 53 || x>55 && x < 60 || x>62 && x < 72)) cout << headsymbol;
			else if (y == 14 && (x > 3 && x < 10 || x>15 && x < 20 || x>20 && x < 24 || x>25 && x < 34 || x>39 && x < 46 || x>49 && x < 53 || x>56 && x < 59 || x>63 && x < 68 || x>68 && x < 72)) cout << headsymbol;
			else { SetConsoleTextAttribute(H, 0); cout << " "; }
			xplace++;
		}
		yplace++;
	}
	Sleep(15);
}

void Row(int bc, int bdc) {  //функция создаёт шаблон пункта, т.е. одной строки меню
	const int wid = 18, heig = 5;
	int rowmass[wid][heig];
	cout << "\n\t\t\t       ";
	for (int j = 0; j < heig; j++) {
		for (int i = 0; i < wid; i++) {
			if (i == 0 && j == 0 || i == wid - 1 && j == 0 || i == 0 && j == heig - 1 || i == wid - 1 && j == heig - 1) {
				SetConsoleTextAttribute(H, bc);
				rowmass[i][j] = 219;
			}
			else if (j == 0 && i != 0 && i != wid - 1) {
				SetConsoleTextAttribute(H, bc);
				rowmass[i][j] = 223;
			}
			else if (j == heig - 1 && i != 0 && i != wid - 1) {
				SetConsoleTextAttribute(H, bc);
				rowmass[i][j] = 220;
			}
			else if (i == wid - 1 && j != 0 && j != heig - 1) {
				SetConsoleTextAttribute(H, bc);
				rowmass[i][j] = 222;
			}
			else if (i == 0 && j != 0 && j != heig - 1) {
				SetConsoleTextAttribute(H, bc);
				rowmass[i][j] = 221;
			}
			else {
				SetConsoleTextAttribute(H, bdc);
				rowmass[i][j] = 0;
			}
			cout << (char)rowmass[i][j];
		}
		SetConsoleTextAttribute(H, 0);
		cout << "\n\t\t\t       ";
	}
}

void Menu(int rownumber) {
	Stand(0, 5, 47, 0);  //очищается нижняя поясняющая строчка
	cout << "                                                           ";
	Stand(0, 5, 47, 7);  //поясняющие строки для пунктов меню
	if (rownumber == 1) cout << "Press enter to start new one player game";
	if (rownumber == 2) cout << "Press enter to start new two players game";
	if (rownumber == 3) cout << "Press enter if you want to know something about sudoku";
	if (rownumber == 4) cout << "Press enter to exit";
	Stand(0, 33, 21, 7);
	if (rownumber == 1) {     // 1 пункт активен, остальные - нет
		Row(145, 144);
		Stand(0, 47, 23, 159);
		cout << (char)191;
		Stand(0, 29, 24, 9);
		cout << (char)16;
	}
	if (rownumber != 1) {
		Row(1, 1);
		Stand(0, 33, 24, 1);
		cout << "1 Player  Game";
	}
	cout << "\n\n\n";
	if (rownumber == 2) {        // 2 пункт активен, остальные - нет
		Row(230, 224);
		Stand(0, 47, 29, 239);
		cout << (char)191;
		Stand(0, 29, 30, 14);
		cout << (char)16;
	}
	if (rownumber != 2) {
		Row(6, 6);
		Stand(0, 33, 30, 6);
		cout << "2 Players Game";
	}
	cout << "\n\n\n";
	if (rownumber == 3) {        // 3 пункт активен, остальные - нет
		Row(213, 208);
		Stand(0, 47, 35, 223);
		cout << (char)191;
		Stand(0, 29, 36, 13);
		cout << (char)16;
	}
	if (rownumber != 3) {
		Row(5, 5);
		Stand(0, 34, 36, 5);
		cout << "About Sudoku";
	}
	cout << "\n\n\n";
	if (rownumber == 4) {        // 4 пункт активен, остальные - нет
		Row(196, 192);
		Stand(0, 47, 41, 207);
		cout << (char)191;
		Stand(0, 29, 42, 12);
		cout << (char)16;
	}
	if (rownumber != 4) {
		Row(4, 4);
		Stand(0, 38, 42, 4);
		cout << "Exit\n\n\n";
	}
	int pause = 35;  //  визуальный эффект, при котором надписи пунктов показываются
	if (rownumber == 1) {        //не сразу, а буква за буквой
		Stand(0, 33, 24, 144);
		cout << "1 "; Sleep(pause); cout << "P"; Sleep(pause); cout << "l"; Sleep(pause); cout << "a"; Sleep(pause);
		cout << "y"; Sleep(pause); cout << "e"; Sleep(pause); cout << "r  "; Sleep(pause); cout << "G"; Sleep(pause);
		cout << "a"; Sleep(pause); cout << "m"; Sleep(pause); cout << "e";
	}
	if (rownumber == 2) {
		Stand(0, 33, 30, 224);
		cout << "2 "; Sleep(pause); cout << "P"; Sleep(pause); cout << "l"; Sleep(pause); cout << "a"; Sleep(pause);
		cout << "y"; Sleep(pause); cout << "e"; Sleep(pause); cout << "r"; Sleep(pause); cout << "s "; Sleep(pause);
		cout << "G"; Sleep(pause); cout << "a"; Sleep(pause); cout << "m"; Sleep(pause); cout << "e";
	}
	if (rownumber == 3) {
		Stand(0, 34, 36, 208);
		cout << "A"; Sleep(pause); cout << "b"; Sleep(pause); cout << "o"; Sleep(pause); cout << "u"; Sleep(pause);
		cout << "t "; Sleep(pause); cout << "S"; Sleep(pause); cout << "u"; Sleep(pause); cout << "d"; Sleep(pause);
		cout << "o"; Sleep(pause); cout << "k"; Sleep(pause); cout << "u ";
	}
	if (rownumber == 4) {
		Stand(0, 38, 42, 192);
		cout << "E"; Sleep(pause); cout << "x"; Sleep(pause); cout << "i"; Sleep(pause); cout << "t";
	}
	SetConsoleTextAttribute(H, 0);
}

void OnePlayerGame(int hard) {
	fortimer = 0; // включить (но не запустить) таймер
	srand(time(NULL));
	system("cls");  // очистить экран
	Massive();  //начать создание массива
	Stand(0, 18, 44, 4);  //перед созданием массива пустых клеток необходимо подождать,
	cout << "ONE PLAYER - ";                  // иначе могут быть созданы одинаковые массивы
	if (hard == 0) cout << "EASY";
	if (hard == 1) cout << "NORMAL";
	if (hard == 2) cout << "HARD";
	cout << " GAME. Loading, please wait...";
	Stand(0, 0, 47, 4);   // для этого добавляется  полоса загрузки 
	int set = 80;
	while (set--) {
		cout << (char)177;
		Sleep(40);
	}
	Stand(0, 0, 47, 0);
	DarkMassive(); // теперь можно создать массив пустых клеток
	Table(32, 13, 1);  //вывод на экран игрового поля 
	int XX = 33;
	int YY = 14;
	Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для показа 
	for (int i = 0; i < massivsize; i++) {                                 // массива
		SetConsoleCursorPosition(H, c);
		if (hard == 0) {
			if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4) mess[i] = 0;
		} // 4 клетки  в строке станут "пустыми" если уровень сложности лёгкий
		if (hard == 1) {
			if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4 || mess[i] == 5) mess[i] = 0;
		} // 5 клеток  в строке станут "пустыми" если  уровень сложности средний
		if (hard == 2) {
			if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4 || mess[i] == 5 || mess[i] == 6) mess[i] = 0;
		} // 6 клеток  в строке станут "пустыми" - если выбран высокий уровень сложности

		if (mess[i] == 0) {
			SetConsoleTextAttribute(H, 7);
			cout << " ";  // если mess[i] равно 0, клетка станет "пустой"
		}
		else {
			SetConsoleTextAttribute(H, 7); //в другом случае снова будет показан эл. mаss[i]
			cout << mass[i];
		}
		c.X += 2;
		if (i % 9 == 8) {  // переход на новую строку
			c.X = XX;
			c.Y += 2;
		}
	}
	int emptyblock = 0; // переменная хранит в себе количество "пустых" клеток
	for (int i = 0; i < massivsize; i++) {
		if (mess[i] == 0) emptyblock++;
	}
	int notemptyblock = 0; // переменная хранит в себе количество заполняемых клеток
	int go; // переменная будет хранить в себе код нажатой клавиши
	Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для начала 																	// игры
	CONSOLE_CURSOR_INFO cci;   // для удобства курсор будет отображаться на экране
	cci.bVisible = 100;
	cci.dwSize = 100;
	SetConsoleCursorInfo(H, &cci);
	gat1 = c.X;  // переменные хранят в себе 
	gat2 = c.Y;     // координаты курсора
	if (hard == 0) sec = 600;
	if (hard == 1) sec = 450;
	if (hard == 2) sec = 300;
	//CreateThread(0, 0, timerminus, (void*)&sec, 0, 0); // вызов функции таймера с передачей количества секунд
	int digit; // для удобства - нажатая цифра запишется в эту переменную
	int mist = 0;  // проверка на ошибки
	int summist = 0;  // количество ошибок
	int youcanplay = 1;  // если ошибок меньше 10 - пользователь может играть
	do {
		gat1 = c.X; // переменные хранят в себе 
		gat2 = c.Y;    // координаты курсора
		if (_kbhit() && sec > 0) {  // если пользователь среагировал 
			go = _getch();
			switch (go) {
			case 77: // вправо
				if (c.X + 2 <= 49) {
					c.X += 2;
					SetConsoleCursorPosition(H, c);
				}
				break;
			case 75: // влево
				if (c.X - 2 >= 33) {
					c.X -= 2;
					SetConsoleCursorPosition(H, c);
				}
				break;
			case 72: // вверх
				if (c.Y - 2 >= 14) {
					c.Y -= 2;
					SetConsoleCursorPosition(H, c);
				}
				break;
			case 80: //	вниз
				if (c.Y + 2 <= 30) {
					c.Y += 2;
					SetConsoleCursorPosition(H, c);
				}
				break;
			case 49: //	1
				digit = 1;
				break;
			case 50: //	2
				digit = 2;
				break;
			case 51: //	3
				digit = 3;
				break;
			case 52: //	4
				digit = 4;
				break;
			case 53: //	5
				digit = 5;
				break;
			case 54: //	6
				digit = 6;
				break;
			case 55: //	7
				digit = 7;
				break;
			case 56: //	8
				digit = 8;
				break;
			case 57: //	9
				digit = 9;
				break;
			case 32: //	если курсор "соскочит" с игрового поля, пробелом его можно вернуть его
				gat1 = 33;
				gat2 = 14;
				Stand(0, gat1, gat2, 7);
				break;
			case 27: // вернуться в main
				fortimer = 1;
				Stand(0, 5, 47, 7);
				cout << "Exit...";
				Sleep(1000);  // для остановки функции Timerminus желательно подождать 1 секунду
				main();
				break;
			}
			if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {
				SetConsoleTextAttribute(H, 10); // ниже следует проверка, можно ли поставить на выбранном месте цифру
				int controlthisdigit = 0; // если переменная изменится, будет показано число и количество заполненных клеток увеличится
				if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] == digit) { controlthisdigit = 1; mess[0] == 1; }
				if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] == digit) { controlthisdigit = 1; mess[1] == 1; }
				if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] == digit) { controlthisdigit = 1; mess[2] == 1; }
				if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] == digit) { controlthisdigit = 1; mess[3] == 1; }
				if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] == digit) { controlthisdigit = 1; mess[4] == 1; }
				if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] == digit) { controlthisdigit = 1; mess[5] == 1; }
				if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] == digit) { controlthisdigit = 1; mess[6] == 1; }
				if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] == digit) { controlthisdigit = 1; mess[7] == 1; }
				if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] == digit) { controlthisdigit = 1; mess[8] == 1; }
				if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] == digit) { controlthisdigit = 1; mess[9] == 1; }
				if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] == digit) { controlthisdigit = 1; mess[10] == 1; }
				if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] == digit) { controlthisdigit = 1; mess[11] == 1; }
				if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] == digit) { controlthisdigit = 1; mess[12] == 1; }
				if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] == digit) { controlthisdigit = 1; mess[13] == 1; }
				if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] == digit) { controlthisdigit = 1; mess[14] == 1; }
				if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] == digit) { controlthisdigit = 1; mess[15] == 1; }
				if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] == digit) { controlthisdigit = 1; mess[16] == 1; }
				if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] == digit) { controlthisdigit = 1; mess[17] == 1; }
				if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] == digit) { controlthisdigit = 1; mess[18] == 1; }
				if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] == digit) { controlthisdigit = 1; mess[19] == 1; }
				if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] == digit) { controlthisdigit = 1; mess[20] == 1; }
				if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] == digit) { controlthisdigit = 1; mess[21] == 1; }
				if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] == digit) { controlthisdigit = 1; mess[22] == 1; }
				if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] == digit) { controlthisdigit = 1; mess[23] == 1; }
				if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] == digit) { controlthisdigit = 1; mess[24] == 1; }
				if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] == digit) { controlthisdigit = 1; mess[25] == 1; }
				if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] == digit) { controlthisdigit = 1; mess[26] == 1; }
				if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] == digit) { controlthisdigit = 1; mess[27] == 1; }
				if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] == digit) { controlthisdigit = 1; mess[28] == 1; }
				if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] == digit) { controlthisdigit = 1; mess[29] == 1; }
				if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] == digit) { controlthisdigit = 1; mess[30] == 1; }
				if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] == digit) { controlthisdigit = 1; mess[31] == 1; }
				if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] == digit) { controlthisdigit = 1; mess[32] == 1; }
				if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] == digit) { controlthisdigit = 1; mess[33] == 1; }
				if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] == digit) { controlthisdigit = 1; mess[34] == 1; }
				if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] == digit) { controlthisdigit = 1; mess[35] == 1; }
				if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] == digit) { controlthisdigit = 1; mess[36] == 1; }
				if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] == digit) { controlthisdigit = 1; mess[37] == 1; }
				if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] == digit) { controlthisdigit = 1; mess[38] == 1; }
				if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] == digit) { controlthisdigit = 1; mess[39] == 1; }
				if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] == digit) { controlthisdigit = 1; mess[40] == 1; }
				if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] == digit) { controlthisdigit = 1; mess[41] == 1; }
				if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] == digit) { controlthisdigit = 1; mess[42] == 1; }
				if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] == digit) { controlthisdigit = 1; mess[43] == 1; }
				if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] == digit) { controlthisdigit = 1; mess[44] == 1; }
				if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] == digit) { controlthisdigit = 1; mess[45] == 1; }
				if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] == digit) { controlthisdigit = 1; mess[46] == 1; }
				if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] == digit) { controlthisdigit = 1; mess[47] == 1; }
				if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] == digit) { controlthisdigit = 1; mess[48] == 1; }
				if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] == digit) { controlthisdigit = 1; mess[49] == 1; }
				if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] == digit) { controlthisdigit = 1; mess[50] == 1; }
				if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] == digit) { controlthisdigit = 1; mess[51] == 1; }
				if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] == digit) { controlthisdigit = 1; mess[52] == 1; }
				if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] == digit) { controlthisdigit = 1; mess[53] == 1; }
				if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] == digit) { controlthisdigit = 1; mess[54] == 1; }
				if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] == digit) { controlthisdigit = 1; mess[55] == 1; }
				if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] == digit) { controlthisdigit = 1; mess[56] == 1; }
				if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] == digit) { controlthisdigit = 1; mess[57] == 1; }
				if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] == digit) { controlthisdigit = 1; mess[58] == 1; }
				if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] == digit) { controlthisdigit = 1; mess[59] == 1; }
				if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] == digit) { controlthisdigit = 1; mess[60] == 1; }
				if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] == digit) { controlthisdigit = 1; mess[61] == 1; }
				if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] == digit) { controlthisdigit = 1; mess[62] == 1; }
				if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] == digit) { controlthisdigit = 1; mess[63] == 1; }
				if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] == digit) { controlthisdigit = 1; mess[64] == 1; }
				if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] == digit) { controlthisdigit = 1; mess[65] == 1; }
				if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] == digit) { controlthisdigit = 1; mess[66] == 1; }
				if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] == digit) { controlthisdigit = 1; mess[67] == 1; }
				if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] == digit) { controlthisdigit = 1; mess[68] == 1; }
				if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] == digit) { controlthisdigit = 1; mess[69] == 1; }
				if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] == digit) { controlthisdigit = 1; mess[70] == 1; }
				if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] == digit) { controlthisdigit = 1; mess[71] == 1; }
				if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] == digit) { controlthisdigit = 1; mess[72] == 1; }
				if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] == digit) { controlthisdigit = 1; mess[73] == 1; }
				if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] == digit) { controlthisdigit = 1; mess[74] == 1; }
				if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] == digit) { controlthisdigit = 1; mess[75] == 1; }
				if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] == digit) { controlthisdigit = 1; mess[76] == 1; }
				if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] == digit) { controlthisdigit = 1; mess[77] == 1; }
				if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] == digit) { controlthisdigit = 1; mess[78] == 1; }
				if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] == digit) { controlthisdigit = 1; mess[79] == 1; }
				if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] == digit) { controlthisdigit = 1; mess[80] == 1; }

				if (controlthisdigit == 1) {
					cout << digit;
					notemptyblock++;
				}
				SetConsoleCursorPosition(H, c); // возвратить курсор на место показанного числа
			}
			if (go != 49 && go != 50 && go != 51 && go != 52 && go != 53 && go != 54 && go != 55 && go != 56 && go != 57 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224 && go != 32) {  // если пользователь вводит не цифры
				int COORDX = c.X, COORDY = c.Y;
				Stand(0, 24, 34, 12);
				cout << "Not correct. You must input digits!";  // показать предупреждающую надпись
				Stand(500, 24, 34, 0);
				cout << "Not correct. You must input digits!";  // убрать предупреждающую надпись
				Stand(0, COORDX, COORDY, 7);
			}
			if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {  // проверка на ошибки
				mist = 0;
				if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] != digit) mist = 1;
				if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] != digit) mist = 1;
				if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] != digit) mist = 1;
				if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] != digit) mist = 1;
				if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] != digit) mist = 1;
				if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] != digit) mist = 1;
				if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] != digit) mist = 1;
				if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] != digit) mist = 1;
				if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] != digit) mist = 1;
				if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] != digit) mist = 1;
				if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] != digit) mist = 1;
				if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] != digit) mist = 1;
				if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] != digit) mist = 1;
				if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] != digit) mist = 1;
				if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] != digit) mist = 1;
				if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] != digit) mist = 1;
				if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] != digit) mist = 1;
				if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] != digit) mist = 1;
				if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] != digit) mist = 1;
				if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] != digit) mist = 1;
				if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] != digit) mist = 1;
				if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] != digit) mist = 1;
				if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] != digit) mist = 1;
				if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] != digit) mist = 1;
				if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] != digit) mist = 1;
				if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] != digit) mist = 1;
				if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] != digit) mist = 1;
				if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] != digit) mist = 1;
				if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] != digit) mist = 1;
				if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] != digit) mist = 1;
				if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] != digit) mist = 1;
				if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] != digit) mist = 1;
				if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] != digit) mist = 1;
				if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] != digit) mist = 1;
				if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] != digit) mist = 1;
				if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] != digit) mist = 1;
				if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] != digit) mist = 1;
				if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] != digit) mist = 1;
				if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] != digit) mist = 1;
				if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] != digit) mist = 1;
				if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] != digit) mist = 1;
				if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] != digit) mist = 1;
				if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] != digit) mist = 1;
				if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] != digit) mist = 1;
				if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] != digit) mist = 1;
				if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] != digit) mist = 1;
				if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] != digit) mist = 1;
				if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] != digit) mist = 1;
				if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] != digit) mist = 1;
				if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] != digit) mist = 1;
				if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] != digit) mist = 1;
				if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] != digit) mist = 1;
				if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] != digit) mist = 1;
				if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] != digit) mist = 1;
				if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] != digit) mist = 1;
				if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] != digit) mist = 1;
				if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] != digit) mist = 1;
				if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] != digit) mist = 1;
				if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] != digit) mist = 1;
				if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] != digit) mist = 1;
				if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] != digit) mist = 1;
				if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] != digit) mist = 1;
				if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] != digit) mist = 1;
				if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] != digit) mist = 1;
				if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] != digit) mist = 1;
				if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] != digit) mist = 1;
				if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] != digit) mist = 1;
				if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] != digit) mist = 1;
				if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] != digit) mist = 1;
				if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] != digit) mist = 1;
				if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] != digit) mist = 1;
				if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] != digit) mist = 1;
				if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] != digit) mist = 1;
				if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] != digit) mist = 1;
				if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] != digit) mist = 1;
				if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] != digit) mist = 1;
				if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] != digit) mist = 1;
				if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] != digit) mist = 1;
				if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] != digit) mist = 1;
				if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] != digit) mist = 1;
				if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] != digit) mist = 1;
			}
			if (mist == 1 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224) {
				int COORDX = c.X, COORDY = c.Y;
				Stand(0, 30, 34, 12);
				cout << "Mistake!!! Wrong digit!";  // если ошибка была, об этом сообщается пользователю
				Stand(500, 30, 34, 0);
				cout << "Mistake!!! Wrong digit!";
				Stand(30, COORDX, COORDY, 7);
				summist++;
			}
			if (summist == 10) youcanplay = 0;  // если допущено 10 ошибок - игра окончена
		}
	} while (emptyblock != notemptyblock && sec != 0 && youcanplay == 1);
	fortimer = 1; // если закончилось время, или допущено 10 ошибок, или заполнены все клетки - таймер останавливается 
	if (emptyblock == notemptyblock) {  // показать таблицу рекордов
		char oneplname[255];  // c помощью этой переменной можно записать имя игрока
		Stand(0, 0, 0, 0);
		const int widthfhs = 80;  // массив, кот. рисует цветные огоньки
		const int heightfhs = 49;
		int tablefhs[widthfhs][heightfhs];
		int cfhs; // особый цвет огонька
		for (int i = 0; i < widthfhs; i++) {
			for (int j = 0; j < heightfhs; j++) {
				int colorfhs = rand() % 200;  // это быстрый способ создания нескольких огоньков на чёрном фоне
				if (colorfhs != 1 && colorfhs != 2 && colorfhs != 3 && colorfhs != 4 && colorfhs != 5) cfhs = 0;
				if (colorfhs == 1) cfhs = 10;  // определение цвета огонька
				if (colorfhs == 2) cfhs = 12;
				if (colorfhs == 3) cfhs = 9;
				if (colorfhs == 4) cfhs = 14;
				if (colorfhs == 5) cfhs = 15;
				SetConsoleTextAttribute(H, cfhs);
				tablefhs[i][j] = 249; // маленькая точка
				cout << (char)tablefhs[i][j];
			}
			cout << "\n";
		}
		Stand(0, 18, 24, 0);    //  очистить место рядом с надписью поздравления
		cout << "\t\t\t\t\t";
		Stand(0, 20, 25, 4);
		cout << "Greetings! Please, enter your name:\t\t";
		Stand(0, 18, 26, 0);
		cout << "\t\t\t\t\t";
		Stand(0, 56, 25, 12);
		//FillConsoleOutputAttribute(H, 12, 1, c, 0);
		cin >> oneplname; // записать имя игрока
		system("cls");
		CONSOLE_CURSOR_INFO cci;
		cci.bVisible = 0;      //курсор становится невидимым
		cci.dwSize = 100;
		SetConsoleCursorInfo(H, &cci);
		CreateThread(0, 0, hsm, 0, 0, 0); // включить музыку 
		Stand(0, 36, 25, 12);
		cout << "HIGHSCORE";
		Stand(0, 23, 28, 8);
		cout << "NAME    LEVEL    TIME    MIS-S    POINTS"; // оформление таблицы рекордов
		Stand(0, 19, 31, 4);
		cout << "1.";
		Stand(0, 19, 33, 6);
		cout << "2.";
		Stand(0, 19, 35, 2);
		cout << "3.";
		Stand(0, 19, 37, 1);
		cout << "4.";
		Stand(0, 19, 39, 5);
		cout << "5.";
		int level_hard = hard + 1;
		int ss;
		int secfortable;
		if (hard == 0) {
			secfortable = 600 - sec;
			ss = 600 - secfortable;
		}
		if (hard == 1) {
			secfortable = 450 - sec;
			ss = 450 - secfortable;
		}
		if (hard == 2) {
			secfortable = 300 - sec;
			ss = 300 - secfortable;
		}
		int finish = (10 - summist) * ss * level_hard; // формула, по которой вычисляется количество очков
		if (finish > 5900) {            // 1  место - очков больше 5900
			Stand(0, 23, 31, 12);
			cout << oneplname;
			Stand(0, 31, 31, 12);
			if (hard == 0) cout << "EASY";
			if (hard == 1) cout << "NORMAL";
			if (hard == 2) cout << "HARD";
			int s = secfortable % 60;
			int m = secfortable / 60;
			Stand(0, 40, 31, 12);
			if (secfortable < 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable < 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			if (secfortable >= 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable >= 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			Stand(0, 50, 31, 12);
			cout << summist;
			Stand(0, 58, 31, 12);
			cout << finish;
			Stand(0, 23, 33, 14);
			cout << "Master  HARD     3:59      0       5900";
			Stand(0, 23, 35, 10);
			cout << "Spec#1  NORMAL   4:43      5       3472";
			Stand(0, 23, 37, 9);
			cout << "Cheat   HARD     2:00      9       2820";
			Stand(0, 23, 39, 13);
			cout << "Looser  EASY     9:59      9          1";
		}
		if (finish <= 5900 && finish > 3472) {    // 2  место - очков больше 3472
			Stand(0, 23, 33, 14);
			cout << oneplname;
			Stand(0, 31, 33, 14);
			if (hard == 0) cout << "EASY";
			if (hard == 1) cout << "NORMAL";
			if (hard == 2) cout << "HARD";
			int s = secfortable % 60;
			int m = secfortable / 60;
			Stand(0, 40, 33, 14);
			if (secfortable < 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable < 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			if (secfortable >= 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable >= 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			Stand(0, 50, 33, 14);
			cout << summist;
			Stand(0, 58, 33, 14);
			cout << finish;
			Stand(0, 23, 31, 12);
			cout << "Master  HARD     3:59      0       5900";
			Stand(0, 23, 35, 10);
			cout << "Spec#1  NORMAL   4:43      5       3472";
			Stand(0, 23, 37, 9);
			cout << "Cheat   HARD     2:00      9       2820";
			Stand(0, 23, 39, 13);
			cout << "Looser  EASY     9:59      9          1";
		}
		if (finish > 2820 && finish <= 3472) {    // 3  место - очков больше 2820
			Stand(0, 23, 35, 10);
			cout << oneplname;
			Stand(0, 31, 35, 10);
			if (hard == 0) cout << "EASY";
			if (hard == 1) cout << "NORMAL";
			if (hard == 2) cout << "HARD";
			int s = secfortable % 60;
			int m = secfortable / 60;
			Stand(0, 40, 35, 10);
			if (secfortable < 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable < 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			if (secfortable >= 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable >= 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			Stand(0, 50, 35, 10);
			cout << summist;
			Stand(0, 58, 35, 10);
			cout << finish;
			Stand(0, 23, 31, 12);
			cout << "Master  HARD     3:59      0       5900";
			Stand(0, 23, 33, 14);
			cout << "Spec#1  NORMAL   4:43      5       3472";
			Stand(0, 23, 37, 9);
			cout << "Cheat   HARD     2:00      9       2820";
			Stand(0, 23, 39, 13);
			cout << "Looser  EASY     9:59      9          1";
		}
		if (finish <= 2820 && finish >= 1) {    // 4  место - очков больше 1
			Stand(0, 23, 37, 9);
			cout << oneplname;
			Stand(0, 31, 37, 9);
			if (hard == 0) cout << "EASY";
			if (hard == 1) cout << "NORMAL";
			if (hard == 2) cout << "HARD";
			int s = secfortable % 60;
			int m = secfortable / 60;
			Stand(0, 40, 37, 9);
			if (secfortable < 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable < 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			if (secfortable >= 600 && secfortable % 60 < 10) cout << m << ":0" << s;
			if (secfortable >= 600 && secfortable % 60 >= 10) cout << m << ":" << s;
			Stand(0, 50, 37, 9);
			cout << summist;
			if (finish >= 1000) Stand(0, 58, 37, 9);
			else Stand(0, 59, 37, 9);
			cout << finish;
			Stand(0, 23, 31, 12);
			cout << "Master  HARD     3:59      0       5900";
			Stand(0, 23, 33, 14);
			cout << "Spec#1  NORMAL   4:43      5       3472";
			Stand(0, 23, 35, 10);
			cout << "Cheat   HARD     2:00      9       2820";
			Stand(0, 23, 39, 13);
			cout << "Looser  EASY     9:59      9          1";
		}  // предположительно, последнее место пользователь не может занять
		sec = 13;
		CreateThread(0, 0, primitivetimer, (void*)&sec, 0, 0);
		while (sec != 0) { // мигающая надпись
			srand(time(0));
			int tsvet = rand() % 16;
			ShockHead(218, tsvet);  // супер анимация на таблице рекордов
			tsvet = rand() % 15 + 1;
			ShockHead(191, tsvet);
			tsvet = rand() % 15 + 1;
			ShockHead(217, tsvet);
			tsvet = rand() % 15 + 1;
			ShockHead(192, tsvet);
		}
		sec = 1; // необходимо изменить значение количества секунд, чтобы не сработало завершение игры
	}
	if (youcanplay == 0 || sec == 0) {  // игра окончена, если закончилось время или допущено 10 ошибок
		system("cls");
		CreateThread(0, 0, gameoverm, 0, 0, 0);
		Stand(0, 36, 22, 12);
		cout << "GAME OVER!";
		Stand(0, 33, 25, 4);
		cout << "Time:";
		Stand(0, 33, 27, 4);
		cout << "Input:";
		Stand(0, 33, 29, 4);
		cout << "Empty:";
		Stand(0, 33, 31, 4);
		cout << "Mistakes:";
		///////////////////// показ времени
		int secfortable;
		if (hard == 0) secfortable = 600 - sec;
		if (hard == 1) secfortable = 450 - sec;
		if (hard == 2) secfortable = 300 - sec;
		int s = secfortable % 60;
		int m = secfortable / 60;
		Stand(0, 44, 25, 9);
		if (secfortable < 600 && secfortable % 60 < 10) cout << "0" << m << ":0" << s;
		if (secfortable < 600 && secfortable % 60 >= 10) cout << "0" << m << ":" << s;
		if (secfortable >= 600 && secfortable % 60 < 10) cout << m << ":0" << s;
		if (secfortable >= 600 && secfortable % 60 >= 10) cout << m << ":" << s;
		/////////////////////// показ количества заполненных клеток
		if (notemptyblock < 10) Stand(0, 48, 27, 9);
		else Stand(0, 47, 27, 9);
		cout << notemptyblock;
		///////////////////// показ количества незаполненных клеток
		if (emptyblock - notemptyblock < 10) Stand(0, 48, 29, 9);
		else Stand(0, 47, 29, 9);
		cout << emptyblock - notemptyblock;
		///////////////////// показ количества ошибок
		if (summist < 10) Stand(0, 48, 31, 9);
		else Stand(0, 47, 31, 9);
		cout << summist;

		CONSOLE_CURSOR_INFO cci;
		cci.bVisible = 0;   //курсор становится невидимым
		cci.dwSize = 100;
		SetConsoleCursorInfo(H, &cci);

		int Linesleep = 5;  // бегущая строка
		sec = 8; // в течение 8 секунд будет изображение на экране, а затем - возврат в главное меню
		CreateThread(0, 0, primitivetimer, (void*)&sec, 0, 0);
		while (sec != 0) { // мигающая надпись
			Stand(Linesleep, 0, 1, 2);
			cout << "SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUD";
			Stand(Linesleep, 0, 48, 2);
			cout << " SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SU";
			Stand(Linesleep, 0, 1, 2);
			cout << "UDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDO";
			Stand(Linesleep, 0, 48, 2);
			cout << "* SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** S";
			Stand(Linesleep, 0, 1, 2);
			cout << "DOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOK";
			Stand(Linesleep, 0, 48, 2);
			cout << "** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** ";
			Stand(Linesleep, 0, 1, 2);
			cout << "OKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU";
			Stand(Linesleep, 0, 48, 2);
			cout << "*** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU ***";
			Stand(Linesleep, 0, 1, 2);
			cout << "KU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU ";
			Stand(Linesleep, 0, 48, 2);
			cout << " *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU **";
			Stand(Linesleep, 0, 1, 2);
			cout << "U *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *";
			Stand(Linesleep, 0, 48, 2);
			cout << "U *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *";
			Stand(Linesleep, 0, 1, 2);
			cout << " *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU **";
			Stand(Linesleep, 0, 48, 2);
			cout << "KU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU ";
			Stand(Linesleep, 0, 1, 2);
			cout << "*** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU ***";
			Stand(Linesleep, 0, 48, 2);
			cout << "OKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU";
			Stand(Linesleep, 0, 1, 2);
			cout << "** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** ";
			Stand(Linesleep, 0, 48, 2);
			cout << "DOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOK";
			Stand(Linesleep, 0, 1, 2);
			cout << "* SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** S";
			Stand(Linesleep, 0, 48, 2);
			cout << "UDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDO";
			Stand(Linesleep, 0, 1, 2);
			cout << " SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SU";
			Stand(Linesleep, 0, 48, 2);
			cout << "SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUDOKU *** SUD";
		}
	}
	main();
}

void TwoPlayersGame(int hard) {
	system("cls");
	Massive();  //начать создание массива #1
	CONSOLE_CURSOR_INFO cci;   // для удобства курсор будет отображаться на экране
	cci.bVisible = 100;
	cci.dwSize = 100;
	SetConsoleCursorInfo(H, &cci);
	Stand(0, 10, 5, 4);  // приветственное сообщение
	cout << "Welcome to the game, Player 1!";
	Stand(0, 10, 7, 4);
	cout << "Please, enter your name:";
	Stand(0, 35, 7, 12);
	cin >> name1;
	Massive_2();  //начать создание массива #2
	Stand(0, 10, 10, 1);
	cout << "Welcome to the game, Player 2!";
	Stand(0, 10, 12, 1);
	cout << "Please, enter your name:";
	Stand(0, 35, 12, 9);
	cin >> name2;
	DarkMassive(); //создать массив пустых клеток #1
	fortimer = 0; // включить (но не запустить) таймер
	srand(time(NULL));
	Stand(0, 7, 44, 4);  //перед созданием массива пустых клеток необходимо подождать,
	cout << name1 << " vs " << name2 << " - TWO PLAYERS - ";  // иначе могут быть созданы одинаковые массивы
	if (hard == 0) cout << "EASY";
	if (hard == 1) cout << "NORMAL";
	if (hard == 2) cout << "HARD";
	cout << " GAME. Loading, please wait...";
	Stand(0, 0, 47, 4);   // для этого добавляется  полоса загрузки 
	cci.bVisible = 0;    // курсор не будет отображаться на экране
	cci.dwSize = 100;
	SetConsoleCursorInfo(H, &cci);
	int set = 80;
	while (set--) {
		cout << (char)177;
		Sleep(40);
	}
	DarkMassive_2(); // создать массив пустых клеток #2
	cci.bVisible = 100;   // сделать курсор видимым
	cci.dwSize = 100;
	SetConsoleCursorInfo(H, &cci);
	int emptyblock; // переменная хранит в себе количество "пустых" клеток игрока№1
	int notemptyblock = 0;   // переменная хранит в себе количество заполняемых клеток игрока№1
	int emptyblock2; // переменная хранит в себе количество "пустых" клеток игрока№1
	int notemptyblock2 = 0;   // переменная хранит в себе количество заполняемых клеток игрока№1
	if (hard == 0) {
		emptyblock = 36;   // количество пустых клеток на лёгком уровне
		emptyblock2 = 36;   // количество пустых клеток на лёгком уровне
	}
	if (hard == 1) {
		emptyblock = 45;   // количество пустых клеток на среднем уровне
		emptyblock2 = 45;   // количество пустых клеток на среднем уровне
	}
	if (hard == 2) {
		emptyblock = 54;   // количество пустых клеток на тяжёлом уровне
		emptyblock2 = 54;   // количество пустых клеток на тяжёлом уровне
	}
	int summist = 0;  // количество ошибок игрока№1
	int summist2 = 0;  // количество ошибок игрока№2
	int shadow1 = 1;  // переменные используются для однократного выяснения пустых клеток
	int shadow2 = 1;
	do {
		int pressent;
		do {
			system("cls");
			cci.bVisible = 0;
			cci.dwSize = 100;
			SetConsoleCursorInfo(H, &cci);
			Stand(0, 30, 11, 14);
			cout << name1 << "! Press enter to start!";
			Sleep(500);
			pressent = _getch();
			switch (pressent) {
			case 27:
				main();
			case 13:
				sec = 10;
				cci.bVisible = 100;
				cci.dwSize = 100;
				SetConsoleCursorInfo(H, &cci);
				Table(32, 13, 4);  //вывод на экран игрового поля 
				fortimer = 0;
				//CreateThread(0, 0, timerminus, (void*)&sec, 0, 0); // вызов функции таймера с передачей количества секунд
				Sleep(15);
				int XX = 33;
				int YY = 14;
				Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для показа 
				for (int i = 0; i < massivsize; i++) {
					SetConsoleCursorPosition(H, c);
					if (shadow1 == 1) {
						if (hard == 0) {
							if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4) mess[i] = 0;
						} // 4 клетки  в строке станут "пустыми" если уровень сложности лёгкий
						if (hard == 1) {
							if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4 || mess[i] == 5) mess[i] = 0;
						} // 5 клеток  в строке станут "пустыми" если  уровень сложности средний
						if (hard == 2) {
							if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4 || mess[i] == 5 || mess[i] == 6) mess[i] = 0;
						} // 6 клеток  в строке станут "пустыми" - если выбран высокий уровень сложности 
					}
					if (mess[i] == 0) {
						SetConsoleTextAttribute(H, 7);
						cout << " ";  // если mess[i] равно 0, клетка станет "пустой"
					}
					else {
						SetConsoleTextAttribute(H, 7); //в другом случае снова будет показан эл. mаss[i]
						cout << mass[i];
					}
					c.X += 2;
					if (i % 9 == 8) {  // переход на новую строку
						c.X = XX;
						c.Y += 2;
					}
				}
				int go; // переменная будет хранить в себе код нажатой клавиши
				Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для начала игры
				cci.bVisible = 100;   // для удобства курсор будет отображаться на экране
				cci.dwSize = 100;
				SetConsoleCursorInfo(H, &cci);
				gat1 = c.X;  // переменные хранят в себе 
				gat2 = c.Y;     // координаты курсора

				int digit; // для удобства - нажатая цифра запишется в эту переменную
				int mist = 0;  // проверка на ошибки

				do {
					gat1 = c.X; // переменные хранят в себе 
					gat2 = c.Y;    // координаты курсора
					if (_kbhit() && sec > 0) {  // если пользователь среагировал 
						go = _getch();
						switch (go) {
						case 77: // вправо
							if (c.X + 2 <= 49) {
								c.X += 2;
								SetConsoleCursorPosition(H, c);
							}
							break;
						case 75: // влево
							if (c.X - 2 >= 33) {
								c.X -= 2;
								SetConsoleCursorPosition(H, c);
							}
							break;
						case 72: // вверх
							if (c.Y - 2 >= 14) {
								c.Y -= 2;
								SetConsoleCursorPosition(H, c);
							}
							break;
						case 80: //	вниз
							if (c.Y + 2 <= 30) {
								c.Y += 2;
								SetConsoleCursorPosition(H, c);
							}
							break;
						case 49: //	1
							digit = 1;
							break;
						case 50: //	2
							digit = 2;
							break;
						case 51: //	3
							digit = 3;
							break;
						case 52: //	4
							digit = 4;
							break;
						case 53: //	5
							digit = 5;
							break;
						case 54: //	6
							digit = 6;
							break;
						case 55: //	7
							digit = 7;
							break;
						case 56: //	8
							digit = 8;
							break;
						case 57: //	9
							digit = 9;
							break;
						case 32: //	если курсор "соскочит" с игрового поля, пробелом его можно вернуть 
							gat1 = 33;
							gat2 = 14;
							Stand(0, gat1, gat2, 7);
							break;
						case 27: // вернуться в main
							cci.bVisible = 0;
							cci.dwSize = 100;
							SetConsoleCursorInfo(H, &cci);
							fortimer = 1;
							Stand(0, 5, 47, 7);
							cout << "Exit...";
							Sleep(1000);  // для остановки функции Timerminus желательно подождать 1 секунду
							main();
							break;
						}
						cci.bVisible = 0;
						cci.dwSize = 100;
						SetConsoleCursorInfo(H, &cci);
						if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {
							SetConsoleTextAttribute(H, 10); // ниже следует проверка, можно ли поставить на выбранном месте цифру
							int controlthisdigit = 0; // если переменная изменится, будет показано число и количество заполненных клеток увеличится
							if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] == digit) { controlthisdigit = 1; mess[0] = 9; }
							if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] == digit) { controlthisdigit = 1; mess[1] = 9; }
							if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] == digit) { controlthisdigit = 1; mess[2] = 9; }
							if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] == digit) { controlthisdigit = 1; mess[3] = 9; }
							if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] == digit) { controlthisdigit = 1; mess[4] = 9; }
							if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] == digit) { controlthisdigit = 1; mess[5] = 9; }
							if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] == digit) { controlthisdigit = 1; mess[6] = 9; }
							if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] == digit) { controlthisdigit = 1; mess[7] = 9; }
							if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] == digit) { controlthisdigit = 1; mess[8] = 9; }
							if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] == digit) { controlthisdigit = 1; mess[9] = 9; }
							if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] == digit) { controlthisdigit = 1; mess[10] = 9; }
							if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] == digit) { controlthisdigit = 1; mess[11] = 9; }
							if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] == digit) { controlthisdigit = 1; mess[12] = 9; }
							if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] == digit) { controlthisdigit = 1; mess[13] = 9; }
							if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] == digit) { controlthisdigit = 1; mess[14] = 9; }
							if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] == digit) { controlthisdigit = 1; mess[15] = 9; }
							if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] == digit) { controlthisdigit = 1; mess[16] = 9; }
							if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] == digit) { controlthisdigit = 1; mess[17] = 9; }
							if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] == digit) { controlthisdigit = 1; mess[18] = 9; }
							if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] == digit) { controlthisdigit = 1; mess[19] = 9; }
							if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] == digit) { controlthisdigit = 1; mess[20] = 9; }
							if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] == digit) { controlthisdigit = 1; mess[21] = 9; }
							if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] == digit) { controlthisdigit = 1; mess[22] = 9; }
							if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] == digit) { controlthisdigit = 1; mess[23] = 9; }
							if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] == digit) { controlthisdigit = 1; mess[24] = 9; }
							if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] == digit) { controlthisdigit = 1; mess[25] = 9; }
							if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] == digit) { controlthisdigit = 1; mess[26] = 9; }
							if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] == digit) { controlthisdigit = 1; mess[27] = 9; }
							if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] == digit) { controlthisdigit = 1; mess[28] = 9; }
							if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] == digit) { controlthisdigit = 1; mess[29] = 9; }
							if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] == digit) { controlthisdigit = 1; mess[30] = 9; }
							if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] == digit) { controlthisdigit = 1; mess[31] = 9; }
							if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] == digit) { controlthisdigit = 1; mess[32] = 9; }
							if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] == digit) { controlthisdigit = 1; mess[33] = 9; }
							if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] == digit) { controlthisdigit = 1; mess[34] = 9; }
							if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] == digit) { controlthisdigit = 1; mess[35] = 9; }
							if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] == digit) { controlthisdigit = 1; mess[36] = 9; }
							if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] == digit) { controlthisdigit = 1; mess[37] = 9; }
							if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] == digit) { controlthisdigit = 1; mess[38] = 9; }
							if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] == digit) { controlthisdigit = 1; mess[39] = 9; }
							if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] == digit) { controlthisdigit = 1; mess[40] = 9; }
							if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] == digit) { controlthisdigit = 1; mess[41] = 9; }
							if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] == digit) { controlthisdigit = 1; mess[42] = 9; }
							if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] == digit) { controlthisdigit = 1; mess[43] = 9; }
							if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] == digit) { controlthisdigit = 1; mess[44] = 9; }
							if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] == digit) { controlthisdigit = 1; mess[45] = 9; }
							if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] == digit) { controlthisdigit = 1; mess[46] = 9; }
							if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] == digit) { controlthisdigit = 1; mess[47] = 9; }
							if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] == digit) { controlthisdigit = 1; mess[48] = 9; }
							if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] == digit) { controlthisdigit = 1; mess[49] = 9; }
							if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] == digit) { controlthisdigit = 1; mess[50] = 9; }
							if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] == digit) { controlthisdigit = 1; mess[51] = 9; }
							if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] == digit) { controlthisdigit = 1; mess[52] = 9; }
							if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] == digit) { controlthisdigit = 1; mess[53] = 9; }
							if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] == digit) { controlthisdigit = 1; mess[54] = 9; }
							if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] == digit) { controlthisdigit = 1; mess[55] = 9; }
							if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] == digit) { controlthisdigit = 1; mess[56] = 9; }
							if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] == digit) { controlthisdigit = 1; mess[57] = 9; }
							if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] == digit) { controlthisdigit = 1; mess[58] = 9; }
							if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] == digit) { controlthisdigit = 1; mess[59] = 9; }
							if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] == digit) { controlthisdigit = 1; mess[60] = 9; }
							if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] == digit) { controlthisdigit = 1; mess[61] = 9; }
							if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] == digit) { controlthisdigit = 1; mess[62] = 9; }
							if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] == digit) { controlthisdigit = 1; mess[63] = 9; }
							if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] == digit) { controlthisdigit = 1; mess[64] = 9; }
							if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] == digit) { controlthisdigit = 1; mess[65] = 9; }
							if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] == digit) { controlthisdigit = 1; mess[66] = 9; }
							if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] == digit) { controlthisdigit = 1; mess[67] = 9; }
							if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] == digit) { controlthisdigit = 1; mess[68] = 9; }
							if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] == digit) { controlthisdigit = 1; mess[69] = 9; }
							if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] == digit) { controlthisdigit = 1; mess[70] = 9; }
							if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] == digit) { controlthisdigit = 1; mess[71] = 9; }
							if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] == digit) { controlthisdigit = 1; mess[72] = 9; }
							if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] == digit) { controlthisdigit = 1; mess[73] = 9; }
							if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] == digit) { controlthisdigit = 1; mess[74] = 9; }
							if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] == digit) { controlthisdigit = 1; mess[75] = 9; }
							if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] == digit) { controlthisdigit = 1; mess[76] = 9; }
							if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] == digit) { controlthisdigit = 1; mess[77] = 9; }
							if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] == digit) { controlthisdigit = 1; mess[78] = 9; }
							if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] == digit) { controlthisdigit = 1; mess[79] = 9; }
							if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] == digit) { controlthisdigit = 1; mess[80] = 9; }

							if (controlthisdigit == 1) {
								cout << digit;
								notemptyblock++;
							}
							SetConsoleCursorPosition(H, c); // возвратить курсор на место показанного числа
						}
						cci.bVisible = 0;
						cci.dwSize = 100;
						SetConsoleCursorInfo(H, &cci);
						if (go != 49 && go != 50 && go != 51 && go != 52 && go != 53 && go != 54 && go != 55 && go != 56 && go != 57 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224 && go != 32) {  // если пользователь вводит не цифры
							int COORDX = c.X, COORDY = c.Y;
							Stand(0, 24, 34, 12);
							cout << "Not correct. You must input digits!";  // показать предупреждающую надпись
							Stand(500, 24, 34, 0);
							cout << "Not correct. You must input digits!";  // убрать предупреждающую надпись
							Stand(0, COORDX, COORDY, 7);
						}
						if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {  // проверка на ошибки
							mist = 0;
							if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] != digit) mist = 1;
							if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] != digit) mist = 1;
							if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] != digit) mist = 1;
							if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] != digit) mist = 1;
							if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] != digit) mist = 1;
							if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] != digit) mist = 1;
							if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] != digit) mist = 1;
							if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] != digit) mist = 1;
							if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] != digit) mist = 1;
							if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] != digit) mist = 1;
							if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] != digit) mist = 1;
							if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] != digit) mist = 1;
							if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] != digit) mist = 1;
							if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] != digit) mist = 1;
							if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] != digit) mist = 1;
							if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] != digit) mist = 1;
							if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] != digit) mist = 1;
							if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] != digit) mist = 1;
							if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] != digit) mist = 1;
							if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] != digit) mist = 1;
							if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] != digit) mist = 1;
							if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] != digit) mist = 1;
							if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] != digit) mist = 1;
							if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] != digit) mist = 1;
							if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] != digit) mist = 1;
							if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] != digit) mist = 1;
							if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] != digit) mist = 1;
							if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] != digit) mist = 1;
							if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] != digit) mist = 1;
							if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] != digit) mist = 1;
							if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] != digit) mist = 1;
							if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] != digit) mist = 1;
							if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] != digit) mist = 1;
							if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] != digit) mist = 1;
							if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] != digit) mist = 1;
							if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] != digit) mist = 1;
							if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] != digit) mist = 1;
							if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] != digit) mist = 1;
							if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] != digit) mist = 1;
							if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] != digit) mist = 1;
							if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] != digit) mist = 1;
							if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] != digit) mist = 1;
							if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] != digit) mist = 1;
							if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] != digit) mist = 1;
							if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] != digit) mist = 1;
							if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] != digit) mist = 1;
							if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] != digit) mist = 1;
							if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] != digit) mist = 1;
							if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] != digit) mist = 1;
							if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] != digit) mist = 1;
							if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] != digit) mist = 1;
							if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] != digit) mist = 1;
							if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] != digit) mist = 1;
							if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] != digit) mist = 1;
							if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] != digit) mist = 1;
							if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] != digit) mist = 1;
							if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] != digit) mist = 1;
							if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] != digit) mist = 1;
							if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] != digit) mist = 1;
							if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] != digit) mist = 1;
							if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] != digit) mist = 1;
							if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] != digit) mist = 1;
							if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] != digit) mist = 1;
							if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] != digit) mist = 1;
							if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] != digit) mist = 1;
							if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] != digit) mist = 1;
							if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] != digit) mist = 1;
							if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] != digit) mist = 1;
							if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] != digit) mist = 1;
							if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] != digit) mist = 1;
							if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] != digit) mist = 1;
							if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] != digit) mist = 1;
							if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] != digit) mist = 1;
							if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] != digit) mist = 1;
							if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] != digit) mist = 1;
							if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] != digit) mist = 1;
							if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] != digit) mist = 1;
							if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] != digit) mist = 1;
							if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] != digit) mist = 1;
							if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] != digit) mist = 1;
							if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] != digit) mist = 1;
						}
						if (mist == 1 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224) {
							int COORDX = c.X, COORDY = c.Y;
							Stand(0, 30, 34, 12);
							cout << "Mistake!!! Wrong digit!";  // если ошибка была, об этом сообщается пользователю
							Stand(500, 30, 34, 0);
							cout << "Mistake!!! Wrong digit!";
							Stand(30, COORDX, COORDY, 7);
							summist++;
						}
						cci.bVisible = 100;
						cci.dwSize = 100;
						SetConsoleCursorInfo(H, &cci);

					}
				} while (emptyblock != notemptyblock && sec != 0 && summist != 10);
				fortimer = 1; // если закончилось время, или допущено 10 ошибок, или заполнены все клетки - таймер останавливается 
				Sleep(1000);
			}
		} while (pressent != 13 && pressent != 27 && emptyblock != notemptyblock && sec != 0 && summist != 10);
		shadow1 = 0;  // больше не показывать старые пустые клетки
		if (summist != 10 && emptyblock != notemptyblock) {
			do {
				system("cls");
				cci.bVisible = 0;
				cci.dwSize = 100;
				SetConsoleCursorInfo(H, &cci);
				Stand(0, 30, 11, 10);
				cout << name2 << "! Press enter to start!";
				Sleep(500);
				pressent = _getch();
				switch (pressent) {
				case 27:
					main();
				case 13:
					sec = 10;
					cci.bVisible = 100;
					cci.dwSize = 100;
					SetConsoleCursorInfo(H, &cci);
					Table(32, 13, 1);  //вывод на экран игрового поля 
					fortimer = 0;
					CreateThread(0, 0, timerminus, (void*)&sec, 0, 0); // вызов функции таймера с передачей количества секунд
					Sleep(15);
					int XX = 33;
					int YY = 14;
					Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для показа  массива
					for (int i = 0; i < massivsize; i++) {
						SetConsoleCursorPosition(H, c);
						if (shadow2 == 1) {  // показать пустые клетки только один раз
							if (hard == 0) {
								if (dame[i] == 1 || dame[i] == 2 || dame[i] == 3 || dame[i] == 4) dame[i] = 0;
							} // 4 клетки  в строке станут "пустыми" если уровень сложности лёгкий
							if (hard == 1) {
								if (dame[i] == 1 || dame[i] == 2 || dame[i] == 3 || dame[i] == 4 || dame[i] == 5) dame[i] = 0;
							} // 5 клеток  в строке станут "пустыми" если  уровень сложности средний
							if (hard == 2) {
								if (dame[i] == 1 || dame[i] == 2 || dame[i] == 3 || dame[i] == 4 || dame[i] == 5 || dame[i] == 6) dame[i] = 0;
							} // 6 клеток  в строке станут "пустыми" - если выбран высокий уровень сложности
						}
						if (dame[i] == 0) {
							SetConsoleTextAttribute(H, 7);
							cout << " ";  // если dame[i] равно 0, клетка станет "пустой"
						}
						else {
							SetConsoleTextAttribute(H, 7); //в другом случае снова будет показан эл. 
							cout << most[i];
						}
						c.X += 2;
						if (i % 9 == 8) {  // переход на новую строку
							c.X = XX;
							c.Y += 2;
						}
					}
					int go; // переменная будет хранить в себе код нажатой клавиши
					Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для начала игры
					cci.bVisible = 100;   // для удобства курсор будет отображаться на экране
					cci.dwSize = 100;
					SetConsoleCursorInfo(H, &cci);
					gat1 = c.X;  // переменные хранят в себе 
					gat2 = c.Y;     // координаты курсора
					int digit; // для удобства - нажатая цифра запишется в эту переменную
					int mist = 0;  // проверка на ошибки
					int youcanplay = 1;  // если ошибок меньше 10 - пользователь может играть
					do {
						gat1 = c.X; // переменные хранят в себе 
						gat2 = c.Y;    // координаты курсора
						if (_kbhit() && sec > 0) {  // если пользователь среагировал 
							go = _getch();
							switch (go) {
							case 77: // вправо
								if (c.X + 2 <= 49) {
									c.X += 2;
									SetConsoleCursorPosition(H, c);
								}
								break;
							case 75: // влево
								if (c.X - 2 >= 33) {
									c.X -= 2;
									SetConsoleCursorPosition(H, c);
								}
								break;
							case 72: // вверх
								if (c.Y - 2 >= 14) {
									c.Y -= 2;
									SetConsoleCursorPosition(H, c);
								}
								break;
							case 80: //	вниз
								if (c.Y + 2 <= 30) {
									c.Y += 2;
									SetConsoleCursorPosition(H, c);
								}
								break;
							case 49: //	1
								digit = 1;
								break;
							case 50: //	2
								digit = 2;
								break;
							case 51: //	3
								digit = 3;
								break;
							case 52: //	4
								digit = 4;
								break;
							case 53: //	5
								digit = 5;
								break;
							case 54: //	6
								digit = 6;
								break;
							case 55: //	7
								digit = 7;
								break;
							case 56: //	8
								digit = 8;
								break;
							case 57: //	9
								digit = 9;
								break;
							case 32: //	если курсор "соскочит" с игрового поля, пробелом его можно вернуть его
								gat1 = 33;
								gat2 = 14;
								Stand(0, gat1, gat2, 7);
								break;
							case 27: // вернуться в main
								cci.bVisible = 0;
								cci.dwSize = 100;
								SetConsoleCursorInfo(H, &cci);
								fortimer = 1;
								Stand(0, 5, 47, 7);
								cout << "Exit...";
								Sleep(1000);  // для остановки функции Timerminus желательно подождать 1 секунду
								main();
								break;
							}
							if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {
								SetConsoleTextAttribute(H, 10); // ниже следует проверка, можно ли поставить на выбранном месте цифру
								int controlthisdigit = 0; // если переменная изменится, будет показано число и количество заполненных клеток увеличится
								if (c.X == 33 && c.Y == 14 && dame[0] == 0 && most[0] == digit) { controlthisdigit = 1; dame[0] = 9; }
								if (c.X == 35 && c.Y == 14 && dame[1] == 0 && most[1] == digit) { controlthisdigit = 1; dame[1] = 9; }
								if (c.X == 37 && c.Y == 14 && dame[2] == 0 && most[2] == digit) { controlthisdigit = 1; dame[2] = 9; }
								if (c.X == 39 && c.Y == 14 && dame[3] == 0 && most[3] == digit) { controlthisdigit = 1; dame[3] = 9; }
								if (c.X == 41 && c.Y == 14 && dame[4] == 0 && most[4] == digit) { controlthisdigit = 1; dame[4] = 9; }
								if (c.X == 43 && c.Y == 14 && dame[5] == 0 && most[5] == digit) { controlthisdigit = 1; dame[5] = 9; }
								if (c.X == 45 && c.Y == 14 && dame[6] == 0 && most[6] == digit) { controlthisdigit = 1; dame[6] = 9; }
								if (c.X == 47 && c.Y == 14 && dame[7] == 0 && most[7] == digit) { controlthisdigit = 1; dame[7] = 9; }
								if (c.X == 49 && c.Y == 14 && dame[8] == 0 && most[8] == digit) { controlthisdigit = 1; dame[8] = 9; }
								if (c.X == 33 && c.Y == 16 && dame[9] == 0 && most[9] == digit) { controlthisdigit = 1; dame[9] = 9; }
								if (c.X == 35 && c.Y == 16 && dame[10] == 0 && most[10] == digit) { controlthisdigit = 1; dame[10] = 9; }
								if (c.X == 37 && c.Y == 16 && dame[11] == 0 && most[11] == digit) { controlthisdigit = 1; dame[11] = 9; }
								if (c.X == 39 && c.Y == 16 && dame[12] == 0 && most[12] == digit) { controlthisdigit = 1; dame[12] = 9; }
								if (c.X == 41 && c.Y == 16 && dame[13] == 0 && most[13] == digit) { controlthisdigit = 1; dame[13] = 9; }
								if (c.X == 43 && c.Y == 16 && dame[14] == 0 && most[14] == digit) { controlthisdigit = 1; dame[14] = 9; }
								if (c.X == 45 && c.Y == 16 && dame[15] == 0 && most[15] == digit) { controlthisdigit = 1; dame[15] = 9; }
								if (c.X == 47 && c.Y == 16 && dame[16] == 0 && most[16] == digit) { controlthisdigit = 1; dame[16] = 9; }
								if (c.X == 49 && c.Y == 16 && dame[17] == 0 && most[17] == digit) { controlthisdigit = 1; dame[17] = 9; }
								if (c.X == 33 && c.Y == 18 && dame[18] == 0 && most[18] == digit) { controlthisdigit = 1; dame[18] = 9; }
								if (c.X == 35 && c.Y == 18 && dame[19] == 0 && most[19] == digit) { controlthisdigit = 1; dame[19] = 9; }
								if (c.X == 37 && c.Y == 18 && dame[20] == 0 && most[20] == digit) { controlthisdigit = 1; dame[20] = 9; }
								if (c.X == 39 && c.Y == 18 && dame[21] == 0 && most[21] == digit) { controlthisdigit = 1; dame[21] = 9; }
								if (c.X == 41 && c.Y == 18 && dame[22] == 0 && most[22] == digit) { controlthisdigit = 1; dame[22] = 9; }
								if (c.X == 43 && c.Y == 18 && dame[23] == 0 && most[23] == digit) { controlthisdigit = 1; dame[23] = 9; }
								if (c.X == 45 && c.Y == 18 && dame[24] == 0 && most[24] == digit) { controlthisdigit = 1; dame[24] = 9; }
								if (c.X == 47 && c.Y == 18 && dame[25] == 0 && most[25] == digit) { controlthisdigit = 1; dame[25] = 9; }
								if (c.X == 49 && c.Y == 18 && dame[26] == 0 && most[26] == digit) { controlthisdigit = 1; dame[26] = 9; }
								if (c.X == 33 && c.Y == 20 && dame[27] == 0 && most[27] == digit) { controlthisdigit = 1; dame[27] = 9; }
								if (c.X == 35 && c.Y == 20 && dame[28] == 0 && most[28] == digit) { controlthisdigit = 1; dame[28] = 9; }
								if (c.X == 37 && c.Y == 20 && dame[29] == 0 && most[29] == digit) { controlthisdigit = 1; dame[29] = 9; }
								if (c.X == 39 && c.Y == 20 && dame[30] == 0 && most[30] == digit) { controlthisdigit = 1; dame[30] = 9; }
								if (c.X == 41 && c.Y == 20 && dame[31] == 0 && most[31] == digit) { controlthisdigit = 1; dame[31] = 9; }
								if (c.X == 43 && c.Y == 20 && dame[32] == 0 && most[32] == digit) { controlthisdigit = 1; dame[32] = 9; }
								if (c.X == 45 && c.Y == 20 && dame[33] == 0 && most[33] == digit) { controlthisdigit = 1; dame[33] = 9; }
								if (c.X == 47 && c.Y == 20 && dame[34] == 0 && most[34] == digit) { controlthisdigit = 1; dame[34] = 9; }
								if (c.X == 49 && c.Y == 20 && dame[35] == 0 && most[35] == digit) { controlthisdigit = 1; dame[35] = 9; }
								if (c.X == 33 && c.Y == 22 && dame[36] == 0 && most[36] == digit) { controlthisdigit = 1; dame[36] = 9; }
								if (c.X == 35 && c.Y == 22 && dame[37] == 0 && most[37] == digit) { controlthisdigit = 1; dame[37] = 9; }
								if (c.X == 37 && c.Y == 22 && dame[38] == 0 && most[38] == digit) { controlthisdigit = 1; dame[38] = 9; }
								if (c.X == 39 && c.Y == 22 && dame[39] == 0 && most[39] == digit) { controlthisdigit = 1; dame[39] = 9; }
								if (c.X == 41 && c.Y == 22 && dame[40] == 0 && most[40] == digit) { controlthisdigit = 1; dame[40] = 9; }
								if (c.X == 43 && c.Y == 22 && dame[41] == 0 && most[41] == digit) { controlthisdigit = 1; dame[41] = 9; }
								if (c.X == 45 && c.Y == 22 && dame[42] == 0 && most[42] == digit) { controlthisdigit = 1; dame[42] = 9; }
								if (c.X == 47 && c.Y == 22 && dame[43] == 0 && most[43] == digit) { controlthisdigit = 1; dame[43] = 9; }
								if (c.X == 49 && c.Y == 22 && dame[44] == 0 && most[44] == digit) { controlthisdigit = 1; dame[44] = 9; }
								if (c.X == 33 && c.Y == 24 && dame[45] == 0 && most[45] == digit) { controlthisdigit = 1; dame[45] = 9; }
								if (c.X == 35 && c.Y == 24 && dame[46] == 0 && most[46] == digit) { controlthisdigit = 1; dame[46] = 9; }
								if (c.X == 37 && c.Y == 24 && dame[47] == 0 && most[47] == digit) { controlthisdigit = 1; dame[47] = 9; }
								if (c.X == 39 && c.Y == 24 && dame[48] == 0 && most[48] == digit) { controlthisdigit = 1; dame[48] = 9; }
								if (c.X == 41 && c.Y == 24 && dame[49] == 0 && most[49] == digit) { controlthisdigit = 1; dame[49] = 9; }
								if (c.X == 43 && c.Y == 24 && dame[50] == 0 && most[50] == digit) { controlthisdigit = 1; dame[50] = 9; }
								if (c.X == 45 && c.Y == 24 && dame[51] == 0 && most[51] == digit) { controlthisdigit = 1; dame[51] = 9; }
								if (c.X == 47 && c.Y == 24 && dame[52] == 0 && most[52] == digit) { controlthisdigit = 1; dame[52] = 9; }
								if (c.X == 49 && c.Y == 24 && dame[53] == 0 && most[53] == digit) { controlthisdigit = 1; dame[53] = 9; }
								if (c.X == 33 && c.Y == 26 && dame[54] == 0 && most[54] == digit) { controlthisdigit = 1; dame[54] = 9; }
								if (c.X == 35 && c.Y == 26 && dame[55] == 0 && most[55] == digit) { controlthisdigit = 1; dame[55] = 9; }
								if (c.X == 37 && c.Y == 26 && dame[56] == 0 && most[56] == digit) { controlthisdigit = 1; dame[56] = 9; }
								if (c.X == 39 && c.Y == 26 && dame[57] == 0 && most[57] == digit) { controlthisdigit = 1; dame[57] = 9; }
								if (c.X == 41 && c.Y == 26 && dame[58] == 0 && most[58] == digit) { controlthisdigit = 1; dame[58] = 9; }
								if (c.X == 43 && c.Y == 26 && dame[59] == 0 && most[59] == digit) { controlthisdigit = 1; dame[59] = 9; }
								if (c.X == 45 && c.Y == 26 && dame[60] == 0 && most[60] == digit) { controlthisdigit = 1; dame[60] = 9; }
								if (c.X == 47 && c.Y == 26 && dame[61] == 0 && most[61] == digit) { controlthisdigit = 1; dame[61] = 9; }
								if (c.X == 49 && c.Y == 26 && dame[62] == 0 && most[62] == digit) { controlthisdigit = 1; dame[62] = 9; }
								if (c.X == 33 && c.Y == 28 && dame[63] == 0 && most[63] == digit) { controlthisdigit = 1; dame[63] = 9; }
								if (c.X == 35 && c.Y == 28 && dame[64] == 0 && most[64] == digit) { controlthisdigit = 1; dame[64] = 9; }
								if (c.X == 37 && c.Y == 28 && dame[65] == 0 && most[65] == digit) { controlthisdigit = 1; dame[65] = 9; }
								if (c.X == 39 && c.Y == 28 && dame[66] == 0 && most[66] == digit) { controlthisdigit = 1; dame[66] = 9; }
								if (c.X == 41 && c.Y == 28 && dame[67] == 0 && most[67] == digit) { controlthisdigit = 1; dame[67] = 9; }
								if (c.X == 43 && c.Y == 28 && dame[68] == 0 && most[68] == digit) { controlthisdigit = 1; dame[68] = 9; }
								if (c.X == 45 && c.Y == 28 && dame[69] == 0 && most[69] == digit) { controlthisdigit = 1; dame[69] = 9; }
								if (c.X == 47 && c.Y == 28 && dame[70] == 0 && most[70] == digit) { controlthisdigit = 1; dame[70] = 9; }
								if (c.X == 49 && c.Y == 28 && dame[71] == 0 && most[71] == digit) { controlthisdigit = 1; dame[71] = 9; }
								if (c.X == 33 && c.Y == 30 && dame[72] == 0 && most[72] == digit) { controlthisdigit = 1; dame[72] = 9; }
								if (c.X == 35 && c.Y == 30 && dame[73] == 0 && most[73] == digit) { controlthisdigit = 1; dame[73] = 9; }
								if (c.X == 37 && c.Y == 30 && dame[74] == 0 && most[74] == digit) { controlthisdigit = 1; dame[74] = 9; }
								if (c.X == 39 && c.Y == 30 && dame[75] == 0 && most[75] == digit) { controlthisdigit = 1; dame[75] = 9; }
								if (c.X == 41 && c.Y == 30 && dame[76] == 0 && most[76] == digit) { controlthisdigit = 1; dame[76] = 9; }
								if (c.X == 43 && c.Y == 30 && dame[77] == 0 && most[77] == digit) { controlthisdigit = 1; dame[77] = 9; }
								if (c.X == 45 && c.Y == 30 && dame[78] == 0 && most[78] == digit) { controlthisdigit = 1; dame[78] = 9; }
								if (c.X == 47 && c.Y == 30 && dame[79] == 0 && most[79] == digit) { controlthisdigit = 1; dame[79] = 9; }
								if (c.X == 49 && c.Y == 30 && dame[80] == 0 && most[80] == digit) { controlthisdigit = 1; dame[80] = 9; }

								if (controlthisdigit == 1) {
									cout << digit;
									notemptyblock2++;
								}
								SetConsoleCursorPosition(H, c); // возвратить курсор на место показанного числа
							}
							cci.bVisible = 0;
							cci.dwSize = 100;
							SetConsoleCursorInfo(H, &cci);
							if (go != 49 && go != 50 && go != 51 && go != 52 && go != 53 && go != 54 && go != 55 && go != 56 && go != 57 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224 && go != 32) {  // если пользователь вводит не цифры
								int COORDX = c.X, COORDY = c.Y;
								Stand(0, 24, 34, 12);
								cout << "Not correct. You must input digits!";  // показать предупреждающую надпись
								Stand(500, 24, 34, 0);
								cout << "Not correct. You must input digits!";  // убрать предупреждающую надпись
								Stand(0, COORDX, COORDY, 7);
							}
							if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {  // проверка на ошибки
								mist = 0;
								if (c.X == 33 && c.Y == 14 && dame[0] == 0 && most[0] != digit) mist = 1;
								if (c.X == 35 && c.Y == 14 && dame[1] == 0 && most[1] != digit) mist = 1;
								if (c.X == 37 && c.Y == 14 && dame[2] == 0 && most[2] != digit) mist = 1;
								if (c.X == 39 && c.Y == 14 && dame[3] == 0 && most[3] != digit) mist = 1;
								if (c.X == 41 && c.Y == 14 && dame[4] == 0 && most[4] != digit) mist = 1;
								if (c.X == 43 && c.Y == 14 && dame[5] == 0 && most[5] != digit) mist = 1;
								if (c.X == 45 && c.Y == 14 && dame[6] == 0 && most[6] != digit) mist = 1;
								if (c.X == 47 && c.Y == 14 && dame[7] == 0 && most[7] != digit) mist = 1;
								if (c.X == 49 && c.Y == 14 && dame[8] == 0 && most[8] != digit) mist = 1;
								if (c.X == 33 && c.Y == 16 && dame[9] == 0 && most[9] != digit) mist = 1;
								if (c.X == 35 && c.Y == 16 && dame[10] == 0 && most[10] != digit) mist = 1;
								if (c.X == 37 && c.Y == 16 && dame[11] == 0 && most[11] != digit) mist = 1;
								if (c.X == 39 && c.Y == 16 && dame[12] == 0 && most[12] != digit) mist = 1;
								if (c.X == 41 && c.Y == 16 && dame[13] == 0 && most[13] != digit) mist = 1;
								if (c.X == 43 && c.Y == 16 && dame[14] == 0 && most[14] != digit) mist = 1;
								if (c.X == 45 && c.Y == 16 && dame[15] == 0 && most[15] != digit) mist = 1;
								if (c.X == 47 && c.Y == 16 && dame[16] == 0 && most[16] != digit) mist = 1;
								if (c.X == 49 && c.Y == 16 && dame[17] == 0 && most[17] != digit) mist = 1;
								if (c.X == 33 && c.Y == 18 && dame[18] == 0 && most[18] != digit) mist = 1;
								if (c.X == 35 && c.Y == 18 && dame[19] == 0 && most[19] != digit) mist = 1;
								if (c.X == 37 && c.Y == 18 && dame[20] == 0 && most[20] != digit) mist = 1;
								if (c.X == 39 && c.Y == 18 && dame[21] == 0 && most[21] != digit) mist = 1;
								if (c.X == 41 && c.Y == 18 && dame[22] == 0 && most[22] != digit) mist = 1;
								if (c.X == 43 && c.Y == 18 && dame[23] == 0 && most[23] != digit) mist = 1;
								if (c.X == 45 && c.Y == 18 && dame[24] == 0 && most[24] != digit) mist = 1;
								if (c.X == 47 && c.Y == 18 && dame[25] == 0 && most[25] != digit) mist = 1;
								if (c.X == 49 && c.Y == 18 && dame[26] == 0 && most[26] != digit) mist = 1;
								if (c.X == 33 && c.Y == 20 && dame[27] == 0 && most[27] != digit) mist = 1;
								if (c.X == 35 && c.Y == 20 && dame[28] == 0 && most[28] != digit) mist = 1;
								if (c.X == 37 && c.Y == 20 && dame[29] == 0 && most[29] != digit) mist = 1;
								if (c.X == 39 && c.Y == 20 && dame[30] == 0 && most[30] != digit) mist = 1;
								if (c.X == 41 && c.Y == 20 && dame[31] == 0 && most[31] != digit) mist = 1;
								if (c.X == 43 && c.Y == 20 && dame[32] == 0 && most[32] != digit) mist = 1;
								if (c.X == 45 && c.Y == 20 && dame[33] == 0 && most[33] != digit) mist = 1;
								if (c.X == 47 && c.Y == 20 && dame[34] == 0 && most[34] != digit) mist = 1;
								if (c.X == 49 && c.Y == 20 && dame[35] == 0 && most[35] != digit) mist = 1;
								if (c.X == 33 && c.Y == 22 && dame[36] == 0 && most[36] != digit) mist = 1;
								if (c.X == 35 && c.Y == 22 && dame[37] == 0 && most[37] != digit) mist = 1;
								if (c.X == 37 && c.Y == 22 && dame[38] == 0 && most[38] != digit) mist = 1;
								if (c.X == 39 && c.Y == 22 && dame[39] == 0 && most[39] != digit) mist = 1;
								if (c.X == 41 && c.Y == 22 && dame[40] == 0 && most[40] != digit) mist = 1;
								if (c.X == 43 && c.Y == 22 && dame[41] == 0 && most[41] != digit) mist = 1;
								if (c.X == 45 && c.Y == 22 && dame[42] == 0 && most[42] != digit) mist = 1;
								if (c.X == 47 && c.Y == 22 && dame[43] == 0 && most[43] != digit) mist = 1;
								if (c.X == 49 && c.Y == 22 && dame[44] == 0 && most[44] != digit) mist = 1;
								if (c.X == 33 && c.Y == 24 && dame[45] == 0 && most[45] != digit) mist = 1;
								if (c.X == 35 && c.Y == 24 && dame[46] == 0 && most[46] != digit) mist = 1;
								if (c.X == 37 && c.Y == 24 && dame[47] == 0 && most[47] != digit) mist = 1;
								if (c.X == 39 && c.Y == 24 && dame[48] == 0 && most[48] != digit) mist = 1;
								if (c.X == 41 && c.Y == 24 && dame[49] == 0 && most[49] != digit) mist = 1;
								if (c.X == 43 && c.Y == 24 && dame[50] == 0 && most[50] != digit) mist = 1;
								if (c.X == 45 && c.Y == 24 && dame[51] == 0 && most[51] != digit) mist = 1;
								if (c.X == 47 && c.Y == 24 && dame[52] == 0 && most[52] != digit) mist = 1;
								if (c.X == 49 && c.Y == 24 && dame[53] == 0 && most[53] != digit) mist = 1;
								if (c.X == 33 && c.Y == 26 && dame[54] == 0 && most[54] != digit) mist = 1;
								if (c.X == 35 && c.Y == 26 && dame[55] == 0 && most[55] != digit) mist = 1;
								if (c.X == 37 && c.Y == 26 && dame[56] == 0 && most[56] != digit) mist = 1;
								if (c.X == 39 && c.Y == 26 && dame[57] == 0 && most[57] != digit) mist = 1;
								if (c.X == 41 && c.Y == 26 && dame[58] == 0 && most[58] != digit) mist = 1;
								if (c.X == 43 && c.Y == 26 && dame[59] == 0 && most[59] != digit) mist = 1;
								if (c.X == 45 && c.Y == 26 && dame[60] == 0 && most[60] != digit) mist = 1;
								if (c.X == 47 && c.Y == 26 && dame[61] == 0 && most[61] != digit) mist = 1;
								if (c.X == 49 && c.Y == 26 && dame[62] == 0 && most[62] != digit) mist = 1;
								if (c.X == 33 && c.Y == 28 && dame[63] == 0 && most[63] != digit) mist = 1;
								if (c.X == 35 && c.Y == 28 && dame[64] == 0 && most[64] != digit) mist = 1;
								if (c.X == 37 && c.Y == 28 && dame[65] == 0 && most[65] != digit) mist = 1;
								if (c.X == 39 && c.Y == 28 && dame[66] == 0 && most[66] != digit) mist = 1;
								if (c.X == 41 && c.Y == 28 && dame[67] == 0 && most[67] != digit) mist = 1;
								if (c.X == 43 && c.Y == 28 && dame[68] == 0 && most[68] != digit) mist = 1;
								if (c.X == 45 && c.Y == 28 && dame[69] == 0 && most[69] != digit) mist = 1;
								if (c.X == 47 && c.Y == 28 && dame[70] == 0 && most[70] != digit) mist = 1;
								if (c.X == 49 && c.Y == 28 && dame[71] == 0 && most[71] != digit) mist = 1;
								if (c.X == 33 && c.Y == 30 && dame[72] == 0 && most[72] != digit) mist = 1;
								if (c.X == 35 && c.Y == 30 && dame[73] == 0 && most[73] != digit) mist = 1;
								if (c.X == 37 && c.Y == 30 && dame[74] == 0 && most[74] != digit) mist = 1;
								if (c.X == 39 && c.Y == 30 && dame[75] == 0 && most[75] != digit) mist = 1;
								if (c.X == 41 && c.Y == 30 && dame[76] == 0 && most[76] != digit) mist = 1;
								if (c.X == 43 && c.Y == 30 && dame[77] == 0 && most[77] != digit) mist = 1;
								if (c.X == 45 && c.Y == 30 && dame[78] == 0 && most[78] != digit) mist = 1;
								if (c.X == 47 && c.Y == 30 && dame[79] == 0 && most[79] != digit) mist = 1;
								if (c.X == 49 && c.Y == 30 && dame[80] == 0 && most[80] != digit) mist = 1;
							}
							if (mist == 1 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224) {
								int COORDX = c.X, COORDY = c.Y;
								Stand(0, 30, 34, 12);
								cout << "Mistake!!! Wrong digit!";  // если ошибка была, об этом сообщается пользователю
								Stand(500, 30, 34, 0); cout << "Mistake!!! Wrong digit!";
								Stand(30, COORDX, COORDY, 7); summist2++;
							}
							cci.bVisible = 100; cci.dwSize = 100; SetConsoleCursorInfo(H, &cci);
							if (summist2 == 10) youcanplay = 0;  // если допущено 10 ошибок - игра окончена
						}
					} while (emptyblock != notemptyblock && sec != 0 && youcanplay == 1 && emptyblock2 != notemptyblock2);

					fortimer = 1; // если закончилось время, или допущено 10 ошибок, или заполнены все клетки - таймер останавливается 
					Sleep(1000);
				}
			} while (pressent != 13 && pressent != 27 && emptyblock2 != notemptyblock2 && sec != 0);
		}
		shadow2 = 0;
	} while (emptyblock != notemptyblock && emptyblock2 != notemptyblock2 && summist != 10 && summist2 != 10);
	Stand(0, 0, 0, 0);
	const int widthfhs = 80;  // массив, кот. рисует цветные огоньки
	const int heightfhs = 49;
	int tablefhs[widthfhs][heightfhs];
	int cfhs; // особый цвет огонька
	for (int i = 0; i < widthfhs; i++) {
		for (int j = 0; j < heightfhs; j++) {
			int colorfhs = rand() % 200;  // это быстрый способ создания нескольких огоньков на чёрном фоне
			if (colorfhs != 1 && colorfhs != 2 && colorfhs != 3 && colorfhs != 4 && colorfhs != 5) cfhs = 0;
			if (colorfhs == 1) cfhs = 10;  // определение цвета огонька
			if (colorfhs == 2) cfhs = 12;
			if (colorfhs == 3) cfhs = 9;
			if (colorfhs == 4) cfhs = 14;
			if (colorfhs == 5) cfhs = 15;
			SetConsoleTextAttribute(H, cfhs);
			tablefhs[i][j] = 249; // точечки
			cout << (char)tablefhs[i][j];
		}
		cout << "\n";
	}
	Stand(0, 18, 24, 0);    // очистить место рядом с надписью поздравления
	cout << "\t\t\t\t\t";

	if (summist == 10 || emptyblock2 == notemptyblock2) {
		Stand(0, 33, 25, 9); cout << name2 << " win!";
	}
	if (summist2 == 10 || emptyblock == notemptyblock) {
		Stand(0, 33, 25, 12); cout << name1 << " win!";
	}
	Stand(0, 18, 26, 0); cout << "\t\t\t\t\t";
	cci.bVisible = 0; cci.dwSize = 100; SetConsoleCursorInfo(H, &cci);
	sec = 7; CreateThread(0, 0, primitivetimer, (void*)&sec, 0, 0);
	int sound = 200;
	while (sec != 0) { // мигающая надпись
		int colorit = rand() % 16;  // случайного цвета
		Stand(0, 33, 25, colorit);
		if (summist == 10 || emptyblock2 == notemptyblock2) cout << name2 << " win!";
		if (summist2 == 10 || emptyblock == notemptyblock) cout << name1 << " win!";
		Beep(sound, 15);  //  и звучок хроматический также добавляется
		sound += 4;
	}
	Beep(sound, 1500); main();
}

void Hardness(int xam, int yam, int strelcolor, int play) { //функция фиксирует выбранный 
	int mark = 62;                        //режим игры и уровень сложности, а затем переходит
	Stand(0, xam, yam, strelcolor);    //к функции, непосредственно реализующей игру
	cout << (char)26;
	SetConsoleTextAttribute(H, 7);
	cout << " Select level of hardness:";//меню сложности позволяет выбрать уровень сложности
	Stand(0, xam + 10, yam + 2, 6); cout << "Easy";
	Stand(0, xam + 10, yam + 4, 8); cout << "Normal";
	Stand(0, xam + 10, yam + 6, 14); cout << "Hard";
	Stand(0, xam + 8, yam + 2, 12); cout << (char)mark;
	Stand(0, 5, 47, 0);
	//FillConsoleOutputAttribute(H, 0, 79, c, 0);
	Stand(0, 5, 47, 7); cout << "Easy";
	int fix = 0, fax;
	do {
		fax = _getch();
		switch (fax) {
		case 72:          //уровень сложности выбирается переключением клавиш 'вверх' и 
			fix--;                                                            // 'вниз'
			if (fix == 0) {
				Stand(0, xam + 8, yam + 4, 0); cout << " ";
				Stand(0, xam + 8, yam + 2, 12); cout << (char)mark;
				Stand(0, 5, 47, 0);
				//FillConsoleOutputAttribute(H, 0, 79, c, 0);
				Stand(0, 5, 47, 7); cout << "Easy";  //строка снизу также показывает уровень игры
			}
			if (fix == 1) {
				Stand(0, xam + 8, yam + 6, 0); cout << " ";
				Stand(0, xam + 8, yam + 4, 12); cout << (char)mark;
				Stand(0, 5, 47, 0);
				//FillConsoleOutputAttribute(H, 0, 79, c, 0);
				Stand(0, 5, 47, 7); cout << "Normal";  //строка снизу также показывает уровень игры
			}
			if (fix < 0) fix = 0;
			break;
		case 80:
			fix++;
			if (fix == 1) {
				Stand(0, xam + 8, yam + 2, 0); cout << " ";
				Stand(0, xam + 8, yam + 4, 12); cout << (char)mark;
				Stand(0, 5, 47, 0);
				//FillConsoleOutputAttribute(H, 0, 79, c, 0);
				Stand(0, 5, 47, 7); cout << "Normal";  //строка снизу также показывает уровень игры
			}
			if (fix == 2) {
				Stand(0, xam + 8, yam + 4, 0); cout << " ";
				Stand(0, xam + 8, yam + 6, 12); cout << (char)mark;
				Stand(0, 5, 47, 0);
				//FillConsoleOutputAttribute(H, 0, 79, c, 0);
				Stand(0, 5, 47, 7); cout << "Hard";  //строка снизу также показывает уровень игры
			}
			if (fix > 2) fix = 2;
			break;
		case 27:   //если нажать 'Escape', произойдёт возврат в главное меню
			main();
			break;
		case 13:  //при нажатии клавиши 'Enter' начнёт работу следующая функция:
			if (fix == 0 && play == 1) OnePlayerGame(0);   //одиночная игра   (легко)
			if (fix == 0 && play == 2) TwoPlayersGame(0);  //  2 игрока       (легко)
			if (fix == 1 && play == 1) OnePlayerGame(1);   //одиночная игра  (нормально)
			if (fix == 1 && play == 2) TwoPlayersGame(1);  //  2 игрока      (нормально)
			if (fix == 2 && play == 1) OnePlayerGame(2);   //одиночная игра   (трудно)
			if (fix == 2 && play == 2) TwoPlayersGame(2);  //  2 игрока       (трудно)
			break;
		}
	} while (fax != 27 && fax != 13);
}

void Massive() {
	srand(time(NULL));
	int yes = 0; // если условия истинны, эта переменная равна 1, ели хоть одно станет ложным - 0
	int koll = 0;  // переменная хранит в себе количество выполненных условий
	for (int i = 0; i < massivsize; i++) {
		mass[i] = rand() % 9 + 1;  // заполнить текущий элемент случайным значением

		if (i % 9 == 8 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3] || mass[i] == mass[i - 4] || mass[i] == mass[i - 5] || mass[i] == mass[i - 6] || mass[i] == mass[i - 7] || mass[i] == mass[i - 8])) yes = 1;
		if (i % 9 == 7 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3] || mass[i] == mass[i - 4] || mass[i] == mass[i - 5] || mass[i] == mass[i - 6] || mass[i] == mass[i - 7])) yes = 1;
		if (i % 9 == 6 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3] || mass[i] == mass[i - 4] || mass[i] == mass[i - 5] || mass[i] == mass[i - 6])) yes = 1;
		if (i % 9 == 5 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3] || mass[i] == mass[i - 4] || mass[i] == mass[i - 5])) yes = 1;
		if (i % 9 == 4 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3] || mass[i] == mass[i - 4])) yes = 1;
		if (i % 9 == 3 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2] || mass[i] == mass[i - 3])) yes = 1;
		if (i % 9 == 2 && (mass[i] == mass[i - 1] || mass[i] == mass[i - 2])) yes = 1;
		if (i % 9 == 1 && (mass[i] == mass[i - 1])) yes = 1; // сравниваются элементы в строке, если два
		//элемента будут равны, осуществится один шаг назад по циклу
		if ((i % 27 == 9 || i % 27 == 12 || i % 27 == 15) && (mass[i] == mass[i - 9] || mass[i] == mass[i - 8] || mass[i] == mass[i - 7])) yes = 1; //сравниваются элементы поля 3х3: например, 9-ый элемент с 0, 1 и 2.
		if ((i % 27 == 10 || i % 27 == 13 || i % 27 == 16) && (mass[i] == mass[i - 10] || mass[i] == mass[i - 9] || mass[i] == mass[i - 8])) yes = 1; //сравниваются элементы поля 3х3: например, 10-ый элемент с 0, 1 и 2.
		if ((i % 27 == 11 || i % 27 == 14 || i % 27 == 17) && (mass[i] == mass[i - 11] || mass[i] == mass[i - 10] || mass[i] == mass[i - 9])) yes = 1; //сравниваются элементы поля 3х3: например, 11-ый элемент с 0, 1 и 2.

		if ((i % 27 == 18 || i % 27 == 21 || i % 27 == 24) && (mass[i] == mass[i - 9] || mass[i] == mass[i - 8] || mass[i] == mass[i - 7] || mass[i] == mass[i - 18] || mass[i] == mass[i - 17] || mass[i] == mass[i - 16])) yes = 1; //сравниваются элементы поля 3х3: например, 18-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 19 || i % 27 == 22 || i % 27 == 25) && (mass[i] == mass[i - 10] || mass[i] == mass[i - 9] || mass[i] == mass[i - 8] || mass[i] == mass[i - 19] || mass[i] == mass[i - 18] || mass[i] == mass[i - 17])) yes = 1; //сравниваются элементы поля 3х3: например, 19-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 20 || i % 27 == 23 || i % 27 == 26) && (mass[i] == mass[i - 11] || mass[i] == mass[i - 10] || mass[i] == mass[i - 9] || mass[i] == mass[i - 20] || mass[i] == mass[i - 19] || mass[i] == mass[i - 18])) yes = 1; //сравниваются элементы поля 3х3: например, 20-ый элемент с 0, 1, 2, 9, 10 и 11.

		if (mass[i] == mass[i - 9] || mass[i] == mass[i - 18] || mass[i] == mass[i - 27] || mass[i] == mass[i - 36] || mass[i] == mass[i - 45] || mass[i] == mass[i - 54] || mass[i] == mass[i - 63] || mass[i] == mass[i - 72]) yes = 1;
		// сравниваются элементы в столбце, если два элемента будут равны, осуществится один шаг назад по циклу
		koll++;  // увеличивается количество выполненных условий
		if (yes == 1) { //если одно или более условий выполнилось,
			i--;  // осуществляется один шаг назад по циклу,
			if (koll > 200) {  // а если проверка застопорится,
				i -= 9;   // осуществится возврат на целую строку - работает безотказно.
				koll = 0; // лучше обнулить количество выполненных условий, иначе всегда
			}  // будет осуществляться возврат на целую строку
			yes = 0; // допустим, что все условия не сработали
		}
	}
}

void Massive_2() {   // массив представляет собой числовое поле для второго игрока
	srand(time(NULL));
	int yes = 0; // если условия истинны, эта переменная равна 1, ели хоть одно станет ложным - 0
	int koll = 0;  // переменная хранит в себе количество выполненных условий
	for (int i = 0; i < massivsize; i++) {
		most[i] = rand() % 9 + 1;  // заполнить текущий элемент случайным значением

		if (i % 9 == 8 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3] || most[i] == most[i - 4] || most[i] == most[i - 5] || most[i] == most[i - 6] || most[i] == most[i - 7] || most[i] == most[i - 8])) yes = 1;
		if (i % 9 == 7 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3] || most[i] == most[i - 4] || most[i] == most[i - 5] || most[i] == most[i - 6] || most[i] == most[i - 7])) yes = 1;
		if (i % 9 == 6 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3] || most[i] == most[i - 4] || most[i] == most[i - 5] || most[i] == most[i - 6])) yes = 1;
		if (i % 9 == 5 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3] || most[i] == most[i - 4] || most[i] == most[i - 5])) yes = 1;
		if (i % 9 == 4 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3] || most[i] == most[i - 4])) yes = 1;
		if (i % 9 == 3 && (most[i] == most[i - 1] || most[i] == most[i - 2] || most[i] == most[i - 3])) yes = 1;
		if (i % 9 == 2 && (most[i] == most[i - 1] || most[i] == most[i - 2])) yes = 1;
		if (i % 9 == 1 && (most[i] == most[i - 1])) yes = 1; // сравниваются элементы в строке, если два
		//элемента будут равны, осуществится один шаг назад по циклу
		if ((i % 27 == 9 || i % 27 == 12 || i % 27 == 15) && (most[i] == most[i - 9] || most[i] == most[i - 8] || most[i] == most[i - 7])) yes = 1; //сравниваются элементы поля 3х3: например, 9-ый элемент с 0, 1 и 2.
		if ((i % 27 == 10 || i % 27 == 13 || i % 27 == 16) && (most[i] == most[i - 10] || most[i] == most[i - 9] || most[i] == most[i - 8])) yes = 1; //сравниваются элементы поля 3х3: например, 10-ый элемент с 0, 1 и 2.
		if ((i % 27 == 11 || i % 27 == 14 || i % 27 == 17) && (most[i] == most[i - 11] || most[i] == most[i - 10] || most[i] == most[i - 9])) yes = 1; //сравниваются элементы поля 3х3: например, 11-ый элемент с 0, 1 и 2.

		if ((i % 27 == 18 || i % 27 == 21 || i % 27 == 24) && (most[i] == most[i - 9] || most[i] == most[i - 8] || most[i] == most[i - 7] || most[i] == most[i - 18] || most[i] == most[i - 17] || most[i] == most[i - 16])) yes = 1; //сравниваются элементы поля 3х3: например, 18-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 19 || i % 27 == 22 || i % 27 == 25) && (most[i] == most[i - 10] || most[i] == most[i - 9] || most[i] == most[i - 8] || most[i] == most[i - 19] || most[i] == most[i - 18] || most[i] == most[i - 17])) yes = 1; //сравниваются элементы поля 3х3: например, 19-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 20 || i % 27 == 23 || i % 27 == 26) && (most[i] == most[i - 11] || most[i] == most[i - 10] || most[i] == most[i - 9] || most[i] == most[i - 20] || most[i] == most[i - 19] || most[i] == most[i - 18])) yes = 1; //сравниваются элементы поля 3х3: например, 20-ый элемент с 0, 1, 2, 9, 10 и 11.

		if (most[i] == most[i - 9] || most[i] == most[i - 18] || most[i] == most[i - 27] || most[i] == most[i - 36] || most[i] == most[i - 45] || most[i] == most[i - 54] || most[i] == most[i - 63] || most[i] == most[i - 72]) yes = 1;
		// сравниваются элементы в столбце, если два элемента будут равны, осуществится один шаг назад по циклу
		koll++;  // увеличивается количество выполненных условий
		if (yes == 1) { //если одно или более условий выполнилось,
			i--;  // осуществляется один шаг назад по циклу,
			if (koll > 200) {  // а если проверка застопорится,
				i -= 9;   // осуществится возврат на целую строку - работает безотказно.
				koll = 0; // лучше обнулить количество выполненных условий, иначе всегда
			}  // будет осуществляться возврат на целую строку
			yes = 0; // допустим, что все условия не сработали
		}
	}
}

void DarkMassive() {
	srand(time(NULL));
	int yes1 = 0; // если условия истинны, эта переменная равна 1, ели хоть одно станет ложным - 0
	int koll1 = 0;  // переменная хранит в себе количество выполненных условий
	for (int i = 0; i < massivsize; i++) {
		mess[i] = rand() % 9 + 1;  // заполнить текущий элемент случайным значением

		if (i % 9 == 8 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3] || mess[i] == mess[i - 4] || mess[i] == mess[i - 5] || mess[i] == mess[i - 6] || mess[i] == mess[i - 7] || mess[i] == mess[i - 8])) yes1 = 1;
		if (i % 9 == 7 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3] || mess[i] == mess[i - 4] || mess[i] == mess[i - 5] || mess[i] == mess[i - 6] || mess[i] == mess[i - 7])) yes1 = 1;
		if (i % 9 == 6 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3] || mess[i] == mess[i - 4] || mess[i] == mess[i - 5] || mess[i] == mess[i - 6])) yes1 = 1;
		if (i % 9 == 5 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3] || mess[i] == mess[i - 4] || mess[i] == mess[i - 5])) yes1 = 1;
		if (i % 9 == 4 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3] || mess[i] == mess[i - 4])) yes1 = 1;
		if (i % 9 == 3 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2] || mess[i] == mess[i - 3])) yes1 = 1;
		if (i % 9 == 2 && (mess[i] == mess[i - 1] || mess[i] == mess[i - 2])) yes1 = 1;
		if (i % 9 == 1 && (mess[i] == mess[i - 1])) yes1 = 1; // сравниваются элементы в строке, если два
		//элемента будут равны, осуществится один шаг назад по циклу
		if ((i % 27 == 9 || i % 27 == 12 || i % 27 == 15) && (mess[i] == mess[i - 9] || mess[i] == mess[i - 8] || mess[i] == mess[i - 7])) yes1 = 1; //сравниваются элементы поля 3х3: например, 9-ый элемент с 0, 1 и 2.
		if ((i % 27 == 10 || i % 27 == 13 || i % 27 == 16) && (mess[i] == mess[i - 10] || mess[i] == mess[i - 9] || mess[i] == mess[i - 8])) yes1 = 1; //сравниваются элементы поля 3х3: например, 10-ый элемент с 0, 1 и 2.
		if ((i % 27 == 11 || i % 27 == 14 || i % 27 == 17) && (mess[i] == mess[i - 11] || mess[i] == mess[i - 10] || mess[i] == mess[i - 9])) yes1 = 1; //сравниваются элементы поля 3х3: например, 11-ый элемент с 0, 1 и 2.

		if ((i % 27 == 18 || i % 27 == 21 || i % 27 == 24) && (mess[i] == mess[i - 9] || mess[i] == mess[i - 8] || mess[i] == mess[i - 7] || mess[i] == mess[i - 18] || mess[i] == mess[i - 17] || mess[i] == mess[i - 16])) yes1 = 1; //сравниваются элементы поля 3х3: например, 18-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 19 || i % 27 == 22 || i % 27 == 25) && (mess[i] == mess[i - 10] || mess[i] == mess[i - 9] || mess[i] == mess[i - 8] || mess[i] == mess[i - 19] || mess[i] == mess[i - 18] || mess[i] == mess[i - 17])) yes1 = 1; //сравниваются элементы поля 3х3: например, 19-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 20 || i % 27 == 23 || i % 27 == 26) && (mess[i] == mess[i - 11] || mess[i] == mess[i - 10] || mess[i] == mess[i - 9] || mess[i] == mess[i - 20] || mess[i] == mess[i - 19] || mess[i] == mess[i - 18])) yes1 = 1; //сравниваются элементы поля 3х3: например, 20-ый элемент с 0, 1, 2, 9, 10 и 11.

		if (mess[i] == mess[i - 9] || mess[i] == mess[i - 18] || mess[i] == mess[i - 27] || mess[i] == mess[i - 36] || mess[i] == mess[i - 45] || mess[i] == mess[i - 54] || mess[i] == mess[i - 63] || mess[i] == mess[i - 72]) yes1 = 1;
		// сравниваются элементы в столбце, если два элемента будут равны, осуществится один шаг назад по циклу
		koll1++;  // увеличивается количество выполненных условий
		if (yes1 == 1) { //если одно или более условий выполнилось,
			i--;  // осуществляется один шаг назад по циклу,
			if (koll1 > 200) {  // а если проверка застопорится,
				i -= 9;   // осуществится возврат на целую строку - работает безотказно.
				koll1 = 0; // лучше обнулить количество выполненных условий, иначе всегда
			}  // будет осуществляться возврат на целую строку
			yes1 = 0; // допустим, что все условия не сработали
		}
	}
}

void DarkMassive_2() {
	srand(time(NULL));
	int yes1 = 0; // если условия истинны, эта переменная равна 1, ели хоть одно станет ложным - 0
	int koll1 = 0;  // переменная хранит в себе количество выполненных условий
	for (int i = 0; i < massivsize; i++) {
		dame[i] = rand() % 9 + 1;  // заполнить текущий элемент случайным значением

		if (i % 9 == 8 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3] || dame[i] == dame[i - 4] || dame[i] == dame[i - 5] || dame[i] == dame[i - 6] || dame[i] == dame[i - 7] || dame[i] == dame[i - 8])) yes1 = 1;
		if (i % 9 == 7 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3] || dame[i] == dame[i - 4] || dame[i] == dame[i - 5] || dame[i] == dame[i - 6] || dame[i] == dame[i - 7])) yes1 = 1;
		if (i % 9 == 6 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3] || dame[i] == dame[i - 4] || dame[i] == dame[i - 5] || dame[i] == dame[i - 6])) yes1 = 1;
		if (i % 9 == 5 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3] || dame[i] == dame[i - 4] || dame[i] == dame[i - 5])) yes1 = 1;
		if (i % 9 == 4 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3] || dame[i] == dame[i - 4])) yes1 = 1;
		if (i % 9 == 3 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2] || dame[i] == dame[i - 3])) yes1 = 1;
		if (i % 9 == 2 && (dame[i] == dame[i - 1] || dame[i] == dame[i - 2])) yes1 = 1;
		if (i % 9 == 1 && (dame[i] == dame[i - 1])) yes1 = 1; // сравниваются элементы в строке, если два
		//элемента будут равны, осуществится один шаг назад по циклу
		if ((i % 27 == 9 || i % 27 == 12 || i % 27 == 15) && (dame[i] == dame[i - 9] || dame[i] == dame[i - 8] || dame[i] == dame[i - 7])) yes1 = 1; //сравниваются элементы поля 3х3: например, 9-ый элемент с 0, 1 и 2.
		if ((i % 27 == 10 || i % 27 == 13 || i % 27 == 16) && (dame[i] == dame[i - 10] || dame[i] == dame[i - 9] || dame[i] == dame[i - 8])) yes1 = 1; //сравниваются элементы поля 3х3: например, 10-ый элемент с 0, 1 и 2.
		if ((i % 27 == 11 || i % 27 == 14 || i % 27 == 17) && (dame[i] == dame[i - 11] || dame[i] == dame[i - 10] || dame[i] == dame[i - 9])) yes1 = 1; //сравниваются элементы поля 3х3: например, 11-ый элемент с 0, 1 и 2.

		if ((i % 27 == 18 || i % 27 == 21 || i % 27 == 24) && (dame[i] == dame[i - 9] || dame[i] == dame[i - 8] || dame[i] == dame[i - 7] || dame[i] == dame[i - 18] || dame[i] == dame[i - 17] || dame[i] == dame[i - 16])) yes1 = 1; //сравниваются элементы поля 3х3: например, 18-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 19 || i % 27 == 22 || i % 27 == 25) && (dame[i] == dame[i - 10] || dame[i] == dame[i - 9] || dame[i] == dame[i - 8] || dame[i] == dame[i - 19] || dame[i] == dame[i - 18] || dame[i] == dame[i - 17])) yes1 = 1; //сравниваются элементы поля 3х3: например, 19-ый элемент с 0, 1, 2, 9, 10 и 11.
		if ((i % 27 == 20 || i % 27 == 23 || i % 27 == 26) && (dame[i] == dame[i - 11] || dame[i] == dame[i - 10] || dame[i] == dame[i - 9] || dame[i] == dame[i - 20] || dame[i] == dame[i - 19] || dame[i] == dame[i - 18])) yes1 = 1; //сравниваются элементы поля 3х3: например, 20-ый элемент с 0, 1, 2, 9, 10 и 11.

		if (dame[i] == dame[i - 9] || dame[i] == dame[i - 18] || dame[i] == dame[i - 27] || dame[i] == dame[i - 36] || dame[i] == dame[i - 45] || dame[i] == dame[i - 54] || dame[i] == dame[i - 63] || dame[i] == dame[i - 72]) yes1 = 1;
		// сравниваются элементы в столбце, если два элемента будут равны, осуществится один шаг назад по циклу
		koll1++;  // увеличивается количество выполненных условий
		if (yes1 == 1) { //если одно или более условий выполнилось,
			i--;  // осуществляется один шаг назад по циклу,
			if (koll1 > 200) {  // а если проверка застопорится,
				i -= 9;   // осуществится возврат на целую строку - работает безотказно.
				koll1 = 0; // лучше обнулить количество выполненных условий, иначе всегда
			}  // будет осуществляться возврат на целую строку
			yes1 = 0; // допустим, что все условия не сработали
		}
	}
}

void Table(int xposit, int yposit, int color) { //функция, которая создаёт массив, содержащий
	system("cls");                          //элементы игрового поля и выводит его на экран                                                
	for (int i = 0; i < trainsize; i++) {
		for (int j = 0; j < trainsize; j++) {
			if (j == 0 && i == 0) traintable[i][j] = 201;
			else if (j == 0 && i == trainsize - 1) traintable[i][j] = 200;
			else if (j == trainsize - 1 && i == 0) traintable[i][j] = 187;
			else if (j == trainsize - 1 && i == trainsize - 1) traintable[i][j] = 188;
			else if (i == 0 && (j == trainsize / 3 || j == 2 * trainsize / 3)) traintable[i][j] = 203;
			else if (i == trainsize - 1 && (j == trainsize / 3 || j == 2 * trainsize / 3)) traintable[i][j] = 202;
			else if (j == 0 && (i == trainsize / 3 || i == 2 * trainsize / 3)) traintable[i][j] = 204;
			else if (j == trainsize - 1 && (i == trainsize / 3 || i == 2 * trainsize / 3)) traintable[i][j] = 185;
			else if (j == trainsize - 1 && (i == trainsize / 3 || i == 2 * trainsize / 3)) traintable[i][j] = 185;
			else if (j == trainsize / 3 && i == trainsize / 3 || j == 2 * trainsize / 3 && i == 2 * trainsize / 3 || j == trainsize / 3 && i == 2 * trainsize / 3 || j == 2 * trainsize / 3 && i == trainsize / 3) traintable[i][j] = 206;
			else if (j % 2 == 1 && (i == 0 || i == trainsize / 3 || i == 2 * trainsize / 3 || i == trainsize - 1)) traintable[i][j] = 205;
			else if (j % 2 == 1 && (i == 0 || i == trainsize / 3 || i == 2 * trainsize / 3 || i == trainsize - 1)) traintable[i][j] = 205;
			else if (i % 2 == 1 && (j == 0 || j == trainsize / 3 || j == 2 * trainsize / 3 || j == trainsize - 1)) traintable[i][j] = 186;
			else if (j == 0 && i % 2 == 0) traintable[i][j] = 199;
			else if (j == trainsize - 1 && i % 2 == 0) traintable[i][j] = 182;
			else if (i == 0 && j % 2 == 0) traintable[i][j] = 209;
			else if (i == trainsize - 1 && j % 2 == 0) traintable[i][j] = 207;
			else if ((j == trainsize / 3 || j == 2 * trainsize / 3) && i % 2 == 0) traintable[i][j] = 215;
			else if ((i == trainsize / 3 || i == 2 * trainsize / 3) && j % 2 == 0) traintable[i][j] = 216;
			else if (j % 2 == 0 && i % 2 == 1) traintable[i][j] = 179;
			else if (j % 2 == 1 && i % 2 == 0) traintable[i][j] = 196;
			else if (j % 2 == 0 && i % 2 == 0) traintable[i][j] = 197;
			else traintable[i][j] = 0;
		}
	}
	Stand(0, xposit, yposit, color);
	for (int i = 0; i < trainsize; i++) {
		c.X = xposit;
		for (int j = 0; j < trainsize; j++) {
			SetConsoleCursorPosition(H, c);
			cout << (char)traintable[i][j];
			c.X++;
		}
		c.Y++;
	}
}

void Training() {   //функция отображает на экране правила игры на практике
	Massive();  //начать создание массива
	Table(32, 13, 1);  //вывод на экран игрового поля 
	int XX = 33;
	int YY = 14;
	Stand(0, XX, YY, 8);
	for (int i = 0; i < massivsize; i++) {
		SetConsoleCursorPosition(H, c);
		cout << mass[i];     //выводится весь массив чисел
		c.X += 2;
		if (i % 9 == 8) {
			c.X = XX; c.Y += 2;
		}
	}
	Stand(800, 33, 14, 12); cout << mass[0]; Stand(200, 33, 14, 8); cout << mass[0];  //красным 
	Stand(0, 35, 14, 12); cout << mass[1]; Stand(200, 35, 14, 8); cout << mass[1];  //выделяются
	Stand(0, 37, 14, 12); cout << mass[2]; Stand(200, 37, 14, 8); cout << mass[2];  //цифры поля
	Stand(0, 37, 16, 12); cout << mass[11]; Stand(200, 37, 16, 8); cout << mass[11];  //3х3, строки
	Stand(0, 35, 16, 12); cout << mass[10]; Stand(200, 35, 16, 8); cout << mass[10];	 //и столбца -
	Stand(0, 33, 16, 12); cout << mass[9]; Stand(200, 33, 16, 8); cout << mass[9];  //цифры  не
	Stand(0, 33, 18, 12); cout << mass[18]; Stand(200, 33, 18, 8); cout << mass[18];  //повторяются
	Stand(0, 35, 18, 12); cout << mass[19]; Stand(200, 35, 18, 8); cout << mass[19];
	Stand(0, 37, 18, 12); cout << mass[20]; Stand(200, 37, 18, 8); cout << mass[20];

	Stand(800, 33, 14, 12); cout << mass[0]; Stand(200, 33, 14, 8); cout << mass[0];
	Stand(0, 33, 16, 12); cout << mass[9]; Stand(200, 33, 16, 8); cout << mass[9];
	Stand(0, 33, 18, 12); cout << mass[18]; Stand(200, 33, 18, 8); cout << mass[18];
	Stand(0, 33, 20, 12); cout << mass[27]; Stand(200, 33, 20, 8); cout << mass[27];
	Stand(0, 33, 22, 12); cout << mass[36]; Stand(200, 33, 22, 8); cout << mass[36];
	Stand(0, 33, 24, 12); cout << mass[45]; Stand(200, 33, 24, 8); cout << mass[45];
	Stand(0, 33, 26, 12); cout << mass[54]; Stand(200, 33, 26, 8); cout << mass[54];
	Stand(0, 33, 28, 12); cout << mass[63]; Stand(200, 33, 28, 8); cout << mass[63];
	Stand(0, 33, 30, 12); cout << mass[72]; Stand(200, 33, 30, 8); cout << mass[72];

	Stand(800, 33, 14, 12); cout << mass[0]; Stand(200, 33, 14, 8); cout << mass[0];
	Stand(0, 35, 14, 12); cout << mass[1]; Stand(200, 35, 14, 8); cout << mass[1];
	Stand(0, 37, 14, 12); cout << mass[2]; Stand(200, 37, 14, 8); cout << mass[2];
	Stand(0, 39, 14, 12); cout << mass[3]; Stand(200, 39, 14, 8); cout << mass[3];
	Stand(0, 41, 14, 12); cout << mass[4]; Stand(200, 41, 14, 8); cout << mass[4];
	Stand(0, 43, 14, 12); cout << mass[5]; Stand(200, 43, 14, 8); cout << mass[5];
	Stand(0, 45, 14, 12); cout << mass[6]; Stand(200, 45, 14, 8); cout << mass[6];
	Stand(0, 47, 14, 12); cout << mass[7]; Stand(200, 47, 14, 8); cout << mass[7];
	Stand(0, 49, 14, 12); cout << mass[8]; Stand(200, 49, 14, 8); cout << mass[8];
	Sleep(600);
	c.X = XX;
	c.Y = YY;
	for (int i = 0; i < massivsize; i++) {
		if (i == 0 || i == 4 || i == 6 || i == 11 || i == 13 || i == 16 || i == 19 || i == 20 || i == 22 || i == 24 || i == 26 || i == 32 || i == 34 || i == 36 || i == 37 || i == 38 || i == 48 || i == 50 || i == 52 || i == 53 || i == 54 || i == 56 || i == 60 || i == 61 || i == 64 || i == 66 || i == 68 || i == 69 || i == 71 || i == 74 || i == 77 || i == 79) SetConsoleTextAttribute(H, 0);
		else SetConsoleTextAttribute(H, 8);
		SetConsoleCursorPosition(H, c);
		cout << mass[i];  // часть цифр специально скрывается
		c.X += 2;
		if (i % 9 == 8) {
			c.X = XX; c.Y += 2;
		}
	}
	Stand(800, 33, 20, 10); cout << mass[27]; Stand(25, 35, 20, 10); cout << mass[28];
	Stand(25, 37, 20, 10); cout << mass[29]; Stand(25, 39, 20, 10); cout << mass[30];
	Stand(25, 41, 20, 10); cout << mass[31]; Stand(25, 45, 20, 10); cout << mass[33];
	Stand(25, 49, 20, 10); cout << mass[35]; // выбирается ряд для заполнения

	Stand(2200, 53, 20, 14); cout << "\"" << mass[32] << "\"";   //сбоку в кавычках указываются 
	Stand(500, 57, 20, 14); cout << "\"" << mass[34] << "\"";     //недостающие в ряду цифры

	Stand(1000, 53, 20, 0); cout << "\"" << mass[32] << "\"";
	Stand(1000, 47, 20, 14); cout << mass[32];         //одна из цифр специально заполняет 
	Stand(1035, 47, 20, 12); cout << mass[32];         //не ту клетку поля и мигает - 
	Stand(350, 47, 20, 0); cout << mass[32];           //в перпендикулярном ряду или
	Stand(350, 47, 20, 12); cout << mass[32];          //в поле 3х3 такая цифра уже должна быть
	Stand(350, 47, 20, 0); cout << mass[32];
	Stand(350, 47, 20, 12); cout << mass[32];
	Stand(350, 47, 20, 0); cout << mass[32];
	Stand(900, 53, 20, 14); cout << "\"" << mass[32] << "\"";
	Stand(2000, 43, 20, 14); cout << mass[32];
	Stand(400, 53, 20, 0); cout << "\"" << mass[32] << "\"";
	Stand(500, 47, 20, 14); cout << mass[34];
	Stand(300, 57, 20, 0); cout << "\"" << mass[34] << "\"";

	Stand(0, 33, 20, 8); cout << mass[27]; Stand(25, 35, 20, 8); cout << mass[28]; //снять выделение  
	Stand(0, 37, 20, 8); cout << mass[29]; Stand(25, 39, 20, 8); cout << mass[30]; //с текущего ряда
	Stand(0, 41, 20, 8); cout << mass[31]; Stand(0, 43, 20, 8); cout << mass[32];
	Stand(25, 45, 20, 8); cout << mass[33]; Stand(0, 47, 20, 8); cout << mass[34];
	Stand(0, 49, 20, 8); cout << mass[35];

	Stand(2100, 39, 14, 10); cout << mass[3]; Stand(25, 39, 16, 10); cout << mass[12];
	Stand(25, 39, 18, 10); cout << mass[21]; Stand(25, 39, 20, 10); cout << mass[30];
	Stand(25, 39, 22, 10); cout << mass[39]; Stand(25, 39, 26, 10); cout << mass[57];
	Stand(25, 39, 30, 10); cout << mass[75]; //выбирается следующий ряд для заполнения

	Stand(2200, 38, 33, 14); cout << "\"" << mass[48] << "\""; Stand(500, 38, 35, 14);
	cout << "\"" << mass[66] << "\"";
	Stand(1000, 38, 33, 0); cout << "\"" << mass[48] << "\"";  //снизу в кавычках указываются 
	Stand(1000, 39, 28, 14); cout << mass[48];             //недостающие в ряду цифры
	Stand(1035, 39, 28, 12); cout << mass[48];
	Stand(350, 39, 28, 0); cout << mass[48];        //снова сначала заполняется не та клетка,
	Stand(350, 39, 28, 12); cout << mass[48];       //а затем - необходимая
	Stand(350, 39, 28, 0); cout << mass[48];
	Stand(350, 39, 28, 12); cout << mass[48];
	Stand(350, 39, 28, 0); cout << mass[48];
	Stand(900, 38, 33, 14); cout << "\"" << mass[48] << "\"";
	Stand(2000, 39, 24, 14); cout << mass[48];
	Stand(400, 38, 33, 0); cout << "\"" << mass[48] << "\"";
	Stand(500, 39, 28, 14); cout << mass[66];
	Stand(400, 38, 35, 0); cout << "\"" << mass[66] << "\"";
	Stand(1800, XX, YY, 0);

	Stand(0, 39, 14, 8); cout << mass[3]; Stand(0, 39, 16, 8); cout << mass[12]; //снять 
	Stand(0, 39, 18, 8); cout << mass[21]; Stand(0, 39, 20, 8); cout << mass[30]; //выделение
	Stand(0, 39, 22, 8); cout << mass[39]; Stand(0, 39, 24, 8); cout << mass[48]; //с текущего
	Stand(0, 39, 26, 8); cout << mass[57]; Stand(0, 39, 28, 8); cout << mass[66]; //  ряда
	Stand(0, 39, 30, 8); cout << mass[75];

	Stand(2000, 39, 20, 12); cout << mass[30]; Stand(200, 39, 20, 8); cout << mass[30];
	Stand(0, 41, 20, 12); cout << mass[31]; Stand(200, 41, 20, 8); cout << mass[31]; //в среднем 
	Stand(0, 43, 20, 12); cout << mass[32]; Stand(200, 43, 20, 8); cout << mass[32]; //поле 3х3
	Stand(0, 39, 22, 12); cout << mass[39]; Stand(200, 39, 22, 8); cout << mass[39]; //не заполнена
	Stand(0, 41, 22, 12); cout << mass[40]; Stand(200, 41, 22, 8); cout << mass[40]; //только одна
	Stand(0, 43, 22, 12); cout << mass[41]; Stand(200, 43, 22, 8); cout << mass[41]; //клетка
	Stand(0, 39, 24, 12); cout << mass[48]; Stand(200, 39, 24, 8); cout << mass[48];
	Stand(0, 41, 24, 12); cout << mass[49]; Stand(200, 41, 24, 8); cout << mass[49];
	Stand(400, 42, 36, 14); cout << "\"" << mass[50] << "\"";
	Stand(1400, 43, 24, 14); cout << mass[50];  //теперь заполнена
	Stand(300, 42, 36, 0); cout << "\"" << mass[50] << "\"";
	Stand(100, 32, 13, 0);
	for (int i = 0; i < trainsize; i++) {      //демонстрационная таблица красиво исчезает с экрана
		for (int j = 0; j < trainsize; j++) {
			cout << " "; Sleep(1);
		}
		cout << "\n\t\t\t\t";
	}
	main();  //возврат в меню 
}

void Traingame() { // функция, которая реализует обучающий процесс
	fortimer = 0;  // включить таймер
	srand(time(NULL)); system("cls");
	Massive();  //начать создание массива
	Stand(0, 26, 44, 4);  //перед созданием массива пустых клеток необходимо подождать,
	cout << "TUTORIAL. Loading, please wait..."; // иначе будут созданы одинаковые массивы - 
	Stand(0, 0, 47, 4);   // для этого добавляется красивая полоса загрузки :)
	int set = 80;
	while (set--) {
		cout << (char)177; Sleep(40);
	}
	Stand(0, 0, 47, 0);
	DarkMassive(); // теперь можно создать массив пустых клеток
	Table(32, 13, 1);  //вывод на экран игрового поля 
	int XX = 33;
	int YY = 14;
	Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для показа 
	for (int i = 0; i < massivsize; i++) {                                 // массива
		SetConsoleCursorPosition(H, c);
		if (mess[i] == 1 || mess[i] == 2 || mess[i] == 3 || mess[i] == 4) mess[i] = 0; // 4 клетки  в строке
		// станут "пустыми"
		if (mess[i] == 0) {
			SetConsoleTextAttribute(H, 7);
			cout << " ";  // если mess[i] равно 0, клетка станет "пустой"
		}
		else {
			SetConsoleTextAttribute(H, 7); //в другом случае снова будет показан эл. mаss[i]
			cout << mass[i];
		}
		c.X += 2;
		if (i % 9 == 8) {  // переход на новую строку
			c.X = XX; c.Y += 2;
		}
	}
	int emptyblock = 0; // переменная хранит в себе количество "пустых" клеток
	for (int i = 0; i < massivsize; i++) {
		if (mess[i] == 0) emptyblock++;
	}
	int notemptyblock = 0;
	int go; // переменная будет хранить в себе код нажатой клавиши
	Stand(0, XX, YY, 8); // установить курсор в верхний левый угол игрового поля для начала 																	// игры
	CONSOLE_CURSOR_INFO cci; cci.bVisible = 100; cci.dwSize = 100; // показать курсор 
	SetConsoleCursorInfo(H, &cci);
	gat1 = c.X;  // переменные хранят в себе 
	gat2 = c.Y;     // координаты курсора
	//CreateThread(0, 0, timerplus, 0, 0, 0); // вызов функции таймера
	int digit; // для удобства нажатая цифра запишется в эту переменную
	do {
		gat1 = c.X; // переменные хранят в себе координаты курсора
		gat2 = c.Y;  go = _getch();
		switch (go) {
		case 77: // вправо
			if (c.X + 2 <= 49) {
				c.X += 2; SetConsoleCursorPosition(H, c);
			}
			break;
		case 75: // влево
			if (c.X - 2 >= 33) {
				c.X -= 2; SetConsoleCursorPosition(H, c);
			}
			break;
		case 72: // вверх
			if (c.Y - 2 >= 14) {
				c.Y -= 2; SetConsoleCursorPosition(H, c);
			}
			break;
		case 80: //	вниз
			if (c.Y + 2 <= 30) {
				c.Y += 2; SetConsoleCursorPosition(H, c);
			}
			break;
		case 49: //	1
			digit = 1;
			break;
		case 50: //	2
			digit = 2;
			break;
		case 51: //	3
			digit = 3;
			break;
		case 52: //	4
			digit = 4;
			break;
		case 53: //	5
			digit = 5;
			break;
		case 54: //	6
			digit = 6;
			break;
		case 55: //	7
			digit = 7;
			break;
		case 56: //	8
			digit = 8;
			break;
		case 57: //	9
			digit = 9;
			break;
		case 32: //	если курсор "соскочит" с игрового поля, пробелом его можно вернуть его
			gat1 = 33; gat2 = 14; Stand(0, gat1, gat2, 7);
			break;
		case 27: // вернуться в main
			fortimer = 1; Stand(0, 5, 47, 7); cout << "Exit...";
			Sleep(1025);  // для остановки функции Timerplus желательно подождать 1 секунду
			main();
			break;
		}
		if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {
			SetConsoleTextAttribute(H, 10); // ниже следует проверка, можно ли поставить на выбранном месте цифру
			int controlthisdigit = 0; // если переменная изменится, будет показано число и количество заполненных клеток увеличится
			if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] == digit) { controlthisdigit = 1; mess[0] == 1; }
			if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] == digit) { controlthisdigit = 1; mess[1] == 1; }
			if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] == digit) { controlthisdigit = 1; mess[2] == 1; }
			if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] == digit) { controlthisdigit = 1; mess[3] == 1; }
			if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] == digit) { controlthisdigit = 1; mess[4] == 1; }
			if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] == digit) { controlthisdigit = 1; mess[5] == 1; }
			if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] == digit) { controlthisdigit = 1; mess[6] == 1; }
			if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] == digit) { controlthisdigit = 1; mess[7] == 1; }
			if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] == digit) { controlthisdigit = 1; mess[8] == 1; }
			if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] == digit) { controlthisdigit = 1; mess[9] == 1; }
			if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] == digit) { controlthisdigit = 1; mess[10] == 1; }
			if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] == digit) { controlthisdigit = 1; mess[11] == 1; }
			if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] == digit) { controlthisdigit = 1; mess[12] == 1; }
			if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] == digit) { controlthisdigit = 1; mess[13] == 1; }
			if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] == digit) { controlthisdigit = 1; mess[14] == 1; }
			if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] == digit) { controlthisdigit = 1; mess[15] == 1; }
			if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] == digit) { controlthisdigit = 1; mess[16] == 1; }
			if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] == digit) { controlthisdigit = 1; mess[17] == 1; }
			if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] == digit) { controlthisdigit = 1; mess[18] == 1; }
			if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] == digit) { controlthisdigit = 1; mess[19] == 1; }
			if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] == digit) { controlthisdigit = 1; mess[20] == 1; }
			if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] == digit) { controlthisdigit = 1; mess[21] == 1; }
			if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] == digit) { controlthisdigit = 1; mess[22] == 1; }
			if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] == digit) { controlthisdigit = 1; mess[23] == 1; }
			if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] == digit) { controlthisdigit = 1; mess[24] == 1; }
			if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] == digit) { controlthisdigit = 1; mess[25] == 1; }
			if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] == digit) { controlthisdigit = 1; mess[26] == 1; }
			if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] == digit) { controlthisdigit = 1; mess[27] == 1; }
			if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] == digit) { controlthisdigit = 1; mess[28] == 1; }
			if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] == digit) { controlthisdigit = 1; mess[29] == 1; }
			if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] == digit) { controlthisdigit = 1; mess[30] == 1; }
			if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] == digit) { controlthisdigit = 1; mess[31] == 1; }
			if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] == digit) { controlthisdigit = 1; mess[32] == 1; }
			if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] == digit) { controlthisdigit = 1; mess[33] == 1; }
			if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] == digit) { controlthisdigit = 1; mess[34] == 1; }
			if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] == digit) { controlthisdigit = 1; mess[35] == 1; }
			if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] == digit) { controlthisdigit = 1; mess[36] == 1; }
			if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] == digit) { controlthisdigit = 1; mess[37] == 1; }
			if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] == digit) { controlthisdigit = 1; mess[38] == 1; }
			if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] == digit) { controlthisdigit = 1; mess[39] == 1; }
			if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] == digit) { controlthisdigit = 1; mess[40] == 1; }
			if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] == digit) { controlthisdigit = 1; mess[41] == 1; }
			if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] == digit) { controlthisdigit = 1; mess[42] == 1; }
			if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] == digit) { controlthisdigit = 1; mess[43] == 1; }
			if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] == digit) { controlthisdigit = 1; mess[44] == 1; }
			if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] == digit) { controlthisdigit = 1; mess[45] == 1; }
			if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] == digit) { controlthisdigit = 1; mess[46] == 1; }
			if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] == digit) { controlthisdigit = 1; mess[47] == 1; }
			if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] == digit) { controlthisdigit = 1; mess[48] == 1; }
			if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] == digit) { controlthisdigit = 1; mess[49] == 1; }
			if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] == digit) { controlthisdigit = 1; mess[50] == 1; }
			if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] == digit) { controlthisdigit = 1; mess[51] == 1; }
			if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] == digit) { controlthisdigit = 1; mess[52] == 1; }
			if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] == digit) { controlthisdigit = 1; mess[53] == 1; }
			if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] == digit) { controlthisdigit = 1; mess[54] == 1; }
			if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] == digit) { controlthisdigit = 1; mess[55] == 1; }
			if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] == digit) { controlthisdigit = 1; mess[56] == 1; }
			if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] == digit) { controlthisdigit = 1; mess[57] == 1; }
			if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] == digit) { controlthisdigit = 1; mess[58] == 1; }
			if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] == digit) { controlthisdigit = 1; mess[59] == 1; }
			if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] == digit) { controlthisdigit = 1; mess[60] == 1; }
			if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] == digit) { controlthisdigit = 1; mess[61] == 1; }
			if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] == digit) { controlthisdigit = 1; mess[62] == 1; }
			if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] == digit) { controlthisdigit = 1; mess[63] == 1; }
			if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] == digit) { controlthisdigit = 1; mess[64] == 1; }
			if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] == digit) { controlthisdigit = 1; mess[65] == 1; }
			if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] == digit) { controlthisdigit = 1; mess[66] == 1; }
			if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] == digit) { controlthisdigit = 1; mess[67] == 1; }
			if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] == digit) { controlthisdigit = 1; mess[68] == 1; }
			if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] == digit) { controlthisdigit = 1; mess[69] == 1; }
			if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] == digit) { controlthisdigit = 1; mess[70] == 1; }
			if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] == digit) { controlthisdigit = 1; mess[71] == 1; }
			if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] == digit) { controlthisdigit = 1; mess[72] == 1; }
			if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] == digit) { controlthisdigit = 1; mess[73] == 1; }
			if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] == digit) { controlthisdigit = 1; mess[74] == 1; }
			if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] == digit) { controlthisdigit = 1; mess[75] == 1; }
			if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] == digit) { controlthisdigit = 1; mess[76] == 1; }
			if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] == digit) { controlthisdigit = 1; mess[77] == 1; }
			if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] == digit) { controlthisdigit = 1; mess[78] == 1; }
			if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] == digit) { controlthisdigit = 1; mess[79] == 1; }
			if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] == digit) { controlthisdigit = 1; mess[80] == 1; }
			if (controlthisdigit == 1) {
				cout << digit; notemptyblock++; // число показывается на экране,
			}  // количество незаполненных клеток уменьшается
			SetConsoleCursorPosition(H, c); // возвратить курсор на место показанного числа
		}
		if (go != 49 && go != 50 && go != 51 && go != 52 && go != 53 && go != 54 && go != 55 && go != 56 && go != 57 && go != 77 && go != 75 && go != 80 && go != 72 && go != 224 && go != 32) {  // если пользователь вводит не цифры
			int COORDX = c.X, COORDY = c.Y;
			Stand(0, 24, 34, 12); cout << "Not correct. You must input digits!";
			Stand(500, 24, 34, 0); cout << "Not correct. You must input digits!";
			Stand(0, COORDX, COORDY, 7);
		}
		int mist = 0; // проверка на ошибки: если введено неправильное число, пользователь узнает об этом
		if (go == 49 || go == 50 || go == 51 || go == 52 || go == 53 || go == 54 || go == 55 || go == 56 || go == 57) {
			if (c.X == 33 && c.Y == 14 && mess[0] == 0 && mass[0] != digit) mist = 1;
			if (c.X == 35 && c.Y == 14 && mess[1] == 0 && mass[1] != digit) mist = 1;
			if (c.X == 37 && c.Y == 14 && mess[2] == 0 && mass[2] != digit) mist = 1;
			if (c.X == 39 && c.Y == 14 && mess[3] == 0 && mass[3] != digit) mist = 1;
			if (c.X == 41 && c.Y == 14 && mess[4] == 0 && mass[4] != digit) mist = 1;
			if (c.X == 43 && c.Y == 14 && mess[5] == 0 && mass[5] != digit) mist = 1;
			if (c.X == 45 && c.Y == 14 && mess[6] == 0 && mass[6] != digit) mist = 1;
			if (c.X == 47 && c.Y == 14 && mess[7] == 0 && mass[7] != digit) mist = 1;
			if (c.X == 49 && c.Y == 14 && mess[8] == 0 && mass[8] != digit) mist = 1;
			if (c.X == 33 && c.Y == 16 && mess[9] == 0 && mass[9] != digit) mist = 1;
			if (c.X == 35 && c.Y == 16 && mess[10] == 0 && mass[10] != digit) mist = 1;
			if (c.X == 37 && c.Y == 16 && mess[11] == 0 && mass[11] != digit) mist = 1;
			if (c.X == 39 && c.Y == 16 && mess[12] == 0 && mass[12] != digit) mist = 1;
			if (c.X == 41 && c.Y == 16 && mess[13] == 0 && mass[13] != digit) mist = 1;
			if (c.X == 43 && c.Y == 16 && mess[14] == 0 && mass[14] != digit) mist = 1;
			if (c.X == 45 && c.Y == 16 && mess[15] == 0 && mass[15] != digit) mist = 1;
			if (c.X == 47 && c.Y == 16 && mess[16] == 0 && mass[16] != digit) mist = 1;
			if (c.X == 49 && c.Y == 16 && mess[17] == 0 && mass[17] != digit) mist = 1;
			if (c.X == 33 && c.Y == 18 && mess[18] == 0 && mass[18] != digit) mist = 1;
			if (c.X == 35 && c.Y == 18 && mess[19] == 0 && mass[19] != digit) mist = 1;
			if (c.X == 37 && c.Y == 18 && mess[20] == 0 && mass[20] != digit) mist = 1;
			if (c.X == 39 && c.Y == 18 && mess[21] == 0 && mass[21] != digit) mist = 1;
			if (c.X == 41 && c.Y == 18 && mess[22] == 0 && mass[22] != digit) mist = 1;
			if (c.X == 43 && c.Y == 18 && mess[23] == 0 && mass[23] != digit) mist = 1;
			if (c.X == 45 && c.Y == 18 && mess[24] == 0 && mass[24] != digit) mist = 1;
			if (c.X == 47 && c.Y == 18 && mess[25] == 0 && mass[25] != digit) mist = 1;
			if (c.X == 49 && c.Y == 18 && mess[26] == 0 && mass[26] != digit) mist = 1;
			if (c.X == 33 && c.Y == 20 && mess[27] == 0 && mass[27] != digit) mist = 1;
			if (c.X == 35 && c.Y == 20 && mess[28] == 0 && mass[28] != digit) mist = 1;
			if (c.X == 37 && c.Y == 20 && mess[29] == 0 && mass[29] != digit) mist = 1;
			if (c.X == 39 && c.Y == 20 && mess[30] == 0 && mass[30] != digit) mist = 1;
			if (c.X == 41 && c.Y == 20 && mess[31] == 0 && mass[31] != digit) mist = 1;
			if (c.X == 43 && c.Y == 20 && mess[32] == 0 && mass[32] != digit) mist = 1;
			if (c.X == 45 && c.Y == 20 && mess[33] == 0 && mass[33] != digit) mist = 1;
			if (c.X == 47 && c.Y == 20 && mess[34] == 0 && mass[34] != digit) mist = 1;
			if (c.X == 49 && c.Y == 20 && mess[35] == 0 && mass[35] != digit) mist = 1;
			if (c.X == 33 && c.Y == 22 && mess[36] == 0 && mass[36] != digit) mist = 1;
			if (c.X == 35 && c.Y == 22 && mess[37] == 0 && mass[37] != digit) mist = 1;
			if (c.X == 37 && c.Y == 22 && mess[38] == 0 && mass[38] != digit) mist = 1;
			if (c.X == 39 && c.Y == 22 && mess[39] == 0 && mass[39] != digit) mist = 1;
			if (c.X == 41 && c.Y == 22 && mess[40] == 0 && mass[40] != digit) mist = 1;
			if (c.X == 43 && c.Y == 22 && mess[41] == 0 && mass[41] != digit) mist = 1;
			if (c.X == 45 && c.Y == 22 && mess[42] == 0 && mass[42] != digit) mist = 1;
			if (c.X == 47 && c.Y == 22 && mess[43] == 0 && mass[43] != digit) mist = 1;
			if (c.X == 49 && c.Y == 22 && mess[44] == 0 && mass[44] != digit) mist = 1;
			if (c.X == 33 && c.Y == 24 && mess[45] == 0 && mass[45] != digit) mist = 1;
			if (c.X == 35 && c.Y == 24 && mess[46] == 0 && mass[46] != digit) mist = 1;
			if (c.X == 37 && c.Y == 24 && mess[47] == 0 && mass[47] != digit) mist = 1;
			if (c.X == 39 && c.Y == 24 && mess[48] == 0 && mass[48] != digit) mist = 1;
			if (c.X == 41 && c.Y == 24 && mess[49] == 0 && mass[49] != digit) mist = 1;
			if (c.X == 43 && c.Y == 24 && mess[50] == 0 && mass[50] != digit) mist = 1;
			if (c.X == 45 && c.Y == 24 && mess[51] == 0 && mass[51] != digit) mist = 1;
			if (c.X == 47 && c.Y == 24 && mess[52] == 0 && mass[52] != digit) mist = 1;
			if (c.X == 49 && c.Y == 24 && mess[53] == 0 && mass[53] != digit) mist = 1;
			if (c.X == 33 && c.Y == 26 && mess[54] == 0 && mass[54] != digit) mist = 1;
			if (c.X == 35 && c.Y == 26 && mess[55] == 0 && mass[55] != digit) mist = 1;
			if (c.X == 37 && c.Y == 26 && mess[56] == 0 && mass[56] != digit) mist = 1;
			if (c.X == 39 && c.Y == 26 && mess[57] == 0 && mass[57] != digit) mist = 1;
			if (c.X == 41 && c.Y == 26 && mess[58] == 0 && mass[58] != digit) mist = 1;
			if (c.X == 43 && c.Y == 26 && mess[59] == 0 && mass[59] != digit) mist = 1;
			if (c.X == 45 && c.Y == 26 && mess[60] == 0 && mass[60] != digit) mist = 1;
			if (c.X == 47 && c.Y == 26 && mess[61] == 0 && mass[61] != digit) mist = 1;
			if (c.X == 49 && c.Y == 26 && mess[62] == 0 && mass[62] != digit) mist = 1;
			if (c.X == 33 && c.Y == 28 && mess[63] == 0 && mass[63] != digit) mist = 1;
			if (c.X == 35 && c.Y == 28 && mess[64] == 0 && mass[64] != digit) mist = 1;
			if (c.X == 37 && c.Y == 28 && mess[65] == 0 && mass[65] != digit) mist = 1;
			if (c.X == 39 && c.Y == 28 && mess[66] == 0 && mass[66] != digit) mist = 1;
			if (c.X == 41 && c.Y == 28 && mess[67] == 0 && mass[67] != digit) mist = 1;
			if (c.X == 43 && c.Y == 28 && mess[68] == 0 && mass[68] != digit) mist = 1;
			if (c.X == 45 && c.Y == 28 && mess[69] == 0 && mass[69] != digit) mist = 1;
			if (c.X == 47 && c.Y == 28 && mess[70] == 0 && mass[70] != digit) mist = 1;
			if (c.X == 49 && c.Y == 28 && mess[71] == 0 && mass[71] != digit) mist = 1;
			if (c.X == 33 && c.Y == 30 && mess[72] == 0 && mass[72] != digit) mist = 1;
			if (c.X == 35 && c.Y == 30 && mess[73] == 0 && mass[73] != digit) mist = 1;
			if (c.X == 37 && c.Y == 30 && mess[74] == 0 && mass[74] != digit) mist = 1;
			if (c.X == 39 && c.Y == 30 && mess[75] == 0 && mass[75] != digit) mist = 1;
			if (c.X == 41 && c.Y == 30 && mess[76] == 0 && mass[76] != digit) mist = 1;
			if (c.X == 43 && c.Y == 30 && mess[77] == 0 && mass[77] != digit) mist = 1;
			if (c.X == 45 && c.Y == 30 && mess[78] == 0 && mass[78] != digit) mist = 1;
			if (c.X == 47 && c.Y == 30 && mess[79] == 0 && mass[79] != digit) mist = 1;
			if (c.X == 49 && c.Y == 30 && mess[80] == 0 && mass[80] != digit) mist = 1;
		}
		if (mist == 1) {
			int COORDX = c.X, COORDY = c.Y;
			Stand(0, 29, 34, 12); cout << "Not correct. Wrong digit!";
			Stand(500, 29, 34, 0); cout << "Not correct. Wrong digit!";
			Stand(30, COORDX, COORDY, 7);
		}
	} while (emptyblock != notemptyblock);
	fortimer = 1; breaktimer = 1; // остановить таймер и включить "анимацию"
	Stand(0, 24, 34, 12); // после заполнения игрового поля на экран выводится надпись о завершении
	if (sec > 0 && sec < 121) {
		Stand(0, 23, 34, 12); cout << "Great!!! Maybe you are sudoku master?";
	}
	if (sec > 120 && sec < 301) {
		Stand(0, 24, 34, 12); cout << "Well done! You can play hard games!";
	}
	if (sec > 300 && sec < 601) {
		Stand(0, 19, 34, 12); cout << "Not bad. I think now you can play real game!";
	}
	if (sec > 600) {
		Stand(0, 18, 34, 12); cout << "You must train more before good fast playing.";
	}
	Stand(0, 32, 37, 12); cout << "Your time: "; Sleep(7000); main();
}

void main() {
	CONSOLE_CURSOR_INFO cci; cci.bVisible = 0; cci.dwSize = 100;
	SetConsoleCursorInfo(H, &cci);  //курсор становится невидимым
	int check = 0, choice; //choice отвечает за принятие кода клавиши, check считает
	Head();  //вывод на экран заголовка меню                           //количество нажатий
	Menu(1); //сразу же активной является первая строка меню
	do {
		choice = _getch();
		switch (choice) {
		case 72: //при нажатии клавиши 'вверх' активной станет строка, которая выше текущей
			check--;
			if (check == 0) Menu(1);
			if (check == 1) Menu(2);
			if (check == 2) Menu(3);
			if (check < 0) check = 0;
			break;
		case 80: //при нажатии клавиши 'вниз' активной станет строка, которая ниже текущей
			check++;
			if (check == 1) Menu(2);
			if (check == 2) Menu(3);
			if (check == 3) Menu(4);
			if (check > 3) check = 3;
			break;
		case 13: //при нажатии клавиши 'Enter' строка запускается
			if (check == 0) Hardness(50, 24, 9, 1); //передать координаты меню сложности, цвет  
			if (check == 1) Hardness(50, 30, 14, 2); //стрелочки меню и количество игроков
			if (check == 2) { //запуск строки для просмотра тренировки
				Stand(0, 5, 47, 0);  //поясняющая строка внизу исчезает, затем красиво
				//FillConsoleOutputAttribute(H, 0, 79, c, 0);      //исчезает меню
				Stand(0, 30, 32, 0);
				int indexi = 5;
				int indexj = 20;
				int fox = 0;
				while (fox != 7) {
					SetConsoleCursorPosition(H, c);
					for (int i = 0; i < indexi; i++) {
						for (int j = 0; j < indexj; j++) {
							cout << " ";
						}
						cout << "\n";
						for (int p = 0; p < c.X; p++) {
							cout << " ";
						}
					}
					c.X -= 3; c.Y -= 2;
					indexj += 6; indexi += 4;
					fox++; Sleep(25);
				}
				Stand(0, 1, 20, 2);
				cout << "14.02.2007  ALEX GAMES special for IT Step. All rights reserved @ Version 1.00";
				Stand(0, 5, 47, 7);
				cout << "Press enter for tutorial, space for demo or escape to back main menu";
				Stand(0, 64, 42, 12); cout << "Training " << (char)26;
				int plus;
				do {
					plus = _getch();
					switch (plus) {
					case 32:  //если нажать пробел, запустится демонстрация
						Stand(0, 0, 47, 0);
						//FillConsoleOutputAttribute(H, 0, 79, c, 0);
						Training();
						break;
					case 27: //если нажать Escape, произойдёт возврат в главное меню
						main();
						break;
					case 13: //если нажать Enter, начнётся тренировочная игра
						Traingame();
						break;
					}
				} while (plus != 27 && plus != 13 && plus != 32);
			}
			if (check == 3) { //выход из программы
				system("cls"); exit(0);
			}
			break;
		}
	} while (choice != 13);
}