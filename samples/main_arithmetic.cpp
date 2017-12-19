// реализация пользовательского приложения

#include "arithmetic.h"
#include "stack.h"
void main()
{
	int h = 1;
	while (h == 1)
	{
		int f = 1;
		string str;
		cout << "Write the expression." << endl;
		getline(cin, str);
		while (!(check_for_correctness(str)))
		{
			cout << "Write the expression again." << endl;
			getline(cin, str);
		}
		Stack<Lexem> a;
		a = convert_string_to_stack(str);
		a = polish_notation(a);
		while (f == 1)
		{
			cout << answer(a) << endl;
			cout << "Do you want to repeat with other parametrs?" << endl;
			cout << "1 - yes" << endl;
			cout << "2 - no" << endl;
			cin >> f;
		}
		cout << "Do you want to repeat?" << endl;
		cout << "1 - yes" << endl;
		cout << "2 - no" << endl;
		cin >> h;
	}
}
