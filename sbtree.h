#ifndef SBTREEHASH_H
#define SBTREEHASH_H

#include <map> //  a self-balancing tree (red-black)
#include <unordered_map> // a hash table
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::sort;
using std::vector;
using std::unordered_map;
using std::pair;
using std::map;

struct ana_result {
    bool found = false;
    string s1;
    string s2;
};

//Do there exist two strings that are anagrams of each other ? (use std::sort and a custom Compare)
// See https://en.cppreference.com/w/cpp/algorithm/sort
// lambda functions are fine, even preferable here
ana_result anyAnagramsSorting(vector<string> ss){
	ana_result ar;
	vector<string> copySS = ss;
	std::vector<std::pair<string, string>> anaVector; 
	for(int i = 0; i< ss.size(); i++){
		string temp = copySS[i];
		std::sort(temp.begin(), temp.end());
		std::pair<string, string> tempPair (temp, ss[i]);
		anaVector.push_back(tempPair);
		//std::cout<<"Added "<<anaVector[i].first<<" "<<anaVector[i].second<<std::endl;
	}
	//We now have a vector of pairs<sorted string, unsorted string>
	//Now we'll sort that vector by sorted string
	std::sort(anaVector.begin(), anaVector.end());
	//Now we just need to run through the vector looking for repeat strings in the first pair
	//Those will be right next to each other. That means that the anagram strings are just the second part of those two pairs
	for(int i = 0; i <anaVector.size()-1; i++){
		//std::cout<<anaVector[i].first<<" "<<anaVector[i].second<<std::endl;
		if(anaVector[i].first == anaVector[i+1].first){
			//std::cout<<"Found a match at position"<<i<<" and "<<i+1<<std::endl;
			//std::cout<<"These are:"<<std::endl;
			//std::cout<<anaVector[i].first<<", "<<anaVector[i].second<<std::endl;
			//std::cout<<anaVector[i+1].first<<", "<<anaVector[i+1].second<<std::endl;
			ar.s1 = anaVector[i].second;
			ar.s2 = anaVector[i+1].second;
			ar.found = true; 
		}
	}


	return ar; 
}

//Do there exist two strings that are anagrams of each other ? (use map, self-balancing tree)
ana_result anyAnagramsMap(vector<string> strings){
   	ana_result res;
	//This holds pairs that contain an anagram
	vector<std::pair<string, string>> anasFound; 
	//Now create the reverse of the above. 
	//Failure to insert represents a duplicate key and therfore anagram is found
	std::map<string, string> reverseMap; 
	for(int i = 0; i< strings.size(); i++){
			
			std::pair<std::map<string, string>::iterator, bool> ret; //holds iterator and if the insert could happen
			string temp = strings[i];
			std::sort(temp.begin(), temp.end());
			ret = reverseMap.insert(pair<string, string>(temp, strings[i])); //attempt to insert a pair of sorted,unsorted
			if(ret.second ==false){
				//temp is the pair that is already in the vector
				//with that pair, we can look up the corresponding pair in the original vector 
				std::pair<string, string> tempPair = std::pair<string, string>(ret.first->first, ret.first->second);
				std::pair<string, string> temp2 = std::pair<string, string>(temp, strings[i]);
				//push theese pairs into a vector
				anasFound.push_back(tempPair);
				anasFound.push_back(temp2);
			}else{
//				
			}
	}
	if(anasFound.size() == 2){
		//If the vector size is 2 then we've succeeded in finding the two strings. Set res accordingly
		res.found = true;
		res.s1 = anasFound[1].second; //the scond element is the unsorted string
		res.s2 = anasFound[0].second; 
		
	}
   	return res;
}

//Do there exist two strings that are anagrams of each other ? (use unordered_map, hash table)
ana_result anyAnagramsHash(vector<string> strings){
	ana_result res;
	//We'll essentiall be doing the same thing here as we did in anaAnagramsMap
	//First lets create a u-map that is <string, string>, unordered, ordered
	std::unordered_map<string, string> origMap; 
	vector<std::pair<string, string>> anasFound;
	for(int i =0; i <strings.size(); i++){
		
		std::pair<std::unordered_map<string, string>::iterator, bool> ret;
		string temp = strings[i];
		std::sort(temp.begin(), temp.end());
		ret = origMap.insert(pair<string, string>(temp, strings[i]));
		if(ret.second == false){
			std::pair<string, string> tempPair1 = std::pair<string, string>(ret.first->first, ret.first->second);
			std::pair<string, string> tempPair2 = std::pair<string, string>(temp, strings[i]);
			anasFound.push_back(tempPair1);
			anasFound.push_back(tempPair2);

		}else{

		}
	}
	if(anasFound.size() == 2){
		res.found = true;
		res.s1 = anasFound[1].second;
		res.s2 = anasFound[0].second;
	}
	
	return res;
}

#endif //SBTREEHASH_H