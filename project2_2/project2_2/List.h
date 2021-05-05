#pragma once

#ifndef LIST_H
#define LIST_H

#include <algorithm>
using namespace std;

template <typename Object>
class List {
private:
    // The basic singly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node {
        Object  data;
        Node* next;
        Node* theList;

        Node(Node* h = nullptr, const Object& d = Object{ }, Node* n = nullptr)
            : data{ d }, theList{ h }, next{ n } { }

        Node(Node* h, Object&& d, Node* n = nullptr)
            : data{ std::move(d) }, theList{ h }, next{ n } { }
    };

public:
    class const_iterator {
    public:

        // Public constructor for const_iterator.
        const_iterator() : current{ nullptr } {}

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object& operator* () const {
            return retrieve();
        }

        const_iterator& operator++ () {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- () {
            const_iterator* tmp = this->theList;
            while (tmp->next != *this) {
                tmp++;
            }
            return *tmp;
        }

        const_iterator& operator-- (int) {
            const_iterator old = this->theList;
            --(*this);
            return old;
        }

        const_iterator operator+ (int rhs) {
            int x = rhs;
            while (x > 0) {
                ++(*this);
                --x;
            }
            return *this;
        }

        const_iterator operator- (int rhs) {
            int x = rhs;
            while (x > 0) {
                --(*this);
                x--;
            }
            return *this;
        }

        bool operator== (const const_iterator& rhs) const {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node* current = Node(Node* head);

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object& retrieve() const {
            return current->data;
        }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator(Node* p) : current{ p } {}

        friend class List<Object>;
    };

    class iterator : public const_iterator {
    public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator() {}

        Object& operator* () {
            return const_iterator::retrieve();
        }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object& operator* () const {
            return const_iterator::operator*();
        }

        iterator& operator++ () {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ (int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- () {
            iterator* tmp = this->theList;
            while (tmp->next != *this) {
                tmp++;
            }
            return *tmp;
        }

        iterator operator+ (int rhs) {
            int x = rhs;
            while (x > 0) {
                ++(*this);
                x--;
            }
            return *this;
        }
        
        iterator operator- (int rhs) {
            int x = rhs;
            while (x > 0) {
                (this)--;
                x--;
            }
            return *this;
        }


    protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator(Node* p) : const_iterator{ p } {}

        friend class List<Object>;
    };

public:
    List() {
        init();
    }

    ~List() {
        clear();
        delete head;
        delete tail;
    }

    List( List& rhs) {
        init();
        for (auto& x : rhs)
            push_back(x);
    }

    List& operator= ( List& rhs) {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    List(List&& rhs) noexcept : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail } {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    List& operator= (List&& rhs) noexcept {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);

        return *this;
    }

    // Return iterator representing beginning of list.
    // Mutator version is first, then accessor version.
    iterator begin() {
        return iterator(head);
    }

    const_iterator begin() const {
        return const_iterator(head);
    }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end() {
        return iterator(tail);
    }

    const_iterator end() const {
        return const_iterator(tail);
    }

    // Return number of elements currently in the list.
    int size() const {
        return theSize;
    }

    // Return true if the list is empty, false otherwise.
    bool empty() const {
        return size() == 0;
    }

    void clear() {
        while (!empty())
            pop_front();
    }

    // front, back, push_front, push_back, pop_front, and pop_back
    // are the basic double-ended queue operations.
    Object& front() {
        return *begin();
    }

    const Object& front() const {
        return *begin();
    }

    Object& back() {
        return *(--end());
    }

    const Object& back() const {
        return *(--end());
    }

    void push_front(Object& x) {
        insert(begin(), x);
    }

    void push_back(Object& x) {
        insert(end(), x);
    }

    void push_front(Object&& x) {
        insert(begin(), std::move(x));
    }

    void push_back(Object&& x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(end());
    }

    // Insert x before itr.
    iterator insert(iterator itr, const Object& x) {
        Node* p = itr.current;
        --p;
        ++theSize;
        return iterator(p->next = new Node{ p->theList, x, p });
    }

    // Insert x before itr.
    iterator insert(iterator itr, Object&& x) {
        Node* p = itr.current;
        --p;
        ++theSize;
        return iterator(p->next = new Node{ p->theList, std::move(x), p });
    }

    // Erase item at itr.
    iterator erase(iterator itr) {
        Node* p = itr.current;
        --p;
        iterator retVal(p->next);
        Node* q = p->next;
        p->next = q->next;
        delete q;
        theSize--;

        return retVal;
    }

    iterator erase(iterator from, iterator to) {
        for (iterator itr = from; itr != to; )
            itr = erase(itr);

        return to;
    }

    bool contains(Object& rhs) {
        for (iterator itr = begin(); itr != end(); ++itr) {
            if (*itr == rhs) {
                return true;
            }
        }
        return false;
    }

    void print(iterator to, iterator from) {
        for (iterator itr = to; itr != from; ++itr) {
            cout << *itr << " ";
        }
        cout << endl;
    }

private:
    int   theSize;
    Node* head;
    Node* tail;

    void init() {
        theSize = 0;
        head = new Node();
        tail = new Node(head);
        head->next = tail;
    }
};

#endif
