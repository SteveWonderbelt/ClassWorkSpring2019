#ifndef TREE_H
#define TREE_H

template<typename T>
struct BST_Node {
T val;
BST_Node* left;
BST_Node* right;

BST_Node(T v) : val(v),left(NULL),right(NULL)
{}

void insert(T v) {
    if(v>val){
        if (right==NULL) right = new BST_Node<T>(v);
        else right->insert(v);
    }
    else{
        if (left==NULL) left = new BST_Node<T>(v);
        else left->insert(v);
    }
}

};


template<typename T>
void delete_tree(BST_Node<T>* root){
    if (root==NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}


//your work starts here
template<typename T>
int num_nodes(BST_Node<T>* root){

	//we test if the null exists. If not return 0. 
	if(root == NULL){
		return 0;
	}
	//if it does exist we recusively go through the tree and return the number of recursions(nodes). 
	else{
		return (num_nodes(root->left) + num_nodes(root->right) + 1); 
	}
}


template<typename T>
bool has_duplicate_val(BST_Node<T>* root){
	//test if the root is actually there
	if(root == NULL){
		return false; 
	}else{//if it is there, go ahead with duplicate check
			
		
		if((root->left->val == root->val)|| //Is the roots left node's value equal to the root's? 
		(root->right->val == root->val)|| //is the roots right node's value equal to the root's?
		(root->left->val == root->right->val) //Is the rooys left nodes value equal to its right node's value?
		){
				return true; //if any of those are true, there is a duplicate
		}
		else {
		//if we haven't found a duplicate yet, call the function again to keep looking
		
		return (has_duplicate_val(root->left)) || (has_duplicate_val(root->right)); 
		}
	}
}


template<typename T>
bool trees_identical(BST_Node<T>* a, BST_Node<T>* b){
	
	//if the trees are blank they woul be identical
	if(a == NULL && b == NULL){
		return true; 
	}
	//If either a is empty when b isn't or vice-versa then the trees are not identical
	else if((a == NULL && b != NULL) || (a != NULL && b == NULL)){
		return false;
	}
	//If nothing is null yet we keep looking by calling function again. 
	else{
		//To be identical, a and b must be equal, 
		//A and B's left nodes must be identical
		//A and B's right nodes must be identical
		//Those must all be true, otherwise trees are not identical
		if((a->val == b->val) && (trees_identical(a->left, b->left)) && (trees_identical(a->right, b->right))){
			return true; 
		}else{
			return false; 
		}
	}
}


#endif //TREE_H