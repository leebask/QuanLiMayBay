#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <mylib.h>
#include <fstream>
#include <windows.h>
#include <cwchar>
#include <ctype.h>
#include <ctime>
#include <conio.h>
#include <sstream> 
#include <string>
#define MAXMB 300
#define MAXVE 30
#define PageCB 1
//-------------------------COLOR-----------------------
#define ColorBLACK			0
#define ColorDARKBLUE		1
#define ColorDARKCYAN		3
#define ColorDARKRED		4
#define ColorPURPLE			5
#define ColorDARKYELLOW		6
#define ColorDARKWHITE		7
#define ColorGRAY			8
#define ColorBLUE			9
#define ColorGREEN		 	10
#define ColorCYAN			11
#define ColorRED			12
#define ColorPINK			13
#define ColorYELLOW			14
#define ColorWHITE			15
//---------------HOTKEY------------------
#define Enter 13
#define BACKSPACE 8
#define ESC 27
#define Tab 9
#define Up 72
#define Down 80
#define Left 75
#define Right 77
#define Space 32
#define Page_Down 81// 224
#define Page_Up 73
#define Insert 82
#define Del 83
#define Home 71
#define End 79// 224
#define F1 59
#define F2 60
#define F3 61
#define F4 62
//----------------------------
#define boxx 18 //Vi tri x bat dau cua box
#define boxy 15 //Vi tri y bat dau cua box
#define boxs 60 //Box size
#define tabx 6 // vi tri x bat dau cua table
#define taby 4  // vi tri y bat dau cua table
#define tabs 83 // table box
#define tabw 20 // table hight
#define box2x 50 //Vi tri x bat dau cua box2 
#define box2y 30 //Vi tri y bat dau cua box2
#define box2s 60 //Box2 size
#define tab2x 6 // vi tri x bat dau cua table2
#define tab2y 4  // vi tri y bat dau cua table2
#define tab2s 86 // table box2
#define tab2w 15	// table2 hight
#define xNgay 78
#define yNgay 28
#define xVe 5
#define yVe 14
using namespace std;



//------------------------------time
struct ThoiGian{
	int gio, phut, ngay, thang, nam;
};


//---------------------Ve may bay----------------------------------------------------------------------------------------------------
struct Ve {
    char cmnd[16];
//    string TTVe;
};


//------------------------May Bay----------------------------------------------------------------------------------------------------
struct mayBay{
	char soHieuMB[15];
	char loaiMB[40];
	int soCho;
};
struct listMayBay{
	int soluong;
	mayBay *maybay[MAXMB];
};
typedef struct listMayBay ListMayBay;
int Empty_MB(ListMayBay dsMB)
{
	return dsMB.soluong == 0;
}
int Full_MB(ListMayBay dsMB)
{
	return dsMB.soluong == MAXMB;
}

void DocFileMayBay(ListMayBay &listmb);

//------------------------------------------------------------CHECK - GET-----------------------------
int Check_SoHieu_MB(ListMayBay listMB, char sohieu[])
{
	if (Empty_MB(listMB))
		return -1;
	else
	{
		for (int i = 0; i < listMB.soluong; i++)
		{
			if (stricmp(listMB.maybay[i]->soHieuMB, sohieu) == 0)
				return i;
		}
		return -1;
	}
}
int Get_socho(ListMayBay lmb, char soHieu[])
{
	for (int i = 0; i < lmb.soluong; i++)
	{
		if (strcmp(lmb.maybay[i]->soHieuMB, soHieu) == 0)
			return lmb.maybay[i]->soCho;
	}
	return -1;
}
//----------------------Chuyen bay----------------------------------------------------------------------------------------------------
struct ChuyenBay{
	char MaChuyenBay[15];
	char SanBayDen[20];
    ThoiGian ThoiGianDi;
	char soHieuMB[15];
	int TrangThai;// 0: huy chuyen 1: con ve, 2: het ve,3: hoan tat
	int TongSoDaBan;
	Ve *DsVe;
};


struct nodeCB {
	ChuyenBay CB;
	nodeCB *next;
};
typedef nodeCB* ptrCB;


struct listCB
{
	nodeCB *Head;
	nodeCB *Tail;
	int SoLuongChuyenBay;
};
typedef struct listCB* ListCB;

//------CHUC NANG CHUYEN BAY-----------------
void NhapChuyenBay(ListMayBay lmb,listCB &list);
void MenuChuyenBay(ListMayBay lmb,listCB &list);
void Danh_Sach_MayBay(ListMayBay &lmb,listCB &list);
void MenuDatVeMB(ListMayBay lmb,listCB list);
void DanhSachChuyenBayTheoNgay(ListMayBay lmb,listCB list);
void MenuHuyVe(ListMayBay lmb,listCB list);
// KHOI TAO CHUYEN BAY


//Khoi Tao list
void InitFlightList(listCB &list)
{
	list.Head = NULL;
	list.Tail = NULL;
	list.SoLuongChuyenBay = 0;

}

void initListVe(ChuyenBay &cb, int socho){
	cb.DsVe = new Ve[socho+1];
	cb.TongSoDaBan = 0;
	for(int dem=0;dem <= socho;dem++){
		strcpy(cb.DsVe[dem].cmnd,"");
	}
	
}

// Khoi tao node 
nodeCB *CreateNode_CB(ChuyenBay cb_moi)
{
	nodeCB *temp = new nodeCB;
	if(temp != NULL)
	{
		temp->CB = cb_moi;
		temp->next = NULL;
	}
	else
		return NULL;
	return temp;
}

//THEM DAU DANH SACH

void AddBeginningList(listCB &list,ChuyenBay cb)
{
	nodeCB *temp = CreateNode_CB(cb);
	if(list.Head==NULL){
		list.Head=temp;
		list.Tail=temp;
	}else
	{	
		temp->next = list.Head;
		list.Head = temp;
	}
	list.SoLuongChuyenBay++;
}


//THEM CUOI DANH SACH
void AddEndingList(listCB &list,ChuyenBay cb)
{
	nodeCB *temp = CreateNode_CB(cb);

	if( list.Head == NULL )
	{
		list.Head=temp;
		list.Tail=temp;
	}
	else
	{
		list.Tail->next = temp;
		list.Tail = temp;
		list.Tail->next = NULL;
	}
	list.SoLuongChuyenBay++;
}

// DELETE FIRST
int Delete_First (listCB &list)
{ 
	ptrCB temp;
   if (list.Head==NULL)
      return 0;
    temp = list.Head;    // nut can xoa la nut dau
    list.Head = temp->next;
    delete temp; 
    return 1;
}


// DELETE AFTER
int  Delete_after(ptrCB &p)
{   nodeCB *q;
  // neu p là NULL hoac sau p không có nút
   if((p == NULL) || (p->next == NULL))	
      return 0;
    q = p->next;  // q chi nut can xoa
     p->next = q->next;
     delete q;
     return 1;
}

// Tim so thu tu dua vao MaChuyenBay
int TimSTTChuyenBay( listCB list,char *MaChuyenBayCanTim)
{
	int index = 0;
	for( nodeCB *search = list.Head ; search != NULL; search = search->next)
	{
		/*so sanh 2 chuoi voi nhau co phan biet hoa thuong*/
		if( _stricmp(search->CB.MaChuyenBay,MaChuyenBayCanTim) == 0 )
		{
			return index;
		}
		index++;
	}
	return -1;
}

nodeCB* DuyetCB(listCB list,int index)
{
	nodeCB *pNode = list.Head;
	if(index!=0)
	{
		for (int count = 0; count < index; pNode=pNode->next)
		{
			count++;	
		}
	}
	return pNode;
}
int FindDestination( listCB list,char* SanBayDenCanTim)
{
	int index = 0;
	for( nodeCB *search = list.Head ; search != NULL; search = search->next)
	{
		if( _stricmp(search->CB.SanBayDen ,SanBayDenCanTim) == 0 )
		{
			return index;
		}
		index++;
	}
	return -1;
}
// TIM CHUYEN BAY THEO MA~
nodeCB *TimChuyenBay ( listCB list,char *MaChuyenBayCanTim)
{
	if( list.Head == NULL)
		return NULL;
	for( nodeCB *search = list.Head ; search != NULL; search = search->next)
	{
		if( _strcmpi(search->CB.MaChuyenBay,MaChuyenBayCanTim) == 0 )
		{
			return search;
		}
	}
	return NULL;
}
//XOA DAU` CHUYEN BAY
int RemoveHead(listCB &list)
{
	if(list.Head == NULL)
		return 0;
	nodeCB *temp = list.Head;
	list.Head = list.Head->next;
	delete temp;
	list.SoLuongChuyenBay--;
	return 1;
}

//XOA CUOI CHUYEN BAY
int RemoveEnding(listCB &list)
{
	if( list.Head == NULL)
		return 0;
	nodeCB *temp = NULL;
	for( nodeCB *search = list.Head ; search != NULL;search = search->next)
	{
		if( search == list.Tail)
		{
			temp->next = NULL;
			list.Tail = temp;
			delete search;
			--list.SoLuongChuyenBay;
			return 1;
		}
		temp = search;
	}
}

//GIAI PHONG BO NHO
bool CleanUpFlightList(listCB &list)
{
	if( list.Head == NULL)
		return false;
	nodeCB *temp;
	while(list.Head != NULL)
	{
		temp = list.Head;
		list.Head = list.Head->next;
		delete temp;
	}
	return true;
}

//-------------------------CHUC NANG VE -------------------------
int InsertVe(ChuyenBay &cb,int vitri,char cmnd[16]){
	if (strcmp(cb.DsVe[vitri].cmnd,"\0"))
		return 0;
	else
	{
		strcpy(cb.DsVe[vitri].cmnd,cmnd);
		cb.TongSoDaBan++;
		return 1;
	}
}

int XacNhanDatVe(int i)
{
	int x = 65, y = 39;
	int xXacNhan=45 ,yXacNhan=9;
	gotoxy(xXacNhan, yXacNhan);
	SetColor(ColorYELLOW);
	SetBGColor(ColorGRAY);
					cout << "                                ";
	gotoxy(xXacNhan, yXacNhan+1); cout << "                                ";
	gotoxy(xXacNhan, yXacNhan+2); cout << "     XAC NHAN DAT VE THU "<<i<<"      ";
	gotoxy(xXacNhan, yXacNhan+3); cout << "                                ";
	gotoxy(xXacNhan, yXacNhan+4); cout << "     YES                NO      ";
	gotoxy(xXacNhan, yXacNhan+5); cout << "                                ";
	int keyhit;
	do{
		gotoxy(xXacNhan=45, yXacNhan+4);
		SetColor(ColorBLUE);
		switch(x)
		{
		case 65 : gotoxy(xXacNhan+5, yXacNhan+4); cout << "YES"; break;
		case 84 : gotoxy(xXacNhan+24, yXacNhan+4); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(65, 19);
			SetColor(ColorYELLOW);
			switch(x)
			{
			case 65 :  gotoxy(xXacNhan+5, yXacNhan+4); cout << "YES"; break;
			case 84 :  gotoxy(xXacNhan+24, yXacNhan+4); cout << "NO"; break;
			}
			x -= 19;
			if(x != 65)
			{
				x = 84;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(65, 19);
			SetColor(ColorYELLOW);
			switch(x)
			{
			case 65 :  gotoxy(xXacNhan+5, yXacNhan+4); cout << "YES"; break;
			case 84 :  gotoxy(xXacNhan+24, yXacNhan+4); cout << "NO"; break;
			}
			x += 19;
			if(x != 84)
			{
				x = 65;
			}
		}
		else if(x == 65 && keyhit == Enter)
		{	
			SetBGColor(ColorBLACK);
			return 1;//YES
		}
		else if(x == 84 && keyhit == Enter)
		{	
			SetBGColor(ColorBLACK);
			system("cls");
			return 0; //NO
		}
	}while(true);
}

int Dem(listCB lcb, char soHieu[]) //
{
	int dem = 0;
	nodeCB *pNode = lcb.Head;
	while (pNode != NULL)
	{
		if (strcmp(pNode->CB.soHieuMB, soHieu) == 0)
			if (pNode->CB.TrangThai == 3)
				dem++;
		pNode = pNode->next;
	}
	return dem;
}



//--------------------------Hanh khach----------------------------------------------------------------------------------------------------
struct hanhKhach{
    char cmnd[16];// day la key chinh
	char ho[20];
	char ten[10];
	char phai[10];// 1 la nam , 0 la nu
	bool Booked;// kiem tra xem da mua ve chua
		
};
typedef struct hanhKhach HanhKhach;

struct Node_HK{
	HanhKhach HK;
	Node_HK *pLeft;
	Node_HK *pRight;
};



//typedef Node_HK *TREE_HK;
typedef Node_HK *NODPTR;

NODPTR tree = NULL;


//CHUC NANG HANH KHACH
void NhapHanhKhach(NODPTR &tree);

int XacNhanTaoHanhKhach()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON TAO HANH KHACH ?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == Enter)
		{
			gotoxy(boxx + 22, 29);
			Sleep(1000);
			SetBGColor(ColorBLACK);
			system("cls");
			return 1;
		}
		else if(x == 64 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
			system("cls");
			return 0;
		}
	}while(true);
}


void InitTreeHK(NODPTR &tree_hk)
{
	tree_hk = NULL;
}

bool Empty_HK(NODPTR tree_hk)
{
	return tree_hk == NULL;
}
//search
Node_HK *SearchHK(NODPTR tree_hk, char cmnd[])
{
	if (tree_hk != NULL)
	{
		Node_HK *pNode = tree_hk;
		while (pNode != NULL)
		{
			if (strcmp(pNode->HK.cmnd, cmnd) == 0)
				return pNode;
			else if (strcmp(pNode->HK.cmnd, cmnd) > 0)
				pNode = pNode->pLeft;
			else if (strcmp(pNode->HK.cmnd, cmnd) < 0)
				pNode = pNode->pRight;
		}
	}
	return NULL;
}
//CHUC NANG LIEN QUAN CHUYEN BAY
int CheckHKtrongCB(listCB list,ListMayBay lmb,char MaCB[],char cmnd[]);
int SearchVeHK(listCB list,ListMayBay lmb,char MaCB[],char cmnd[]);
int CheckDSVe(listCB list,ListMayBay lmb,char MaCB[]);
void Danh_Sach_HK_Trong_CB(listCB &list, ListMayBay lmb);
void DanhSachVeTrongCB(ListMayBay lmb,listCB list);
void Danh_Sach_Thong_Ke_So_Luot_Bay(listCB lcb, ListMayBay lmb);	
//

void InsertHKToTree(NODPTR &tree_hk, HanhKhach hk)
{
	if (tree_hk == NULL)
	{
		Node_HK *pNode = new Node_HK;
		pNode->HK = hk;
		pNode->pLeft = pNode->pRight = NULL;
		tree_hk = pNode;
	}
	else
	{
		if (atoi(tree_hk->HK.cmnd) > atoi(hk.cmnd))
			InsertHKToTree(tree_hk->pLeft, hk);
		else if (atoi(tree_hk->HK.cmnd) < atoi(hk.cmnd))
			InsertHKToTree(tree_hk->pRight, hk);
	}
}


//------------------------------------------------Constraint------------------------------------------------------------------------------------
string nhapChuoi(int x, int y){
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case Enter:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"                      ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 20)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                     ";
					gotoxy(x,y); cout<<s;
				}
				
				break;
			}
		}
	}
}

string nhapChuoi2(int x, int y){ // DUNG DE SUA CHUYEN BAY
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case Down:
				{
					return "next";
					break;
				}
			case Enter:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"                      ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 20)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                      ";
					gotoxy(x,y); cout<<s;
				}
				
				break;
			}
		}
	}

}


string nhapSo(int x, int y){
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case Enter:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"                    ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 4)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"                    ";
					gotoxy(x,y); cout<<s;
				}
				break;
			}
		}
	}
}

string nhapSo2(int x, int y){
	string s = "";
	
	while(true){
		char key = getch();
		switch(int(key)){
			case ESC:{
				return "exit";
				break;
			}
			case Down:
				{
					return "next";
					break;
			}
			case Enter:{
				return s;
				break;
			}
			case BACKSPACE:{
				if(s.length() > 0) s = s.substr(0,s.length()-1);
				else {
					s = "";
				}
				gotoxy(x,y); cout<<"  ";
				gotoxy(x,y); cout<<s;
				break;
			}
			default:{
				if (s.length() < 4)
				{
					s+= char(key);
					gotoxy(x,y); cout<<"  ";
					gotoxy(x,y); cout<<s;
				}
				break;
			}
		}
	}
}



bool check_number(string str) {
   for (int i = 0; i < str.length(); i++)
  // if(str[i]!=((int)str[i]) && isdigit(str[i]) == false )
   if (isdigit(str[i]) == false)
      return false;
	  return true;
     
      
}

int check_Chuoi_Char(char ma[])
{
	for(int i = 0; i < strlen(ma); i++){
		if (!isdigit(ma[i]))
			return -1;
	}
	return 1;
} 
void XoaKiTu(char s[], int vitrixoa)
{
	int n = strlen(s);
	for (int i = vitrixoa + 1; i < n; i++)
		s[i-1] = s[i];
	s[n-1] = '\0';
}
char *fix_Ma(char *ma)
{
	if( strcmp(ma, "\0") == 0)
		return ma;
	int dai = strlen(ma);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (ma[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (ma[0] == ' ')
				XoaKiTu(ma, 0);
			else if (ma[strlen(ma)-1] == ' ')
				XoaKiTu(ma, strlen(ma)-1);
			else
				break;
		}
		return ma;
	}
		
	while (true)
	{
		if (ma[0] == ' ')
			XoaKiTu(ma, 0);
		else if (ma[strlen(ma)-1] == ' ')
			XoaKiTu(ma, strlen(ma)-1);
		else
			break;
	}
	// Xoa khoang trang o giua
	for (int i = 0; i < strlen(ma) - 1; i++)
	{
		if ((ma[i] == ' ' && ma[i+1] == ' ') || (ma[i] == ' ' && ma[i+1] != ' '))
		{
			XoaKiTu(ma, i);
			i--;
		}
	}
	if (strcmp(ma, "") != 0)
	{
		// Chuyen chu thuong thanh chu hoa
		for (int i = 0; i < strlen(ma); i++)
		{
			if (ma[i] >= 'a' && ma[i] <= 'z')
				ma[i] -= 32;
		}
	}
	return ma;
}

string* splitToTwoString(const string str, char splitchar){
	int pos = 0;
	string* arr = new string[2];
	arr[0] = "";
	arr[1] = "";
	for(pos; pos < str.length();pos ++){
		if(str.at(pos) == splitchar){
			arr[0] = str.substr(0,pos); // 12-
			arr[1] = str.substr(pos+1, str.length()-pos);
		}
	}
	return arr;
}

char *tach_Ten(char str[])
{
	char *ten = new char[100];
	
	for (int i = strlen(str)-1; i >= 0; i--)
		if (str[i] == ' ')
		{
			int k = 0;
			for (int j = i + 1; j < strlen(str); j++)
			{
				ten[k++] = str[j];
			}
			ten[k]='\0';
			break;
		}
	return ten;
}

char *tach_ho_dem(char str[])
{
	char *hodem = new char[100];

	for (int i = strlen(str)-1; i >= 0; i--)
		if (str[i] == ' ')
		{
			int k = 0;
			for (int j = 0; j < i; j++)
			{
				hodem[k++] = str[j];
			}
			hodem[k]='\0';
			break;
		}
	return hodem;
}
char *fix_HoTen(char *hoten)
{
	if( strcmp(hoten, "\0") == 0)
		return hoten;
		
	int dai = strlen(hoten);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (hoten[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (hoten[0] == ' ')
				XoaKiTu(hoten, 0);
			else if (hoten[strlen(hoten)-1] == ' ')
				XoaKiTu(hoten, strlen(hoten)-1);
			else
				break;
		}
		return hoten;
	}
	// Xoa khoang trang dau va cuoi
	while (true)
	{
		if (hoten[0] == ' ')
			XoaKiTu(hoten, 0);
		else if (hoten[strlen(hoten)-1] == ' ')
			XoaKiTu(hoten, strlen(hoten)-1);
		else
			break;
	}
	// Xoa khoang tang o giua
	for (int i = 0; i < strlen(hoten) - 1; i++)
	{
		if (hoten[i] == ' ' && hoten[i+1] == ' ')
		{
			XoaKiTu(hoten, i);
			i--;
		}
	}
	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(hoten); i++)
		if(hoten[i] >= 'A' && hoten[i] <= 'Z') hoten[i] += 32;
	
	hoten[0] = hoten[0] - 32; // In hoa Ki tu dau tien
	
	for(int i = 1;i < strlen(hoten); i++) // In hoa chu cai dau tien sau moi khoang trang
	{
		if(hoten[i] == ' ')
		{
			if(hoten[i+1] >= 'a' && hoten[i+1] <= 'z')
			{
				hoten[i+1] -= 32;
				i = i+1;
			}
		}
	}
	return hoten;
}
char *fix_Ten(char *ma)
{
	if( strcmp(ma, "\0") == 0)
		return ma;
	int dai = strlen(ma);
	int dem = 0;
	for(int i = 0; i < dai; i++)
	{
		if (ma[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (ma[0] == ' ')
				XoaKiTu(ma, 0);
			else if (ma[strlen(ma)-1] == ' ')
				XoaKiTu(ma, strlen(ma)-1);
			else
				break;
		}
		return ma;
	}
		
	while (true)
	{
		if (ma[0] == ' ')
			XoaKiTu(ma, 0);
		else if (ma[strlen(ma)-1] == ' ')
			XoaKiTu(ma, strlen(ma)-1);
		else
			break;
	}
	// Xoa khoang tang o giua
	for (int i = 0; i < strlen(ma) - 1; i++)
	{
		if ((ma[i] == ' ' && ma[i+1] == ' ') || (ma[i] == ' ' && ma[i+1] != ' '))
		{
			XoaKiTu(ma, i);
			i--;
		}
	}

	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(ma); i++)
		if(ma[i] >= 'A' && ma[i] <= 'Z') ma[i] += 32;
	
	ma[0] = ma[0] - 32; // In hoa Ki tu dau tien
	return ma;
}

char *fix_GioiTinh(char *phai)
{
	if (strcmp(phai, "\0") == 0)
		return phai;
		
	int dai = strlen(phai);
	int dem = 0;
	for (int i = 0; i < dai; i++)
	{
		if (phai[i] == ' ')
			dem++;
	}
	if (dem == dai)
	{
		while (true)
		{
			if (phai[0] == ' ')
				XoaKiTu(phai, 0);
			else if (phai[strlen(phai)-1] == ' ')
				XoaKiTu(phai, strlen(phai)-1);
			else
				break;
		}
		return phai;
	}
	// Xoa khoang trang dau va cuoi
	while (true)
	{
		if (phai[0] == ' ')
			XoaKiTu(phai, 0);
		else if (phai[strlen(phai)-1] == ' ')
			XoaKiTu(phai, strlen(phai)-1);
		else
			break;
	}
	
	// Chuyen Hoa thanh thuong
	for(int i = 0; i < strlen(phai); i++)
		if(phai[i] >= 'A' && phai[i] <= 'Z') phai[i] += 32;
	return phai;
}

