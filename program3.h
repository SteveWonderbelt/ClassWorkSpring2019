#ifndef PROGRAM2_H
#define PROGRAM2_H

#include "metrics.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <map>
#include <iterator> 

int bfCounter = 0, divCount = 0; 

template<typename T>
std::vector<Point<T>> merge(vector<Point<T>> left, vector<Point<T>> right, std::string coordinate){
	int i = 0, j=0, k=0;
	int leftSize = left.size();
	int rightSize = right.size();
	int totalSize = leftSize + rightSize;
	std::vector<Point<T>> sortedVector(totalSize, left[0]) ;

	for(i = 0; i <totalSize; i++){
		divCount++;
		if(j < leftSize && k < rightSize){
			if(coordinate == "x"){
				if(left[j].x <= right[k].x){
					sortedVector[i] = left[j];
					j++;
				}else{
					sortedVector[i] = right[k];
					k++;
				}
			}else{
				if(left[j].y <= right[k].y){
					sortedVector[i] = left[j];
					j++;
				}else{
					sortedVector[i] = right[k];
					k++;
				}
			}
		}else if(j < leftSize){
			sortedVector[i] = left[j];
			j++;
		}else if(k < rightSize){
			sortedVector[i] = right[k];
			k++;
		}
	}
	return sortedVector;		
}

template<typename T>
std::vector<Point<T>> mergesort(std::vector<Point<T>> vec,std:: string coordinate){
	int vectorSize = vec.size();
	int middle = vectorSize/2; 
	std::vector<Point<T>> leftVector;
	std::vector<Point<T>> rightVector;
	if(vectorSize <= 1){
		return vec; 
	}
	for(int i = 0; i < middle; i++){
		leftVector.push_back(vec[i]);
		rightVector.push_back(vec[i + middle]);
	}
	if(vectorSize % 2 != 0){
		rightVector.push_back(vec.back()); 
	}
	leftVector = mergesort(leftVector, coordinate);
	rightVector = mergesort(rightVector, coordinate);
	return merge(leftVector, rightVector, coordinate);
	
}

template<typename T>
std::pair<Point<T>, Point<T> > closestPair( vector<Point<T> > v){
	std::vector<Point<T> > sortedv = mergesort(v, "x");
	if(v.size() <= 3){
		return closestPairBF(v);
	}	

	int sizeV = sortedv.size();
	int halfSizeV = sizeV/2;
	std::vector<Point<T>> leftPairs;
	std::vector<Point<T>> rightPairs;
	//std::pair<Point<T>, Point<T>> firstResult, secondResult; 

	if(sizeV % 2 == 0){
		for( int i =0; i <halfSizeV; i++){
			leftPairs.push_back(sortedv[i]);
			rightPairs.push_back(sortedv[i + halfSizeV]);
		}
	}else{
		for(int i = 0; i <=halfSizeV; i++){
			leftPairs.push_back(sortedv[i]);
		}
		for(int i = halfSizeV + 1; i <sizeV; i++){
			rightPairs.push_back(sortedv[i]);
		}
	}
	
	std::pair<Point<T>, Point<T> > firstResult (closestPair(leftPairs));
	std::pair<Point<T>, Point<T> > secondResult (closestPair(rightPairs));

	double minFirst = dist(firstResult.first, firstResult.second);
	double minSecond = dist(secondResult.first, secondResult.second);
	double minAll = std::min(minFirst, minSecond);
	std::vector<Point<T>> sPoints; 
	for( int i = halfSizeV-1; i > 0; i--){
		if(sortedv[halfSizeV].x - sortedv[i].x < minAll){
			sPoints.push_back(sortedv[i]);
		}else{
			break;
		}
	
	}
	for(int i = halfSizeV + 1; i <sizeV; i++){
		if(sortedv[i].x - v[halfSizeV].x < minAll){
			sPoints.push_back(v[i]);
		}else{
			break;
		}
	}
	sPoints.push_back(sortedv[halfSizeV]);
	std::vector<Point<T>> sortedSPoints;
	std::vector<Point<T>> sClosestPair;
	double dminsq = std::pow(minAll, 2);
	if(sPoints.size() > 1){
		double min = minAll; 
		sortedSPoints = mergesort(sPoints, "y");
		int sizeOfSortS = sortedSPoints.size();
		for(int i = 0; i < sizeOfSortS - 1; i++){
			for(int j = i +1; j < sizeOfSortS && (sortedSPoints[j].x - sortedSPoints[i].x < min); j++){
				divCount ++;
				double pDistance = dist(sortedSPoints[i], sortedSPoints[j]);
				if(pDistance < min){
					min = pDistance;
					sClosestPair.clear();
					sClosestPair.push_back(sortedSPoints[i]);
					sClosestPair.push_back(sortedSPoints[j]);
				}
			}
		}if(sClosestPair.size()> 0){
			int a = 0;
			int b = 1; 
			std::pair<Point<T>, Point<T>> finalPair(sClosestPair[0], sClosestPair[1]);
			return finalPair; 
		}else{
			return (minFirst < minSecond) ? firstResult : secondResult; 
		}
	}else{
		return (minFirst < minSecond) ? firstResult : secondResult; 
	
	}
	//std::pair<Point<T>, Point<T>> endanswer (v[0],v[1]);
 	//return endanswer;
}
#endif //PROGRAM2_H