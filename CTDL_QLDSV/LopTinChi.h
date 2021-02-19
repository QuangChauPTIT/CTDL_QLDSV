#pragma once
#include "Common.h"
#include "DangKy.h"
#include "LopTinChi.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "myLib.h"


void XuatDanhSachSinhVienTheoMASV(NODESV nsv,int dem,bool flag);
NODESV searchSV(NODESV nsv,char Masv[]);


int DemDangKy(NODEDK ndk);
int ThemNodeDK(NODEDK &ndk, DANGKY dk);
int checkMasv(NODESV nsv, char Masv[]);
void ThemLopSVDK(TREE &t,LOPTC ltc[],int m,char MASV[],int choose1,int choose2,int hky,char nkhoa[]);
void Them_CoTTDK(NODEDK &First,DANGKY dky);
NODESV searchSV(NODESV nsv,char Masv[]);
void Them_DauDK(NODEDK &First,DANGKY dky);

void NhapMaSV(TREE &t,char masv[],int chooseFromMenu1,int chooseFromMenu2);
void HuyDKLTC(TREE &t,char masv[],int chooseFromMenu1,int chooseFromMenu2);
void In_Bang_Diem_LTC(LOPTC ltc,int choose1,int choose2);
void MangTamLopTinChi(TREE t, LOPTC ltc[], int &dem);

//===============================
void KhoiTaoCay(TREE &t);
void GhiFileMaLopTinChi(int arr[], int n);
int DocFileMaLopTinChi();
void GhiLopTinChi(TREE t, ofstream &f);
void GhiFileLopTinChi(TREE t);

int TongSoLopTinhChi(TREE t);
int KT_4_Field(TREE t, char MaMH[], char NienKhoa[], int HocKy, int Nhom);
void XoaMaLopTinChi(int arr[],int &n, int vitri);
void ThemLopTinChi(TREE &p, LOPTC ltc);
void SuaThongTinLopTinChi(TREE &t, DSMH dsmh,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[]);


void ThemDiemVaoDanhSachDangKy(TREE &t, int MaLTC, char diem[][5], int slsv);
void ChinhSuaDiem(TREE &t,int MaLTC,int chooseFromMenu1,int chooseFromMenu2);
void NhapDiem(TREE &t,NODESV node,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[]);


void KhoiTaoCay(TREE &t)
{
	t = NULL;
}

void ThemLopTinChi(TREE &t, LOPTC ltc)
{
	if(t == NULL)
	{
		t = new NodeLopTinChi();
		t->LopTC = ltc;
		t->pLeft = NULL;
		t->pRight = NULL;
	}
	else
	{
		if(t->LopTC.MALOPTC > ltc.MALOPTC)
		{
			ThemLopTinChi(t->pLeft,ltc);
		}
		else if(t->LopTC.MALOPTC < ltc.MALOPTC)
		{
			ThemLopTinChi(t->pRight,ltc);
		}
	}
}

int KT_4_Field(TREE t, char MaMH[], char NienKhoa[], int HocKy, int Nhom)
{
	int dem = 0;
	int slltc = TongSoLopTinhChi(t);
	LOPTC ltc[slltc];
	MangTamLopTinChi(t,ltc,dem);
	for(int i = 0 ; i < dem; i++)
	{
		if(strcmp(ltc[i].NIENKHOA,NienKhoa) == 0 && ltc[i].HOCKY == HocKy && ltc[i].NHOM == Nhom && strcmp(ltc[i].MAMH,MaMH) == 0)
		{
			return 1;
		}
	}
	return 0;
}

// xoa lop tin chi khoi mang sau khi lay ra de them lop tin chi
void XoaMaLopTinChi(int arr[],int &n, int vitri)
{
	for(int i = vitri + 1; i < n; i++)
	{
		arr[i - 1] = arr[i];
	}
	n--;
}

// ghi mang lop tin chi vo file
void GhiFileMaLopTinChi(int arr[], int n)
{
	ofstream f;
	f.open(FILE_MALOPTINCHI,ios::out);
	f<<n<<endl;
	for(int i = 0; i< n;i++)
	{
		f<<arr[i]<<" ";
	}
	f.close();
}

int DocFileMaLopTinChi()
{
	int n, res = 0;
	fstream f;
	f.open(FILE_MALOPTINCHI,ios::in);
	if(f.fail())
	{
		cout<<"file khong ton tai";
		getch();
		return 0;
	}
	f>>n;
	if(n > 0)
	{
		int arr[n];
		for(int i = 0; i< n;i++)
		{
			int SoNgauNhien;
			f>>SoNgauNhien;
			arr[i] = SoNgauNhien;
		}
		res = arr[0];
		XoaMaLopTinChi(arr,n,0);
		GhiFileMaLopTinChi(arr,n);
	}
	return res;
}

// tong lop tin chi
int TongSoLopTinhChi(TREE t)
{
	if(t == NULL)
	{
		return 0;
	}
	else
	{
		return TongSoLopTinhChi(t->pLeft) + TongSoLopTinhChi(t->pRight) + 1;
	}
}
void GhiLopTinChi(TREE t, ofstream &f)
{
	if(t != NULL)
	{
		GhiLopTinChi(t->pLeft,f);
		GhiLopTinChi(t->pRight,f);
		LopTinChi ltc;
		ltc = t->LopTC;
		f<<ltc.MALOPTC <<" "<<ltc.MAMH<<" "<<ltc.NIENKHOA<<" "<<ltc.HOCKY<<" "<<ltc.NHOM<<" "<<ltc.MAXSV<<" "<<ltc.MINSV<<endl;
		//Luu danh sach dang ky
		int sldk = 0;
		
		NODEDK ndk = ltc.pHead;
		if(ndk != NULL)
		{
			sldk = DemDangKy(ndk);
		}
		f<<sldk<<endl;
		if(sldk>0){
			for(NODEDK p = ndk;p != NULL;p =p->pNext)
			{
				DANGKY dky = p->dk;
				f<<dky.MASV<<" "<<dky.DIEM<<endl;
			}
		}
	}
}
void GhiFileLopTinChi(TREE t)
{
	ofstream f;
	f.open(FILE_LOPTINCHI,ios::out);
	if(f.fail())
	{
		cout<<"file khong ton tai";
		getch();
		return;
	}
	int slltc = TongSoLopTinhChi(t);
	f<<slltc<<endl;
	if(t!=NULL)
	{
		GhiLopTinChi(t,f);
	}
	f.close();
}


void DocFileLopTinChi(TREE &t)
{
	ifstream f;
	f.open(FILE_LOPTINCHI,ios::in);
	if(f.fail())
	{
		cout<<"file khong ton tai";
		getch();
		return;
	}
	int slltc = 0;
	int sldk = 0;
	f>>slltc;
	string space;
	if(slltc > 0)
	{
		for(int i = 0; i < slltc; i++)
		{
			LOPTC ltc;
			f>>ltc.MALOPTC;
			f>>ltc.MAMH;
			f>>ltc.NIENKHOA;
			f>>ltc.HOCKY;
			f>>ltc.NHOM;
			f>>ltc.MAXSV;
			f>>ltc.MINSV;
			ltc.pHead = NULL;
			f>>sldk;
			DANGKY dk;
			for(int j = 0; j < sldk;j++){
				f>>dk.MASV;
				f>>dk.DIEM;
				int x = ThemNodeDK(ltc.pHead,dk);
				if(x == 0){
					gotoxy(70, 40); cout << "Doc file that bai";
				}
			}
			ThemLopTinChi(t,ltc);
		}
	}
	f.close();
}
// show danh sach ltc
void TaoKhungDanhSachLopTinChi(int x, int y, int width, int height)
{
	TaoKhungDon(x, y, width, height);
	SetColor(10);
	gotoxy(x+3, y+2); cout << "MA LOP TIN CHI";
	gotoxy(x+26, y+2); cout << "MA MON HOC";
	gotoxy(x+52, y+2); cout << "NIEN KHOA";
	gotoxy(x+75, y+2); cout << "HOC KY";
	gotoxy(x+88, y+2); cout << "NHOM";
	gotoxy(x+100, y+2); cout << "MAXSV";
	gotoxy(x+114, y+2); cout << "MINSV";
	Normal();
	//======== Chot ================
	gotoxy(x+20, y); cout << char(194);
	gotoxy(x+42, y); cout << char(194);
	gotoxy(x+70, y); cout << char(194);
	gotoxy(x+85, y); cout << char(194);
	gotoxy(x+95, y); cout << char(194);
	gotoxy(x+110, y); cout << char(194);
//	//==============================
	gotoxy(x+20, y + 3); cout << char(193);
	gotoxy(x+42, y + 3); cout << char(193);
	gotoxy(x+70, y + 3); cout << char(193);
	gotoxy(x+85, y + 3); cout << char(193);
	gotoxy(x+95, y + 3); cout << char(193);
	gotoxy(x+110, y + 3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
//	//==============================
	for (int i = y+1; i < y+3; i++)
	{
		gotoxy(x+20, i); cout << char(179);
		gotoxy(x+42, i); cout << char(179);
		gotoxy(x+70, i); cout << char(179);
		gotoxy(x+85, i); cout << char(179);
		gotoxy(x+95, i); cout << char(179);
		gotoxy(x+110, i); cout << char(179);
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+20 && i != x+42 && i != x+70 && i != x+ 85&& i != x+ 95&& i != x+ 110)
		{
			gotoxy(i,y + 3); cout << char(196);
		}
	}
}

