//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop
#include "arbori.h"
#include "Unit1.h"
#include <string>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::calculiciClick(TObject *Sender)
{
    char s[256];
	String INPUT = inp->Text;
    int i;
	for(i=0;i<INPUT.Length();i++)
		s[i] = INPUT[i+1];
    s[i] = '=';
    int rez = rezultat(s,nu);
	Rezultate->Items->Add(rez);
}
//--------------------------------------------------------------------------
