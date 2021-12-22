#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;        //�������� ��������
	Element* pNext; //����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	friend class ForwardList;
};
class ForwardList
{
	Element* Head;
public:
	ForwardList()
	{
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//                            Adding Elements:
	void push_front(int Data)
	{
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) "�����������" ������� � ������ ������:
		New->pNext = Head;
		//3) ������ ����� ������� ������� ������:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) ������� ����� �������:
		Element* New = new Element(Data);
		//2) ������� �� ����� ������:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//3) ��������� ��������� ������� � ����� ������:
		Temp->pNext = New;
	}
	void insert(int Data, int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;
	}

	//                        Removing Elements
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;
	}
	void pop_back()
	{
		Element* Temp=Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
	}
	void erase(int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		/*Element* Erased = Head;
		for (int i = 0; i < index; i++)Erased = Erased->pNext;*/
		Element* Erased = Temp->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
	}

	//                        Methods:
	void print()const
	{
		Element* Temp = Head;  //Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������
		//� ��������� ��������� ������.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //��������� �� ��������� �������.
		}
	}

};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(value, index);
	list.print();
	/*cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();*/
}