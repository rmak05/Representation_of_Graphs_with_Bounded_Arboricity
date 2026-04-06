#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP 1

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