#pragma once
#include "Common.h"
#include "DangKy.h"
#include "LopTinChi.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "myLib.h"
#include "Menu.h"

int KT_MaMH(DSMH ds, char MaMH[]);
void ThemMonHoc(DSMH &ds, MONHOC mh);
int XoaMonHoc(DSMH &ds,TREE t, char MaMH[]);
void GhiFileMonHoc(DSMH ds);
void DocFileMonHoc(DSMH &ds);
void TaoKhungDanhSachMonHoc(int x, int y, int width, int height);

void NhapThongTinMonHoc(DSMH &ds,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[]);

void SuaMonHoc(DSMH ds,MONHOC &mh,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[]);
void SuaThongTinMonHoc(DSMH &ds,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[]);

void SwapMonHoc(MONHOC *mhA, MONHOC *mhB);
void DanhSachMonHoc_TangDanTheoTen(DSMH ds);
void ShowDanhSachTangDanTheoTen(DSMH ds,int chooseFromMenu1,int chooseFromMenu2);


int KT_MaMH(DSMH ds, char MaMH[])
{
	for(int i = 0; i < ds.n; i++)
	{
		if(strcmp(ds.ds[i]->MAMH,MaMH) == 0)
		{
			return i;
		}
	}
	return -1;
}


void ThemMonHoc(DSMH &ds, MONHOC mh)
{
	ds.ds[ds.n] = new MONHOC();
	*ds.ds[ds.n] = mh;
	ds.n++;
}


int XoaMonHoc(DSMH &ds,TREE t, char MaMH[])
{
	int Vitri = KT_MaMH(ds,MaMH);
	if(Vitri == -1)
	{
		return 0;//ko ton tai trong danh sach
	}
	else
	{
		for(int i = Vitri + 1; i < ds.n; i++)
		{
			ds.ds[i - 1] = ds.ds[i];
		}
		ds.n--;
		return 1;//Xoa thanh cong
	}
}


void GhiFileMonHoc(DSMH ds)
{
	ofstream f;
	f.open(FILE_MONHOC,ios::out);
	f<<ds.n<<endl;
	if(ds.n > 0 && ds.n < MAX)
	{
		for(int i = 0; i< ds.n;i++)
		{
			f<<ds.ds[i]->MAMH<<" "<<ds.ds[i]->STCLT<<" "<<ds.ds[i]->STCTH<<endl;
			f<<ds.ds[i]->TENMH<<endl;
		}
	}
	f.close();
}

void DocFileMonHoc(DSMH &ds)
{
	fstream f;
	f.open(FILE_MONHOC,ios::in);
	if(f.fail())
	{
		cout<<"file khong ton tai";
		getch();
		return;
	}
	int n = 0;
	string TenMH;
	string space;
	f>>n;
	for(int i = 0; i<n;i++)
	{
		MONHOC mh;
		f>>mh.MAMH;
		f>>mh.STCLT;
		f>>mh.STCTH;
		getline(f,space);
		getline(f,TenMH); strcpy(mh.TENMH,TenMH.c_str());
		ThemMonHoc(ds,mh);
	}
	f.close();
}

void SwapMonHoc(MONHOC *mhA, MONHOC *mhB)
{
	MONHOC temp = *mhA;
	*mhA = *mhB;
	*mhB = temp;
}

void DanhSachMonHoc_TangDanTheoTen(DSMH ds)
{
	for(int i = 0; i < ds.n;i++)
	{
		for(int j = i+1; j < ds.n;j++)
		{
			if(strcmp(ds.ds[i]->TENMH,ds.ds[j]->TENMH) > 0)
			{
				MONHOC *mhA = ds.ds[i];
				MONHOC *mhB = ds.ds[j];
				SwapMonHoc(mhA,mhB);
			}
		}
	}
}


