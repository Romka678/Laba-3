// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память
#ifndef __Stack_H__
#define __Stack_H__
#include <iostream>
#include <string>

using namespace std;

const int MAXElem = 1000000;

template <class ValType>
class Stack
{
	ValType *arr;
	int nElem;
	int MaxElem;
public:
	Stack();
	Stack(const int a);
	Stack(const Stack<ValType> &s);
	~Stack() { delete[] arr; }
	void push(const ValType a);
	ValType pop();
	ValType& top();
	bool check_void();
	void convert();
	int get_nElem() const { return nElem; }
	void clean_stack() { nElem = 0; }
	Stack<ValType>& operator=(const Stack<ValType>& s);
	bool operator==(const Stack<ValType>& s) const;
	bool operator!=(const Stack<ValType>& s) const;
	friend ostream & operator<<(ostream &out, const Stack<ValType> &mt)
	{
		for (int i = 0; i < mt.nElem; i++)
			out << mt.arr[i] << " ";
		out << endl;
		return out;
	}
};

template<class ValType>
inline Stack<ValType>::Stack()
{
	MaxElem = 10;
	nElem = 0;
	arr = new ValType[MaxElem];
}

template<class ValType>
inline Stack<ValType>::Stack(const int a)
{
	if ((a>MAXElem)||(a < 0))
		throw "Negative number";
	MaxElem = a;
	nElem = 0;
	arr = new ValType[MaxElem];
}

template<class ValType>
inline Stack<ValType>::Stack(const Stack<ValType> & s)
{
	MaxElem = s.MaxElem;
	nElem = s.nElem;
	arr = new ValType[MaxElem];
	for (int i = 0; i < nElem; i++)
		arr[i] = s.arr[i];
}

template<class ValType>
inline void Stack<ValType>::push(const ValType a)
{
	if (nElem == MaxElem)
	{
		Stack<ValType> s(MaxElem + 10);
		for (int i = 0; i < nElem; i++)
			s.arr[i] = arr[i];
		s.arr[nElem] = a;
		s.nElem = nElem + 1;
		*this = s;
	}
	else
	{
		arr[nElem] = a;
		nElem++;
	}
}

template<class ValType>
inline ValType Stack<ValType>::pop()
{
	if (nElem == 0)
		throw "Error: no elem in stack";
	nElem--;
	return arr[nElem];
}

template<class ValType>
inline ValType & Stack<ValType>::top()
{
	if (nElem == 0)
		throw "Error: no elem in stack";
	return arr[nElem - 1];
}

template<class ValType>
inline bool Stack<ValType>::check_void()
{
	if (nElem == 0)
		return true;
	else
		return false;
}

template<class ValType>
inline void Stack<ValType>::convert()
{
	ValType a;
	for (int i = 0; i < (nElem / 2); i++)
	{
		a = arr[i];
		arr[i] = arr[nElem - i - 1];
		arr[nElem - i - 1] = a;
	}
}

template<class ValType>
inline Stack<ValType> & Stack<ValType>::operator=(const Stack<ValType> & s)
{
	if (this != &s)
	{
		if (MaxElem != s.MaxElem)
		{
			delete[] arr;
			MaxElem = s.MaxElem;
			arr = new ValType[MaxElem];
		}
		nElem = s.nElem;
		for (int i = 0; i < nElem; i++)
			arr[i] = s.arr[i];
	}
	return *this;
}

template<class ValType>
inline bool Stack<ValType>::operator==(const Stack<ValType>& s) const
{
	if (this != &s)
	{
		if (nElem == s.nElem)
		{
			for (int i = 0; i < nElem; i++)
				if (arr[i] != s.arr[i])
					return false;
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

template<class ValType>
inline bool Stack<ValType>::operator!=(const Stack<ValType>& s) const
{
	return (!(*this == s));
}

#endif