nodeCB *Search_MaMBinCB(listCB list, char maMB[]){
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return NULL;
	}
		
	else
	{
	
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.soHieuMB, maMB) == 0){
			
				return temp;
			}
				
		}
	}
	return NULL;
}
int Check_MaMBinCB(listCB list, char maMB[])
{
	if(Search_MaMBinCB(list,maMB)!=NULL){
		return 1;
	}
	return -1;
}


nodeCB *Search_MaCB(listCB list, char macb[]){
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return NULL;
	}
		
	else
	{
	
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.MaChuyenBay, macb) == 0){
			
				return temp;
			}
				
		}
	}
	return NULL;
}


int Check_MaCB(listCB list, char macb[])
{
	if(Search_MaCB(list,macb)!=NULL){
		return 1;
	}
	return -1;
}




int Check_NoiDen(listCB list, char noiden[])
{

	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return 0;
	}
		
	else
	{
		for (; temp != NULL; temp=temp->next)
		{
			if (strcmp(temp->CB.SanBayDen, noiden) == 0){
			
				return 1;
			}
				
		}
	}
	return 0;
}
 
int CheckThoiGianNoiDen(ChuyenBay cb,ThoiGian tg,char noiden[])
{
			if (cb.ThoiGianDi.ngay == tg.ngay )
			{
				if(cb.ThoiGianDi.thang == tg.thang)
				{
					if(cb.ThoiGianDi.nam == tg.nam)
					{
						if(strcmp(cb.SanBayDen,noiden)==0)
						{
							return 1;
						}
					}
				}
			}
	return 0;
}


int CountCB_ThoiGianNoiDen(listCB list, ThoiGian tg, char noiden[])
{
	int dem = 0;
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return 0;
	}
		
	else
	{
		for (; temp != NULL; temp=temp->next)
		{
			if (temp->CB.ThoiGianDi.ngay == tg.ngay )
			{
				if(temp->CB.ThoiGianDi.thang == tg.thang)
				{
					if(temp->CB.ThoiGianDi.nam == tg.nam)
					{
						if(strcmp(temp->CB.SanBayDen,noiden)==0)
						{
							dem++;
						}
					}
				}
			}
				
		}
		return dem;
	}
	return 0;
}

bool CheckInvalidFlight(listCB list, ChuyenBay cb)
{
	int dem = 0;
	nodeCB *temp = list.Head;
	if (temp == NULL){
	
		return false;
	}
		
	else
	{
		
		for (; temp != NULL; temp=temp->next)
		{
			
			
			if (temp->CB.ThoiGianDi.ngay == cb.ThoiGianDi.ngay)
			{
				if(temp->CB.ThoiGianDi.thang == cb.ThoiGianDi.thang)
				{
					if(temp->CB.ThoiGianDi.nam == cb.ThoiGianDi.nam)
					{
							if(strcmp(temp->CB.soHieuMB,cb.soHieuMB)==0)
							{
								if(strcmp(temp->CB.MaChuyenBay,cb.MaChuyenBay)!=0)
								{
									if(temp->CB.TrangThai==0){
									return false;}
									
								return true;
								}
							}
							
							
					}
				}
			}
				
		}
		return false;
	}
}


bool Check_Date(int nam, int thang, int ngay)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if ( (nam % 4 == 0 && nam % 100 != 0) || nam % 400 == 0)
	{
		Thang[1] = 29;
	}
	if (thang >= 1 && thang <= 12)
	{
		if (ngay >= 1 && ngay <= Thang[thang - 1])
		{
			return true;	
		}
	}
	return false;
}

bool Check_ThoiGian_ChuyenBay(ThoiGian tg)
{
	int Thang[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (!Check_Date(tg.nam, tg.thang, tg.ngay)) return false;

	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	ThoiGian dtNow;
	dtNow.nam = 1900 + ltm->tm_year;
	dtNow.thang = 1 + ltm->tm_mon;
	dtNow.ngay = ltm->tm_mday;
	dtNow.gio = ltm->tm_hour;
	dtNow.phut = ltm->tm_min;

	if (tg.nam < dtNow.nam) return false;
	if ((tg.nam == dtNow.nam) && (tg.thang < dtNow.thang))  return false;
	if ((tg.nam % 400 == 0) || (tg.nam % 4 == 0 && tg.nam % 100 != 0))
		Thang[1] = 29;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay < dtNow.ngay)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio < dtNow.gio)return false;
	if (tg.nam == dtNow.nam && tg.thang == dtNow.thang && tg.ngay == dtNow.ngay && tg.gio == dtNow.gio && tg.phut <= dtNow.phut)return false;
	return true;
}

//------------------------------------------DOC GHI FILE------------------------------------------
int XacNhanSaveFile()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON SAVE FILE KHONG?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == Enter)
		{
			gotoxy(boxx + 22, 29);
			cout << "LUU FILE THANH CONG";
			Sleep(1000);
			SetBGColor(ColorBLACK);
			system("cls");
			return 1;
		}
		else if(x == 64 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
			system("cls");
			return 0;
		}
	}while(true);
}

int XacNhanXoa()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "      BAN CO MUON XOA KHONG  ?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
//			system("cls");
			return 1;
		}
		else if(x == 64 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
//			system("cls");
			return 0;
		}
	}while(true);
}

int XacNhanHuyChuyen()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON HUY CHUYEN KHONG ?";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
//			system("cls");
			return 1;
		}
		else if(x == 64 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
//			system("cls");
			return 0;
		}
	}while(true);
}



void LuuFileChuyenBay(listCB list, listMayBay lmb)
{
	ofstream fileout;
	fileout.open("chuyenbay.txt", ios::out);
	nodeCB *Temp = list.Head;
	for ( ; Temp != NULL; Temp=Temp->next)	{
		ChuyenBay cb;
		cb = Temp->CB;
		fileout << cb.soHieuMB << endl;
		fileout << cb.MaChuyenBay << "," 
				<< cb.ThoiGianDi.ngay << "/" 
				<< cb.ThoiGianDi.thang << "/" 
				<< cb.ThoiGianDi.nam << ","
				<< cb.ThoiGianDi.gio << ":"
				<< cb.ThoiGianDi.phut << endl;
		fileout << cb.SanBayDen <<endl;
		fileout << cb.TrangThai <<endl;

		int socho=Get_socho(lmb,cb.soHieuMB);
		for(int vitri = 1; vitri <= socho; vitri++){
			if(strcmp(cb.DsVe[vitri].cmnd,"\0"))
			{
				fileout << vitri << "-" << cb.DsVe[vitri].cmnd << endl;
			}
		}
		fileout << endl << endl;
	}

	fileout.close();
}

void DocFileChuyenBay(listCB &list, listMayBay lmb)
{
	ifstream filein;
	filein.open("chuyenbay.txt", ios::in);
	string tmp; 
	do
	{
		ChuyenBay cb;
		getline(filein, tmp);
		if (tmp != ""){
			strcpy(cb.soHieuMB, tmp.c_str());
			
			getline(filein, tmp, ',');
			strcpy(cb.MaChuyenBay, tmp.c_str());
			
//			cout<<cb.maCB<<endl;
			getline(filein, tmp, '/');
			cb.ThoiGianDi.ngay = atoi(tmp.c_str());
			
			getline(filein, tmp, '/');
			cb.ThoiGianDi.thang = atoi(tmp.c_str());
			
			getline(filein, tmp, ',');
			cb.ThoiGianDi.nam = atoi(tmp.c_str());
			
			getline(filein, tmp, ':');
			cb.ThoiGianDi.gio = atoi(tmp.c_str());
			
			getline(filein, tmp);
			cb.ThoiGianDi.phut = atoi(tmp.c_str());
			
			
			getline(filein, tmp);
			strcpy(cb.SanBayDen, tmp.c_str());
			getline(filein, tmp);
			cb.TrangThai = atoi(tmp.c_str());
			if (Check_ThoiGian_ChuyenBay(cb.ThoiGianDi) == false)
				cb.TrangThai = 3;
			int socho = Get_socho(lmb,cb.soHieuMB);
			initListVe(cb,socho);
			string tmp1 = "";
			getline(filein, tmp1);
			
			while(tmp1 != "")
			{
				string *arrVe = splitToTwoString(tmp1, '-');
				string ghe = arrVe[0];
				char cmnd[16];
				strcpy(cmnd , arrVe[1].c_str());
				InsertVe(cb, atoi(ghe.c_str()), cmnd);
				getline(filein, tmp1);
			}
			tmp = "";
			AddEndingList(list, cb);
			
		}
		
	}while (!filein.eof());
	filein.close();
}

void LuuFileHKKoDeQuy(NODPTR tree_hk)
{
	ofstream fileout;
	fileout.open("hanhkhach.txt", ios::out);
	if (fileout.fail())
	{
		cout<<"Loi mo file hanh khach";
		return;
	}
	const int STACKSIZE = 10000;
	NODPTR Stack[STACKSIZE];
	NODPTR p = tree_hk;
	int sp = -1; //Khai bao Stack rong
	do
	{
		while(p!=NULL)
		{
			Stack[++sp] = p;
			p = p->pLeft;
		}
		if (sp != -1)
		{
			p = Stack[sp--];
			fileout<<p->HK.cmnd<<","<<p->HK.ho<<" "<<p->HK.ten<<","<<p->HK.phai<<endl;
			p = p->pRight;
		}
		else break;
	}while(1);
}
void DocFileHanhKhach(NODPTR &tree_hk)
{
	ifstream filein;
	filein.open("hanhkhach.txt", ios::in);
	HanhKhach hk;
	string tmp; // lay ky tu xuong dong 
	do{
		string cmnd, hoten;
	    fflush(stdin);
		getline(filein, cmnd, ',');
		if(cmnd != ""){
			strcpy(hk.cmnd, cmnd.c_str());
			
			getline(filein, hoten, ',');
			char ho[100], ten[100], hotenc[200];
			strcpy(hotenc, hoten.c_str());
			
			strcpy(hk.ho, tach_ho_dem(hotenc));
		
			strcpy(hk.ten, tach_Ten(hotenc));
		
			filein>>hk.phai;
		
			getline(filein, tmp);
			InsertHKToTree(tree_hk, hk);
		}
	}while(!filein.eof());
	filein.close();
}




//---------------------------------------------------------------Giao Dien--------------------------------------------
void Color(int x) {
    HANDLE color;
    color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(color, x);
}
void CursorStatus(unsigned size, WINBOOL stt) {
    CONSOLE_CURSOR_INFO crs_inf = {size, stt};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &crs_inf);
}
void delLine(int x, int y, int leng) {
    gotoxy(x, y);
    for (int i = 1; i <= leng; i++) {

        cout << " ";
    }
    gotoxy(x, y);

}

void TextSlide(string Str, int x1, int y1, int color)
 {
    Color(color);
    for (int i = 0; i < 4; i++) {
        gotoxy(x1, y1);
        cout << Str;
    }
}

void DrawFrame(int x, int y, int dai, int rong){
	Color(11);
	//bien trai
    gotoxy(x, y);
    printf("%c", 201);
    for (int i = y+1; i <= rong; i++) {
        gotoxy(x, i);
        printf("%c", 186); 
    }
    //bien duoi
    gotoxy(x, y+rong);
    printf("%c", 200);

    for (int i = x+1; i < x+dai; i++) {
        gotoxy(i, y+rong);
        printf("%c", 205); 
    }
    //bien phai
    gotoxy(x+dai, y+rong);
    printf("%c", 188);
    for (int i = y+rong-1; i > y; i--) {
        gotoxy(x+dai, i);
        printf("%c", 186);
    }
    //bien tren
    gotoxy(x+dai,y);
    printf("%c", 187);
    for (int i = x+dai-1; i > x ; i--) {
        gotoxy(i, y);
        printf("%c", 205);

    }
}
// VE KHUNG

void Khung_SuaMayBay()
{
	SetColor(15);
	
	gotoxy(boxx + 30, boxy - 1); cout<<"THONG TIN";
	gotoxy(boxx + 65, boxy - 1); cout<<"DANG SUA";
	
	
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 30; i++) cout << char(205);
	cout << char(187);
	gotoxy(boxx + 58,boxy); cout<<char(203); //  ||``
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 1); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< " Nhap vao so hieu may bay:  ";  // boxx + 27      boxx + 61
	gotoxy((boxx + boxs + 75)/2, boxy + 2); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 30, boxy + 3); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 3); cout << char(186);
	
	gotoxy(boxx, boxy + 4); cout << char(186)<< "    Nhap vao loai may bay:  ";
	gotoxy((boxx + boxs + 75)/2, boxy + 4); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 4); cout << char(186);
	
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 5); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 5); cout << char(186);
	
	gotoxy(boxx, boxy + 6); cout << char(186)<< "          Nhap vao so cho:  ";
	gotoxy((boxx + boxs + 75)/2, boxy + 6); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 6); cout << char(186);
	
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 7); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 7); cout << char(186);
	
	gotoxy(boxx, boxy + 8); cout << char(186);
	gotoxy((boxx + boxs + 75)/2, boxy + 8); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 8); cout << char(186);
	
	gotoxy(boxx, boxy + 9); cout << char(186);
	gotoxy(boxx + boxs + 30, boxy + 9); cout << char(186);
	
	gotoxy((boxx + boxs + 75)/2, boxy + 9); cout << char(186);
	
	gotoxy(boxx, boxy + 10); cout << char(200);
	for(int i = 1; i < boxs + 30; i++) cout << char(205);
	cout << char(188); 
	gotoxy(boxx + 58,boxy + 10); cout<<char(202); //  ||__
}

void Khung_NhapHanhKhach()
{
	SetColor(15);
	gotoxy(boxx, boxy); cout << char(201);
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx, boxy + 1); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 1); cout << char(186);
	
	gotoxy(boxx, boxy + 2); cout << char(186)<< "            Nhap CMND: ";
	gotoxy(boxx + boxs + 1, boxy + 2); cout << char(186);
	
	gotoxy(boxx, boxy + 3); cout << char(186) ;
	gotoxy(boxx + boxs + 1, boxy + 3); cout << char(186);
	
	gotoxy(boxx, boxy + 4); cout << char(186)<< "              Nhap Ho: ";
	gotoxy(boxx + boxs + 1, boxy + 4); cout << char(186);
	
	gotoxy(boxx, boxy + 5); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 5); cout << char(186);
	
	gotoxy(boxx, boxy + 6); cout << char(186)<< "             Nhap Ten: ";
	gotoxy(boxx + boxs + 1, boxy + 6); cout << char(186);
	
	gotoxy(boxx, boxy + 7); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 7); cout << char(186);
	
	gotoxy(boxx, boxy + 8); cout << char(186);
	gotoxy(boxx, boxy + 8); cout << char(186)<< "   Nhap Phai (Nam/Nu): ";
	gotoxy(boxx + boxs + 1, boxy + 8); cout << char(186);
	
	gotoxy(boxx, boxy + 9); cout << char(186);
	gotoxy(boxx + boxs + 1, boxy + 9); cout << char(186);

	gotoxy(boxx, boxy + 10); cout << char(200);	
	for(int i = 1; i < boxs + 1; i++) cout << char(205);
	cout << char(188); 
}



void Khung_NhapMayBay()
{
	SetColor(11);
	gotoxy(boxx+70, boxy-9); cout << char(201);
	for(int i = 30; i < boxs ; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(boxx+70, boxy-8); cout << char(186);
	gotoxy(boxx+69+boxs -28 , boxy-8); cout << char(186);
	
	gotoxy(boxx+70, boxy-7); cout << char(186)<< " SO HIEU: "; // boxx+27       boxx + 61
	gotoxy(boxx+69+boxs -28, boxy-7); cout << char(186);
	
	gotoxy(boxx+70, boxy-6); cout << char(186) ;
	gotoxy(boxx+69+boxs-28, boxy-6); cout << char(186);
	gotoxy(boxx+70, boxy-5); cout << char(186)<< " LOAI MB: ";
	gotoxy(boxx+69+boxs -28, boxy-5); cout << char(186);
	gotoxy(boxx+70, boxy-4); cout << char(186);
	gotoxy(boxx+69+boxs -28, boxy -4); cout << char(186);
	gotoxy(boxx+70, boxy-3); cout << char(186)<< "  SO CHO: ";
	gotoxy(boxx+69+boxs -28, boxy -3); cout << char(186);
	gotoxy(boxx+70, boxy -2); cout << char(186);
	gotoxy(boxx+69+boxs -28, boxy -2); cout << char(186);
	gotoxy(boxx+70, boxy -1); cout << char(186);
    gotoxy(boxx+69+boxs -28, boxy -1); cout << char(186);
    gotoxy(boxx+70, boxy ); cout << char(200);
	for(int i = 30; i < boxs ; i++) cout << char(205);
	cout << char(188); 
}

void In1Ve(int x, int y, int  text, int Trangthai)
{
	SetColor(ColorYELLOW);// yellow VE CHUA DAT
	if (Trangthai == 1) {
		SetColor(ColorRED); // RED VE DA DAT
	}
//	SetBGColor(0);// black
	/*Ve duong ve ben tren*/
	gotoxy(x, y - 1);
	cout << char(219) << char(219) << char(219) << char(219)<<char(219);
	/*So thu tu cua cai ve do*/
	gotoxy(x, y);
	cout << char(219) << setw(3) << setfill('0')<<text<<char(219);
	/*ve duong ke ben duoi cua cai ve*/
	gotoxy(x,y+1);
	
	cout << char(219) << char(219) << char(219) << char(219)<<char(219);

}	

void InVeBiHuy(int sove)
{
	int x=xVe,y=yVe;
	int hang = sove/14;
	int cot = sove - hang*14;
	x= xVe + (cot-1)*8;
	y = yVe + hang*5;
	SetColor(ColorYELLOW);
	gotoxy(x, y - 1);
	Sleep(500);
	cout << char(219) << char(219) << char(219) << char(219)<<char(219);
	/*So thu tu cua cai ve do*/
	gotoxy(x, y);Sleep(500);
	cout << char(219) << setw(3) << setfill('0')<<sove<<char(219);
	/*ve duong ke ben duoi cua cai ve*/
	gotoxy(x,y+1);Sleep(500);
	cout << char(219) << char(219) << char(219) << char(219)<<char(219);
}


void XuatDSVe(ChuyenBay cb,int max){
	int x=xVe,y=yVe,dem;
	int Size;
	SetColor(ColorCYAN);
	if(max <= 28)
	{
		Size = 1;
	}
	else if(max <= 42)
	{
		Size = 2;
	}
	else if(max <= 70)
	{
		Size = 3;
	}
	else if(max <= 98)
	{
		Size = 4;
	}
	else
	{
		Size = 5;
	}
		for (int i = yVe;i<= yVe+8*Size;i++)
		{	
			gotoxy(xVe+8*14+1,i);cout << char(186);
			gotoxy(xVe-4,i);cout << char(186);
		}
		for (int i = xVe;i<= xVe+8*14+3;i++)
		{
			cout << char(205);
		}
		gotoxy(xVe-4,yVe+8*Size);cout<<char(200); // |_	
		gotoxy(xVe+8*14+1,yVe+8*Size); cout<< char(188);// _|
		
		
	
	for(int dem= 1;dem <= max; dem++)
	{
		
		if(strcmp(cb.DsVe[dem].cmnd,"\0")==0){
			In1Ve(x,y,dem,0);	
		}
		else{
			In1Ve(x,y,dem,1);	
		}
		
		x =x+8;
		if(dem%14==0)
		{
			x= xVe;
			y = y+5;
		}
	}
}

void Khung_DatVe() {
	resizeConsole(1000,600);
	system("cls");
	
	Color(ColorCYAN);
	gotoxy(15,3);  cout << "XIN CHAO                                 - MOI BAN NHAP VI TRI MUON DAT VE";
	gotoxy(18, 8);
	cout << "                                                    ";
	
//	gotoxy(74,3);  cout << "THONG TIN HANH KHACH";
	SetColor(ColorCYAN);
	gotoxy(44,11);cout<<"        DANH SACH VE";
	gotoxy(17,1);cout<<"DAT VE CHUYEN BAY:                    BAY DEN:                 Vao Ngay:             ";
	SetColor(ColorYELLOW);
	gotoxy(16, 6);cout << "MAY BAY      : ";
	gotoxy(63, 6);cout << "SO CHO       : ";
	SetColor(ColorYELLOW);
	gotoxy(16, 8); cout <<"NHAP SO VE   : ";
//	gotoxy(70, 6); cout << "CMND  : ";
//	gotoxy(70, 8); cout << "Ho    : ";
//	gotoxy(70, 10); cout <<"Ten   : ";
//	gotoxy(70, 12); cout <<"Phai  : ";
//	SetColor(6);
	
	SetColor(ColorCYAN);
	for (int i = 1; i <= 118; i++)
	{
		gotoxy(i, 0);  cout << char(205);
		gotoxy(i, 2);  cout << char(205);
		gotoxy(i, 10);  cout << char(205);
//		gotoxy(67,2); cout << char (203);
//		gotoxy(i, 33); cout << char(205); THANH NGANG DUOI CUNG
				
	}
//	gotoxy(67,3); cout << char (203);
//	for (int i = 3; i < 15; i++)
//	{
//		gotoxy(67, i); cout << char(186);
////		gotoxy(67,3); cout<< char(204);
//
	
//	} 	gotoxy(67, 14);cout<< char(202);
//	
	for (int i = 1; i <= 118; i++)
	{

		gotoxy(i, 4);  cout << char(205);
		
	}
//		gotoxy(67,4); cout<< char(206);

	for (int i = 0; i <= 20; i++)
	{
		gotoxy(1,0); cout<< char(201);
		gotoxy(1,2); cout<<char(204);
//		gotoxy(1,33); cout<<char(200);// |_
		gotoxy(1, i); cout << char(186);
		gotoxy(118,0); cout<<char(187);
		gotoxy(118,2); cout<<char(185);
		gotoxy(118,4); cout<<char(185);
		gotoxy(118, i); cout << char(186);
	}
	gotoxy(1,10); cout<<char(204);
	gotoxy(1,4); cout<<char(204);
//	gotoxy(118,33); cout<< char(188);// _|
	gotoxy(118,10); cout<< char(185);
}


void Khung_XemVe()
{
	resizeConsole(1000,600);
	system("cls");
	
	Color(ColorCYAN);
	gotoxy(15,3);  cout << "                               DANH SACH CAC VE CON TRONG                 ";
	gotoxy(18, 8);
	cout << "                                                    ";
	
//	gotoxy(74,3);  cout << "THONG TIN HANH KHACH";
	SetColor(ColorCYAN);
	gotoxy(44,11);cout<<"        DANH SACH VE";
	gotoxy(17,1);cout<<"       CHUYEN BAY:                    BAY DEN:                 Vao Ngay:             ";
	SetColor(ColorYELLOW);
	gotoxy(16, 7);cout << "VE CON TRONG CO MAU VANG "<<char(219);
	SetColor(ColorRED);
	gotoxy(78, 7);cout << "VE DA CO NGUOI DAT MAU DO "<<char(219);
//	gotoxy(70, 6); cout << "CMND  : ";
//	gotoxy(70, 8); cout << "Ho    : ";
//	gotoxy(70, 10); cout <<"Ten   : ";
//	gotoxy(70, 12); cout <<"Phai  : ";
//	SetColor(6);
	
	SetColor(ColorCYAN);
	for (int i = 1; i <= 118; i++)
	{
		gotoxy(i, 0);  cout << char(205);
		gotoxy(i, 2);  cout << char(205);
		gotoxy(i, 10);  cout << char(205);
//		gotoxy(67,2); cout << char (203);
//		gotoxy(i, 33); cout << char(205); THANH NGANG DUOI CUNG
				
	}
//	gotoxy(67,3); cout << char (203);
//	for (int i = 3; i < 15; i++)
//	{
//		gotoxy(67, i); cout << char(186);
////		gotoxy(67,3); cout<< char(204);
//
	
//	} 	gotoxy(67, 14);cout<< char(202);
//	
	for (int i = 1; i <= 118; i++)
	{

		gotoxy(i, 4);  cout << char(205);
		
	}
//		gotoxy(67,4); cout<< char(206);

	for (int i = 0; i <= 20; i++)
	{
		gotoxy(1,0); cout<< char(201);
		gotoxy(1,2); cout<<char(204);
//		gotoxy(1,33); cout<<char(200);// |_
		gotoxy(1, i); cout << char(186);
		gotoxy(118,0); cout<<char(187);
		gotoxy(118,2); cout<<char(185);
		gotoxy(118,4); cout<<char(185);
		gotoxy(118, i); cout << char(186);
	}
	gotoxy(1,10); cout<<char(204);
	gotoxy(1,4); cout<<char(204);
//	gotoxy(118,33); cout<< char(188);// _|
	gotoxy(118,10); cout<< char(185);
}

void Khung_HuyVe() {
	system("cls");
	SetColor(11);
	gotoxy(18, 8);
	cout << "                                                    ";
	gotoxy(38, 2);cout << "HUY VE HANH KHACH CHUYEN BAY";
	gotoxy(2, 5);  cout << "Ma chuyen bay :";
	gotoxy(2, 7);  cout << "Chon ghe so   :";
	gotoxy(2, 9);  cout << "Nhap CMND Hanh Khach:";
	gotoxy(79,5);  cout << " THONG BAO ";

	SetColor(ColorRED);
	for (int i = 1; i <= 100; i++)
	{
		gotoxy(i, 1);  cout << char(205);
		gotoxy(i, 3);  cout << char(205);
		gotoxy(67,3); cout << char (203);
		gotoxy(i, 28); cout << char(205);
				
	}
	for (int i = 4; i <= 28; i++)
	{
		gotoxy(67, i); cout << char(186);
		gotoxy(67,6); cout<< char(204);
		gotoxy(67,28); cout<< char(202);
		gotoxy(100,28); cout<< char(188);

	}
	for (int i = 68; i <= 100; i++)
	{

		gotoxy(i, 6);  cout << char(205);
		
	}
	for (int i = 1; i <= 27; i++)
	{
		gotoxy(1,1); cout<< char(201);
		gotoxy(1,3); cout<<char(204);
		gotoxy(1,28); cout<<char(200);
		gotoxy(1, i); cout << char(186);
		gotoxy(100,1); cout<<char(187);
		gotoxy(100,3); cout<<char(185);
		gotoxy(100,6); cout<<char(185);
		gotoxy(100, i); cout << char(186);
	}
	
}

void Khung_DS_HK_Trong_CB()
{
//	resizeConsole(800,600);
	SetColor(ColorCYAN);
	gotoxy(27, 2);
	cout << "DANH SACH HANH KHACH CUA CHUYEN BAY CO MA: "; // 80,2
	gotoxy(25,3);
	cout << "Ngay gio thoi hanh: "; // 49,3
	gotoxy(46,3); cout<<"/";
	gotoxy(49,3); cout<<"/";
	gotoxy(58,3); cout<<":";
	gotoxy(63,3);
	cout << "Noi den:"; // 77,3
	SetColor(ColorCYAN);
	gotoxy(tabx, taby);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tabs ; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx, taby + tabw);
	cout << char(192);
	//dong cuoi
	for(int i = 1; i < tabs + 1; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs , taby + tabw);
	cout << char(217);

	// STT
	gotoxy(tabx + 8, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 8, taby + i); cout << char(179); // cot stt
	}
	
	gotoxy(tabx, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tabs ; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 8, taby + 2); cout << char(197);
	gotoxy(tabx + tabs , taby + 2); cout << char(180);
	gotoxy(tabx + 8, taby + tabw); cout << char(193);

	// SO HIEU
	gotoxy(tabx + 20, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 20, taby + i); cout << char(179);
	}
	gotoxy(tabx + 20, taby + 2); cout << char(197);
	gotoxy(tabx + 20, taby + tabw); cout << char(193);

	// LOAI
	gotoxy(tabx + 38, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 38, taby + i); cout << char(179);
	}
	gotoxy(tabx + 38, taby + 2); cout << char(197);
	gotoxy(tabx + 38, taby + tabw); cout << char(193);

	// SO CHO
	gotoxy(tabx + 70, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 70, taby + i); cout << char(179);
	}
	gotoxy(tabx + 70, taby + 2); cout << char(197);
	gotoxy(tabx + 70, taby + tabw); cout << char(193);

	SetColor(ColorCYAN);
	gotoxy(tabx + 3, taby + 1); cout << "STT";
	gotoxy(tabx + 12, taby + 1); cout << "SO VE";
	gotoxy(tabx + 26, taby + 1); cout << "CMND";
	gotoxy(tabx + 50, taby + 1); cout << "HO TEN";
	gotoxy(tabx + 75, taby + 1); cout << "PHAI";

}


