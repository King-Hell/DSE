#include"calculate.h"
int main() {
	string str;
	while (true) {
		cout << "�����������ʽ" << endl;
		cin >> str;
		cout << str<<'='<< calculate(str) << endl;
		cout << "__________________" << endl;
	}
	
	system("pause");
	return 0;
}