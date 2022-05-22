#include <iterator>


namespace task {


template<class T>
class list {

protected:  // NOTE (Kirill Soloshenko) changed private to protected 
            // in order to make further inheritance just a lil' bit easier :)
    template<class U>
    class list_node {
        public:
            U data;
            class list_node *next;
            class list_node *prev;

            list_node(U& val=U(), list_node *next_node=nullptr, list_node *prev_node=nullptr) : data(val), next(next_node), prev(prev_node) { }
            ~list_node() = default;

            void unlink() {
                if (next != nullptr) next->prev = prev;
                if (prev != nullptr) prev->next = next;
            }

            void rlink(list_node<U> *node) {
                (*this).uio();
                next = node;
                node->uio();
                node->prev = this;
                                std::cout << "next linked to this" << std::endl;

            }
            
            void llink(list_node<U> *node) {
                prev = node;
                node->next = this;
            }

            void link(list_node<U> *left, list_node<U> *right) {
                std::cout << "enter link" << std::endl;
                llink(left);
                std::cout << "llink OK" << std::endl;
                rlink(right);
                std::cout << "rlink OK" << std::endl;
            }

            void uio() {
                std::cout << (prev != nullptr ? "has prev; ": "no prev item; ") << " " << (next != nullptr ? "has next" : "no next item") << ";" << std::endl;
            }

        };

    list_node<T> *head;
    list_node<T> *tail;
    size_t     length;

public:
    class iterator {
        friend list<T>::iterator list<T>::insert(iterator pos, const T& value);
        friend list<T>::iterator list<T>::erase(iterator first, iterator last);
        friend list<T>::iterator list<T>::erase(iterator pos);
    private:
        list_node<T> *current;


    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() { current = nullptr; }
        iterator(const iterator &other) { current = other.current; }
        iterator(list_node<T> *node) : current(node){}
        iterator& operator=(const iterator &other) {
            current = other.current;
            return *this;
        }

        iterator& operator++() {
            current = current->next;
            return *this;
        }
        iterator operator++(int) {
            iterator old = *this;
            current = current->next;
            return old;
        }
        iterator& operator+(size_t val) {
            for (size_t i = 0; i < val; i++) {
                current = current->next;
            }
            return *this;
        }
        reference operator*() const { return current->data; }
        pointer operator->() const { return current->data; }
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(iterator other) const { return current == other.current; }
        bool operator!=(iterator other) const { return current != other.current; }

    };

    class const_iterator {
        friend list<T>::iterator list<T>::insert(iterator pos, const T& value);
        friend list<T>::iterator list<T>::erase(iterator first, iterator last);
        friend list<T>::iterator list<T>::erase(iterator pos);
    private:
        list_node<T> *current;

    public:
        // list_node<T> *current;

        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::bidirectional_iterator_tag;

        const_iterator() { current = nullptr; }
        const_iterator(const const_iterator &other) { current = other.current; }
        const_iterator (list_node<T> *node) : current(node){}
        iterator& operator=(const iterator &other) {
            current = other.current;
            return *this;
        }
        const_iterator& operator++() {
            current = current->next;
            return *this;
        }
        const_iterator operator++(int) {
            iterator old = *this;
            current = current->next;
            return old;
        }
        const_iterator& operator+(size_t val) {
            for (size_t i = 0; i < val; i++) {
                current = current->next;
            }
            return *this;
        }
        reference operator*() const { return current->data; }
        pointer operator->() const { return current->data; }
        const_iterator& operator--() {
            current = current->prev;
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator old = *this;
            current = current->prev;
            return old;
        }

        bool operator==(const_iterator other) const { return current == other.current; }
        bool operator!=(const_iterator other) const { return current != other.current; }
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
    iterator insert(iterator pos, const T& value);
    iterator insert(const_iterator pos, size_t count, const T& value);
    iterator insert(iterator pos, size_t count, const T& value);

    iterator erase(const_iterator pos);
    iterator erase(iterator pos);
    iterator erase(const_iterator first, const_iterator last);
    iterator erase(iterator first, iterator last);


    void push_back(const T& value);
    void pop_back();

    void push_front(const T& value);
    void pop_front();

