#include "linked_list.hpp"

list_node::list_node(const int _vertex, list_node *_next, list_node *_previous, list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}

keyed_set_list_node::keyed_set_list_node(const int _x, const int _k, keyed_set_list_node *_next, keyed_set_list_node *_previous, keyed_set_graph_node *_external) :
x(_x), k(_k), next(_next), previous(_previous), external(_external){}

keyed_set_graph_node::keyed_set_graph_node(const int _vertex, keyed_set_graph_node *_next, keyed_set_graph_node *_previous, keyed_set_list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}