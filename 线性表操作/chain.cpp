#include"chain.h"
int main() {
	chain<int> a;
	//��������
	cout << "��������" << endl;
	cin >> a;
	cout << a<<endl;
	//���Բ���
	cout << "���Բ���" << endl;
	chain<int> b;
	b.insert(1);
	b.insert(2);
	b.insert(3);
	b.insert(4);
	cout << "b ���ӦΪ4 3 2 1" << endl << b << endl;
	//����ɾ��
	cout << "����ɾ��" << endl;
	b.erase(2);
	b.erase(4);
	cout << "b ���ӦΪ3 1" << endl<<b<<endl;
	//��������
	cout << "��������" << endl;
	cout << "���ӦΪ0 -1" << endl;
	cout<<b.indexOf(3)<<" ";
	cout << b.indexOf(2) << endl;
	//���Է������
	cout << "���Է������" << endl;
	a.inverse();
	//���Ժϲ�
	cout << "���Ժϲ�" << endl;
	chain<int> d;
	chain<int> e;
	d.insert(3);
	d.insert(1);
	e.insert(4);
	e.insert(2);
	chain<int>  c;
	c.merge(d, e);
	cout << "���ӦΪ1 2 3 4" << endl;
	cout << c << endl;
	system("pause");
	return 0;
}