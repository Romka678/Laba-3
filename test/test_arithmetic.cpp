// тесты дл€ вычислени€ арифметических выражений
#include <gtest.h>
#include "stack.h"
#include "arithmetic.h"

class GlobalStackLexmem : public ::testing::Test
{
protected:
	Stack<Lexem> s1;
	Stack<Lexem> s2;

public:
	GlobalStackLexmem()
	{
		s1.push(5.0);    
		s1.push('+');   
		s1.push(5.0);
		s1.push('+');
		s1.push(10.0);
		s1.push('-');
		s1.push('(');
		s1.push(10.0);
		s1.push('*');
		s1.push(2.0);
		s1.push('-');
		s1.push(10.0);
		s1.push(')');

		s2.push(5.0);
		s2.push(5.0);
		s2.push('+');
		s2.push(10.0);
		s2.push('+');
		s2.push(10.0);
		s2.push(2.0);
		s2.push('*');
		s2.push(10.0);
		s2.push('-');
		s2.push('-');
	}
	~GlobalStackLexmem() {}
};

string str1[22] = { "", "+","(", ")", ")5+5(", "5+-5", "5 + 5", "(5+5", "5+5)", "5(5+5)", "(5+5)5", "5.5.5", "5..5", "a.5+5", "(5+5)(5+5)", "(5+5+)", "(+5+5)", "(5+(5))))" ,"*5+5", "5+5*",".5","5.."};
string str2[5] = { "5+5+10-(10*2-10)", "-5", "(-5)", "a+1", "a1+2" };
string str3[6] = { "2+3", "10-5", "20/4", "2.5*2", "-3+8" , "15-(6+4)" };

class ParamArithmetic : public ::testing::TestWithParam<string>
{
protected:
	string st;
public:
	ParamArithmetic() { st = GetParam(); }
	~ParamArithmetic() {}
};
class ParamArithmetic2 : public ParamArithmetic
{
protected:
	string st2;
public:
	ParamArithmetic2() { st2 = GetParam(); }
	~ParamArithmetic2() {}
};
class ParamArithmetic3 : public ParamArithmetic2
{
protected:
	string st3;
public:
	ParamArithmetic3() { st3 = GetParam(); }
	~ParamArithmetic3() {}
};

TEST_P(ParamArithmetic, isIncorrect1)
{
	EXPECT_EQ(false, check_for_correctness(st));
}
INSTANTIATE_TEST_CASE_P(i1, ParamArithmetic, ::testing::ValuesIn(str1));

TEST_P(ParamArithmetic2, isIncorrect2)
{
	EXPECT_EQ(true, check_for_correctness(st2));
}
INSTANTIATE_TEST_CASE_P(i2, ParamArithmetic2, ::testing::ValuesIn(str2));

TEST_P(ParamArithmetic3, isIncorrect3)
{
	Stack<Lexem> a = convert_string_to_stack(st3);
	a = polish_notation(a);
	EXPECT_EQ(5, answer(a));
}
INSTANTIATE_TEST_CASE_P(i3, ParamArithmetic3, ::testing::ValuesIn(str3));

TEST_F(GlobalStackLexmem, work_convert_string_to_stack)
{
	string a = "5+5+10-(10*2-10)";
	Stack<Lexem> b = convert_string_to_stack(a);
	EXPECT_EQ(s1, b);
}
TEST_F(GlobalStackLexmem, work_polish_notation)
{
	EXPECT_EQ(s2, polish_notation(s1));
}
TEST_F(GlobalStackLexmem, work_answer)
{
	EXPECT_EQ(10,answer(s2));
}
TEST(arithmetic, to_get_nElem)
{
	string tmp="a+5+1-20/2";
	Stack<Lexem> h = convert_string_to_stack(tmp);
	int k = h.get_nElem();
	EXPECT_EQ(9, k);
}
//¬вод одной и той же переменной в выражении,еще тестов ,что правильно бьет на лексемы,и польскую запись