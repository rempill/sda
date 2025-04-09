#pragma once
#include <functional>
#include <iostream>
#include <iostream>
template<typename T> class Iterator;

template <typename T>
class LinkedList {
    friend class Iterator<T>;
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& val): data(val), next(nullptr) {}
    };
    Node *head;
    Node *tail;
    int size;
public:
    using iterator = Iterator<T>;
    LinkedList():head(nullptr),tail(nullptr), size(0) {}
    ~LinkedList() {
        while (head) {
            pop_front();
        }
    }
    LinkedList(const LinkedList & other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head; // Start from the head of the original list
        while (current) {
            this->push_back(current->data); // Copy each node's data
            current = current->next;
        }
    }
    LinkedList& operator=(const LinkedList & other) {
        if (this != &other) { // BROOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
            while (head) {
                pop_front();
            }
            Node* current = other.head;
            while (current) {
                this->push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    void push_back(const T&);
    void push_front(const T&);
    void pop_back();
    void pop_front();
    void erase(iterator pos);
    [[nodiscard]] int getSize() const {
        return size;
    }
    [[nodiscard]] bool isEmpty() const{
        return size == 0;
    }
    iterator begin() const {
        return iterator(head);
    }
    static iterator end() {
        return iterator(nullptr);
    }
    Node* mergeSort(Node* head, const std::function<bool(const T&, const T&)>& comparator);
    Node* merge(Node*,Node*,const std::function<bool(const T&, const T&)>& comparator);
    Node* getMiddle(Node*);
    void  insert(const T& val, iterator pos);
    void sort(const std::function<bool(const T&, const T&)>& comparator);
};

template <typename T> class Iterator {
    friend class LinkedList<T>;
public:
    typename LinkedList<T>::Node* current;
    explicit Iterator(typename LinkedList<T>::Node* node): current(node) {}
    T& operator*()const {
        return current->data;
    }
    T* operator->()const {
        return &current->data;
    }
    Iterator operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }
    Iterator operator++(int) {
        Iterator temp = *this;
        ++(*this);
        return temp;
    }
    bool operator==(const Iterator& other) const {
        return current == other.current;
    }
    bool operator!=(const Iterator& other) const {
        return current != other.current;
    }
};

template<typename T>
void LinkedList<T>::push_back(const T& val) {
    Node* newNode= new Node(val);
    if (!head) {
        head=tail=newNode;
    }
    else {
        tail->next=newNode;
        tail=newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::push_front(const T& val) {
    Node* newNode= new Node(val);
    if (!head) {
        head=tail=newNode;
    }
    else {
        newNode->next=head;
        head=newNode;
    }
    ++size;
}

template<typename T>
void LinkedList<T>::pop_back() {
    if (!head) {
        return;
    }
    if (head == tail) {
        delete head;
        head = tail = nullptr;
    } else {
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
    }
    --size;
}

template<typename T>
void LinkedList<T>::pop_front() {
    if (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
    }
    if (!head) {
        tail = nullptr;
    }
}

template<typename T>
void LinkedList<T>::erase(iterator pos) {
    if (!head || !pos.current) {
        return;
    }
    if (pos.current==head) {
        pop_front();
        return;
    }
    Node* prev=head;
    while (prev && prev->next!=pos.current) {
        prev=prev->next;
    }
    if (prev && prev->next==pos.current) {
        Node* todel=pos.current;
        prev->next=todel->next;
        if (todel==tail) {
            tail=prev;
        }
        delete todel;
        --size;
    }
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::mergeSort(Node* head, const std::function<bool(const T&, const T&)>& comparator) {
    if (!head || !head->next) {
        return head; // Base case: 0 or 1 element
    }

    // Split the list into two halves
    Node* middle = getMiddle(head);
    Node* nextToMiddle = middle->next;
    middle->next = nullptr;

    // Recursively sort both halves
    Node* left = mergeSort(head, comparator);
    Node* right = mergeSort(nextToMiddle, comparator);

    // Merge the sorted halves
    return merge(left, right, comparator);
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::merge(Node* left, Node* right, const std::function<bool(const T&, const T&)>& comparator) {
    if (!left) return right;
    if (!right) return left;

    Node* result = nullptr;

    // Compare and merge
    if (comparator(left->data, right->data)) {
        result = left;
        result->next = merge(left->next, right, comparator);
    } else {
        result = right;
        result->next = merge(left, right->next, comparator);
    }
    return result;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::getMiddle(Node* head) {
    if (!head) return head;

    Node* slow = head;
    Node* fast = head->next;

    // Move fast by two and slow by one
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

template <typename T>
void LinkedList<T>::sort(const std::function<bool(const T&, const T&)>& comparator) {
    head = mergeSort(head, comparator);

    // Update tail after sorting
    tail = head;
    while (tail && tail->next) {
        tail = tail->next;
    }
}

template<typename T>
void LinkedList<T>::insert(const T& val, iterator pos) {
    if (!head || !pos.current) {
        return;
    }
    Node* newNode = new Node(val);
    if (pos.current == head) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prev = head;
        while (prev && prev->next != pos.current) {
            prev = prev->next;
        }
        if (prev) {
            newNode->next = prev->next;
            prev->next = newNode;
        }
    }
    ++size;
}