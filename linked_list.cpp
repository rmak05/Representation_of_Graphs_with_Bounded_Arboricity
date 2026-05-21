#include "linked_list.hpp"

list_node::list_node(const int _vertex, list_node *_next, list_node *_previous, list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}