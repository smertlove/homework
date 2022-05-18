#include <iterator>

// wsl gcc test.hpp -std=c++17 -g -fdiagnostics-color -O0 -Wall -Wextra -Werror -I. 

namespace task {


template<class T>
class list {

protected:  // NOTE (Kirill Soloshenko) changed private to protected 
            // in order to make further inheritance just a lil' bit easier :)
    template<class U>
    class list_node {
        public:
            class list_node *next;
            class list_node *prev;
            U data;

            list_node(U val=U(), list_node *next_node=nullptr, list_node *prev_node=nullptr) {
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
        reference operator*() const { return current; }
        pointer operator->() const { return current; }
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(iterator other) const { return current == other->current}
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
        reference operator*() const { return current; }
        pointer operator->() const { return current; }
        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(const_iterator other) const { return current == other->current}
        bool operator!=(const_iterator other) const { return (*this) != other; }
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
};

template<class T>
list<T>::list() {
    length = 0;
    head = nullptr;
    tail = nullptr;
}

template<class T>
list<T>::list(size_t count, const T& value) {
    list();
    for (size_t i = 0; i < count; i++) {
        push_back(value);
    }
}

template<class T>
list<T>::list(size_t count) {
    list(count, T());
}

template<class T>
list<T>::~list() {
    clear();
}

template<class T>
void list<T>::push_back(const T& value) {
    if (head == nullptr) {
        head = new list_node<T>(value);
        tail = head;
    } else {
        tail->next = new list_node<T>(value, nullptr, tail);
        tail = tail->next;
    }
}

template<class T>
void list<T>::pop_back() {
    if (tail == nullptr) {
        return;
    } else {
        tail = tail->prev;
    }
}

template<class T>
list<T>::list(const list& other) {
    *this = other;
};

template<class T>
list<T>& list<T>::operator=(const list<T>& other) {
    *this = other;
}

template<class T>
T& list<T>::front() { return head; };

template<class T>
const T& list<T>::front() const { return head; };

template<class T>
T& list<T>::back() { return tail; };

template<class T>
const T& list<T>::back() const { return tail; };

template<class T>
typename list<T>::iterator list<T>::begin() const { return iterator(head); }

template<class T>
typename list<T>::iterator list<T>::end() const {return iterator(tail);}

template<class T>
typename list<T>::const_iterator list<T>::cbegin() const { return const_iterator(head); }

template<class T>
typename list<T>::const_iterator list<T>::cend() const { return const_iterator(end); }

template<class T>
typename list<T>::reverse_iterator list<T>::rbegin() const { return reverse_iterator(head); }

template<class T>
typename list<T>::reverse_iterator list<T>::rend() const { return reverse_iterator(end); }

template<class T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const { return const_reverse_iterator(head); }

template<class T>
typename list<T>::const_reverse_iterator list<T>::crend() const { return const_reverse_iterator(end); }

template<class T>
bool list<T>::empty() const { return length == 0; }

template<class T>
size_t list<T>::size() const { return length; }

template<class T>
size_t list<T>::max_size() const { return 1000000; };

template<class T>
void list<T>::clear() {
    while (head != nullptr) {
        pop_back();
    }
    length = 0;
}

template<class T>
void list<T>::push_front(const T& value) {
    if (head == nullptr) {
        head = new list_node<T>(value);
        tail = head;
    } else {
        head->prev = new list_node<T>(value, head);
        head = head->prev;
    }
}

template<class T>
void list<T>::pop_front() {
    if (head == nullptr) {
        return;
    } else {
        head = head->next;
    }
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const T& value) {
    const_iterator pos_next = pos + 1;
    list_node<T> new_node = new list_node<T>(value);
    pos.current->next = new_node;
    pos_next.current->prev = new_node;
    pos++;
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_t count, const T& value) {
    const_iterator pos_next = pos + 1;
    for (size_t i = 0; i < count; i++) {
        pos = insert(pos, value);
    }
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator pos) {
    pos.current->prev->next = pos.current->next;
    pos.current->next->prev = pos.current->prev;
    pos--;
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
    first.current->prev->next = last.current;
    last.current->prev = first.current->prev;
    first--;
    return first;
}

template<class T>
void list<T>::resize(size_t count) {
    while (length != count) {
        if (length > count) {
            pop_back();
        } else {
            push_back(T());
        }
    }
}

template<class T>
void list<T>::swap(list& other) {
    list<T> buf = *this;
    this = other;
    other = buf;
}

template<class T>
void list<T>::merge(list<T>& other) {return;};
template<class T>
void list<T>::splice(const_iterator pos, list& other){return;};

template<class T>
void list<T>::remove(const T& value){return;};
template<class T>
void list<T>::reverse(){return;};
template<class T>
void list<T>::unique(){return;};
template<class T>
void list<T>::sort(){return;};

}  // namespace task
