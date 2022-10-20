#pragma once
#include <memory>

using namespace std;

template<typename T>
class Node
{
public:
	Node(unique_ptr<T> data);
	unique_ptr<T> Data;
	shared_ptr<Node<T>> Next;
	weak_ptr<Node<T>> Prev;
};

template<typename T>
inline Node<T>::Node(unique_ptr<T> data)
	: Data(move(data))
{
}
