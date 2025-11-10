#include "BST.h"

void testInsertion1();
void testInsertion2();
void sumLETest1();
void sumLETest2();
void magicalPancakeGymTest();
void heavyMagicalPancakeGymTest1();
void heavyMagicalPancakeGymTest2();


int main() {

	/*testInsertion1();*/
	//testInsertion2();
	//sumLETest1();
	//sumLETest2();
	//magicalPancakeGymTest();
	heavyMagicalPancakeGymTest1();
	heavyMagicalPancakeGymTest2();

}

//void testInsertion1() {
//
//	cout << "Insertion Test 1" << endl;
//	cout << "This tree should look the same with our without balancing" << endl;
//	int array[] = { 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14 };
//	BinarySearchTree<int> bsti(false);
//	for (int i = 0; i < 15; i++)
//		bsti.insert(array[i]);
//
//	bsti.printTree(false);
//	cout << endl << endl;
//	bsti.printTree(true);
//	cout << endl << endl;
//	cout << "The size of the tree is " << bsti.size() << endl;
//
//}
//
//void testInsertion2() {
//
//	cout << "Insertion Test 2" << endl;
//	cout << "The tree shape should be the same as Test 1" << endl;
//	cout << "if you have done the balancing correctly." << endl;
//	BinarySearchTree<int> bsti;
//	for (int i = 0; i < 15; i++)
//		bsti.insert(i);
//
//	bsti.printTree(true);
//	cout << endl << endl;
//}
//
//void sumLETest1() {
//
//	cout << "sumLETest1" << endl;
//	cout << "This tree should look the same with or without balancing" << endl;
//	int array[] = { 7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14 };
//	BinarySearchTree<int> bsti(false);
//	for (int i = 0; i < 15; i++)
//		bsti.insert(array[i]);
//
//	bsti.printTree(false);
//	cout << endl << endl;
//	bsti.printTree(true);
//
//	for (int i = 0; i < 15; i++)
//		cout << "The sum less than " << i << " in the tree = " << bsti.sumLE(i) << endl;
//	cout << endl << endl;
//}
//
//void sumLETest2() {
//
//	cout << "Sum LE Test 2" << endl;
//	BinarySearchTree<int> bsti;
//	for (int i = -100000; i <= 100000; i++)
//		bsti.insert(i);
//
//	//bsti.printTree(true); // you don't want to print this tree out
//
//	cout << "The size of the tree is " << bsti.size() << endl;
//	for (int i = 90000; i <= 100000; i += 1000)
//		cout << "The sum less than or equal to " << i << " is " << bsti.sumLE(i) << endl;
//	
//	cout << endl << endl;
//}

void magicalPancakeGymTest()
{
	cout << "Magical Pancake Test" << endl;
	MagicalPancakeGym mpg;
	long long int ow,ob;
	mpg.addPancake(10);
	mpg.addPancake(12);
	mpg.addPancake(17);
	mpg.addPancake(3);
	mpg.addPancake(9);
	cout << "The initial pancake stack after adding 10, 12, 17, 3 and 9: \n";
	mpg.printPancakes();


	int test[] = { 0,1,3,4,10,14,16,25,26,51,52,100 };
	for (int i = 0; i < 12; i++)
	{
		ob = mpg.minimalBottomPancake2Lift(test[i]);
		ow = mpg.totalWeightAbovePancake(ob);
		if (ob == -1)
			cout << "Not enough pancakes to provide a stack of at least " << test[i] << "g" << endl;
		else			
			cout << "Minimal bottom to have at least " << test[i] << "g of pancakes is to lift pancake " << ob << " with total weight = " << ow << "g"<< endl;

	}

	mpg.addPancake(50);
	mpg.addPancake(78);
	mpg.addPancake(7);
	mpg.addPancake(5);
	mpg.addPancake(2);
	cout << "\nThe pancake stack after adding 50, 78, 7, 5 and 2: \n";
	mpg.printPancakes();
	for (int i = 0; i < 12; i++)
	{
		ob = mpg.minimalBottomPancake2Lift(test[i]);
		ow = mpg.totalWeightAbovePancake(ob);
		if (ob == -1)
			cout << "Not enough pancakes to provide a stack of at least " << test[i] << "g" << endl;
		else
			cout << "Minimal bottom to have at least " << test[i] << "g of pancakes is to lift pancake " << ob << " with total weight = " << ow << "g" << endl;

	}
}

void heavyMagicalPancakeGymTest1()
{

	cout << "Heavy Magical Pancake Test 1" << endl;
	MagicalPancakeGym mpg;
	long long int ow, ob;

	for (long long int i = 1; i <= 20000000001; i+= 2000000000)
		mpg.addPancake(i);

	mpg.printPancakes();

	long long int test[] = { 0,1,3,4,10,14,16,25,20000000001,110000000010,110000000011,110000000012 };
	for (int i = 0; i < 12; i++)
	{
		ob = mpg.minimalBottomPancake2Lift(test[i]);
		ow = mpg.totalWeightAbovePancake(ob);
		if (ob == -1)
			cout << "Not enough pancakes to provide a stack of at least " << test[i] << "g" << endl;
		else
			cout << "Minimal bottom to have at least " << test[i] << "g of pancakes is to lift pancake " << ob << " with total weight = " << ow << "g" << endl;

	}
	cout << endl;
}


void heavyMagicalPancakeGymTest2()
{

	cout << "Heavy Magical Pancake Test 2" << endl;
	MagicalPancakeGym mpg;
	long long int ow, ob;

	for (long long int i = 1; i <= 200001; i++)
		mpg.addPancake(i);

	//mpg.printPancakes();

	long long int test[] = { 0,1,3,4,10,14,16,25,20000000001,20000300000,20000300001,20000300002 };
	for (int i = 0; i < 12; i++)
	{
		ob = mpg.minimalBottomPancake2Lift(test[i]);
		ow = mpg.totalWeightAbovePancake(ob);
		if (ob == -1)
			cout << "Not enough pancakes to provide a stack of at least " << test[i] << "g" << endl;
		else
			cout << "Minimal bottom to have at least " << test[i] << "g of pancakes is to lift pancake " << ob << " with total weight = " << ow << "g" << endl;

	}

}