void KhungNhapCMND(){
		SetColor(14);
	gotoxy(box2x, 33 - 8); cout << char(201);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(box2x, 33 - 7); cout << char(186);
	gotoxy(box2x + box2s + 1, 33 - 7); cout << char(186);
	
	gotoxy(box2x, 33 - 6); cout << char(186)<< "          Nhap CMND:                   ";
	gotoxy(box2x + box2s + 1, 33 - 6); cout << char(186);
	
	gotoxy(box2x, 33 - 5); cout << char(186) ;
	gotoxy(box2x + box2s + 1, 33 - 5); cout << char(186);
	
	gotoxy(box2x, 33 - 4); cout << char(186)<< " Nhap ma chuyen bay:                       ";
	gotoxy(box2x + box2s + 1, 33 - 4); cout << char(186);
	
	
	
	gotoxy(box2x, 33 - 3); cout << char(186);
	gotoxy(box2x + box2s + 1, 33 - 3); cout << char(186);
	gotoxy(box2x, 33 - 2); cout << char(200);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(188); 
}

void KhungNhapMaCB(int x, int y){

	gotoxy(x, y); SetBGColor(ColorDARKBLUE); SetColor(ColorDARKYELLOW);	cout << "       NHAP MA CHUYEN BAY       ";
	gotoxy(x, y + 1); SetBGColor(ColorDARKBLUE);						cout << "     ";
	gotoxy(x + 5, y + 1);  SetBGColor(ColorWHITE); 						cout << "                       ";
	gotoxy(x + 27, y + 1); SetBGColor(ColorDARKBLUE); 					cout << "     ";
	gotoxy(x, y + 2); SetBGColor(ColorDARKBLUE);						cout << "                                ";
	SetBGColor(ColorBLACK); SetColor(ColorWHITE);

}
void KhungNhap1CMND(int x, int y){

	gotoxy(x, y); SetBGColor(ColorDARKBLUE); SetColor(ColorDARKYELLOW);	cout << "            NHAP CMND           ";
	gotoxy(x, y + 1); SetBGColor(ColorDARKBLUE);						cout << "     ";
	gotoxy(x + 5, y + 1);  SetBGColor(ColorWHITE); 						cout << "                       ";
	gotoxy(x + 27, y + 1); SetBGColor(ColorDARKBLUE); 					cout << "     ";
	gotoxy(x, y + 2); SetBGColor(ColorDARKBLUE);						cout << "                                ";
	SetBGColor(ColorBLACK); SetColor(ColorWHITE);

}


void Khung_DS_Thong_Ke_So_Luot_Bay()
{
	
//	resizeConsole(800,600);
	SetColor(ColorWHITE);
	gotoxy(43, 2);
	cout << "THONG KE SO LUOT BAY CUA MAY BAY";
	SetColor(ColorCYAN);	
	gotoxy(tabx+10, taby);
	cout << char(218);

	//-------- dong dau
	for(int i = -9; i < tabs - 14 ; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
		// STT
	gotoxy(tabx + 15, taby +1); cout << "STT";
	for(int i = 1; i < tabw ; i++)
	{
		gotoxy(tabx+10, taby + i);
		cout << char(179);
	}
	gotoxy(tabx+20, taby );
	cout << char(194);
	


	//cot dau
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx+20, taby + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs + 6, taby + i);
		cout << char(179) ;
	}
	
	gotoxy(tabx+20, taby + tabw);
	cout << char(192);
	//dong cuoi
	for(int i = -9; i < tabs - 14; i++)
	{
		gotoxy(tabx + i + 20, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + 20, taby + tabw);
	cout << char(193);
	gotoxy(tabx +10, taby + tabw);
	cout << char(192);
	gotoxy(tabx + tabs + 6, taby + tabw);
	cout << char(217);
	

	// SO HIEU MAY BAY
	gotoxy(tabx + 45, taby); cout << char(194);
	gotoxy(tabx + 70, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 45, taby + i); cout << char(179); // cot stt
		gotoxy(tabx + 70, taby + i); cout << char(179); // cot stt
		
	}
	
	gotoxy(tabx + 20, taby + 2);
	cout << char(195);
	// dong hai
	for(int i = -9; i < tabs - 14 ; i++)
	{
		gotoxy(tabx + i + 20, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 10, taby + 2); cout << char(195);
	gotoxy(tabx + 20, taby + 2); cout << char(197);
	gotoxy(tabx + 45, taby + 2); cout << char(197);
	gotoxy(tabx + tabs - 13, taby + 2); cout << char(180);
	gotoxy(tabx + tabs + 6, taby + 2); cout << char(180);
	gotoxy(tabx + 45, taby + tabw); cout << char(193);
	gotoxy(tabx + 70, taby + tabw); cout << char(193);
	gotoxy(tabx + 70, taby + 2); cout << char(197);

	SetColor(ColorCYAN);
	//SO HIEU MB
	gotoxy(tabx + 26, taby + 1); cout << "SO HIEU MAY BAY";
	// LOAI MAY BAY
	gotoxy(tabx + 52, taby + 1); cout << "LOAI MAY BAY";
	// SO LUOT BAY
	gotoxy(tabx + 75, taby +1 ); cout <<"SO LUOT BAY";
    gotoxy(25,27);cout<<char(176)<<"THOAT: ESC";

}




void Khung_MayBay()
{
	
	Color(11);
	
	gotoxy(40, 2);
	cout << "DANH SACH MAY BAY";
	gotoxy(tabx, taby);
	cout << char(218);
	for(int i = 1; i < tabs - 2; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx, taby + i);
		cout << char(179);
	}

	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + tabs - 2, taby + i);
		cout << char(179);
	}
	gotoxy(tabx, taby + tabw);
	cout << char(192);
	for(int i = 1; i < tabs - 2; i++)
	{
		gotoxy(tabx + i, taby + tabw);
		cout << char(196);
	}
	gotoxy(tabx + tabs - 2, taby + tabw);
	cout << char(217);

	// STT
	gotoxy(tabx + 3, taby + 1); cout << "STT";
	gotoxy(tabx + 8, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 8, taby + i); cout << char(179);
	}
	gotoxy(tabx, taby + 2);
	cout << char(195);
	for(int i = 1; i < tabs - 2; i++)
	{
		gotoxy(tabx + i, taby + 2);
		cout << char(196);
	}
	gotoxy(tabx + 8, taby + 2); cout << char(197);
	gotoxy(tabx + tabs - 2, taby + 2); cout << char(180);
	gotoxy(tabx + 8, taby + tabw); cout << char(193);

	// SO HIEU
	gotoxy(tabx + 15, taby + 1); cout << "SO HIEU";
	gotoxy(tabx + 27, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 27, taby + i); cout << char(179);
	}
	gotoxy(tabx + 27, taby + 2); cout << char(197);
	gotoxy(tabx + 27, taby + tabw); cout << char(193);

	// LOAI
	gotoxy(tabx + 40, taby + 1); cout << "LOAI";
	gotoxy(tabx + 60, taby); cout << char(194);
	for(int i = 1; i < tabw + 1; i++)
	{
		gotoxy(tabx + 60, taby + i); cout << char(179);
	}
	gotoxy(tabx + 60, taby + 2); cout << char(197);
	gotoxy(tabx + 60, taby + tabw); cout << char(193);

	// SO cho
	gotoxy(tabx + 67, taby + 1); cout << "SO CHO";
	gotoxy(10, 26); SetColor(ColorCYAN);cout <<char(178)<< "Insert:";
	gotoxy(18,26 ); SetColor(ColorCYAN);	cout << "THEM ";
	gotoxy(10, 27); SetColor(ColorCYAN);cout <<char(178)<< "Delete:";
	gotoxy(18,27); SetColor(ColorCYAN);	cout << "XOA ";
	gotoxy(10, 28); SetColor(ColorCYAN);cout <<char(178)<< "Backspace:";
	gotoxy(22,28 ); SetColor(ColorCYAN);	cout << "SUA ";
}

void Khung_NhapChuyenBay()
{
	
	SetColor(15);
	gotoxy(box2x, box2y - 8); cout << char(201);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(box2x, box2y - 7); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 7); cout << char(186);
	
	gotoxy(box2x, box2y - 6); cout << char(186)<< " Nhap vao so hieu may bay:                ";
	gotoxy(box2x + box2s + 1, box2y - 6); cout << char(186);
	
	gotoxy(box2x, box2y - 5); cout << char(186) ;
	gotoxy(box2x + box2s + 1, box2y - 5); cout << char(186);
	
	gotoxy(box2x, box2y - 4); cout << char(186)<< "       Nhap ma chuyen bay:                       ";
	gotoxy(box2x + box2s + 1, box2y - 4); cout << char(186);
	
	gotoxy(box2x, box2y - 3); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 3); cout << char(186);
	
	gotoxy(box2x, box2y - 2); cout << char(186)<< "                     Ngay:                  ";
	gotoxy(xNgay+2, yNgay);cout<<"/";
	gotoxy(xNgay+5, yNgay);cout<<"/";
	gotoxy(box2x + box2s + 1, box2y - 2); cout << char(186);
	
	gotoxy(box2x, box2y - 1); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 1); cout << char(186);
	
	gotoxy(box2x, box2y); 	cout << char(186)<< "                      Gio:   :  ";
	gotoxy(box2x + box2s + 1, box2y); cout << char(186);
	
	gotoxy(box2x, box2y + 1); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y + 1); cout << char(186);
	
	gotoxy(box2x, box2y + 2); cout << char(186)<< "              San bay den:                ";
	gotoxy(box2x + box2s + 1, box2y + 2); cout << char(186);
	
	gotoxy(box2x, box2y + 3); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y + 3); cout << char(186);
	gotoxy(box2x, box2y + 4); cout << char(200);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(188); 
}


void Khung_NhapChuyenBayTheoNgay()
{
	
	SetColor(ColorWHITE);
	DrawFrame(box2x,box2y - 8,61,6);
	gotoxy(box2x, box2y - 7); cout<< char(186);
	gotoxy(box2x, box2y - 6); cout<< char(186) << "        Nhap San Bay Den:                ";
	gotoxy(box2x + box2s + 1, box2y - 6); cout << char(186);
	
	gotoxy(box2x, box2y - 5); cout << char(186);
	gotoxy(box2x, box2y - 4); cout << char(186) << "               Nhap Ngay:                       ";
	gotoxy(box2x + box2s + 1, box2y - 4); cout << char(186);
	gotoxy(xNgay+2, yNgay-2);cout<<"/";
	gotoxy(xNgay+5, yNgay-2);cout<<"/";
	
	gotoxy(box2x, box2y - 3); cout << char(186);

	
}


void Khung_SuaChuyenBay()
{
	SetColor(15);
	gotoxy(box2x, box2y - 8); cout << char(201);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(187);
	
	gotoxy(box2x, box2y - 7); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 7); cout << char(186);
	
	gotoxy(box2x, box2y - 6); cout << char(186)<< "   Nhap vao ma chuyen bay:                ";
	gotoxy(box2x + box2s + 1, box2y - 6); cout << char(186);
	
	gotoxy(box2x, box2y - 5); cout << char(186) ;
	gotoxy(box2x + box2s + 1, box2y - 5); cout << char(186);
	
	gotoxy(box2x, box2y - 4); cout << char(186)<< "     Nhap so hieu may bay:                       ";
	gotoxy(box2x + box2s + 1, box2y - 4); cout << char(186);
	
	gotoxy(box2x, box2y - 3); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 3); cout << char(186);
	
	gotoxy(box2x, box2y - 2); cout << char(186)<< "                     Ngay:                  ";
	gotoxy(xNgay+2, yNgay);cout<<"/";
	gotoxy(xNgay+5, yNgay);cout<<"/";
	gotoxy(box2x + box2s + 1, box2y - 2); cout << char(186);
	
	gotoxy(box2x, box2y - 1); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y - 1); cout << char(186);
	
	gotoxy(box2x, box2y); 	cout << char(186)<< "                      Gio:   :  ";
	gotoxy(box2x + box2s + 1, box2y); cout << char(186);
	
	gotoxy(box2x, box2y + 1); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y + 1); cout << char(186);
	
	gotoxy(box2x, box2y + 2); cout << char(186)<< "              San bay den:                ";
	gotoxy(box2x + box2s + 1, box2y + 2); cout << char(186);
	
	gotoxy(box2x, box2y + 3); cout << char(186);
	gotoxy(box2x + box2s + 1, box2y + 3); cout << char(186);
	gotoxy(box2x, box2y + 4); cout << char(200);
	for(int i = 1; i < box2s + 1; i++) cout << char(205);
	cout << char(188); 
}

void Khung_ChuyenBay()
{
	resizeConsole(1000,600);
	Color(ColorCYAN);
	gotoxy(45, 2);
	cout << "DANH SACH CHUYEN BAY"; 
	gotoxy(30,3);
	
	gotoxy(tab2x, tab2y);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tab2s + 21; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x, tab2y + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + tab2s + 21, tab2y + i);
		cout << char(179) ;
	}
	
	gotoxy(tab2x , tab2y + tab2w);
	cout << char(192); // L
	//dong cuoi
	for(int i = 1; i < tab2s + 21; i++)
	{
		gotoxy(tab2x + i, tab2y + tab2w);
		cout << char(196);
	}
	gotoxy(tab2x + tab2s + 21 , tab2y + tab2w);
	cout << char(217); // _|

	// STT
	gotoxy(tab2x + 3, tab2y + 1); cout << "STT";
	gotoxy(tab2x + 8, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 8, tab2y + i); cout << char(179); // cot stt
	}
	
	gotoxy(tab2x, tab2y + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tab2s + 21; i++)
	{
		gotoxy(tab2x + i, tab2y + 2);
		cout << char(196);
	}
	gotoxy(tab2x + 8, tab2y + 2); cout << char(197);
	gotoxy(tab2x + tab2s + 21, tab2y + 2); cout << char(180); //-|
	gotoxy(tab2x + 8, tab2y + tab2w); cout << char(193);

	// SO HIEU MB
	gotoxy(tab2x + 9, tab2y + 1); cout << "SO HIEU MB";
	gotoxy(tab2x + 20, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 20, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 20, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 20, tab2y + tab2w); cout << char(193);

	// MA CHUYEN BAY
	gotoxy(tab2x + 23, tab2y + 1); cout << "MA CHUYEN BAY";
	gotoxy(tab2x + 38, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 38, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 38, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 38, tab2y + tab2w); cout << char(193);

	// NGAY
	gotoxy(tab2x + 40, tab2y + 1); cout << "NGAY KHOI HANH";
	gotoxy(tab2x + 55, tab2y); cout << char(194);
	
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 55, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 55, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 55, tab2y + tab2w); cout << char(193);
	
	// GIO
	gotoxy(tab2x + 60, tab2y + 1); cout << "GIO";
	gotoxy(tab2x + 68, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 68, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 68, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 68, tab2y + tab2w); cout << char(193);
	
	// SAN BAY DEN
	gotoxy(tab2x + 70, tab2y + 1); cout<<"SAN BAY DEN";
	gotoxy(tab2x + 83, tab2y); cout << char(194);
	
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 83, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 83, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 83, tab2y + tab2w); cout << char(193);
	gotoxy(tab2x + 94+2, tab2y ); cout << char(194);
	
	gotoxy(tab2x + 85, tab2y + 1); cout<<"TRANG THAI";
	// VE CON LAI
		for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + tab2s + 10, tab2y + i);
		cout << char(179) ;
	}
	gotoxy(tab2x + tab2s + 10, tab2y + 2); cout << char(197);
	gotoxy(tab2x + tab2s + 10, tab2y + tab2w); cout << char(193);
	gotoxy(tab2x + tab2s + 13, tab2y +1); cout << "SO VE";
	//BUTTON
	gotoxy(7,27);cout<<char(176)<<"DI CHUYEN:  LEFT, RIGHT";
	gotoxy(7,29);cout<<char(176)<<"THEM: INSERT| XOA : DELETE| HUY: ESC";
	gotoxy(7,30);cout<<char(176)<<"CHON: ENTER";

}

