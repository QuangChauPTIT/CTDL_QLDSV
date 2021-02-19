#pragma once
#include "Menu.h"
#include "Common.h"
using namespace std;


#define MENU_ITEM 10

#define Y_MENU_1 10
#define X_MENU_1 4 

#define MENU_LOP_TIN_CHI_ITEM 3
#define SHOW_SINHVIEN_ITEM 4
#define SHOW_MONHOC_ITEM 4
#define SHOW_DANGKY_ITEM 2

#define SHOW_ITEM_LOPTC 7
#define SHOW_ITEM_DSSV 6
#define SHOW_ITEM_DANGKY 3
#define SHOW_ITEM_DSSVDK 4
void onExitProgram(int chooseFromMenu1) {
	int rs = showMessageBox("Thoat", "Ban muon thoat khoi chuong trinh ???", MB_ICONQUESTION);
	if (rs == IDOK) {
		exitProgram();
	}
	if (chooseFromMenu1 >= 0) {
		showMenu1(chooseFromMenu1);
	}
}
int MenuChoose(int chon) {
	Normal();
	int i;
	for (i = 0; i < MENU_ITEM; i++)
	{
		gotoxy(X_MENU_1, Y_MENU_1 + i);
		cout << MENU_TABLE[i];
	}
	HighLight();
	gotoxy(X_MENU_1, Y_MENU_1 + chon);
	cout << MENU_TABLE[chon];
	char kytu;
	do {
		if (_kbhit()) {
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu) {
			case UP:
				if (chon > 0) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
					chon--;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];

					chon = MENU_ITEM - 1;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				break;
			case DOWN:
				if (chon < MENU_ITEM - 1) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
					chon++;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];

					chon = 0;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << MENU_TABLE[chon];
				}
				break;
			case ESC:
			{
				onExitProgram(-1);
				break;
			}
			case ENTER:
				return chon;
			case RIGHT:
				return chon;
			}  // end switch
		}
	} while (1);
}
int XacNhanEdit(string Text[], bool flag){
	Normal();
	gotoxy(100,35);
	clearScreen(120,35,20,2);
	int x = 110;
	int y = 35;
	char kytu;
	int chon = 0;
	for(int i = 0;i<2;i++){
		x+=20;
		gotoxy(x,y);
		cout<<Text[i];
	}
	x = 130;
	if(flag == true){
		HighLight();
		gotoxy(x,y);
		cout<<Text[chon];
		do{
			if(_kbhit()){
				kytu = getch();
				if (kytu == 0) kytu = getch();
				switch(kytu){
					case UP:
						if(chon==0){
							Normal();
							gotoxy(x,y);
							cout<<Text[chon];
							chon++;
							HighLight();
							gotoxy(x+20,y);
							cout<<Text[chon];
							
						}else{
							Normal();
							gotoxy(x+20,y);
							cout<<Text[chon];
							chon--;
							HighLight();
							gotoxy(x,y);
							cout<<Text[chon];
							
						}
						break;
					case LEFT:
						if(chon==0){
							Normal();
							gotoxy(x,y);
							cout<<Text[chon];
							chon++;
							HighLight();
							gotoxy(x+20,y);
							cout<<Text[chon];
						}else{
							Normal();
							gotoxy(x+20,y);
							cout<<Text[chon];
							chon--;
							HighLight();
							gotoxy(x,y);
							cout<<Text[chon];
						}
						break;
					case DOWN:
						if(chon==1){
							Normal();
							gotoxy(x+20,y);
							cout<<Text[chon];
							chon--;
							HighLight();
							gotoxy(x,y);
							cout<<Text[chon];
						}else{
							Normal();
							gotoxy(x,y);
							cout<<Text[chon];
							chon++;
							HighLight();
							gotoxy(x+20,y);
							cout<<Text[chon];
						}
						break;
					case RIGHT:
						if(chon==1){
							Normal();
							gotoxy(x+20,y);
							cout<<Text[chon];
							HighLight();
							chon--;
							gotoxy(x,y);
							cout<<Text[chon];
						}else{
							Normal();
							gotoxy(x,y);
							cout<<Text[chon];
							chon++;
							HighLight();
							gotoxy(x+20,y);
							cout<<Text[chon];
						}
						break;
					case ENTER:
						return chon;
						break;
					case ESC:
						return ESC;
						break;
				}
			}	
		}while(1);
	}
}
int Menu2Choose(string td[], int slMenu, int chon) {
	Normal();
	clearScreen(4,10,33,MENU_ITEM);
	int i;
	for (i = 0; i < slMenu; i++)
	{
		gotoxy(X_MENU_1, Y_MENU_1 + i);
		cout << td[i];
	}
	HighLight();
	gotoxy(X_MENU_1, Y_MENU_1 + chon);
	cout << td[chon];
	char kytu;
	do {
		if (_kbhit()) {
			kytu = _getch();
			if (kytu == 0) kytu = _getch();
			switch (kytu) {
			case UP:
				if (chon > 0) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
					chon--;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
				}
				else {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];

					chon = slMenu - 1;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
				}
				break;
			case DOWN:
				if (chon < slMenu - 1) {
					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
					chon++;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
				}
				else {

					Normal();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
					chon = 0;
					HighLight();
					gotoxy(X_MENU_1, Y_MENU_1 + chon);
					cout << td[chon];
				}
				break;
			case LEFT:
				return LEFT;
				break;
			case ESC:
				return ESC;
				break;
			case ENTER:
				return chon;
			}  // end switch
		}
	} while (1);
}
void backMenu1(int slItem, int chooseOld) {
	Normal();
	clearScreen(4,10,25,slItem);
	showMenu1(chooseOld);
}
void backMenu2(int chooseMenu1,int chooseMenu2){
	Normal();
	KhungShow();
	int chooseOld = chooseMenu1;
	switch(chooseOld){
		case 0:
			Normal();
			menuMonHoc(chooseMenu1,chooseMenu2);
			break;
		case 1:
			Normal();
			menuLopTinChi(chooseMenu1, chooseMenu2);
			break;
		case 2:
			Normal();
			menuDSSV(chooseMenu1, chooseMenu2);
			break;
		case 3:
			Normal();
			menuDangKy(chooseMenu1, chooseMenu2);
			break;
		case 4:
			Normal();
			backMenu1(10,chooseMenu1);
			break;
		case 5:
			Normal();
			backMenu1(10,chooseMenu1);
			break;
		case 6:
			Normal();
			backMenu1(10,chooseMenu1);
			break;
		case 7:
			Normal();
			backMenu1(10,chooseMenu1);
			break;
	}
}

void onExitEdit(int chooseFromMenu1,int chooseFromMenu2,string Text) {
	int rs = showMessageBox("THONG BAO", Text, MB_ICONQUESTION);
	char malop[slMax]="";
	char masv[slMax]="";
	if (rs == IDOK) {
		strcpy(MALOPSV,malop);
		strcpy(MASVSV,masv);
		backMenu2(chooseFromMenu1,chooseFromMenu2);
	}
}

