#include <iostream>
#include <ctime>
#include "skip_list.h"
#include "entry.h"
using namespace std;


int main()
{
	srand(time(0));
	SkipList test;
	Entry element1;
	element1.random();
	cout << "Inserting Element 1: " << element1.toString() << endl;
	test.put(element1.getKey(),element1.getValue());
	Entry element2;
	element2.random();
	cout << "Inserting Element 2: " << element2.toString() << endl;
	test.put(element2.getKey(),element2.getValue());
	Entry element3;
	element3.random();
	cout << "Inserting Element 3: " << element3.toString() << endl;
	test.put(element3.getKey(),element3.getValue());
	Entry element4;
	element4.random();
	cout << "Inserting Element 4: " << element4.toString() << endl;
	test.put(element4.getKey(),element4.getValue());
	Entry element5;
	element5.random();
	cout << "Inserting Element 5: " << element5.toString() << endl;
	test.put(element5.getKey(),element5.getValue());
	Entry element6;
	element6.random();
	cout << "Inserting Element 6: " << element6.toString() << endl;
	test.put(element6.getKey(),element6.getValue());
	Entry element7;
	element7.random();
	cout << "Inserting Element 7: " << element7.toString() << endl;
	test.put(element7.getKey(),element7.getValue());
	Entry element8;
	element8.random();
	cout << "Inserting Element 8: " << element8.toString() << endl;
	test.put(element8.getKey(),element8.getValue());
	cout << "-----Printing the elemets in the skipList-----" << endl;
	test.print();
	/* Now delete an Entry from the SkipList   */
	cout << "Deleting the entry: " << element4.toString() << endl;
	test.erase(element4.getKey());
	cout << "-----Printing the elemets in the skipList After the deletion-----" << endl;
	test.print();
	Entry test_find1=test.find(element6.getKey());
	cout << "searching for entry of Element 6: " << element6.toString() << endl;
	cout << "The entry that was found is: " << test_find1.toString() << endl;
	cout << "searching for entry of Element 4: " << element4.toString() << endl;
	Entry test_find2=test.find(element4.getKey());
	cout << "The entry that was found: " << test_find2.toString() << endl; 
	/* testing the greaterEntry(k) and lessEntry(k) methods */
	cout << "finding the entry with the lowest key that is greater than key: " << element3.getKey() << endl;
	Entry test_find3=test.greaterEntry(element3.getKey());
	cout << "The entry with the lowest key that is greater than key of Element 3 is: " << test_find3.toString() << endl;
	cout << "finding the entry with the greatest key that is less than key: " << element4.getKey() << endl;
	Entry test_find4=test.lessEntry(element4.getKey());
	cout << "The entry with the greatest key that is less than key Element 4 is: " << test_find4.toString() << endl;
	int size=40;
	SkipList arrayOfEntries;
	Entry* myElements=new Entry[size];
	/* Inserting 40 entries in the SkipList */
	for(int i=0;i<size;i++)
	{
		myElements[i].random();
		arrayOfEntries.put(myElements[i].getKey(),myElements[i].getValue());
	}
	cout << "-----Printing the SkipList with inserted 40 entries-----" << endl;
	arrayOfEntries.print();
	delete [] myElements;
	return 0;
}