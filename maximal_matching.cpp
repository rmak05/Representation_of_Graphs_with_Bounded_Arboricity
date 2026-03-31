#include <stack>
#include "maximal_matching.hpp"

graph_maximal_matching::list_node::list_node(const int _vertex, list_node *_next, list_node *_previous, list_node *_external) :
vertex(_vertex), next(_next), previous(_previous), external(_external){}

graph_maximal_matching::linked_list::linked_list() :
head(nullptr), size(0){}

void graph_maximal_matching::insert_list_node(linked_list& _list, list_node* _node){
    list_node *_head = _list.head;

    if(!_node) return;

    _node->next = _head;
    _node->previous = nullptr;
    if(_head) _head->previous = _node;

    _head = _node;

    _list.size++;
}

// void graph_maximal_matching::erase_list_node(list_node*& _head, list_node* _node){
void graph_maximal_matching::erase_list_node(linked_list& _list, list_node* _node){
    list_node *_head = _list.head;

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

    _list.size--;
}

// bool graph_maximal_matching::erase_vertex_from_out_list(list_node*& _head, int _vertex){
bool graph_maximal_matching::erase_vertex_from_out_list(linked_list& _list, int _vertex){
    list_node *_head = _list.head;

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
            
            erase_list_node(_list, temp);

            return true;
        }

        temp = temp->next;
    }

    return false;
}

void graph_maximal_matching::notify_out_neighbours(int _u, bool _matched){
    list_node *list_itr = out_list[_u].head;
    
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

graph_maximal_matching::graph_maximal_matching(){
    build(0, std::vector<std::pair<int, int>>(), 0);
}

graph_maximal_matching::graph_maximal_matching(const int _num_vertices, const int _arboricity){
    build(_num_vertices, std::vector<std::pair<int, int>>(), _arboricity);
}

graph_maximal_matching::graph_maximal_matching(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    build(_num_vertices, _edges, _arboricity);
}

void graph_maximal_matching::insert(const int _u, const int _v){
    int delta = 4 * arboricity;

    list_node* u_node = new list_node(_u, nullptr, nullptr, nullptr);
    list_node* v_node = new list_node(_v, nullptr, nullptr, nullptr);
    u_node->external = v_node;
    v_node->external = u_node;
    insert_list_node(out_list[_u], v_node);
    if(matching[_u] != -1){
        insert_list_node(in_list_matched[_v], u_node);
    }
    else{
        if(matching[_v] == -1){
            matching[_u] = _v;
            matching[_v] = _u;

            notify_out_neighbours(_u, true);
            notify_out_neighbours(_v, true);

            insert_list_node(in_list_matched[_v], u_node);
        }
        else{
            insert_list_node(in_list_unmatched[_v], u_node);
        }
    }

    if(out_list[_u].size  == delta + 1){
        std::stack<int> stk;

        stk.push(_u);
        while(!stk.empty()){
            int w = stk.top();
            stk.pop();

            while(out_list[w].size > 0){
                int x = out_list[w].head->vertex;

                erase_vertex_from_out_list(out_list[w], x);

                list_node* w_node = new list_node(w, nullptr, nullptr, nullptr);
                list_node* x_node = new list_node(x, nullptr, nullptr, nullptr);
                w_node->external = x_node;
                x_node->external = w_node;
                insert_list_node(out_list[x], w_node);
                if(matching[x] != -1){
                    insert_list_node(in_list_matched[w], x_node);
                }
                else{
                    insert_list_node(in_list_unmatched[w], x_node);
                }

                if(out_list[x].size == delta + 1){
                    stk.push(x);
                }
            }
        }
    }
}

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

        list_node *list_itr = out_list[w].head;
    
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

void graph_maximal_matching::build(const int _num_vertices, const std::vector<std::pair<int, int>>& _edges, const int _arboricity){
    arboricity = _arboricity;

    matching.clear();
    out_list.clear();
    in_list_matched.clear();
    in_list_unmatched.clear();
    matching.resize(_num_vertices, -1);
    out_list.resize(_num_vertices);
    in_list_matched.resize(_num_vertices);
    in_list_unmatched.resize(_num_vertices);

    for(auto& edge :_edges){
        insert(edge.first, edge.second);
    }
}

int graph_maximal_matching::get_matched_vertex(const int _u) const{
    return matching[_u];
}