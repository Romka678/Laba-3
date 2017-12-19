// тесты для стека
#include "stack.h"
#include <gtest.h>

class GlobalStack : public ::testing::Test
{
protected:
	Stack<int> a;
public:
	GlobalStack()
	{
		for (int i = 0; i < 5; i++)
			a.push(i);
	}
	~GlobalStack() {}
};
TEST(Stack, negative_length)
{
	ASSERT_ANY_THROW(Stack<int> a(-1));
}
TEST(Stack, too_large_number)
{
	ASSERT_ANY_THROW(Stack<int> a(MAXElem + 1));
}
TEST_F(GlobalStack, work_get_nElem)
{
	EXPECT_EQ(5, a.get_nElem());
}
TEST_F(GlobalStack, work_top)
{
	EXPECT_EQ(4, a.top());
}
TEST_F(GlobalStack, work_push)
{
	a.push(7);
	EXPECT_EQ(7, a.top());
	EXPECT_EQ(6, a.get_nElem());
}
TEST_F(GlobalStack, work_pop)
{
	a.push(7);
	a.pop();
	EXPECT_NE(7, a.top());
	EXPECT_EQ(5, a.get_nElem());
}
TEST_F(GlobalStack, work_clean_stack)
{
	a.clean_stack();
	EXPECT_EQ(0, a.get_nElem());
}
TEST_F(GlobalStack, work_check_void)
{
	a.clean_stack();
	EXPECT_EQ(true, a.check_void());
}
TEST_F(GlobalStack, work_copy_constructor)
{
	Stack<int> a1 = a;
	EXPECT_EQ(a, a1);
}
TEST_F(GlobalStack, work_operator)
{
	Stack<int> a1;
	a1 = a;
	EXPECT_EQ(a, a1);
}
TEST_F(GlobalStack, work_converter)
{
	Stack<int> a1;
	for (int i = 4; i >= 0; i--)
		a1.push(i);
	a1.convert();
	EXPECT_EQ(a, a1);
}