#pragma once
#ifndef DoubleyLinkedList_cpp
#define DoubleyLinkedList_cpp

#include "DoubleyLinkedList.h"

template <class type>
void DoubleyLinkedList<type>::append(type newNode)
{
    DLLNode<type>* nextNode = new DLLNode<type>;
    nextNode->info = newNode;
    if (head == nullptr)
    {
        head = nextNode;
        tail = nextNode;
    }
    else {
        tail->next = nextNode;
        nextNode->previous = tail;
        tail = nextNode;
    }
    count++;
}
template <class type>
void DoubleyLinkedList<type>::getNextNode(DLLNode<type>*& currentNode) {
    if (currentNode == nullptr)
    {
        currentNode = head;
    }
    else {
        currentNode = currentNode->next;
    }
}
template <class type> DoubleyLinkedList<type>::DoubleyLinkedList()
{
    tail = nullptr;
    head = nullptr;
    count = 0;
}
template <class type> DoubleyLinkedList<type>::~DoubleyLinkedList()
{
    if (count != 0)
    {
        DLLNode<type>* currentNode = nullptr;
        getNextNode(currentNode);
        while (currentNode != nullptr) {
            if (currentNode != head)
            {
                delete currentNode->previous;
            }
            if (currentNode == tail)
            {
                delete currentNode;
            }
            getNextNode(currentNode);
        }
    }
}
template <class type> int DoubleyLinkedList<type>::size()
{
    return count;
}

#endif
