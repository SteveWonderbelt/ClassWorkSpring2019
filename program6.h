#ifndef PROGRAM4_H
#define PROGRAM4_H

#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

typedef struct char_freq{
  char c;
  double freq;

  char_freq(char c, double freq)
    :c(c),
     freq(freq)
  {}
} CFreq;

typedef struct char_code{
  char c;
  std::string code;
  char_code(char c, std::string code)
    :c(c),
     code(code)
  {}
} CCode;


struct HuffTreeNode{
                char data;
                double freq;
                HuffTreeNode* left;
		HuffTreeNode* right;
		HuffTreeNode(){
			data = '\0';
			freq = 0; 
		}
                HuffTreeNode(char data, double freq):data(data),
							freq(freq),
							left(nullptr),
							right(nullptr)
		{}
~HuffTreeNode()
{
	delete left;
	delete right;
}
};

struct compare{
                bool operator()(HuffTreeNode* l, HuffTreeNode* r){
                        return (l->freq > r->freq);
                }
};
HuffTreeNode* top;
std::vector<CCode> finalCodes;  

std::string codes; 
std::string genCodeVector2(HuffTreeNode* root, std::string str){
	//std::vector<std::string> codes; 
	if(root == nullptr){
		return "";
	}
	if(root->data != '$'){
		finalCodes.push_back( CCode(root->data, str)); 
		codes = codes + root->data+" : "+str+"\n"; 		
	}
	genCodeVector2(root->left, str+"0");
	genCodeVector2(root->right, str+"1"); 	
	return codes; 
}

//input: vector of CFreqs 
//returns: vector of CCodes
std::vector<CCode> getHuffCodes(std::vector<CFreq > cfs){

  //can define in separate .cpp file (make this into declaration) 
  //or define everything here (nothing in targetgtest.cpp)

  //following is for compilation purposes
	HuffTreeNode* left;
	HuffTreeNode* right;

	std::priority_queue<HuffTreeNode*, std::vector<HuffTreeNode*>, compare> huffHeap;

	for(int i = 0; i < cfs.size(); ++i){
		huffHeap.push(new HuffTreeNode(cfs[i].c, cfs[i].freq));
	}

	while(huffHeap.size() != 1){
		left = huffHeap.top();
		huffHeap.pop();

		right=huffHeap.top();
		huffHeap.pop();

		top = new HuffTreeNode('$', left->freq + left->freq);
		top->left = left;
		top->right = right;
		huffHeap.push(top);
	}
	genCodeVector2(huffHeap.top(), "");
	return finalCodes;
}

#endif //PROGRAM4_H