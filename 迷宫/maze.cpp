//迷宫寻路
#include <iostream>
#include <fstream>
#include<Windows.h>
#include "arrayStack.h"
#include "position.h"
#include "make2dArray.h"

// 全局变量
int **maze, rows, cols;//二维数组maze存放迷宫数据，rows与cols分别为迷宫的行数与列数
arrayStack<position>* path;  // 路径栈

void setColor(unsigned short forecolor = 7, unsigned short backgroudcolor = 0){
	//该函数用于设置输出颜色，默认为黑底白字
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); //获取缓冲区句柄
	SetConsoleTextAttribute(hCon, forecolor | backgroudcolor); //设置文本及背景色
}

void inputMaze(){// 读入迷宫数据
	//从文件读入一组迷宫数据
	//迷宫数据的前两个数字为大小，后面用0代表可通过，1代表不可通过
	ifstream in("data2.txt");
	if (!in.is_open())
		throw "Loading data error";
	in >> rows;//读入迷宫的行数
	in >> cols;//读入迷宫的列数
	make2dArray(maze, rows + 2, cols + 2);//初始化迷宫数组，并设置围墙
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			in >> maze[i][j];//将0，1数据插入maze数组中
			if (maze[i][j] == 1) {
				setColor(4, 0);
				cout << "▇";//如果可不可通过，打印红色块
			}
			else {
				setColor(2,0);
				cout << "▇";//如果可通过，打印绿色块
			}
		}
		cout << endl;
	}
	setColor();
	cout << "Load data successfully" << endl;

}

bool findPath(){//寻找一条从入口（1，1）到出口（rows,cols）的路径
	//如果找到返回true，没有返回false
	//该方法为主要方法，思想是将一个可通过位置压入路径栈中，然后依次按右下左上的顺序寻找
	//可以通过的下一个路径点并压入栈中，当寻路到达出口时，返回true
	//当路径栈为空时，表明没有路径可以通过，返回false
	path = new arrayStack<position>;//路径栈
	// 初始化偏移量
	position offset[4];//设定四个寻路方向
	offset[0].row = 0; offset[0].col = 1;   // 右
	offset[1].row = 1; offset[1].col = 0;   // 下
	offset[2].row = 0; offset[2].col = -1;  // 左
	offset[3].row = -1; offset[3].col = 0;  // 上

	// 初始化迷宫外围障碍墙，防止寻路时超出边界
	for (int i = 0; i <= cols + 1; i++)
		maze[0][i] = maze[rows+1][i] = 1; // 初始化上下围墙
	for (int i = 0; i <= rows + 1; i++)
		maze[i][0] = maze[i][cols + 1] = 1; // 初始化左右围墙

	position here;//当前位置
	here.row = 1;
	here.col = 1;//从入口开始
	maze[1][1] = 1; // 防止回到入口

	int option = 0; // 按照右下左上的顺序寻路
	int lastOption = 3;

	// 寻找一条路径
	while (here.row != rows || here.col != cols) {//没有到达出口
	   // 找到要移动的相邻一步
		int r, c;//r为要寻路的行，c为要寻路的列
		while (option <= lastOption) {
			r = here.row + offset[option].row;
			c = here.col + offset[option].col;
			if (maze[r][c] == 0)
				break;//若可走，跳出循环，否则继续搜索下一个方向
			option++;
		}

		// 判断是否找到下一步，若option<4，则找到一个位置
		if (option <= lastOption) {// 将该位置压入路径栈
			path->push(here);
			here.row = r;
			here.col = c;
			maze[r][c] = 4; // 然后将该位置设为不可通过
			option = 0;
		}
		else {// 若没有，则将上一位置弹出路径栈
			if (path->empty())
				return false;   // 若路径栈为空，则表明没有路径
			position next = path->top();
			path->pop();
			if (next.row == here.row)
				option = 2 + next.col - here.col;//此时应该向下或上寻路
			else
				option = 3 + next.row - here.row;//此时应该向左
			here = next;
		}
	}

	return true;  // at exit
}

void outputPath(){// 打印路径坐标
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
			if (maze[i][j] == 1) {//当该点不通
				setColor(1, 0);//设置颜色为蓝色
				cout << "▇";
			}
			else if (maze[i][j] == 3) {//当该点是路径点
				setColor(15, 0);//设置颜色为白色
				cout << "▇";
			}
			else {//当该点可通但不是路径点
				setColor(14, 0);//设置颜色为黄色
				cout << "▇";
			}
		}
		cout << endl;
	}
	setColor();
}

int main() {
	inputMaze();//读入迷宫数据
	if (findPath())//寻路
		outputPath();//输出路径
	else
		cout << "No path" << endl;
	system("pause");
	return 0;
}
