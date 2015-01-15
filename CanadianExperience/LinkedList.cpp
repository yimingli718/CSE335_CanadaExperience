/**
 * \file LinkedList.cpp
 *
 * \author Yiming Li
 */


#include "stdafx.h"
#include "LinkedList.h"


/**
 * \brief Constructor
 */
CLinkedList::CLinkedList()
{
}

/**
 * \brief Destructor
 */
CLinkedList::~CLinkedList()
{
}


/**
 * \brief Insert a snowfalke to the tail of linked list 
 * \param flake the Snowflake to insert to the end
 */
void CLinkedList::Insert(std::shared_ptr<CSnowflake> flake){
	if (head == nullptr && tail == nullptr){
		head = flake;
		tail = head;
	}
	else{
		tail->SetNext(flake);
		tail = flake;
	}
	size++;
}


/**
 * \brief Popfront the first snowflake in the list and return it
 * \returns the snowfleak pop out
 */
std::shared_ptr<CSnowflake> CLinkedList::Popfront(){
	if (size > 1){
		size--;
		auto temp = head;
		head = head->GetNext();
		return temp;
	}
	else if(size == 1){
		size--;
		auto temp = head;
		head = nullptr;
		tail = nullptr;
		return temp;
	}
}

/**
* \brief Remove a certain point from the linked list
*/
void CLinkedList::Remove(std::shared_ptr<CSnowflake> temp){
	size--;
	std::shared_ptr<CSnowflake> del = head;
	if (temp == head){
		head = head->GetNext();
		return;
	}
	while (del->GetNext() != temp){
		del = del->GetNext();
	}
	if (del->GetNext() == temp && del->GetNext() != tail){
		del->SetNext(del->GetNext()->GetNext());
		return;
	}
	else if (del->GetNext() == temp && del->GetNext() == tail){
		tail = del;
		del->SetNext(nullptr);
		return;
	}
}