void TaoKhungDanhSachMonHoc(int x, int y, int width, int height)
{
	TaoKhungDon(x, y, width, height);
	SetColor(10);
	gotoxy(x+10, y+2); cout << "MA MON HOC";
	gotoxy(x+50, y+2); cout << "TEN MON HOC";
	gotoxy(x+90, y+2); cout << "STCLT";
	gotoxy(x+110, y+2); cout << "STCTH";
	Normal();
	//======== Chot ================
	gotoxy(x+30, y); cout << char(194);
	gotoxy(x+80, y); cout << char(194);
	gotoxy(x+100, y); cout << char(194);
	//==============================
	gotoxy(x+30, y+3); cout << char(193);
	gotoxy(x+80, y+3); cout << char(193);
	gotoxy(x+100, y+3); cout << char(193);
	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
	//==============================
	for (int i = y+1; i < y+3; i++)
	{
		if (i !=  5)
		{
			gotoxy(x+30, i); cout << char(179);
			gotoxy(x+80, i); cout << char(179);
			gotoxy(x+100, i); cout << char(179);
		}
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+30 && i != x+80 && i != x+100)
		{
			gotoxy(i, 4); cout << char(196);
		}
	}
}

void ShowDanhSachTangDanTheoTen(DSMH ds,int chooseFromMenu1,int chooseFromMenu2)
{
	Normal();
	TaoKhungDanhSachMonHoc(40, 1, 124, 40);
	int key,col = 40,hang = 5;
	if(ds.n > 0)
	{
		DanhSachMonHoc_TangDanTheoTen(ds);
		for (int i = 0; i < ds.n; i++)
		{
			gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
			gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
			gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
			gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
			hang++;
		}
	}
	do
	{
		key = getch();
		switch(key)
		{
			case ESC:
				clearScreen(40,1,125,40);
				KhungShow();
				backMenu2(chooseFromMenu1,chooseFromMenu2);
				break;
			default:
				continue;
		}
	}while(1);
	
}
void NhapThongTinMonHoc(DSMH &ds,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	clearScreen(40,22,124,19);
	bool flag = false;
	int chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,Text);
	MONHOC mh;
	char MAMH[11] = "";
	char TENMH[51] = "";
	char STCLT[5] = "";
	char STCTH[5] = "";
	
	TaoKhungDanhSachMonHoc(40, 1, 124, 20);
	if(ds.n > 0)
	{
		for (int i = 0; i < ds.n; i++)
		{
			gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
			gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
			gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
			gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
			hang++;
		}
	}
	col = 61 ;hang = 26;
	int key;
	do{
		switch(chon){
				case 0:
					InputCodeToUpper(MAMH,10,col,hang);
					break;
				case 1:
					InputStringName(TENMH,50,col,hang+3);
					break;
				case 2:
					InputNumberSTCIsFloat(STCLT,4,col,hang+6);
					break;
				case 3:
					InputNumberSTCIsFloat(STCTH,4,col,hang +9);
					break;
				default:
					continue; 
			}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key){
			case UP:
				if(chon > 0){chon--;}
					else{chon = 3;}
					break;
			case DOWN:
				if(chon < 3){chon++;}
					else{chon = 0;}
					break;
				break;
			case ESC:
				if(ThongBao("Ban chac chan muon thoat?Y/N") == 'Y')
				{
					clearScreen(40,1,125,40);
					KhungShow();
					backMenu2(chooseFromMenu1,chooseFromMenu2);
				}
				break;
			case ENTER:
				flag = true;
				c = XacNhanEdit(TEXT_XACNHAN,flag);
				Normal();
				if(strlen(MAMH) == 0)
				{
					gotoxy(70,40) ;cout<<"Ma mon hoc khong duoc de trong";
					chon = 0;
				}
				else if(strlen(TENMH) == 0)
				{
					gotoxy(70,40) ;cout<<"Ten mon hoc khong duoc de trong";
					chon = 1;
				}
				else if(strlen(STCLT) == 0)
				{
					gotoxy(70,40) ;cout<<"So tin chi ly thuyet khong duoc de trong";
					chon = 2;
				}
				else if(strlen(STCTH) == 0)
				{
					gotoxy(70,40) ;cout<<"So tin chi thuc hanh khong duoc de trong";
					chon = 3;
				}
				else if(KT_MaMH(ds,MAMH) != -1)
				{
					gotoxy(70,40) ;cout<<"Ma mon hoc trung";
					chon = 0;
				}
				else
				{
					if(c==0)
					{
						strcpy(mh.MAMH,MAMH);
						strcpy(mh.TENMH,TENMH);
						mh.STCLT = atof(STCLT);
						mh.STCTH = atof(STCTH);
						if(ThongBao("Ban chac chan muon luu?Y/N") == 'N')
						{
							NhapThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);	
						}
						ThemMonHoc(ds,mh);
						gotoxy(70,38) ;cout<<"Them thanh cong";
						GhiFileMonHoc(ds);
						col = 40;
						hang = 5;
						if(ds.n > 0)
						{
							for (int i = 0; i < ds.n; i++)
							{
								gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
								gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
								gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
								gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
								hang++;
							}
						}
						if(ThongBao("Ban muon tiep tuc them mon hoc?Y/N") == 'Y')
						{
							NhapThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							clearScreen(40,1,125,40);
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}
					else{
						NhapThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);	
					}
				}
				flag = false;
				XacNhanEdit(TEXT_XACNHAN,flag);
				break;
			default:
				continue;
		}
	}while(1);
}


