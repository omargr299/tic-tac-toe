#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#define arriba 72
#define abajo 80
#define izquierda 75
#define derecha 77

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;

    SetConsoleCursorPosition(hCon, dwPos);
}

void ocultar_cursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;

    SetConsoleCursorInfo(hCon, &cci);
}

void mostrar_cursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = TRUE;

    SetConsoleCursorInfo(hCon, &cci);
}

bool AjustarVentana(int Ancho, int Alto) {
	_COORD Coordenada;
	Coordenada.X = Ancho;
	Coordenada.Y = Alto;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Right = Ancho - 1;
	Rect.Bottom = Alto - 1;

	HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleScreenBufferSize(hConsola, Coordenada);

	SetConsoleWindowInfo(hConsola, TRUE, &Rect);
	return TRUE;
}

class TABLERO{
    public:
        int tablero[12][11] = {32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32,
                                205,205,205,206,205,205,205,206,205,205,205,
                                32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32,
                                205,205,205,206,205,205,205,206,205,205,205,
                                32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32,
                                32,32,32,186,32,32,32,186,32,32,32};  
        void imprimir();
        bool ganador();
};

void TABLERO::imprimir(){
    gotoxy(0,2);
           
    for (int i = 0; i < 12; i++)
    {   
        printf("  ");
        for (int j = 0; j < 11; j++)
        {
            printf("%c", tablero[i][j]);
        }
        printf("\n");
    }
}

bool TABLERO::ganador(){
    int ganador = 0;

    for (int i = 2; i <= 10; i+=4)
    {
        if(tablero[i][2]!=32 && tablero[i][2]==tablero[i][6] && tablero[i][6]==tablero[i][10]){
            if(tablero[i][2]==1){
                gotoxy(15,6);
                printf("GANADOR: X");
                return FALSE;
            }
            else{
                gotoxy(15,6);
                printf("GANADOR: O");
                return FALSE;
            }
        }

        if(tablero[2][i]!=32 && tablero[2][i]==tablero[6][i] && tablero[6][i]==tablero[10][i]){
            if(tablero[2][i]==1){
                gotoxy(15,6);
                printf("GANADOR: X");
                return FALSE;
            }
            else{
                gotoxy(15,6);
                printf("GANADOR: O");
                return FALSE;
            }
        }
    }
    
    if(tablero[2][2]!=32 && tablero[2][2]==tablero[6][6] && tablero[6][6]==tablero[10][10]){
        if(tablero[2][2]==1){
            gotoxy(15,6);
            printf("GANADOR: X");
            return FALSE;
        }
        else{
            gotoxy(15,6);
            printf("GANADOR: O");
            return FALSE;
        }
    }

    if(tablero[2][10]!=32 && tablero[2][10]==tablero[6][6] && tablero[6][6]==tablero[10][2]){
        if(tablero[2][10]==1){
            gotoxy(15,6);
            printf("GANADOR: X");
            return FALSE;
        }
        else{
            gotoxy(15,6);
            printf("GANADOR: O");
            return FALSE;
        }
    }

    if(tablero[2][2]!=32 && tablero[2][6]!=32 && tablero[2][10]!=32 &&
       tablero[6][2]!=32 && tablero[6][6]!=32 && tablero[6][10]!=32 &&
       tablero[10][2]!=32 && tablero[10][6]!=32 && tablero[10][10]!=32 && ganador == 0){
        gotoxy(15,6);
        printf("EMPATE");
        return FALSE;
    }
}

class FICHA{
    int x, y, turno;
    public:
        FICHA(int _x, int _y, int _t): x(_x), y(_y), turno(_t){}
        int X(){return x;}
        int Y(){return y;}
        int T(){return turno;}
        int mover(int tecla);
        void pintar();
        void cambio();
        void ganador();
};

int FICHA::mover(int tecla)
{
    

        switch (tecla)
        {
            case izquierda:
                if(x>3){
                    x-=4;
                }
                break;
            case derecha:
                if(x<9){
                    x+=4;
                }
                break;
             case abajo:
                if(y<9){
                    y+=4;
                }
                break;
            case arriba:
                if(y>3){
                    y-=4;
                }
                break;              
            default:
                break;
        }
        
    
    gotoxy(x,y);
}

void FICHA::pintar(){
    if(turno==1){
        printf("X");
    }
    else{
        printf("O");
    }
}

void FICHA::cambio(){
    if(turno==1){
        turno = 2;
        gotoxy(3,0);
        printf("Turno: O");
    }
    else{
        turno = 1;
        gotoxy(3,0);
        printf("Turno: X");
    }
}

int main(){
    AjustarVentana(34,16); 
    ocultar_cursor();    

    gotoxy(16,8);
    printf("GATO");
    gotoxy(16,9);
    printf("XO");
    Sleep(1000);
    system("cls");
    gotoxy(2,7);
    printf("Usa las teclas %c, %c, %c, %c para moverse", 24,25,26,27);
    gotoxy(2,8);
    printf("Usa la tecla ESPACIO para colocar tu marca (X/O)");
    gotoxy(0,9);
    system("pause");
    system("cls");

    TABLERO T;
    T.imprimir();

    FICHA F(3,3,1);
    int tecla;

    gotoxy(3,0);
    printf("Turno: X");

    gotoxy(3,3);
    bool game = TRUE;
    mostrar_cursor();
    while (game == TRUE)
    {
        if (kbhit()){
            tecla = getch();
            F.mover(tecla);

            if(tecla==32 && T.tablero[F.Y()-1][F.X()-1]==32){
                ocultar_cursor();
                F.pintar();
                T.tablero[F.Y()-1][F.X()-1] = F.T();
                game = T.ganador();
                F.cambio();
                gotoxy(F.X(), F.Y());
                mostrar_cursor();
            }
        }

    
        Sleep(30);  
    }

    gotoxy(3,13);
    printf("GAME OVER");
    Sleep(200);
    gotoxy(0,15);
    system("pause");

    return 0;
}