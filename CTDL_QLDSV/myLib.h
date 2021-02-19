#pragma once
#include <conio.h>

#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include<sstream>
#include "Common.h"

#define UP 72
#define DOWN 80
#define BACKSPACE 8
#define ENTER 13
#define ESC 27
#define RIGHT 77
#define LEFT 75 
#define SPACE 32

using namespace std;

void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol() {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}


void setFullScreen() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SMALL_RECT rect;
	COORD coord;
	coord.X = 168; // Defining our X and
	coord.Y = 44;  // Y size for buffer.

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = coord.Y - 1; // height for window
	rect.Right = coord.X - 1;  // width for window

	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // get handle
	SetConsoleWindowInfo(hwnd, TRUE, &rect);
}

void SetWindow(int Width, int Height) {
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, Width, Height, TRUE);
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(1);
}

void exitProgram() {
	PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
}

int showMessageBox(string title, string message, int typeIcon)
{
	int msgboxID = MessageBoxA(
		GetConsoleWindow(),
		message.c_str(),
		title.c_str(),
		typeIcon | MB_OKCANCEL
	);
	return msgboxID;
}
void clearScreen(int x, int y, int width, int height) {
	ShowCur(false);
	string w = "";
	for (int i = 0; i < width; i++) {
		w += " ";
	}
	for (int i = 0; i < height; i++) {
		gotoxy(x, y + i);
		cout << w;
	}
	ShowCur(true);
}
void clearEdit(){
	Normal();
	clearScreen(40,2,124,40);
}

//============================================================================


void TaoKhungDon(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		gotoxy(x + i, y); cout << char(196);
	}
	gotoxy(x, y); cout << char(218);
	for (int i = 1; i < height; i++)
	{
		gotoxy(x, y + i); cout << char(179);
	}
	gotoxy(x, y + height); cout << char(192);
	for (int i = 1; i < width; i++)
	{
		gotoxy(x + i, y + height); cout << char(196);
	}
	gotoxy(x + width, y); cout << char(191);
	for (int i = 1; i < height; i++)
	{
		gotoxy(x + width, y + i); cout << char(179);
	}
	gotoxy(x + width, y + height); cout << char(217);
}

void TaoKhungKep(int x, int y, int width, int height)
{
	for (int i = 0; i < width; i++)
	{
		gotoxy(x + i, y); cout << char(205);
	}
	gotoxy(x, y); cout << char(201);
	for (int i = 1; i < height; i++)
	{
		gotoxy(x, y + i); cout << char(186);
	}
	gotoxy(x, y + height); cout << char(200);
	for (int i = 1; i < width; i++)
	{
		gotoxy(x + i, y + height); cout << char(205);
	}
	gotoxy(x + width, y); cout << char(187);
	for (int i = 1; i < height; i++)
	{
		gotoxy(x + width, y + i); cout << char(186);
	}
	gotoxy(x + width, y + height); cout << char(188);
}
//============================================================================

char ThongBao(char *str)
{
	gotoxy(70,40); cout<<str;
	int key;
	do
	{
		key = getch();
		key = toupper(key);
	}while(key != 89 && key != 78); // Y : N
	return char(key);
}

//============================================================================

void XoaKyTu(char str[], int vitri)
{
	for(int i = vitri + 1; i < strlen(str); i++)
	{
		str[i - 1] = str[i];
	}
	str[strlen(str) - 1] = '\0';
}

//void ChuanHoa(char Name[])
//{
//	if(Name[0]>=97 && Name[0] <= 122)
//	{
//		Name[0]-=32;
//	}
//	
//	for(int i = 1;i < strlen(Name); i++)
//	{
//		if(Name[i] == ' ' && Name[i+1] != ' ')
//		{
//			if(Name[i + 1]>=97 && Name[i + 1] <= 122)
//			{
//				Name[i + 1]-=32;
//			}
//		}
//	}
//}


void InputCodeToUpper(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int key, i = strlen(str);
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if( key == BACKSPACE || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122))
		{
			switch(key)
			{
					
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length)
					{
						continue;
					}
					char k = key;
					if(k >= 97 && k<=122)
					{
						k-=32;
					}
					str[i] = char(k);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)k;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
}


