//������ѧ���ʽ
#ifndef calculate_
#define calculate_
#include "arrayStack.h"
double calculate(string &str);
bool isNum(char a);
void pushNum(char a);
void pushOp(char ch);
double calc(char op);
class operators {//����һ��������࣬��������Ա������char opΪ�������char���ͣ�int PRIΪ����������ȼ�
public:
	operators() {}
	operators(char a) :op(a) {//�趨��������ȼ�����Ϊ1��*/Ϊ2��+-Ϊ3,)Ϊ4
		if (op == '(')
			PRI = 1;
		else if (op == '*' || op == '/')
			PRI = 2;
		else if (op == '+' || op == '-')
			PRI = 3;
		else if (op == ')')
			PRI = 4;
	}
	//���رȽϲ�������PRIС�����ȼ��ߣ�������бȽ�
	bool operator>(operators &right) {
		return PRI < right.PRI;
	}
	bool operator<(operators &right) {
		return PRI > right.PRI;
	}
	bool operator==(operators &right) {
		return PRI == right.PRI;
	}
	char operator*() {//���ز��������������Աת��Ϊchar��
		return op;
	}
private:
	char op;
	int PRI;//���ȼ�
};
//����ȫ��ջ���ֱ�洢���ֺ������
arrayStack<double> numStack;//����ջ
arrayStack<operators> opStack;//�����ջ

double calculate(string &str) {
	for (int i = 0; i < (int)str.length(); i++) {//ÿ�δ��ַ�����ȡ��һ���ַ����ж������ֻ��������
		if (str[i] != ' '){
			if (isNum(str[i]))//isNum�����ж��Ƿ�Ϊ����
				pushNum(str[i]);//�ú���������ѹջ
			else
				pushOp(str[i]);//�÷���������ѹջ
		}
	}
	double result = 0;
	while (!opStack.empty()) {//��ʣ����ʽ����
		result = calc(*(opStack.top()));
		numStack.push(result);
	}
	return result;//����������
}

bool isNum(char a) {//�ж������ֻ��������,�����ַ���true�������������false�������׳��쳣
	if (a >= '0'&&a <= '9')
		return true;
	else if (a == '+' || a == '-' || a == '*' || a == '/' || a == '(' || a == ')')
		return false;
	else
		throw illegalInputData();
}
void pushNum(char a) {//����ѹջ
	int num = a - '0';//��charת��Ϊint
	numStack.push(num);//������ѹջ
}
void pushOp(char ch) {//�����ѹջ
	operators op(ch);
	if (opStack.empty()||opStack.top()<op)//��ջ����������ȼ����ڵ�ǰ�������ջΪ��
		opStack.push(op);//ֱ�ӽ��������ջ
	else {//��ջ����������ȼ����ڵ�ǰ�����
		if (*(opStack.top()) == '(') {//���ж�ջ�������Ƿ�Ϊ�����ţ�����ǣ����������Ҳѹջ
			opStack.push(op);
			return;
		}
		double result = calc(*(opStack.top()));//������ʽ
		numStack.push(result);//�������Ľ��ѹ������ջ
		if (ch == ')') {//���ж��Ƿ�Ϊ������
			while (*(opStack.top()) != '(') {//��������֮�������ȫ������
				double result = calc(*(opStack.top()));
				numStack.push(result);
			}
			opStack.pop();//ɾ�������ţ�
		}
		else
			opStack.push(op);
	}
}

double calc(char op) {//ִ�����㣬����Ϊ���������
	double right = numStack.top();//������ջ��ȡ�Ҳ�����
	numStack.pop();
	double left = numStack.top();//������ջ��ȡ�������
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

