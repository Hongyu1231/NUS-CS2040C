#include <iostream>
#include "circularIntLinkedList.h"
#include <ctime>

////////////////////////////////////////////////////////////////////////////
//      Feel free to modify this file to do testing and debuging          //
//      However, you should NOT submit any of these to coursemology       //
////////////////////////////////////////////////////////////////////////////

using namespace std;

void insertHeadTest();
void existTest();
void advanceHeadTest();
void removeHeadTest();
void removeAndAdvanceHeadTest();
void timingTest();

int main()
{
	// Feel free to uncomment the following functions to test/debug your code
	insertHeadTest();
	existTest();
	advanceHeadTest();
	removeHeadTest();
	removeAndAdvanceHeadTest();
	timingTest();
	return 0;
}

void insertHeadTest()
{
	CircularList l;
	cout << "insertHeadtest()" << endl;
	l.insertHead(123);
	cout << "After adding 123" << endl;
	l.print();
	l.insertHead(11);
	cout << "After adding 11" << endl;
	l.print();
	l.insertHead(9);
	cout << "After adding 9" << endl;
	l.print();
	l.insertHead(1);
	cout << "After adding 1" << endl;
	l.print();
	l.insertHead(20);
	cout << "After adding 20" << endl;
	l.print();
	cout << endl;
}

void advanceHeadTest()
{
	cout << "advanceHeadtest()" << endl;
	CircularList l;

	l.insertHead(123);
	l.insertHead(11);
	l.insertHead(9);
	l.insertHead(1);
	l.insertHead(20);

	cout << "The original list:";
	l.print();
	for (int i = 0; i < 5; i++) {
		l.advanceHead();
		cout << "After " << i + 1 << " \"advance\"" << endl;
		cout << "The current list is: ";
		l.print();
	}
	cout << endl;
}

void existTest()
{
	CircularList l;
	cout << "existTest()" << endl;
	l.insertHead(123);
	l.insertHead(11);
	l.insertHead(9);
	l.insertHead(1);
	l.insertHead(20);

	cout << "The list is: ";
	l.print();
	cout << "Does 9 exist in the list? " << (l.exist(9) ? "Yes" : "No") << endl << endl;
	cout << "Does 11 exist in the list? " << (l.exist(11) ? "Yes" : "No") << endl << endl;
	cout << "Does 99 exist in the list? " << (l.exist(99) ? "Yes" : "No") << endl << endl;
	cout << endl;

}

void removeHeadTest()
{

	CircularList l;
	cout << "removeHeadtest()" << endl;
	l.insertHead(123);
	l.insertHead(11);
	l.insertHead(9);
	l.insertHead(1);
	l.insertHead(20);
	for (int i = 0; i < 5; i++) {
		l.removeHead();
		cout << "After removing the head, the current list is: ";
		l.print();
		cout << "Does 9 exist in the list? " << (l.exist(9) ? "Yes" : "No") << endl << endl;
	}
	cout << endl;
}

void removeAndAdvanceHeadTest()
{
	CircularList l;
	cout << "removeAndAdvanceHeadTest()" << endl;
	l.insertHead(123);
	l.insertHead(11);
	l.insertHead(9);
	l.insertHead(1);
	l.insertHead(20);

	for (int i = 0; i < 4; i++) {
		cout << "The current list is: ";
		l.print();
		cout << "Does 9 exist in the list? " << (l.exist(9) ? "Yes" : "No") << endl << endl;
		l.removeHead();
		l.advanceHead();
		cout << "Now we remove the head and advance it once" << endl;
	}
	cout << endl;
}

void timingTest()
{
	cout << "Timing Test" << endl;
	for (int nt = 1; nt <= 1000000; nt *= 10)
	{
		clock_t begin = clock();

		CircularList l; // a new list
		for (int i = 0; i < nt; i++)
			l.insertHead(i);

		clock_t end = clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Time taken for adding " << nt << " items : " << elapsed_secs << "s" << endl;

		begin = clock();
		for (int i = 0; i < (3 * nt / 4); i++)
			l.advanceHead();
		end = clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		cout << "Time taken for advancing three quarters of the list: " << elapsed_secs << "s" << endl;
		cout << "(Head item = " << l.headItem() << ")" << endl << endl;


	}
}