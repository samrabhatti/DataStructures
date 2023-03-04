#include<iostream>
#include<stack>
using namespace std;

void Input(char s[])
{
	cout << "Enter a string to check if it is balanced or not: \n";
	cin.getline(s, 50);
}

bool Balanced(char s[])
{
	stack<char> stack;
	int length = strlen(s);

	for (int i = 0; i < length; i++)
	{
		if (s[i] == '0')
		{
			stack.push(s[i]);
		}

		else if (s[i] == '1')
		{
			if (stack.empty())
				return false;
			stack.pop();
		}

		else
		{
			cout << "Invalid\n";
		}
	}

	if (stack.empty() == false)
		return false;
	else
		return true;

}

int main()
{
	char str[50];
	Input(str);

	if (Balanced(str) == true)
		cout << "Balanced\n";
	else
		cout << "Not Balanced\n";

	system("pause");
	return 0;
}