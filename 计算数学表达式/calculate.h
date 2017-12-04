//计算数学表达式
#ifndef calculate_
#define calculate_
#include "arrayStack.h"
double calculate(string &str);
bool isNum(char a);
void pushNum(char a);
void pushOp(char ch);
double calc(char op);
class operators {//创建一个运算符类，有两个成员变量，char op为运算符的char类型，int PRI为运算符的优先级
public:
	operators() {}
	operators(char a) :op(a) {//设定运算符优先级，（为1，*/为2，+-为3,)为4
		if (op == '(')
			PRI = 1;
		else if (op == '*' || op == '/')
			PRI = 2;
		else if (op == '+' || op == '-')
			PRI = 3;
		else if (op == ')')
			PRI = 4;
	}
	//重载比较操作符，PRI小的优先级高，方便进行比较
	bool operator>(operators &right) {
		return PRI < right.PRI;
	}
	bool operator<(operators &right) {
		return PRI > right.PRI;
	}
	bool operator==(operators &right) {
		return PRI == right.PRI;
	}
	char operator*() {//返回操作符，将该类成员转化为char型
		return op;
	}
private:
	char op;
	int PRI;//优先级
};
//两个全局栈，分别存储数字和运算符
arrayStack<double> numStack;//数字栈
arrayStack<operators> opStack;//运算符栈

double calculate(string &str) {
	for (int i = 0; i < (int)str.length(); i++) {//每次从字符串中取出一个字符，判断是数字还是运算符
		if (str[i] != ' '){
			if (isNum(str[i]))//isNum函数判断是否为数字
				pushNum(str[i]);//该函数将数字压栈
			else
				pushOp(str[i]);//该方法将符号压栈
		}
	}
	double result = 0;
	while (!opStack.empty()) {//将剩余表达式计算
		result = calc(*(opStack.top()));
		numStack.push(result);
	}
	return result;//返回运算结果
}

bool isNum(char a) {//判断是数字还是运算符,是数字返回true，是运算符返回false，否则抛出异常
	if (a >= '0'&&a <= '9')
		return true;
	else if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')')
		return false;
	else
		throw illegalInputData();
}
void pushNum(char a) {//数字压栈
	int num = a - '0';//将char转化为int
	numStack.push(num);//将数字压栈
}
void pushOp(char ch) {//运算符压栈
	operators op(ch);
	if (opStack.empty()||opStack.top()<op)//若栈顶运算符优先级低于当前运算符或栈为空
		opStack.push(op);//直接将运算符入栈
	else {//若栈顶运算符优先级高于当前运算符
		if (*(opStack.top()) == '(') {//先判断栈顶符号是否为左括号，如果是，将该运算符也压栈
			opStack.push(op);
			return;
		}
		double result = calc(*(opStack.top()));//计算表达式
		numStack.push(result);//将运算后的结果压入数字栈
		if (ch == ')') {//再判断是否为有括号
			while (*(opStack.top()) != '(') {//将两括号之间的运算全部计算
				double result = calc(*(opStack.top()));
				numStack.push(result);
			}
			opStack.pop();//删除左括号（
		}
		else
			opStack.push(op);
	}
}

double calc(char op) {//执行运算，参数为运算符类型
	double right = numStack.top();//从数字栈顶取右操作数
	numStack.pop();
	double left = numStack.top();//从数字栈顶取左操作数
	numStack.pop();
	opStack.pop();
	switch (op) {
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left*right;
	case '/':
		return left / right;
	default:
		throw illegalInputData();
	}
}

#endif // !calculate_

