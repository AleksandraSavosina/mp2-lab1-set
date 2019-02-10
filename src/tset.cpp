// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля


#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
  maxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
  maxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return bitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
  return bitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
  bitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
  bitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  bitField = s.bitField;
  maxPower = s.maxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
  return bitField == s.bitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
  return bitField != s.bitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
  TSet result(bitField | s.bitField);
  return result;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
  TSet result(*this);
  result.InsElem(elem);
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
  TSet result(bitField & s.bitField);
  return result;
}

TSet TSet::operator~(void) // дополнение
{
  TSet result(*this);
  result.bitField = ~result.bitField;
  return result;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  return ostr;
}