void SuaMonHoc(DSMH ds,MONHOC &mh,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	bool flag = false;
	int key, chon = 0;
	int col = 61 ,hang = 26;
	KhungEdit(slItem,Text);
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	char TENMH[51] = "";
	char STCLT[5] = "";
	char STCTH[5] = "";
	
	stringstream ssSTCLT;
	ssSTCLT<<mh.STCLT;
	string STCLTtemp = ssSTCLT.str();
	strcpy(STCLT,STCLTtemp.c_str());
	

	strcpy(TENMH,mh.TENMH);
	
	stringstream ssSTCTH;
	ssSTCTH<<mh.STCTH;
	string STCTHtemp = ssSTCTH.str();
	strcpy(STCTH,STCTHtemp.c_str());
	
	
	do{
		switch(chon){
				case 0:
					InputStringName(TENMH,50,col,hang+3);
					break;
				case 1:
					InputNumberSTCIsFloat(STCLT,4,col,hang+6);
					break;
				case 2:
					InputNumberSTCIsFloat(STCTH,4,col,hang +9);
					break;
				default:
					continue; 
			}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key){
			case UP:
				if(chon > 0){chon--;}
					else{chon = 2;}
					break;
			case DOWN:
				if(chon < 2){chon++;}
					else{chon = 0;}
					break;
				break;
			case ESC:
				if(ThongBao("Ban chac chan muon thoat?Y/N") == 'Y')
				{
					clearScreen(40,1,125,40);
					KhungShow();
					backMenu2(chooseFromMenu1,chooseFromMenu2);
				}
				break;
			case ENTER:
				flag = true;
				c = XacNhanEdit(TEXT_XACNHAN,flag);
				Normal();
				if(strlen(TENMH) == 0)
				{
					gotoxy(70,40) ;cout<<"Ten mon hoc khong duoc de trong";
					chon = 0;
				}
				else if(strlen(STCLT) == 0)
				{
					gotoxy(70,40) ;cout<<"So tin chi ly thuyet khong duoc de trong";
					chon = 1;
				}
				else if(strlen(STCTH) == 0)
				{
					gotoxy(70,40) ;cout<<"So tin chi thuc hanh khong duoc de trong";
					chon = 2;
				}
				else
				{
					if(c==0){
						if(ThongBao("Ban chac chan muon luu?Y/N") == 'N')
						{
							SuaThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);	
						}
						strcpy(mh.TENMH,TENMH);
						mh.STCLT = atof(STCLT);
						mh.STCTH = atof(STCTH);
						GhiFileMonHoc(ds);
						gotoxy(70,38) ;cout<<"Sua thanh cong";
						col = 40;
						hang = 5;
						if(ds.n > 0)
						{
							for (int i = 0; i < ds.n; i++)
							{
								gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
								gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
								gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
								gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
								hang++;
							}
						}
						if(ThongBao("Ban muon tiep tuc sua mon hoc?Y/N") == 'Y')
						{
							SuaThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							clearScreen(40,1,125,40);
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}else{
						SuaThongTinMonHoc(ds,chooseFromMenu1,chooseFromMenu2,slItem,Text);	
					}
				}
			flag = false;
			XacNhanEdit(TEXT_XACNHAN,flag);
			break;
		default:
			continue;
		}
	}while(1);
}


