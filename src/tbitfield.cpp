// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "negative length error";
	//if (len >= 0)
	//{
    bitLen = len;				// длина битового поля
    memLen = (len + 31) >> 5;	// количество "корзинок"		// побитовое смещение (деление на 2^5)
    pMem = new TELEM[memLen];	// битовое поле
    for (int i = 0; i < memLen; i++)
    {
      pMem[i] = 0;			// зануляем битовое поле
    }
	//}
	//else throw "len have an invalidate value";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[memLen];
  for (int i = 0; i < memLen; i++)
    pMem[i] = bf.pMem[i];
	
}

TBitField::~TBitField()
{
  delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if (n >= bitLen) throw "Error: 'n' is too big";
  if (n >= 0)
    return (n / (sizeof(TELEM) * 8));
  else throw "Error: invalid value" ;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  TELEM mask = 1 << (n % (sizeof(TELEM) * 8));

  return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
  if ((n < bitLen) && (n >= 0))
  {
    int index = GetMemIndex(n);
    pMem[index] = pMem[index] | GetMemMask(n);	// | - побитовое "или"
  }
  else throw "invalid value";
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < bitLen) && (n >= 0))
  {
    int index = GetMemIndex(n);
    pMem[index] = pMem[index] & ~GetMemMask(n);	// & - побитовое "и"
  }  
  else throw "invalid value";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if (n >= 0 && n <= bitLen)
  {
    int a = 1;
    int index = n / (sizeof(TELEM) * 8);	// индекс нужной "корзины" массива
    int position = n % (sizeof(TELEM) * 8); // позиция бита в "корзине"
    a = a << position;
    if ((pMem[index] & a) == a)
      return 1;
    if ((pMem[index] & a) == 0)
      return 0;
  }
  else throw "Error"; 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  delete[] pMem;
  bitLen = bf.bitLen;
  memLen = bf.memLen;
  pMem = new TELEM[bf.memLen];
  for (int i = 0; i < bf.memLen; i++)
    pMem[i] = bf.pMem[i];
  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.bitLen)
    return false;

  for (int i = 0; i < memLen; i++)
    if (pMem[i] != bf.pMem[i])
      return  false;

  return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.bitLen)
    return true;

  for (int i = 0; i < memLen; i++)
    if (pMem[i] != bf.pMem[i])
      return  true;

  return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  TBitField tmp(*this);
  int min = bf.memLen;

  if (bitLen < bf.bitLen)
  {
    tmp = bf;
    min = memLen;
  }

  for (int i = 0; i < min; i++)
    tmp.pMem[i] = pMem[i] | bf.pMem[i];

  return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  TBitField tmp(bitLen);
  int min = bf.memLen;
  
  if (bitLen < bf.bitLen)
  {
    TBitField h(bf.bitLen);
    tmp = h;
    min = memLen;
  }

  for (int i = 0; i < min; i++)
    tmp.pMem[i] = pMem[i] & bf.pMem[i];

  return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField res(bitLen);
  for (int i = 0; i < memLen - 1; i++) 
  {
    res.pMem[i] = ~pMem[i];
  }
  for (int i = (memLen - 1) * 32; i < bitLen; i++) 
  {
    if (GetBit(i) == 0) 
    {
      res.SetBit(i);	
    }
  }
  return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  return ostr;
}