void KhungDanhSachCBTrongNgay()
{
	SetBGColor(ColorBLACK);
	clrscr();
	resizeConsole(1000,600);
	Color(ColorCYAN);
	gotoxy(30, 2);
	cout << "DANH SACH CHUYEN BAY TRONG NGAY"; 
	gotoxy(30,3);
	
	gotoxy(tab2x, tab2y);
	cout << char(218);
	//-------- dong dau
	for(int i = 1; i < tab2s + 21; i++)
	{
		cout << char(196);
	}
	cout << char(191);
	
	//cot dau
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x, tab2y + i);
		cout << char(179);
	}
	//cot cuoi
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + tab2s + 21, tab2y + i);
		cout << char(179) ;
	}
	
	gotoxy(tab2x , tab2y + tab2w);
	cout << char(192); // L
	//dong cuoi
	for(int i = 1; i < tab2s + 21; i++)
	{
		gotoxy(tab2x + i, tab2y + tab2w);
		cout << char(196);
	}
	gotoxy(tab2x + tab2s + 21 , tab2y + tab2w);
	cout << char(217); // _|

	// STT
	gotoxy(tab2x + 3, tab2y + 1); cout << "STT";
	gotoxy(tab2x + 8, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 8, tab2y + i); cout << char(179); // cot stt
	}
	
	gotoxy(tab2x, tab2y + 2);
	cout << char(195);
	// dong hai
	for(int i = 1; i < tab2s + 21; i++)
	{
		gotoxy(tab2x + i, tab2y + 2);
		cout << char(196);
	}
	gotoxy(tab2x + 8, tab2y + 2); cout << char(197);
	gotoxy(tab2x + tab2s + 21, tab2y + 2); cout << char(180); //-|
	gotoxy(tab2x + 8, tab2y + tab2w); cout << char(193);

	// SO HIEU MB
	gotoxy(tab2x + 9, tab2y + 1); cout << "SO HIEU MB";
	gotoxy(tab2x + 20, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 20, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 20, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 20, tab2y + tab2w); cout << char(193);

	// MA CHUYEN BAY
	gotoxy(tab2x + 23, tab2y + 1); cout << "MA CHUYEN BAY";
	gotoxy(tab2x + 38, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 38, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 38, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 38, tab2y + tab2w); cout << char(193);

	// NGAY
	gotoxy(tab2x + 40, tab2y + 1); cout << "NGAY KHOI HANH";
	gotoxy(tab2x + 55, tab2y); cout << char(194);
	
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 55, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 55, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 55, tab2y + tab2w); cout << char(193);
	
	// GIO
	gotoxy(tab2x + 60, tab2y + 1); cout << "GIO";
	gotoxy(tab2x + 68, tab2y); cout << char(194);
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 68, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 68, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 68, tab2y + tab2w); cout << char(193);
	
	// SAN BAY DEN
	gotoxy(tab2x + 70, tab2y + 1); cout<<"SAN BAY DEN";
	gotoxy(tab2x + 83, tab2y); cout << char(194);
	
	for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + 83, tab2y + i); cout << char(179);
	}
	gotoxy(tab2x + 83, tab2y + 2); cout << char(197);
	gotoxy(tab2x + 83, tab2y + tab2w); cout << char(193);
	gotoxy(tab2x + 94+2, tab2y ); cout << char(194);
	
	gotoxy(tab2x + 85, tab2y + 1); cout<<"TRANG THAI";
	// VE CON LAI
		for(int i = 1; i < tab2w + 1; i++)
	{
		gotoxy(tab2x + tab2s + 10, tab2y + i);
		cout << char(179) ;
	}
	gotoxy(tab2x + tab2s + 10, tab2y + 2); cout << char(197);
	gotoxy(tab2x + tab2s + 10, tab2y + tab2w); cout << char(193);
	gotoxy(tab2x + tab2s + 13, tab2y +1); cout << "SO VE";
	//BUTTON
	gotoxy(7,27);cout<<char(176)<<"DI CHUYEN:  LEFT, RIGHT";
	gotoxy(7,29);cout<<char(176)<<"NHAP: ENTER";
}

//---------------- MENU
void MenuSelection(int vt){
		Color(ColorWHITE);
		gotoxy(11,7);cout<<"         DANH  SACH  MAY  BAY          ";
		gotoxy(11,8);cout<<"                                       ";
		gotoxy(11,12);cout<<"        DANH  SACH  CHUYEN  BAY        ";
		gotoxy(11,13);cout<<"                                       ";
		gotoxy(11,16);cout<<"           DAT  VE  MAY  BAY           ";
		gotoxy(11,17);cout<<"                                       ";
		gotoxy(11,21);cout<<"         HUY  VE  MAY  BAY             ";
		gotoxy(11,22);cout<<"                                       ";
		gotoxy(61,7);cout<<"   DANH SACH HANH KHACH THUOC CHUYEN BAY ";
		gotoxy(61,8);cout<<"                                         ";
		gotoxy(61,12);cout<<"    DANH SACH CHUYEN BAY TRONG NGAY      ";
		gotoxy(61,13);cout<<"                                         ";
		gotoxy(61,16);cout<<"      DANH  SACH  CAC  VE  CON  TRONG    ";
		gotoxy(61,17);cout<<"                                         ";
		gotoxy(61,21);cout<<"        THONG  KE  SO  LUOT BAY          ";
		gotoxy(61,22);cout<<"                                         ";
		SetBGColor(4);SetColor(ColorWHITE);
		if (vt==1) {
			gotoxy(11,7);cout<<"         DANH  SACH  MAY  BAY          ";
			gotoxy(11,8);cout<<"                                       ";

		}
		else if (vt==2) {
			gotoxy(11,12);cout<<"        DANH  SACH  CHUYEN  BAY        ";
			gotoxy(11,13);cout<<"                                       ";
		}
		else if (vt==3) {
			gotoxy(11,16);cout<<"           DAT  VE  MAY  BAY           ";
			gotoxy(11,17);cout<<"                                       ";
		}
		else if (vt==4) {
			gotoxy(11,21);cout<<"         HUY  VE  MAY  BAY             ";
			gotoxy(11,22);cout<<"                                       ";
		}
		else if (vt==5) {
			gotoxy(61,7);cout<<"   DANH SACH HANH KHACH THUOC CHUYEN BAY ";
			gotoxy(61,8);cout<<"                                         ";
		}
		else if (vt==6) {
			gotoxy(61,12);cout<<"    DANH SACH CHUYEN BAY TRONG NGAY      ";
			gotoxy(61,13);cout<<"                                         ";
		}
		else if (vt==7) {
			gotoxy(61,16);cout<<"      DANH  SACH  CAC  VE  CON  TRONG    ";
			gotoxy(61,17);cout<<"                                         ";
		}
		else if (vt==8) {
			gotoxy(61,21);cout<<"        THONG  KE  SO  LUOT BAY          ";
			gotoxy(61,22);cout<<"                                         ";
		}
		Color(ColorBLACK);
}
void menu(int vt,ListMayBay lmb, listCB list) {
		
		
	int c = _getch();
	if( c == 224)
	c = _getch();	
	do
	{
		MenuSelection(vt);
		c = _getch();
		switch (c)
		{
		case Up: vt--;
			if (vt == 0) {
				vt = 8;
			}
			break;
		case Down:vt++;
			if (vt == 9) {
				vt = 1;
			}
			break;
		case Right: 
			if (vt == 1) {
				vt = 5;
			}
			else if(vt == 2){
				vt = 6;
			}
			else if(vt == 3){
				vt = 7;
			}
			else if(vt == 4){
				vt = 8;
			}
			break;
		case Left:
			if (vt == 5) {
				vt = 1;
			}
			else if(vt == 6){
				vt = 2;
			}
			else if(vt == 7){
				vt = 3;
			}
			else if(vt == 8){
				vt = 4;
			}
			break;
		case ESC:
			exit(0);
		}
		
	} while (c!=13);// PHIM ENTER
	switch (vt){
		case 1: // DANH SACH MAY BAY
		{
			DocFileMayBay(lmb);
	        Danh_Sach_MayBay(lmb,list);
			break;
		}
		case 2: // DANH SACH CHUYEN BAY
		{
			MenuChuyenBay(lmb,list);
			break;
		}
		case 3: // DAT VE MAY BAY
		{
			MenuDatVeMB(lmb,list);
			break;
		}
		case 4: // HUY VE MAY BAY
		{
			MenuHuyVe(lmb,list);
			break;
		}
		case 5: // DANH SACH HANH KHACH THUOC CHUYEN BAY
		{
			Danh_Sach_HK_Trong_CB(list,lmb);
			break;
		}
		case 6: // DANH SACH CHUYEN BAY TRONG NGAY
		{
			DanhSachChuyenBayTheoNgay(lmb,list);
			break;
		}
		case 7: // DANH SACH CAC VE CON TRONG 
		{
			DanhSachVeTrongCB(lmb,list);
			break;
		}
		case 8: // THONG KE SO LUOT BAY
		{
			Danh_Sach_Thong_Ke_So_Luot_Bay(list,lmb);
			break;
		}
		default:
        exit(0);
	}
}
//void Initiator(){
//		
// 	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
//	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
//	DisableResizeWindow();
//	DisableSelection();
//    DisableCtrButton(false, true, true);
//    ShowScrollbar(0);
//    ShowCur(0);
//	DisableSelection();
//	
//}

void display(){
// Ham khong cho boi den
//	Initiator();
	
//    make border
    CursorStatus(25, TRUE);
    Color(12);
    //bien trai
    gotoxy(10+10, 1);
    printf("%c", 201);
    for (int i = 2; i < 25; i++) {
        gotoxy(10+10, i);
        printf("%c", 186); 
    }
    //bien duoi
    gotoxy(10+10, 25);
    printf("%c", 200); Sleep(5);

    for (int i = 11; i < 90; i++) {
        gotoxy(10+i, 25);
        printf("%c", 205); 
    }
    //bien phai
    gotoxy(10+90, 25);
    printf("%c", 188);
    for (int i = 24; i > 1; i--) {
        gotoxy(10+90, i);
        printf("%c", 186); 
    }
    //bien tren
    gotoxy(10+90, 1);
    printf("%c", 187);
    for (int i = 89; i > 10; i--) {
        gotoxy(10+i, 1);
        printf("%c", 205); 
    }
    //Thong tin truong
    Color(244);
    gotoxy(10+13, 3);
    cout << " HOC VIEN CONG NGHE BUU CHINH VIEN THONG ";

    gotoxy(10+26, 4);
    Color(244);
    cout << " KHOA: CNTT2 ";
    gotoxy(10+16,5);
    Color(11);
    cout<<"MON: CAU TRUC DU LIEU & GIAI THUAT";
    gotoxy(10+78, 3);
    //Ten De tai
    Color(10);
    gotoxy(10+39, 9);
    cout << " QUAN LY CHUYEN BAY ";
    //TEN CHUONG TRINH
	Color(12);
	
    TextSlide("LUONG DINH KHANG - N18DCCN093",35,19,13);
    TextSlide("LE BA KHANH      - N18DCCN099",35,20,13);
    
    for (int i = 0; i< 5 ;i++){
	Color(15);
    gotoxy(10+15,11); cout <<"    __          __     _               ______      _   ";
	gotoxy(10+15,12); cout <<"    ||\\        /||    / \\  \\\\    //    ||   \\\\    / \\  \\\\    //   ";
	gotoxy(10+15,13); cout <<"    || \\      //||   / _ \\  \\\\  //     ||___||   / _ \\  \\\\  //     ";
	gotoxy(10+15,14); cout <<"    ||  \\    // ||  / |__|\\  \\\\//      ||___||  / |__|\\  \\\\//     ";
	gotoxy(10+15,15); cout <<"    ||   \\  //  || /  ___  \\  ||       ||   || /  ___  \\  ||          ";
	gotoxy(10+15,16);cout << "    ||    \\//   ||/__/   \\__\\ ||       ||___///__/   \\__\\ ||   ";
	Color(12);Sleep(400);
	gotoxy(10+15,11); cout <<"    __          __     _               ______      _   ";
	gotoxy(10+15,12); cout <<"    ||\\        /||    / \\  \\\\    //    ||   \\\\    / \\  \\\\    //   ";
	gotoxy(10+15,13); cout <<"    || \\      //||   / _ \\  \\\\  //     ||___||   / _ \\  \\\\  //     ";
	gotoxy(10+15,14); cout <<"    ||  \\    // ||  / |__|\\  \\\\//      ||___||  / |__|\\  \\\\//     ";
	gotoxy(10+15,15); cout <<"    ||   \\  //  || /  ___  \\  ||       ||   || /  ___  \\  ||          ";
	gotoxy(10+15,16);cout << "    ||    \\//   ||/__/   \\__\\ ||       ||___///__/   \\__\\ ||   ";
	Sleep(500);
	}
	gotoxy(10+31, 23);
	Color(12);
    system("PAUSE");
    //----- Menu
    clrscr();
}
//-- GIAO DIEN MENU
	void MenuInterface(listMayBay lmb,listCB list){
		clrscr();
		DrawFrame(3,1,110,28);
		gotoxy(55,3);
		Color(15);cout<<char(178)<<"MENU"<<char(178);
		DrawFrame(10,6,40,3);
		DrawFrame(10,11,40,3);
		DrawFrame(10,15,40,3);
		DrawFrame(10,20,40,3);
		
		gotoxy(10,8);cout<<char(186);
		gotoxy(10,7);cout<<char(186);
		
		gotoxy(10,13);cout<<char(186);
		gotoxy(10,12);cout<<char(186);
		
		gotoxy(10,17);cout<<char(186);
		gotoxy(10,16);cout<<char(186);
		
		gotoxy(10,22);cout<<char(186);
		gotoxy(10,21);cout<<char(186);
		//Cot 2 
		DrawFrame(60,6,42,3);
		DrawFrame(60,11,42,3);
		DrawFrame(60,15,42,3);
		DrawFrame(60,20,42,3);
		
		gotoxy(60,22);cout<<char(186);
		gotoxy(60,21);cout<<char(186);
		
		gotoxy(60,12);cout<<char(186);
		gotoxy(60,13);cout<<char(186);
		
		gotoxy(60,16);cout<<char(186);
		gotoxy(60,17);cout<<char(186);
		
		gotoxy(60,8);cout<<char(186);
		gotoxy(60,7);cout<<char(186);
		Color(ColorWHITE);
		gotoxy(11,7);cout<<"         DANH  SACH  MAY  BAY          ";
		gotoxy(11,8);cout<<"                                       ";
		gotoxy(11,12);cout<<"        DANH  SACH  CHUYEN  BAY        ";
		gotoxy(11,13);cout<<"                                       ";
		gotoxy(11,16);cout<<"           DAT  VE  MAY  BAY           ";
		gotoxy(11,17);cout<<"                                       ";
		gotoxy(11,21);cout<<"         HUY  VE  MAY  BAY             ";
		gotoxy(11,22);cout<<"                                       ";
		gotoxy(61,7);cout<<"   DANH SACH HANH KHACH THUOC CHUYEN BAY ";
		gotoxy(61,8);cout<<"                                         ";
		gotoxy(61,12);cout<<"    DANH SACH CHUYEN BAY TRONG NGAY      ";
		gotoxy(61,13);cout<<"                                         ";
		gotoxy(61,16);cout<<"      DANH  SACH  CAC  VE  CON  TRONG    ";
		gotoxy(61,17);cout<<"                                         ";
		gotoxy(61,21);cout<<"        THONG  KE  SO  LUOT BAY          ";
		gotoxy(61,22);cout<<"                                         ";
		gotoxy(10,26);cout<<char(176)<<"THAO TAC: UP, DOWN, LEFT, RIGHT, ENTER";
		gotoxy(10,27);cout<<char(176)<<"THOAT: ESC";
		menu(1,lmb,list);
	}

// GIAO DIEN KET THUC
void The_End(){
	
//    Nocursortype(0);
    int x = 1, y = 5;
    ifstream file("The_end.txt", ios::in);
    string a; 
    int i = 0;
    gotoxy(0,2);
    if (file.good())  // Kiem tra xem file co ket noi duoc hay khong?
        while (!file.eof()) {
                getline(file, a);
                SetColor(11);
                gotoxy(x,y+i);
                cout << a << endl;
                Sleep(100);
                i++;
            }
    file.close();
	system("pause");

}

//HIEN THI TRANG
void HienThiTrang(int tongtrang, int tranghientai, int x, int y)
{
    //textcolor(62);
    gotoxy(x, y + 1);
    cout << "Trang :  " << (tranghientai + 1) << " / " << tongtrang << "   ";
}
//------------------------------------- NHAP CHUYEN BAY-------------------------------------

