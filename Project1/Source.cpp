#include <list>
#include <iostream>
#include "CList.h"

using namespace std;

int main()
{
	
	
	CList<int> CList_Test;
	CList_Test.Push_Back(1);
	CList_Test.Push_Back(2);
	CList_Test.Push_Back(3);
	CList_Test.Push_Back(4);

	CList<int>::Iterator iterator_test = CList_Test.begin();

	CList<int>::Iterator iterator_test2 = CList_Test.erase(iterator_test);

	/*list<int> Test_List;
	Test_List.push_back(10);

	list<int>::iterator Iter = Test_List.begin();
	list<int>::iterator Iter_test = Test_List.erase((Iter));
	cout << *Iter_test;*/
	


	return 0;
}