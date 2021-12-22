#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;        //Значение элемента
	Element* pNext;  //Адрес следующего элемента
	static int count; //Статическая переменная, которая будет считать кол-во элементов
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

	}

	friend class ForwardList;
};

int Element::count = 0;  //Инициализация статической переменной

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		//int const* - указатель на константу
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - итератор
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp = Temp->pNext)
			push_back(Temp->Data);*/
		*this = other; //Вызываем оператор присвоить
		cout << "CopyConstructor" << this << endl;
	}
	~ForwardList()
	{
		while (Head)(pop_front());
		cout << "LDestructor:\t" << this << endl;
	}
	
	//                  Operator
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp = Temp->pNext)
			push_back(Temp->Data);
		return *this;
		cout << "CopyAssignment" << this << endl;
	}

	//                            Adding Elements:
	void push_front(int Data)
	{
		/*//1) Создаем новый элемент:
		Element* New = new Element(Data);
		//2) "Привязываем" элемент к началу списка:
		New->pNext = Head;
		//3) Делаем новый элемент началом списка:
		Head = New;*/

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		//3) Добавляем созданный элемент в конец списка:
		//Temp->pNext = New;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index > size)
		{
			cout << "Error: Выход за пределы списка: " << endl;
			return;
		}
		//Общий случай
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//---------------------------------------------------------------
		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}

	//                        Removing Elements
	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;

		size--;
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

		size--;
	}

	//                        Methods:
	void print()const
	{
		/*Element* Temp = Head;  //Temp - это Итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ
		//к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; //Переходим на следующий элемент.
		}*/

		for(Element* Temp=Head; Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Кол-во элементов списка: " << size << endl;
		cout << "Общиее кол-во элементов: " << Element::count << endl;
		//cout << "Общиее кол-во элементов: " << Head->count<< endl;
	}

};

//#define BASE_CHECK
//#define COUNT_CHECK
//#define PREFOMANCE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.push_back(123);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
	int value;
	int index;
	cout << "Введите Индекс добовляемого элемента: "; cin >> index;
	cout << "Введите значение добовляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите Индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef PREFOMANCE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "List filled" << endl;
#endif // PREFOMANCE_CHECK

	//int arr[] = { 3,5,8,13,21 };
	ForwardList list = { 3,5,8,13,21 };
	list = list;
	list.print();
	//ForwardList list2= list;;   //CopyConstructor
	ForwardList list2;
	list2 = list;                 //CopyAssignment
	list2 = list;                 //CopyAssignment
	list2.print();
}