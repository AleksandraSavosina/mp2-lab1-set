// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля


#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
  maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
  return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
  BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
  BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  BitField = s.BitField;
  maxPower = s.maxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet result(BitField | s.BitField);
  return result;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  TSet result(*this);
  result.InsElem(Elem);
  return result;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
  TSet result(*this);
  result.DelElem(Elem);
  return result;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
  TSet result(BitField & s.BitField);
  return result;
}

TSet TSet::operator~(void) // дополнение
{
  TSet result(*this);
  result.BitField = ~result.BitField;
  return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	/*s = TSet(s.MaxPower);
	int a;
	istr >> a;
	while (a != -1) 
	{
		s.InsElem(a);
		istr >> a;
	} */
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	/*bool f = true;
	for (int i = 0; i<s.MaxPower; i++) 
	{
		if (s.IsMember(i)) 
		{
			ostr << i << " ";
			f = false;
		}
	}
	if (f) ostr << "Пустое множество"; */
  return ostr;
}
