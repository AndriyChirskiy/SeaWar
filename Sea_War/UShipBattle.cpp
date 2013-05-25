
 // -
#include <vcl.h>
#pragma hdrstop
#include "UShipBattle.h"
#include "Instruction_1.h"
 // -
#pragma package (smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;



 // ----------------------------------------------------------------------------



__fastcall TForm1::TForm1 (TComponent* Owner)
: TForm(Owner)
{
 HE = new EventsForm (Fild1, Fild2);//об'єкт класу, який працює напряму з формою
}



 // ----------------------------------------------------------------------------



int Flot:: GetStatus()
{
destroy = true; //прапор наявності флоту

for (j = 0; j < 10; j++)   //цикл кораблів
   for (i = 0; i < ship[j].col_deck; i++)  //цикл палуб корабля
   if (ship[j].decks[i])
   {
   destroy = false;
   return 1;
   }

return 0;

}



 // ----------------------------------------------------------------------------


//розміщення кораблів противника
int ComputerAI :: Generation (Flot *CPU, int col_ship, int col_deck)
{
int x1, y1, k, i, j;
bool vertical = false, regen;

do {

randomize();
x1 = rand()% 10;
y1 = rand()% 10;
regen = false;

for (k = 0; k < col_deck; k++)
   for (i = 0; i < col_ship; i++)
      for (j = 0; j < CPU -> ship[i].col_deck; j++)
      {

if(regen) break;

if(! vertical)
{
if (x1 + k >= 10)
   {
   vertical = true;
   regen = true;
   continue;
   }



   if((CPU -> ship[i].desp_of_part[j].x== x1 + k &&
   CPU -> ship[i].desp_of_part[j].y == y1))
   {
   vertical = true;
   regen = true;
   continue;
   }

   if((CPU -> ship[i].desp_of_part[j].x - 1 == x1 + k ||
   CPU -> ship[i].desp_of_part[j].x + 1 == x1 + k) &&
   (CPU -> ship[i].desp_of_part[j].y - 1 == y1 ||
   CPU -> ship[i].desp_of_part[j].y + 1 == y1))
   {
   vertical = true;
   regen = true;
   continue;
   }
}


if(vertical)
{

if (y1 + k >= 10)
   {
   vertical = false;
   regen = true;
   continue;
   }

   if((CPU -> ship[i].desp_of_part[j].x == x1 &&
   CPU -> ship[i].desp_of_part[j].y == y1 + k) )
   {
   vertical = false;
   regen = true;
   continue;
   }

   if ( (CPU -> ship[i].desp_of_part[j].x - 1 == x1 ||
   CPU -> ship[i].desp_of_part[j].x + 1 == x1) &&
   (CPU -> ship[i].desp_of_part[j].y - 1 == y1 + k ||
   CPU -> ship[i].desp_of_part[j].y + 1 == y1 + k))
   {
   vertical = true;
   regen = true;
   continue;
   }
}

      }

} while(regen);

if(! vertical)
for (i = 0; i < col_deck; i++)
{
CPU -> ship [col_ship - 1].desp_of_part[i].x = x1 + i;
CPU -> ship [col_ship - 1].desp_of_part[i].y = y1;
}
else
for (i = 0; i < col_deck; i++)
{
CPU -> ship [col_ship - 1].desp_of_part[i].x = x1;
CPU -> ship [col_ship - 1].desp_of_part[i].y = y1 + i;
}
return 0;

}

 // -


 //запуск ф-ії перевірки
int Judge :: GoChecking (int x, int y, int n)
{
if (n == 1)
        if (! Check(net1, x, y)) return 0;

if (n == 2)
        if (! Check(net2, x, y)) return 0;

return 1;
}




 // -



//перевірка попадання в стару або нову клітинку
int Judge:: Check (bool net[10] [10], int x, int y)
{
x /= 20; y /= 20;
if (! net[x] [y]) return 0;
return 1;
}



 // -


//запуск ф-ії сканування
int Judge:: GoScaning (int x, int y, int n)
{
if (n == 1)
        if (! Scan(player, x, y)) return 0;

if (n == 2)
        if (! Scan(CPU, x, y)) return 0;

return 1;
}



 // -



 //перевірка попадання в корабель
