#include"calculate.h"
int main() {
	string str;
	while (true) {
		cout << "请输入计算表达式" << endl;
		cin >> str;
		cout << str<<'='<< calculate(str) << endl;
		cout << "__________________" << endl;
	}
	
	system("pause");
	return 0;
}