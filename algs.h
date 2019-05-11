#ifndef ALGS_H
#define ALGS_H

#include <algorithm>
#include <queue>
using std::swap;

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

//just copy code over from program 1's hoarePartition. 
int hoarePartition(T A[], int l, int r){
	int median = medianOf3(A, l, r);
	swap(A[l], A[median]);

	int pivotNumber = 1;
	int pivotElement = A[l]; 

	for(int i=l+1; i<= r; i++){
		if(A[i] <= pivotElement){
			pivotNumber++;
			swap(A[i],A[pivotNumber]);
		}
	}
	swap(A[pivotNumber], A[l]);

	return pivotNumber;
}

template<typename T>
void heapsort(std::vector<T>& V){
	std::priority_queue<T, std::vector<T>, std::greater<T>> pq; //create a priority queue
	for( int i = 0; i<V.size(); ++i){ //iterate through V to fill priority queue
		pq.push(V.at(i)); 
	}
	for(int i = 0; i < V.size(); ++i){//all popped elements of pq will be in order
		V.at(i) = pq.top();
		pq.pop();
	}
	
	
}



bool are_anagrams(std::string a, std::string b){
	bool is_anagram = true; 	
	//If two strings are anagrams they will have the same number of all characters. 
	std::vector<char> alphabet = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int a_num; 
	int b_num; 
	
	//we run through the alphabet and compare the counts of each letter found in both strings. 
	//if they are not the same an anagram cannot occur
	for(int i = 0;i<alphabet.size();++i){
		a_num = std::count(a.begin(), a.end(), alphabet.at(i));
		b_num = std::count(b.begin(), b.end(), alphabet.at(i));
		if(a_num != b_num){
			is_anagram = false; 
			break;
		}
	}
	
	return is_anagram;
}


#endif