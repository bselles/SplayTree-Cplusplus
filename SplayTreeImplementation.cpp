/*
	Author: Gabriel Sellés Salvà
	UCM Student 2016-2017
-*/

#include "SplayTreeHeader.h"

//Public methods implementation

SplayTree::SplayTree() {
	root = NULL;
}

bool SplayTree::insert(int element) {
	if (isEmpty()) return insert_if_empty(element);
	return insert_if_not_empty(element);
}

bool SplayTree::search(int elem) {
	//If it's empty, we won't find it.
	if (isEmpty()) return false;
	return search_if_not_empty(elem);	
}

bool SplayTree::remove(int elem) {
	//If its empty, we can't remove anything.
	if (isEmpty()) return false;
	return remove_if_not_empty(elem);
}

//Private methods implementation.

bool SplayTree::isEmpty() {
	return root == NULL;
}

void SplayTree::get_biggest(Node* &actualNode) {
	//If it has a left son, we look for the node that's more to the right from his right son.
	actualNode = root->leftSon;

	while (actualNode->rightSon != NULL) {
		//While it has a right son...
		actualNode = actualNode->rightSon;
	}
	//Once this finished, actualNode is going to point to a node that it hasn't a right son (it's going to be the bigger from the original actualNode's left son).
}

bool SplayTree::study_right_son(Node* &actualNode, int element) {
	//If it has not a right son, we have a place to put it.
	if (actualNode->rightSon == NULL) {
		insert_to_right_son(actualNode, element);
		return true;
	}
	//If not, we change the node we are studying. Now it's going to be his right son.
	actualNode = actualNode->rightSon;
	return false;

}

bool SplayTree::study_left_son(Node* &actualNode, int element) {
	//If the node we are evaluating has a bigger value than the one we want to introduce, we study his right son.
	if (actualNode->leftSon == NULL) {
		insert_to_left_son(actualNode, element);
		return true;
	}
	//If not, we change the node we are studying. Now it's going to be his left son.
	actualNode = actualNode->leftSon;
	return false;
}

void SplayTree::insert_to_right_son(Node* &actualNode, int element) {
	actualNode->rightSon = new Node;
	actualNode->rightSon->rightSon = NULL;
	actualNode->rightSon->leftSon = NULL;
	actualNode->rightSon->father = actualNode;
	actualNode->rightSon->value = element;

	floation(actualNode->rightSon);
}

void  SplayTree::insert_to_left_son(Node* &actualNode, int element) {
	actualNode->leftSon = new Node;
	actualNode->leftSon->rightSon = NULL;
	actualNode->leftSon->leftSon = NULL;
	actualNode->leftSon->father = actualNode;
	actualNode->leftSon->value = element;

	floation(actualNode->leftSon);
}

void SplayTree::updateParents(Node* &n, Node* &aux) {
	aux = n->father;
	n->father = n->father->father;
	aux->father = n;
}

void SplayTree::updateGrandpa(Node* &n, Node* &aux) {
	if (n->father != NULL) {
		if (n->father->rightSon == aux) {
			//If the father was grandpa's right son...
			n->father->rightSon = n;
		}
		else {
			//If the father was grandpa's left son...
			n->father->leftSon = n;
		}
	}
}

/*
Represents an L rotation.
Described here: http://www.ics.uci.edu/~dan/class/165/notes/splay.html
*/
void SplayTree::L(Node* n) {
	Node* aux;
	updateParents(n, aux);
	aux->rightSon = n->leftSon;
	if (n->leftSon != NULL) {
		aux->rightSon->father = aux;
	}
	n->leftSon = aux;
	updateGrandpa(n, aux);
}


/*
Represents a R rotation.
Described here: http://www.ics.uci.edu/~dan/class/165/notes/splay.html
*/
void SplayTree::R(Node* n) {
	Node* aux;
	updateParents(n, aux);
	aux->leftSon = n->rightSon;
	if (aux->leftSon != NULL) {
		aux->leftSon->father = aux;
	}
	n->rightSon = aux;
	updateGrandpa(n, aux);
}


bool SplayTree::remove_node(Node* &actualNode) {
	floation(actualNode);
	//If it doesn't have a left son.
	if (root->leftSon == NULL) {
		if (root->rightSon != NULL)	root->rightSon->father = NULL;
		root = root->rightSon;
		return true;
	}	
	//If it has a left son, we look for the node that's more to the right from his right son.
	get_biggest(actualNode);
	//Once this finished, actualNode is going to point to a node that it hasn't a right son (it's going to be the bigger from the original actualNode's left son).
	//Root's right son, if it existed, it's going to be new actualNode's right son.
	if (root->rightSon != NULL) {
		actualNode->rightSon = root->rightSon;
		root->rightSon->father = actualNode;
	}
	//Root's left son will be the new root.
	root = root->leftSon;
	root->father = NULL;
	
	return true;
}

bool SplayTree::insert_if_empty(int element) {
	//We create a node in the root. We put the correct values in every field ( references=NULL and value=element).
	root = new  Node;
	root->rightSon = NULL;
	root->leftSon = NULL;
	root->father = NULL;
	root->value = element;
	//There's no need to fload, because the tree has only one node.
	//Everything worked correctly, so we return true.
	return true;
}

