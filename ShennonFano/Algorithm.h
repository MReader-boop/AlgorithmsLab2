#pragma once
#include"Pair.h"
#include"List.h"
template<class T>
void QuickSort(T* mas, int first, int last)
{
	T mid;
	int f = first, l = last;
	mid = mas[(f + l) / 2];
	do
	{
		while (mas[f] < mid) f++;
		while (mas[l] > mid) l--;
		if (f <= l)
		{
			swap(&mas[f], &mas[l]);
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) QuickSort(mas, first, l);
	if (f < last) QuickSort(mas, f, last);
}
template<class T>
void swap(T* a, T* b) {
	T* c = a;
	a = b;
	b = c;
}
template<class T>
T max(const T& a, const T& b) {
	return a > b ? a : b;
}



