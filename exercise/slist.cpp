#include <cstddef>
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>
#include <initializer_list>

template<class T>
class slist {
private:
    struct Node;
public:
    class iterator;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    slist() {
        head = tail = 0;
        size = 0;
    }

    slist(std::initializer_list<T> list) : slist() {
        for(auto t : list) {
            push_back(t);
        }
    }
   ~slist() { clear(); } 
    bool is_empty() const { return size == 0; }
    int  length() const { return size;}

    void clear() {
        while(!is_empty())
            erase(begin());
    }
 
    T pop_back() {
        if(is_empty()) throw "list is empty cant pop value.";
        T ret_val = tail->data;
        Node* new_tail = tail->prev;
        if(new_tail != 0) new_tail->next = 0;
        delete tail;
        tail = new_tail;            
        size--;
        return ret_val;
    }

    T pop_front() {
        if(is_empty()) throw "list is empty cant pop value.";
        T ret_val = head->data;
        Node* new_head = head->next;
        if(new_head != 0) head->prev = 0;
        delete head;
        head = new_head;            
        size--;
        return ret_val;
    }

    slist& push_back(T t) {
        Node* new_node = new Node(t);
        if(head == 0 && tail == 0) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;            
        }
        size++;
        return *this;
    }

    slist& push_front(T t) {
        Node* new_node = new Node(t);
        if(head == 0 && tail == 0) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            new_node->next = head;
            head = new_node;
        }
        size++;
        return *this;
    }

    iterator begin() const { return iterator(head); }
    iterator rbegin() const { return iterator(tail); }
    iterator end() const { return iterator(); }
    iterator erase(iterator pos) {
        if(is_empty()) return end();
        Node* current = pos.current;
        remove(current);
        ++pos;
        delete current;
        return pos;
    }

    iterator rerase(iterator pos) {
        if(is_empty()) return end();
        Node* current = pos.current;
        remove(current);
        --pos;
        delete current;
        return pos;
    }

    class iterator {
    public:
        friend class slist;
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef T& reference;

        iterator(Node* cur = 0) : current(cur) {}
        iterator& operator++() {
            current = current->next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            this->operator++();
            return temp;
        }
        iterator& operator--() {
            current = current->prev;
            return *this;
        }
        iterator operator--(int) {
            iterator temp = *this;
            this->operator--();
            return temp;
        }
        iterator operator+(int offset) {
            iterator temp = *this;
            if(offset > 0) {
                while(offset-- != 0 && temp.current->next != 0) ++temp;
            } else if(offset < 0) {
                while(offset++ != 0 && temp.current->prev != 0) --temp;
            }
            return temp;
        }
        iterator operator-(int offset) {
            return operator+(-offset);
        }

        int operator-(iterator target) {
            if(*this == target) return 0;
            int count = 0;
            bool find = false;
            Node* current = this->current;
            while(this->current->next != 0) {
                count--;
                if(++*this == target) { find = true; break; }
            }
            if(!find) {
                this->current = current;
                count = 0;
                while(this->current->prev != 0) {
                    count++;
                    if(--*this == target) { find = true; break; }
                }

            }
            if(find) return count;
            throw "Unexpected Error!";
        }

        T& operator*() { return current->data; }
        bool operator==(const iterator& iter) const {
            return current == iter.current;
        }
        bool operator!=(const iterator& iter) const {
            return current != iter.current;
        }
    private:
        Node* current;
    };

private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& data) : data(data) {
            next = prev = 0;
        }
    };
    Node* head;
    Node* tail;
    int   size;
    void  remove(Node* delete_node) {
        if(delete_node == head) head = delete_node->next;
        if(delete_node == tail) tail = delete_node->prev;
        Node* prev_node = delete_node->prev;
        Node* next_node = delete_node->next;
        if(prev_node != 0) prev_node->next = next_node;
        if(next_node != 0) next_node->prev = prev_node;
        size--;
    }
};

void test_vector() {

    std::vector<int> v {1,2,3,4,5,6};

    auto found = std::find(v.begin(), v.end(), 0);
    if(found != v.end())
        std::cout << "Found Number" << std::endl;
    else
        std::cout << "Not Found" << std::endl;

}

void test_slist() {
    slist<int> list {1,2,3,4,5};
    std::cout << "position 4: " << *(list.begin()+4) << std::endl;
    std::cout << "offset = " << ((list.begin()+3) -(list.begin()+4)) << std::endl;
    list.erase(list.begin());
    std::cout << "list size = " << list.length() << std::endl;
    
    for(auto it=list.rbegin(); it!=list.end(); it--) {
        std::cout << *it << std::endl;
    }
    auto found = std::find(list.begin(), list.end(), 4);
    if(found != list.end())
        std::cout << "Found Number" << " " << *found << std::endl;
    else
        std::cout << "Not Found" << std::endl;    

    std::cout << "list is empty ? " << (list.is_empty() ? "Yes" : "No") << std::endl;
    std::cout << "clear list..." << std::endl;
    list.clear();
    std::cout << "list is empty ? " << (list.is_empty() ? "Yes" : "No") << std::endl;
}


int main() {
    test_slist();
    return 0;
}