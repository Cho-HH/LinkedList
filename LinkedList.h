#pragma once
#include <memory>
#include "Node.h"

using namespace std;

template<typename T>
class LinkedList
{
public:
	LinkedList();
	void Insert(unique_ptr<T> data);
	bool Delete(const T& data);
	bool Search(const T& data) const;
	unsigned int GetSize() const;

	void Print() const;
	void PrintReverse() const;

private:
	unsigned int mSize;
	shared_ptr<Node<T>> mHead;
	shared_ptr<Node<T>> mTail;
};

template<typename T>
inline LinkedList<T>::LinkedList()
	: mSize(0)
{
}

template<typename T>
inline void LinkedList<T>::Insert(unique_ptr<T> data)
{
	if (mHead == nullptr)
	{
		mHead = make_shared<Node<T>>(move(data));
		mTail = mHead;
	}
	else
	{
		auto newNode = make_shared<Node<T>>(move(data));
		mTail->Next = newNode;
		newNode->Prev = mTail;
		mTail = newNode;
	}
	mSize++;
}

template<typename T>
inline bool LinkedList<T>::Delete(const T& data)
{
	auto curNode = mHead;
	while (curNode != nullptr)
	{
		if (*(curNode->Data) == data)
		{
			if (curNode == mHead)
			{
				mHead = curNode->Next;
				if (mHead == nullptr)
				{
					mTail = nullptr;
				}
			}
			else if (curNode == mTail)
			{
				mTail = mTail->Prev.lock();
				mTail->Next = nullptr;
			}
			else
			{
				auto prevNode = curNode->Prev.lock();
				prevNode->Next = curNode->Next;
				curNode->Next->Prev = curNode->Prev;
			}
			mSize--;
			return true;
		}
		curNode = curNode->Next;
	}
	return false;
}

template<typename T>
inline bool LinkedList<T>::Search(const T& data) const
{
	auto curNode = mHead;
	while (curNode != nullptr)
	{
		if (*(curNode->data) == data)
		{
			return true;
		}
		curNode = curNode->Next;
	}
	return false;
}

template<typename T>
inline unsigned int LinkedList<T>::GetSize() const
{
	return mSize;
}

template<typename T>
inline void LinkedList<T>::Print() const
{
	if (mSize == 0)
	{
		cout << "list is empty" << '\n';
		return;
	}

	auto curNode = mHead;
	while (curNode != nullptr)
	{
		cout << *(curNode->Data) << ' ';
		curNode = curNode->Next;
	}
	cout << '\n';
}

template<typename T>
inline void LinkedList<T>::PrintReverse() const
{
	if (mSize == 0)
	{
		cout << "list is empty" << '\n';
		return;
	}

	auto curNode = mTail;
	while (curNode != nullptr)
	{
		cout << *(curNode->Data) << ' ';
		curNode = curNode->Prev.lock();
	}
	cout << '\n';

}
