#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef struct list_t list_t;
struct list_t {
    void* data;
    list_t* succ;
    list_t* pred;
};

/* Create a new list node with this data. */
list_t* new_list(void* data) {
    list_t* list = malloc(sizeof(list_t));
    if (list == NULL)
        exit(1);

    list->data = data;
    list->succ = list->pred = list;
    return list;
}

/*
 * deallocate entire list, but not any data pointer. 
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
    size_t len  = 0;
    list_t* tmp = list->succ;;
    if(list == NULL)
        return 0;

    ++len;
    while(tmp != list) {
        ++len;
        tmp = tmp->succ;
    }
    return len;
}

/* insert data first in the list */
void insert_first(list_t** list, void* data) {
    list_t* new = new_list(data);
    list_t* h   = *list;
    
    if(h != NULL) {
        h->pred->succ = new;
        new->pred     = h->pred;
        h->pred       = new;
        new->succ     = h;
        *list = new;
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
    // Fetch data from head
    void* data = h->data;
    // The succesor of head is now the new head
    list_t* n  = h->succ;
    // The tails succesor is now the new head
    h->pred->succ = n;
    // The new heads predecssor is now the tail
    n->pred = h->pred;
    // List now points to the new head
    *list      = n;
    // Free memory of the old head
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

int main(void) {
    list_t** list = malloc(sizeof(list_t*));
    int a = 3;
    *list = new_list(&a);
    assert(length(*list) == 1);
    int b = 5;
    insert_first(list, &b);
    assert(length(*list) == 2);
    int c = 7;
    insert_last(list, &c);
    assert(length(*list) == 3);
    assert(*(int*)((*list)->pred->data) == 7);
    printf("%d", *(int*)((*list)->data));
    assert(*(int*)((*list)->data) == 5);
    int* t = remove_first(list);
    size_t sz;
    int** arr = (int**) list_to_array(*list, &sz);
    assert(sz == 2);
    assert(*t == 5);
    assert(*arr[0] == 3);
    assert(*arr[1] == 7);
    free_list(*list);
    free(list);
    free(arr);
}
