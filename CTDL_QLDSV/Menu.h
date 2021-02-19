#pragma once
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include "myLib.h" 
#include "Controller.h"


void menuMonHoc(int chooseFromMenu1, int chooseFromMenu2);
void menuDangKy(int chooseFromMenu1, int chooseFromMenu2);
void showMenu1(int chon);
void menuLopTinChi(int chooseFromMenu1, int chooseFromMenu2);
void menuDSSV(int chooseFromMenu1, int chooseFromMenu2);
//void Normal() {
//	SetColor(15);
//	SetBGColor(0);
//}
//void HighLight() {
//	SetColor(15);
//	SetBGColor(66);
//}
string SHOW_TEXT_MONHOC[] = {
	"Ma mon hoc  ",
	"Ten mon hoc ",
	"So TCLT     ",
	"So TCTH     "};
string SHOW_TEXT_LOPTC[] = {
	"Ma lop TC   ",
	"Ma mon hoc  ",
	"Nien khoa   ",
	"Hoc ky      ",
	"Nhom        ",
	"So SV max   ",
	"So SV min   "};
string SHOW_TEXT_DSSV[] = {
	"Ma SV       ",
	"Ho          ",
	"Ten         ",
	"Gioi tinh   ",
	"So DT       ",
	"Nam nhap hoc"};
string SHOW_TEXT_DSSV1[] = {
	"Ma SV       ",
	"Ho          ",
	"Ten         ",
	"Gioi tinh   ",
	"So DT       ",
	"Ma lop      ",
	"Nam nhap hoc"};
string SHOW_TEXT_DANGKY[] = {
	"Ma SV       ",
	"Nien khoa   ",
	"Hoc ky      "
};
string SHOW_TEXT_DSSVDK[] = {
	"Ma mon hoc  ",
	"Nien khoa   ",
	"Hoc ky      ",
	"Nhom        "
};
void KhungEdit(int slNhap,string menu[]){
	Normal();
	TaoKhungDon(40, 1, 124, 20);
	TaoKhungDon(40, 22, 124, 19);
	int hang = 25;
	int col = 60;
	for(int i = 0;i < slNhap;i++){
		if(i%4==0 && i!=0){
			hang-=12;
			col+=60;
			gotoxy(col-14,hang+1);
			cout<<menu[i];
			TaoKhungDon(col,hang,40,2);
			hang+=3;
		}else{
			gotoxy(col-14,hang+1);
			cout<<menu[i];
			TaoKhungDon(col,hang,40,2);
			hang+=3;
		}
	}
	Normal();	
}

string TEXT_XACNHAN[] = {
	"Xac nhan",
	"   Huy  "
};
void KhungShow(){
	//gotoxy(40,21);
	Normal();
	clearScreen(40,2,124,40);
	TaoKhungDon(40, 1, 124, 40);
}
void KhungMain(bool flag){
	TaoKhungDon(1, 0, 165, 42);
	TaoKhungDon(3, 1, 35, 5);
	TaoKhungDon(3, 7, 35, 34);
	KhungShow();
	//KhungEdit(7,SHOW_TEXT_LOPTC);
	
}


string MENU_TABLE[] = {
							"1. Quan ly mon hoc               ",
							"2. Quan ly lop tin chi           ",
							"3. Quan ly sinh vien             ",
							"4. Sinh vien dang ky lop tin chi ",
							"5. In danh sach sinh vien dang ky",
							"6. Cap nhat diem                 ",
							"7. In BDMH cua mot lop tin chi   ",
							"8. In DTBKT khoa hoc cua mot lop ",
							"9. In DTK cua cac mon cua SV 1lop",
							"10.Thoat                         "
};
string SHOW_LOP_TIN_CHI_TABLE[] = {
	"1. Them lop tin chi            *",
	"2. Xoa lop tin chi             *",
	"3. Hieu chinh lop tin chi      *" };
string SHOW_SINHVIEN_TABLE[] = {
	"1. Them sinh vien              *",
	"2. Xoa sinh vien               *",
	"3. Hieu chinh sinh vien        *",
	"4. In DSSV tang dan theo MaSV  *" };

string SHOW_MONHOC_TABLE[] = {
	"1. Them mon hoc                *",
	"2. Xoa mon hoc                 *",
	"3. Hieu chinh mon hoc          *",
	"4. In DSMH tang dan theo ten   *" };

string SHOW_DANGKY_TABLE[] = {
	"1. Dang ky                     *",
	"2. Huy dang ky                 *" };



