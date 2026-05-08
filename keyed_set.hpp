#ifndef KEYED_SET_HPP
#define KEYED_SET_HPP 1

#include <vector>
#include "linked_list.hpp"

/*
* ReportMax(X): return a pointer to an element from X that has the maximum key.
• Increment(X,x): given a pointer to an element x ∈ X \{x0}, increment the key of x.
• Decrement(X,x): given a pointer to an element x ∈ X \{x0}, decrement the key of x.
• Insert(X,xi,ki): insert a new element xi with key ki ≤ k0 + 1 into X.
• Delete(X,x): given a pointer to an element x ∈ X \{x0}, remove x from X.
• IncrementCenter(X): increment k0. This operation takes O(k0) worst-case time.
• DecrementCenter(X): decrement k0 (unless k0 = 1). This operation takes O(k0) worst-case time.
*/

class keyed_set{
private:
    int                                             x0;
    int                                             k0;
    std::vector<linked_list<keyed_set_list_node>>   static_lists;   /* size is k0 + 2 (useful indices are 1 ... k0 + 1) */
    std::vector<linked_list<keyed_set_list_node>>   dynamic_lists;  /* sorted lists w.r.t. key */
    /* vector wont do, a linked list of linked lists is required, then access is tricky, linked_list<linked_list<list_node>> */

public:
    keyed_set();

    keyed_set_list_node* report_max() const;
    void increment(keyed_set_list_node *_x_ptr);
    void decrement(keyed_set_list_node *_x_ptr);
    void insert(const int _x, const int _k);
    void erase(keyed_set_list_node *_x_ptr);
    void increment_center();
    void decrement_center();
};

#endif /* KEYED_SET_HPP */