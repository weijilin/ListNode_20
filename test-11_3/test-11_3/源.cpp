#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
namespace bite
{
	template<class T>
	struct list_node
	{
		list_node(const T& data = T())
		: prev(nullptr)
		, next(nullptr)
		, _data(data)
		{}

		list_node<T>* prev;
		list_node<T>* next;
		T _data;
	};

	template<class T>
	class list_iterator
	{
		typedef list_node<T> node;
		typedef list_iterator<T> self;
	public:
		list_iterator(node* pNode = nullptr)
			: _pNode(pNode)
		{}

		// 让迭代器具有指针类似操作
		T& operator*()
		{
			return _pNode->_data;
		}

		T* operator->()
		{
			return &operator*();
		}

		// 让迭代器可以移动
		self& operator++()
		{
			_pNode = _pNode->next;
			return *this;
		}

		self operator++(int)
		{
			self temp(*this);
			_pNode = _pNode->next;
			return temp;
		}

		self& operator--()
		{
			_pNode = _pNode->prev;
			return *this;
		}

		self operator--(int)
		{
			self temp(*this);
			_pNode = _pNode->prev;
			return temp;
		}

		// 迭代器具有比较操作
		bool operator!=(const self& s)const
		{
			return _pNode != s._pNode;
		}

		bool operator==(const self& s)const
		{
			return _pNode == s._pNode;
		}

		node* _pNode;
	};


	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef list_iterator<T> iterator;

	public:
		list()
		{
			creathead();
		}

		list(int n, const T& data)
		{
			creathead();
			for (int i = 0; i < n; ++i)
				push_back(data);
		}

		template<class Iterator>
		list(Iterator first, Iterator last)
		{
			creathead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& L)
		{
			creathead();

			node* pCur = L._pHead->next;
			while (pCur != L._pHead)
			{
				push_back(pCur->_data);
				pCur = pCur->next;
			}
		}

		/////////////////////////////////////
		// iterator
		iterator begin()
		{
			return iterator(_pHead->next);
		}

		iterator end()
		{
			return iterator(_pHead);
		}

		////////////////////////////////////
		// capacity
		size_t size()const
		{
			size_t count = 0;
			node* pCur = _pHead->next;
			while (pCur != _pHead)
			{
				count++;
				pCur = pCur->next;
			}

			return count;
		}

		bool empty()const
		{
			return _pHead->next == _pHead;
		}

		void resize(size_t newsize, const T& data = T())
		{
			size_t oldsize = size();
			if (newsize > oldsize)
			{
				for (size_t i = oldsize; i < newsize; ++i)
					push_back(data);
			}
			else
			{
				for (size_t i = newsize; i < oldsize; ++i)
					pop_back();
			}
		}

		//////////////////////////////////////
		// access
		T& front()
		{
			return _pHead->next->_data;
		}

		const T& front()const
		{
			return _pHead->next->_data;
		}

		T& back()
		{
			return _pHead->prev->_data;
		}

		const T& back()const
		{
			return _pHead->prev->_data;
		}

		///////////////////////////////////////
		// modify
		void push_back(const T& data)
		{
			insert(end(), data);
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& data)
		{
			insert(begin(), data);
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator insert(iterator pos, const T& data)
		{
			node* pCur = pos._pNode;
			node* pNewNode = new node(data);

			pNewNode->next = pCur;
			pNewNode->prev = pCur->prev;

			pCur->prev = pNewNode;
			pNewNode->prev->next = pNewNode;

			return iterator(pNewNode);
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
				return;

			node* pDelNode = pos._pNode;
			node* pRetNode = pDelNode->next;

			pDelNode->prev->next = pDelNode->next;
			pDelNode->next->prev = pDelNode->prev;
			delete pDelNode;

			return iterator(pRetNode);
		}

		void clear()
		{
			node* pCur = _pHead->next;
			while (pCur != _pHead)
			{
				_pHead->next = pCur->next;
				delete pCur;
				pCur = _pHead->next;
			}

			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}

		void swap(const list<T>& l)
		{
			swap(_pHead, l._pHead);
		}

	private:
		void creathead()
		{
			_pHead = new node;
			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}
	private:
		node* _pHead;
	};
}

#include <vector>

void TestList1()
{
	bite::list<int> L1;
	bite::list<int> L2(10, 5);

	vector<int> v{ 1, 2, 3, 4 };
	bite::list<int> L3(v.begin(), v.end());

	bite::list<int> L4(L3);

	auto it = L2.begin();
	while (it != L2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : L3)
		cout << e << " ";
	cout << endl;
}

int main()
{
	TestList1();
	return 0;
}

