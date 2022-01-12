#include"ClassList.h"

/////////////////////////////////////////////////////////////////////////////////////
///////////////          Class Defintion (Определение Класса)         ///////////////
/////////////////////////////////////////////////////////////////////////////////////



template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}
///////////////////////////////////////////////////////////////////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BaseItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator()
{
#ifdef DEBUG
	cout << "BaseItDestructor:\t" << this << endl;
#endif // DEBUG
}

template<typename T>bool  List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template<typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
///////////////////////////////////////////////////////////////////
template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}

//                                Operator:
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstIterator::Temp = ConstIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstIterator::Temp = ConstIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator:: operator--()
{
	ConstIterator::Temp = ConstIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstIterator::Temp = ConstIterator::Temp->pPrev;
	return old;
}
///////////////////////////////////////////////////////////////////
template <typename T>List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}

//                            Operator:
template <typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator ::operator++()
{
	ConstReverseIterator::Temp = ConstReverseIterator::Temp->pPrev;
	return *this;
}
template <typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstReverseIterator::Temp = ConstReverseIterator::Temp->pPrev;
	return old;
}
template <typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstReverseIterator::Temp = ConstReverseIterator::Temp->pNext;
	return *this;
}
template <typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstReverseIterator::Temp = ConstReverseIterator::Temp->pNext;
	return old;
}
///////////////////////////////////////////////////////////////////
template <typename T>T& List<T>::Iterator::operator*()
{
	return ConstIterator::Temp->Data;
}
template <typename T>T& List<T>::ReverseIterator::operator*()
{
	return  ConstReverseIterator::Temp->Data;
}
///////////////////////////////////////////////////////////////////
template <typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template <typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template <typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}

//                             Constructors:
template <typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

}
template <typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}

	//for (int const* it = il.end() - 1; it != il.begin() - 1; it--)push_front(*it);

	//for (T i : il)push_back(i);
}
template <typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
#ifdef DEBUG
	cout << "CopyConstructor:\t" << this << endl;
#endif // DEBUG

}
template <typename T>List<T>::List(List<T>&& other)
{
	*this = std::move(other);
#ifdef DEBUG
	cout << "MoveConstructor:\t" << this << endl;
#endif // DEBUG

}
template <typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif // DEBUG

}

//                              Operators:
template <typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	//Deep copy (Глубокое копирование) - Побитовое копирование:
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
#ifdef DEBUG
	cout << "CopeAssignment:\t" << this << endl;
#endif // DEBUG

	return *this;
}
template <typename T>List<T>& List<T>::operator=(List<T>&& other)
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
#ifdef DEBUG
	cout << "MoveAssignment:\t" << this << endl;
#endif // DEBUG
	return *this;
}

//                            Adding elements:
template <typename T>void List<T>::push_front(T Data)
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
template <typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Element* New = new Element(Data);//1)
	New->pPrev = Tail;//2)
	Tail->pNext = New;//3)
	Tail = New;//4)
	size++;
}
template <typename T>void List<T>::insert(T Data, int Index)
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

//                           Removing Elements
template <typename T>void List<T>::pop_front()
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
template <typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T>void List<T>::erase(int Index)
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

//                            Methods:
template <typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template <typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;

}
/////////////////////////////////////////////////////////////////////////////////////
////////////        Class Defintion End (Конец Определение Класса)        ///////////
/////////////////////////////////////////////////////////////////////////////////////

//                      Non-member function related to class
//                    (Глобальные функции связфнные с классом):
template<typename T>void print_list(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>void reverse_print_list(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
}

