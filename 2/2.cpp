#include <iostream>
#include <algorithm>
#include <cstring>
#include <stack>
#include <cmath>

using namespace std;
char s[1000];
int  i;

//将字符串转换成double型数字
double ChangeToNum(int & pos)
{
	double integer = 0.0;
	double remainder = 0.0;

	while (s[pos] >= '0' && s[pos] <= '9')
	{
		integer *= 10;
		integer += (s[pos] - '0');
		pos++;
	}
	if (s[pos] == '.'){
		pos++;
		int c = 1;
		while (s[pos] >= '0' && s[pos] <= '9')
		{
			double t = s[pos] - '0';
			t *= pow(0.1, c);
			c++;
			remainder += t;
			pos++;
		}
	}
	return integer + remainder;
}

//返回操作符ch的优先级
int GetLevel(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '(':
		return 0;
	case '#':
		return -1;
	};
}

//进行运算 a1 op a2
//a1、a2为操作数 op为操作符
double Operate(double a1, char op, double a2)
{
	switch (op)
	{
	case '+':
		return a1 + a2;
	case '-':
		return a1 - a2;
	case '*':
		return a1 * a2;
	case '/':
		return a1 / a2;
	};
}

//运算主过程
//维护一个操作符栈 一个操作数栈
double calc()
{

	stack<char> optr;//
	stack<double> opnd;

	optr.push('#');
	int len = strlen(s);
	bool is_minus = true;
	for (i = 0; i < len;){
		if (s[i] == '-' && is_minus){
			opnd.push(0);
			optr.push('-');
			i++;
		}
		else if (s[i] == ')'){
			is_minus = false;
			i++;
			while (optr.top() != '('){
				double a2 = opnd.top();
				opnd.pop();
				double a1 = opnd.top();
				opnd.pop();
				char op = optr.top();
				optr.pop();
				double result = Operate(a1, op, a2);
				opnd.push(result);
			}
			optr.pop();
		}//运算括号内的所有表达式

		else if (s[i] >= '0' && s[i] <= '9'){
			is_minus = false;
			opnd.push(ChangeToNum(i));
		}
		else if (s[i] == '(') {
			is_minus = true;
			optr.push(s[i]);
			i++;
		}
		else {
			while (GetLevel(s[i]) <= GetLevel(optr.top())) {
				double a2 = opnd.top();
				opnd.pop();
				double a1 = opnd.top();
				opnd.pop();
				char op = optr.top();
				optr.pop();

				double result = Operate(a1, op, a2);
				opnd.push(result);
			}//当即将加入的运算符优先级大于栈顶，先运算栈内的运算符
			optr.push(s[i]);
			i++;
		}
	}

	while (optr.top() != '#'){
		double a2 = opnd.top();
		opnd.pop();
		double a1 = opnd.top();
		opnd.pop();
		char op = optr.top();
		optr.pop();
		double result = Operate(a1, op, a2);
		opnd.push(result);
	}

	return opnd.top();
}

//判断表达式是否合法的函数
//若()数量不等不合法
//若存在非+-*/或数字的字符 则为不合法
bool judge() {
	int l = 0, r = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == '(') { l++; continue; }
		if (s[i] == ')') { r++; continue; }
		if (s[i] <= '9' && s[i] >= '0') continue;
		if (s[i] == '+') continue;
		if (s[i] == '-') continue;
		if (s[i] == '*') continue;
		if (s[i] == '/') continue;
		return 0;
	}
	if (l != r) return 0;
	return 1;
}

int main()
{
	while (cin >> s) {
		if (s == "#") {
			cout << "程序结束\n";
			exit(0);
		}
		if (!judge()) {
			cout << "表达式错误，请重新输入" << endl;
			continue;
		}
		cout << "表达式结果为：" << calc() << endl << endl;
	}
	return 0;
}