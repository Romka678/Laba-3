// объ€вление функций и классов дл€ вычислени€ арифметических выражений
#pragma once
#include "stack.h"
class Lexem
{
	double number;
	char symbol;
	int num;
	string stroka;
public:
	Lexem() {};
	Lexem(const Lexem &a);
	Lexem(const int n, const string str = "", const double d = 0.0, const char c = '0');
	Lexem(const string &str);
	Lexem(const double a);
	Lexem(const char a);
	~Lexem() {};
	Lexem& operator=(const Lexem& a);
	Lexem& operator=(const double a);
	Lexem& operator=(const char c);
	Lexem& operator=(const string& str);
	bool operator==(const Lexem& a) const;
	bool operator!=(const Lexem& a) const;
	string return_s() const;
	double return_n() const;
	char return_c() const;
	int return_b() const;
	friend ostream & operator<<(ostream & out, const Lexem & v);
};
double rank_number(const double a, const int i);
double converter_in_number(const string &s);
int prioritet(const char s);
double evaluation_of_expression(const double a, const double b, const char c);
bool check_for_correctness(const string &s);
Stack<Lexem> convert_string_to_stack(const string &c);
Stack<Lexem> polish_notation(const Stack<Lexem> &st);
double answer(const Stack<Lexem> &s);