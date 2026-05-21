#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP 1

#include <cstddef>

template<typename _list_data_type>
struct doubly_list_node{
public:
    _list_data_type     data;
    doubly_list_node*   next;
    doubly_list_node*   previous;
    
    doubly_list_node(const _list_data_type _data = _list_data_type(), doubly_list_node* _next = nullptr, doubly_list_node* _previous = nullptr);
};

template<typename _list_data_type>
class doubly_linked_list{
public:
    doubly_list_node<_list_data_type>*  head;
    doubly_list_node<_list_data_type>*  tail;
    std::size_t                         nodes_count;  

    doubly_linked_list();

    void insert(const _list_data_type& _data);
    void insert_at(doubly_list_node<_list_data_type>* _node, const _list_data_type& _data);
    void erase(doubly_list_node<_list_data_type>* _node);
    std::size_t size() const;
    bool empty() const;
};

template<typename _list_data_type>
doubly_list_node<_list_data_type>::doubly_list_node(const _list_data_type _data, doubly_list_node* _next, doubly_list_node* _previous) :
data(_data), next(_next), previous(_previous){}

template<typename _list_data_type>
doubly_linked_list<_list_data_type>::doubly_linked_list() :
head(nullptr), tail(nullptr), nodes_count(0uz){}

template<typename _list_data_type>
void doubly_linked_list<_list_data_type>::insert(const _list_data_type& _data){
    if(tail){
        tail->next = new doubly_list_node<_list_data_type>{_data, nullptr, tail};
        
        tail = tail->next;
    }
    else{
        head = tail = new doubly_list_node<_list_data_type>{_data};
    }

    nodes_count++;
}

/*
inserts _data after _node; if _node == nullptr, inserts at head
*/
template<typename _list_data_type>
void doubly_linked_list<_list_data_type>::insert_at(doubly_list_node<_list_data_type>* _node, const _list_data_type& _data){
    if(!_node){
        if(head){
            head = new doubly_list_node<_list_data_type>{_data, head, nullptr};
            head->next->previous = head;
        }
        else{
            head = tail = new doubly_list_node<_list_data_type>{_data};
        }
    }
    else if(_node->next){
        _node->next->previous = new doubly_list_node<_list_data_type>{_data, _node->next, _node};
        _node->next = _node->next->previous;
    }
    else{
        tail->next = new doubly_list_node<_list_data_type>{_data, nullptr, tail};
    
        tail = tail->next;
    }

    nodes_count++;
}

/*
_node must be present inside the list
*/
template<typename _list_data_type>
void doubly_linked_list<_list_data_type>::erase(doubly_list_node<_list_data_type>* _node){
    if(!head || !_node) return;
    
    if(nodes_count == 1){
        head = tail = nullptr;
    }
    else if(_node == head){
        head = head->next;
        head->previous = nullptr;
    }
    else if(_node == tail){
        tail = tail->previous;
        tail->next = nullptr;
    }
    else{
        _node->previous->next = _node->next;
        _node->next->previous = _node->previous;
    }
    delete _node;

    nodes_count--;
}

template<typename _list_data_type>
std::size_t doubly_linked_list<_list_data_type>::size() const{
    return nodes_count;
}

template<typename _list_data_type>
bool doubly_linked_list<_list_data_type>::empty() const{
    return nodes_count == 0uz;
}

struct list_node;
template <typename _list_node_type>
class linked_list;

template <typename _list_node_type>
void insert_list_node(linked_list<_list_node_type>& _list, list_node* _node);
template <typename _list_node_type>
void erase_list_node(linked_list<_list_node_type>& _list, list_node* _node); /* _node must exist in _list */

struct list_node{
public:
    int         vertex;
    list_node*  next;
    list_node*  previous;
    list_node*  external;

    list_node(const int _vertex = -1, list_node *_next = nullptr, list_node *_previous = nullptr, list_node *_external = nullptr);
};

template <typename _list_node_type>
class linked_list{
public:
    _list_node_type*    head;
    int                 size;

    linked_list();

    void insert(_list_node_type* _node);
    void erase(_list_node_type* _node); /* _node must exist */
};

template <typename _list_node_type>
linked_list<_list_node_type>::linked_list() :
head(nullptr), size(0){}

template <typename _list_node_type>
void insert_list_node(linked_list<_list_node_type>& _list, list_node* _node){
    if(!_node) return;

    _node->next = _list.head;
    _node->previous = nullptr;
    if(_list.head) _list.head->previous = _node;

    _list.head = _node;

    _list.size++;
}

template <typename _list_node_type>
void erase_list_node(linked_list<_list_node_type>& _list, list_node* _node){
    if(!_list.head || !_node) return;

    if(_list.head == _node){
        list_node *temp = _list.head;

        _list.head = _list.head->next;
        if(_list.head) _list.head->previous = nullptr;

        delete temp;
    }
    else{
        _node->previous->next = _node->next;
        if(_node->next) _node->next->previous = _node->previous;

        delete _node;
    }

    _list.size--;
}

template <typename _list_node_type>
void linked_list<_list_node_type>::insert(_list_node_type* _node){
    insert_list_node(*this, _node);
}

template <typename _list_node_type>
void linked_list<_list_node_type>::erase(_list_node_type* _node){
    erase_list_node(*this, _node);
}

#endif /* LINKED_LIST_HPP */