void NhapChuyenBay(ListMayBay lmb, listCB &list){
		while (true)
		{
			int key,xThongBao = 20, yThongBao = -10;
			int dem = 0;	
//			system("cls");
			Khung_NhapChuyenBay();
			ChuyenBay cb;
			strcpy(cb.soHieuMB, "");
			strcpy(cb.MaChuyenBay, "");
			cb.ThoiGianDi.ngay = -1;
			cb.ThoiGianDi.thang = -1;
			cb.ThoiGianDi.nam = -1;
			cb.ThoiGianDi.gio = -1;
			cb.ThoiGianDi.phut = -1;
			strcpy(cb.SanBayDen, "");
			cb.TrangThai = 1; // CON VE
			gotoxy(box2x + xThongBao, box2y + yThongBao);cout<<"                               ";
			gotoxy(box2x + xThongBao+30, box2y + yThongBao);cout<<"                                     ";
	
				bool trung;
				// NHAP SO HIEU MAY BAY
				
				do{
					gotoxy(box2x + 28, box2y - 6); 
					string tmp = nhapChuoi(box2x + 28, box2y - 6);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cb.soHieuMB, tmp.c_str()); 
					strcpy(cb.soHieuMB, fix_Ma(cb.soHieuMB));	
					if (Check_SoHieu_MB(lmb, cb.soHieuMB) != -1)
					{
						dem++;
						gotoxy(box2x + 28, box2y - 6);  	cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 6); 	cout<<cb.soHieuMB;
						trung = true;
					}
					else if (strcmp(cb.soHieuMB, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG !";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
					}
					else
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"SO HIEU MAY BAY NAY KHONG CO !";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
					}	
				}while(trung == false);
				if (strcmp(cb.soHieuMB, "") == 0) break;
				
				// NHAP MA CHUYEN BAY
				do{
					trung = false;
					gotoxy(box2x + 28, box2y - 4);
					string tmp = nhapChuoi(box2x + 28, box2y - 4);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cb.MaChuyenBay, tmp.c_str()); 
					strcpy(cb.MaChuyenBay, fix_Ma(cb.MaChuyenBay));
					
				
					if (Check_MaCB(list, cb.MaChuyenBay) == 1)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"MA CHUYEN BAY NAY DA CO!";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 4);  cout<<"                                 ";
					
					}
					else if (strcmp(cb.MaChuyenBay, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG!";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 4);  cout<<"                                 ";
					
					}
					else
					{	
						dem++;
						gotoxy(box2x + 28, box2y - 4);  cout<<"                                 ";
						gotoxy(box2x + 28, box2y - 4);cout<<cb.MaChuyenBay;
						trung = true;
					}
				}while(trung == false);
				if (strcmp(cb.MaChuyenBay, "") == 0) break;
				int ngayBay=0;
					// NHAP NGAY 
				do{
					
					trung = false;
					gotoxy(xNgay, yNgay);
					char ngay[10];
					string tmp = nhapSo(xNgay, yNgay);
					gotoxy(xNgay+2, yNgay);cout<<"/";
					gotoxy(xNgay+5, yNgay);cout<<"/";
	
					if(tmp == "exit"){
						break;
					}
					strcpy(ngay, tmp.c_str()); 
					strcpy(ngay, fix_Ma(ngay));
					if (strcmp(ngay, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                               ";
						gotoxy(xNgay, yNgay);  cout<<"  ";
					}
					else
					{
						int check = check_Chuoi_Char(ngay);
						if (check == 1)
						{
							ngayBay = atoi(ngay);
							if (ngayBay <= 0 || ngayBay > 31 )
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
								gotoxy(xNgay, yNgay);  	cout<<"  ";
							}
							else 
							{
								dem++;
								cb.ThoiGianDi.ngay = ngayBay;
								gotoxy(box2x + 28, yNgay);  	cout<<"  ";
								gotoxy(xNgay, yNgay);	cout<<cb.ThoiGianDi.ngay;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
							gotoxy(xNgay, yNgay);  cout<<"  ";
						}
					}
			
				}while(trung == false);
				if (cb.ThoiGianDi.ngay == -1) break;
				
				// NHAP THANG
				do{
					trung = false;
					gotoxy(xNgay+3, yNgay);
					char thang[10];
					string tmp = nhapSo(xNgay+3, yNgay);
					gotoxy(xNgay+2, yNgay);cout<<"/";
						gotoxy(xNgay+5, yNgay);cout<<"/";
	
					if(tmp == "exit"){
						break;
					}
					strcpy(thang, tmp.c_str()); 
					
					strcpy(thang, fix_Ma(thang));
					if (strcmp(thang, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(xNgay+3, yNgay);  cout<<"  ";
					}
					else
					{
						int check = check_Chuoi_Char(thang);
						if (check == 1)
						{
							int thangBay = atoi(thang);
							if (thangBay <= 0 || thangBay > 12)
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THANG KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                        ";
								gotoxy(xNgay+3, yNgay);  	cout<<"  ";
							}
							else
							{
								dem++;
								cb.ThoiGianDi.thang = thangBay;
								gotoxy(xNgay+3, yNgay);  	cout<<"  ";
								gotoxy(xNgay+3, yNgay);	cout<<cb.ThoiGianDi.thang;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                   ";
							gotoxy(xNgay+3, yNgay);  cout<<"  ";
						}
					}
			
				}while(trung == false);
				if (cb.ThoiGianDi.thang == -1) break;
				
				// NHAP NAM
				do{
					trung = false;
					gotoxy(xNgay+6, yNgay);
					char nam[10];
					string tmp = nhapSo(xNgay+6, yNgay);
					gotoxy(xNgay+2, yNgay);cout<<"/";
					gotoxy(xNgay+5, yNgay);cout<<"/";
	
					if(tmp == "exit"){
						break;
					}
					strcpy(nam, tmp.c_str()); 
					
					strcpy(nam, fix_Ma(nam));
					if (strcmp(nam, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(xNgay+6, yNgay);  cout<<"    ";
					}
					else if ( !Check_Date(cb.ThoiGianDi.nam, cb.ThoiGianDi.thang, ngayBay))
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
						gotoxy(xNgay+6, yNgay); cout<<"    ";
					}
					else
					{
						int check = check_Chuoi_Char(nam);
						if (check == 1)
						{
							int namBay = atoi(nam);
							if (namBay < 2019)
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"CHI NHAN SO VA >= 2019!";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                 ";
								gotoxy(xNgay+6, yNgay);  	cout<<"    ";
							}
							else
							{
								dem++;
								cb.ThoiGianDi.nam = namBay;
								gotoxy(xNgay+6, yNgay);  	cout<<"    ";
								gotoxy(xNgay+6, yNgay);	cout<<cb.ThoiGianDi.nam;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
							gotoxy(xNgay+6, yNgay);  cout<<"    ";
						}
						
					}
			
				}while(trung == false);
				if (cb.ThoiGianDi.nam == -1) break;
				
				
			
				// NHAP GIO
				do{
					trung = false;
					gotoxy(box2x + 28, box2y);
					char gio[10];
					string tmp = nhapSo(box2x + 28, box2y);
					
	
					if(tmp == "exit"){
						break;
					}
					strcpy(gio, tmp.c_str()); 
					
					strcpy(gio, fix_Ma(gio));
					if (strcmp(gio, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(box2x + 28, box2y );  cout<<"  ";
					}
					else
					{
						int check = check_Chuoi_Char(gio);
						if (check == 1)
						{
							int gioBay = atoi(gio);
							if (gioBay < 0 || gioBay > 23 )
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"GIO KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
								gotoxy(box2x + 28, box2y );  	cout<<"  ";
							}
							else 
							{
								dem++;
								cb.ThoiGianDi.gio = gioBay;
								gotoxy(box2x + 28, box2y );  	cout<<"  :";
								gotoxy(box2x + 28, box2y );	cout<<cb.ThoiGianDi.gio;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
							gotoxy(box2x + 28, box2y );  cout<<"  ";
						}
							
					}
			
				}while(trung == false);
				if (cb.ThoiGianDi.gio == -1) break;
				
				// NHAP PHUT
				do{
					trung = false;
					gotoxy(box2x + 31, box2y );
					char phut[10];
					string tmp = nhapSo(box2x + 31, box2y);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(phut, tmp.c_str()); 
					
					strcpy(phut, fix_Ma(phut));
					if (strcmp(phut, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(box2x + 31, box2y );  cout<<"  ";
					}
					else
					{
						int check = check_Chuoi_Char(phut);
						if (check == 1)
						{
							int phutBay = atoi(phut);
							if (phutBay < 0 || phutBay > 59)
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"PHUT KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
								gotoxy(box2x + 31, box2y);  	cout<<"    ";
							}
							else 
							{
								dem++;
								cb.ThoiGianDi.phut = phutBay;
								gotoxy(box2x + 31, box2y );  	cout<<"    ";
								gotoxy(box2x + 31, box2y );	cout<<cb.ThoiGianDi.phut;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
							gotoxy(box2x + 31, box2y );  cout<<"    ";
						}
					}
			
				}while(trung == false);
				if (cb.ThoiGianDi.phut == -1) break;
				
				if (!Check_ThoiGian_ChuyenBay(cb.ThoiGianDi))
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THOI GIAN CUA BAN DA QUA HAN";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
					continue;
				}
				if(CheckInvalidFlight(list,cb))
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"DA TON TAI CHUYEN BAY CO CUNG NGAY GIO & MAY BAY";
					Sleep(2000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao);cout<<"                               				       	";
					continue;
				}
				// NHAP SAN BAY DEN
				do{
					trung = false;
					gotoxy(box2x + 28, box2y + 2);
					char sanBayDen[150];
					string tmp = nhapChuoi(box2x + 28, box2y + 2);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(sanBayDen, tmp.c_str()); 
					
					strcpy(sanBayDen, fix_HoTen(sanBayDen));
					if (strcmp(sanBayDen, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(box2x + 28, box2y + 2);  cout<<"    ";
					}
					else
					{
						dem++;
						strcpy(cb.SanBayDen, sanBayDen);
						gotoxy(box2x + 28, box2y + 2);  	cout<<"    ";
						gotoxy(box2x + 28, box2y + 2);	cout<<cb.SanBayDen;
						trung = true;
					}
			
				}while(trung == false);
				if (cb.SanBayDen == 0) break;
				int socho = Get_socho(lmb,cb.soHieuMB);
				
				if (dem == 8)
				{
					initListVe(cb,socho);
					AddEndingList(list, cb);
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"DA THEM THANH CONG";
					Sleep(1500);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                             ";
					dem = 0;
				}
		}
		int a = XacNhanSaveFile();
		if(a == 1)
		{
			LuuFileChuyenBay(list, lmb);
		}
}

void SuaChuyenBay(ListMayBay lmb, listCB &list)
{
	int key,xThongBao = 20, yThongBao = -10;
	int dem = 0;
	Khung_SuaChuyenBay();
	ChuyenBay cb_edit;
	strcpy(cb_edit.soHieuMB, "");
	strcpy(cb_edit.MaChuyenBay, "");
	cb_edit.ThoiGianDi.ngay = -1;
	cb_edit.ThoiGianDi.thang = -1;
	cb_edit.ThoiGianDi.nam = -1;
	cb_edit.ThoiGianDi.gio = -1;
	cb_edit.ThoiGianDi.phut = -1;
	strcpy(cb_edit.SanBayDen, "");
	cb_edit.TrangThai = 1;
	char maCB[15];
	char SanbayDen[20];
	char SoHieuMB[15];
	int ngayBay=0;
	bool trung;
	//NHAP MA CHUYEN BAY
	NhapCB:
		gotoxy(box2x + 28, box2y - 6);cout<<"              ";
		gotoxy(box2x + 28, box2y - 6);
		string tmp = nhapChuoi(box2x + 28, box2y - 6);
		if(tmp == "exit"){
			return;
		}
		strcpy(maCB, tmp.c_str()); 
		strcpy(maCB, fix_Ma(maCB));
		nodeCB *ptr = Search_MaCB(list, maCB); 
		if (!strcmp(maCB, "\0"))
		{
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG !";
			Sleep(1000);  
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
			gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
			goto NhapCB;
		}	
					
		else if (ptr != NULL)
		{
			if(!CheckDSVe(list,lmb,maCB))
			{
				gotoxy(box2x + 28, box2y - 6);cout<<"                                 ";
				strcpy(cb_edit.MaChuyenBay,maCB);
			}
			else
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"CHUYEN BAY NAY DA CO NGUOI DAT VE";
				Sleep(1400);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
				goto NhapCB;							
			}	
		}
					
		else
		{
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"MA CHUYEN BAY KHONG TON TAI !";
			Sleep(1000);  
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
			gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
			goto NhapCB;
		}
	// XUAT CHUYEN BAY CHINH SUA
	gotoxy(box2x + 28, box2y - 6); cout<<ptr->CB.MaChuyenBay;
	gotoxy(box2x + 28, box2y - 4);cout<<ptr->CB.soHieuMB;
	gotoxy(xNgay,yNgay);cout<<ptr->CB.ThoiGianDi.ngay;
	gotoxy(xNgay+2,yNgay);cout<<"/"<<ptr->CB.ThoiGianDi.thang;
	gotoxy(xNgay+5,yNgay);cout<<"/"<<ptr->CB.ThoiGianDi.nam;
	gotoxy(xNgay,yNgay+2);cout<<ptr->CB.ThoiGianDi.gio;
	gotoxy(xNgay+2,yNgay+2);cout<<":"<<ptr->CB.ThoiGianDi.phut;
	gotoxy(xNgay,yNgay+4);cout<<ptr->CB.SanBayDen;			
	while(true)
	{	
		//NHAP SO HIEU MB CHINH SUA
		gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                               				   	"; // CLEAR THONG BAO
		NhapSoHieuMB:
		gotoxy(box2x + 28, box2y - 4);cout<<ptr->CB.soHieuMB;
		gotoxy(box2x + 28, box2y - 4);
		tmp = nhapChuoi2(box2x + 28, box2y - 4);
		if(tmp == "exit"){
			break;
		}
		else if(tmp==""||tmp=="next"){
			dem++;
			strcpy(cb_edit.soHieuMB,ptr->CB.soHieuMB);
			goto NhapNgay;
		}
		strcpy(SoHieuMB, tmp.c_str()); 
		strcpy(SoHieuMB, fix_Ma(SoHieuMB));
		if (strcmp(SoHieuMB, "\0") == 0)
		{
			dem++;
			strcpy(cb_edit.soHieuMB,ptr->CB.soHieuMB);
			goto NhapNgay;
		}
		else if (Check_SoHieu_MB(lmb, SoHieuMB)!=-1)
		{
			strcpy(cb_edit.soHieuMB,SoHieuMB);
			gotoxy(box2x + 28, box2y - 4);  cout<<"                                 ";
			gotoxy(box2x + 28, box2y - 4); 	cout<<cb_edit.soHieuMB;
			dem++;
		}
		else
		{
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"SO HIEU MAY BAY NAY KHONG CO !";
			Sleep(1000);  
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
			goto NhapSoHieuMB;
		}
		// NHAP NGAY CHINH SUA
		NhapNgay:
		do{	
			gotoxy(xNgay,yNgay);cout<<ptr->CB.ThoiGianDi.ngay;
			gotoxy(xNgay+2,yNgay);cout<<"/"<<ptr->CB.ThoiGianDi.thang;
			gotoxy(xNgay+5,yNgay);cout<<"/"<<ptr->CB.ThoiGianDi.nam;
			trung = false;
			gotoxy(xNgay, yNgay);
			char ngay[10];
			tmp = nhapSo2(xNgay, yNgay);		
			if(tmp == "exit"){
				break;
			}
			else if(tmp==""||tmp=="next"){
			dem++;
			cb_edit.ThoiGianDi.ngay = ptr->CB.ThoiGianDi.ngay;
			ngayBay = cb_edit.ThoiGianDi.ngay;
			gotoxy(box2x + 28, yNgay);cout<<"  ";
			gotoxy(xNgay, yNgay);cout<<ngayBay;
			break;
			}
			strcpy(ngay, tmp.c_str()); 
			strcpy(ngay, fix_Ma(ngay));
			if (strcmp(ngay, "\0") == 0)
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                               ";
				gotoxy(xNgay, yNgay);  cout<<"  ";
			}
			else
			{
				int check = check_Chuoi_Char(ngay);
				if (check == 1)
				{
					ngayBay = atoi(ngay);
					if (ngayBay <= 0 || ngayBay > 31 )
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
						gotoxy(xNgay, yNgay);  	cout<<"  ";
					}
					else 
					{
						dem++;
						cb_edit.ThoiGianDi.ngay = ngayBay;
						gotoxy(box2x + 28, yNgay);cout<<"  ";
						gotoxy(xNgay, yNgay);cout<<ngayBay;
						trung = true;
					}
				}
				else
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
					gotoxy(xNgay, yNgay);  cout<<"  ";
				}
			}
		}while(trung == false);
		if (cb_edit.ThoiGianDi.ngay == -1) break;
		// NHAP THANG
		do{
			trung = false;
			gotoxy(xNgay+3, yNgay);
			char thang[10];
			string tmp = nhapSo2(xNgay+3, yNgay);
			gotoxy(xNgay+2, yNgay);cout<<"/";
			gotoxy(xNgay+5, yNgay);cout<<"/";
			if(tmp == "exit"){
				break;
			}
			else if(tmp==""||tmp=="next"){
				dem++;
				cb_edit.ThoiGianDi.thang = ptr->CB.ThoiGianDi.thang;
				gotoxy(xNgay+3, yNgay); cout<<"  ";
				gotoxy(xNgay+3, yNgay);	cout<<cb_edit.ThoiGianDi.thang;
				break;
			}
			strcpy(thang, tmp.c_str()); 	
			strcpy(thang, fix_Ma(thang));
			if (strcmp(thang, "\0") == 0)
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
				gotoxy(xNgay+3, yNgay);  cout<<"  ";
			}
			else
			{
				int check = check_Chuoi_Char(thang);
				if (check == 1)
				{
					int thangBay = atoi(thang);						
					if (thangBay <= 0 || thangBay > 12)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THANG KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                        ";
						gotoxy(xNgay+3, yNgay);  	cout<<"  ";
					}
					else
					{
						dem++;
						cb_edit.ThoiGianDi.thang = thangBay;
						gotoxy(xNgay+3, yNgay); cout<<"  ";
						gotoxy(xNgay+3, yNgay);	cout<<cb_edit.ThoiGianDi.thang;
						trung = true;
					}
				}
				else
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                   ";
					gotoxy(xNgay+3, yNgay);  cout<<"  ";
				}
			}
	
		}while(trung == false);
		if (cb_edit.ThoiGianDi.thang == -1) break;
		
		// NHAP NAM
		do{
			trung = false;
			gotoxy(xNgay+6, yNgay);
			char nam[10];
			string tmp = nhapSo2(xNgay+6, yNgay);
			gotoxy(xNgay+2, yNgay);cout<<"/";
			gotoxy(xNgay+5, yNgay);cout<<"/";

			if(tmp == "exit"){
				break;
			}
			else if(tmp==""||tmp=="next"){
				dem++;
				cb_edit.ThoiGianDi.nam = ptr->CB.ThoiGianDi.nam;
				break;
			}
			strcpy(nam, tmp.c_str()); 
			
			strcpy(nam, fix_Ma(nam));
			if (strcmp(nam, "\0") == 0)
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
				gotoxy(xNgay+6, yNgay);  cout<<"    ";
			}
			else if ( !Check_Date(cb_edit.ThoiGianDi.nam, cb_edit.ThoiGianDi.thang, ngayBay))
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
				gotoxy(xNgay+6, yNgay); cout<<"    ";
				goto NhapNgay;
			}
			else
			{
				int check = check_Chuoi_Char(nam);
				if (check == 1)
				{
					int namBay = atoi(nam);
					if (namBay < 2019)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"CHI NHAN SO VA >= 2019!";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                 ";
						gotoxy(xNgay+6, yNgay);  	cout<<"    ";
					}
					else
					{
						dem++;
						cb_edit.ThoiGianDi.nam = namBay;
						gotoxy(xNgay+6, yNgay); cout<<"    ";
						gotoxy(xNgay+6, yNgay);cout<<cb_edit.ThoiGianDi.nam;
						trung = true;
					}
				}
				else
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
					gotoxy(xNgay+6, yNgay);  cout<<"    ";
				}
				
			}
	
		}while(trung == false);
		if (cb_edit.ThoiGianDi.nam == -1) break;
		
		// NHAP GIO BAY
		do{
			trung = false;
			gotoxy(box2x + 28, box2y);
			char gio[10];
			string tmp = nhapSo2(box2x + 28, box2y);

			if(tmp == "exit"){
				break;
			}
			else if(tmp==""||tmp=="next"){
				dem++;
				cb_edit.ThoiGianDi.gio = ptr->CB.ThoiGianDi.gio;
				break;
			}
			strcpy(gio, tmp.c_str()); 
			strcpy(gio, fix_Ma(gio));
			if (strcmp(gio, "\0") == 0)
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
				gotoxy(box2x + 28, box2y );  cout<<"  ";
			}
			else
			{
				int check = check_Chuoi_Char(gio);
				if (check == 1)
				{
					int gioBay = atoi(gio);
					if (gioBay < 0 || gioBay > 23 )
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"GIO KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
						gotoxy(box2x + 28, box2y );  	cout<<"  ";
					}
					else 
					{
						dem++;
						cb_edit.ThoiGianDi.gio = gioBay;
						gotoxy(box2x + 28, box2y );  	cout<<"  :";
						gotoxy(box2x + 28, box2y );	cout<<cb_edit.ThoiGianDi.gio;
						trung = true;
					}
				}
				else
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
					gotoxy(box2x + 28, box2y );  cout<<"  ";
				}		
			}	
		}while(trung == false);
				if (cb_edit.ThoiGianDi.gio == -1) break;
				
				// NHAP PHUT
		do{
			trung = false;
			gotoxy(box2x + 31, box2y );
			char phut[10];
			string tmp = nhapSo(box2x + 31, box2y);

			if(tmp == "exit"){
				break;
			}
			else if(tmp==""||tmp=="next")
			{
				dem++;
				cb_edit.ThoiGianDi.phut = ptr->CB.ThoiGianDi.phut;
				break;
			}
			strcpy(phut, tmp.c_str()); 
			
			strcpy(phut, fix_Ma(phut));
			if (strcmp(phut, "\0") == 0)
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
				gotoxy(box2x + 31, box2y );  cout<<"  ";
			}
			else
			{
				int check = check_Chuoi_Char(phut);
				if (check == 1)
				{
					int phutBay = atoi(phut);
					if (phutBay < 0 || phutBay > 59)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"PHUT KHONG HOP LE ";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
						gotoxy(box2x + 31, box2y);  	cout<<"    ";
					}
					else 
					{
						dem++;
						cb_edit.ThoiGianDi.phut = phutBay;
						gotoxy(box2x + 31, box2y );  	cout<<"    ";
						gotoxy(box2x + 31, box2y );	cout<<cb_edit.ThoiGianDi.phut;
						trung = true;
					}
				}
				else
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
					gotoxy(box2x + 31, box2y );  cout<<"    ";
				}
			}
	
		}while(trung == false);
		if (cb_edit.ThoiGianDi.phut == -1)break;
		if (!Check_ThoiGian_ChuyenBay(cb_edit.ThoiGianDi))
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THOI GIAN CUA BAN DA QUA HAN";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
				continue;
			}
		if(CheckInvalidFlight(list,cb_edit))
			{
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"DA TON TAI CHUYEN BAY CO CUNG NGAY GIO & MAY BAY";
				Sleep(1000);  
				gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                               					 ";
				continue;
			}
		// NHAP SAN BAY DEN
				do{
					trung = false;
					gotoxy(box2x + 28, box2y + 2);
					char sanBayDen[100];
					string tmp = nhapChuoi(box2x + 28, box2y + 2);
					if(tmp == "exit"){
						break;
					}
					else if(tmp==""){
						dem++;
						strcpy(cb_edit.SanBayDen,ptr->CB.SanBayDen);
						break;
						}
					strcpy(sanBayDen, tmp.c_str()); 
					strcpy(sanBayDen, fix_HoTen(sanBayDen));
					if (strcmp(sanBayDen, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(box2x + 28, box2y + 2);  cout<<"    ";
					}
					else
					{
						dem++;
						strcpy(cb_edit.SanBayDen, sanBayDen);
						gotoxy(box2x + 28, box2y + 2); cout<<"              ";
						gotoxy(box2x + 28, box2y + 2);cout<<cb_edit.SanBayDen;
						trung = true;
						
					}
				}while(trung == false);
				if(cb_edit.SanBayDen=="")break;
			

				if(dem==7)
				{
					int socho = Get_socho(lmb,cb_edit.soHieuMB);
					initListVe(cb_edit,socho);
					ptr->CB = cb_edit;
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"DA SUA THANH CONG";
					Sleep(1500);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                             ";
					dem = 0;
				}
				if(XacNhanSaveFile())
				{
					LuuFileChuyenBay(list,lmb);
					return;
				}
				else
				return;
	}					
}

bool XoaThanhCong(listCB &list, char maChuyenbaycanxoa[15])
{
	nodeCB *pDel = list.Head; 
	if (pDel == NULL)
		return false;
	else
	{
		nodeCB *ptemp = NULL;
		while (pDel != NULL)
		{
			if (strcmp(pDel->CB.MaChuyenBay, maChuyenbaycanxoa) == 0)
				break;
			ptemp = pDel;
			pDel = pDel->next;
		}
		if (pDel == NULL)
		{
			return false;
		}
		else if(pDel == list.Head)
		{
			Delete_First(list);
			list.SoLuongChuyenBay--;
			return true;
		}
		else
		{
			if(list.Tail == pDel ){
				list.Tail = ptemp;
			}
			Delete_after(ptemp);
			list.SoLuongChuyenBay--;
			return true;
		}
	}
}


void XoaChuyenBay(ListMayBay lmb, listCB &list)
{
	char chuyenbay[15];
	int xThongBao = 63, yThongBao = 28;
	KhungNhapMaCB(60,25);
	NhapChuyenBay:
	gotoxy(65,26);
	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
	cout<<"                      ";
	gotoxy(65,26);
	string temp = nhapChuoi(65,26);
	if(temp == "exit")
	{
		return;
	}	
	strcpy(chuyenbay, temp.c_str());
	strcpy(chuyenbay, fix_Ma(chuyenbay));
	if(strcmp(chuyenbay,"")==0)
	{
		gotoxy(xThongBao, yThongBao); cout <<" VUI LONG NHAP MA CHUYEN BAY ";
		Sleep(1000);
		goto NhapChuyenBay;
	}
	else if(Check_MaCB(list,chuyenbay)==-1)
	{
		gotoxy(xThongBao, yThongBao);cout <<" MA CHUYEN BAY KHONG TON TAI  ";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout << "                              ";
		goto NhapChuyenBay;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==3)
	{
		gotoxy(65,26);cout<<chuyenbay;
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HOAN TAT";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		if(XacNhanXoa())goto XacNhan;
		return;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==0)
	{
		gotoxy(65,26);cout<<chuyenbay;
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA BI HUY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		if(XacNhanXoa())goto XacNhan;
		
		return;
	}
	else
	{
		gotoxy(65,26);cout<<chuyenbay;
		ChuyenBay cb;
		cb = Search_MaCB(list,chuyenbay)->CB;
		if(cb.TongSoDaBan==0)
		{
			if(XacNhanXoa()){
				XacNhan:
				if(XoaThanhCong(list,chuyenbay))
				{
					SetColor(ColorBLACK);
					SetBGColor(ColorDARKWHITE);
					gotoxy(40, 16); cout << "                                ";
					gotoxy(40, 17); cout << "         XOA THANH CONG         ";
					gotoxy(40, 18); cout << "                                ";
					gotoxy(40, 19); cout << "                                ";
					gotoxy(40, 20); cout << "                                ";
					Sleep(1000);
					SetColor(ColorWHITE);
					SetBGColor(ColorBLACK);
					system("cls");
				}
				else
				{
					SetColor(ColorBLACK);
					SetBGColor(ColorDARKWHITE);
					gotoxy(40, 16); cout << "                                ";
					gotoxy(40, 17); cout << "       XOA KHONG THANH CONG     ";
					gotoxy(40, 18); cout << "                                ";
					gotoxy(40, 19); cout << "                                ";
					gotoxy(40, 20); cout << "                                ";
					Sleep(1000);
					SetColor(ColorWHITE);
					SetBGColor(ColorBLACK);
					clrscr();
				}
			}
			return;
		}
		else
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY CO NGUOI DAT VE KHONG THE XOA!";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout <<"                                          ";
			goto NhapChuyenBay;
			
		}
	}
}

void HuyChuyenBay(listMayBay lmb,listCB &list)
{
	string temp;
	char chuyenbay[15];
	int xThongBao = 65, yThongBao = 28;
	KhungNhapMaCB(60,25);
	nodeCB *PtrCB;
	NhapChuyenBay:
	gotoxy(65,26);
	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
	cout<<"                      ";
	gotoxy(65,26);
	temp = nhapChuoi(65,26);	
	 if(temp=="exit"){
		return;
	}
	strcpy(chuyenbay, temp.c_str());
	strcpy(chuyenbay, fix_Ma(chuyenbay));
	if(strcmp(chuyenbay,"")==0)
	{
		gotoxy(xThongBao, yThongBao); cout <<"VUI LONG NHAP MA CHUYEN BAY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao); cout <<"     			                ";
		goto NhapChuyenBay;
	}
	else if(Check_MaCB(list,chuyenbay)==-1)
	{
		gotoxy(xThongBao, yThongBao);cout << "MA CHUYEN BAY KHONG TON TAI";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout << "                              ";
		goto NhapChuyenBay;
	}
	else{
		PtrCB = Search_MaCB(list,chuyenbay);
		if(PtrCB->CB.TrangThai==3)
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HOAN TAT";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout <<"                            ";
			goto NhapChuyenBay;
		}
		else if(PtrCB->CB.TrangThai==0)
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA BI HUY";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout <<"                            ";
			goto NhapChuyenBay;
		}
		else 
		{	
			if(PtrCB->CB.TongSoDaBan!=0)
				{
					gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY CO NGUOI DAT VE ";
					Sleep(1000);
					gotoxy(xThongBao, yThongBao);cout <<"                            ";
				}
			if(XacNhanHuyChuyen())
			{
				PtrCB->CB.DsVe = NULL;
				PtrCB->CB.TrangThai=0;
				SetColor(ColorBLACK);SetBGColor(ColorDARKWHITE);gotoxy(40, 17);cout << "         XOA THANH CONG         ";
				SetBGColor(ColorBLACK);
			}
		}
	}
	
}

int XacNhanThoat()
{
	int x = 45, y = 19;
	gotoxy(40, 15);
	SetColor(ColorBLACK);
	SetBGColor(ColorDARKWHITE);
	cout << "                                ";
	gotoxy(40, 16); cout << "                                ";
	gotoxy(40, 17); cout << "  BAN CO MUON THOAT KHONG?  ";
	gotoxy(40, 18); cout << "                                ";
	gotoxy(40, 19); cout << "     YES                NO      ";
	gotoxy(40, 20); cout << "                                ";
	int keyhit;
	do{
		gotoxy(45, 19);
//		SetColor(ColorDARKCYAN);
		switch(x)
		{
		case 45 : gotoxy(45, 19); cout << "YES"; break;
		case 64 : gotoxy(64, 19); cout << "NO"; break;
		}
		keyhit = getch();
		if(keyhit == Left)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x -= 19;
			if(x != 45)
			{
				x = 64;
			}
		}
		else if(keyhit == Right)
		{
			gotoxy(45, 19);
//			SetColor(ColorDARKCYAN);
			switch(x)
			{
			case 45 : gotoxy(45, 19); cout << "YES"; break;
			case 64 : gotoxy(64, 19); cout << "NO"; break;
			}
			x += 19;
			if(x != 64)
			{
				x = 45;
			}
		}
		else if(x == 45 && keyhit == Enter)
		{
			gotoxy(boxx + 22, 29);
			SetBGColor(ColorBLACK);
			system("cls");
			return 1;
		}
		else if(x == 64 && keyhit == Enter)
		{
			SetBGColor(ColorBLACK);
			system("cls");
			return 0;
		}
	}while(true);
}

