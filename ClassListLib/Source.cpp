#include<ClassList.h>

#pragma comment(lib, "ClassList.lib")

void main()
{
	setlocale(LC_ALL, " ");
	List<int> list1 = { 2,5,8,13,21 };
	list1.print();
	list1.reverse_print();
}