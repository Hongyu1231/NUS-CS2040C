#include "BST.h"


void testInsertion1(bool printwithHeightAndWeight = true);
void testInsertion2(bool printwithHeightAndWeight = true);
void rankTest1();
void selectTest1();


int main() {

	testInsertion1(true);
	testInsertion2(true);
	rankTest1();
	selectTest1();

}

void testInsertion1(bool printwithHeightAndWeight) {

	cout << "Insertion Test 1" << endl;
	int array[] = { 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14 };
	BinarySearchTree<int> bsti;
	for (int i = 0; i < 15; i++)
		bsti.insert(array[i]);

	bsti.printTree(printwithHeightAndWeight);
	cout << endl << endl;
	cout << "The size of the tree is " << bsti.size() << endl;
	cout << "Pre-order Traversal:" << endl;
	bsti.preOrderPrint();
	cout << "In-order Traversal:" << endl;
	bsti.inOrderPrint();
	cout << "Post-order Traversal:" << endl;
	bsti.postOrderPrint();

	cout << "Level order traversal" << endl;
	//bsti.LOT();

	cout << endl << endl;

	
}

void testInsertion2(bool printwithHeightAndWeight) {

	cout << "Insertion Test 2" << endl;
	cout << "The tree shape should be the same as Test 1" << endl;
	cout << "if you have done the balancing correctly." << endl;
	BinarySearchTree<int> bsti;
	for (int i = 0; i < 15; i++)
		bsti.insert(i);

	bsti.printTree(printwithHeightAndWeight);
	cout << endl << endl;
	cout << "The size of the tree is " << bsti.size() << endl;
	cout << "Pre-order Traversal:" << endl;
	bsti.preOrderPrint();
	cout << "In-order Traversal:" << endl;
	bsti.inOrderPrint();
	cout << "Post-order Traversal:" << endl;
	bsti.postOrderPrint();

	cout << endl << endl;
}


void rankTest1()
{
	cout << "Rank Test 1" << endl;
	int array[] = { 7,3,11,1,5,9,13,0,2,4,6,8,10,12,14 };
	for (int i = 0; i < 15; i++)
		array[i] *= 2;
	BinarySearchTree<int> bsti;
	for (int i = 0; i < 15; i++)
		bsti.insert(array[i]);
	bsti.printTree(true);
	for (int i = 0; i < 16; i++)
		cout << "The rank of " << i * 2 << " is " << bsti.rank(i * 2) << endl;
	cout << endl;

}

void selectTest1()
{
	cout << "Select Test 1" << endl;
	int array[] = { 7,3,11,1,5,9,13,0,2,4,6,8,10,12,14 };
	for (int i = 0; i < 15; i++)
		array[i] *= 2;
	BinarySearchTree<int> bsti;
	for (int i = 0; i < 15; i++)
		bsti.insert(array[i]);
	bsti.printTree(true);
	for (int i = 1; i < 16; i++)
		cout << "The item with rank " << i << " is " << bsti.select(i) << endl;
	cout << endl;

}

