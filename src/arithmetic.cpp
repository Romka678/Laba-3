#include "..\include\arithmetic.h"
#include <iostream>
// реализация функций и классов для вычисления арифметических выражений

Lexem::Lexem(const Lexem & a)
{	
	stroka = a.stroka;
	number = a.number;
	symbol = a.symbol;
	num = a.num;
}

Lexem::Lexem(const string & str)
{
	stroka = str;
	num = 2;
}

Lexem::Lexem(const int n, const string str, const double d, const char c)
{
	num = n;
	stroka = str;
	number = d;
	symbol = c;
}

Lexem::Lexem(const double a)
{
	number = a;
	num = 1;
}

Lexem::Lexem(const char a)
{
	symbol = a;
	num = 0;
}

Lexem & Lexem::operator=(const Lexem & a)
{
	stroka = a.stroka;
	number = a.number;
	symbol = a.symbol;
	num = a.num;
	return *this;
}

Lexem & Lexem::operator=(const double a)
{
	number = a;
	num = 1;
	return *this;
}

Lexem & Lexem::operator=(const char c)
{
	symbol = c;
	num = 0;
	return *this;
}

Lexem & Lexem::operator=(const string & str)
{
	stroka = str;
	num = 2;
	return*this;
}

bool Lexem::operator==(const Lexem & a) const
{
	if (this != &a)
	{
		if (num == a.num)
		{
			if (num == 1)
			{
				if (number != a.number)
					return false;
				else
					return true;
			}
			else
			{
				if (num == 0)
				{
					if (symbol != a.symbol)
						return false;
					else
						return true;
				}
				else
				{
					if (stroka != a.stroka)
						return false;
					else
						return true;
				}
			}
		}
		else return false;
	}
	else return true;
}

bool Lexem::operator!=(const Lexem & a) const
{
	return (!(*this == a));
}

string Lexem::return_s() const
{
	return stroka;
}

double Lexem::return_n() const
{
	return number;
}

char Lexem::return_c() const
{
	return symbol;
}

int Lexem::return_b() const
{
	return num;
}

double rank_number(const double a, const int i)
{
	double b = 1;
	for (int j = 0; j < i; j++)
		b *= a;
	return b;
}
ostream & operator<<(ostream & out, const Lexem & v)
{
	if (v.num == 0)
		out << v.symbol;
	else
		if (v.num == 1)
			out << v.number;
		else
			out << v.stroka;
	return out;
}
double converter_in_number(const string &s)
{
	int len = s.length();
	double a = 0.0;
	int i = 0;
	for (i = 0; ((i < len) && (s[i] != '.')); i++)
		a = a * 10.0 + (s[i] - '0');
	int j = i;
	if (s[j] == '.')
		for (i = j + 1; i < len; i++)
			a = a + (s[i] - '0') / (rank_number(10.0, (i - j)));
	return a;
}

int prioritet(const char s)
{
	switch (s)
	{
	case '(':
		return 0;
		break;
	case '+':
		return 1;
		break;
	case '-':
		return 1;
		break;
	case '*':
		return 2;
		break;
	case '/':
		return 2;
		break;
	}
}

double evaluation_of_expression(const double a, const double b, const char c)
{
	switch (c)
	{
	case '+':
		return (a + b);
		break;
	case '-':
		return (b - a);
		break;
	case '*':
		return (a * b);
		break;
	case '/':
		return (b / a);
		break;
	}
}

