//
//  DoubleyLinkedList.h
//  DoublelyLinkedList
//
//  Created by Hayden Crabb on 10/13/18.
//  Copyright © 2018 Coconut Productions. All rights reserved.
//


#pragma once
#ifndef DoubleyLinkedList_h
#define DoubleyLinkedList_h
template <class t> class DLLNode {
public:
    t info;
    DLLNode<t> * next = nullptr;
    DLLNode<t> * previous = nullptr;
};

template <class type> class DoubleyLinkedList {
private:
    DLLNode<type> * tail;
    DLLNode<type> * head;
    int count;
public:
    DoubleyLinkedList();
    ~DoubleyLinkedList();
    void append(type);
    //void deleteNode(int);
    int size();
    void getNextNode(DLLNode<type> * &);
};
#endif /* DoubleyLinkedList_h */
