/*
 * LinkedList.h
 *
 *  Created on: Apr 20, 2017
 *      Author: Mostafa Mahmoud
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//Node Class Declaration

template <class Type>
class Node {

    //Member variables
protected:
    Type data;
    Node *prev;
    Node *next;

    //Constructors and Destructor
    explicit Node();
    explicit Node(const Type &passedData);
    ~Node();

    //Methods
    Type getData() const;
    void setData(Type d);
    Node* getNext() const;
    void setNext(Type d);

    template <class>
    friend class LinkedList;

};


////////////////////////////////////////////////////////////////////////////

//LinkedList Class Declaration

template <class Type>
class LinkedList {

private:
    //Member variables
    Node<Type> *head;
    Node<Type> *tail;
    unsigned long theSize;

public:
    //Constructors and Destructor
    explicit LinkedList();
    explicit LinkedList(const Type &passedData);
    ~LinkedList();

    //Methods
    void push_back(const Type &passedData);
    void push_front(const Type &passedData);
    void pop_back();
    void pop_front();
    void insertAt(const Type &passedData, unsigned long pos);
    void removeAt(unsigned long pos);
    void removeFirstOccurenceOf(const Type &passedData);
    void removeLastOccurenceOf(const Type &passedData);
    Type& getAt(unsigned long idx);
    Node<Type>* find(const Type &passedData);
    void clear();
    void display() const;
    Node<Type>* getHead() const;
    Node<Type>* getTail() const;
    Type front() const;
    Type back() const;
    bool isEmpty() const;
    unsigned long size() const;
    void sortList();
    void sortList( bool (*compare)(const Type&, const Type&) );

    void reverse();

private:
    void print(Node<Type>* ptr) const;

};




////////////////////////////////////////////////////////////////////////////////////

//Implementation of Node Class

//Node Class Constructors and Destructor

template <class Type>
Node<Type>::Node()
        : data{0}, prev{NULL}, next{NULL} {}

template <class Type>
Node<Type>::Node(const Type &passedData)
        : data {passedData}, prev{NULL}, next{NULL} {}

template <class Type>
Node<Type>::~Node() {}	//No implementation needed since it deleting nodes was taken care of in LinkedList class


//Node Class Member Methods

template <class Type>
Type Node<Type>::getData() const {
    return this->data;
}

template <class Type>
void Node<Type>::setData(Type d) {
    this->data = d;
}

template <class Type>
Node<Type>* Node<Type>::getNext() const {
    return this->next;
}

template <class Type>
void Node<Type>::setNext(Type d) {
    next->data = d;
}



/////////////////////////////////////////////////////////////////////////////////

//Implementation of LinkedList Class

//LinkedList Class Constructors and Destructors

template <class Type>
LinkedList<Type>::LinkedList()
        : head{NULL}, tail{NULL} , theSize{0} {}

template <class Type>
LinkedList<Type>::LinkedList(const Type &passedData)
        : head{ new Node<Type>(passedData) }, tail {head}, theSize{1} {}

template <class Type>
LinkedList<Type>::~LinkedList() {
    clear();
}


//LinkedList Class Methods

template <class Type>
void LinkedList<Type>::push_back(const Type &passedData) {

    if (isEmpty()) {
        head = new Node<Type>(passedData);
        tail = head;
        theSize++;
    }
    else {
        Node<Type> *tmp = tail;
        tail = new Node<Type>(passedData);
        tmp->next = tail;
        tail->prev = tmp;
        theSize++;
    }

}

template <class Type>
void LinkedList<Type>::push_front(const Type &passedData) {

    if (isEmpty()) {
        head = new Node<Type>(passedData);
        tail = head;
        theSize++;
    }
    else {
        Node<Type> *tmp = head;
        head = new Node<Type>(passedData);
        tmp->prev = head;
        head->next = tmp;
        theSize++;
    }

}

template <class Type>
void LinkedList<Type>::pop_back() {

    if (this->size() == 1) {
        Node<Type> *tmp = tail;
        head = NULL;
        tail = NULL;
        delete tmp;
        theSize--;
    }
    else {
        Node<Type> *tmp = tail;
        tail = tail->prev;
        tail->next = NULL;
        delete tmp;
        theSize--;
    }

}

template <class Type>
void LinkedList<Type>::pop_front() {

    if (this->size() == 1) {
        Node<Type> *tmp = head;
        head = NULL;
        tail = NULL;
        delete tmp;
        theSize--;
    }
    else {
        Node<Type> *tmp = head;
        head = head->next;
        head->prev = NULL;
        delete tmp;
        theSize--;
    }

}

template <class Type>
void LinkedList<Type>::display() const {	//The interface to be used by external user

    cout << "[ ";
    print(this->head);
    cout << " ]" << endl;

}

template <class Type>
void LinkedList<Type>::print(Node<Type>* ptr) const {

    if (ptr == NULL)
        return;
    else {
        cout << ptr->data;
        if (ptr->next != NULL)
            cout << ", ";
        print(ptr->next);
    }

}

template <class Type>
void LinkedList<Type>::insertAt(const Type &passedData, unsigned long pos) {

    if (pos == 0)
        push_front(passedData);
    else if (pos == this->size())
        push_back(passedData);
    else if (pos < 0 || pos > this->size()) {
        //throw out of bounds exception
    }
    else if (pos < this->size() / 2) {	//traverse from head
        Node<Type> *tmpNode = new Node<Type>(passedData);
        Node<Type> *ptr = head;
        while (pos--) {
            ptr = ptr->next;
        }
        tmpNode->prev = ptr->prev;
        tmpNode->next = ptr;
        ptr->prev -> next = tmpNode;
        ptr->prev = tmpNode;
        theSize++;
    }
    else {	//traverse from tail
        Node<Type> *tmpNode = new Node<Type>(passedData);
        Node<Type> *ptr = tail;
        pos = this->size() - pos - 1;
        while (pos--) {
            ptr = ptr->prev;
        }
        tmpNode->prev = ptr->prev;
        tmpNode->next = ptr;
        ptr->prev->next = tmpNode;
        ptr->prev = tmpNode;
        theSize++;
    }

}

template <class Type>
void LinkedList<Type>::removeAt(unsigned long pos) {

    if (pos == 0)
        pop_front();
    else if (pos == this->size() - 1)
        pop_back();
    else if (pos < 0 || pos > this->size()) {
        //throw out of bounds exception
    }
    else if (pos < this->size() / 2) {	//traverse from head
        Node<Type> *ptr = head;
        while (pos--) {
            ptr = ptr->next;
        }
        ptr->prev -> next = ptr->next;
        ptr->next -> prev = ptr->prev;
        delete ptr;
        theSize--;
    }
    else {	//traverse from tail
        Node<Type> *ptr = tail;
        pos = this->size() - pos - 1;
        while (pos--) {
            ptr = ptr->prev;
        }
        ptr->prev -> next = ptr->next;
        ptr->next -> prev = ptr->prev;
        delete ptr;
        theSize--;
    }

}

template <class Type>
void LinkedList<Type>::removeFirstOccurenceOf(const Type &passedData) {

    unsigned long idx = 0;
    Node<Type> *ptr = head;
    while (ptr->data != passedData && ptr->next != NULL) {
        ptr = ptr->next;
        idx++;
    }

    removeAt(idx);	//it is neater this way, although it increases execution time and loops again through list

}

template <class Type>
void LinkedList<Type>::removeLastOccurenceOf(const Type &passedData) {

    unsigned long idx = this->size() - 1;
    Node<Type> *ptr = tail;
    while (ptr->data != passedData && ptr->prev != NULL) {
        ptr = ptr->prev;
        idx--;
    }

    removeAt(idx);	//it is neater this way, although it increases execution time and loops again through list
}

template <class Type>
Type& LinkedList<Type>::getAt(unsigned long idx) {

    if (idx == 0)
        return head->data;
    else if (idx == this->size() - 1)
        return tail->data;
    else if (idx < 0 || idx > this->size()) {
        //throw out of bounds exception
    }
    else if (idx < this->size() / 2) {	//traverse from head
        Node<Type> *ptr = head;
        while (idx--) {
            ptr = ptr->next;
        }
        return ptr->data;
    }
    else {	//traverse from tail
        Node<Type> *ptr = tail;
        idx = this->size() - idx - 1;
        while (idx--) {
            ptr = ptr->prev;
        }
        return ptr->data;
    }

}

template <class Type>
Node<Type>* LinkedList<Type>::getHead() const {
    return head;
}

template <class Type>
Node<Type>* LinkedList<Type>::getTail() const {
    return tail;
}

template <class Type>
Type LinkedList<Type>::front() const {
    return head->data;
}

template <class Type>
Type LinkedList<Type>::back() const {
    return tail->data;
}

template <class Type>
bool LinkedList<Type>::isEmpty() const {
    return theSize == 0? true: false;
}

template <class Type>
unsigned long LinkedList<Type>::size() const {
    return theSize;
}

template <class Type>
Node<Type>* LinkedList<Type>::find(const Type &passedData) {

    Node<Type> *ptr = head;
    while (ptr->next != NULL) {
        if (ptr->data == passedData)
            return ptr;

        ptr = ptr->next;
    }

    return NULL;

}

template <class Type>
void LinkedList<Type>::clear() {

    while(!isEmpty())
        pop_front();

}

template <class Type>
void LinkedList<Type>::sortList() {

    vector<Type> tmp;
    unsigned long size = this->size();
    tmp.resize(size);

    Node<Type> *ptr = head;
    for (unsigned long i = 0; i < size; ++i) {	//copy linked list elements into a vector to be sorted
        tmp[i] = ptr->data;
        ptr = ptr->next;
    }

    sort(tmp.begin(), tmp.end());	//using C++ built-in sort() function

    ptr = head;
    for (unsigned long i = 0; i < size; ++i) {	//return elements after sorting from vector into linked list
        ptr->data = tmp[i];
        ptr = ptr->next;
    }

}

template <class Type>
void LinkedList<Type>::sortList( bool (*compare)(const Type&, const Type&) ) {

    vector<Type> tmp;
    unsigned long size = this->size();
    tmp.resize(size);

    Node<Type> *ptr = head;
    for (unsigned long i = 0; i < size; ++i) {	//copy linked list elements into a vector to be sorted
        tmp[i] = ptr->data;
        ptr = ptr->next;
    }

    sort(tmp.begin(), tmp.end(), compare);	//using C++ built-in sort() function

    ptr = head;
    for (unsigned long i = 0; i < size; ++i) {	//return elements after sorting from vector into linked list
        ptr->data = tmp[i];
        ptr = ptr->next;
    }

}


#endif /* LINKEDLIST_H_ */
