//�Թ�Ѱ·
#include <iostream>
#include <fstream>
#include<Windows.h>
#include "arrayStack.h"
#include "position.h"
#include "make2dArray.h"

// ȫ�ֱ���
int **maze, rows, cols;//��ά����maze����Թ����ݣ�rows��cols�ֱ�Ϊ�Թ�������������
arrayStack<position>* path;  // ·��ջ

void setColor(unsigned short forecolor = 7, unsigned short backgroudcolor = 0){
	//�ú����������������ɫ��Ĭ��Ϊ�ڵװ���
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //��ȡ���������
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //�����ı�������ɫ
}

void inputMaze(){// �����Թ�����
	//���ļ�����һ���Թ�����
	//�Թ����ݵ�ǰ��������Ϊ��С��������0�����ͨ����1������ͨ��
	ifstream in("data2.txt");
	if (!in.is_open())
		throw "Loading data error";
	in >> rows;//�����Թ�������
	in >> cols;//�����Թ�������
	make2dArray(maze, rows + 2, cols + 2);//��ʼ���Թ����飬������Χǽ
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			in >> maze[i][j];//��0��1���ݲ���maze������
			if (maze[i][j] == 1) {
				setColor(4, 0);
				cout << "�~";//����ɲ���ͨ������ӡ��ɫ��
			}
			else {
				setColor(2,0);
				cout << "�~";//�����ͨ������ӡ��ɫ��
			}
		}
		cout << endl;
	}
	setColor();
	cout << "Load data successfully" << endl;

}

bool findPath(){//Ѱ��һ������ڣ�1��1�������ڣ�rows,cols����·��
	//����ҵ�����true��û�з���false
	//�÷���Ϊ��Ҫ������˼���ǽ�һ����ͨ��λ��ѹ��·��ջ�У�Ȼ�����ΰ��������ϵ�˳��Ѱ��
	//����ͨ������һ��·���㲢ѹ��ջ�У���Ѱ·�������ʱ������true
	//��·��ջΪ��ʱ������û��·������ͨ��������false
	path = new arrayStack<position>;//·��ջ
	// ��ʼ��ƫ����
	position offset[4];//�趨�ĸ�Ѱ·����
	offset[0].row = 0; offset[0].col = 1;   // ��
	offset[1].row = 1; offset[1].col = 0;   // ��
	offset[2].row = 0; offset[2].col = -1;  // ��
	offset[3].row = -1; offset[3].col = 0;  // ��

	// ��ʼ���Թ���Χ�ϰ�ǽ����ֹѰ·ʱ�����߽�
	for (int i = 0; i <= cols + 1; i++)
		maze[0][i] = maze[rows+1][i] = 1; // ��ʼ������Χǽ
	for (int i = 0; i <= rows + 1; i++)
		maze[i][0] = maze[i][cols + 1] = 1; // ��ʼ������Χǽ

	position here;//��ǰλ��
	here.row = 1;
	here.col = 1;//����ڿ�ʼ
	maze[1][1] = 1; // ��ֹ�ص����

	int option = 0; // �����������ϵ�˳��Ѱ·
	int lastOption = 3;

	// Ѱ��һ��·��
	while (here.row != rows || here.col != cols) {//û�е������
	   // �ҵ�Ҫ�ƶ�������һ��
		int r, c;//rΪҪѰ·���У�cΪҪѰ·����
		while (option <= lastOption) {
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)
				break;//�����ߣ�����ѭ�����������������һ������
			option++;
		}

		// �ж��Ƿ��ҵ���һ������option<4�����ҵ�һ��λ��
		if (option <= lastOption) {// ����λ��ѹ��·��ջ
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 4; // Ȼ�󽫸�λ����Ϊ����ͨ��
			option = 0;
		}
		else {// ��û�У�����һλ�õ���·��ջ
			if (path->empty())
				return false;   // ��·��ջΪ�գ������û��·��
			position next = path->top();
			path->pop();
			if (next.row == here.row)
				option = 2 + next.col - here.col;//��ʱӦ�����»���Ѱ·
			else
				option = 3 + next.row - here.row;//��ʱӦ������
			here = next;
		}
	}

	return true;  // at exit
}

void outputPath(){// ��ӡ·������
	cout << "The path is" << endl;
	position here;
	while (!path->empty()) {
		here = path->top();
		path->pop();
		//cout << here.row << ' ' << here.col << endl;
		maze[here.row][here.col] = 3;
	}
	maze[rows][cols] = 3;
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			Sleep(1);
			if (maze[i][j] == 1) {//���õ㲻ͨ
				setColor(1, 0);//������ɫΪ��ɫ
				cout << "�~";
			}
			else if (maze[i][j] == 3) {//���õ���·����
				setColor(15, 0);//������ɫΪ��ɫ
				cout << "�~";
			}
			else {//���õ��ͨ������·����
				setColor(14, 0);//������ɫΪ��ɫ
				cout << "�~";
			}
		}
		cout << endl;
	}
	setColor();
}

int main() {
	inputMaze();//�����Թ�����
	if (findPath())//Ѱ·
		outputPath();//���·��
	else
		cout << "No path" << endl;
	system("pause");
	return 0;
}
