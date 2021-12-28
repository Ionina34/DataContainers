#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		friend class List;
	}*Head, * Tail;//Сразу же после описания класа Element объявляем 2 указателя на Element
	size_t size;
public:

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		//                                Operator:
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		 int& operator*()
		{
			return Temp->Data;
		}

	};

	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
		}

		//                            Operator:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator& operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator& operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator==(const ReverseIterator& other)
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		 int& operator*()
		{
			return Temp->Data;
		}

	};

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	//                      Constructors:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		/*for (int const* it = il.begin(); it!= il.end(); it++)
		{
			push_back(*it);
		}*/

		//for (int const* it = il.end() - 1; it != il.begin() - 1; it--)push_front(*it);

		for (int i : il)push_back(i);
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	List(List&& other)
	{
		*this = std::move(other);
		cout << "MoveConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//                              Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Deep copy (Глубокое копирование) - Побитовое копирование:
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopeAssignment:\t" << this << endl;
		return *this;
	}
	List& operator=(List&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		//Shallow copy - Поверхностое копирование:
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size = other.size;

		//Обнуление other:
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	//                            Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//Добавление элемента частный случай:
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		//Общий случай:
		Element* New = new Element(Data);//1)
		New->pNext = Head;//2)
		Head->pPrev = New;//3)
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);//1)
		New->pPrev = Tail;//2)
		Tail->pNext = New;//3)
		Tail = New;//4)
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);

		Element* Temp; //Создаем итератор, но мы пока не знаем,
		//с какой стороны списка лучше зайти, с начала или с конца.
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		//Неважно, с какой стороны мы добрались до нужной позиции,
		//вставка элемента будет осуществляться по одному и томуже алгоритму:
		Element* New = new Element(Data); //1)
		New->pNext = Temp;//2)
		New->pPrev = Temp->pPrev;//3)
		Temp->pPrev->pNext = New;//4)
		Temp->pPrev = New;
		size++;
	}

	//                    Removing Elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			//Удаление единственного элемента из списка:
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(int Index)
	{
		if (Index >= size)return;
		if (Index == 0)return pop_front();
		if (Index == size - 1)return pop_back();

		//Доходим до нужного элемента:
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}

		//Исключаем его из списка:
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;

		//Удаляем элемент из памяти:
		delete Temp;
		size--;
	}

	//                     Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;

	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int index;
	int value;
	cout << "Введите индекс добавдяемого элемента: "; cin >> index;
	cout << "Введите значение добавдяемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List list = { 3,5,8,13,21 };
	list.print();
	list.reverse_print();
	List list2 = list;
	/*list2.print();
	list2.reverse_print();*/
	for (int i : list2)cout << i << tab; cout << endl;

	for (List::ReverseIterator rit = list2.rbegin(); rit != list2.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
}