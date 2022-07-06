// Ordinary least square finding equation f(x)= a.x^b

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#define MAX 10

using namespace std;


// Hàm thay đổi màu cho Console
void SET_COLOR(int color)
{
	WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}



// Hàm gotoxy để di chuyển con trỏ đến vị trí nào đó xác định bởi vị trí hiện tại trên cửa sổ màn hình.
// Nếu như vị trí đó không hợp lệ hàm này sẽ không thực hiện gì cả.
// gotoxy(a,b);   với   a – hoành độ, b – tung độ
void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 


// Hàm move() tự động bắt sự kiện được gõ từ bàn phím rồi trả về giá trị của kí tự vừa được gõ.
// Khi ta nhấn một phím bất kì thì kí tự đó sẽ được nạp vào mà không cần nhấn Enter.
int move()
{
    char c = getch();
    if ((int) c == -32) c = getch();
    switch ((int) c) 
    {
        case 80:
            return 1; //cout << "Xuong";
        case 72:
            return 2; //cout << "Len";
        case 77:
            return 3; //cout << "Phai";       
        case 75:
            return 4; //cout << "Trai";
        case 27:
            return 8; //Nut ESC thoat
        case 13:
            return 5; //Nut Enter
        default:
            return 0; //cout << "Sai";
    }
}
 

// Định nghĩa lớp Menu gồm các thuộc tính (Attribute) là: item,_numberOfItem,...
// Và các phương thức (Method) là: printMenu(),deleteMenu(), getItem(),...
class Menu 
{
    public:
        Menu();

    ~Menu() {}

    void printMenu();
    void deleteMenu(); //Xóa menu khi kết thúc chương trình bằng cách viết đè kí tự trắng

    int numberOfItem() 
    {
        return _numberOfItem;
    }
 
    string * getItem() 
    {
        return item;
    }
 
    private:
        string * item; //Mảng lưu tên của các menu
    int _numberOfItem; //Số lượng menu
};
 

// Khởi tạo các thuộc tính ban đầu cho lớp (class) Menu
Menu::Menu() 
{
    item = new string[100];
    _numberOfItem = 11;
    item[0]  = "|-----------------------------------------------------------------------------------";
    item[1]  = "|                                       MENU                                        ";
    item[2]  = "|-----------------------------------------------------------------------------------";
    item[3]  = "|1. Thong tin de tai PBL1                                                           ";
    item[4]  = "|2. Thong tin thanh vien nhom                                                       ";
    item[5]  = "|3. Danh sach cac truong hop cua file *.INP                                         ";
    item[6]  = "|4. Ghi du lieu n, x, y vao file *.INP                                              ";                                     
    item[7]  = "|5. Doc va in du lieu n, x, y tu file *.INP                                         ";                                               
    item[8]  = "|6. Thuc hien chuong trinh tinh toan tim bieu thuc f(x)=a.x^b                       ";                                                     
    item[9]  = "|7. Ket thuc chuong trinh tinh toan (hoac bam ESC)                                  "; 
    item[10] = "|-----------------------------------------------------------------------------------";
}
 

// Hàm thành viên
void Menu::printMenu() 
{
    SET_COLOR(14);
    for (int i = 0; i < _numberOfItem; i++) 
    {
        gotoxy(3, i);
        cout << item[i]; cout <<'|';
        Sleep(100); //Tạm dừng 100ms
    }
    SET_COLOR(3);
    cout << "\nDung phim mui ten de chon lenh: ";
}
 
// Hàm thành viên
void Menu::deleteMenu() 
{
    for (int i = 0; i < _numberOfItem; i++) 
    {
        Sleep(100);
        gotoxy(0, i);
        for (int j = 0; j < item[i].size() + 3; j++) 
        {
            cout << " "; //Xóa bằng cách ghi đè kí tự trắng
        }
    }
}

// Hàm lấy logarit cho các phần tử
void loga(float a[], int n)
{
	int i;
	for(i = 0; i < n; i++)
    {
		a[i] = log10(a[i]);
	}
}

// Hàm lấy tổng các phần tử có trong mảng
float tong(float a[], int n)
{
	float s = 0;
	int i;
	for(i = 0; i < n; i++)
    {
		s += a[i];
	}
	return s;
}

// Hàm lấy tổng các tích phần tử có trong mảng
float tongmang(float a[], float b[], int n)
{
	float s = 0;
	int i;
	for(i = 0; i <n; i++){
		s += a[i] * b[i];
	}
	return s;
}


// Định nghĩa đối tượng menu thuộc lớp (Class) Menu
Menu menu;


// Hàm hỏi ý kiến người dùng có muốn kết thúc chương trình hay không
void ketthuc(int *thoat)
{
    char finish;
    SET_COLOR(2);
    fflush(stdin);
    cout << "\nNhap 'y' neu ban muon tro ve menu, nhap phim khac neu ban muon thoat: ";
    cin >> finish;
    fflush(stdin);
    if (finish=='y')
    {
        system("cls");
        menu.printMenu();
    }
    else
    {
        *thoat=1;
    }
}




