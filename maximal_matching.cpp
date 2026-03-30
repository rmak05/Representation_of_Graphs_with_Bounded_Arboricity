#include <stack>
#include "maximal_matching.hpp"

graph_maximal_matching::list_node::list_node(const int _vertex, list_node *_next, list_node *_previous, list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}

void graph_maximal_matching::insert_list_node(list_node*& _head, list_node* _node){
    if(!_node) return;

    _node->next = _head;
    _node->previous = nullptr;
    if(_head) _head->previous = _node;

    _head = _node;
}

void graph_maximal_matching::erase_list_node(list_node*& _head, list_node* _node){
    if(!_head || !_node) return;

    if(_head == _node){
        list_node *temp = _head;

        _head = _head->next;
        if(_head) _head->previous = nullptr;

        delete temp;
    }
    else{
        _node->previous->next = _node->next;
        if(_node->next) _node->next->previous = _node->previous;

        delete _node;
    }
}

bool graph_maximal_matching::erase_vertex_from_out_list(list_node*& _head, int _vertex){
    if(!_head) return false;

    list_node *temp = _head;

    while(temp){
        if(temp->vertex == _vertex){
            if(matching[temp->external->vertex] == -1){
                erase_list_node(in_list_unmatched[temp->vertex], temp->external);
            }
            else{
                erase_list_node(in_list_matched[temp->vertex], temp->external);
            }
            
            erase_list_node(_head, temp);

            return true;
        }

        temp = temp->next;
    }

    return false;
}

void graph_maximal_matching::notify_out_neighbours(int _u, bool _matched){
    list_node *list_itr = out_list[_u];
    
    while(list_itr){
        int x = list_itr->vertex;

        if(_matched){
            erase_list_node(in_list_unmatched[x], list_itr->external);
        }
        else{
            erase_list_node(in_list_matched[x], list_itr->external);
        }
        
        list_itr->external = new list_node(_u, nullptr, nullptr, list_itr);
        if(_matched){
            insert_list_node(in_list_matched[x], list_itr->external);
        }
        else{
            insert_list_node(in_list_unmatched[x], list_itr->external);
        }

        list_itr = list_itr->next;
    }
}

// graph_maximal_matching::graph_maximal_matching(const int _num_vertices, const int _arboricity){
//     graph_maximal_matching::build(_num_vertices, std::vector<std::pair<int, int>>(), _arboricity);
// }

// void graph_maximal_matching::insert(const int _u, const int _v){
//     int delta = 4 * arboricity;

//     /*
//     if _u and _v are unmatched, match them immediately
//     */
    
//     /*
//     below lines update the list correctly but it is supposed to match as well if possible
//     */
//     out_list[_u].push_back(_v);
//     if(matching[_u] == -1) partial_unmatched_list[_v].insert(_u);
//     if(matching[_v] == -1) partial_unmatched_list[_u].insert(_v);

//     if(static_cast<int>(out_list[_u].size()) == delta + 1){
//         std::stack<int> stk;

//         stk.push(_u);
//         while(!stk.empty()){
//             int w = stk.top();
//             stk.pop();

//             for(auto& x : out_list[w]){
//                 out_list[x].push_back(w);
//                 if(matching[x] == -1) partial_unmatched_list[w].insert(x);

//                 if(static_cast<int>(out_list[x].size()) == delta + 1){
//                     stk.push(x);
//                 }
//             }

//             out_list[w].clear();
//         }
//     }
// }

void graph_maximal_matching::erase(int _u, int _v){
    if(erase_vertex_from_out_list(out_list[_u], _v)){
        // pass
    }
    else if(erase_vertex_from_out_list(out_list[_v], _u)){
        std::swap(_u, _v);
    }
    else{
        return;
    }

    if(matching[_u] != _v) return;
    matching[_u] = matching[_v] = -1;

    notify_out_neighbours(_u, false);
    notify_out_neighbours(_v, false);

    for(int w : {_u, _v}){
        if(matching[w] != -1) continue;

        list_node *list_itr = out_list[w];
    
        while(list_itr){
            int x = list_itr->vertex;

            if(matching[x] == -1){
                matching[w] = x;
                matching[x] = w;

                notify_out_neighbours(w, true);
                notify_out_neighbours(x, true);

                break;
            }

            list_itr = list_itr->next;
        }
    }
}

// void graph_maximal_matching::build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
//     sparse_graph::build(_num_vertices, _edges, _arboricity);

//     matching.clear();
//     matching.resize(_num_vertices, -1);

//     out_list.clear();
//     out_list.resize(_num_vertices);

//     partial_unmatched_list.clear();
//     partial_unmatched_list.resize(_num_vertices);
// }