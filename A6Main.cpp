#include<iostream>
#include"AVLTree.h"
using namespace std; 

int main()
{
	AVLTree T1;
	/////////////// TEST 1: INSERT 7 ENTRIES INTO TREE T1 //////////////////////
	T1.put(10);
	T1.put(20);
	T1.put(5);
	T1.put(30);
	T1.put(35);
	T1.put(25); 
	T1.put(40);
	
	cout << "\nAfter inserting 7 entries into AVL tree T1, T1 is now:" << endl;
	T1.print();

	//////////////// TEST 2: DELETE AN ENTRY FROM T1 ////////////////////////////
	T1.erase(5);
	cout << "\nAfter erasing key 5 from T1, T1 is now:" << endl;
	T1.print(); 

	//////////////// TEST 3: FIND KEYS IN T1 ////////////////////////////////////
	AVLTree::Node answer; 
	answer = T1.find(10); 
	cout << "\nFinding key 10 in T1..." << endl;
	if (answer == T1.getEnd())
		cout << "Key not found in T1." << endl; 
	else
		cout << "Key is found at: " << answer.toString() << endl;

	answer = T1.find(5);
	cout << "\nFinding key 5 in T1..." << endl;
	if (answer == T1.getEnd())
		cout << "Key not found in T1." << endl; 
	else
		cout << "Key is found at: " << answer.toString() << endl << endl;
	cout << "========================================================" << endl;

	/////////////// TEST 4: INSERT 15 ENTRIES INTO A NEW TREE T2 ////////////////
	AVLTree T2; 
	for (int i=1; i<= 15; i++)
		T2.put(i); 
	
	cout << "\nAfter inserting 15 entries into AVL tree T2, T2 is now: " << endl;
	T2.print(); 

	/////////////// TEST 5: DELETE 5 ENTRIES FROM T2 ////////////////////////////
	T2.erase(6);
	T2.erase(7); 
	T2.erase(5); 
	T2.erase(2); 
	T2.erase(4); 

	cout << "\nAfter deleting keys 6, 7, 5, 2, 4 from T2, T2 is now: " << endl;
	T2.print();

	////////////// TEST 6: INSERT DUPLICATES /////////////////////////////////////
	AVLTree T3;
	T3.put(1);
	T3.put(2);
	T3.put(1);

	cout << "==========================================================" << endl;
	cout << "\nTest insert duplicate keys: " << endl;
	T3.print();

	return 0;
}

