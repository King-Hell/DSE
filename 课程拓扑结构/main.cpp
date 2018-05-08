#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<list>
#include<set>
using namespace std;

class classMap :public multimap<int, int> {
public:
	void insert(int first, int second) {
		multimap::insert(pair<int, int>(first, second));
	}
};

class graph {
public:
	graph() {}
	graph(int size) {
		aList.resize(size + 1);
	}
	void insert(int first, int second) {
		aList[first].push_back(second);
		m.insert(second, first);
	}

	int maxV(vector<int> &Ve, int second) {
		//����second�γ����翪��ѧ��
		int max = 0;
		for (classMap::iterator i = m.equal_range(second).first; i != m.equal_range(second).second; i++)
			if (Ve[(*i).second] > max)
				max = Ve[(*i).second];
		return max;
	}
	int size() { return aList.size() - 1; }


	vector<list<int>> aList;
	classMap m;
};

queue<int>& findFirstClass(graph &g) {
	//�ҳ����в������пγ̵Ŀ�
	queue<int> *q = new queue<int>;
	set<int> secondClass;
	for (int i = 1; i <(int) g.aList.size(); i++)
		for (list<int>::iterator j = g.aList[i].begin(); j != g.aList[i].end(); j++)
			secondClass.insert((*j));
	for (int i = 1; i < (int)g.aList.size(); i++)
		if (secondClass.find(i) == secondClass.end())
			q->push(i);
	return *q;
}

int main() {
	graph s(7);
	vector<set<int>> classList;//�γ��嵥
	vector<int> Ve(s.size() + 1);//�������翪��ѧ��
	s.insert(1, 3);
	s.insert(2, 4);
	s.insert(3, 5);
	s.insert(4, 6);
	s.insert(3, 7);
	queue<int> q = findFirstClass(s);
	while (!q.empty()) {
		int c = q.front();
		for (list<int>::iterator i = s.aList[c].begin(); i != s.aList[c].end(); i++)
			q.push((*i));//��c�γ̵ĺ����γ̼������
		Ve[c] = s.maxV(Ve, c) + 1;//c�γ������ڵ�Ve[c]ѧ�ڿ���
		q.pop();
		if ((int)classList.size() <= Ve[c])
			classList.resize(Ve[c] + 1);
		classList[Ve[c]].insert(c);
	}
	cout << "������Ҫ" << classList.size() - 1 << "ѧ��" << endl;
	for (int i = 1; i <(int) classList.size(); i++) {
		cout << "��" << i << "ѧ�ڣ�";
		for (set<int>::iterator j = classList[i].begin(); j != classList[i].end(); j++)
			cout << (*j) << "  ";
		cout << endl;
	}
	system("pause");
	return 0;

}