void MangTamLopTinChi(TREE t, LOPTC ltc[], int &dem)
{
	if(t!=NULL)
	{
		MangTamLopTinChi(t->pLeft,ltc,dem);
		MangTamLopTinChi(t->pRight,ltc,dem);
		ltc[dem++] = t->LopTC;
	}
}
void ShowDanhSachLopTinChi(TREE t)
{
	TaoKhungDanhSachLopTinChi(40, 1, 124, 20);	
	int col = 40,hang = 5;
	int dem = 0;
	int slltc = TongSoLopTinhChi(t);
	LOPTC ltc[slltc];
	MangTamLopTinChi(t,ltc,dem);
	if(dem  > 0)
	{
		for(int i = 0; i < dem; i++)
		{
			gotoxy(col+7,hang);cout<<ltc[i].MALOPTC;
			gotoxy(col+27,hang);cout<<ltc[i].MAMH;
			gotoxy(col+52,hang);cout<<ltc[i].NIENKHOA;
			gotoxy(col+77,hang);cout<<ltc[i].HOCKY;
			gotoxy(col+90,hang);cout<<ltc[i].NHOM;
			gotoxy(col+100,hang);cout<<ltc[i].MAXSV;
			gotoxy(col+115,hang);cout<<ltc[i].MINSV;
			hang++;
		}
	}
	
}

