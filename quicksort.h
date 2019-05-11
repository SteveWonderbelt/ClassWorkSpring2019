#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <algorithm>
#include <iostream>
#include <array>
using std::swap;
using namespace std;

//note returns INDEX of median
//does NOT move the median into the pivot position
template<typename T> inline
int medianOf3(T A[], int l, int r){
	//this is overcommented... also, try and avoid using pointers
	T* a = A + l;//array name is just pointer to 1st (0 index) elem., + l shifts l*(T size)
	T* b = A + l + (r-l)/2;//middle item... int division rounds down
	T* c = A + r;

	//when a is a pointer, *a is the dereference operator (gives value a points to)
	T* m;
	if(*a < *b){
		if(*b < *c) m=b; 
		else if(*c < *a) m=a;
		else m=c;
	} else{ //b <=a
		if(*a < *c) m=a;
		else if(*c < *b) m=b;
		else m=c;
	}
	return m-A; //m-A is the number of elements from A[0]

}

//remember: l and r are INLCUSIVE (just like Lomuto)
//make sure to call medianOf3 on the subarray before partitioning
template<typename T>
int hoarePartition(T A[], int l, int r){
	int median = medianOf3(A, l, r);//variable that is the median of the array 
	swap(A[l], A[median]); //swaps the beginning of the array with the median
	
	int pivotNumber = l;
	int pivotElement = A[l];

	for(int i = l+1; i <= r; i++) //Loop goes through array to form partitions
	{
		if(A[i] <= pivotElement) //check if current element is less than pivot
					//if so, increase the array index and swap out the elements
		{
			pivotNumber++;
			swap(A[i],A[pivotNumber]);
		}
	}	
	
	swap(A[pivotNumber], A[l]);// make a swap so that the pivot element is back in its proper place
	return pivotNumber; 
	
}

template<typename T>
void quicksort(T A[], int l, int r){
	if (l < r){
		int s = hoarePartition(A, l, r);
		quicksort(A, l, s-1);
		quicksort(A, s+1, r);
	}	
}


#endif