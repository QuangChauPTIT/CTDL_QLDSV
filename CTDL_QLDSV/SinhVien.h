#pragma once
#include "Common.h"
#include "DangKy.h"
#include "LopTinChi.h"
#include "MonHoc.h"
#include "SinhVien.h"
#include "myLib.h"
int checkMasv(NODESV nsv, char Masv[]);
void deletedSvByMasv(char Text[],int chooseFromMenu1,int chooseFromMenu2);
NODESV CreateNodeSV(SINHVIEN sinhvien){
	NODESV p = new NodeSinhVien;
	if(p == NULL){
		cout<<"Khong du bo nho de cap phat";
		return NULL;
	}
	p->sv = sinhvien;
	p->pNext = NULL;
	return p;
}
void ThemSV(NODESV &nsv,SINHVIEN sv){
	nsv = new NodeSinhVien;
	nsv->sv = sv;
	nsv->pNext = NULL;
}
int insertNodeSV(NODESV &nsv, SinhVien sv) {
	NODESV nodesv = CreateNodeSV(sv);
	if (nodesv == NULL) {
		return 0;
	}
	if (nsv == NULL) {
		head = nodesv;
	}
	else {
		for (NODESV p = head; p != NULL; p = p->pNext) {
			if (p->pNext == NULL) {
				p->pNext = nodesv;
				break;
			}
		}
	}
	return 1;
}
int DemSinhVien(NODESV nsv)
{
	int dem = 0;
	for (NODESV p = nsv; p != NULL; p = p->pNext) { dem++; }
	return dem;
}
void GhiFileSinhVien(NODESV nsv)
{
	ofstream f;
	f.open(FILE_SINHVIEN,ios::out);
	if(f.fail()){
		cout<<"Ghi file loi!!!!";
		return;
	}
	int slSV = DemSinhVien(nsv);
	f<<slSV<<endl;
	for(NODESV p = nsv;p != NULL;p =p->pNext)
	{
		//ghi_file(f,p->sv);
		SINHVIEN svien = p->sv; 
		f<< svien.MALOP <<" " <<svien.MASV <<" " << svien.TEN <<" " << svien.PHAI <<" " << svien.SODT <<" " << svien.NAMNHAPHOC<<endl;
		f<< svien.HO<<endl;
	}
	f.close();
}

void DocFileSinhVien(NODESV &nsv)
{
	fstream f;
	f.open(FILE_SINHVIEN,ios::in);
	if(f.fail())
	{
		gotoxy(60,20);
		cout<<"file khong ton tai";
		getch();
		return;
	}
	int slsv = 0,i;
	f>>slsv;
	int x;
	string Ho;
	string space;
	if(slsv>0){
		SINHVIEN sv;
		for(i=0;i<slsv;i++)
		{
			f>>sv.MALOP;
			f>>sv.MASV;
			f>>sv.TEN;
			f>>sv.PHAI;
			f>>sv.SODT;
			f>>sv.NAMNHAPHOC;
			getline(f,space);
			getline(f,Ho); strcpy(sv.HO,Ho.c_str());
			x = insertNodeSV(nsv, sv);
			if (x == 0) {
				gotoxy(70, 40); cout << "fail to insert";
			}
		}
	}
	f.close();
}

