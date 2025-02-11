#include "priority_queue.h"

// TODO: Task 0
PQNode *pq_enqueue(PQNode **a_head, void *a_value, int (*cmp_fn)(const void *, const void *))
{
    // empty case
    if (a_head == NULL) {
        return NULL;
    }

    // new node creation
    PQNode *new_node= (PQNode *)malloc(sizeof(PQNode));
    new_node->a_value = a_value;
    // no next because its the head
    new_node->next = NULL;

    PQNode *prevnode = NULL;
    PQNode *currnode= *a_head;
    

    //first node where new value has equal or higher priority
    while (currnode != NULL && cmp_fn(a_value, currnode->a_value) > 0) {
        prevnode = currnode;
        currnode = currnode->next;
    }

    if (prevnode== NULL) {
        new_node->next = *a_head;
        *a_head = new_node;
    } else {
        prevnode->next = new_node;
        new_node->next = currnode;
    }

    return new_node;

}

// TODO: Task 0
PQNode *pq_dequeue(PQNode **a_head)
{
    // if head or ptr to head is null, return null
    if (a_head == NULL || *a_head == NULL) {
        return NULL;
    }

    // updating new head and remembering old head
    PQNode *old_head = *a_head;
    *a_head = old_head->next;

    // need to erase pointer
    old_head->next = NULL;

    return old_head;

}

// TODO: Task 0
PQNode *stack_push(PQNode **stack, void *a_value)
{
    // null case handling
    if (stack == NULL) {
        return NULL;
    }

    // creating the new node with a_value
    PQNode *pushNode = (PQNode *)malloc(sizeof(PQNode));

    // value assignment
    pushNode->a_value = a_value;
    pushNode->next = *stack;

    *stack = pushNode;

    return pushNode;


}

// TODO: Task 0
PQNode *stack_pop(PQNode **stack) {
    if (stack == NULL || *stack == NULL) {
        return NULL;
    }

    PQNode *old_head = *stack;
    *stack = old_head->next;
    old_head->next = NULL;

    return old_head;
}


// TODO: Task 0
void destroy_list(PQNode **a_head, void (*destroy_fn)(void *))
{
    if (a_head == NULL || *a_head == NULL) {
        return;
    }

    PQNode *currNode = *a_head;
    PQNode *nextNode;

    // pq traversal
    while (currNode != NULL) {
        nextNode = currNode->next;

        if (destroy_fn != NULL) {
            destroy_fn(currNode->a_value);
        }

        free(currNode);
        currNode = nextNode;;

    }

    *a_head = NULL;

}