bool SplayTree::insert_if_not_empty(int element) {
	/*Pointer we are going to use to move through the tree. Points to the node we are studying every moment.
	It's going to start pointing to the root.*/
	Node* actualNode;
	actualNode = root;
	//This loop won't stop until a return statement is executed.
	while (true) {
		if (actualNode->value == element) {
			//Insertion didn't work correctly, we've found the element that we are trying to insert. We return false.
			floation(actualNode);
			return false;
		}
		else if (actualNode->value < element) {
			//If the node we are evaluating has a lower value than the one we want to introduce, we study his right son.
			if (study_right_son(actualNode, element)) return true;
		}
		else {
			//If the node we are evaluating has a bigger value than the one we want to introduce, we study his left son.
			if (study_left_son(actualNode, element)) return true;
		}
	}
}

bool SplayTree::rotate_if_father(Node* &actualNode) {
	//If it's father's right son.
	if (actualNode->father->rightSon == actualNode) {
		L(actualNode);
		root = actualNode;
		//After the rotation, we've finished.
		return true;
	}
	//If it's father's left son.
	else if (actualNode->father->leftSon == actualNode) {
		R(actualNode);
		root = actualNode;
		//After the rotation, we've finished.
		return true;
	}
	return false;
}


void SplayTree::rotate_if_grandpa(Node* &actualNode) {
	//We use it to avoid the entrance to both ifs.
	bool entered = false;
	//If it has a grandpa and his father is his grandpa's left son.
	if (actualNode->father->father->leftSon != NULL) {
		//If actualNode is the left son from the grandpa's left son...
		if (actualNode->father->father->leftSon->leftSon == actualNode) {
			R(actualNode->father);
			R(actualNode);
			entered = true;
		}
		//If actualNode is the right son from grandpa's left son.
		else if (actualNode->father->father->leftSon->rightSon == actualNode) {
			L(actualNode);
			R(actualNode);
			entered = true;
		}
	}
	//If it has a grandpa and his father is his grandpa's right son.
	if (!entered && actualNode->father->father->rightSon != NULL) {
		//If actualNode is the right son from grandpa's right son.
		if (actualNode->father->father->rightSon->rightSon == actualNode) {
			L(actualNode->father);
			L(actualNode);
		}
		//If actualNode is the left son from grandpa's right son.
		else if (actualNode->father->father->rightSon->leftSon == actualNode) {
			R(actualNode);
			L(actualNode);
		}
	}
}

void SplayTree::floation(Node* n) {
	//Pointer we are going to use to move through the tree. Points to the node we are studying every moment
	Node* actualNode = n;
	//This loop won't stop until a return statement is executed.
	while (true) {
		//If a node has a grandpa, we will float differently ( consult link above).
		if (actualNode->father != NULL && actualNode->father->father != NULL) {
			rotate_if_grandpa(actualNode);
		}
		//If it has a father but not a grandpa...
		else if (actualNode->father != NULL) {
			if (rotate_if_father(actualNode)) break;
		}
		else {
			//If it doesn't have father, it means we've finished.
			root = actualNode;
			break;
		}
	}
}

bool SplayTree::remove_if_not_empty(int elem) {

	Node* actualNode = root;
	//This loop won't stop until a return statement is executed.
	while (true) {

		//If the node we're studying has the value we're looking for, we proceed to remove the element transforming the subtree. 
		if (actualNode->value == elem) {
			return remove_node(actualNode);
		}
		else if (actualNode->value < elem) {
			//If it doesn't have a right son, we won't find what we are looking for.
			if (actualNode->rightSon == NULL) {
				//If we don't find the node we are trying to remove, we only floate the last node visited.
				floation(actualNode);
				return false;
			}
			else {
				//If it has a right son, the next node we're going to study it's going to be his right son.
				actualNode = actualNode->rightSon;
			}
		}
		else {
			//If it doesn't have a left son, we won't find what we are looking for.
			if (actualNode->leftSon == NULL) {
				//If we don't find the node we are trying to remove, we only floate the last node visited.
				floation(actualNode);
				return false;
			}
			else {
				//If it has a left son, the next node we're going to study it's going to be his left son.
				actualNode = actualNode->leftSon;
			}
		}
	}
}

bool SplayTree::search_if_not_empty(int elem) {

	Node* actualNode = root;

	//This loop won't stop until a return statement is executed.
	while (true) {
		//If the node we're studying has the value we're looking for, we stop.
		if (actualNode->value == elem) {
			floation(actualNode);
			//We've found what we were looking for, we return true.
			return true;
		}
		else if (actualNode->value < elem) {
			if (actualNode->rightSon == NULL) {
				//If it doesn't have a right son, we won't find anything.
				floation(actualNode);
				return false;
			}
			else {
				//If it has a right son, the next node we're going to study it's going to be his right son.
				actualNode = actualNode->rightSon;
			}
		}
		else {
			if (actualNode->leftSon == NULL) {
				//If it doesn't have a left son, we won't find anything.
				floation(actualNode);
				return false;
			}
			else {
				//If it has a left son, the next node we're going to study it's going to be his left son.
				actualNode = actualNode->leftSon;
			}
		}
	}
}