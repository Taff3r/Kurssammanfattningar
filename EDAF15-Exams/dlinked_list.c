#include <stdlib.h>
typedef struct list_t list_t;
struct list_t {
    void* data;
    list_t* succ;
    list_t* pred;
};

/* Create a new list node with this data. */
list_t* new_list(void* data) {
    list_t* list = malloc(sizeof(list_t));
    list->data = data;
    list->succ = list->pred = list;
    return list;
}

/*
 * deallocate entire list, but not any data pointer. 
 *
 */
void free_list(list_t* list) {
    if(list == NULL)
        return;

    list_t* tmp;
    list_t* n;
    list->pred->succ = NULL;
    tmp = list;
    while(tmp != NULL){
        n = tmp->succ;
        free(tmp);
        tmp = n;
    }
    
}

/* return the number of nodes in the list*/
size_t length(list_t* list) {
    size_t len = 0;
    list_t* tmp = list;
    if(list == NULL)
        return 0;
    while(tmp->succ != list) {
        ++len;
        tmp = tmp->succ;
    }
    return len;
}

/* insert data first in the list */
void insert_first(list_t** list, void* data) {
    list_t* new = new_list(data);
    list_t* h   = *list;
    
    if(h != NULL){
        h->pred->succ = new;
        new->pred = h->pred;
        h->pred = new;
        new->succ = h;
    } else
        h = new;
}

/* insert data last in the list */
void insert_last(list_t** list, void* data) {
    list_t* t = new_list(data);
    list_t* h = *list;
    if (h != NULL){
        h->pred->succ = t;
        t->pred = h->pred;
        h->pred = t;
        t->succ = h;
    } else 
        h = t;
}

/* if the list is empty return NULL, othersiw remove and free the first node in the list and return its data pointer */
void* remove_first(list_t** list) {
    list_t* h = *list;
    if(h == NULL)
        return NULL;
    void* data = h->data;
    list_t* n = h->succ;
    n->pred = h->pred;
    *list = n;
    free(h);
    return data;
}

/*
Allocate and return a pointer to an array with contents (data pointers) of the list, and write the length of the list in varaible pointer to by size. If the size is zero, NULL should be returned.

Note: the word array above is used in the sense that memory should allocated for a numer of elements in contigous memory locations and not as in array declaration */
void** list_to_array(list_t* list, size_t* size) {
    size_t len = *size = length(list);
    if(len == 0)
        return NULL;

    list_t* it = list;
    void** arr = malloc(len * sizeof(void*));
    for (int i = 0; i < len; ++i){
        arr[i] = it->data;
        it = it->succ;
    }
    return arr;
}
