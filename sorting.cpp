#include <bits/stdc++.h>
using namespace std;
#define ll long long

void swap(int a[], int index1, int index2) {
	int temp = a[index1];
	a[index1] = a[index2];
	a[index2] = temp;}


void selectionSort(int a[], int len) {
	for (int i=0; i<len; i++) {
		int minn = len-1;
		for (int j=i; j<len; j++) minn = a[j]<a[minn] ? j:minn;
		int temp = a[minn];
		a[minn] = a[i];
		a[i] = temp;
	}}

void bubbleSort(int a[], int len) {
	for (int i=len; i>1; i--) {
		bool sorted = true;
		for (int j=0; j<i; j++) {
			if (a[j] > a[j+1]) {
				swap(a, j, j+1);
				sorted = false;
			}
		}
		if (sorted) return;
	}}

void insertionSort(int a[], int len) {
	for (int i=1; i<len; i++) {
		for (int j=i; j>0; j--) {
			if (a[j]<a[j-1]) swap(a, j, j-1);
			else break;
		}
	}}

void merge(int a[], int start, int mid, int end) {
	int i=start, j=mid+1, k=0, b[end-start+1];
	while (i<=mid && j<=end) {
		if (a[i]<=a[j]) {
			b[k] = a[i];
			i++;
		}
		else {
			b[k] = a[j];
			j++;
		}
		k++;
	}
	while (i<=mid) {
		b[k] = a[i];
		i++;
		k++;
	}
	while (j<=end) {
		b[k] = a[j];
		j++;
		k++;
	}
	for (int x=start; x<=end; x++) a[x] = b[x-start];}

void mergeSort(int a[], int start, int end) {
	if (start==end) return;
	int mid = (end-start)/2 + start;
	mergeSort(a, start, mid);
	mergeSort(a, mid+1, end);
	merge(a, start, mid, end);}

void mergeVector(vector<int> &v, int start, int mid, int end) {
    vector<int> sorted;

    int i=start, j=mid+1;
    while(i<=mid && j<=end) {
        if (v[i]<v[j]) {
            sorted.push_back(v[i]);
            i++;
        }
        else {
            sorted.push_back(v[j]);
            j++;
        }
    }
    while (i<=mid) {
        sorted.push_back(v[i]); 
        i++;
    }
    while (j<=end) {
        sorted.push_back(v[j]);
        j++;
    }
    for (int x=start; x<=end; x++) v[x] = sorted[x-start];}

void mergeSortVector(vector<int> &v, int start, int end) {
    if (start==end) return;
    int mid = (end-start)/2+start;
    mergeSortVector(v, start, mid);
    mergeSortVector(v, mid+1, end);
    mergeVector(v, start, mid, end);}

int partition(int a[], int start, int end) {
	int pivot = a[start];
	int i=start, j=end;
	while(i<j) {
		while(a[i]<=pivot && i<=end+1) i++;
		while(a[j]>pivot && j>=start+1) j--;

		if (i<j) swap(a, i, j);
	}
	swap(a, start, j);
	return j;
}

void quickSort(int a[], int start, int end) {
	if (start==end) return;
	int pIndex = partition(a, start, end);

	quickSort(a, start, pIndex-1);
	quickSort(a, pIndex+1, end);}

int main() {
	vector<int> a = {9, 4, 6, 3, 7, 2, 1};
	int len = a.size();
	mergeSortVector(a, 0, len-1);

	for (int i=0; i<len; i++) cout << a[i] << ", ";
	return 0;
}
