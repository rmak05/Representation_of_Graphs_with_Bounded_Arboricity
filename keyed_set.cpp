#include "keyed_set.hpp"

keyed_set_list_node* keyed_set::report_max() const{
    if(!dynamic_lists.empty()){
        return dynamic_lists.back().head;
    }
    else if(!static_lists.empty()){
        return static_lists.back().head;
    }
    else{
        return nullptr;
    }
}

void keyed_set::increment(keyed_set_list_node *_x_ptr){
    if(!_x_ptr) return;

    auto new_ptr = new keyed_set_list_node(_x_ptr->x, _x_ptr->k + 1, nullptr, nullptr, _x_ptr->external);
    if(_x_ptr->k <= k0 + 1){
        static_lists[_x_ptr->k].erase(_x_ptr);
    }
    else{
        // pass
    }
}