//---------------------CHUC NANG MAY BAY

void frame_NhapMaMayBay(int x, int y)
{
	gotoxy(x, y); SetBGColor(ColorDARKBLUE); SetColor(ColorDARKYELLOW);	cout << "    NHAP VAO SO HIEU MAY BAY    ";
	gotoxy(x, y + 1); SetBGColor(ColorDARKBLUE);		cout << "     ";
	gotoxy(x + 5, y + 1);  SetBGColor(ColorWHITE); 	cout << "                       ";
	gotoxy(x + 27, y + 1); SetBGColor(ColorDARKBLUE); 	cout << "     ";
	gotoxy(x, y + 2); SetBGColor(ColorDARKBLUE);		cout << "                                ";
	SetBGColor(ColorBLACK); SetColor(ColorWHITE);
}

void LuuFileMayBay(ListMayBay &listMB, ofstream &fileout)
{
	fileout << listMB.soluong<<endl;
	for (int i = 0; i < listMB.soluong; i++)
	{
		fflush(stdin);
		fileout << listMB.maybay[i]->soHieuMB << ","<<listMB.maybay[i]->loaiMB << ","<<listMB.maybay[i]->soCho<<endl;
		
	}
	
	fileout.close();
}


void Delete_MB(ListMayBay &listMB, char sohieu[])
{
	for (int i = 0; i < listMB.soluong; i++)
	{
		if (strcmp(listMB.maybay[i]->soHieuMB, sohieu) == 0)
		{
			mayBay* temp = listMB.maybay[i];
			int j = i+1;
			for( j ; j < listMB.soluong; j++){
				listMB.maybay[i] = listMB.maybay[j];
				i = j;
			}
			delete temp;
			listMB.maybay[j] = NULL;
			listMB.soluong--;
			cout<<"Da xoa\n";
			break;
		}
		
	}
	
}

mayBay *SearchMB(ListMayBay lmb, char sohieu[])
{
	
	for (int i = 0; i < lmb.soluong; i++){
		if (strcmp(lmb.maybay[i]->soHieuMB, sohieu) == 0)
			return lmb.maybay[i];
	}
	return NULL;
}




void XoaMayBay(ListMayBay &lmb,listCB &list)
{
    NhapMA:
        SetColor(ColorWHITE); SetBGColor(ColorBLACK);
        //system("cls");
        frame_NhapMaMayBay(40,8);
        char soHieu[15];
        gotoxy(45, 9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE);
        string ma = nhapChuoi(45,9);
        if (ma == "exit")
            return;
        strcpy(soHieu, ma.c_str());
        strcpy(soHieu, fix_Ma(soHieu));
        int x = Check_SoHieu_MB(lmb, soHieu);
        int y =Check_MaMBinCB(list,soHieu);
        if (x == -1)
        {
            SetColor(ColorWHITE); SetBGColor(ColorBLACK);
            gotoxy(39,12); cout<<"Khong tim thay may bay nay!";
            Sleep(1000);
            gotoxy(39,12); cout<<"                            ";
            goto NhapMA;
//        }else if(Check_MaMBinCB( list,soHieu))
//              {
//              	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
//                gotoxy(39,12); cout<<"May bay da co chuyen bay!";
//                goto NhapMA;
//               } 
        
           } else {
            	if(y==1)
              {
              	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
                gotoxy(39,12); cout<<"May bay da co chuyen bay!";
                Sleep(1000);
          		gotoxy(39,12); cout<<"                            ";
                goto NhapMA;
               } 
               else {
            int i=0;
            for ( i = x; i < lmb.soluong; i++)
            {
                lmb.maybay[i] = lmb.maybay[i+1];
            }
            lmb.maybay[i+1] = NULL;
            delete lmb.maybay[i+1];
            lmb.soluong--;
            Sleep(1000);
            gotoxy(39,12); cout<<"                                 ";
            gotoxy(50,12); cout<<"Da xoa!";

                    Sleep(1000);
//                    gotoxy(boxx + 14, boxy + 10); cout<<"               ";
                    ofstream fileout;
                    fileout.open("maybay.txt", ios::out);
                    LuuFileMayBay(lmb,fileout);
            }
				}
}

void SuaMayBay(ListMayBay &lmb){
		
	NhapMA:
		//system("cls");
		frame_NhapMaMayBay(40,8);
		char soHieu[15];
		gotoxy(45, 9); SetColor(ColorPURPLE); SetBGColor(ColorWHITE);
		string ma = nhapChuoi(45,9);
		if (ma == "exit")
			return;
		strcpy(soHieu, ma.c_str());
		strcpy(soHieu, fix_Ma(soHieu));
		int x = Check_SoHieu_MB(lmb, soHieu);
		if (x == -1)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			gotoxy(40,12); cout<<"Khong tim thay chuyen bay nay!";
//			Sleep(1000);
//			gotoxy(40,12); cout<<"                                               ";
			goto NhapMA;
		}
		
		while(true)
		{
			SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			int demfield = 0;
			bool trung;
			system("cls");
			Khung_SuaMayBay();
			mayBay *mb = SearchMB(lmb, soHieu);
			gotoxy(boxx + 28, boxy + 2); cout<<mb->soHieuMB;
			gotoxy(boxx + 28, boxy + 4); cout<<mb->loaiMB;
			gotoxy(boxx + 28, boxy + 6); cout<<mb->soCho;
			gotoxy(boxx + 61, boxy + 2); cout<<mb->soHieuMB;
			
			char loai[40];
			strcpy(loai,"");
			int cho_edit = 0;
		
			do{
				   gotoxy(boxx + 61, boxy + 4); cout<<mb->loaiMB;
				   gotoxy(boxx + 61, boxy + 6);  cout<<mb->soCho;
					trung = false;
					gotoxy(boxx + 61, boxy + 4);
					string tmp = nhapChuoi(boxx + 61, boxy + 4);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(loai, tmp.c_str()); 
					strcpy(loai, fix_HoTen(loai));
					
					if (strcmp(loai, "\0") == 0)
					{
						strcpy(loai, mb->loaiMB);
						gotoxy(boxx + 61, boxy + 4);  cout<<loai;
						demfield++;
//						gotoxy(boxx + 25, boxy + 12); cout<<"Da luu loai May Bay";
//						Sleep(1000);  
//						gotoxy(boxx + 14, boxy + 10); cout<<"                 ";
						//toxy(boxx + 61, boxy + 4);  cout<<"                 ";
						trung=true;
					}
					else
					{
						demfield++;
						gotoxy(boxx + 61, boxy + 4);  cout<<"                 ";
						gotoxy(boxx + 61, boxy + 4);  cout<<loai;
						trung = true;
					}
				}while(trung == false);
				if (strcmp(loai, "") == 0) break;
				
				// NHAP SO CHO MAY BAY > SO CHO CU
				do{
				
				    
					trung = false;
					gotoxy(boxx + 61, boxy + 6);
					char cho[10];
					string tmp = nhapChuoi(boxx + 61, boxy + 6);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cho, tmp.c_str()); 
					
					strcpy(cho, fix_Ma(cho));
					if (strcmp(cho, "\0") == 0)
					{
						
						
						demfield++;
					
						cho_edit = mb->soCho;
						gotoxy(boxx + 61, boxy + 6);  cout<<cho_edit;
						trung = true;
//						gotoxy(boxx + 25, boxy + 12); cout<<"KHONG BO TRONG";
//						Sleep(1000);  
//						gotoxy(boxx + 14, boxy + 10); cout<<"               ";
//						gotoxy(boxx + 61, boxy + 6);  cout<<"               ";
					}
					else
					{
						int socho = atoi(cho);
						if (socho < mb->soCho)
						{
							gotoxy(boxx + 25, boxy + 12); cout<<"SO CHO PHAI LON HON SO CHO CU";
							Sleep(1000);  
							gotoxy(boxx + 25, boxy + 12); cout<<"                                 ";
							gotoxy(boxx + 61, boxy + 6);  cout<<"                             ";
						}
						else
						{
							demfield++;
							cho_edit = socho;
							gotoxy(boxx + 61, boxy + 6);  cout<<"                                 ";
							gotoxy(boxx + 61, boxy + 6);  cout<<cho_edit;
							trung = true;
						}
					}
			
				}while(trung == false);
				if (cho_edit == 0) break;

				if (demfield == 2)
				{
					for (int i = 0; i < lmb.soluong; i++){
						if (strcmp(lmb.maybay[i]->soHieuMB, mb->soHieuMB) == 0){
							strcpy(lmb.maybay[i]->loaiMB, loai);
							lmb.maybay[i]->soCho = cho_edit;
							
							break;
						}
					}
					
					gotoxy(boxx + 25, boxy + 12); cout<<"SUA THANH CONG";
					Sleep(1500);  
					gotoxy(boxx + 14, boxy + 10); cout<<"               ";
					ofstream fileout;
					fileout.open("maybay.txt", ios::out);
					LuuFileMayBay(lmb,fileout);
					demfield = 0;
					break;
				}
//				ofstream fileout;
//					fileout.open("maybay.txt", ios::out);
//					LuuFileMayBay(lmb,fileout);
					
		}
		
}




int Insert_MB(ListMayBay &listMB, mayBay mb)
{
	int empty = Empty_MB(listMB);
	int full = Full_MB(listMB);
	if (empty == 1)
	{
		listMB.maybay[0] = new mayBay;
 		strcpy(listMB.maybay[0]->soHieuMB, mb.soHieuMB);
 		strcpy(listMB.maybay[0]->loaiMB , mb.loaiMB);
		listMB.maybay[0]->soCho = mb.soCho;
		
		listMB.soluong = 1;
		return 1;
	}
	else if (full)
	{
		return -1;
	}
		
	else
	{
		listMB.maybay[listMB.soluong] = new mayBay;
		strcpy(listMB.maybay[listMB.soluong]->soHieuMB, mb.soHieuMB);
		strcpy(listMB.maybay[listMB.soluong]->loaiMB , mb.loaiMB);
		listMB.maybay[listMB.soluong]->soCho = mb.soCho;
		
		listMB.soluong++;
		return 1;
	}
}
void DocFileMayBay(ListMayBay &listmb)
{
	ifstream filein;
	filein.open("maybay.txt", ios::in);
	int n; // get so luong may bay
	listmb.soluong = 0;
	string tmp;
	
	filein>>n;
	
	getline(filein,tmp);
	for (int i = 0; i < n; i++)
	{
		mayBay mb;
		getline(filein, tmp, ',');
		strcpy(mb.soHieuMB, tmp.c_str());
		
		getline(filein, tmp, ',');
		strcpy(mb.loaiMB, tmp.c_str());
		
		filein >> mb.soCho;
		getline(filein, tmp);

		Insert_MB(listmb, mb);
	}
	filein.close();
}



void Xuat_MB(ListMayBay listMB)
{
	cout<<"So luong: "<<listMB.soluong<<endl;
	for (int i = 0; i < listMB.soluong; i++)
	{
		gotoxy(boxs+1,10+i);
		cout<<listMB.maybay[i]->soHieuMB<<"\t"<<listMB.maybay[i]->loaiMB<<"\t"<<listMB.maybay[i]->soCho<<endl;
	}
}

void NhapMayBay(ListMayBay &lmb)
{ 
//	int keyhit,x = 28;
	int demfield = 0;
	while (true)
	{
		if (Full_MB(lmb))
		{
			gotoxy(boxx +70, boxy+2); cout<<"SO LUONG MAY BAY DAT GIOI HAN";
			Sleep(1500);  
			gotoxy(boxx +70, boxy+2); cout<<"                             ";
			break;
		}
		else
		{
		//	system("cls");
		gotoxy(boxx + 80, boxy -7);  cout<<"                   ";
		gotoxy(boxx + 80, boxy -5);  cout<<"                    ";
		gotoxy(boxx + 80, boxy -3);  cout<<"                    ";	
//			Khung_MayBay();
			Khung_NhapMayBay();
			mayBay mb;
			//listMayBay lmb;
			strcpy(mb.soHieuMB, "");
			strcpy(mb.loaiMB, "");
			mb.soCho = 0;
			
	
				bool trung;
				// NHAP SO HIEU MAY BAY
				
				do{
				    
					fflush(stdin);
                    
					gotoxy(boxx + 80, boxy -7); 
					string tmp = nhapChuoi(boxx + 80, boxy -7);
	
					if(tmp == "exit"){
						break;
					}
					
					strcpy(mb.soHieuMB, tmp.c_str()); 
					strcpy(mb.soHieuMB, fix_Ma(mb.soHieuMB));	
					
					if (Check_SoHieu_MB(lmb, mb.soHieuMB) != -1)
					{
						gotoxy(boxx +72, boxy-1); cout<<"SO HIEU MAY BAY TRUNG!";
						Sleep(1000);  
						gotoxy(boxx +72, boxy-1); cout<<"                       ";
						gotoxy(boxx + 80, boxy -7);  cout<<"                    ";
						NhapMayBay(lmb);	
					}
					else if (strcmp(mb.soHieuMB, "\0") == 0)
					{
						gotoxy(boxx +72, boxy-1); cout<<"KHONG BO TRONG !";
						Sleep(1000);  
						gotoxy(boxx +72, boxy-1); cout<<"                  ";
						gotoxy(boxx + 80, boxy -7);  cout<<"                   ";
					}
					else
					{
						demfield++;
						gotoxy(boxx + 80, boxy -7);  cout<<"                    ";
						SetColor(ColorWHITE);
						gotoxy(boxx + 80, boxy -7); cout<<mb.soHieuMB;
						SetColor(ColorCYAN);
						trung = true;
					}	
				}while(trung == false);
	     		//gotoxy(4,2); cout<<"KQ1: "<<mb.soHieuMB;
				if (strcmp(mb.soHieuMB, "") == 0) break;
				
				// NHAP LOAI MAY BAY
				do{
					trung = false;
					gotoxy(boxx + 80, boxy -5);
					string tmp = nhapChuoi(boxx + 80, boxy -5);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(mb.loaiMB, tmp.c_str()); 
					strcpy(mb.loaiMB, fix_HoTen(mb.loaiMB));
					
					if (strcmp(mb.loaiMB, "\0") == 0)
					{
						gotoxy(boxx +72, boxy-1); cout<<"KHONG BO TRONG!";
						Sleep(1000);  
						gotoxy(boxx +72, boxy-1); cout<<"                 ";
						gotoxy(boxx + 80, boxy -5);  cout<<"                   ";
					}
					else
					{
						demfield++;
						gotoxy(boxx + 80, boxy -5);  cout<<"                  ";
						SetColor(ColorWHITE);
						gotoxy(boxx + 80, boxy -5);cout<<mb.loaiMB;
						SetColor(ColorCYAN);
						trung = true;
					}
				}while(trung == false);
				if (strcmp(mb.loaiMB, "") == 0) break;
				
	
				// NHAP SO CHO MAY BAY >20 
				do{
					trung = false;
					gotoxy(boxx + 80, boxy -3);
					char cho[10];
					string tmp = nhapSo(boxx + 80, boxy -3);
	
					if(tmp == "exit"){
						break;
					}
					strcpy(cho, tmp.c_str()); 
					
					strcpy(cho, fix_Ma(cho));
					if (strcmp(cho, "\0") == 0)
					{
						gotoxy(boxx +72, boxy-1); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(boxx +72, boxy-1); cout<<"                  ";
						gotoxy(boxx + 80, boxy -3);  cout<<"               ";
					}
					else
					{
						int check = check_Chuoi_Char(cho);
						if (check == 1)
						{
							int socho = atoi(cho);
							if (socho < 20)
							{
								gotoxy(boxx +72, boxy-1); cout<<"SO CHO IT NHAT LA 20!";
								Sleep(1000);  
								gotoxy(boxx +72, boxy-1); cout<<"                      ";
								gotoxy(boxx + 80, boxy -3);  cout<<"              ";
							}
							else
							{
								demfield++;
								mb.soCho = socho;
								gotoxy(boxx + 80, boxy -3);  cout<<"              ";
								SetColor(ColorWHITE);
							    gotoxy(boxx + 80, boxy -3);cout<<mb.soCho;
							    //SetColor(ColorCYAN);
								trung = true;
							}
						}
						else
						{
							gotoxy(boxx +72, boxy-1); cout<<"SO CHO CHI NHAN SO!";
							Sleep(1000);  
							gotoxy(boxx +72, boxy-1); cout<<"                    ";
							gotoxy(boxx + 80, boxy -3);  cout<<"           ";
						}
						
					}
			
				}while(trung == false);
				if (mb.soCho == 0) break;
				if (demfield == 3)
				{
					Insert_MB(lmb, mb);
					gotoxy(boxx +72, boxy-1); cout<<"DA THEM THANH CONG";
					Sleep(1500);  
					gotoxy(boxx +72, boxy-1); cout<<"                    ";
					demfield = 0;
				}	
		}
		
		
	}
	int a = XacNhanSaveFile();
	
	if(a == 1)
	{
		ofstream fileout;
		fileout.open("maybay.txt", ios::out);
		if(fileout.fail())
		{
			gotoxy(boxx +70, boxy-1);
		cout<<"chua mo dc ";
		}
		LuuFileMayBay(lmb,fileout);
		system("cls");
	}
}


void Danh_Sach_MayBay(ListMayBay &lmb,listCB &list)
{	
	int trang = 0, tongtrang = 0;
	if (lmb.soluong <= 8)
	{
		trang = 0;
		tongtrang = 1;
	}
	else
	{
		tongtrang = (lmb.soluong / 8.1) + 1;
	}
	while(1)
	{
	Xuat:	
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		system("cls");
		Khung_MayBay();
		HienThiTrang(tongtrang, trang, 20, 28);	
		SetColor(ColorCYAN); SetBGColor(ColorBLACK);
		gotoxy(tabx + 4, taby + 3);
		int dem = 0;
		for (int i = 0 + trang * 8; i < 8 + trang * 8 && i < lmb.soluong; i++)
		{
			SetColor(ColorWHITE);
			gotoxy(tabx + 4, taby + 3 + dem); cout <<i+1;
			gotoxy(tabx + 14, taby + 3 + dem); cout<<lmb.maybay[i]->soHieuMB;
			gotoxy(tabx + 43-strlen(lmb.maybay[i]->loaiMB)/2, taby + 3 + dem); cout <<lmb.maybay[i]->loaiMB;
			gotoxy(tabx + 68, taby + 3 + dem); cout <<lmb.maybay[i]->soCho;
			dem=dem+2;
		}
		gotoxy(40, 29);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 	
		int c = 0;
		do{
			c = getch();
		}while(c != Left && c != Right && c!= ESC && c != Insert  && c != Del && c != BACKSPACE);
		if (c == ESC)
		{
			Sleep(500);
				ofstream fileout;
				fileout.open("maybay.txt", ios::out);
				LuuFileMayBay(lmb, fileout);
				MenuInterface(lmb,list);
		}
		else if (c == Left)
		{
			if(tongtrang > 1 && trang > 0)
			{
				trang--;
				
			}
			else
			{
			trang=tongtrang-1;
			}
			goto Xuat;
		}
		else if (c == Right)
		{
			if(tongtrang > 1 && trang  + 1 < tongtrang)
			{
				trang++;
				goto Xuat;
			}
			else
			Danh_Sach_MayBay(lmb,list);
		}
		
	
		else if (c == Insert)
		{
			
			NhapMayBay(lmb);
			Sleep(500);
			goto Xuat;
		}
		else if (c == Del)
		{
			XoaMayBay(lmb,list);
			Sleep(500);
			goto Xuat;
		}
		else if (c == BACKSPACE)
		{
			SuaMayBay(lmb);
			Sleep(500);
			goto Xuat;
		}
	}	
}



//-------XUAT CHUYEN BAY





void XuatChuyenBay(int &trang,int &tongtrang,ListMayBay lmb,listCB &list){
	int soluong = list.SoLuongChuyenBay;
	if (soluong <= 6)
	{
		tongtrang = 1;
	}
	else
	{
		tongtrang = (soluong / 6.1) + 1;
	}
	clrscr();
	Khung_ChuyenBay();
	Color(ColorWHITE);
	gotoxy(1,1);cout<<"SO LUONG CHUYEN BAY: "<<soluong;
	HienThiTrang(tongtrang,trang,94,20);
	int dem = 0;
	int item = 0 + trang * 6;
	int itemtoida = 6 + trang * 6;
	gotoxy(40, 21);
	cout << "[<-] Tro lai | Tiep Theo [->]"; 
	string TrangThai[4] = {"Huy Chuyen","Con Ve","Het Ve","Hoan Tat"};
	for (nodeCB *xuat = DuyetCB(list,item); xuat != NULL; xuat=xuat->next)
		{
			if (item < itemtoida && item < soluong)
			{
				int ngay = xuat->CB.ThoiGianDi.ngay;
				int thang = xuat->CB.ThoiGianDi.thang;
				int nam = xuat->CB.ThoiGianDi.nam;
				int gio = xuat->CB.ThoiGianDi.gio;
				int phut = xuat->CB.ThoiGianDi.phut;
				
				if (Check_ThoiGian_ChuyenBay(xuat->CB.ThoiGianDi) == false)
				 	xuat->CB.TrangThai = 3;
				SetColor(ColorWHITE);
				gotoxy(tabx + 4, taby + 3 + dem*2); cout <<item+1;
				gotoxy(tabx + 14-strlen(xuat->CB.soHieuMB)/2, taby + 3 + dem*2); cout<<xuat->CB.soHieuMB;
				gotoxy(tabx + 30-strlen(xuat->CB.MaChuyenBay)/2, taby + 3 + dem*2); cout<<xuat->CB.MaChuyenBay;
				gotoxy(tabx + 42, taby + 3 + dem*2); cout <<ngay<<"/"<<thang<<"/"<<nam;
				gotoxy(tabx + 59, taby + 3 + dem*2); cout<<gio<<":"<<phut;
				gotoxy(tabx + 76-strlen(xuat->CB.SanBayDen)/2, taby + 3 + dem*2); cout <<xuat->CB.SanBayDen;
				if(xuat->CB.TrangThai==0)
				{
					gotoxy(tabx + 85, taby + 3 + dem*2); cout << TrangThai[xuat->CB.TrangThai];
				}
				else
				{
					gotoxy(tabx + 87, taby + 3 + dem*2); cout << TrangThai[xuat->CB.TrangThai];
				}
				if(xuat->CB.TrangThai!=1){
					if(xuat->CB.TrangThai==0)
					{
						gotoxy(tabx + tabs + 14,taby +3+dem*2); cout<<TrangThai[xuat->CB.TrangThai];
					}
					else
					{
						gotoxy(tabx + tabs + 15,taby +3+dem*2); cout<<TrangThai[xuat->CB.TrangThai];	
					}	
					
				}else{
				int socho = Get_socho(lmb,xuat->CB.soHieuMB);
				gotoxy(tabx + tabs + 18,taby +3+dem*2); cout<<socho-xuat->CB.TongSoDaBan;// XUAT SO VE CON LAI
				}
				dem++;
				item++;
			}
		}
}