int Judge:: Scan (Flot *fl, int x, int y)
{
x /= 20; y /= 20;

for (i = 0; i < 10; i++)
   for (j = 0; j < fl -> ship[i].col_deck; j++)
        if (fl -> ship[i].desp_of_part[j].x == x &&
        fl -> ship[i].desp_of_part[j].y == y)
        {
        fl -> ship[i].decks[j] = false;
        return 0;
        }

return 1;
}



 // -


//позначення клітинки в яку попали (але не корабля)
int Judge:: Miss (int x, int y, int n)
{
x /= 20; y /= 20;

if (n == 1) net1 [x] [y] = false;
if (n == 2) net2 [x] [y] = false;

return 1;
}



 // -


//кінець гри
int Judge:: EndRaund (int n)
{
Form1->Timer3->Enabled=false;

if (n == 2)
{
Form1 -> Label1 -> Caption = "Ви виграли!";
Form1->Label5->Caption=StrToInt(Form1->Label5->Caption)+1;

Form2->Memo2->Lines->Clear();
Form2->Memo1->Lines->Clear();
Form2->Memo2->Lines->LoadFromFile("rahunok/bals.txt");
Form2->Memo1->Lines->LoadFromFile("rahunok/rahunok.txt");
int lc=( StrToInt(Form1->Label5->Caption) - StrToInt(Form1->Label6->Caption) );

for (int i=0; i<10; i++)
{

if (lc  >  StrToInt(Form2->Memo2->Lines->Strings[i]))
   {
     Form2->Memo2->Lines->Strings[i]=IntToStr(lc);
     Form2->Memo1->Lines->Strings[i]=(IntToStr(i+1)+") " +Form1->Label2->Caption +
                "     " + Form1->Label5->Caption + "  -  " +
                Form1->Label6->Caption );
    break;
}
}

Form2->Memo1->Lines->SaveToFile("rahunok/rahunok.txt");
 Form2->Memo2->Lines->SaveToFile("rahunok/bals.txt");
}

if (n == 1)
{
Form1 -> Label1 -> Caption = "Ви програли!";
Form1->Label6->Caption=StrToInt(Form1->Label6->Caption)+1;

Form2->Memo2->Lines->Clear();
Form2->Memo1->Lines->Clear();
Form2->Memo2->Lines->LoadFromFile("rahunok/bals.txt");
Form2->Memo1->Lines->LoadFromFile("rahunok/rahunok.txt");
int lc=( StrToInt(Form1->Label5->Caption) - StrToInt(Form1->Label6->Caption) );

for (int i=0; i<10; i++)
{

if (lc  >  StrToInt(Form2->Memo2->Lines->Strings[i]))
   {
     Form2->Memo2->Lines->Strings[i]=IntToStr(lc);
     Form2->Memo1->Lines->Strings[i]=(IntToStr(i+1)+") " +Form1->Label2->Caption +
                "     " + Form1->Label5->Caption + "  -  " +
                Form1->Label6->Caption );
    break;
}
}

Form2->Memo1->Lines->SaveToFile("rahunok/rahunok.txt");
 Form2->Memo2->Lines->SaveToFile("rahunok/bals.txt");

}
game_over = true;

return 0;
}



 // -


// початок гри
int EventsForm:: Play (TImage *Im1, TImage *Im2)
{
Form1->Timer3->Enabled=true;
Im1 -> Enabled = true;
Im2 -> Enabled = true;
return 0;
}



 // -