//nhap lop tin chi
void NhapThongTinLopTinChi(TREE &t, DSMH dsmh,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	clearScreen(40,1,125,40);
	bool flag = false;
	int key, chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	
	KhungEdit(slItem,Text);
	ShowDanhSachLopTinChi(t);
//	TaoKhungDanhSachMonHoc(40, 1, 124, 20);
//	if(dsmh.n > 0)
//	{
//		for (int i = 0; i < dsmh.n; i++)
//		{
//			gotoxy(col + 13, hang); cout << dsmh.ds[i]->MAMH;
//			gotoxy(col + 40, hang); cout << dsmh.ds[i]->TENMH;
//			gotoxy(col + 90, hang); cout << dsmh.ds[i]->STCLT;
//			gotoxy(col + 110, hang); cout << dsmh.ds[i]->STCTH;
//			hang++;
//		}
//	}

	int MALTC;
	char MAMH[11]="";
	char NIENKHOA[12] = "";
	char HOCKY[2] = "";
	char NHOM[2] ="";
	char MAXSV[4] = "";
	char MINSV[4] = "";
	
	LOPTC ltc;
	
	
	col = 61 ;hang = 26;
	MALTC = DocFileMaLopTinChi();
	gotoxy(col,hang) ;cout<< MALTC;
	ltc.MALOPTC = MALTC;
	
	do
	{
		switch(chon)
		{
			case 0:
				InputCodeToUpper(MAMH,10,col,hang + 3);
				break;
			case 1:
				InputStringIsSchoolYear(NIENKHOA,9,col,hang + 6);
				break;
			case 2:
				InputNumberIsInteger(HOCKY,1,col,hang + 9);
				break;
			case 3:
				InputNumberIsInteger(NHOM,1,col + 60,hang); 
				break;
			case 4:
				InputNumberIsInteger(MAXSV,3,col + 60,hang + 3); 
				break;
			case 5:
				InputNumberIsInteger(MINSV,3,col + 60,hang + 6);
				break;
			default:
				continue;
				
		}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key)
		{	
			case UP:
				if(chon > 0){chon--;}
				else{chon = 5;}
				break;
				
			case DOWN:
				if(chon < 5){chon++;}
				else{chon = 0;}
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
			    else if(strlen(NIENKHOA) == 0)
				{
					gotoxy(70,40) ;cout<<"Nien khoa khong duoc de trong";
					chon = 1;
				}
				else if(strlen(HOCKY) == 0)
				{
					gotoxy(70,40) ;cout<<"Hoc ky khong duoc de trong";
					chon = 2;
				}
				else if(strlen(NHOM) == 0)
				{
					gotoxy(70,40) ;cout<<"Nhom khong duoc de trong";
					chon = 3;
				}
				else if(strlen(MAXSV) == 0)
				{
					gotoxy(70,40) ;cout<<"MaxSV khong duoc de trong";
					chon = 4;
				}
				else if(strlen(MINSV) == 0)
				{
					gotoxy(70,40) ;cout<<"MinSV khong duoc de trong";
					chon = 5;
				}
				else if(KT_MaMH(dsmh,MAMH) == -1)
				{
					gotoxy(70,40) ;cout<<"Ma mon hoc khong ton tai";
					chon = 0;
				}
				else if(atoi(MAXSV) < atoi(MINSV))
				{
					gotoxy(70,40) ;cout<<"MaxSV phai lon hon MinSV";
					chon = 4;
				}
				else if(KT_4_Field(t,MAMH,NIENKHOA,atoi(HOCKY),atoi(NHOM)) == 1)
				{
					gotoxy(70,40) ;cout<<"Ma mon hoc, nien khoa, hoc ky, nhom khong duoc trung";
					chon = 0;
				}
				else
				{
					if(c==0)
					{
					    strcpy(ltc.MAMH,MAMH);
						strcpy(ltc.NIENKHOA,NIENKHOA);
						ltc.HOCKY = atoi(HOCKY);
						ltc.NHOM = atoi(NHOM);
						ltc.MAXSV = atoi(MAXSV);
						ltc.MINSV = atoi(MINSV);
						ltc.pHead = NULL;
						if(ThongBao("Ban chac chan muon luu?Y/N") == 'N')
						{
							NhapThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}
						ThemLopTinChi(t,ltc);
						GhiFileLopTinChi(t);
						ShowDanhSachLopTinChi(t);
						gotoxy(70,38) ;cout<<"Them thanh cong";
						if(ThongBao("Ban muon tiep tuc them lop tin chi?Y/N") == 'Y')
						{
							NhapThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							clearScreen(40,1,125,40);
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}
					else
					{
						NhapThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
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

// sua lop
void SuaLTC(TREE t,LOPTC ltc)
{
	if(t != NULL)
	{
		if(t->LopTC.MALOPTC == ltc.MALOPTC)
		{
			t->LopTC = ltc;
		}
		else if(t->LopTC.MALOPTC > ltc.MALOPTC)
		{
			SuaLTC(t->pLeft,ltc);
		}
		else if(t->LopTC.MALOPTC < ltc.MALOPTC)
		{
			SuaLTC(t->pRight,ltc);
		}
	}
}


void SuaLopTinChi(TREE t, DSMH dsmh,LOPTC &ltc, int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	bool flag = false;
	int key, chon = 0;
	int col = 61 ,hang = 26;
	KhungEdit(slItem,Text);
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	
	char MAMH[11]="";
	char NIENKHOA[12] = "";
	char HOCKY[2] = "";
	char NHOM[2] ="";
	char MAXSV[4] = "";
	char MINSV[4] = "";
	
	strcpy(MAMH,ltc.MAMH);
	strcpy(NIENKHOA,ltc.NIENKHOA);
	
	stringstream ssHOCKY;
	ssHOCKY<<ltc.HOCKY;
	string HOCKYtemp = ssHOCKY.str();
	strcpy(HOCKY,HOCKYtemp.c_str());
	

	stringstream ssNHOM;
	ssNHOM<<ltc.NHOM;
	string NHOMtemp = ssNHOM.str();
	strcpy(NHOM,NHOMtemp.c_str());
	
	stringstream ssMAXSV;
	ssMAXSV<<ltc.MAXSV;
	string MAXSVtemp = ssMAXSV.str();
	strcpy(MAXSV,MAXSVtemp.c_str());
	
	stringstream ssMINSV;
	ssMINSV<<ltc.MINSV;
	string MINSVtemp = ssMINSV.str();
	strcpy(MINSV,MINSVtemp.c_str());
	
	
	do
	{
		switch(chon)
		{
			case 0:
				InputNumberIsInteger(MAXSV,3,col + 60,hang + 3);
				break;
			case 1:
				InputNumberIsInteger(MINSV,3,col + 60,hang + 6);
				break;
				
		}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key)
		{
			case UP:
				if(chon > 0){chon--;}
				else{chon = 1;}
				break;
				
			case DOWN:
				if(chon < 1){chon++;}
				else{chon = 0;}
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
				if(strlen(MAXSV) == 0)
				{
					gotoxy(70,40) ;cout<<"MaxSV khong duoc de trong";
					chon = 0;
				}
				else if(strlen(MINSV) == 0)
				{
					gotoxy(70,40) ;cout<<"MinSV khong duoc de trong";
					chon = 1;
				}
				else if(atoi(MAXSV) < atoi(MINSV))
				{
					gotoxy(70,40) ;cout<<"MaxSV phai lon hon MinSV";
					chon = 0;
				}
				else
				{
					if(c==0){
						ltc.MAXSV = atoi(MAXSV);
						ltc.MINSV = atoi(MINSV);
						Normal();
						if(ThongBao("Ban chac chan muon luu?Y/N") == 'N')
						{
							SuaThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}
						SuaLTC(t,ltc);
						GhiFileLopTinChi(t);
						gotoxy(70,38) ;cout<<"Sua thanh cong";
						ShowDanhSachLopTinChi(t);
						if(ThongBao("Ban muon tiep tuc sua mon hoc?Y/N") == 'Y')
						{
							SuaThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}else{
						clearScreen(40,1,125,40);
						SuaThongTinLopTinChi(t,dsmh,chooseFromMenu1,chooseFromMenu2,slItem,Text);
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


void SuaThongTinLopTinChi(TREE &t, DSMH dsmh,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	clearScreen(40,1,125,40);
	bool flag = false;
	int key,chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,Text);
	
	ShowDanhSachLopTinChi(t);
	
	int dem = 0,dong = 0;
	int slltc = TongSoLopTinhChi(t);
	LOPTC ltc[slltc];
	MangTamLopTinChi(t,ltc,dem);
	hang = 5;
	HighLight();
	for(int i = 41; i < 164;i++)
	{
		gotoxy(i,hang);cout<<" ";
	}
	gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
	gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
	gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
	gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
	gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
	gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
	gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
	Normal();
	
	int coll = 61,hangg = 26;
	gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
	gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
	gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
	gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
	gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
	gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
	gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
	do
	{
		key = getch();
		switch(key)
		{
			case DOWN:
				if(dong +1 < dem)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					hang++;
					dong++;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					
					Normal();
					
					gotoxy(coll,hangg);cout<<"                                   ";
					gotoxy(coll,hangg + 3);cout<<"                                   ";
					gotoxy(coll,hangg + 6);cout<<"                                   ";
					gotoxy(coll,hangg + 9);cout<<"                                   ";
					gotoxy(coll + 60,hangg);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 3);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 6);cout<<"                                   ";
					
					gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
					gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
					gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
					gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
					gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
					gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
					gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
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
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					hang--;
					dong--;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					
					Normal();
					
					gotoxy(coll,hangg);cout<<"                                   ";
					gotoxy(coll,hangg + 3);cout<<"                                   ";
					gotoxy(coll,hangg + 6);cout<<"                                   ";
					gotoxy(coll,hangg + 9);cout<<"                                   ";
					gotoxy(coll + 60,hangg);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 3);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 6);cout<<"                                   ";
					
					gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
					gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
					gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
					gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
					gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
					gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
					gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
				}
				break;
			case ENTER:
				SuaLopTinChi(t,dsmh,ltc[dong],chooseFromMenu1,chooseFromMenu2,slItem,Text);
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


// kiem tra sinh vien co ton tai trong lop de xoa
int DemSinhVienDangKyCua_1_LTC(TREE t, int MaLopTC)
{
	int dem = 0;
	if(t == NULL)
	{
		return 0;
	}
	else {
		if(t->LopTC.MALOPTC > MaLopTC)
		{
			return DemSinhVienDangKyCua_1_LTC(t->pLeft, MaLopTC);
		}
		else if(t->LopTC.MALOPTC < MaLopTC)
		{
			return DemSinhVienDangKyCua_1_LTC(t->pRight, MaLopTC);
		}
		else{

			NODEDK p = t->LopTC.pHead;
			if(p == NULL)
			{
				return 0;
			}
			else
			{
				for (p = t->LopTC.pHead; p != NULL; p = p->pNext) {
					dem++;
				}
			}
		}
	}
	return dem;
}

//tim node trai nhat de xoa sau khi xoa ben nhanh phai
void SwapLopTinChiSauKhiXoa(TREE &a, TREE &b)
{
	if(b->pLeft != NULL)
	{
		SwapLopTinChiSauKhiXoa(a,b->pLeft);//tim node trai nhat
	}
	else
	{
		a->LopTC = b->LopTC; // chep du lieu b sang a
		a = b;		// de lat nua free a
		b = b->pRight;
	}
}


int XoaLopTinChi(TREE &t, int MaLopTC)
{
	if(t==NULL)
	{
		return 0;
	}
	else
	{
		if(t->LopTC.MALOPTC > MaLopTC)
		{
			return XoaLopTinChi(t->pLeft,MaLopTC);
		}
		else if(t->LopTC.MALOPTC < MaLopTC)
		{
			return XoaLopTinChi(t->pRight,MaLopTC);
		}
		else
		{
			TREE node = t;
			if(node->pLeft == NULL)
			{
				t = node->pRight;
			}
			else if(node->pRight == NULL)
			{
				t = node->pLeft;
			}
			else
			{
				SwapLopTinChiSauKhiXoa(node, t->pRight);
			}
			delete node;
			node = NULL;
			return 1;
		}
	}
}
void XoaThongTinLopTinChi(TREE &t,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	Normal();
	clearScreen(40,1,125,40);
	bool flag = false;
	int key,chon = 0,col = 40,hang = 5;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,Text);
	
	ShowDanhSachLopTinChi(t);
	
	int dem = 0,dong = 0;
	int slltc = TongSoLopTinhChi(t);
	if(slltc == 0)
	{
		gotoxy(70,40);cout<<"Lop tin chi rong";
		return;
	}
	LOPTC ltc[slltc];
	MangTamLopTinChi(t,ltc,dem);
	hang = 5;
	HighLight();
	for(int i = 41; i < 164;i++)
	{
		gotoxy(i,hang);cout<<" ";
	}
	gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
	gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
	gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
	gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
	gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
	gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
	gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
	Normal();
	
	int coll = 61,hangg = 26;
	gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
	gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
	gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
	gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
	gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
	gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
	gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
	do
	{
		key = getch();
		switch(key)
		{
			case DOWN:
				if(dong +1 < dem)
				{
					Normal();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					hang++;
					dong++;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					
					Normal();
					
					gotoxy(coll,hangg);cout<<"                                   ";
					gotoxy(coll,hangg + 3);cout<<"                                   ";
					gotoxy(coll,hangg + 6);cout<<"                                   ";
					gotoxy(coll,hangg + 9);cout<<"                                   ";
					gotoxy(coll + 60,hangg);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 3);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 6);cout<<"                                   ";
					
					gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
					gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
					gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
					gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
					gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
					gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
					gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
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
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					hang--;
					dong--;
					HighLight();
					for(int i = 41; i < 164;i++)
					{
						gotoxy(i,hang);cout<<" ";
					}
					gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
					gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
					gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
					gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
					gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
					gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
					gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
					
					Normal();
					
					gotoxy(coll,hangg);cout<<"                                   ";
					gotoxy(coll,hangg + 3);cout<<"                                   ";
					gotoxy(coll,hangg + 6);cout<<"                                   ";
					gotoxy(coll,hangg + 9);cout<<"                                   ";
					gotoxy(coll + 60,hangg);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 3);cout<<"                                   ";
					gotoxy(coll + 60,hangg + 6);cout<<"                                   ";
					
					gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
					gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
					gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
					gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
					gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
					gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
					gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
				}
				break;
			case ENTER:
				flag = true;
				c = XacNhanEdit(TEXT_XACNHAN,flag);
				Normal();
				if(c == 0)
				{
					int kt = DemSinhVienDangKyCua_1_LTC(t,ltc[dong].MALOPTC);
					if(kt > 0)
					{
						gotoxy(70,38) ;
						cout<<"Co sinh vien ton tai trong lop tin chi";
						continue;
					}
					if(ThongBao("Ban chac chan muon xoa?Y/N") == 'N')
					{
						XoaThongTinLopTinChi(t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
					}
					int kq = XoaLopTinChi(t,ltc[dong].MALOPTC);
					if(kq == 0)
					{
						gotoxy(70,38) ;
						cout<<"Lop tin chi khong ton tai";
						continue;
					}
					else
					{
						clearScreen(40,1,125,40);
						gotoxy(70,38) ;
						cout<<"Xoa thanh cong";
						GhiFileLopTinChi(t);
						col = 40;
						hang = 5;
						TaoKhungDanhSachLopTinChi(40, 1, 124, 20);
						KhungEdit(slItem,Text);
						slltc = TongSoLopTinhChi(t);
						if(slltc > 0)
						{
							ShowDanhSachLopTinChi(t);
							hang = 5;
							HighLight();
							for(int i = 41; i < 164;i++)
							{
								gotoxy(i,hang);cout<<" ";
							}
							gotoxy(col+7,hang);cout<<ltc[dong].MALOPTC;
							gotoxy(col+27,hang);cout<<ltc[dong].MAMH;
							gotoxy(col+52,hang);cout<<ltc[dong].NIENKHOA;
							gotoxy(col+77,hang);cout<<ltc[dong].HOCKY;
							gotoxy(col+90,hang);cout<<ltc[dong].NHOM;
							gotoxy(col+100,hang);cout<<ltc[dong].MAXSV;
							gotoxy(col+115,hang);cout<<ltc[dong].MINSV;
							Normal();
							
							int coll = 61,hangg = 26;
							gotoxy(coll,hangg);cout<<ltc[dong].MALOPTC;
							gotoxy(coll,hangg + 3);cout<<ltc[dong].MAMH;
							gotoxy(coll,hangg + 6);cout<<ltc[dong].NIENKHOA;
							gotoxy(coll,hangg + 9);cout<<ltc[dong].HOCKY;
							gotoxy(coll + 60,hangg);cout<<ltc[dong].NHOM;
							gotoxy(coll + 60,hangg + 3);cout<<ltc[dong].MAXSV;
							gotoxy(coll + 60,hangg + 6);cout<<ltc[dong].MINSV;
						}
						Normal();
						if(ThongBao("Ban muon tiep tuc xoa lop tin chi?Y/N") == 'Y')
						{
							XoaThongTinLopTinChi(t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
						}else{
							clearScreen(40,1,125,40);
							backMenu2(chooseFromMenu1,chooseFromMenu2);
						}
					}
				}
				else{
						XoaThongTinLopTinChi(t,chooseFromMenu1,chooseFromMenu2,slItem,Text);
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

// in danh sach sinh vien dang ky theo nhien khoa, hoc ky, nhom, ma mon hoc

int TimKiemMaLopTC(LOPTC ltc[], int n,  char NienKhoa[], int HocKy, int Nhom, char MaMH[])
{
	for(int i = 0; i < n; i++)
	{
		LOPTC l = ltc[i];
		if(strcmp(l.NIENKHOA,NienKhoa) == 0 && l.HOCKY == HocKy && l.NHOM == Nhom && strcmp(l.MAMH,MaMH) == 0)
		{
			return l.MALOPTC;
		}
	}
	return 0;
}

TREE TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(TREE t, int MaLTC)
{
	if(t==NULL)
	{
		return NULL;
	}
	else
	{
		if(t->LopTC.MALOPTC > MaLTC)
		{
			return TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(t->pLeft,MaLTC);
		}
		else if(t->LopTC.MALOPTC < MaLTC)
		{
			return TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(t->pRight,MaLTC);
		}
		else
		{
			return t;
		}
	}
}

void TaoKhungDanhSachSinhVienDangKy(int x, int y, int width, int height)
{
	TaoKhungDon(x, y, width, height);
	SetColor(10);
	gotoxy(x+5, y+2); cout << "STT";
	gotoxy(x+15, y+2); cout << "MALOP";
	gotoxy(x+30, y+2); cout << "MASV";
	gotoxy(x+50, y+2); cout << "HO";
	gotoxy(x+70, y+2); cout << "TEN";
	gotoxy(x+90, y+2); cout << "PHAI";
	gotoxy(x+110, y+2); cout << "SDT";
	Normal();
	//======== Chot ================
	gotoxy(x+10, y); cout << char(194);
	gotoxy(x+25, y); cout << char(194);
	gotoxy(x+40, y); cout << char(194);
	gotoxy(x+60, y); cout << char(194);
	gotoxy(x+80, y); cout << char(194);
	gotoxy(x+100, y); cout << char(194);
//	//==============================
	gotoxy(x+10, y +3); cout << char(193);
	gotoxy(x+25, y+3); cout << char(193);
	gotoxy(x+40, y+3); cout << char(193);
	gotoxy(x+60, y+3); cout << char(193);
	gotoxy(x+80, y+3); cout << char(193);
	gotoxy(x+100, y+3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
	//==============================
	for (int i = y+1; i < y+3; i++)
	{
		if (i !=  5)
		{
			gotoxy(x+10, i); cout << char(179);
			gotoxy(x+25, i); cout << char(179);
			gotoxy(x+40, i); cout << char(179);
			gotoxy(x+60, i); cout << char(179);
			gotoxy(x+80, i); cout << char(179);
			gotoxy(x+100, i); cout << char(179);
		}
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+10 && i != x+25 && i != x+40 && i != x+60 && i != x+80 && i != x+100)
		{
			gotoxy(i, 4); cout << char(196);
		}
	}
}

void ShowDSSV_LTC_NienKhoa_HocKy_Nhom_MaMH(TREE t,NODESV node,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
MENU:	Normal();
	clearScreen(40,1,125,40);
	ShowDanhSachLopTinChi(t);
	int key, chon = 0,col = 61,hang = 26;
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	char MAMH[11]="";
	char NIENKHOA[12] = "";
	char HOCKY[2] = "";
	char NHOM[2] ="";
	KhungEdit(slItem,Text);
	
	do
	{
		switch(chon)
		{
			case 0:
				InputCodeToUpper(MAMH,10,col,hang);
				break;
			case 1:
				InputStringIsSchoolYear(NIENKHOA,11,col,hang + 3);
				break;
			case 2:
				InputNumberIsInteger(HOCKY,1,col,hang + 6);
				break;
			case 3:
				InputNumberIsInteger(NHOM,1,col,hang +9); 
				break;
			default:
				continue;
				
		}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key)
		{	
			case UP:
				if(chon > 0){chon--;}
				else{chon = 3;}
				break;
				
			case DOWN:
				if(chon < 3){chon++;}
				else{chon = 0;}
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
			    else if(strlen(NIENKHOA) == 0)
				{
					gotoxy(70,40) ;cout<<"Nien khoa khong duoc de trong";
					chon = 1;
				}
				else if(strlen(HOCKY) == 0)
				{
					gotoxy(70,40) ;cout<<"Hoc ky khong duoc de trong";
					chon = 2;
				}
				else if(strlen(NHOM) == 0)
				{
					gotoxy(70,40) ;cout<<"Nhom khong duoc de trong";
					chon = 3;
				}
				else
				{
					if(c==0)
					{
						int dem = 0;
						int slltc = TongSoLopTinhChi(t);
						if(slltc == 0)
						{
							gotoxy(70,40);cout<<"Lop tin chi rong";
							getch();
							goto MENU;
						}
						LOPTC ltc[slltc];
						MangTamLopTinChi(t,ltc,dem);
						int HocKy = atoi(HOCKY);
						int Nhom = atoi(NHOM);
						int MaLTC = TimKiemMaLopTC(ltc,slltc,NIENKHOA,HocKy,Nhom,MAMH);
						
						TREE tree = TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(t,MaLTC);
						if(tree != NULL)
						{
							NODEDK dk = tree->LopTC.pHead;
							
							if(dk != NULL)
							{
								clearScreen(40,1,125,40);
								TaoKhungDanhSachSinhVienDangKy(40, 1, 124, 40);
								int stt = 1, col = 40, hang = 5;
								for(NODEDK p= dk;p!=NULL;p=p->pNext)
								{
									for(NODESV q = node; q!=NULL;q=q->pNext)
									{
										if(strcmp(p->dk.MASV,q->sv.MASV) == 0)
										{
											gotoxy(col + 2,hang);cout<<stt;
											gotoxy(col + 12,hang);cout<<q->sv.MALOP;
											gotoxy(col + 26,hang);cout<<q->sv.MASV;
											gotoxy(col + 42,hang);cout<<q->sv.HO;
											gotoxy(col + 62,hang);cout<<q->sv.TEN;
											gotoxy(col + 82,hang);cout<<q->sv.PHAI;
											gotoxy(col + 102,hang);cout<<q->sv.SODT;
											hang++;
											stt++;
										}
									}
								}
							}
							else
							{
								gotoxy(70,40);cout<<"Lop chua co sinh vien dang ky";
								getch();
								goto MENU;
							}
						}
						else
						{
							gotoxy(70,40);cout<<"Lop tin chi khong ton tai";
							getch();
							goto MENU;
						}
					}
					else
					{
						flag = false;
					}
				}
				break;
			default:
				continue;
		}
	}while(1);
}

// nhap diem
void TaoKhungDanhSachSinhVienDangKy_NhapDiem(int x, int y, int width, int height)
{
	TaoKhungDon(x, y, width, height);
	SetColor(10);
	gotoxy(x+5, y+2); cout << "STT";
	gotoxy(x+25, y+2); cout << "MASV";
	gotoxy(x+45, y+2); cout << "HO";
	gotoxy(x+80, y+2); cout << "TEN";
	gotoxy(x+110, y+2); cout << "DIEM";
	Normal();
	//======== Chot ================
	gotoxy(x+15, y); cout << char(194);
	gotoxy(x+35, y); cout << char(194);
	gotoxy(x+70, y); cout << char(194);
	gotoxy(x+100, y); cout << char(194);
//	//==============================
	gotoxy(x+15, y +3); cout << char(193);
	gotoxy(x+35, y+3); cout << char(193);
	gotoxy(x+70, y+3); cout << char(193);
	gotoxy(x+100, y+3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
	//==============================
	for (int i = y+1; i < y+3; i++)
	{
		if (i !=  5)
		{
			gotoxy(x+15, i); cout << char(179);
			gotoxy(x+35, i); cout << char(179);
			gotoxy(x+70, i); cout << char(179);
			gotoxy(x+100, i); cout << char(179);
		}
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+15 && i != x+35 && i != x+70 && i != x+100)
		{
			gotoxy(i, 4); cout << char(196);
		}
	}
}
void ShowDanhSachSinhVien_DangKy_NhapDiem(NODEDK dk, NODESV node)
{
	clearScreen(40,1,125,40);
	Normal();
	TaoKhungDanhSachSinhVienDangKy_NhapDiem(40,1,124,40);
	int stt = 1, col = 40, hang = 5;
	for(NODEDK p= dk;p!=NULL;p=p->pNext)
	{
		for(NODESV q = node; q!=NULL;q=q->pNext)
		{
			if(strcmp(p->dk.MASV,q->sv.MASV) == 0)
			{
				gotoxy(col + 5,hang);cout<<stt;
				gotoxy(col + 20,hang);cout<<q->sv.MASV;
				gotoxy(col + 40,hang);cout<<q->sv.HO;
				gotoxy(col + 80,hang);cout<<q->sv.TEN;
				gotoxy(col + 105,hang);cout<<p->dk.DIEM;
				hang++;
				stt++;
			}
		}
	}
	Normal();
	ShowCur(false);
}


void ThemDiemVaoDanhSachDangKy(TREE &t, int MaLTC, char diem[][5], int slsv)
{
	if(t!= NULL)
	{
		if(t->LopTC.MALOPTC < MaLTC)
		{
			ThemDiemVaoDanhSachDangKy(t->pRight,MaLTC,diem,slsv);
		}
		else if(t->LopTC.MALOPTC > MaLTC)
		{
			ThemDiemVaoDanhSachDangKy(t->pLeft,MaLTC, diem,slsv);
		}
		else
		{
			int dem = 0;
			for(NODEDK p = t->LopTC.pHead; p!=NULL;p=p->pNext)
			{
				if(strcmp(diem[dem],"") == 0)
				{
					//diem ko thay doi
				}
				else
				{
					p->dk.DIEM = atof(diem[dem]);
					dem++;	
				}
			}
		}
	}
}
void ChinhSuaDiem(TREE &t,int MaLTC,int chooseFromMenu1,int chooseFromMenu2)
{
	
	int slsv = DemSinhVienDangKyCua_1_LTC(t,MaLTC);
	char diem[slsv][5];
	for(int i =0; i < slsv;i++)
	{
		strcpy(diem[i],"");
	}
	int dem = 0;
	TREE tree = TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(t,MaLTC);
	for(NODEDK p = tree->LopTC.pHead; p!=NULL;p=p->pNext)
	{
		stringstream ss;
		ss<<p->dk.DIEM;
		string temp = ss.str();
		strcpy(diem[dem],temp.c_str());
		dem++;
	}
	ShowCur(true);
	int chon = 0, key, col = 40,hang = 5;
	do
	{
		switch(0)
		{
			case 0:
				InputNumberIsFloat(diem[chon],4,col+105,hang+chon);
		}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key)
		{
			case UP:
				if(chon > 0){chon--;}
				else{chon = slsv - 1;}
				break;
				
			case DOWN:
				if(chon < slsv - 1){chon++;}
				else{chon = 0;}
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
				bool loiNhap = false;
				for(int i = 0 ; i < slsv; i++)
				{
					float point;
					if(diem[i][0] == '.' || (diem[i][strlen(diem[i])-1] == '.'))
					{
						loiNhap = true;
						break;
					}
					if(diem[i] == "")
					{
						point = 0;
					}
					else
					{
						point = atof(diem[i]);
					}
					if(point < 0 || point > 10)
					{
						loiNhap = true;
						break;
					}					
				}
				if(loiNhap == true)
				{
					gotoxy(70,40);cout<<"Vui long nhap diem tu 0 -> 10";
					continue;
				}
				else
				{
					ThemDiemVaoDanhSachDangKy(t,MaLTC,diem,slsv);
					GhiFileLopTinChi(t);
					gotoxy(70,40);cout<<"Nhap diem thanh cong";
					continue;
				}
				break;
		}
	}
	while(1);
}
void NhapDiem(TREE &t,NODESV node,int chooseFromMenu1,int chooseFromMenu2,int slItem,string Text[])
{
	
MENU:	Normal();
	clearScreen(40,1,125,40);
	ShowDanhSachLopTinChi(t);
	int key, chon = 0,col = 61,hang = 26;
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	char MAMH[11]="";
	char NIENKHOA[12] = "";
	char HOCKY[2] = "";
	char NHOM[2] ="";
	KhungEdit(slItem,Text);
	
	do
	{
		switch(chon)
		{
			case 0:
				InputCodeToUpper(MAMH,10,col,hang);
				break;
			case 1:
				InputStringIsSchoolYear(NIENKHOA,11,col,hang + 3);
				break;
			case 2:
				InputNumberIsInteger(HOCKY,1,col,hang + 6);
				break;
			case 3:
				InputNumberIsInteger(NHOM,1,col,hang +9); 
				break;
			default:
				continue;
				
		}
		key = getch();
		Normal();
		clearScreen(70,39,60,2);
		switch(key)
		{	
			case UP:
				if(chon > 0){chon--;}
				else{chon = 3;}
				break;
				
			case DOWN:
				if(chon < 3){chon++;}
				else{chon = 0;}
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
			    else if(strlen(NIENKHOA) == 0)
				{
					gotoxy(70,40) ;cout<<"Nien khoa khong duoc de trong";
					chon = 1;
				}
				else if(strlen(HOCKY) == 0)
				{
					gotoxy(70,40) ;cout<<"Hoc ky khong duoc de trong";
					chon = 2;
				}
				else if(strlen(NHOM) == 0)
				{
					gotoxy(70,40) ;cout<<"Nhom khong duoc de trong";
					chon = 3;
				}
				else
				{
					if(c==0)
					{
						int dem = 0;
						int slltc = TongSoLopTinhChi(t);
						if(slltc == 0)
						{
							gotoxy(70,40);cout<<"Lop tin chi rong";
							getch();
							goto MENU;
						}
						LOPTC ltc[slltc];
						MangTamLopTinChi(t,ltc,dem);
						int HocKy = atoi(HOCKY);
						int Nhom = atoi(NHOM);
						int MaLTC = TimKiemMaLopTC(ltc,slltc,NIENKHOA,HocKy,Nhom,MAMH);
						
						TREE tree = TimKiemLTC_NienKhoa_HocKy_Nhom_MaMH(t,MaLTC);
						if(tree != NULL)
						{
							NODEDK dk = tree->LopTC.pHead;
							
							if(dk != NULL)
							{
								ShowDanhSachSinhVien_DangKy_NhapDiem(dk,node);
								ChinhSuaDiem(t,MaLTC,chooseFromMenu1,chooseFromMenu2);
							}
							else
							{
								gotoxy(70,40);cout<<"Lop chua co sinh vien dang ky";
								getch();
								goto MENU;
							}
						}
						else
						{
							gotoxy(70,40);cout<<"Lop tin chi khong ton tai";
							getch();
							goto MENU;
						}
					}
					else
					{
						flag = false;
					}
				}
				break;
			default:
				continue;
		}
	}while(1);
}



//================================================================================================================
void DsLtcNKHK(TREE t, LOPTC ltc[],int &sl,char NienKhoa[], int HocKy)
{
	if(t!=NULL)
	{
		DsLtcNKHK(t->pLeft, ltc,sl, NienKhoa,HocKy);
		DsLtcNKHK(t->pRight, ltc,sl, NienKhoa,HocKy);
		if(strcmp(t->LopTC.NIENKHOA,NienKhoa) == 0 && t->LopTC.HOCKY == HocKy)
		{
			ltc[sl++] = t->LopTC;
		}
	}
}
char* TenMonHoc(DSMH ds, char MaMH[])
{
	for(int i = 0; i < ds.n; i++)
	{
		if(strcmp(ds.ds[i]->MAMH, MaMH) == 0)
		{
			return ds.ds[i]->TENMH;
		}
	}
}
int DanhSachLTC_DaDangKy_ChuaDangKy(LOPTC ltc[],LOPTC ltcddk[], LOPTC ltccdk[], int m, int &n, int &k, char MaSV[]){
	if(m > 0)
	{
		for(int i =0; i < m; i++)
		{
			LOPTC x = ltc[i];
			if(x.pHead != NULL)
			{
				bool flag = false;
				for(NODEDK p = x.pHead; p!=NULL;p=p->pNext)
				{
					if(strcmp(p->dk.MASV,MaSV) == 0)
					{
						flag = true;
					}
				}
				if(flag == true)
				{
					ltcddk[n++] = ltc[i];
				}
				else
				{
					ltccdk[k++] = ltc[i];
				}
			}
			else
			{
				ltccdk[k++] = ltc[i];
			}
		}
		
		return 1;
	}
	else
	{
		return 0;
	}
}
void Dangkylop(TREE &t, int maltc, DANGKY dky){
	if(t!=NULL)
	{
		if(t->LopTC.MALOPTC>maltc){
			Dangkylop(t->pLeft, maltc,dky);
		}
		else if(t->LopTC.MALOPTC<maltc){
			Dangkylop(t->pRight, maltc,dky);
		}else{
			Them_CoTTDK(t->LopTC.pHead,dky);
		}
	}
}
void KhungLopDK(){
	int x =40,y=4,width=62,height=18;
	TaoKhungDon(x, y, width, height);
	gotoxy(x+22,y-1);cout << "LOP TIN CHI DA DANG KY";
	SetColor(10);
	gotoxy(x+3, y+2); cout << "MA LOPTC";
	gotoxy(x+15, y+2); cout << "MA MON HOC";
	gotoxy(x+36, y+2); cout << "TEN MH";
	gotoxy(x+56, y+2); cout << "NHOM";
	Normal();
	//======== Chot ================
	gotoxy(x+12, y); cout << char(194);
	gotoxy(x+26, y); cout << char(194);
	gotoxy(x+52, y); cout << char(194);
	gotoxy(x+62, y); cout << char(194);
//	//==============================
	gotoxy(x+12, y + 3); cout << char(193);
	gotoxy(x+26, y + 3); cout << char(193);
	gotoxy(x+52, y + 3); cout << char(193);
	gotoxy(x+62, y + 3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
//	//==============================
	for (int i = y+1; i < y+3; i++)
	{   
		gotoxy(x+12, i); cout << char(179);
		gotoxy(x+26, i); cout << char(179);
		gotoxy(x+52, i); cout << char(179);
		gotoxy(x+62, i); cout << char(179);
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+12 && i != x+26 && i != x+52)
		{
			gotoxy(i,y + 3); cout << char(196);
		}
	}
}
void KhungLopChua_DK(){
	int x =102,y=4,width=62,height=18;
	TaoKhungDon(x, y, width, height);
	gotoxy(x+20,y-1);cout << "LOP TIN CHI CHUA DANG KY";
	SetColor(10);
	gotoxy(x+3, y+2); cout << "MA LOPTC";
	gotoxy(x+15, y+2); cout << "MA MON HOC";
	gotoxy(x+36, y+2); cout << "TEN MH";
	gotoxy(x+56, y+2); cout << "NHOM";
	Normal();
	//======== Chot ================
	gotoxy(x+12, y); cout << char(194);
	gotoxy(x+26, y); cout << char(194);
	gotoxy(x+52, y); cout << char(194);
	gotoxy(x+62, y); cout << char(194);
//	//==============================
	gotoxy(x+12, y + 3); cout << char(193);
	gotoxy(x+26, y + 3); cout << char(193);
	gotoxy(x+52, y + 3); cout << char(193);
	gotoxy(x+62, y + 3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
//	//==============================
	for (int i = y+1; i < y+3; i++)
	{   
		gotoxy(x+12, i); cout << char(179);
		gotoxy(x+26, i); cout << char(179);
		gotoxy(x+52, i); cout << char(179);
		gotoxy(x+62, i); cout << char(179);
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+12 && i != x+26 && i != x+52)
		{
			gotoxy(i,y + 3); cout << char(196);
		}
	}
}
void HienThiLopTC_DK(LOPTC ltc[],int m,char masv[]){
	int n=0,k=0;
	LOPTC cdk[m];
	LOPTC ddk[m];
	KhungLopDK();
	KhungLopChua_DK();
	DanhSachLTC_DaDangKy_ChuaDangKy(ltc,ddk,cdk,m,n,k,masv);
	int col = 40,hang = 8;
	int x = 102, y = 8;
	if(n>0){
		for(int i=0;i<n;i++){
			char* tenMh = TenMonHoc(dsmh,ddk[i].MAMH);
			gotoxy(col+5,hang);cout<<ddk[i].MALOPTC;
			gotoxy(col+17,hang);cout<<ddk[i].MAMH;
			gotoxy(col+30,hang);cout<<tenMh;
			gotoxy(col+58,hang);cout<<ddk[i].NHOM;
			hang++;
		}
	}
	if(k>0){
		for(int i=0;i<k;i++){
			char* tenMHDK = TenMonHoc(dsmh,cdk[i].MAMH);
			gotoxy(x+5,y);cout<<cdk[i].MALOPTC;
			gotoxy(x+17,y);cout<<cdk[i].MAMH;
			gotoxy(x+30,y);cout<<tenMHDK;
			gotoxy(x+58,y);cout<<cdk[i].NHOM;
			y++;
		}
	}
}
void MangTamLopTinChi_Da_DK(TREE t, LOPTC ltc[], int &dem,char masv[]){
	if(t!=NULL)
	{
		MangTamLopTinChi_Da_DK(t->pLeft,ltc,dem,masv);
		MangTamLopTinChi_Da_DK(t->pRight,ltc,dem,masv);
		NODEDK ndk = t->LopTC.pHead;
		if(ndk != NULL){
			if(strcmp(ndk->dk.MASV,masv)==0){
				ltc[dem++] = t->LopTC;
			}
		}
	}
}
void HienThiLoptcDaDK(TREE,char masv[]){
	Normal();
	TaoKhungDanhSachLopTinChi(40, 1, 124, 20);
	int col = 40,hang = 5;
	int dem = 0;
	int slltc = TongSoLopTinhChi(t);
	LOPTC ltc[slltc];
	MangTamLopTinChi_Da_DK(t,ltc,dem,masv);
	if(dem  > 0)
	{
		for(int i = 0; i < dem; i++)
		{
			gotoxy(col+7,hang);cout<<ltc[i].MALOPTC;
			gotoxy(col+27,hang);cout<<ltc[i].MAMH;
			gotoxy(col+52,hang);cout<<ltc[i].NIENKHOA;
			gotoxy(col+77,hang);cout<<ltc[i].HOCKY;
			gotoxy(col+90,hang);cout<<ltc[i].NHOM;
			gotoxy(col+100,hang);cout<<ltc[i].MAXSV;
			gotoxy(col+115,hang);cout<<ltc[i].MINSV;
			hang++;
		}
	}
	
}
//===========================================================================================
//===========================================DANG KY=========================================
//===========================================================================================


NODEDK TaoNodeDK(DANGKY dk){
	NODEDK p = new NodeDangKy;
	if(p == NULL){
		cout<<"Khong du bo nho de cap phat";
		return NULL;
	}
	p->dk = dk;
	p->pNext = NULL;
	return p;
}
int ThemNodeDK(NODEDK &ndk, DANGKY dk) {
	NODEDK nodedk = TaoNodeDK(dk);
	if (nodedk == NULL) {
		return 0;
	}
	if (ndk == NULL) {
		ndk = nodedk;
	}
	else {
		for (NODEDK p = ndk; p != NULL; p = p->pNext) {
			if (p->pNext == NULL) {
				p->pNext = nodedk;
				break;
			}
		}
	}
	return 1;
}
int DemDangKy(NODEDK ndk){
	int dem = 0;
	for (NODEDK p = ndk; p != NULL; p = p->pNext) { dem++;}
	return dem;
}
void Them_DauDK(NODEDK &First,DANGKY dky){
		NODEDK p = new NodeDangKy;
		p->dk = dky;
		p->pNext = First;
		First = p;
}
void Them_SauDK(NODEDK &p,DANGKY dky){
	NODEDK q = new NodeDangKy;
	q->dk = dky;
	q->pNext = p->pNext;
	p->pNext = q;
}
void Them_CoTTDK(NODEDK &First,DANGKY dky){
	NODEDK p,q;
	q=NULL;
	p=NULL;
	for(p = First; p != NULL && strcmp(p->dk.MASV,dky.MASV) < 0; p = p->pNext){
		q=p;
	}
	if(q==NULL){
		if(First == NULL){
			Them_DauDK(First,dky);
		}else{
			Them_SauDK(q,dky);
		}
	}else{
		p=NULL;
		p = q->pNext;
		if(p != NULL){
			Them_DauDK(q->pNext,dky);
		}else{
			Them_SauDK(q,dky);
		}
	}
}
void ThemTTDK(TREE &t,int choose1,int choose2){
	clearEdit();
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	int chon = 0,col = 61,hang = 26,i = 0;
	int slItem = SHOW_ITEM_DANGKY;
	KhungEdit(slItem,SHOW_TEXT_DANGKY);
	ShowDanhSachLopTinChi(t);
	LOPTC ltc[MAX];
	gotoxy(61,26);
	char MASV[slMax]="";
	char NIENKHOA[12]="";
	char HOCKY[2]="";
	int kytu = 0;
	do{
		switch(chon){
			case 0:
				InputCodeToUpper(MASV,10,col,hang);
				break;
			case 1:
				InputStringIsSchoolYear(NIENKHOA,10,col,hang+3);
				break;
			case 2:
				InputNumberIsInteger(HOCKY, 1, col, hang+6);
				break;
			default:
				continue; 
		}
		kytu = getch();
		switch(kytu){
			case UP:{
				if(chon>0){
					chon--;
				}else{
					chon = slItem-1;
				}
				break;
			}
			case DOWN:{
				if(chon<slItem-1){
					chon++;
				}else{
					chon=0;
				}
				break;
			}
			case ESC:{
				onExitEdit(choose1,choose2,"Ban co muon thoat chuc nang nay");
				break;
			}	
			case ENTER:{
				flag = true;
				int c = XacNhanEdit(TEXT_XACNHAN,flag);
				if(c==0){
					int x = checkMasv(head,MASV);
					if(strlen(MASV)==NULL){
						showMessageBox("THONG BAO","Khong duoc de trong ma sinh vien",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(x==2){
						showMessageBox("THONG BAO","Ma sinh vien khong ton tai",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strlen(NIENKHOA)==NULL){
						showMessageBox("THONG BAO","Nien khoa khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strlen(HOCKY)==NULL){
						showMessageBox("THONG BAO","Hoc ky khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strcmp(HOCKY,"1")<0||strcmp(HOCKY,"3")>0){
						showMessageBox("THONG BAO","Hoc ky khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else{
						int hky = atoi(HOCKY);
						int m = 0;
						DsLtcNKHK(t, ltc, m, NIENKHOA, hky);
						ThemLopSVDK(t,ltc, m, MASV, choose1, choose2,hky,NIENKHOA);
					}
				}
			}
				break;
			default: 
				continue;
		}
	}while(1);
}
int LopTinChiDaDK(LOPTC ltc, char MASV[]){
	if(ltc.pHead != NULL)
	{
		NODEDK ndk = ltc.pHead;
		for(NODEDK p = ndk;p!=NULL;p=p->pNext){
			if(strcmp(p->dk.MASV,MASV)==0){
				return 1;
			}
		}
		return 0;
	}else{
		return 0;
	}
}

int KiemTraMonHocSinhVienDK_MonHoc_NienKhoa_HocKy(LOPTC ltc[], int slltc, LOPTC x)
{
	for(int i =0; i < slltc; i++)
	{
		LOPTC l = ltc[i];
		if(strcmp(l.MAMH,x.MAMH) == 0 && strcmp(l.NIENKHOA,x.NIENKHOA) == 0 && l.HOCKY == x.HOCKY)
		{
			return 1;
		}
	}
	return 0;
}
void ThemLopSVDK(TREE &t,LOPTC ltc[],int m,char MASV[],int choose1,int choose2,int hky,char nkhoa[]){
	clearEdit();
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	int chon = 0,col = 90,hang = 25,i;
	int slItem = SHOW_ITEM_DANGKY;
	LOPTC list[m];
	DANGKY dky;
	HienThiLopTC_DK(ltc,m,MASV);
	for(i= 0; i<m;i++){
		list[i] = ltc[i];
		gotoxy(70,50+i);cout<<list[i].MALOPTC;
	}
	gotoxy(80,26);cout<<"Ma lop tc";
	TaoKhungDon(40, 1, 124, 20);
	TaoKhungDon(40, 22, 124, 19);
	TaoKhungDon(col,hang,20,2);
	KhungLopDK();
	char MA[slMax]="";
	int kytu=0;
	do{
		switch(chon){
			case 0:
				InputNumberIsInteger(MA,6,col+1,26);
				break;
			default:
				continue;
		}
		kytu = getch();
		switch(kytu){
			case ENTER:
				c = XacNhanEdit(TEXT_XACNHAN,true);
				if(c==0){
					int mltc= atoi(MA);
					DANGKY dky;
					mltc = atoi(MA);
					strcpy(dky.MASV,MASV);
					dky.DIEM = 0;
					for(i = 0; i < m; i++){
						if(mltc == list[i].MALOPTC){
							int yes = LopTinChiDaDK(list[i],MASV);
							if(yes == 0){
								int slSVDK = 0;
								LOPTC l[m];
								MangTamLopTinChi_Da_DK(t,l,slSVDK,MASV);
								if(KiemTraMonHocSinhVienDK_MonHoc_NienKhoa_HocKy(l,slSVDK,list[i]) == 0)
								{
									Dangkylop(t,mltc,dky);
									GhiFileLopTinChi(t);
									int n = showMessageBox("THONG BAO","Ban da dang ky thang cong!!",MB_OKCANCEL);
									if(n==IDOK){
										m=0;
										DsLtcNKHK(t, ltc, m, nkhoa, hky);
										ThemLopSVDK(t,ltc,m,MASV,choose1,choose2,hky,nkhoa);
									}else{
										backMenu2(choose1,choose2);
									}
								}
								else
								{
									showMessageBox("THONG BAO","Ban da dang ky mon hoc nay!!",MB_OK);
								}
							}else{
								showMessageBox("THONG BAO","Ban da co ten\nlop tc nay truoc do!!",MB_OK);
							}
						}
					}
				}
				break;
			case ESC:
				onExitEdit(choose1,choose2,"Ban muon thoat chuc nang nay?");
				break;
			default:
				continue;
		}
	}while(1);
}
void XoaDauDK(NODEDK &ndk){
	NODEDK p;
	if(ndk == NULL){
		return;
	}else{
		p = ndk;
		ndk = p->pNext;
		delete p;
	}
}
void XoaSauDK(NODEDK &ndk,char Text[]){
	NODEDK p,q;
	if(ndk == NULL || ndk->pNext == NULL){
		return;
	}else{
		for(p = ndk; p -> pNext != NULL && strcmp(p->pNext->dk.MASV,Text)!=0&&p->pNext->dk.DIEM==0; p = p->pNext);
		if(p->pNext != NULL){
			q=p->pNext;
			p->pNext = q->pNext;
			delete q;
		}
	}
}
void XoaCuoiDK(NODEDK &ndk){
	NODEDK p;
	for(p=ndk;p->pNext->pNext!=NULL;p=p->pNext);
	delete(p->pNext);
	p->pNext=NULL;
}
int XoaDK(NODEDK First,char masv[],int choose1, int choose2){
	NODEDK p;
	for(p = First; p != NULL; p = p->pNext){
		if(p->dk.DIEM!=0){
			return -2;
		}
	}
	for(p = First; p != NULL&&p->dk.DIEM==0; p = p->pNext){
		DANGKY dky = p->dk;
		if(strcmp(dky.MASV,masv)==0&&dky.DIEM==0&&p==First){
			return 1;
		}
		if(strcmp(dky.MASV,masv)==0&&dky.DIEM==0&&p->pNext==NULL){
			return -1;
		}
		if(strcmp(dky.MASV,masv)==0&&dky.DIEM==0&&p->pNext!=NULL){
			return 0;
		}	
	}
	return 2;
}
int checkLopTC(TREE t, int maltc){
	if(t==NULL)
	{
		return 0;
	}else{
		if(t->LopTC.MALOPTC>maltc){
			return checkLopTC(t->pLeft, maltc);
		}
		else if(t->LopTC.MALOPTC<maltc){
			return checkLopTC(t->pRight, maltc);
		}else{
			return 1;
		}
	}
}
void HuyDK(TREE &t,int maltc,char masv[],int choose1, int choose2){
	if(t!=NULL)
	{
		if(t->LopTC.MALOPTC>maltc){
			HuyDK(t->pLeft, maltc,masv,choose1,choose2);
		}
		else if(t->LopTC.MALOPTC<maltc){
			HuyDK(t->pRight, maltc,masv,choose1,choose2);
		}else{
			int huy = XoaDK(t->LopTC.pHead,masv,choose1,choose2);
			if(huy== -2){
				showMessageBox("THONG BAO","Danh sach da co diem\nKhong the huy",MB_OKCANCEL);
				HuyDKLTC(t,masv,choose1,choose2);
			}else if(huy == 2){
				showMessageBox("THONG BAO","Sinh vien chua dk lop tc",MB_OKCANCEL);
				HuyDKLTC(t,masv,choose1,choose2);
			}else if(huy==1){
				int x = showMessageBox("THONG BAO","Ban co chac muon huy dk",MB_OKCANCEL);
				if(x==IDOK){
					XoaDauDK(t->LopTC.pHead);
				}else{
					HuyDKLTC(t,masv,choose1,choose2);
				}
			}else if(huy==-1){
				int x = showMessageBox("THONG BAO","Ban co chac muon huy dk",MB_OKCANCEL);
				if(x==IDOK){
					XoaCuoiDK(t->LopTC.pHead);
				}else{
					HuyDKLTC(t,masv,choose1,choose2);
				}
			}else{
				int x = showMessageBox("THONG BAO","Ban co chac muon huy dk",MB_OKCANCEL);
				if(x==IDOK){
					XoaSauDK(t->LopTC.pHead,masv);
				}else{
					HuyDKLTC(t,masv,choose1,choose2);
				}
			}
		}
	}
}

void NhapMaSV(TREE &t,char masv[],int chooseFromMenu1,int chooseFromMenu2){
	string MASV[]={"Ma Sinh Vien"};
	KhungEdit(1,MASV);
	int x=61;
	int y=26;
	gotoxy(100,40);cout<<"Bam phim dac biet bat ky";
	XuatDanhSachSinhVienTheoMASV(head,0,false);
	InputCodeToUpper(masv,10,x,y);
	if(strlen(masv)==0){
		gotoxy(70,40);
		onExitEdit(chooseFromMenu1,chooseFromMenu2,"Ma sinh vien khong duoc de trong\nBan co muon thoat??");
		NhapMaSV(t,masv,chooseFromMenu1,chooseFromMenu2);
	}else{
		NODESV nodesv = searchSV(head,masv);
		if(nodesv==NULL){
			showMessageBox("Thong bao","Ma sinh vien khong ton tai",MB_OKCANCEL);
			NhapMaSV(t,masv,chooseFromMenu1,chooseFromMenu2);
		}else{
			int slSVDK = 0;
			int slltc = TongSoLopTinhChi(t);
			LOPTC l[slltc];
			MangTamLopTinChi_Da_DK(t,l,slSVDK,masv);
			if(slSVDK>0){
				HuyDKLTC(t,masv,chooseFromMenu1,chooseFromMenu2);
			}else{
				showMessageBox("Thong bao","Sinh vien chua dk lop tc nao",MB_OKCANCEL);
				NhapMaSV(t,masv,chooseFromMenu1,chooseFromMenu2);
			}
		}
	}
}
void HuyDKLTC(TREE &t,char masv[],int choose1,int choose2){
	clearEdit();
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	int chon = 0,col = 90,hang = 25,i;
	int slItem = SHOW_ITEM_DANGKY;
	gotoxy(80,26);cout<<"Ma lop tc";
	TaoKhungDon(40, 1, 124, 20);
	TaoKhungDon(40, 22, 124, 19);
	TaoKhungDon(col,hang,20,2);
	HienThiLoptcDaDK(t,masv);
	char MA[slMax]="";
	int kytu=0;
	do{
		switch(chon){
			case 0:
				InputNumberIsInteger(MA,6,col+1,26);
				break;
			default:
				continue;
		}
		kytu = getch();
		switch(kytu){
			case ENTER:
				c = XacNhanEdit(TEXT_XACNHAN,true);
				if(c==0){
					int mltc= atoi(MA);
					int ltc = checkLopTC(t,mltc);
					if(ltc==1){
						HuyDK(t,mltc,masv,choose1,choose2);
						GhiFileLopTinChi(t);
						int x = showMessageBox("THONG BAO","Huy dang ky thanh cong",MB_OKCANCEL);
						if(x==IDOK){
							HuyDKLTC(t,masv,choose1,choose2);
						}else{
							backMenu2(choose1,choose2);
						}
					}
					else{
						showMessageBox("THONG BAO","Lop tin chi ko ton tai",MB_OKCANCEL);
					}
				}
				break;
			case ESC:
				onExitEdit(choose1,choose2,"Ban muon thoat chuc nang nay?");
				break;
			default:
				continue;
		}
	}while(1);
}
void Tim_4_Field(TREE t, LOPTC &ltc,char MaMH[], char NienKhoa[], int HocKy, int Nhom){
	if(t != NULL)
	{
		Tim_4_Field(t->pLeft,ltc,MaMH,NienKhoa,HocKy,Nhom);
		Tim_4_Field(t->pRight,ltc,MaMH,NienKhoa,HocKy,Nhom);
		if(strcmp(t->LopTC.MAMH,MaMH) == 0 && strcmp(t->LopTC.NIENKHOA,NienKhoa) == 0 && t->LopTC.HOCKY == HocKy && t->LopTC.NHOM == Nhom)
		{
			ltc = t->LopTC;
		}
	}
}
void Nhap_4_Field(TREE t,int choose1,int choose2){
	clearEdit();
	bool flag = false;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	int chon = 0,col = 61,hang = 26,i = 0;
	int slItem = SHOW_ITEM_DSSVDK;
	KhungEdit(slItem,SHOW_TEXT_DSSVDK);
	ShowDanhSachLopTinChi(t);
	LOPTC ltc;
	gotoxy(61,26);
	char MAMH[11]="";
	char NIENKHOA[12]="";
	char HOCKY[2]="";
	char NHOM[3]="";
	int kytu = 0;
	do{
		switch(chon){
			case 0:
				InputCodeToUpper(MAMH,10,col,hang);
				break;
			case 1:
				InputStringIsSchoolYear(NIENKHOA,10,col,hang+3);
				break;
			case 2:
				InputNumberIsInteger(HOCKY,1,col,hang+6);
				break;
			case 3:
				InputNumberIsInteger(NHOM,1,col,hang+9);
				break;
			default:
				continue;
		}
		kytu = getch();
		switch(kytu){
			case UP:{
				if(chon>0){
					chon--;
				}else{
					chon = slItem-1;
				}
				break;
			}
			case DOWN:{
				if(chon<slItem-1){
					chon++;
				}else{
					chon=0;
				}
				break;
			}
			case ESC:{
				onExitEdit(choose1,choose2,"Ban co muon thoat chuc nang nay");
				break;
			}	
			case ENTER:{
				flag = true;
				int c = XacNhanEdit(TEXT_XACNHAN,flag);
				if(c==0){
					if(strlen(NIENKHOA)==NULL){
						showMessageBox("THONG BAO","Nien khoa khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strlen(HOCKY)==NULL){
						showMessageBox("THONG BAO","Hoc ky khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strcmp(HOCKY,"1")<0||strcmp(HOCKY,"3")>0){
						showMessageBox("THONG BAO","Hoc ky khong duoc nho hon 1 va lon hon 3",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strlen(NHOM)==NULL){
						showMessageBox("THONG BAO","Nhom khong duoc de trong",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else if(strlen(MAMH)==NULL){
						showMessageBox("THONG BAO","Khong duoc de trong ma mon hoc",MB_OK);
						flag = false;
						XacNhanEdit(TEXT_XACNHAN,flag);
					}else{
						int hky = atoi(HOCKY);
						int nhom = atoi(NHOM);
						int k = KT_4_Field(t,MAMH,NIENKHOA,hky,nhom);
						if(k == 0){
							cout<<k;
							showMessageBox("THONG BAO","Khong co lop tin chi ton tai",MB_OKCANCEL);
							flag = false;
							XacNhanEdit(TEXT_XACNHAN,flag);
						}else{
							Tim_4_Field(t,ltc,MAMH,NIENKHOA,hky,nhom);
							In_Bang_Diem_LTC(ltc,choose1,choose2);
						}
					}
				}
			}
				break;
			default: 
				continue;
		}
	}while(true);
}
void KhungBangDiem(LOPTC ltc){
	Normal();
	clearEdit();
	int x=40,y=6,width=124,height=35;
	KhungShow();
	char* tenMh = TenMonHoc(dsmh,ltc.MAMH);
	gotoxy(x+40,y-4);cout << "BANG DIEM MON HOC "<<tenMh;
	gotoxy(x+40,y-2);cout << "Nien khoa: "<<ltc.NIENKHOA<<".. "<<"Hoc ky: "<<ltc.HOCKY<<".. "<<"Nhom: "<<ltc.NHOM<<".";
	SetColor(10);
	gotoxy(x+5, y+2); cout << "STT";
	gotoxy(x+25, y+2); cout << "MASV";
	gotoxy(x+60, y+2); cout << "HO";
	gotoxy(x+92, y+2); cout << "TEN";
	gotoxy(x+115, y+2); cout << "DIEM";
	Normal();
	//======== Chot ================
	gotoxy(x+12, y); cout << char(194);
	gotoxy(x+40, y); cout << char(194);
	gotoxy(x+80, y); cout << char(194);
	gotoxy(x+105, y); cout << char(194);
//	//==============================
	gotoxy(x+12, y + 3); cout << char(193);
	gotoxy(x+40, y + 3); cout << char(193);
	gotoxy(x+80, y + 3); cout << char(193);
	gotoxy(x+105, y + 3); cout << char(193);
//	//==============================
	gotoxy(x, y+3); cout << char(195);
	gotoxy(x+width, y+3); cout << char(180);
//	//==============================
	for (int i = y+1; i < y+3; i++)
	{   
		gotoxy(x+12, i); cout << char(179);
		gotoxy(x+40, i); cout << char(179);
		gotoxy(x+80, i); cout << char(179);
		gotoxy(x+105, i); cout << char(179);
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+12 && i != x+40 && i != x+80&& i!=x+105)
		{
			gotoxy(i,y); cout << char(196);
		}
	}
	for (int i = x+1; i < x + width; i++)
	{
		if (i != x+12 && i != x+40 && i != x+80&& i!=x+105)
		{
			gotoxy(i,y + 3); cout << char(196);
		}
	}
	
}
void In_Bang_Diem_LTC(LOPTC ltc,int choose1,int choose2){
	clearEdit();
	KhungBangDiem(ltc);
	int stt = 1;
	int x=40,y=6,width=124,height=35;
	if(ltc.pHead!=NULL){
		NODEDK ndk = ltc.pHead;
		for(NODEDK p = ndk;p!=NULL;p=p->pNext){
			NODESV nsv = searchSV(head,p->dk.MASV);
			if(nsv!=NULL){
				gotoxy(x+6,y+4);cout<<stt;
				gotoxy(x+20,y+4);cout<<p->dk.MASV;
				gotoxy(x+55,y+4);cout<<nsv->sv.HO;
				gotoxy(x+90,y+4);cout<<nsv->sv.TEN;
				gotoxy(x+117,y+4);cout<<p->dk.DIEM;
				stt++;
				y++;
			}
		}
	}
	char key;
	do{
		key = _getch();
		switch(key){
			case ESC:
				onExitEdit(choose1,choose2,"Ban muon thoat chuc nang nay??");
				break;
			default:
				continue;
		}
	}while(1);
}