    void resize(size_t count);
    void swap(list& other);


    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void splice(iterator pos, list& other);
    void remove(const T& value);
    void reverse();
    void unique();
    void sort();
};

template<class T>
list<T>::list() : head(nullptr), tail(nullptr), length(0) { }

template<class T>
list<T>::list(size_t count, const T& value) : list() {
    for (size_t i = 0; i <= count; ++i) {
        push_back(value);
    }
    length = count;
}

template<class T>
list<T>::list(size_t count) : list(count, T()) { }

template<class T>
list<T>::~list() { clear(); }

template<class T>
void list<T>::push_back(const T& value) {
    T temp = value;
    if (!length) {
        head =  new list_node<T>(temp);
        tail = head;
    } else {
        list_node<T> *new_node = new list_node<T>(temp, nullptr, tail);
        tail->rlink(new_node);
        tail = tail->next;
    }
    ++length;
}

template<class T>
void list<T>::pop_back() {
    if (length < 2){
        head = tail = nullptr;
        if (length == 1) --length;
        return;
    }
    tail = tail->prev;
    tail->next->unlink();
    --length;
}

template<class T>
list<T>::list(const list& other) {
    *this = other;
};

template<class T>
list<T>& list<T>::operator=(const list<T>& other) {
    head = other.head;
    tail = other.tail;
    length = other.length;
    return *this;
}

template<class T>
T& list<T>::front() { return head->data; };

template<class T>
const T& list<T>::front() const { return head->data; };

template<class T>
T& list<T>::back() { return tail->data; };

template<class T>
const T& list<T>::back() const { return tail->data; };

template<class T>
typename list<T>::iterator list<T>::begin() const { return iterator(head); }

template<class T>
typename list<T>::iterator list<T>::end() const {return iterator(tail);}

template<class T>
typename list<T>::const_iterator list<T>::cbegin() const { return const_iterator(head); }

template<class T>
typename list<T>::const_iterator list<T>::cend() const { return const_iterator(tail); }

template<class T>
typename list<T>::reverse_iterator list<T>::rbegin() const { return reverse_iterator(tail); }

template<class T>
typename list<T>::reverse_iterator list<T>::rend() const { return reverse_iterator(head); }

template<class T>
typename list<T>::const_reverse_iterator list<T>::crbegin() const { return const_reverse_iterator(tail); }

template<class T>
typename list<T>::const_reverse_iterator list<T>::crend() const { return const_reverse_iterator(head); }

template<class T>
bool list<T>::empty() const { return length == 0; }

template<class T>
size_t list<T>::size() const { return length; }

template<class T>
size_t list<T>::max_size() const { return 1000000; };

template<class T>
void list<T>::clear() {
    while (length) { pop_back(); }
}

template<class T>
void list<T>::push_front(const T& value) {
    T temp = value;
    if (!length) {
        head = new list_node<T>(temp);
        tail = head;
    } else {
        list_node<T> *new_node = new list_node<T>(temp, head);
        head->llink(new_node);
        head = head->prev;
    }
    ++length;
} 

template<class T>
void list<T>::pop_front() {
    if (!length) {
        return;
    } else {
        head = head->next;
        head->prev->unlink();
        --length;
    }
}


template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, const T& value) {
    T temp = value;
    iterator pos_next = pos + 1;
    list_node<T> *new_node = new list_node<T>(temp);
    new_node->link(pos.current, pos_next.current);
    ++pos;
    ++length;
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::insert(const_iterator pos, size_t count, const T& value) {
    for (size_t i = 0; i < count; i++) {
        pos = insert(pos, value);
    }
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::insert(iterator pos, const T& value) {
    T temp = value;
    if (pos == begin()) {
        push_front(temp);
        return pos;
    }
    list_node<T> *new_node = new list_node<T>(temp);
    std::cout << "create node" << std::endl;
    new_node->link(pos.current->prev, pos.current);
    std::cout << "link new node" << std::endl;
    ++length;
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::insert(iterator pos, size_t count, const T& value) {
    std::cout << "enter chad insert" << std::endl;
    for (size_t i = 0; i < count; i++) {
        pos = insert(pos, value);
        std::cout << i << std::endl;
    }
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator pos) {
    const_iterator res = pos - 1;
    pos.current->unlink();
    --length;
    return res;
}

template<class T>
typename list<T>::iterator list<T>::erase(const_iterator first, const_iterator last) {
    first.current->prev->next = last.current;
    last.current->prev = first.current->prev;
    --first;
    return first;
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator pos) {
    std::cout << "1" << std::endl;
    if (pos == begin()) {
        std::cout << "2" << std::endl;
        ++pos;
        pop_front();
        return pos; 
    } else if (pos == end()) {
        --pos;
        pop_back();
        return pos;
    }
    std::cout << "3" << std::endl;
    --pos;
    pos.current->next->unlink();
    --length;
    return pos;
}

template<class T>
typename list<T>::iterator list<T>::erase(iterator first, iterator last) {
    std::cout << "enter erase" << std::endl;
    do {
        last = erase(last);
        std::cout << "- - - - -" << std::endl;
    } while (first != last);
    erase(last);
    return last;
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
    other.pop_back();
    return;
}

template<class T>
void list<T>::merge(list<T>& other) {
    other.pop_back();
    return;};
template<class T>
void list<T>::splice(const_iterator pos, list& other){
    pos++;
    other.pop_back();
    return;};
template<class T>
void list<T>::splice(iterator pos, list& other){pos++; other.pop_back(); return;};

template<class T>
void list<T>::remove(const T& value){
    std::cout << value << std::endl;
    return;};
template<class T>
void list<T>::reverse(){return;};
template<class T>
void list<T>::unique(){return;};
template<class T>
void list<T>::sort(){return;};

}  // namespace task