//розміщення кораблів
int EventsForm:: Desposition (int x, int y, TMouseButton Button)
{
if(play) return 0;
x /= 20; y /= 20;
for (k = 0; k < col_deck; k++) // к-сть палуб
for (i = 0; i < col_ship; i++)    // к-сть кораблів
for (j = 0; j < player -> ship[i].col_deck; j++)   // к-сть палуб корабля
{
if (Button == mbLeft)  //натискання лівої кнопки миші
{

if ((player -> ship[i].desp_of_part[j].y == y - 1 ||
player -> ship[i].desp_of_part[j].y == y + 1) &&
player -> ship[i].desp_of_part[j].x == x)
{
ShowMessage ("ERROR!");
return 0;
}

if ((player -> ship[i].desp_of_part[j].x == x-1  ||
player -> ship[i].desp_of_part[j].x == x+k+1) &&
player -> ship[i].desp_of_part[j].y == y)
{
ShowMessage ("ERROR!");
return 0;
}


if((player -> ship[i].desp_of_part[j].x - 1 == x + k ||
player -> ship[i].desp_of_part[j].x + 1 == x + k) &&
(player -> ship[i].desp_of_part[j].y - 1 == y ||
player -> ship[i].desp_of_part[j].y + 1 == y))
{
ShowMessage ("ERROR!");
return 0;
}

if (x + k >= 10)
{
ShowMessage ("ERROR!");
return 0;
}

}
if (Button == mbRight)  //натискання правої кнопки миші
{


if ((player -> ship[i].desp_of_part[j].x == x+1 ||
player -> ship[i].desp_of_part[j].x == x-1)  &&
(player -> ship[i].desp_of_part[j].y == y))
{
ShowMessage ("ERROR!");
return 0;
}

if ((player -> ship[i].desp_of_part[j].x == x &&
player -> ship[i].desp_of_part[j].y == y + k+1) ||
(player -> ship[i].desp_of_part[j].x == x &&
player -> ship[i].desp_of_part[j].y == y - 1))
{
ShowMessage ("ERROR!");
return 0;
}

if((player -> ship[i].desp_of_part[j].x - 1 == x ||
player -> ship[i].desp_of_part[j].x + 1 == x) &&
(player -> ship[i].desp_of_part[j].y - 1 == y + k ||
player -> ship[i].desp_of_part[j].y + 1 == y + k))
{
ShowMessage ("ERROR!");
return 0;
}


if (y + k >= 10)
{
ShowMessage ("ERROR!");
return 0;
}


}


}

if (Button == mbLeft)
Draw ("position_h", x*20, y*20, 1);
else
Draw ("position_v", x*20, y*20, 1);

Generation (CPU, col_ship, col_deck);

if (col_ship == 1) col_deck --;
if (col_ship == 3) col_deck --;
if (col_ship == 6) col_deck --;
if (col_ship == 10) play = true;

if(play) Form1 -> Label1 -> Caption = "Поїхали!";
col_ship++;
return 0;
};



 // -



//вистріл комп'ютера
int EventsForm:: Shoot (int x, int y)
{
if (game_over) return 0;

int shoot_player = ShootPlayer (x, y, 2);
if (shoot_player > 0)
do {
x = rand()% 200;
y = rand()% 200;
int shoot_cpu = ShootPlayer (x, y, 1);
if (shoot_cpu > 0)
break;
if (shoot_cpu < 0)
player -> GetStatus();
if (player -> destroy || target_CPU > 19)
{
EndRaund(1);
return 0;
}
} while(true);
else
{
if (shoot_player < 0)
CPU -> GetStatus();
if (CPU -> destroy || target_player > 19)
{
EndRaund(2);
return 0;
}
}
return 0;
}



 // -


//вистріл гравця
int EventsForm:: ShootPlayer (int x, int y, int n)
{
if(! play) return 0;

if (! GoChecking(x, y, n))
{
if (n == 2) Form1 -> Label1 -> Caption = "Ще раз! Туди вже стріляли!";
return 0;
}
else
        if (! GoScaning(x, y, n))
        {
        Draw ("target", x, y, n);
        Miss (x, y, n);

        if (n == 2)
        {
        Form1 -> Label1 -> Caption = "Попав! Ще раз!";
        target_player++;
        }
        else target_CPU++;

        return -1;
        }
        Miss (x, y, n);
        if (n == 2) Form1 -> Label1 -> Caption = "Схибив! Хід противника";
        Draw ("miss", x, y, n);
        return 1;
}



 // -


 //зарисовка на полях
