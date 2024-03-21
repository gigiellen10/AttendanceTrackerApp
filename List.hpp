/* File: List.hpp
Purpose: This file contains the List class and method definition(s)
Date: March 13th, 2024 */

#pragma once

#include "Node.hpp"
#include "Data.hpp"

template <class T>
class List
{
public:
	/* constructor */
	List(Node<T>* newmpHead = nullptr);

	/* setters and getters */
	void setmpHead(const Node<T>* newmpHead);

	Node<T>* getmpHead() const;

	/* methods/list operations */
	bool insertAtFront(Data& newData);
	bool isEmpty(void);
	Node<T>* searchList(int searchID);
	Node<T>* searchList(string& searchString);



	~List();

private:
	Node<T>* mpHead;
};

template <class T>
List<T>::List(Node<T>* newmpHead)
{
	mpHead = newmpHead;
}

/* setters and getters */

template <class T>
void List<T>::setmpHead(const Node<T>* newmpHead)
{
	mpHead = newmpHead;
}

template <class T>
Node<T>* List<T>::getmpHead() const
{
	return mpHead;
}


template <class T>
bool List<T>::insertAtFront(Data& newData)
{
	int success = false;

	// allocate memory with "new" keyword and init Node to newData
	Node<Data>* pMem = new Node<Data>(newData);

	if (pMem != nullptr)
	{
		// successfully allocated memory on heap
		success = true;

		// update next ptr of new node to node currently at front of list (if mpHead is null, pNext is set to null...no harm done)
		pMem->setmpNext(mpHead);
		mpHead = pMem; // update mpHead complete insert

	}

	return success;

}

template <class T>
bool List<T>::isEmpty(void)
{
	return mpHead == nullptr;
}

template <class T>
List<T>::~List()
{
	// will call destructor of node which recursively deletes the other nodes in sequence
	if (mpHead != nullptr)
	{
		delete mpHead;
	}

	// reset mpHead to null
	mpHead = nullptr;
}

// searches for the node containing the ID number passed in
template <class T>
Node<T>* List<T>::searchList(int searchID)
{
	Node<T>* iterateList = this->getmpHead();
	Data temp; // use to access private data of node

	while (iterateList != nullptr)
	{
		// sequential search
		temp = iterateList->getData();
		if (temp.getID() == searchID)
		{
			// we found the ID we were looking for
			return iterateList;
		}

		iterateList = iterateList->getmpNext();
	}

	return iterateList; // will only hit this point if iterateList becomes nullptr, so not found
}

// searches for the node containing the string passed in
template <class T>
Node<T>* List<T>::searchList(string& searchString)
{
	Node<T>* iterateList = this->getmpHead();

	while (iterateList != nullptr)
	{
		// sequential search
		if (getFullStudentName(iterateList) == searchString)
		{
			// we found the ID we were looking for
			return iterateList;
		}

		iterateList = iterateList->getmpNext();
	}

	return iterateList; // will only hit this point if iterateList becomes nullptr, so not found

}