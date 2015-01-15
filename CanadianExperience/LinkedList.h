/**
 * \file LinkedList.h
 *
 * \author Yiming Li
 *
 * \brief The linked list to store the snowflake
 */

#pragma once
#include "Snowflake.h"
#include <memory>

/**
 * \brief The linked calss to store the snow flakes
 */
class CLinkedList
{
public:
	CLinkedList();
	~CLinkedList();
	void Insert(std::shared_ptr<CSnowflake> flake);
	std::shared_ptr<CSnowflake> Popfront();
	void Remove(std::shared_ptr<CSnowflake> temp);
	/**
	* \brief Get the head of the linked list
	* \returns the header pointer
	*/
	std::shared_ptr<CSnowflake> GetHead(){ return head; }
	/**
	* \brief Get the tail of the linked list
	* \returns the tail pointer
	*/
	std::shared_ptr<CSnowflake> GetTail(){ return tail; }

private:
	///The head of the linked list
	std::shared_ptr<CSnowflake> head = nullptr;
	///The tail of the linked list
	std::shared_ptr<CSnowflake> tail = nullptr;
	///The Size of the linked list
	int size = 0;
};

