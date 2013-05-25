 // Ц
#ifndef UShipBattleH
#define UShipBattleH

 // Ц

 #include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Menus.hpp>
#include "CSPIN.h"
#include <ActnList.hpp>
 // Ц
struct Ship //структура даних про корабель
{
bool destroy;  //прапор знищенн€ корабл€
int col_deck;  //к-сть палуб
bool *decks;   //масив палуб
TPoint *desp_of_part;  //розм≥щенн€ частин (палуб) корабл€
};

class Flot //клас даних про корабл≥
{
public:
int i, j, n;  //зм≥нн≥, €к≥ викор. в циклах
bool destroy;  //прапор, €кий перев≥р€Ї на€вн≥сть флоту
TImage *Im;   //поле, на €кому малюЇмо
Ship ship[10];  //к-сть корабл≥в
Flot (TImage *I)  //конструктор класу Flot
{
destroy = false;
Im = I;
n = 1;
for (i = 0; i < 10; i++)
{
if (i < 6) n = 2;
if (i < 3) n = 3;
if (i == 0) n = 4;
ship[i].destroy = false;
ship[i].col_deck = n;
ship[i].decks = new bool[n];
ship[i].desp_of_part = new TPoint[n];
}
}
int GetStatus();
};


class ComputerAI //клас, €кий розм≥щуЇ корабл≥ противника
{
public:
TPoint decks_[20];
int col_decks_;
int Generation (Flot *CPU, int col_ship, int col_deck);//розм≥щ. корабл≥в противника
};

class Judge: public ComputerAI //перев≥р€Ї стан флот≥в
{
public:
int i, j, target_player, target_CPU;
bool net1 [10] [10], net2 [10] [10], game_over;
Flot *player, *CPU;
Judge() //конструктор класу Referee
{
for (i = 0; i < 10; i++)
for (j = 0; j < 10; j++)
{
net1 [i] [j] = true;
net2 [i] [j] = true;
}
game_over = false;
target_player = 0;
target_CPU = 0;
col_decks_ = 0;
}
int GoChecking (int x, int y, int n); //запуск перев≥рки
int Check (bool net[10] [10], int x, int y);//перев≥рка попаданн€ в стару або нову кл≥тинку
int GoScaning (int x, int y, int n); //запуск скануванн€
int Scan (Flot *fl, int x, int y); //скануванн€ (перев≥рка) попаданн€ в корабель
int Miss (int x, int y, int n);  //позначенн€ кл≥тинки в €ку попали (але не корабель)
int EndRaund (int n);
};

class EventsForm: public Judge //взаЇмод≥€ з формою
{
public:
bool play;
int col_deck, col_ship, i, j, k;
EventsForm (TImage *Im1, TImage *Im2)
{
play = false;
col_deck = 4; col_ship = 1;
player = new Flot(Im1);
CPU = new Flot(Im2);
}
int Play (TImage *Im1, TImage *Im2); //початок гри
//int Move();
int Desposition (int x, int y, TMouseButton Button); //розм≥щенн€ корабл≥в
int Draw (String key, int x, int y, int n); //малюванн€
int ShootPlayer (int x, int y, int n);  //вистр≥л гравц€
int Shoot (int x, int y);  //вистр≥л комп'ютера

int BuildShipsCPU();

};
class TForm1: public TForm
{
__published:	 // IDE-managed Components
TImage *Fild1;
TImage *Fild2;
        TLabel *Label1;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TMenuItem *N4;
        TMenuItem *N5;
        TMenuItem *N6;
        TMenuItem *N7;
        TMenuItem *N11;
        TMenuItem *N21;
        TMenuItem *N8;
        TTimer *Timer1;
        TTimer *Timer2;
        TMenuItem *N9;
        TMenuItem *N10;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        TBitBtn *BitBtn1;
        TImage *Image1;
        TLabel *Label4;
        TTimer *Timer3;
        TImage *Image2;
        TLabel *Label5;
        TLabel *Label6;
        TMenuItem *N12;
        TMenuItem *N13;
        TLabel *Label7;
        TLabel *Label8;
        TMenuItem *N14;
        TMenuItem *N15;
        TMenuItem *N16;
void __fastcall Fild2MouseDown (TObject *Sender,
TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall Fild1MouseDown (TObject *Sender,
TMouseButton Button, TShiftState Shift, int X, int Y);
void __fastcall BitBtn3Click (TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N7Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Timer2Timer(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall Timer3Timer(TObject *Sender);
        void __fastcall N9Click(TObject *Sender);
        void __fastcall N11Click(TObject *Sender);
        void __fastcall N21Click(TObject *Sender);
        void __fastcall N12Click(TObject *Sender);
        void __fastcall N13Click(TObject *Sender);
        void __fastcall N14Click(TObject *Sender);
        void __fastcall Fild1Click(TObject *Sender);
        void __fastcall N16Click(TObject *Sender);
private:	 // User declarations
public: // User declarations
__fastcall TForm1 (TComponent* Owner);
EventsForm *HE;
};
 // Ц
extern PACKAGE TForm1 *Form1;
 // Ц
#endif


