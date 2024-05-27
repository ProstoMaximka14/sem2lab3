#include <iostream>
#include <string>
using namespace std;

struct Steak
{
	string value;
	Steak* next=NULL;
};

void print_st(Steak* result)
{
	while (result != 0)
	{
		cout << result->value << ' ';
		result = result->next;
	}
}

bool is_oper(char a)
{
	if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')')
	{
		return true;
	}
	return false;
}

int prior(char a)
{
	switch (a) 
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
	case ')':
		return 0;
	default:
		return -1;
	}
}

void transport(Steak*& op, Steak*& res)
{
	while (op->next != 0)
	{
		Steak* now;
		now = new Steak;
		now->value = op->value;
		now->next = res;
		res = now;
		op = op->next;
	}
	Steak* now;
	now = new Steak;
	now->value = op->value;
	now->next = res;
	res = now;
	op = op->next;
}

void znak(Steak*& op, char a, Steak*& res)
{
	Steak* oper;
	oper = new Steak;
	oper->value = a;
	if (op == 0)
	{
		oper->next = 0;
	}
	else
	{
		if (prior(a) < prior(op->value[0]))
		{
			transport(op, res);
			oper->next = 0;
		}
		else
		{
			oper->next = op;
		}
	}
	op = oper;
	cout << "Steak simbols ";
	print_st(op);
	cout << '\n';
}

void str(Steak*& start, string a)
{
	Steak* work;
	work = new Steak;
	work->value = a;
	if (start == 0) 
	{
		work->next = 0;
	}
	else
	{
		work->next = start;
	}
	start = work;
	cout << "Steak result ";
	print_st(start);
	cout << '\n';
}

Steak* pr_pol_nat(int len, string example)
{
	string b;
	Steak* result=0, * oper=0;
	for (int i = len-1; i >= 0; i--)
	{
		if (is_oper(example[i]))
		{
			str(result, b);
			b = "";
			znak(oper, example[i], result);
		}
		else
		{
			b += example[i];
		}
	}
	str(result, b);
	transport(oper, result);
	oper = result;
	cout << "Pol nat = ";
	print_st(result);
	return oper;
}

void obr_transport(Steak*& res)
{
	Steak* head = 0;
	while (res->next != 0)
	{
		Steak* now;
		now = new Steak;
		now->value = res->value;
		if (head == 0)
		{
			now->next = 0;
		}
		else
		{
			now->next = head;
		}
		head = now;
		res = res->next;
	}
	Steak* now;
	now = new Steak;
	now->value = res->value;
	now->next = head;
	head = now;
	res = head;
}

Steak* obr_pol_nat(int len, string example)
{
	string b;
	Steak* result = 0, * oper = 0;
	for (int i = 0; i <len; i++)
	{
		if (is_oper(example[i]))
		{
			str(result, b);
			b = "";
			znak(oper, example[i], result);
		}
		else
		{
			b += example[i];
		}
	}
	str(result, b);
	transport(oper, result);
	obr_transport(result);
	oper = result;
	cout << "Reverse Pol. nat = ";
	print_st(result);
	return oper;
}

int mth(int value1, int value2, char zn)
{
	switch (zn) 
	{
	case '+':
		return value1 + value2;
		break;
	case '-':
		return value1 - value2;
		break;
	case '*':
		return value1 * value2;
		break;
	case '/':
		return value1 / value2;
		break;
	default:
		break;
	}
}

void pr_ch(Steak*& now)
{
	obr_transport(now);
	Steak* ch = 0, * head = 0;
	while (now != 0)
	{
		if (!is_oper(now->value[0]))
		{
			if (now->value != "")
			{
				ch = new Steak;
				ch->next = head;
				ch->value = now->value;
				head = ch;
			}
		}
		else
		{
			if (head->next == 0)
			{
				cout << "Eror input";
				return;
			}
			else
			{
				head->next->value = to_string(mth(stoi(head->value), stoi(head->next->value), now->value[0]));
				head = head->next;
				cout << "operation ";
				cout << now->value << '\n';
			}
		}
		now = now->next;
		cout << "Stek result ";
		print_st(head);
		cout << '\n';
	}
	cout << "Result = ";
	cout << head->value;
}

void obr_ch(Steak*& now)
{
	Steak* ch = 0, * head=0;
	while (now != 0)
	{
		if (!is_oper(now->value[0]))
		{
			if (now->value != "")
			{
				ch = new Steak;
				ch->next = head;
				ch->value = now->value;
				head = ch;
			}
		}
		else
		{
			if (head->next == 0)
			{
				cout << "Eror input";
				return;
			}
			else
			{
				head->next->value = to_string(mth(stoi(head->next->value), stoi(head->value), now->value[0]));
				head = head->next;
				cout << "operation ";
				cout << now->value << '\n';
			}	
		}
		cout << "Stek result ";
		print_st(head);
		now = now->next;
		cout << '\n';
	}
	cout << "Result = ";
	cout << head->value;
}

void menu()
{
	bool p = true;
	while (p)
	{
		system("cls");
		string example;
		Steak* pr_nat, * obr_nat;
		cout << "Enter example ";
		cin >> example;
		int len;
		len = size(example);
		pr_nat = pr_pol_nat(len, example);
		cout << '\n';
		cout << '\n';
		obr_nat = obr_pol_nat(len, example);
		cout << '\n';
		cout << '\n';
		system("pause");
		string b, c;
		Steak* prov = 0, * prova = 0;
		prov = obr_nat;
		prova = pr_nat;
		while (prov != 0)
		{
			if (!is_oper(prov->value[0]) and !isdigit(prov->value[0]) and prov->value != "")
			{
				cout << "Enter value var " << prov->value << ' ';
				c = prov->value;
				cin >> prov->value;
				b = prov->value;
				while (prova->value != c)
				{
					prova = prova->next;
				}
				prova->value = b;
			}
			prov = prov->next;
		}
		cout << "Pol. nat ";
		print_st(pr_nat);
		cout << '\n';
		cout << '\n';
		pr_ch(pr_nat);
		cout << '\n';
		cout << "Reverse Pol. nat ";
		print_st(obr_nat);
		cout << '\n';
		obr_ch(obr_nat);
		cout << "Do you want to rewrite example (pres 1-yes) ";
		int a;
		cin >> a;
		if (a!=1)
		{
			p = false;
		}
	}
}

int main()
{
	menu();
}
