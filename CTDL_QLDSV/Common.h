#pragma once
#include<iostream>
#include<string.h>
#include<string>
#include<fstream>
#include "myLib.h"


#define MAX 300

const char FILE_MONHOC[11] = "MonHoc.txt";
const char FILE_MALOPTINCHI[20] = "MaLopTinChiData.txt";
const char FILE_LOPTINCHI[14] = "LopTinChi.txt";
const char FILE_SINHVIEN[13] = "SinhVien.txt";
const int slMax = 13;

using namespace std;
//============ danh sach mon hoc ==============
struct MonHoc
{
	char MAMH[11];
	char TENMH[50];
	float STCLT;
	float STCTH;
};
typedef struct MonHoc MONHOC;

struct DanhSachMonHoc
{
	MONHOC* ds[MAX];
	int n = 0;	
};
typedef struct DanhSachMonHoc DSMH;



//============== danh sach sinh vien =============
struct SinhVien
{
	char MASV[11];
	char HO[51];
	char TEN[11];
	char PHAI[4];
	char SODT[12];	
	char MALOP[13];
	int NAMNHAPHOC;
};
typedef struct SinhVien SINHVIEN;

struct NodeSinhVien
{
	SinhVien sv;
	NodeSinhVien* pNext;
};
typedef struct NodeSinhVien* NODESV;


//===============  Danh sach dang ky ================
struct DangKy
{
	char MASV[12];
	float DIEM;
};
typedef struct DangKy DANGKY;

struct NodeDangKy
{
	DangKy dk;
	NodeDangKy* pNext;
};
typedef struct NodeDangKy* NODEDK;



//=============== danh sach lop tin chi =============
struct LopTinChi
{
	int MALOPTC;
	char MAMH[11];
	char NIENKHOA[10];
	int HOCKY;
	int NHOM;
	int MAXSV;
	int MINSV;
	
	NODEDK pHead;
};
typedef struct LopTinChi LOPTC;

struct NodeLopTinChi
{
	LOPTC LopTC;
	NodeLopTinChi* pLeft;
	NodeLopTinChi* pRight;	
};
typedef struct NodeLopTinChi* TREE;

//===================================================





DSMH dsmh;
TREE t = NULL;
NODESV head;
NODEDK dsdk;
char MALOPSV[slMax];
char MASVSV[slMax];