int EventsForm:: Draw (String key, int x, int y, int n)
{
TImage *Im;
x /= 20; y /= 20;
if (n == 1) Im = Form1 -> Fild1;
if (n == 2) Im = Form1 -> Fild2;

if (key == "target")   //при попаданні в ціль
{
Im -> Canvas -> Brush -> Color = clRed;
Im -> Canvas -> Rectangle (x*20, y*20, x*20 + 20, y*20 + 20);

Im->Canvas->Pen->Width=2;
Im -> Canvas -> Brush -> Color = clRed;
Im->Canvas->MoveTo(x*20+1,y*20+1);
Im->Canvas->LineTo(x*20+19,y*20+19) ;

Im->Canvas->MoveTo(x*20+19,y*20+1);
Im->Canvas->LineTo(x*20+1,y*20+19) ;

Im -> Canvas -> Brush -> Color = clWhite;
Im->Canvas->Pen->Width=1;

}

if (key == "miss")       // при промаху
{

Im->Canvas->Pen->Width=5;
Im -> Canvas->MoveTo(x*20 + 10, y*20 + 10);
Im->Canvas->LineTo(x*20+10,y*20+10);
Im->Canvas->Pen->Width=1;
}

if (key == "position_h")     // малювання корабля по горизонталі
{
for (i = 0; i < col_deck; i++)
{
Im -> Canvas -> Brush -> Color = clAqua;
Im -> Canvas -> Rectangle (x*20 + i*20, y*20, x*20 + 20 + i*20, y*20 + 20);
player -> ship [col_ship - 1].desp_of_part[i].x = x + i;
player -> ship [col_ship - 1].desp_of_part[i].y = y;
Im -> Canvas -> Brush -> Color = clWhite;
}
}
if (key == "position_v")     //малювання корабля по вертикалі
{
for (i = 0; i < col_deck; i++)
{
Im -> Canvas -> Brush -> Color = clAqua;
Im -> Canvas -> Rectangle (x*20, y*20 + i*20, x*20 + 20, y*20 + 20 + i*20);
player -> ship [col_ship - 1].desp_of_part[i].x = x;
player -> ship [col_ship - 1].desp_of_part[i].y = y + i;
Im -> Canvas -> Brush -> Color = clWhite;
}
}
return 0;
}



 // -



void __fastcall TForm1:: Fild2MouseDown (TObject *Sender,
TMouseButton Button, TShiftState Shift, int X, int Y)
{
HE -> Shoot (X, Y);
}
 // -
void __fastcall TForm1:: Fild1MouseDown (TObject *Sender,
TMouseButton Button, TShiftState Shift, int X, int Y)
{
HE -> Desposition (X, Y, Button);
}
 // -
void __fastcall TForm1:: BitBtn3Click (TObject *Sender)
{
Label1 -> Caption = "Розставте кораблі";
Fild1 -> Picture -> LoadFromFile ("foto/net.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net.bmp");

HE = new EventsForm (Fild1, Fild2);
}
 // -




