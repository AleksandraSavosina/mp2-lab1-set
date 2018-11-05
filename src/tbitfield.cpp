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
		BitLen = len;				// длина битового поля
		MemLen = (len + 31) >> 5;	// количество "корзинок"		// побитовое смещение (деление на 2^5)
		pMem = new TELEM[MemLen];	// битовое поле
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;			// зануляем битовое поле
		}
	//}
	//else throw "len have an invalidate value";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen) throw "Error: 'n' is too big";
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
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < BitLen) && (n >= 0))
	{
		int index = GetMemIndex(n);
		pMem[index] = pMem[index] | GetMemMask(n);	// | - побитовое "или"
	}
	else throw "invalid value";
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < BitLen) && (n >= 0))
	{
		int index = GetMemIndex(n);
		pMem[index] = pMem[index] & ~GetMemMask(n);	// & - побитовое "и"
	}
	else throw "invalid value";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen)
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
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return false;

	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return  false;

	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return true;

	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return  true;

	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField tmp(*this);
	int min = bf.MemLen;

	if (BitLen < bf.BitLen)
	{
		tmp = bf;
		min = MemLen;
	}

	for (int i = 0; i < min; i++)
		tmp.pMem[i] = pMem[i] | bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField tmp(BitLen);
	int min = bf.MemLen;

	if (BitLen < bf.BitLen)
	{
		TBitField h(bf.BitLen);
		tmp = h;
		min = MemLen;
	}

	for (int i = 0; i < min; i++)
		tmp.pMem[i] = pMem[i] & bf.pMem[i];

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen - 1; i++) 
	{
		res.pMem[i] = ~pMem[i];
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++) 
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
