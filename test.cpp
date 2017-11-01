#include <iostream>
using namespace std;
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include "SplayTreeHeader.h"

void show_Node(Node* n);

//To get operation execution time.
double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b);

int main() {
	SplayTree s = SplayTree();
	LARGE_INTEGER start, end;
	double tiempo;
	srand(time(NULL));
	//We print the result in result.dat.
	ofstream nf("result.dat");
	int m, n;

	for (int i = 0; i < 50000; i++) {
		m = rand() % 3;
		n = rand() % 50000;
		if (m == 0) {
			//Insert
			QueryPerformanceCounter(&start);
			s.insert(n);
			QueryPerformanceCounter(&end);
			nf << i << " " << performancecounter_diff(&end, &start) * 1000 << endl;
		}
		else if (m == 1) {
			//Search
			QueryPerformanceCounter(&start);
			s.search(n);

			QueryPerformanceCounter(&end);
			nf << i << " " << performancecounter_diff(&end, &start) * 1000 << endl;

		}
		else {
			//Remove
			QueryPerformanceCounter(&start);
			s.remove(n);
			QueryPerformanceCounter(&end);
			nf << i << " " << performancecounter_diff(&end, &start) * 1000 << endl;
		}
	}
	return 0;
}


double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b) {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void show_Node(Node* n) {
	if (n != NULL) {
		if (n->father != NULL) {
			cout << n->value << " with father with value " << n->father->value << endl;
		}

		if (n->rightSon != NULL) {
			cout << n->value << " with right son with value " << n->rightSon->value << endl;
			show_Node(n->rightSon);
		}
		if (n->leftSon != NULL) {
			cout << n->value << " with left son with value " << n->leftSon->value << endl;
			show_Node(n->leftSon);
		}
	}
}