void SuaThongTinMonHoc(DSMH &ds,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	if(ds.n == 0)
	{
		return ;
	}
	Normal();
	clearScreen(40,1,125,40);
	bool flag = false;
	int chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,Text);
	
	int dong = 0;
	int key;
	TaoKhungDanhSachMonHoc(40, 1, 124, 20);
	if(ds.n > 0)
	{
		for (int i = 0; i < ds.n; i++)
		{
			gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
			gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
			gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
			gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
			hang++;
		}
	}
	hang = 5;
	HighLight();
	for(int i = 41; i < 164;i++)
	{
		gotoxy(i,hang);cout<<" ";
	}
	gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
	gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
	gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
	gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
	Normal();
	
	int coll = 61,hangg = 26;
	gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
	gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
	gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
	gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
	do
	{
		key = getch();
		switch(key)
		{
			case DOWN:
				if(dong +1 < ds.n)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					hang++;
					dong++;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					
					Normal();
					
					gotoxy(coll, hangg); cout << "                               ";
					gotoxy(coll, hangg + 3); cout << "                               ";
					gotoxy(coll, hangg+ 6); cout << "                               ";
					gotoxy(coll, hangg + 9); cout << "                               ";
					
					gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
					gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
					gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
					gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
				}
				break;
			case UP:
				if(dong > 0)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					hang--;
					dong--;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					
					Normal();
					
					gotoxy(coll, hangg); cout << "                               ";
					gotoxy(coll, hangg + 3); cout << "                               ";
					gotoxy(coll, hangg+ 6); cout << "                               ";
					gotoxy(coll, hangg + 9); cout << "                               ";
					
					gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
					gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
					gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
					gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
				}
				break;
			case ENTER:
				SuaMonHoc(ds,*ds.ds[dong],chooseFromMenu1,chooseFromMenu2,slItem,Text);
				flag = false;
				XacNhanEdit(TEXT_XACNHAN,flag);
				break;
			case ESC:
				if(ThongBao("Ban chac chan muon thoat?Y/N") == 'Y')
				{
					clearScreen(40,1,125,40);
					KhungShow();
					backMenu2(chooseFromMenu1,chooseFromMenu2);
				}
				break;
			default:
				continue;
		}
	}while(1);
}