void XuatChuyenBayTheoNgay(ListMayBay lmb,listCB list, ThoiGian tg,char noiden[])
{
	int key,tongtrang,trang =0;
	
	while(true)
	{
		KhungDanhSachCBTrongNgay();
		int soluong = CountCB_ThoiGianNoiDen(list,tg,noiden);
		gotoxy(30, 2);
		cout << "DANH SACH CHUYEN BAY TRONG NGAY "<<tg.ngay<<"/"<<tg.thang<<"/"<<tg.nam<<" "<<tg.gio<<":"<<tg.phut<<" DEN "<<noiden;
		gotoxy(1,1);cout<<"SO LUONG CHUYEN BAY: "<<soluong;
		if (soluong <= 6)
		{
			tongtrang = 1;
		}
		else
		{
			tongtrang = (soluong / 6.1) + 1;
		}		
		HienThiTrang(tongtrang,trang,94,20);
		Xuat:
		int dem = 0;
		int item = 0 + trang * 6;
		int itemtoida = 6 + trang * 6;
		gotoxy(40, 21);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 
		string TrangThai[4] = {"Huy Chuyen","Con Ve","Het Ve","Hoan Tat"};
		for (int i=0;i<6;i++) // CLEAR THONG TIN TRANG CU
		{
			gotoxy(10,7+i*2);				cout << "  ";
			gotoxy(15,7+i*2);				cout<<"          ";
			gotoxy(tabx + 22, taby + 3+i*2);cout << "                ";
			gotoxy(tabx + 40, taby + 3+i*2);cout << "             ";
			gotoxy(tabx + 58, taby + 3+i*2);cout << "          ";
			gotoxy(tabx + 70, taby + 3+i*2);cout<<"            ";
			gotoxy(tabx + tabs + 15, taby+3+i*2); cout << "         ";
			gotoxy(tabx + 85, taby + 3 +i*2); cout << "          ";
		}
		
		for (nodeCB *xuat = DuyetCB(list,item); xuat != NULL; xuat=xuat->next)
		{
			if(item < itemtoida && item < soluong)
			{
				if(CheckThoiGianNoiDen(xuat->CB,tg,noiden)==1)
				{
					int ngay = xuat->CB.ThoiGianDi.ngay;
				int thang = xuat->CB.ThoiGianDi.thang;
				int nam = xuat->CB.ThoiGianDi.nam;
				int gio = xuat->CB.ThoiGianDi.gio;
				int phut = xuat->CB.ThoiGianDi.phut;
				
				if (Check_ThoiGian_ChuyenBay(xuat->CB.ThoiGianDi) == false)
				 	xuat->CB.TrangThai = 3;
				SetColor(ColorWHITE);
				gotoxy(tabx + 4, taby + 3 + dem*2); cout <<item+1;
				gotoxy(tabx + 14-strlen(xuat->CB.soHieuMB)/2, taby + 3 + dem*2); cout<<xuat->CB.soHieuMB;
				gotoxy(tabx + 30-strlen(xuat->CB.MaChuyenBay)/2, taby + 3 + dem*2); cout<<xuat->CB.MaChuyenBay;
				gotoxy(tabx + 42, taby + 3 + dem*2); cout <<ngay<<"/"<<thang<<"/"<<nam;
				gotoxy(tabx + 59, taby + 3 + dem*2); cout<<gio<<":"<<phut;
				gotoxy(tabx + 76-strlen(xuat->CB.SanBayDen)/2, taby + 3 + dem*2); cout <<xuat->CB.SanBayDen;
				if(xuat->CB.TrangThai==0)
				{
					gotoxy(tabx + 85, taby + 3 + dem*2); cout << TrangThai[xuat->CB.TrangThai];
				}
				else
				{
					gotoxy(tabx + 87, taby + 3 + dem*2); cout << TrangThai[xuat->CB.TrangThai];
				}
				if(xuat->CB.TrangThai!=1){
					if(xuat->CB.TrangThai==0)
					{
						gotoxy(tabx + tabs + 14,taby +3+dem*2); cout<<TrangThai[xuat->CB.TrangThai];
					}
					else
					{
						gotoxy(tabx + tabs + 15,taby +3+dem*2); cout<<TrangThai[xuat->CB.TrangThai];	
					}	
					
				}else{
				int socho = Get_socho(lmb,xuat->CB.soHieuMB);
				gotoxy(tabx + tabs + 18,taby +3+dem*2); cout<<socho-xuat->CB.TongSoDaBan;// XUAT SO VE CON LAI
				}
				dem++;
				item++;	
				}
			}
		}
		key=_getch();
		switch(key)
		{
			case ESC:	
				MenuInterface(lmb,list);
				break;
			case Left:
			{
				if(tongtrang > 1 && trang > 0)
				{
					trang--;
					goto Xuat;	
				}
			}
			case Right:
			{
				if(tongtrang > 1 && trang  + 1 < tongtrang)
				{
					trang++;
					goto Xuat;	
				}
			}
		}
	}
}

void DanhSachChuyenBayTheoNgay(ListMayBay lmb,listCB list)
{
	int dem=0,xThongBao = 20, yThongBao = -10;
	KhungDanhSachCBTrongNgay();
	Khung_NhapChuyenBayTheoNgay();
	int trang = 0, tongtrang = 0;
	bool trung = false;
	char noiden[150];
	ThoiGian tg;
	
	
	strcpy(noiden,"");
	while(true)
	{
		tg.nam = -1;
		tg.thang = -1;
		tg.ngay = -1;
		tg.gio = 23;
		tg.phut = 59;
		int ngayBay= -1;
		gotoxy(box2x + 28, box2y - 6);cout<<"                    ";
		gotoxy(box2x + 28, box2y - 4);cout<<"  /  /     ";
		do{
		// NHAP SAN BAY DEN	
		gotoxy(box2x + 28, box2y - 6); 
		string tmp = nhapChuoi(box2x + 28, box2y - 6);
		if(tmp == "exit"){
			break;
		}
		strcpy(noiden, tmp.c_str()); 
		strcpy(noiden, fix_HoTen(noiden));	
		if (!strcmp(noiden,"\0"))
		{
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG !";
			Sleep(1000);  
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                 ";
			gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
		}
		else if (Check_NoiDen(list,noiden))
		{
			gotoxy(box2x + 28, box2y - 6);cout<<noiden;
			dem++;
			trung = true;
		}
		else
		{
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG CO CHUYEN BAY DEN SAN BAY NAY";
			Sleep(1000);  
			gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                    ";
			gotoxy(box2x + 28, box2y - 6);  cout<<"                                 ";
		}
		}while(trung==false);
		if(!strcmp(noiden,""))break;
		
		do
		{
			// NHAP NGAY 
			NhapNgay:
			gotoxy(xNgay+2, yNgay-2);cout<<"/";
			gotoxy(xNgay+5, yNgay-2);cout<<"/";	
			trung = false;	
			char ngay[10];
			gotoxy(box2x + 28, box2y - 4);
			string tmp = nhapSo(box2x + 28, box2y - 4);
			gotoxy(xNgay+2, yNgay-2);cout<<"/";
			gotoxy(xNgay+5, yNgay-2);cout<<"/";
			if(tmp == "exit"){
				break;
			}
			strcpy(ngay, tmp.c_str()); 
			strcpy(ngay, fix_Ma(ngay));
			if (strcmp(ngay, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                               ";
						gotoxy(xNgay, yNgay-2);  cout<<"  ";
					}
					else
					{
						int check = check_Chuoi_Char(ngay);
						if (check == 1)
						{
							ngayBay = atoi(ngay);
							if (ngayBay <= 0 || ngayBay > 31 )
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
								gotoxy(xNgay, yNgay-2);  	cout<<"  ";
							}
							else 
							{
								tg.ngay = ngayBay;
								gotoxy(box2x + 28, yNgay-2);  	cout<<"  ";
								gotoxy(xNgay, yNgay-2);	cout<<tg.ngay;
								dem++;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
							gotoxy(xNgay, yNgay-2);  cout<<"  ";
						}
					}
		}while(trung==false);
		if(tg.ngay==-1)break;
		// NHAP THANG
				do{
					trung = false;
					gotoxy(xNgay+3, yNgay-2);
					char thang[10];
					string tmp = nhapSo(xNgay+3, yNgay-2);
					gotoxy(xNgay+2, yNgay-2);cout<<"/";
					gotoxy(xNgay+5, yNgay-2);cout<<"/";
	
					if(tmp == "exit"){
						break;
					}
					strcpy(thang, tmp.c_str()); 
					strcpy(thang, fix_Ma(thang));
					if (strcmp(thang, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(xNgay+3, yNgay-2);  cout<<"  ";
					}
					else
					{
						if (check_Chuoi_Char(thang))
						{
							int thangBay = atoi(thang);
							if (thangBay <= 0 || thangBay > 12)
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THANG KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                        ";
								gotoxy(xNgay+3, yNgay-2);  	cout<<"  ";
							}
							else
							{
								tg.thang = thangBay;
								gotoxy(xNgay+3, yNgay-2);  	cout<<"  ";
								gotoxy(xNgay+3, yNgay-2);	cout<<tg.thang;
								dem++;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                   ";
							gotoxy(xNgay+3, yNgay-2);  cout<<"  ";
						}
					}
				}while(trung == false);
				if (tg.thang == -1) break;
				// NHAP NAM
				do{
					trung = false;
					gotoxy(xNgay+6, yNgay-2);
					char nam[10];
					string tmp = nhapSo(xNgay+6, yNgay-2);
					gotoxy(xNgay+2, yNgay-2);cout<<"/";
					gotoxy(xNgay+5, yNgay-2);cout<<"/";
	
					if(tmp == "exit"){
						break;
					}
					strcpy(nam, tmp.c_str()); 
					
					strcpy(nam, fix_Ma(nam));
					if (strcmp(nam, "\0") == 0)
					{
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG BO TRONG";
						Sleep(1000);  
						gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                                ";
						gotoxy(xNgay+6, yNgay-2);  cout<<"    ";
					}
					else
					{
						int check = check_Chuoi_Char(nam);
						if (check == 1)
						{
							int namBay = atoi(nam);
							if (namBay < 2019&&namBay!=0)
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NAM BAY >= 2019!";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                 ";
								gotoxy(xNgay+6, yNgay-2);  	cout<<"    ";
							}
							else if ( !Check_Date(namBay, tg.thang, ngayBay))
							{
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"NGAY KHONG HOP LE ";
								Sleep(1000);  
								gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
								gotoxy(xNgay, yNgay-2); cout<<"          ";
								goto NhapNgay;
							}
							else
							{
								tg.nam = namBay;
								gotoxy(xNgay+6, yNgay-2);  	cout<<"    ";
								gotoxy(xNgay+6, yNgay-2);	cout<<tg.nam;
								dem++;
								trung = true;
							}
						}
						else
						{
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"KHONG DUOC CO CHU!";
							Sleep(1000);  
							gotoxy(box2x + xThongBao, box2y + yThongBao); cout<<"                  ";
							gotoxy(xNgay+6, yNgay);  cout<<"    ";
						}
						
					}
			
				}while(trung == false);
				if (tg.nam == -1) break;
		
				if (!Check_ThoiGian_ChuyenBay(tg))
				{
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"THOI GIAN CUA BAN DA QUA HAN";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                ";
					continue;
				}
				if(dem==4)
				{
					for (nodeCB *check=list.Head;check!=NULL;check = check->next)
					{
						if(CheckThoiGianNoiDen(check->CB,tg,noiden)==1)
						{
							XuatChuyenBayTheoNgay(lmb,list,tg,noiden);
							break;
						}
					}
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"HIEN TAI KHONG CO CHUYEN BAY PHU HOP";
					Sleep(1000);  
					gotoxy(box2x + xThongBao, box2y + yThongBao); 	cout<<"                                    ";
				}
				
	}
	MenuInterface(lmb,list);
	
}


//-------------------------------MENU CHUYEN BAY
void Updatetrang(int &trang,int &tongtrang,listCB list){
	int soluong = list.SoLuongChuyenBay;
	
	if (soluong <= 6)
	{
		tongtrang = 1;
	}
	else
	{
		tongtrang = (soluong / 6.1) + 1;
		if (trang >= tongtrang)
		{
			trang--;
		}
	}
}




void MenuChuyenBay(ListMayBay lmb,listCB &list){

	
	int trang = 0, tongtrang = 0;
	int key;
	XuatChuyenBay(trang,tongtrang,lmb,list);
	SetColor(ColorCYAN);
	gotoxy(7,27);cout<<char(176)<<"DI CHUYEN:  LEFT, RIGHT";
	gotoxy(7,29);cout<<char(176)<<"THEM: INSERT| XOA : DELETE| HUY: ESC";
	gotoxy(7,30);cout<<char(176)<<"F1: HUY CHUYEN |F2: LUU FILE";
	while(true)
	{
			while(kbhit())
			{
				key=_getch();
				switch(key)
				{
				case ESC:	
					MenuInterface(lmb,list);
					break;
				case Left:
				{
					if(tongtrang > 1 && trang > 0)
					{
						trang--;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Right:
				{
					if(tongtrang > 1 && trang  + 1 < tongtrang)
					{
						trang++;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Insert:
					NhapChuyenBay(lmb,list);
					XuatChuyenBay(trang,tongtrang,lmb,list);
					break;
				
				case Home:
					SuaChuyenBay(lmb,list);
					XuatChuyenBay(trang,tongtrang,lmb,list);
					break;
				case Del:
					XoaChuyenBay(lmb,list);
					Updatetrang(trang,tongtrang,list);
					XuatChuyenBay(trang,tongtrang,lmb,list);
					break;
				case F2:
					XacNhanSaveFile();
					LuuFileChuyenBay(list,lmb);
					XuatChuyenBay(trang,tongtrang,lmb,list);
					break;
				case F1:
					HuyChuyenBay(lmb,list);
					LuuFileChuyenBay;
					XuatChuyenBay(trang,tongtrang,lmb,list);
				default:
					break;
				}
//				
			}
	}
}


//DAT VE MAY BAY

void NhapVeMB(ListMayBay lmb,listCB &list,NODPTR tree,char cmnd[16], char *MaChuyenBayCanTim,bool Booked)
{
	int xThongBao= 80, yThongBao =8,vitri=0;
	char input[3];
	string temp;
	nodeCB *cb =  Search_MaCB(list,MaChuyenBayCanTim);
	mayBay *mb = SearchMB(lmb,cb->CB.soHieuMB);
	Node_HK *hk = SearchHK(tree,cmnd);
	//XUAT THONG TIN
	XuatThongTin:
	Khung_DatVe();
	XuatDSVe(cb->CB,mb->soCho);
	Color(ColorYELLOW);
	gotoxy(36,1);cout<<cb->CB.MaChuyenBay;
	gotoxy(64,1);cout<<cb->CB.SanBayDen;
	gotoxy(90,1);cout<<cb->CB.ThoiGianDi.ngay<<"/"<<cb->CB.ThoiGianDi.thang<<"/"<<cb->CB.ThoiGianDi.nam<<"  "<<cb->CB.ThoiGianDi.gio<<":"<<cb->CB.ThoiGianDi.phut;
	gotoxy(25,3); cout<<hk->HK.ho<<" "<<hk->HK.ten;
	gotoxy(31,6); cout<<mb->loaiMB;
	gotoxy(78,6);cout<<mb->soCho;

	
	
	if(Booked==true){
		Color(ColorCYAN);
		gotoxy(16, 8); cout <<"SO VE CUA BAN: ";
		Color(ColorYELLOW);
		int View = vitri; // XAC DINH KHACH XEM LAI VE HAY DAT VE
		vitri = SearchVeHK(list,lmb,MaChuyenBayCanTim,cmnd);
		cout<<vitri;
		
		while(getch()!=ESC){
		}
		if(View!=0)
		{
			if(cb->CB.TongSoDaBan==mb->soCho)
			cb->CB.TrangThai=2;
			if(XacNhanSaveFile()){
			LuuFileChuyenBay(list,lmb);
			}
		}
		return;
	}
	
		NhapVe:
		gotoxy(31,8);cout<<"    ";
		strcpy(input,"");
		gotoxy(31,8);
		Color(ColorYELLOW);
		temp = nhapSo(31,8);
		strcpy(input, temp.c_str());
		strcpy(input, fix_Ma(input));
		Color(ColorCYAN);
		if (strcmp(input, "\0") == 0)
		{
			gotoxy(xThongBao, yThongBao); cout << "VUI LONG NHAP SO VE";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout << "                   ";
			goto NhapVe;
		}
		else if (temp == "exit")
		{
			return;
		}
		else if(check_Chuoi_Char(input)==1)
		{
			vitri = atoi(input);
			if(vitri<=0||vitri>mb->soCho)
			{
				gotoxy(xThongBao, yThongBao); cout << "SO VE KHONG HOP LE";
				gotoxy(xThongBao, yThongBao+1); cout << "0 < SO VE < SO CHO";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "                   ";
				gotoxy(xThongBao, yThongBao+1);cout<<"                     ";
				goto NhapVe;
			}
			else if(strcmp(cb->CB.DsVe[vitri].cmnd,"\0")!=0)
			{
				gotoxy(xThongBao, yThongBao); cout << "VE DA CO NGUOI DAT VUI LONG CHON LAI";
				Sleep(1000);
				gotoxy(xThongBao, yThongBao); cout << "                                     ";
				goto NhapVe;
			}
			else
			{
				
				if(XacNhanDatVe(vitri)==1)
				{					
					if(InsertVe(cb->CB,vitri,cmnd)==0){
						gotoxy(xThongBao, yThongBao);cout<<"DAT VE KHONG THANH CONG";
						Sleep(1000);
						gotoxy(xThongBao, yThongBao);cout <<"                      ";	
					}
					else{
					Color(ColorCYAN);
					gotoxy(55, 8);cout<<"DAT VE THANH CONG";
					Sleep(1000);
					gotoxy(xThongBao, yThongBao); cout << "                  ";
					Booked = true;	// HANH KHACH DA~ DAT VE
					}
				}
				clrscr();
				goto XuatThongTin;	
			}
		}
		else
		{
			gotoxy(xThongBao, yThongBao); cout << "SO VE KHONG HOP LE";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout << "                   ";
			goto NhapVe;	
		}
}



void DatVeMB(ListMayBay lmb,listCB list){
	KhungNhapCMND();
	char cmnd[16];
	bool Booked = false;
	string temp;
	char chuyenbay[15];
	int xThongBao = 56, yThongBao = 24;
	NhapCMND:
		gotoxy(box2x+22,box2y-3);
		fflush(stdin);
		temp = nhapChuoi(box2x+22,box2y-3);	
		strcpy(cmnd, temp.c_str());
		strcpy(cmnd, fix_Ma(cmnd));
		if(!strcmp(cmnd,""))
		{
			if(XacNhanTaoHanhKhach()==1)
			{
					NhapHanhKhach(tree);	
					clrscr();
					return;
			}
			return;
		}
		else if(temp=="exit")
		{
			return;
		}
		else if(strlen(cmnd)!=9)
		{
		gotoxy(xThongBao, yThongBao); cout << "CMND khong hop le, moi nhap lai!";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao); cout << "                                           ";
		gotoxy(box2x+22,box2y-3);cout<<"                        ";
		goto NhapCMND;
		}
		else if(SearchHK(tree,cmnd)==NULL)
		{
			gotoxy(xThongBao, yThongBao); cout << "CMND khong dung, moi nhap lai!";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout << "                                           ";
			gotoxy(box2x+22,box2y-3);cout<<"                        ";
			goto NhapCMND;
		}
		else
		{
			gotoxy(box2x+22,box2y-3);cout<<cmnd;
		}
	NhapChuyenBay:
		gotoxy(box2x+22,box2y-1);cout<<"                          ";
		gotoxy(xThongBao, yThongBao);cout << "                                       ";
		gotoxy(box2x+22, box2y - 1);
		temp = nhapChuoi(box2x+22, box2y - 1);	
		strcpy(chuyenbay, temp.c_str());
		strcpy(chuyenbay, fix_Ma(chuyenbay));
		if(strcmp(chuyenbay,"")==0)
		{
			gotoxy(xThongBao, yThongBao); cout <<"VUI LONG NHAP MA CHUYEN BAY";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout <<"     			              ";
			goto NhapChuyenBay;
		}
		else if(temp=="exit"){
			return;
		}
		else if(Check_MaCB(list,chuyenbay)==-1)
		{
			gotoxy(xThongBao, yThongBao);cout << "MA CHUYEN BAY KHONG TON TAI";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout << "                            ";
			goto NhapChuyenBay;
		}
		else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==0)
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA BI HUY";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout << "                            ";
			goto NhapChuyenBay;
		}
		else if(CheckHKtrongCB(list,lmb,chuyenbay,cmnd))
		{
			gotoxy(xThongBao, yThongBao);cout << "BAN DA DAT VE TRONG CHUYEN BAY NAY ROI";
			Sleep(1500);
			gotoxy(xThongBao, yThongBao);cout << "                                       ";
			Booked = true;
			Khung_DatVe();
			NhapVeMB(lmb,list,tree,cmnd,chuyenbay,Booked);
		}
		else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==3)
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HOAN TAT";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout << "                            ";
			goto NhapChuyenBay;
		}
		else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==2)
		{
			gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HET VE";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao);cout << "                            ";
			goto NhapChuyenBay;
		}
		else
		{
			Khung_DatVe();
			NhapVeMB(lmb,list,tree,cmnd,chuyenbay,Booked);
		}
}

void XemVeMB(ListMayBay lmb,listCB list,char *MaChuyenBayCanTim)
{
	nodeCB *cb =  Search_MaCB(list,MaChuyenBayCanTim);
	mayBay *mb = SearchMB(lmb,cb->CB.soHieuMB);
	//XUAT THONG TIN
	XuatThongTin:
	Khung_XemVe();
	gotoxy(5,3);cout<<"SO VE CON TRONG: ";SetColor(ColorYELLOW);cout<<mb->soCho-cb->CB.TongSoDaBan;
	XuatDSVe(cb->CB,mb->soCho);
	Color(ColorYELLOW);
	gotoxy(36,1);cout<<cb->CB.MaChuyenBay;
	gotoxy(64,1);cout<<cb->CB.SanBayDen;
	gotoxy(90,1);cout<<cb->CB.ThoiGianDi.ngay<<"/"<<cb->CB.ThoiGianDi.thang<<"/"<<cb->CB.ThoiGianDi.nam<<"  "<<cb->CB.ThoiGianDi.gio<<":"<<cb->CB.ThoiGianDi.phut;
}
int Huy1vemb(ListMayBay lmb,ChuyenBay &cb,char cmnd[15])
{
	int socho = Get_socho(lmb,cb.soHieuMB);
	for (int i = 1; i<=socho;i++)
	{
		if(strcmp(cb.DsVe[i].cmnd,cmnd)==0)
		{
			if(cb.TrangThai==2)
			{
				cb.TrangThai = 1; // HET VE -> CON VE
			}
			
			cb.TongSoDaBan--;
			strcpy(cb.DsVe[i].cmnd,"");
			return i;
		}
	}
	return 0;
}

