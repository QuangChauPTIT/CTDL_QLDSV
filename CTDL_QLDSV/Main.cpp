#pragma once
#include <time.h>
#include "Controller.h"
#include "SinhVien.h"
#include "MonHoc.h"
#include "LopTinChi.h"
using namespace std;

bool flag = true;




void menuMonHoc(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_MONHOC_TABLE, SHOW_MONHOC_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		NhapThongTinMonHoc(dsmh,chooseFromMenu1, c,SHOW_MONHOC_ITEM,SHOW_TEXT_MONHOC);
		break;
	case 1:
		XoaThongTinMonHoc(dsmh,t,chooseFromMenu1, c,SHOW_MONHOC_ITEM,SHOW_TEXT_MONHOC);
		break;
	case 2:
		SuaThongTinMonHoc(dsmh,chooseFromMenu1,c,SHOW_MONHOC_ITEM,SHOW_TEXT_MONHOC);
		break;
	case 3:
		ShowDanhSachTangDanTheoTen(dsmh,chooseFromMenu1,c);
		KhungShow();
		break;
	case ESC:
		backMenu1(SHOW_MONHOC_ITEM, chooseFromMenu1);
		break;
	case LEFT:
		backMenu1(SHOW_MONHOC_ITEM, chooseFromMenu1);
		break;
	}
}

void menuDangKy(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_DANGKY_TABLE, SHOW_DANGKY_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		ThemTTDK(t,chooseFromMenu1,c);
		break;
	case 1:{
		char masv[12]="";
		NhapMaSV(t,masv,chooseFromMenu1,c);
		break;
	}
	case ESC:
		backMenu1(SHOW_DANGKY_ITEM, chooseFromMenu1);
		break;
	case LEFT:
		backMenu1(SHOW_DANGKY_ITEM, chooseFromMenu1);
		break;
	}
}

void menuLopTinChi(int chooseFromMenu1, int chooseFromMenu2) {
	int c = Menu2Choose(SHOW_LOP_TIN_CHI_TABLE, MENU_LOP_TIN_CHI_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:
		NhapThongTinLopTinChi(t,dsmh,chooseFromMenu1,c,SHOW_ITEM_LOPTC,SHOW_TEXT_LOPTC);
		break;
	case 1:
		XoaThongTinLopTinChi(t,chooseFromMenu1,c,SHOW_ITEM_LOPTC,SHOW_TEXT_LOPTC);
		break;
	case 2:
		SuaThongTinLopTinChi(t,dsmh,chooseFromMenu1,c,SHOW_ITEM_LOPTC,SHOW_TEXT_LOPTC);
		break;
	case 3:
		//backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	case ESC:
		backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	case LEFT:
		backMenu1(MENU_LOP_TIN_CHI_ITEM, chooseFromMenu1);
		break;
	}
}

// DSSV menu
void menuDSSV(int chooseFromMenu1, int chooseFromMenu2) {
	chooseFromMenu2 = 0;
	int c = Menu2Choose(SHOW_SINHVIEN_TABLE, SHOW_SINHVIEN_ITEM, chooseFromMenu2);
	switch (c) {
	case 0:{
		char mlop[15]="";
		insertMALOP(mlop,chooseFromMenu1,c);
		break;
	}
	case 1:{
		char mlop[15]="";
		deletedSvByMasv(mlop,chooseFromMenu1,c);
		break;
	}
	case 2:{
		char mlop[15]="";
		editSvByMasv(mlop,chooseFromMenu1,c);
		break;
	}
	case 3:
		insertMALOP_INDSSV(head,chooseFromMenu1,c);
		break;
	case ESC:
		backMenu1(SHOW_SINHVIEN_ITEM, chooseFromMenu1);
		break;
	case LEFT:
		backMenu1(SHOW_SINHVIEN_ITEM, chooseFromMenu1);
		break;
	}
}


void showMenu1(int chon) {
	if (chon == -1) {
		DocFileMonHoc(dsmh);
		DocFileLopTinChi(t);
		DocFileSinhVien(head);
		chon = MenuChoose(0);
	}
	else {
		chon = MenuChoose(chon);
	}
	switch (chon) {
	case 0:
		Normal();
		menuMonHoc(chon, 0);
		break;
	case 1:
		Normal();
		menuLopTinChi(chon, 0);
		break;
	case 2:
		Normal();
		menuDSSV(chon, 0);
		break;
	case 3:
		Normal();
		menuDangKy(chon, 0);
		break;
	case 4:
		Normal();
		ShowDSSV_LTC_NienKhoa_HocKy_Nhom_MaMH(t,head,chon,0,SHOW_ITEM_DSSVDK,SHOW_TEXT_DSSVDK);
		break;
	case 5:
		Normal();
		NhapDiem(t,head,chon,0,SHOW_ITEM_DSSVDK,SHOW_TEXT_DSSVDK);
		break;
	case 6:
		Normal();
		Nhap_4_Field(t,chon,0);
		break;
	case 7:
		Normal();
		//XoaMenu(7);
		onExitProgram(chon);
		
		break;
	case 8:
		onExitProgram(chon);
		break;
	case 9: {
		onExitProgram(chon);
		break;
	}

	}
}

int main()
{
	system("cls");
	setFullScreen();
	gotoxy(10,3);
	SetColor(12);
	cout<<"QUAN LY DIEM SINH VIEN";
	Normal();
	flag = true;
	KhungMain(flag);
	showMenu1(-1);
}

