#pragma once  // NOLINT
#include <iterator>


namespace task {


template<class T>
class list {

protected:  // NOTE (Kirill Soloshenko) changed private to protected 
            // in order to make further inheritance just a lil' bit easier :)
    template <typename T>
    class list_node {
        public:
            class list_node *next;
            class list_node *prev;
            T data;

            list_node(T val=T(), list_node *next_node=nullptr, list_node *prev_node=nullptr) {
                data = val;
                next = next_node;
                prev = prev_node;
            }
        };

    list_node<T> *head;
    list_node<T> *tail;
    size_t     length;

public:
    class iterator {

    private:
        list_node<T> *current;

    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() { current = nullptr; }
        iterator(const iterator &other) { *this = other; }
        iterator& operator=(const iterator &other) { return iterator(other); }

        iterator& operator++() {
            current = current->next;
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            current = current->next;
            return old;
        }
        reference operator*() const { return &current; }
        pointer operator->() const { return *current; }
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(iterator other) const { return current == other->current ? true : false; }
        bool operator!=(iterator other) const { return !((*this) == other); }

    };

    class const_iterator {
    private:
        list_node<T> *current;

    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator() { current = nullptr; }
        const_iterator(const const_iterator &other) { *this = other; }
        const_iterator& operator=(const const_iterator &other) { return const_iterator(other); }

        const_iterator& operator++() {
            current = current->next;
            return *this;
        }
        const_iterator operator++(int) {
            iterator old = *this;
            current = current->next;
            return old;
        }
        reference operator*() const { return &current; }
        pointer operator->() const { return *current; }
        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(const_iterator other) const { return current == other->current ? true : false; }
        bool operator!=(const_iterator other) const { return !((*this) == other); }
    };

    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    list();
    list(size_t count, const T& value);
    explicit list(size_t count);
    ~list();

    list(const list& other);
    list& operator=(const list& other);

    T& front();
    const T& front() const;

    T& back();
    const T& back() const;


    iterator begin() const;
    iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin() const;
    reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;


    bool empty() const;
    size_t size() const;
    size_t max_size() const;
    void clear();

    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);


    void push_back(const T& value);
    void pop_back();

    void push_front(const T& value);
    void pop_front();

    void resize(size_t count);
    void swap(list& other);


    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();

    // Your code goes here?..

};

/*********** list ***********/

list<T>::list() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

list<T>::list(size_t count, const T& value) {
    list();
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}
explicit list<T>::list(size_t count) {
    list(count, T())
}
list<T>::~list() {
    while (head != nullptr) {
        pop_back();
    }
}

list<T>::list(const list& other);
list<T>::list& operator=(const list& other);

T& list<T>::front() { return head; };
const T& list<T>::front() const { return head; };

T& list<T>::back() { return tail; };
const T& list<T>::back() const { return tail; };


iterator list<T>::begin() const { return iterator(head); }
iterator list<T>::end() const {return iterator(tail);}

const_iterator list<T>::cbegin() const { return const_iterator(head); }
const_iterator list<T>::cend() const { return const_iterator(end); }

reverse_iterator list<T>::rbegin() const { return reverse_iterator(head); }
reverse_iterator list<T>::rend() const { return reverse_iterator(end); }

const_reverse_iterator list<T>::crbegin() const { return const_reverse_iterator(head); }
const_reverse_iterator list<T>::crend() const { return const_reverse_iterator(end); }


bool list<T>::empty() const { return size == 0; }
size_t list<T>::size() const { return size; }
size_t list<T>::max_size() const { return 1000000; };
void list<T>::clear();

iterator list<T>::insert(const_iterator pos, const T& value) {
    list_node *new_node = new list_node(value);
    pos->current
}
iterator list<T>::insert(const_iterator pos, size_t count, const T& value);

iterator list<T>::erase(const_iterator pos);
iterator list<T>::erase(const_iterator first, const_iterator last);


list<T>::push_back(const T& value) {
    if (head == nullptr) {
        head = new list_node(data);
        tail = head;
    } else {
        tail->next = new list_node(data, nullptr, tail);
        tail = tail->next;
    }
}

void list<T>::pop_back() {
    if (tail == nullptr) {
        return;
    } else {
        tail = tail->prev;
    }
}

list<T>::push_front(const T& value) {
    if (head == nullptr) {
        head = new list_node(data);
        tail = head;
    } else {
        head->prev = new list_node(data, head);
        head = head->prev;
    }
}

void list<T>::pop_front() {
    if (head == nullptr) {
        return;
    } else {
        head = head->next;
    }
}

void resize(size_t count){return;};
void swap(list& other){return;};


void merge(list& other) {return;};
void splice(const_iterator pos, list& other){return;};
void remove(const T& value){return;};
void reverse(){return;};
void unique(){return;};
void sort(){return;};



}  // namespace task







// list<T>::push_front(const T& value) {
//     if (head == nullptr) {
//         head = new list_node(data);
//         tail = head;
//     } else {
//         head->prev = new list_node(data, head);
//         head = head->prev;
//     }
// }

// list<T>::push_front() {
//     push_front(T());
// }

// T& list<T>::front() {
//     return *head;
// }



// const T& front() const {
//     return *head;
// }

// T& back() {
//     return *tail;
// }

// const T& back() const {
//     return *tail;
// }

// list<T>::list(size_t count, const T& value) {
//     list();
//     size = count;
//     for (size_t i = 0; i < count; i++) {
//         push_back(value);
//     }
// }
// list<T>::list(size_t count) {
//     list(count, T())
// }
// list<T>::~list() = default;

// list<T>::list(const list& other) {
//     this->size = other.size;
//     this->head = other.head;
//     this->tail = other.tail;
// }
// list& operator=(const list& other) {
//     return list<T>(other);
// }