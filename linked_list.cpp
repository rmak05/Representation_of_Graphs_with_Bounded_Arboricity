#include "linked_list.hpp"

list_node::list_node(const int _vertex, list_node *_next, list_node *_previous, list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}

linked_list::linked_list() :
head(nullptr), size(0){}

void insert_list_node(linked_list& _list, list_node* _node){
    if(!_node) return;

    _node->next = _list.head;
    _node->previous = nullptr;
    if(_list.head) _list.head->previous = _node;

    _list.head = _node;

    _list.size++;
}

void erase_list_node(linked_list& _list, list_node* _node){
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

void linked_list::insert(list_node* _node){
    insert_list_node(*this, _node);
}

void linked_list::erase(list_node* _node){
    erase_list_node(*this, _node);
}