void __fastcall TForm1::N3Click(TObject *Sender)
{


if (Form1->Timer3->Enabled == true || Form1->N7->Default == true)
{
Fild1 -> Picture -> LoadFromFile ("foto/net.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net.bmp");
Label1 -> Caption = "Розставте кораблі";
HE = new EventsForm (Fild1, Fild2);
Form1->Timer3->Enabled=true;
}
  else
if (Form1->N11->Default == true)
{

Fild1 -> Picture -> LoadFromFile ("foto/net_2.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net_2.bmp");
Label1 -> Caption = "Розставте кораблі";
HE = new EventsForm (Fild1, Fild2);
Form1->Timer3->Enabled=true;
}
  else
  
if (Form1->N21->Default == true)
{
Fild1 -> Picture -> LoadFromFile ("foto/net_3.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net_3.bmp");
Label1 -> Caption = "Розставте кораблі";
HE = new EventsForm (Fild1, Fild2);
Form1->Timer3->Enabled=true;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
Form1->Timer2->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{


if (Form1->BitBtn1->Visible==true) ShowMessage("Спочатку підтвердіть ваше ім'я!");
else

if (Form1->Edit1->Text =="") ShowMessage("Спочатку введіть своє ім'я!");
else
    {
HE -> Play (Fild1, Fild2);

Form1->N3->Enabled=true;
Form1->N2->Enabled=false;
Form1->N6->Enabled=true;
Form1->Label5->Visible=true;
Form1->Label6->Visible=true;
Form1->Label7->Visible=true;
Form1->Label8->Visible=true;
Form1->Label1->Visible=true;

Label1 -> Caption = "Розставте кораблі";
Fild1 -> Picture -> LoadFromFile ("foto/net.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net.bmp");
Form1->Image2->Picture->LoadFromFile("foto/bg_2.jpg");

Form1->Label2->Visible=true;
Form1->Label3->Visible=true;
}

}
//---------------------------------------------------------------------------


void __fastcall TForm1::N7Click(TObject *Sender)
{
if (Form1->Timer3->Enabled == true) ShowMessage("Неможливо! Триває гра!");
       else
       {
Form1->N7->Default=true;
Form1->N11->Default=false;
Form1->N21->Default=false;

Fild1 -> Picture -> LoadFromFile ("foto/net.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net.bmp");
       }

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
if (Form1->AlphaBlendValue==255)
Form1->Timer1->Enabled=false;
 else Form1->AlphaBlendValue=Form1->AlphaBlendValue+5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer2Timer(TObject *Sender)
{
if (Form1->AlphaBlendValue==0) Form1->Close();
        else Form1->AlphaBlendValue-=5;
}
//---------------------------------------------------------------------------




void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
if (Form1->Edit1->Text =="") ShowMessage("Спочатку введіть своє ім'я");
        else if ( Form1->Edit1->Text.Length()>10) ShowMessage("Ім'я перевищує максимальну кількість допустимих символів!");
                else
                {
                Form1->Label2->Caption = Form1->Edit1->Text;
                Form1->Edit1->Visible=false;
                Form1->BitBtn1->Visible=false;
                Form1->Label4->Visible=false;
                //Form1->Timer3->Enabled=true;
}
}
//---------------------------------------------------------------------------




void __fastcall TForm1::Timer3Timer(TObject *Sender)
{

if (Form1->Image1->Left==-65) Form1->Timer3->Enabled=false;
        else
       Form1->Image1->Left-=1;

   if(Form1->Image1->Left==-65) Form1->Image1->Left=695;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N9Click(TObject *Sender)
{
ShowMessage("Морський Бій  v.1.0");
}
//---------------------------------------------------------------------------







void __fastcall TForm1::N11Click(TObject *Sender)
{
if (Form1->Timer3->Enabled == true) ShowMessage("Неможливо! Триває гра!");
       else
    {
Form1->N7->Default=false;
Form1->N11->Default=true;
Form1->N21->Default=false;

Fild1 -> Picture -> LoadFromFile ("foto/net_2.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net_2.bmp");
     }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N21Click(TObject *Sender)
{
if (Form1->Timer3->Enabled == true) ShowMessage("Неможливо! Триває гра!");
    else
    {
Form1->N7->Default=false;
Form1->N11->Default=false;
Form1->N21->Default=true;

Fild1 -> Picture -> LoadFromFile ("foto/net_3.bmp");
Fild2 -> Picture -> LoadFromFile ("foto/net_3.bmp");
    }
}
//---------------------------------------------------------------------------




void __fastcall TForm1::N12Click(TObject *Sender)
{
Form2->Visible=true;
Form2->Caption="Управління";

Form2->Memo1->Visible=false;
Form2->Image1->Visible=true;

Form2->Image1->Picture->LoadFromFile("foto/upravlinya.jpg");
Form2->Image1->Width=457;
Form2->Image1->Height=241;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N13Click(TObject *Sender)
{
Form2->Visible=true;
Form2->Caption="Правила";

Form2->Memo1->Visible=false;
Form2->Image1->Visible=true;

Form2->Image1->Picture->LoadFromFile("foto/referee.jpg");
Form2->Image1->Width=600;
Form2->Image1->Height=300;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N14Click(TObject *Sender)
{
Form2->Visible=true;
Form2->Caption="Найкращі результати";
Form2->Memo1->Visible=true;
Form2->Image1->Visible=false;

Form2->Memo1->Lines->LoadFromFile("rahunok/rahunok.txt");
Form2->Memo2->Lines->LoadFromFile("rahunok/bals.txt");
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Fild1Click(TObject *Sender)
{
if (Form1->Timer3->Enabled == false) ShowMessage("Натисність 'Заново' в меню гри!");
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N16Click(TObject *Sender)
{
for (int i=0; i<10; i++)
{
Form2->Memo2->Lines->Strings[i]="0";
Form2->Memo1->Lines->Strings[i]=(IntToStr(i+1)+") none   0  -  0");
}

Form2->Memo2->Lines->SaveToFile("rahunok/bals.txt");
Form2->Memo1->Lines->SaveToFile("rahunok/rahunok.txt");

}
//---------------------------------------------------------------------------