int main()
{
    cout.precision(4);
    cout.setf(ios::fixed);
    char tenfile[50];

    
    int p;
    int line = 0; //Vị trí dòng của menu
    int thoat = 0;
    char finish;
 

    menu.printMenu();
    
    gotoxy(0, line);
    cout << (char) 26; //Vẽ con trỏ trỏ tới menu
    
    int n=-1;
    float x[MAX], y[MAX];

    while (!thoat) 
    {
        p = move();
        gotoxy(0, line);
        cout << " "; //Xóa con trỏ ở vị trí cũ

        switch (p) 
        {
            case 1:
            case 3:
                {
                    line++;
                    if (line >= menu.numberOfItem()) line = 0;
                    break;
                }

            case 2:

            case 4:
                {
                    line--;
                    if (line < 0) line = menu.numberOfItem() - 1;
                    break;
                }

            case 5:
                {
                    gotoxy(0, 14);
                    cout << "                                           ";
                    gotoxy(0, 14);
                    SET_COLOR(2);
                    if (line == 0 || line == 1 || line ==2 || line == 10) 
                    {
                        cout << "Moi ban dieu khien lai mui ten!!!";
                        break;
                    }
                    else
                    {
                        cout << "Ban chon " << menu.getItem()[line];
                        Sleep(1000);
                        system("cls");

                        if (line == 3)
                        {
                            FILE * file = NULL;
                            file= fopen("DetaiPBL1.txt", "r");

                            char c;
                            SET_COLOR(123);
                            //Đọc từng ký tự từ file cho tới khi gặp EOF
                            while ((c = fgetc(file)) != EOF)
                            {
                                //Xuất từng ký tự ra màn hình
                                cout << c;
                                Sleep(1);  
                            }

                            ketthuc(&thoat);

                        }
                        else if (line==4)
                        {
                            FILE * file = NULL;
                            file= fopen("Thanhviennhom.txt", "r");

                            char c;
                            SET_COLOR(123);
                            //Đọc từng ký tự từ file cho tới khi gặp EOF
                            while ((c = fgetc(file)) != EOF)
                            {
                                //Xuất từng ký tự ra màn hình
                                cout << c;
                                Sleep(1);  
                            }

                            ketthuc(&thoat);
                        }
                        else if (line==5)
                        {
                            FILE * file = NULL;
                            file= fopen("Danhsachinput.txt", "r");

                            char c;
                            SET_COLOR(123);
                            //Đọc từng ký tự từ file cho tới khi gặp EOF
                            while ((c = fgetc(file)) != EOF)
                            {
                                //Xuất từng ký tự ra màn hình
                                cout << c;
                                Sleep(1);  
                            }

                            fclose(file);

                            ketthuc(&thoat);
                        }
                        else if (line==6)
                        {
                            FILE *file ;
                            SET_COLOR(123);
                            cout << "Moi ban nhap ten file ma ban muon ghi: ";
                            cin >> tenfile;

                            file=fopen(tenfile,"w");

                            int n;
                            float x[MAX], y[MAX];
                            int i=0, j=0;

                            do
                            {
                                cout << "Moi ban nhap n>=0: "; cin >> n;
                            } while (n<=0); 

                            fprintf(file,"%d\n",n);

                            cout << "Moi ban nhap cac phan tu x: \n";

                            while (i<n) 
                            {
                                cout <<"x[" << i << "]= "; cin >> x[i];
                                while (x[i]<=0)
                                {
                                    cout << "Moi ban nhap lai x[" <<i<<"]= "; cin >> x[i];
                                }
                                fprintf(file, "%7.2f",x[i]);
                                i++;
                            }

                            fprintf(file,"\n");
                            cout << "Moi ban nhap cac phan tu y: \n";

                            while (j<n) 
                            {
                                cout <<"y[" << j << "]= "; cin >> y[j];
                                while (y[j]<=0)
                                {
                                    cout << "Moi ban nhap lai y[" <<j<<"]= "; cin >> y[j];
                                }
                                fprintf(file, "%7.2f",y[j]);
                                j++;
                            }

                            cout << "Ban da nhap thanh cong du lieu vao file " << tenfile;
                            fclose(file);
                            
                            ketthuc(&thoat);
                        }
                        else if (line==7)
                        {
                            FILE *file=NULL;

                            SET_COLOR(123);

                            cout << "Moi ban nhap ten file ma ban muon doc: ";
                            cin >> tenfile;
                            file = fopen(tenfile,"r");
                            if (file==NULL)
                            {
                                cout << "\nKhong ton tai file co ten la " << tenfile;

                                ketthuc(&thoat);
                            }
                            else
                            {

                                bool checkempty = true;
                                bool checkn = true; 
                                bool checkx = true;
                                bool checky = true;

                                if (fscanf(file, "%d\n",&n)==EOF)
                                {
                                    checkempty = false;
                                }


                                if (n<=0) checkn = false;

                                for (int i = 0; i < n; i++)
                                {
                                    fscanf(file, "%f", &x[i]);
                                    if (x[i] <=0) checkx = false;
                                }

                                for (int i = 0; i < n; i++)
                                {
                                    fscanf(file, "%f", &y[i]);
                                    if (y[i] <=0) checky = false;
                                }

                                if (checkempty==false || checkn==false || checkx==false || checky==false)
                                {
                                    if (checkempty==false)
                                    {
                                        cout << "Du lieu file "<<tenfile<< " rong";
                                    }
                                    else
                                    {
                                        if (checkn==false)
                                        {
                                            cout << "File co gia tri n<=0 (n=" <<n <<" se khong tinh toan duoc\n";
                                        }
                                        if (checkx==false)
                                        {
                                            cout << "File co phan tu x<=0 se khong tinh toan duoc\n";
                                        }
                                        if (checky==false)
                                        {
                                            cout << "File co phan tu y<=0 se khong tinh toan duoc\n";
                                        }
                                    }
                                    ketthuc(&thoat);
                                    fclose(file);
                                }
                                else
                                {
                                    cout << "Da doc thanh cong du lieu tu file "<< tenfile<< endl;
                                    cout <<"Du lieu tu file " << tenfile <<" la: \n";
                                    cout << n << endl;
                                    for (int i=0; i<n; i++)
                                    {
                                        printf("%7.2f",x[i]);
                                    }
                                    cout << endl;
                                    for (int i=0; i<n; i++)
                                    {
                                        printf("%7.2f",y[i]);
                                    }

                                    ketthuc(&thoat);
                                }
                            }
                        }
                        else if (line==8)
                        {
                            if (n==-1)
                            {
                                cout <<"Chua thiet lap gia tri n, x, y";
                                ketthuc(&thoat);
                            }
                            else
                            {
                                SET_COLOR(3);
                                cout << "Du lieu la: \n";
                                cout << n << endl;
                                for (int i=0; i<n; i++)
                                {
                                    printf("%7.2f",x[i]);
                                }
                                cout << endl;
                                for (int i=0; i<n; i++)
                                {
                                    printf("%7.2f",y[i]);
                                }

                                float s1, s2, s3, s4;
                                float D, Dx, Dy, A, B;

                                loga(x,n);
                                loga(y,n);

                                s1 = tong(x, n);
                                s2 = tongmang(x, x, n);
                                s3 = tongmang(x, y, n);
                                s4 = tong(y, n);
                                
                                D = n * s2 - s1 * s1;
                                Dx = s2 * s4 - s1 * s3;
                                Dy = n * s3 - s1 * s4;

                                if(D == 0)
                                {
                                    SET_COLOR(6);
                                    if(Dx + Dy == 0)
                                    {
                                        cout << "\nHe phuong trinh co vo so nghiem\n";
                                        cout << "Khong co bieu thuc phi tuyen tinh dang y=a.x^b thoa man du lieu tren\n";
                                    }
                                    else
                                    {
                                        cout << "\nHe phuong trinh vo nghiem\n";
                                        cout << "Khong co bieu thuc phi tuyen tinh dang y=a.x^b thoa man du lieu tren\n";
                                    }
                                    ketthuc(&thoat);
                                }
                                else
                                {
                                    FILE *file;
                                    A = Dx / D;
                                    B = Dy / D;
                                    float a=pow(10,A);
                                    SET_COLOR(169);
                                    printf("\n\nBieu thuc thoa man la: y=%.2f.x^%.2f\n",a,B);

                                    file=fopen("Ketqua.txt","+");
                                    fprintf(file,"File %s co bieu thuc thoa man la: \n",tenfile);
                                    fprintf(file,"y=%.2f.x^%.2f\n",a,B);
                                    cout << "Da luu ket qua vao file ketqua.txt\n";

                                    ketthuc(&thoat);
                                }
                            }
                        }
                        else if (line==9)
                        {
                            FILE * file = NULL;
                            file= fopen("Ketthuc.txt", "r");

                            char c;
                            SET_COLOR(123);
                            //Đọc từng ký tự từ file cho tới khi gặp EOF
                            while ((c = fgetc(file)) != EOF)
                            {
                                //Xuất từng ký tự ra màn hình
                                cout << c; 
                            }
                            Sleep(3000);
                            exit(0);
                        }
                        break;
                    }
                }
            case 8:
                thoat = 1;
        }
        gotoxy(0, line);
        cout << (char) 26;
    }
    menu.deleteMenu();
    return 0;
}


