/*
	Author: Gabriel Sellés Salvà
	UCM Student 2016-2017
-*/


#ifndef SPLAYTTREEHEADER
#define SPLAYTREEHEADER

#include <iostream>
using namespace std;

//Struct that represents a node from the SplayTree.
struct Node {
	Node* father;
	Node* rightSon;
	Node* leftSon;
	int value;
};

class SplayTree {
		//Private atributes
		Node* root;
		//Private Methods
		bool isEmpty();
		bool search_if_not_empty(int element);
		bool remove_if_not_empty(int elem);
		void get_biggest(Node* &actualNode);
		bool remove_node(Node* &actualNode);
		bool insert_if_empty(int element);
		bool insert_if_not_empty(int element);
		bool study_right_son(Node* &actualNode, int element);
		bool study_left_son(Node* &actualNode, int element);
		void insert_to_right_son(Node* &actualNode, int element);
		void insert_to_left_son(Node* &actualNode, int element);
		void updateParents(Node* &n, Node* &aux);
		void updateGrandpa(Node* &n, Node* &aux);
		void L(Node* n);
		void R(Node* n);
		bool rotate_if_father(Node* &actualNode);
		void rotate_if_grandpa(Node* &actualNode);
		void floation(Node* n);
	public:
		//Public Methods
		SplayTree();

		//Remove, if it exists, a node with value=elem from the SplayTree. It returns true if it existed and it has been removed.
		bool remove(int elem);
		//Looks for a node with value = elem. It returns true if its on the tree. False if not.
		bool search(int elem);
		//Inserts a node with value= elem. If there's another node with the same value, it returns false. True if not.
		bool insert(int element);
};



#endif