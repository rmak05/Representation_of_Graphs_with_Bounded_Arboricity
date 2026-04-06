#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP 1

struct list_node;
class linked_list;

void insert_list_node(linked_list& _list, list_node* _node);
void erase_list_node(linked_list& _list, list_node* _node); /* _node must exist in _list */

struct list_node{
    int         vertex;
    list_node*  next;
    list_node*  previous;
    list_node*  external;

    list_node(const int _vertex = -1, list_node *_next = nullptr, list_node *_previous = nullptr, list_node *_external = nullptr);
};


class linked_list{
public:
    list_node*  head;
    int         size;

    linked_list();

    void insert(list_node* _node);
    void erase(list_node* _node); /* _node must exist */
};


#endif /* LINKED_LIST_HPP */