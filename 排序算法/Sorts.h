#pragma once
#ifndef SORTS_
#define SORTS_

#include<iostream>
using namespace std;
/*ʵ�����������򣬶��������鷽ʽʵ�֣�ÿ�ַ�����Ϊ��̬�������Է�����ã�ǰ�������������ʾ�������
�鲢���������������Ϊ�漰���ݹ飬û�������ʾ������̵Ĺ��ܡ�
ѡ������ð������Ͳ�������Ƚϼ򵥣�����ʵ���˼�ʱ��ֹ
��������͹鲢��������˵ݹ�ķ�ʽ������֮ǰû��ѧ���鲢���򣬻�����һЩʱ��ȥѧϰ
��������û�в������ϵ�����ʽ���������鷽ʽ��
ʵ�ʲ���ʱ������˺ܶ����⣬ֻ��˼�벻��ʵ�ֻ���û�ã�д����һ��Ҫϸ�ģ�����ع�ͷ�ٵ���ʵ��̫�鷳�ˡ�
*/
class sorts {
public:
	//ѡ������
	template<class T>
	void static selectionSort(T a[], int n) {
		bool sorted = false;//������ʱ����ʱ��ֹ
		//��ѭ���������飬��ѭ��ÿ����������������С�ģ�Ȼ��ŵ������������
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
	//ð������
	template<class T>
	void static bubbleSort(T a[], int n) {
		bool sorted = false;
		//��ѭ���������飬��ѭ�������Ԫ��ð�ݵ��������
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
	//��������
	template<class T>
	void static insertSort(T a[], int n) {
		//��ѭ���������飬��ѭ�����д��ڵ�ǰԪ�ص�Ԫ������ƶ�
		for (int i = 1; i < n; i++) {
			T t = a[i];
			int j;
			for (j = i - 1; j >= 0 && t < a[j]; j--)
				a[j + 1] = a[j];
			a[j + 1] = t;
			output(a, n);
		}
	}
	//��������
	void static radixSort(int a[], int n) {
		//��ʼ��10��Ͱ
		int* bucket[10];
		//ÿ��Ͱ�������n��Ԫ��
		for (int i = 0; i < 10; i++)
			bucket[i] = new int[n];

		int count[10];//���ڼ���ÿ��Ͱ��Ԫ�صĸ���
		for (int i = 0; i < 10; i++)
			count[i] = 0;//��ÿ��Ͱ��Ԫ��������ʼ��Ϊ0
		bool sorted = false;
		int k = 1;
		while (!sorted) {
			//������Ԫ�ذ���kλ����10��Ͱ��
			sorted = true;
			for (int i = 0; i < n; i++) {
				int num = getDigit(a[i], k);//��ǰ���ĵ�kλ
				bucket[num][count[num]++] = a[i];
				if (!(num == 0 && a[i] / (int)pow(10, k - 1) == 0))
					sorted = false;
			}
			k++;
			//��10��Ͱ�е�Ԫ��ȡ��
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
	//�÷���ȡa�ĵ�kλ
	int static getDigit(int a, int k) {
		return a / (int)pow(10, k - 1) % 10;
	}
	//��������
	template<class T>
	void static quickSort(T a[], int n) {
		quick(a, 0, n - 1);
		output(a, n);
	}
	template<class T>
	void static quick(T a[], int left, int right) {
		if (left > right)
			return;
		T base = a[left];//�����������Ϊ��׼��
		int i = left, j = right;
		while (i != j) {//������С��base��Ԫ�ط�����ߣ�����base��Ԫ�ط����ұ�
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
	//�鲢����
	template<class T>
	void static mergeSort(T a[], int n) {
		T *temp = new T[n];
		merge_sort(a, 0, n - 1, temp);
		delete[] temp;
		output(a, n);
	}
	//��a[left:right]����
	template<class T>
	void static merge_sort(T a[], int left, int right, T temp[]) {
		//�Ȱ����з�Ϊ2�������У��ֱ�����Ȼ����кϲ�
		if (left < right) {
			int mid = (left + right) / 2;
			merge_sort(a, left, mid, temp);
			merge_sort(a, mid + 1, right, temp);
			merge_merge(a, left, mid, right, temp);
		}
	}
	//��a[left:mid]��a[mid+1:right]�ϲ�
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
		for (k = 0; left <= right; left++, k++)//��temp��Ԫ�ظ��ƻ�ԭ����
			a[left] = temp[k];
	}
	//�������
	template<class T>
	void static output(T a[], int n) {
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}
};

#endif // !SORTS_