void Insert_First(NODESV &First,SINHVIEN sinhvien){
		NODESV p = new NodeSinhVien;
		p->sv = sinhvien;
		p->pNext = First;
		First = p;
}
void Insert_After(NODESV &p,SINHVIEN sinhvien){
	NODESV q = new NodeSinhVien;
	q->sv = sinhvien;
	q->pNext = p->pNext;
	p->pNext = q;
}
void Insert_Order(NODESV &First,SINHVIEN sinhvien){
	NODESV p,q,t;
	q = NULL;
	for(p = First;p!=NULL&&(strcmp(p->sv.MALOP,sinhvien.MALOP) < 0);p = p->pNext){
		q = p;
	}
	if(q==NULL){
		if(First != NULL && strcmp(p->sv.MALOP,sinhvien.MALOP)==0){
			p=NULL;
			for(t = First;t != NULL && (strcmp(t->sv.MALOP,sinhvien.MALOP)==0) && (strcmp(t->sv.MASV,sinhvien.MASV)<0);t = t->pNext){
				p = t;
			}
			if(p==NULL){
				Insert_First(First,sinhvien);
			}else{
				Insert_After(p,sinhvien);
			}
		}else{
			Insert_First(First,sinhvien);
		}
	}else{
		p = q->pNext;
		if(p!=NULL&&strcmp(p->sv.MALOP,sinhvien.MALOP)==0){
			p = NULL;
			for(t = q->pNext; t != NULL && strcmp(t->sv.MALOP,sinhvien.MALOP)==0 &&strcmp(t->sv.MASV,sinhvien.MASV)<0;t = t->pNext){
				p = t;
			}
			if(p == NULL){
				Insert_First(q->pNext,sinhvien);
			}else{
				Insert_After(p,sinhvien);
			}
		}else{
			Insert_After(q,sinhvien);
		}
	}
}
int checkMasv(NODESV nsv, char Masv[]){
	for(NODESV p = nsv; p != NULL; p = p->pNext){
		if(strcmp(p->sv.MASV,Masv)==0&&p==nsv){//dau ds
			return 1;
		}
		if(strcmp(p->sv.MASV,Masv)==0&&p->pNext==NULL){//cuoi ds
			return -1;
		}
		if(strcmp(p->sv.MASV,Masv)==0&&p->pNext!=NULL){//giua ds
			return 0;
		}
	}
	return 2;
}
NODESV searchSV(NODESV nsv,char Masv[]){
	if(nsv == NULL){
		return NULL;
	}
	for(NODESV p = nsv; p != NULL; p = p->pNext){
		if(strcmp(p->sv.MASV,Masv)==0){
			return p;
		}
	}
	return NULL;
}
void sapxepSVByMASV(NODESV &nsv){
	NODESV t;
	NODESV p;
	NODESV q;
	SINHVIEN sv;
	if(nsv==NULL){
		return;
	}
	for(p = nsv; p != NULL; p = p->pNext){
		t=p;
		sv=t->sv;
		for(q = p; q != NULL; q = q->pNext){ //duyet tu dau den phan tu q = null
			char s[slMax] = "";
			strcpy(s,t->sv.MASV); //s=t->sv.MASV
			if(strcmp(s,q->sv.MASV)>0){
				t=q;
			}
		}
		p->sv = t->sv;
		t->sv = sv;
	}
}
void KhungDSSV(){
	Normal();
	int key,col = 52,hang = 3;
	gotoxy(col-3,hang);cout<<"Lop";
	gotoxy(col + 12, hang); cout<<"Ma SV";
	gotoxy(col + 30, hang); cout<<"Ho";
	gotoxy(col + 45, hang); cout<<"Ten";
	gotoxy(col + 55, hang); cout<<"Gioi tinh";
	gotoxy(col + 73, hang);cout<<"So DT";
	gotoxy(col + 93, hang);cout<<"Nam nhap hoc";
//===============================================
	gotoxy(col+8, hang-2); cout << char(194);
	gotoxy(col+25, hang-2); cout << char(194);
	gotoxy(col+40, hang-2); cout << char(194);
	gotoxy(col+52, hang-2); cout << char(194);
	gotoxy(col+65, hang-2); cout << char(194);
	gotoxy(col+85, hang-2); cout << char(194);
//===============================================
	gotoxy(col+8, hang+2); cout << char(193);
	gotoxy(col+25, hang+2); cout << char(193);
	gotoxy(col+40, hang+2); cout << char(193);
	gotoxy(col+52, hang+2); cout << char(193);
	gotoxy(col+65, hang+2); cout << char(193);
	gotoxy(col+85, hang+2); cout << char(193);
//================================================
	gotoxy(col-12, hang+2); cout << char(195);
	gotoxy(col+112, hang+2); cout << char(180);
//================================================
	for (int i = hang-1; i < hang+2; i++)
	{
		gotoxy(col+8,  i); cout << char(179);
		gotoxy(col+25, i); cout << char(179);
		gotoxy(col+40, i); cout << char(179);
		gotoxy(col+52, i); cout << char(179);
		gotoxy(col+65, i); cout << char(179);
		gotoxy(col+85, i); cout << char(179);
	}
	for (int i = col-11; i < col + 112; i++)
	{
		if (i != col+8 && i != col+25 && i != col+40 && i != col+52 && i != col+65 && i != col+85)
		{
			gotoxy(i, 5); cout << char(196);
		}
	}
}
void XuatDanhSachSinhVienTheoMASV(NODESV nsv,int dem,bool flag)
{
	sapxepSVByMASV(nsv);
	KhungDSSV();
	int n;
	if(flag==true){
		n = dem+50;
	}else{
		n = dem+10;
	}
	
	int key,col = 49,hang = 7;
	for(NODESV p = nsv; p != NULL&&dem<n;p=p->pNext)
	{
		dem++;
		gotoxy(col - 3,  hang); cout<<p->sv.MALOP<<endl;
		gotoxy(col + 15, hang); cout<<p->sv.MASV<<endl;
		gotoxy(col + 30, hang); cout<<p->sv.HO<<endl;
		gotoxy(col + 47, hang); cout<<p->sv.TEN<<endl;
		gotoxy(col + 60, hang); cout<<p->sv.PHAI<<endl;
		gotoxy(col + 73, hang); cout<<p->sv.SODT<<endl;
		gotoxy(col + 100,hang); cout<<p->sv.NAMNHAPHOC<<endl;
		hang++;
	}
	if(flag==true){
		do{
			char key = getch();
			switch(key){
				case ESC:
					onExitEdit(2,4,"Ban muon thoat chuc nang nay??");
					break;
				default:
					continue;
			}
		}while(1);
	}
}
void XuatDanhSachSinhVienTheoLOP(NODESV nsv,char mlop[],int dem,bool flag)
{
	KhungShow();
	sapxepSVByMASV(nsv);
	KhungDSSV();
	int n;
	if(flag==true){
		n = dem+50;
	}else{
		n = dem+10;
	}
	
	int key,col = 49,hang = 7;
	for(NODESV p = nsv; p != NULL&&dem<n;p=p->pNext)
	{
		if(strcmp(p->sv.MALOP,mlop)==0){
			dem++;
			gotoxy(col - 3,  hang); cout<<p->sv.MALOP<<endl;
			gotoxy(col + 15, hang); cout<<p->sv.MASV<<endl;
			gotoxy(col + 30, hang); cout<<p->sv.HO<<endl;
			gotoxy(col + 47, hang); cout<<p->sv.TEN<<endl;
			gotoxy(col + 60, hang); cout<<p->sv.PHAI<<endl;
			gotoxy(col + 73, hang); cout<<p->sv.SODT<<endl;
			gotoxy(col + 100,hang); cout<<p->sv.NAMNHAPHOC<<endl;
			hang++;
		}
	}
	if(flag==true){
		do{
			char key = getch();
			switch(key){
				case ESC:
					onExitEdit(2,4,"Ban muon thoat chuc nang nay??");
					break;
				default:
					continue;
			}
		}while(1);
	}
}
void insertSinhVien(NODESV &nsv,char MALOP[],int chooseFromMenu1,int chooseFromMenu2){
	Normal();
	clearScreen(40,2,124,40);
	bool flag = false;
	int chon = 0,col = 61,hang = 26,i = 0;
	XuatDanhSachSinhVienTheoLOP(nsv,MALOP,0,false);
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	int slItem = SHOW_ITEM_DSSV;
	string Text = "Ban muon ngung them sv";
	string Textsv = "Ban vua nhap vao chuoi rong\nBan muon ngung them sv";
	
	KhungEdit(slItem,SHOW_TEXT_DSSV);
	SINHVIEN sv;
	
	gotoxy(61,26);
	char MASV[slMax] ="";
	char HO[51]="";
	char TEN[11]="";
	char PHAI[4]="";
	char SODT[12]="";
	char NAMHOC[5]="";
	int kytu;
	int key=0;
	do{
		switch(chon){
			case 0:
				InputCodeToUpper(MASV,12,col,hang);
				break;
			case 1:
				InputStringNamePeople(HO,15,col,hang+3);
				break;
			case 2:
				InputStringNamePeople(TEN,10,col,hang+6);
				break;
			case 3:
				InputStringName(PHAI,4,col,hang+9);
				break;
			case 4:
				InputNumberIsInteger(SODT,11,col+60,hang);
				break;
			case 5:
				InputNumberIsInteger(NAMHOC,5,col+60,hang+3);
				break;
			default:
				continue; 
		}
		kytu = getch();
		switch(kytu){
		case UP:
			if(chon > 0){
				chon--;
			}else{
				chon = slItem-1;
			}
			break;
		case DOWN:
			if(chon < slItem-1){
				chon++;
			}else{
				chon=0;
			}
			break;
		case ESC:
			//KhungShow();
			onExitEdit(chooseFromMenu1,chooseFromMenu2,Text);
			//backMenu2(chooseFromMenu1,chooseFromMenu2);
			break;
		case ENTER:
			flag = true;
			c = XacNhanEdit(TEXT_XACNHAN,flag);
			if(c==0){
				int x = checkMasv(head,MASV);
				flag=false;
				XacNhanEdit(TEXT_XACNHAN,flag);
				if(strlen(MASV) == 0){
					//gotoxy(70,40);
					onExitEdit(chooseFromMenu1,chooseFromMenu2,Textsv);
					break;
				}else if(x != 2){
					gotoxy(70,40);
					cout<<"Ma sv da ton tai "<<MASV;
					flag=false;
					XacNhanEdit(TEXT_XACNHAN,flag);
				}else if(strlen(HO)==0){
					gotoxy(70,40);
					cout<<"Ho khong duoc de trong ";
				}else if(strlen(TEN)==0){
					gotoxy(70,40);
					cout<<"Ten khong duoc de trong ";
				}else if(strlen(PHAI)==0){
					gotoxy(70,40);
					cout<<"Phai khong duoc de trong ";
				}else if(strcmp(PHAI,"Nam")!=0&&strcmp(PHAI,"Nu")!=0){
					gotoxy(70,40);
					cout<<"Phai la Nam hoac Nu ";
				}else if(strlen(SODT)==0){
					gotoxy(70,40);
					cout<<"So dien thoai khong duoc de trong ";
				}else if(strlen(NAMHOC)==0){
					gotoxy(70,40);
					cout<<"Nam hoc khong duoc de trong ";
				}else if(atoi(NAMHOC)<2010){
					gotoxy(70,40);
					cout<<"Nam hoc khong duoc nho hon 2010";
				}else{
					strcpy(sv.MASV,MASV);
					strcpy(sv.HO,HO);
					strcpy(sv.TEN,TEN);
					strcpy(sv.PHAI,PHAI);
					strcpy(sv.SODT,SODT);
					strcpy(sv.MALOP,MALOP);
					sv.NAMNHAPHOC = atoi(NAMHOC);
					Insert_Order(nsv,sv);
					gotoxy(70,39);
					cout<<"THANH CONG "<<sv.MASV;
					GhiFileSinhVien(nsv);
					int rs = showMessageBox("THONG BAO", "Them thanh cong\nBan muon tiep tuc??", MB_ICONQUESTION);
					if(rs == IDOK){
						insertSinhVien(nsv,MALOP,chooseFromMenu1,chooseFromMenu2);
					}else{
						backMenu2(chooseFromMenu1,chooseFromMenu2);
					}
				}
			}else{
				insertSinhVien(nsv,MALOP,chooseFromMenu1,chooseFromMenu2);	
			}
			break;
			default:
				continue;
		}
		//cout<<key;
		//cout<<chon;
		
	}while(1);
}
void sapxepSV(NODESV &nsv){
	NODESV t;
	NODESV p;
	NODESV q;
	SINHVIEN sv;
	if(nsv==NULL){
		return;
	}
	for(p = nsv;p != NULL;p=p->pNext){ //duyet tu dau cho toi phan tu p = NULL
		t = p;
		sv = t->sv;
		for(q = p; q != NULL; q = q->pNext){ //duyet tu dau den phan tu q = null
			char x[slMax] ="";
			strcpy(x,sv.MALOP); //x=sv.MALOP
			if(strcmp(x,q->sv.MALOP)>0){
				t = q;
			}else{
				if(strcmp(x,q->sv.MALOP)==0){
					char s[slMax] = "";
					strcpy(s,t->sv.MASV); //s=t->sv.MASV
					if(strcmp(s,q->sv.MASV)>0){
						t=q;
					}
				}
			}
		}
		p->sv = t->sv;
		t->sv = sv;
	}
}

