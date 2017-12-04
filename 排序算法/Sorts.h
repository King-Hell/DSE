#pragma once
#ifndef SORTS_
#define SORTS_

#include<iostream>
using namespace std;
/*实现了六种排序，都是用数组方式实现，每种方法均为静态方法，以方便调用，前四种排序均可显示排序过程
归并排序与快速排序因为涉及到递归，没有设计显示排序过程的功能。
选择排序，冒泡排序和插入排序比较简单，而且实现了及时终止
快速排序和归并排序采用了递归的方式，由于之前没有学过归并排序，花费了一些时间去学习
基数排序没有采用书上的链表方式，而是数组方式。
实际测试时代码出了很多问题，只会思想不会实现还是没用，写代码一定要细心，否则回过头再调试实在太麻烦了。
*/
class sorts {
public:
	//选择排序
	template<class T>
	void static selectionSort(T a[], int n) {
		bool sorted = false;//当有序时，及时终止
		//外循环遍历数组，内循环每次找无序数组中最小的，然后放到有序数组后面
		for (int size = n; !sorted&&size > 1; size--) {
			int max = 0;
			sorted = true;
			for (int i = 1; i < size; i++) {
				if (a[i] >= a[max])
					max = i;
				else
					sorted = false;

			}
			swap(a[max], a[size - 1]);
			output(a, n);
		}
	}
	//冒泡排序
	template<class T>
	void static bubbleSort(T a[], int n) {
		bool sorted = false;
		//外循环遍历数组，内循环将最大元素冒泡到数组最后
		for (int i = 0; !sorted&& i < n - 1; i++) {
			sorted = true;
			for (int j = 0; j < n - 1 - i; j++) {
				if (a[j] > a[j + 1]) {
					swap(a[j], a[j + 1]);
					sorted = false;
				}
			}
			output(a, n);
		}
	}
	//插入排序
	template<class T>
	void static insertSort(T a[], int n) {
		//外循环遍历数组，内循将所有大于当前元素的元素向后移动
		for (int i = 1; i < n; i++) {
			T t = a[i];
			int j;
			for (j = i - 1; j >= 0 && t < a[j]; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
			output(a, n);
		}
	}
	//基数排序
	void static radixSort(int a[], int n) {
		//初始化10个桶
		int* bucket[10];
		//每个桶最多容纳n个元素
		for (int i = 0; i < 10; i++)
			bucket[i] = new int[n];

		int count[10];//用于计数每个桶中元素的个数
		for (int i = 0; i < 10; i++)
			count[i] = 0;//将每个桶的元素数量初始化为0
		bool sorted = false;
		int k = 1;
		while (!sorted) {
			//将所有元素按第k位放入10个桶中
			sorted = true;
			for (int i = 0; i < n; i++) {
				int num = getDigit(a[i], k);//当前数的第k位
				bucket[num][count[num]++] = a[i];
				if (!(num == 0 && a[i] / (int)pow(10, k - 1) == 0))
					sorted = false;
			}
			k++;
			//将10个桶中的元素取出
			int c = 0;
			for (int j = 0; j < 10; j++) {
				for (int i = 0; i < count[j]; i++)
					a[c++] = bucket[j][i];
				count[j] = 0;
			}
			output(a, n);
		}
		for (int i = 0; i < 10; i++)
			delete[] bucket[i];
	}
	//该方法取a的第k位
	int static getDigit(int a, int k) {
		return a / (int)pow(10, k - 1) % 10;
	}
	//快速排序
	template<class T>
	void static quickSort(T a[], int n) {
		quick(a, 0, n - 1);
		output(a, n);
	}
	template<class T>
	void static quick(T a[], int left, int right) {
		if (left > right)
			return;
		T base = a[left];//将最左侧数作为基准数
		int i = left, j = right;
		while (i != j) {//将所有小于base的元素放在左边，大于base的元素放在右边
			while (a[j] >= base&&i < j)
				j--;
			while (a[i] <= base&&i < j)
				i++;
			if (i < j)
				swap(a[i], a[j]);
		}
		a[left] = a[i];
		a[i] = base;
		quick(a, left, i - 1);
		quick(a, i + 1, right);
	}
	//归并排序
	template<class T>
	void static mergeSort(T a[], int n) {
		T *temp = new T[n];
		merge_sort(a, 0, n - 1, temp);
		delete[] temp;
		output(a, n);
	}
	//将a[left:right]排序
	template<class T>
	void static merge_sort(T a[], int left, int right, T temp[]) {
		//先把序列分为2个子序列，分别排序，然后进行合并
		if (left < right) {
			int mid = (left + right) / 2;
			merge_sort(a, left, mid, temp);
			merge_sort(a, mid + 1, right, temp);
			merge_merge(a, left, mid, right, temp);
		}
	}
	//将a[left:mid]与a[mid+1:right]合并
	template<class T>
	void static merge_merge(T a[], int left, int mid, int right, T temp[]) {
		int i = left, j = mid + 1, k = 0;
		for (k = 0; i <= mid&&j <= right; k++) {
			if (a[i] < a[j])
				temp[k] = a[i++];
			else
				temp[k] = a[j++];
		}
		for (; i <= mid; k++, i++)
			temp[k] = a[i];
		for (; j <= right; k++, j++)
			temp[k] = a[j];
		for (k = 0; left <= right; left++, k++)//将temp中元素复制回原数组
			a[left] = temp[k];
	}
	//输出数组
	template<class T>
	void static output(T a[], int n) {
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
};

#endif // !SORTS_