void HuyVeMB(ListMayBay lmb,listCB list)
{
	string temp;
	char chuyenbay[15];
	int xThongBao = 65, yThongBao = 28;
	KhungNhapMaCB(60,25);
	NhapChuyenBay:
	gotoxy(65,26);
	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
	cout<<"                      ";
	gotoxy(65,26);
	temp = nhapChuoi(65,26);	
	strcpy(chuyenbay, temp.c_str());
	strcpy(chuyenbay, fix_Ma(chuyenbay));
	if(strcmp(chuyenbay,"")==0)
	{
		gotoxy(xThongBao, yThongBao); cout <<"VUI LONG NHAP MA CHUYEN BAY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao); cout <<"     			                ";
		goto NhapChuyenBay;
	}
	else if(temp=="exit"){
		return;
	}
	else if(Check_MaCB(list,chuyenbay)==-1)
	{
		gotoxy(xThongBao, yThongBao);cout << "MA CHUYEN BAY KHONG TON TAI";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout << "                              ";
		goto NhapChuyenBay;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==3)
	{
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HOAN TAT";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		goto NhapChuyenBay;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==0)
	{
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA BI HUY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		goto NhapChuyenBay;
	}
	else
	{
		int xThongBao = 52,yThongBao = 5;
		XemVeMB(lmb,list,chuyenbay);
		KhungNhap1CMND(44,6);
		NhapCMND:           // NHAP CMND
		gotoxy(49,7);
		fflush(stdin);
		char cmnd[15];
		SetBGColor(ColorWHITE); SetColor(ColorBLACK);
		string temp = nhapChuoi(49,7);	
		strcpy(cmnd, temp.c_str());
		strcpy(cmnd, fix_Ma(cmnd));
		SetBGColor(ColorBLACK);SetColor(ColorWHITE);
		if(!strcmp(cmnd,""))
		{
			gotoxy(xThongBao, yThongBao); cout << "  VUI LONG NHAP CMND  ";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout << "                         ";
			gotoxy(49,7);cout<<"                        ";
			goto NhapCMND;
		}
		else if(temp=="exit")
		{
			return;
		}
		else if(strlen(cmnd)!=9)
		{
		gotoxy(xThongBao, yThongBao); cout << "CMND khong hop le, moi nhap lai!";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao); cout << "                                           ";
		gotoxy(49,7);cout<<"                        ";
		goto NhapCMND;
		}
		else if(CheckHKtrongCB(list,lmb,chuyenbay,cmnd)!=1)
		{
			gotoxy(xThongBao, yThongBao); cout << "CMND khong co ve trong chuyen bay nay!";
			Sleep(1000);
			gotoxy(xThongBao, yThongBao); cout << "                                           ";
//			gotoxy(box2x+22,box2y-3);cout<<"                        ";
			goto NhapCMND;
		}
		else
		{
			if(XacNhanXoa())
			{
				XemVeMB(lmb,list,chuyenbay);
				nodeCB *cb;
				cb = Search_MaCB(list,chuyenbay) ;
				int del = Huy1vemb(lmb,cb->CB,cmnd);
				InVeBiHuy(del);
				Sleep(1000);
				if(XacNhanSaveFile())
				{
					LuuFileChuyenBay(list,lmb);
				} 	
			}
		}
		
	}
	MenuInterface(lmb,list);
}

void MenuHuyVe(ListMayBay lmb,listCB list){
	int trang = 0, tongtrang = 0;
	int key;
	XuatChuyenBay:
	XuatChuyenBay(trang,tongtrang,lmb,list);
	while(true)
	{
			while(kbhit())
			{
				key=_getch();
				switch(key)
				{
				case ESC:	
					MenuInterface(lmb,list);
					break;
				case Left:
				{
					if(tongtrang > 1 && trang > 0)
					{
						trang--;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Right:
				{
					if(tongtrang > 1 && trang  + 1 < tongtrang)
					{
						trang++;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Insert:
					HuyVeMB(lmb,list);
					goto XuatChuyenBay;
					break;
				default:
					break;
				}
			}
	}
}

void InputChuyenBay(ListMayBay lmb,listCB list)
{
	string temp;
	char chuyenbay[15];
	int xThongBao = 63, yThongBao = 28;
	KhungNhapMaCB(60,25);
	NhapChuyenBay:
	gotoxy(65,26);
	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
	cout<<"                      ";
	gotoxy(65,26);
	temp = nhapChuoi(65,26);	
	strcpy(chuyenbay, temp.c_str());
	strcpy(chuyenbay, fix_Ma(chuyenbay));
	if(strcmp(chuyenbay,"")==0)
	{
		gotoxy(xThongBao, yThongBao); cout <<"VUI LONG NHAP MA CHUYEN BAY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao); cout <<"     			                ";
		goto NhapChuyenBay;
	}
	else if(temp=="exit"){
		return;
	}
	else if(Check_MaCB(list,chuyenbay)==-1)
	{
		gotoxy(xThongBao, yThongBao);cout << "MA CHUYEN BAY KHONG TON TAI";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout << "                              ";
		goto NhapChuyenBay;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==3)
	{
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA HOAN TAT";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		goto NhapChuyenBay;
	}
	else if(Search_MaCB(list,chuyenbay)->CB.TrangThai==0)
	{
		gotoxy(xThongBao, yThongBao);cout << "CHUYEN BAY DA BI HUY";
		Sleep(1000);
		gotoxy(xThongBao, yThongBao);cout <<"                            ";
		goto NhapChuyenBay;
	}
	else
	{
		XemVeMB(lmb,list,chuyenbay);
		while(getch()!=ESC);
	}
	

}
	
void NhapHanhKhach(NODPTR &tree)
{   
	int  x = 28;
	int demfield = 0;
	char cmnd[16];
	fflush(stdin);
	Khung_NhapHanhKhach();
	HanhKhach hk;
	string temp;
	NhapCMND:
	fflush(stdin);
	gotoxy(boxx + 28, boxy + 2) ;
    temp = nhapChuoi(boxx + 28, boxy + 2);
    strcpy(cmnd, temp.c_str());
    strcpy(cmnd, fix_Ma(cmnd));
    if(strcmp(cmnd,"")==0)
	{
	    gotoxy(boxx + 14, boxy + 12); cout << "KHONG DUOC DE TRONG";
	    Sleep(1000);
	    gotoxy(boxx + 14, boxy + 12); cout << "                                           ";
	    gotoxy(box2x+22,box2y-3);cout<<"                        ";
	    goto NhapCMND;
    }
    else if(strlen(cmnd)!=9)
	{
	    gotoxy(boxx + 14, boxy + 12); cout << "CMND khong hop le, moi nhap lai!";
	    Sleep(1000);
	    gotoxy(boxx + 14, boxy + 12); cout << "                                           ";
	    gotoxy(boxx + 28, boxy + 2);cout<<"                        ";
	    goto NhapCMND;
    }
    else if(SearchHK(tree,cmnd)!=NULL)
	{
		gotoxy(boxx + 14, boxy + 12); cout << "BAN DA LA HANH KHACH!";
	    Sleep(1000);
	    gotoxy(boxx + 14, boxy + 12); cout << "                                           ";
	    gotoxy(boxx + 28, boxy + 2);cout<<"                        ";
	    return;
	}       
	strcpy(hk.cmnd,  cmnd);
	strcpy(hk.ho,  "");
	strcpy(hk.ten,  "");
	strcpy(hk.phai,  "");
	gotoxy(boxx + 28, boxy + 2);  cout<<"                                 ";
	gotoxy(boxx + 28, boxy + 2);cout<<hk.cmnd;
	bool trung;
	
//	if (strcmp(hk.cmnd, "") == 0) break;
	
	
	// NHAP HO
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 4);
		string tmp = nhapChuoi(boxx + 28, boxy + 4);
		if(tmp == "exit"){
			break;
		}
		strcpy(hk.ho, tmp.c_str());
		strcpy(hk.ho, fix_HoTen(hk.ho));
		
		if (strcmp(hk.ho, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
		}
		else if(check_number(tmp) )
		{
		gotoxy(boxx + 14, boxy + 12); cout<<"CHI DUOC NHAP CHU!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
		}
		else
		{
			demfield++;
			gotoxy(boxx + 28, boxy + 4);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 4);cout<<hk.ho;
			trung = true;
		}
	}while(trung == false);
//	if (strcmp(hk.ho, "") == 0) break;
	
	// NHAP TEN
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 6);
		string tmp = nhapChuoi(boxx + 28, boxy + 6);
		if(tmp == "exit"){
			break;
		}
		strcpy(hk.ten, tmp.c_str());
		strcpy(hk.ten, fix_Ten(hk.ten));
		
		if (strcmp(hk.ten, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
		}
		else if(check_number(tmp))
		{
		gotoxy(boxx + 14, boxy + 12); cout<<"CHI DUOC NHAP CHU!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
			}
		else
		{
			demfield++;
			gotoxy(boxx + 28, boxy + 6);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 6);cout<<hk.ten;
			trung = true;
		}
	}while(trung == false);
	//if (strcmp(hk.ten, "") == 0) break;
	
	// NHAP PHAI (NAM/NU)
	do{
		trung = false;
		gotoxy(boxx + 28, boxy + 8);
		char phai[10];
		string tmp = nhapChuoi(boxx + 28, boxy + 8);
		if(tmp == "exit"){
			break;
		}
		char temp[10];
		strcpy(temp, tmp.c_str());
		strcpy(phai, fix_GioiTinh(temp));
		if (strcmp(phai, "\0") == 0)
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG BO TRONG!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                ";
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                ";
		}
		else if ((strncmp(phai, "nam", 3) == 0 ) || (strncmp(phai, "nu", 2) == 0) )
		{
			demfield++;
			strcpy(hk.phai, phai);
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                 ";
			gotoxy(boxx + 28, boxy + 8);cout<<hk.phai;
			trung = true;
		}
		else
		{
			gotoxy(boxx + 14, boxy + 12); cout<<"KHONG DUNG YEU CAU!";
			Sleep(1000);  
			gotoxy(boxx + 14, boxy + 12); cout<<"                                ";
			gotoxy(boxx + 28, boxy + 8);  cout<<"                                ";
			
		}
	}while(trung == false);
//	if (strcmp(hk.phai, "") == 0) break;
	
	if (demfield == 3)
	{
		gotoxy(boxx + 14, boxy + 11); cout<<"DA THEM THANH CONG HANG KHACH";
		InsertHKToTree(tree, hk);
		Sleep(1500);  
		gotoxy(boxx + 14, boxy + 11); cout<<"                             ";
		demfield = 0;
	}
		
	int a = XacNhanSaveFile();
	if(a == 1)
	{
		LuuFileHKKoDeQuy(tree);
	}
}

void Danh_Sach_Thong_Ke_So_Luot_Bay(listCB lcb, ListMayBay lmb)
{
	int trang = 0, tongtrang = 0;
	if (lmb.soluong <= 8)
	{
		trang = 0;
		tongtrang = 1;
	}
	else
	{
		tongtrang = (lmb.soluong / 8.1) + 1;
	}
	string sh[lmb.soluong]; // mang chua so Hieu
	int soluot[lmb.soluong]; // mang chua so luot
	string loai[lmb.soluong];//mang chua loai 
	int index = 0;
	
	for(int i = 0; i < lmb.soluong; i++)
	{
		sh[index] = string(lmb.maybay[i]->soHieuMB);
		loai[index] = string(lmb.maybay[i]->loaiMB);
		soluot[index] = Dem(lcb,lmb.maybay[i]->soHieuMB);
		index++;
	}
	
	for (int i = 0; i < lmb.soluong-1; i++){
		for (int j = lmb.soluong - 1; j > i; j--){
			if (soluot[j-1] < soluot[j]){
				int m = soluot[j-1];
				string n = sh[j-1];
				
				soluot[j-1] = soluot[j];
				sh[j-1] = sh[j];
				
				soluot[j] = m;
				sh[j] = n;
			}
		}
	}
	
	while(1)
	{
		Xuat:
			system("cls");
			//SetColor(ColorWHITE);
		//	SetBGColor(ColorBLACK);
			Khung_DS_Thong_Ke_So_Luot_Bay();
			HienThiTrang(tongtrang, trang, 27, 28);
		//SetColor(ColorBLACK);
			//ButtonESC(ColorDARKWHITE);
		//	SetColor(ColorWHITE); SetBGColor(ColorBLACK);
			
			gotoxy(tabx + 30, taby + 3);
			int dem = 0;
 			for (int i = 0 + trang * 8; i < 8 + trang * 8 && i < lmb.soluong; i++) 
			{
				SetColor(ColorWHITE);
				gotoxy(tabx +15, taby + 3 + dem); cout <<i+1;
				gotoxy(tabx + 30, taby + 3 + dem); cout<<sh[i];
				gotoxy(tabx + 53, taby + 3 + dem); cout<<loai[i];
				gotoxy(tabx + 79, taby + 3 + dem); cout<<soluot[i];
				dem=dem+2;
			}
			
			gotoxy(50, 29);
			cout << "[<-] Tro lai | Tiep Theo [->]"; 
			
			int c = 0;
			do{
				c = getch();
			}while(c != Left && c != Right && c != ESC);
			 if (c == Left)
			{
				if(tongtrang > 1 && trang > 0)
				{
					trang--;
					goto Xuat;
				}
				else
				{
					trang=tongtrang-1;
				}
			}
			else if (c == Right)
			{
				if(tongtrang > 1 && trang  + 1 < tongtrang)
				{
					trang++;
					goto Xuat;
				}
				else
			Danh_Sach_Thong_Ke_So_Luot_Bay(lcb,lmb);
			}
			else if (c == ESC)
			{
				clrscr();
			    MenuInterface(lmb,lcb);
			    break;
			}
			
	}
}

//---------------------------CHECK HANH KHACH TRONG CHUYEN BAY---------------------------		

int SearchVeHK(listCB list,ListMayBay lmb,char MaCB[],char cmnd[]){
	ChuyenBay cb;
	int socho;
	cb = Search_MaCB(list,MaCB)->CB;
	socho = Get_socho(lmb,cb.soHieuMB);
	
	for(int dem= 1;dem <= socho;dem++)
	{
		if(!strcmp(cb.DsVe[dem].cmnd,cmnd )){
			return dem;
		}
	}
	return 0;
	
}

int CheckHKtrongCB(listCB list,ListMayBay lmb,char MaCB[],char cmnd[])
{
	ChuyenBay cb;
	int socho;
	cb = Search_MaCB(list,MaCB)->CB;
	socho = Get_socho(lmb,cb.soHieuMB);
	for(int dem= 1;dem <= socho;dem++)
	{
		if(!strcmp(cb.DsVe[dem].cmnd,cmnd)){
			return 1;
		}
	}
	return 0;
}

int CheckDSVe(listCB list,ListMayBay lmb,char MaCB[])
{
	ChuyenBay cb;
	int socho;
	cb = Search_MaCB(list,MaCB)->CB;
	socho = Get_socho(lmb,cb.soHieuMB);
	for(int dem= 1;dem <= socho;dem++)
	{
		if(strcmp(cb.DsVe[dem].cmnd,"") ){
			return 1;
		}
	}
	return 0;
}	

void MenuDatVeMB(ListMayBay lmb,listCB list){
	int trang = 0, tongtrang = 0;
	int key;
	XuatChuyenBay:
	XuatChuyenBay(trang,tongtrang,lmb,list);
	while(true)
	{
			while(kbhit())
			{
				key=_getch();
				switch(key)
				{
				case ESC:	
					MenuInterface(lmb,list);
					break;
				case Left:
				{
					if(tongtrang > 1 && trang > 0)
					{
						trang--;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Right:
				{
					if(tongtrang > 1 && trang  + 1 < tongtrang)
					{
						trang++;
						XuatChuyenBay(trang,tongtrang,lmb,list);
					}
					break;
				}
				case Insert:
//					KhungNhapCMND();
					DatVeMB(lmb,list);
					goto XuatChuyenBay;
					break;
				default:
					break;
				}
			}
	}
}

void DanhSachVeTrongCB(ListMayBay lmb,listCB list)
{

	int trang = 0, tongtrang = 0;
	int key;
	XuatChuyenBay:
	XuatChuyenBay(trang,tongtrang,lmb,list);
	SetColor(ColorCYAN);
	gotoxy(7,27);cout<<char(176)<<"DI CHUYEN:  LEFT, RIGHT";
	gotoxy(7,29);cout<<char(176)<<"NHAP MA CHUYEN BAY: INSERT | HUY: ESC            ";
	gotoxy(6,30);cout<<"                    ";
	while(true)
	{
			while(kbhit())
			{
				key=_getch();
				switch(key)
				{
				case ESC:	
					MenuInterface(lmb,list);
					break;
				case Left:
				{
					if(tongtrang > 1 && trang > 0)
					{
						trang--;
						goto XuatChuyenBay;
					}
					break;
				}
				case Right:
				{
					if(tongtrang > 1 && trang  + 1 < tongtrang)
					{
						trang++;
						goto XuatChuyenBay;
					}
					break;
				}
				case Insert:
					InputChuyenBay(lmb,list);
					goto XuatChuyenBay;
					break;
				default:
					break;
				}
			}
	}
}

void Danh_Sach_HK_Trong_CB(listCB &list, ListMayBay lmb)
{

	int stt;
	int trang = 0, tongtrang = 0;
	char maCB[15];
	strcpy(maCB, "");
	nodeCB *pNodeCB ;
	bool flag = false;
	while(flag == false)
	{
		NhapLai:
		system("cls");
		Khung_DS_HK_Trong_CB();
		gotoxy(70,2);
		SetColor(ColorWHITE);
		string ma = nhapChuoi(70,2);
		if (ma == "exit")MenuInterface(lmb,list);
		strcpy(maCB, ma.c_str());
		strcpy(maCB, fix_Ma(maCB)); // chua xet TH rong, ko co ma CB
		gotoxy(70,2); cout<<"                    ";
		gotoxy(70,2); cout<<maCB;
		
		if (strcmp(maCB, "\0") == 0)
		{
			gotoxy(35,28); cout <<"Khong bo trong";
			Sleep(1500);
			gotoxy(35,28); cout <<"					";
			goto NhapLai;
		}
		int x = Check_MaCB(list, maCB);
		if (x == -1){
			gotoxy(35,28); cout <<"Ma Chuyen Bay khong ton tai!	";
			Sleep(1500);
			gotoxy(35,28); cout <<"								";
			goto NhapLai;
		}else if (x == 1){
			pNodeCB = Search_MaCB(list,maCB);
			flag = true;
		}
//		
//		gotoxy(44,3); cout<<pNodeCB->CB.ThoiGianDi.ngay;
//		gotoxy(47,3); cout<<pNodeCB->CB.ThoiGianDi.thang;
//		gotoxy(50,3); cout<<pNodeCB->CB.ThoiGianDi.nam;
//		gotoxy(56,3); cout<<pNodeCB->CB.ThoiGianDi.gio;
//		gotoxy(59,3); cout<<pNodeCB->CB.ThoiGianDi.phut;
//		gotoxy(72,3); cout<<pNodeCB->CB.SanBayDen;
		
		if (pNodeCB->CB.TongSoDaBan <= 8)  
		{
			trang = 0;
			tongtrang = 1;
		}
		else
		{
			tongtrang = (pNodeCB->CB.TongSoDaBan / 8.1) + 1;
		}
	}
	if (strcmp(maCB, "")==0) return;
	
	while(1)
	{
	Xuat:	
	    
		system("cls");
		
		Khung_DS_HK_Trong_CB();
		SetColor(ColorDARKWHITE);
		gotoxy(5, 25); cout <<"TONG SO: "<<pNodeCB->CB.TongSoDaBan<<" VE DA BAN RA";
		gotoxy(70,2); cout<<maCB;
		gotoxy(44,3); cout<<pNodeCB->CB.ThoiGianDi.ngay;
		gotoxy(47,3); cout<<pNodeCB->CB.ThoiGianDi.thang;
		gotoxy(50,3); cout<<pNodeCB->CB.ThoiGianDi.nam;
		gotoxy(56,3); cout<<pNodeCB->CB.ThoiGianDi.gio;
		gotoxy(59,3); cout<<pNodeCB->CB.ThoiGianDi.phut;
		gotoxy(72,3); cout<<pNodeCB->CB.SanBayDen;
		HienThiTrang(tongtrang, trang, 20, 28);
		SetColor(ColorBLACK);
		
		SetColor(ColorWHITE); SetBGColor(ColorBLACK);
		gotoxy(tabx + 4, taby + 3);
		int socho = Get_socho(lmb, pNodeCB->CB.soHieuMB); 
		int dem = 0;
		stt = 1 ;
		for (int i = 1 ; stt <=8+ 8*trang  && i <=socho; i++)
		{
			if (strcmp(pNodeCB->CB.DsVe[i].cmnd,"\0")!=0)
             {
             	if(stt<=8*trang)
             	{
             		stt++;
             	}
             	else
				{
	             	char cmnd[16];
					strcpy(cmnd,"");
					strcpy(cmnd,pNodeCB->CB.DsVe[i].cmnd);
					Node_HK *pHK = SearchHK(tree, cmnd);
					char hoten[150]; 
					strcpy(hoten,"");
					strcat(hoten, pHK->HK.ho );
					strcat(hoten, " ");
					strcat(hoten, pHK->HK.ten);
					//SetColor(ColorCYAN);
					gotoxy(tabx + 4, taby + 3 + dem); cout<<stt;
					gotoxy(tabx + 14, taby + 3 + dem);cout<<i;
					gotoxy(tabx + 25, taby + 3 + dem);cout<<pNodeCB->CB.DsVe[i].cmnd;
					gotoxy(tabx + 47, taby + 3 + dem);cout<<hoten;
					gotoxy(tabx + 75, taby + 3 + dem);cout<<pHK->HK.phai;
					stt++;
					dem+=2;
             	}	
			}
		}
		gotoxy(40, 29);
		cout << "[<-] Tro lai | Tiep Theo [->]"; 
		
		int c = 0;
		do{
			c = getch();
		}while(c != Left && c != Right && c != ESC);
		if (c == Left)
		{
			if(tongtrang > 1 && trang > 0)
			{
				trang--;
			}
			else{
				trang = tongtrang-1;
			}
			goto Xuat;
		}
		else if (c == Right)
		{
			if(tongtrang > 1 && trang  + 1 < tongtrang)
			{
				trang++;
				gotoxy(1,1);cout<<trang;
			}
			else
			trang=0;
			goto Xuat;
		}
		else if (c == ESC)
		{
			clrscr();
			MenuInterface(lmb,list);
			break;
		}
	}	
}

int main(){
		display();
		ListMayBay lmb;
		listCB list;
		InitFlightList(list);
		DocFileMayBay(lmb);
		DocFileChuyenBay(list,lmb);
		DocFileHanhKhach(tree);
		MenuInterface(lmb,list);
		CleanUpFlightList(list);
		The_End();
//---------------------------------------------------		
	return 0;
}                       		
