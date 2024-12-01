#pragma once 

#include <iostream>
using namespace std;
template<typename T>
class TList {
protected:
    struct Node {
        Node* next;
        T value;
        Node(T value, Node* next) :next(next), value(value) {}
    };
    size_t sz = 0;
    Node* first = nullptr;
public:
    class iterator {
    public:
        Node* cr;
        iterator(Node* nodePtr) : cr(nodePtr) {}

        iterator& operator++() {
            if (cr != nullptr) {
                cr = cr->next;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        T& operator*() {
            if (cr == nullptr) {
                throw "incorectable operation";
            }
            return cr->value;
        }

        const T& operator*() const {
            if (cr == nullptr) {
                throw "incorectable operation";
            }
            return cr->value;
        }

        bool operator!=(const iterator& other) const { return cr != other.cr; }

        bool operator==(const iterator& other) const { return cr == other.cr; }

    };
    TList(int n = 0) {
        if (n < 0) throw "incorrect operation";
        sz = n;
        for (int i = 0; i < n; ++i) {
            first = new Node(0, first);
        }
    }

    TList(const TList& other) {
        if (!other.empty()) {
            sz = other.sz;
            Node* curr1 = other.first;
            Node* curr2 = new Node(curr1->value, nullptr);
            first = curr2;
            while (!curr1) {
                Node* next1 = curr1->next;
                if (!next1) break;
                curr2->next = new Node(next1->value, nullptr);
                curr2 = curr2->next;
                curr1 = curr1->next;
            }
        }
    }

    TList& operator=(const TList& other) {
        if (this != &other) {
            (*this).clear();
            sz = other.sz;
            if (other.sz != 0) {
                Node* curr1 = other.first;
                Node* curr2 = new Node(curr1->value, nullptr);
                first = curr2;
                while (!curr1) {
                    Node* next1 = curr1->next;
                    if (!next1) break;
                    curr2->next = new Node(next1->value, nullptr);
                    curr2 = curr2->next;
                    curr1 = curr1->next;
                }
            }
        }
        return *this;
    }

    TList(TList&& other) noexcept {
        first = other.first;
        other.first = nullptr;
        sz = other.sz;
        other.sz = 0;
    }

    TList& operator=(TList&& other) noexcept {
        sz = other.sz;
        first = other.first;
        other.sz = 0;
        other.first = nullptr;
        return *this;
    }

    bool empty() const { return (sz == 0); }

    void print() const {
        Node* curr = first;
        while (curr) {
            cout << curr->value << " ";
            curr = curr->next;
        }
    }

    size_t size() const { return sz; }

    void clear() {
        while (first != nullptr) {
            Node* curr = first;
            first = first->next;
            delete curr;
        }
        sz = 0;
    }

    bool operator==(const TList& other) const {
        bool flag = true;
        if (this->sz != other.sz) {
            flag = false;
            return flag;
        }
        Node* l1 = first;
        Node* l2 = other.first;
        for (int i = 0; i < sz; i++) {
            if (curr1 != curr2) flag = false;
            if !(flag) return flag;
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return flag;
    }

    bool operator!=(const TList& other) const {
        return !((*this) == other);
    }

    iterator begin() const { return iterator(this->first); }

    iterator end() const { return iterator(nullptr); }

    T& at(int index) {
        if (index < 0 || index >= sz) {
            throw "incorectable operation";
        }
        Node* curr = first;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->value;
    }

    const T& at(int index) const {
        if (index < 0 || index >= sz) {
            throw "incorectable operation";
        }
        Node* curr = first;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->value;
    }

    T& operator[](int index) { return at(index); }

    const T& operator[](int index) const { return at(index); }

    T& at(iterator k) { return (*k); }

    T at(iterator k) const { return (*k); }

    T& operator[](iterator k) { return (*k); }

    Node* insert_front(T v) {
        sz++;
        first = new Node(v, first);
        return first;
    }

    Node* insert_after(T data, Node* prev) {
        if (!prev) {
            throw "incorectable operation";
        }
        sz++;
        Node* tmp = new Node(data, prev->next);
        prev->next = tmp;
        return tmp;
    }

    Node* erase_front() {
        if (first) {
            sz--;
            Node* tmp = first->next;
            delete first;
            first = tmp;
        }
        return first;
    }

    Node* erase_after(Node* prev) {
        if (!prev->next) {
            throw "incorectable operation";
        }
        Node* tmp = prev->next;
        if (tmp) {
            prev->next = tmp->next;
            delete tmp;
            sz--;
        }
        return prev->next;
    }

    ~TList() {
        clear();
    }

    friend istream& operator>>(istream& istr, const TList& l) {
        Node* curr = l.first;
        while (curr) {
            istr >> curr->value;
            curr = curr->next;
        }
        return istr;
    }

    friend ostream& operator<<(ostream& ostr, const TList& l) {
        Node* curr = l.first;
        while (curr != nullptr) {
            ostr << curr->value << ' ';
            curr = curr->next;
        }
        std::cout << "\n";
        return ostr;
    }

    //задача_3
    /*T find_kth_elem_from_end(Node* first, int k) {
        if (first == nullptr || k <= 0) { throw "incorectable operation"; }
        Node* main_Ptr = first;
        Node* k_ptr = first;
        for (int i = 0; i < k; ++i) {
            if (main_Ptr == nullptr) { throw "incorectable operation"; }
            main_Ptr = main_Ptr->next;
        }
        while (main_Ptr != nullptr) {
            main_Ptr = main_Ptr->next;
            k_ptr = k_ptr->next;
        }
        return k_ptr->value;
    }*/
};