void XoaThongTinMonHoc(DSMH &ds,TREE t,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	clearScreen(40,22,124,19);
	bool flag = false;
	int chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,Text);
	
	int dong = 0;
	int key;
	TaoKhungDanhSachMonHoc(40, 1, 124, 20);
	if(ds.n > 0)
	{
		for (int i = 0; i < ds.n; i++)
		{
			gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
			gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
			gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
			gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
			hang++;
		}
	}
	hang = 5;
	HighLight();
	for(int i = 41; i < 164;i++)
	{
		gotoxy(i,hang);cout<<" ";
	}
	gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
	gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
	gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
	gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
	Normal();
	
	int coll = 61,hangg = 26;
	gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
	gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
	gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
	gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
	do
	{
		key = getch();
		Normal();
		clearScreen(70,38,60,3);
		switch(key)
		{
			case DOWN:
				if(dong +1 < ds.n)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					hang++;
					dong++;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					
					Normal();
					
					gotoxy(coll, hangg); cout << "                               ";
					gotoxy(coll, hangg + 3); cout << "                               ";
					gotoxy(coll, hangg+ 6); cout << "                               ";
					gotoxy(coll, hangg + 9); cout << "                               ";
					
					gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
					gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
					gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
					gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
				}
				break;
			case UP:
				if(dong > 0)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					hang--;
					dong--;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
					gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
					gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
					gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
					
					Normal();
					
					gotoxy(coll, hangg); cout << "                               ";
					gotoxy(coll, hangg + 3); cout << "                               ";
					gotoxy(coll, hangg+ 6); cout << "                               ";
					gotoxy(coll, hangg + 9); cout << "                               ";
					
					gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
					gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
					gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
					gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
				}
				break;
			case ENTER:
				flag = true;
				c = XacNhanEdit(TEXT_XACNHAN,flag);
				Normal();
				if(c == 0)
				{
					if(ThongBao("Ban chac chan muon xoa?Y/N") == 'N')
					{
						XoaThongTinMonHoc(ds,t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
					}
					char MaMH[11] = "";
					strcpy(MaMH,ds.ds[dong]->MAMH);
					int kq = XoaMonHoc(ds,t,MaMH);
					if(kq == 0)
					{
						gotoxy(70,38) ;
						cout<<"Mon hoc khong ton tai";
						continue;
					}
					else
					{
						gotoxy(70,38) ;
						cout<<"Xoa thanh cong";
						GhiFileMonHoc(ds);
						col = 40;
						hang = 5;
						clearScreen(40,1,125,40);
						TaoKhungDanhSachMonHoc(40, 1, 124, 20);
						KhungEdit(slItem,Text);
						if(ds.n > 0)
						{
							for (int i = 0; i < ds.n; i++)
							{
								gotoxy(col + 13, hang); cout << ds.ds[i]->MAMH;
								gotoxy(col + 40, hang); cout << ds.ds[i]->TENMH;
								gotoxy(col + 90, hang); cout << ds.ds[i]->STCLT;
								gotoxy(col + 110, hang); cout << ds.ds[i]->STCTH;
								hang++;
							}
							
							hang = 5;
							HighLight();
							for(int i = 41; i < 164;i++)
							{
								gotoxy(i,hang);cout<<" ";
							}
							gotoxy(col + 13, hang); cout << ds.ds[dong]->MAMH;
							gotoxy(col + 40, hang); cout << ds.ds[dong]->TENMH;
							gotoxy(col + 90, hang); cout << ds.ds[dong]->STCLT;
							gotoxy(col + 110, hang); cout << ds.ds[dong]->STCTH;
							Normal();
							
							int coll = 61,hangg = 26;
							gotoxy(coll, hangg); cout << ds.ds[dong]->MAMH;
							gotoxy(coll, hangg + 3); cout << ds.ds[dong]->TENMH;
							gotoxy(coll, hangg + 6); cout << ds.ds[dong]->STCLT;
							gotoxy(coll, hangg + 9); cout << ds.ds[dong]->STCTH;
						}
						Normal();
						if(ThongBao("Ban muon tiep tuc xoa mon hoc?Y/N") == 'Y')
						{
							XoaThongTinMonHoc(ds,t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							clearScreen(40,1,125,40);
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}
				}
				else{
						XoaThongTinMonHoc(ds,t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
					}
				flag = false;
				XacNhanEdit(TEXT_XACNHAN,flag);
				break;
			case ESC:
				if(ThongBao("Ban chac chan muon thoat?Y/N") == 'Y')
				{
					clearScreen(40,1,125,40);
					KhungShow();
					backMenu2(chooseFromMenu1,chooseFromMenu2);
				}
				break;
			default:
				continue;
		}
	}while(1);
}