void editSinhVien(NODESV &nsv,char Masv[],int chooseFromMenu1,int chooseFromMenu2){
	Normal();
	clearScreen(40,2,124,40);
	bool flag = false;
	int chon = 1,col = 61,hang = 26,i = 0;
	
	int slItem = 7;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,SHOW_TEXT_DSSV1);
	NODESV nodesv = searchSV(nsv,Masv);
	gotoxy(61,29);
	char NAMHOC[5]="";
	
	gotoxy(col,hang); cout<<nodesv->sv.MASV;
	gotoxy(col,hang+3); cout<<nodesv->sv.HO;
	gotoxy(col,hang+6); cout<<nodesv->sv.TEN;
	gotoxy(col,hang+9); cout<<nodesv->sv.PHAI;
	gotoxy(col+60,hang); cout<<nodesv->sv.SODT;
	gotoxy(col+60,hang+3); cout<<nodesv->sv.MALOP;
	gotoxy(col+60,hang+6); cout<<nodesv->sv.NAMNHAPHOC;
	
	itoa(nodesv->sv.NAMNHAPHOC,NAMHOC,10);
	
	int kytu;
	int key=0;
	do{
		switch(chon){
			case 0:
				InputCodeToUpper(nodesv->sv.MASV,5,col,hang);
				break;
			case 1:
				InputStringNamePeople(nodesv->sv.HO,10,col,hang+3);
				break;
			case 2:
				InputStringNamePeople(nodesv->sv.TEN,10,col,hang+6);
				break;
			case 3:
				InputStringName(nodesv->sv.PHAI,10,col,hang+9);
				break;
			case 4:
				InputNumberIsInteger(nodesv->sv.SODT,10,col+60,hang);
				break;
			case 5:
				InputCodeToUpper(nodesv->sv.MALOP,10,col+60,hang+3);
				break;
			case 6:
				InputNumberIsInteger(NAMHOC,5,col+60,hang+6);
				break;
			default:
				continue; 
		}
		kytu = getch();
		switch(kytu){
		case UP:
			if(chon > 1){
				chon--;
			}else{
				chon = slItem-1;
			}
			break;
		case DOWN:
			if(chon < slItem-1){
				chon++;
			}else{
				chon=1;
			}
			break;
		case ESC:
			KhungShow();
			onExitEdit(chooseFromMenu1,chooseFromMenu2,"Ban muon thoat chuc nang nay");
			break;
		case ENTER:
			flag = true;
			c = XacNhanEdit(TEXT_XACNHAN,flag);
			if(c==0){
				//int x = checkMasv(head,MASV);
				flag=false;
				XacNhanEdit(TEXT_XACNHAN,flag);
				if(strlen(nodesv->sv.MASV) == 0){
					gotoxy(70,40);cout<<"Ma sinh vien khong duoc de trong ";
				}
				else if(strlen(nodesv->sv.HO)==0){
					gotoxy(70,40);
					cout<<"Ho khong duoc de trong ";
				}else if(strlen(nodesv->sv.TEN)==0){
					gotoxy(70,40);
					cout<<"Ten khong duoc de trong ";
				}else if(strlen(nodesv->sv.PHAI)==0){
					gotoxy(70,40);
					cout<<"Phai khong duoc de trong ";
				}else if(strcmp(nodesv->sv.PHAI,"Nam")!=0&&strcmp(nodesv->sv.PHAI,"Nu")!=0){
					gotoxy(70,40);
					cout<<"Phai la Nam hoac Nu ";
				}else if(strlen(nodesv->sv.SODT)==0){
					gotoxy(70,40);
					cout<<"So dien thoai khong duoc de trong ";
				}else if(strlen(NAMHOC)==0){
					gotoxy(70,40);
					cout<<"Nam hoc khong duoc de trong ";
				}else{
					nodesv->sv.NAMNHAPHOC = atoi(NAMHOC);
					gotoxy(70,38);
					sapxepSV(nsv);
					//gotoxy(70,40);
					//cout<<"SUA THANH CONG "<<nodesv->sv.MASV;
					GhiFileSinhVien(nsv);
					int rs = showMessageBox("THONG BAO", "Sua sinh vien thanh cong!!!", MB_ICONQUESTION);
					if(rs == IDOK){
						backMenu2(chooseFromMenu1,chooseFromMenu2);
					}else{
						backMenu2(chooseFromMenu1,chooseFromMenu2);
					}
				}
			}else{
				onExitEdit(chooseFromMenu1,chooseFromMenu2,"Ban muon thoat chuc nang nay");
			}
			break;
			default:
				continue;
		}
	}while(1);
}
void deletedFirst(NODESV &nsv){
	NODESV p;
	if(nsv == NULL){
		return;
	}else{
		p = nsv;
		nsv = p->pNext;
		delete p;
	}
}
void deletedAfter(NODESV &nsv,char Text[]){
	NODESV p,q;
	if(nsv == NULL || nsv->pNext == NULL){
		return;
	}else{
		for(p = nsv; p -> pNext != NULL && strcmp(p->pNext->sv.MASV,Text)!=0; p = p->pNext);
		if(p->pNext != NULL){
			q=p->pNext;
			p->pNext = q->pNext;
			delete q;
		}
	}
}
void deletedLast(NODESV &nsv){
	NODESV p;
	for(p=nsv;p->pNext->pNext!=NULL;p=p->pNext);
	delete(p->pNext);
	p->pNext=NULL;
}
void deletedSinhVien(NODESV &nsv,char Masv[],int chooseFromMenu1,int chooseFromMenu2){
	Normal();
	clearScreen(40,2,124,40);
	bool flag = true;
	int chon = 1,col = 61,hang = 26,i = 0;
	
	int slItem = 7;
	int c = XacNhanEdit(TEXT_XACNHAN,flag);
	KhungEdit(slItem,SHOW_TEXT_DSSV1);
	NODESV nodesv = searchSV(nsv,Masv);
	gotoxy(61,29);
	char NAMHOC[5]="";
	
	gotoxy(col,hang); cout<<nodesv->sv.MASV;
	gotoxy(col,hang+3); cout<<nodesv->sv.HO;
	gotoxy(col,hang+6); cout<<nodesv->sv.TEN;
	gotoxy(col,hang+9); cout<<nodesv->sv.PHAI;
	gotoxy(col+60,hang); cout<<nodesv->sv.SODT;
	gotoxy(col+60,hang+3); cout<<nodesv->sv.MALOP;
	gotoxy(col+60,hang+6); cout<<nodesv->sv.NAMNHAPHOC;
	
	itoa(nodesv->sv.NAMNHAPHOC,NAMHOC,10);
	
	int kytu;
	int key=0;
	do{
		kytu = getch();
		switch(kytu){
		case ESC:
			KhungShow();
			onExitEdit(chooseFromMenu1,chooseFromMenu2,"Ban muon thoat chuc nang nay");
			break;
		case ENTER:
			flag = true;
			c = XacNhanEdit(TEXT_XACNHAN,flag);
			if(c==0){
				int x = checkMasv(head,Masv);
				flag=false;
				if(x==1){
					gotoxy(70,37);cout<<"Xoa dau";
					deletedFirst(nsv);
				}else if(x==-1){
					gotoxy(70,37);cout<<"Xoa cuoi";
					deletedLast(nsv);
				}else if(x==0){
					gotoxy(70,37);cout<<"Xoa giua1";
					deletedAfter(nsv,Masv);
				}else{
					gotoxy(70,40); cout<<"Ma sv ko ton tai";
				}
				XacNhanEdit(TEXT_XACNHAN,flag);
				gotoxy(70,38);
				sapxepSV(nsv);
				GhiFileSinhVien(nsv);
				int rs = showMessageBox("THONG BAO", "Xoa sinh vien thanh cong!!!", MB_OK);
					if(rs == IDOK){
						backMenu2(chooseFromMenu1,chooseFromMenu2);
					}else{
						backMenu2(chooseFromMenu1,chooseFromMenu2);
					}
			}else{
				onExitEdit(chooseFromMenu1,chooseFromMenu2,"Ban muon thoat chuc nang nay");
			}
			break;
			default:
				continue;
		}
		//cout<<key;
		//cout<<chon;
		
	}while(1);
}
void insertMALOP(char Text[],int chooseFromMenu1,int chooseFromMenu2){
	string MALOP[]={"MA LOP"};
	KhungEdit(1,MALOP);
	int x=61;
	int y=26;
	InputCodeToUpper(Text,10,x,y);
	if(strlen(Text)==0){
		gotoxy(70,40);
		cout<<"Ma lop khong duoc de trong ";
		backMenu2(chooseFromMenu1,chooseFromMenu2);
	}else{
		insertSinhVien(head,Text,chooseFromMenu1,chooseFromMenu2);
	}
}
void insertMALOP_INDSSV(NODESV nsv,int chooseFromMenu1,int chooseFromMenu2){
	string MALOP[]={"MA LOP"};
	KhungEdit(1,MALOP);
	int x=61;
	int y=26;
	char mlop[slMax]="";
	InputCodeToUpper(mlop,10,x,y);
	if(strlen(mlop)==0){
		gotoxy(70,40);
		cout<<"Ma lop khong duoc de trong ";
		backMenu2(chooseFromMenu1,chooseFromMenu2);
	}else{
		XuatDanhSachSinhVienTheoLOP(nsv,mlop,0,true);
	}
}
void editSvByMasv(char Text[],int chooseFromMenu1,int chooseFromMenu2){
	string MASV[]={"Ma Sinh Vien"};
	KhungEdit(1,MASV);
	int x=61;
	int y=26;
	gotoxy(100,40);cout<<"Bam phim dac biet bat ky";
	InputCodeToUpper(Text,10,x,y);
	if(strlen(Text)==0){
		gotoxy(70,40);
		cout<<"Ma lop khong duoc de trong ";
		backMenu2(chooseFromMenu1,chooseFromMenu2);
	}else{
		NODESV nodesv = searchSV(head,Text);
		if(nodesv==NULL){
			gotoxy(70,40); cout<<"Ma sv khong ton tai";
			editSvByMasv(Text,chooseFromMenu1,chooseFromMenu2);
		}else{
			editSinhVien(head,Text,chooseFromMenu1,chooseFromMenu2);
		}
	}
}
void deletedSvByMasv(char Text[],int chooseFromMenu1,int chooseFromMenu2){
	string MASV[]={"Ma Sinh Vien"};
	KhungEdit(1,MASV);
	int x=61;
	int y=26;
	gotoxy(100,40);cout<<"Bam phim dac biet bat ky";
	InputCodeToUpper(Text,10,x,y);
	if(strlen(Text)==0){
		gotoxy(70,40);
		cout<<"Ma lop khong duoc de trong ";
		backMenu2(chooseFromMenu1,chooseFromMenu2);
	}else{
		NODESV nodesv = searchSV(head,Text);
		if(nodesv==NULL){
			gotoxy(70,40); cout<<"Ma sv khong ton tai";
			deletedSvByMasv(Text,chooseFromMenu1,chooseFromMenu2);
		}else{
			deletedSinhVien(head,Text,chooseFromMenu1,chooseFromMenu2);
		}
	}
}