bool check_for_correctness(const string & s)
{
	if (s !="")
	{
		string str;
		str += ' ';
		str += s;
		str += ' ';
		string symbols = "+-*/";
		string wrong_symbols = "=!@#$%^&?;:<>{},' '";
		int len = str.length();
		int l = 0;
		int z = 0;
		if ((symbols.find(str[1]) != symbols.npos) && (str[1] != '-'))
		{
			cout << "The sign at the beginning of the expression." << endl;
			return false;
		}
		if (symbols.find(str[len - 2]) != symbols.npos)
		{
			cout << "The sign at the end of the expression." << endl;
			return false;
		}
		for (int i = 1; i < len - 1; i++)
		{
			if ((symbols.find(str[i]) != symbols.npos) && (symbols.find(str[i + 1]) != symbols.npos))
			{
				cout << "Two sign." << endl;
				return false;
			}
			if ((str[i] == '(') && (str[i + 1] != '-') && (symbols.find(str[i + 1]) != symbols.npos))
			{
				cout << "The sign after the opening bracket." << endl;
				return false;
			}
			if ((symbols.find(str[i]) != symbols.npos) && (str[i + 1] == ')'))
			{
				cout << "The sign before closing bracket." << endl;
				return false;
			}
			if ((str[i] == '(') && (str[i + 1] == ')'))
			{
				cout << "The empty brackets" << endl;
				return false;
			}
			if ((str[i] == ')') && (str[i + 1] == '('))
			{
				cout << "The error in expression." << endl;
				return false;
			}
			if (wrong_symbols.find(str[i]) != wrong_symbols.npos)
			{
				cout << "Wrong symbols." << endl;
				return false;
			}
			if (((str[i] >= '0') && (str[i] <= '9') && (str[i + 1] == '(')))
			{
				cout << "There are not enough signs in the expression." << endl;
				return false;
			}
			if (((str[i] == ')') && (str[i + 1] >= '0') && (str[i + 1] <= '9')))
			{
				cout << "There are not enough signs in the expression." << endl;
				return false;
			}
			if ((str[i] == '.') && (((str[i + 1] < '0') || (str[i + 1] > '9')) || ((str[i - 1] < '0') || (str[i - 1] > '9'))))
			{
				cout << "The error in expression." << endl;
				return false;
			}
			if (((str[i] >= '0') && (str[i] <= '9')) || (str[i] == '.'))
			{
				if ((str[i] == '.'))
					z++;
				if (z > 1)
				{
					cout << "The error in expression." << endl;
					return false;
				}
			}
			else
				z = 0;
			if (str[i] == ')')
				l--;
			if (l < 0)
			{
				cout << "A lot of close brackets." << endl;
				return false;
			}			
			if (str[i] == '(')
				l++;
		}
		if (l > 0)
		{
			cout << "A lot of open brackets." << endl;
			return false;
		}
		return true;
	}
	else
	{
		cout << "Nothing has been entered." << endl;
		return false;
	}
}
Stack<Lexem> convert_string_to_stack(const string & c)
{
	if (!check_for_correctness(c))
		throw "No correctness";
	string str;
	str = str + ' ';
	str = str + c;
	int len = str.length();
	Stack<Lexem> stack(len);
	string str_num;
	string str_param;
	Lexem a;
	int k = 1;
	bool p = false;
	if (str[1] == '-')
	{
		p = true;
		k++;
	}
	for (int i = k; i < len; i++)
	{
		if ((str[i] == '-') && (str[i - 1] == '('))
			p = true;
		else
		{
			if ((((str[i] >= 'a') && (str[i] <= 'z')) || ((str[i] >= 'A') && (str[i] <= 'Z'))) || ((str[i] <= '9') && (str[i] >= '0') && (str_param != "")))
				str_param = str_param + str[i];
			else
			{
				if (str_param != "")
				{
					if (p)
					{
						str_param = '-' + str_param;
						p = false;
					}
					a = str_param;
					stack.push(a);
					str_param = "";
				}
				if ((((str[i] <= '9') && (str[i] >= '0')) || (str[i] == '.')))
					str_num = str_num + str[i];
				else
				{
					if (str_num != "")
					{
						double q = converter_in_number(str_num);
						if (p)
						{
							q *= -1;
							p = false;
						}
						a = q;
						stack.push(a);
						str_num = "";
					}
					a = str[i];
					stack.push(a);
				}
			}
		}
	}
	if (str_param != "")
	{
		if (p)
		{
			str_param = '-' + str_param;
			p = false;
		}
		a = str_param;
		stack.push(a);
	}
	if (str_num != "")
	{
		double q = converter_in_number(str_num);
		if (p)
		{
			q *= -1;
			p = false;
		}
		a = q;
		stack.push(a);
	}
	return stack;
}
Stack<Lexem> polish_notation(const Stack<Lexem>& st)
{
	Stack<Lexem> stack = st;
	stack.convert();
	Stack<Lexem> stack2(st.get_nElem());
	Lexem elem_stack;
	Stack<char> sym_stack;
	while (!(stack.check_void()))
	{
		elem_stack = stack.pop();
		if (elem_stack.return_b() != 0)
			stack2.push(elem_stack);
		else
		{
			char c = elem_stack.return_c();
			if (sym_stack.check_void())
				sym_stack.push(c);
			else
			{
				if (c == '(')
					sym_stack.push(c);
				else
				{
					if (c == ')')
					{
						while (sym_stack.top() != '(')
							stack2.push(sym_stack.pop());
						sym_stack.pop();
					}
					else
					{
						while ((!(sym_stack.check_void())) && (prioritet(c) <= prioritet(sym_stack.top())))
							stack2.push(sym_stack.pop());
						sym_stack.push(c);
					}
				}
			}
		}
	}
	while (!(sym_stack.check_void()))
		stack2.push(sym_stack.pop());
	return stack2;
}
double answer(const Stack<Lexem>& s)
{
	Stack<Lexem> stack = s;
	Stack<Lexem> stack2;
	int i = stack.get_nElem();
	Lexem* st = new Lexem[i / 2 + 1];
	i = 0;
	while (!(stack.check_void()))
	{
		Lexem a = stack.pop();
		if (a.return_b() == 2)
		{
			int k = 1;
			string min = a.return_s();
			if (min[0] == '-')
			{
				k = -1;
				min.erase(0, 1);
				a = min;
			}
			bool p = true;
			for (int j = 0; ((j < i) && (p)); j++)
				if (st[j].return_s() == a.return_s())
				{
					p = false;
					a = st[j];
				}
			if (p)
			{
				cout << "Write parametr " << a.return_s() << endl;
				double w;
				cin >> w;
				Lexem a(a.return_b(), a.return_s(), k * w, a.return_c());
				a = k * w;
				stack2.push(a);
				st[i++] = a;
			}
			else
			{
				Lexem l = a.return_n();
				if (k == -1)
					l = k * a.return_n();
				stack2.push(l);
			}
		}
		else
			stack2.push(a);
	}
	Stack<double> num_stack;
	while (!(stack2.check_void()))
	{
		Lexem w = stack2.pop();
		if (w.return_b() != 0)
			num_stack.push(w.return_n());
		else
		{
			double number_1 = num_stack.pop();
			double number_2 = num_stack.pop();
			char sym = w.return_c();
			num_stack.push(evaluation_of_expression(number_1, number_2, sym));
		}
	}
	delete[] st;
	return num_stack.top();
}