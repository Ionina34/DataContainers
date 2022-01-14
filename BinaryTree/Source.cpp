#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :
			Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	} *Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
			insert(*it, Root);
	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}


	void insert(int Data)
	{
		insert(Data, Root);
	}

	void print()const
	{
		print(this->Root);
		cout << endl;
	}

	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int count()const
	{
		return count(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void clear()
	{
		 clear(Root);
		//Root == nullptr;
	}
	int depth()const
	{
		return depth(Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else //if(Data> Root-> Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		//insert(Data, Root);
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft != nullptr)return minValue(Root->pLeft);
		else return Root->Data;*/

		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight != nullptr)return maxValue(Root->pRight);
		else return Root->Data;*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int count(Element* Root)const
	{
		/*if (Root->pLeft == nullptr && Root->pRight == nullptr)return 1;
		if (Root == nullptr)return 0;
		int right, left;
		//return count(Root->pLeft) + count(Root->pRight) + 1;
		if (Root->pLeft != nullptr)left = count(Root->pLeft);
		else left = 0;
		if (Root->pRight != nullptr)right = count(Root->pRight);
		else right = 0;
		return left + right + 1;*/

		/*if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;*/

		return Root == nullptr ? 0 : count(Root->pLeft) + count(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		/*static int summ = 0;
		if (Root == nullptr)return 0;
		else
		{
			summ += Root->Data;
			sum(Root->pLeft);
			sum(Root->pRight);
		}
		return summ;*/

		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return 
			depth(Root->pLeft)+1 > depth(Root->pRight)+1 ? 
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void clear(Element*& Root)const
	{
		if (Root == nullptr)return;
		if (Root->pLeft)clear(Root->pLeft);
		if (Root->pRight)clear(Root->pRight);
		delete Root;
		Root = nullptr;
	}
};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		//insert(Data, Root);
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ���-�� ���������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << "����������� �������� ������: " << tree.minValue() << endl;
	cout << "������������ �������� ������: " << tree.maxValue() << endl;
	cout << "���-�� ��������� ������: " << tree.count() << endl;
	cout << "����� ��������� ������: " << tree.sum() << endl;
	cout << "������� �������������� ��������� ������: " << tree.avg() << endl;
	cout << "������� ������: " << tree.depth() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "����������� �������� ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� ������: " << u_tree.maxValue() << endl;
	cout << "���-�� ��������� ������: " << u_tree.count() << endl;
	cout << "����� ��������� ������: " << u_tree.sum() << endl;
	cout << "������� �������������� ��������� ������: " << u_tree.avg() << endl;
	cout << "������� ������: " << u_tree.depth() << endl;

	u_tree.clear();
	u_tree.print();
#endif // BASE_CHECK

	Tree tree = { 50,25,75,16,32,/*48,*/64,80/*,77*/};
	tree.print();
	cout << "������� ������: " << tree.depth() << endl;
}