void InputStringNamePeople(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int key, i = strlen(str);
	int space = 0;
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if(key == BACKSPACE || key == SPACE ||  (key >= 65 && key <= 90) || (key >= 97 && key <= 122))
		{
			switch(key)
			{
				case SPACE:
					if(space == 1 || strlen(str) == 0)
					{
						continue;
					}
					space++;
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
					break;
					
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length)
					{
						continue;
					}
					char k = key;
					if((k >= 97 && k<=122) && (str[i - 1] == ' ' || strlen(str) == 0))
					{
						k-=32;
					}
					str[i] = char(k);
					str[++i] = '\0';
					space = 0;
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)k;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
	
	if(str[strlen(str) - 1] == SPACE)
	{
		XoaKyTu(str,strlen(str) - 1);
	}
}

void InputStringName(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int key, i = strlen(str);
	int space = 0;
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if(key == BACKSPACE || key == SPACE || (key >= 48 && key <= 57) || (key >= 65 && key <= 90) || (key >= 97 && key <= 122))
		{
			switch(key)
			{
				case SPACE:
					if(space == 1 || strlen(str) == 0)
					{
						continue;
					}
					space++;
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
					break;
					
					
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length)
					{
						continue;
					}
					char k = key;
					if((k >= 97 && k<=122) && (strlen(str) == 0))
					{
						k-=32;
					}
					str[i] = char(k);
					str[++i] = '\0';
					space = 0;
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)k;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
	
	if(str[strlen(str) - 1] == SPACE)
	{
		XoaKyTu(str,strlen(str) - 1);
	}
}

void InputNumberIsInteger(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int key, i = strlen(str);
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if( key == BACKSPACE || (key >= 48 && key <= 57))
		{
			switch(key)
			{	
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length)
					{
						continue;
					}
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
}



void InputNumberSTCIsFloat(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int dem = 0;
	int key, i = strlen(str);
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if(key == BACKSPACE || key == 46 || (key >= 48 && key <= 57))
		{
			
			switch(key)
			{						
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						if(str[i - 1] == 46)
						{
							dem = 0;
						}
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length)
					{
						continue;
					}
					if(((strlen(str) == 0 || str[i - 1] == 46 || dem == 1) && key == 46) || (str[i - 1] == 46 && key != 53) || (str[i-1] == 53 && str[i-2] == 46))
					{
						continue;
					}
					if(key == 46)
					{
						dem++;	
					}
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
			}	
		}
		else
		{
			flag = false;			
		}
	}while(flag);
}

void InputNumberIsFloat(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int dem = 0;
	int key, i = strlen(str);
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if(key == BACKSPACE || key == 46 || (key >= 48 && key <= 57))
		{
			switch(key)
			{	
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						if(str[i - 1] == 46)
						{
							dem = 0;
						}
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length || (strlen(str) == 0 || str[i - 1] == 46 || dem == 1) && key == 46)
					{
						continue;
					}
					if(key == 46)
					{
						dem++;	
					}
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
}


void InputStringIsSchoolYear(char str[],int Length, int ToaDo_X, int ToaDo_Y)
{
	bool flag = true;
	int dem = 0;
	int key, i = strlen(str);
	if(i > 0)
	{
		gotoxy(ToaDo_X,ToaDo_Y);cout<<str;
	}
	gotoxy(ToaDo_X + i,ToaDo_Y);
	do
	{
		key = getch();
		if(key == BACKSPACE || key == 45 || (key >= 48 && key <= 57))
		{
			switch(key)
			{	
				case BACKSPACE:
					if(strlen(str) > 0)
					{
						if(str[i - 1] == 46)
						{
							dem = 0;
						}
						gotoxy(ToaDo_X+i,ToaDo_Y);
						XoaKyTu(str,i-1);
						gotoxy(ToaDo_X+i-1,ToaDo_Y);cout<<" ";
						gotoxy(ToaDo_X+i-1,ToaDo_Y);
						i--;
					}
					break;
				default:
					if(strlen(str) == Length || (strlen(str) == 0 || str[i - 1] == 45 || dem == 1) && key == 45)
					{
						continue;
					}
					if(key == 45)
					{
						dem++;	
					}
					str[i] = char(key);
					str[++i] = '\0';
					gotoxy(ToaDo_X + i - 1,ToaDo_Y);cout<<(char)key;
			}
			
		}
		else
		{
			flag = false;
		}
	}while(flag);
}

