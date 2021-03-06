#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    IS_NULL_POINTER(q);
    /* TODO: What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q) {
        return;
    }
    while (q->head) {
        list_ele_t *tmp;
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    /*using a tmp pointer to free the link list elements*/
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    IS_NULL_POINTER(q);
    IS_NULL_POINTER(s);
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    IS_NULL_POINTER(newh);
    int len = strlen(s);
    char *cpy = malloc(sizeof(char) * len + 1);
    if (!cpy) {
        free(newh);
        return false;
    }
    for (int i = 0; i < len; i++) {
        *(cpy + i) = *(s + i);
    }
    *(cpy + len) = '\0';
    //    strncpy(cpy, s, strlen(s) + 1);
    newh->value = cpy;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->tail) {
        q->tail = newh;
    }
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    IS_NULL_POINTER(q);
    IS_NULL_POINTER(s);
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    IS_NULL_POINTER(newt);
    int len = strlen(s);
    char *cpy = malloc(sizeof(char) * len + 1);
    if (!cpy) {
        free(newt);
        return false;
    }
    //        strncpy(cpy, s, strlen(s) + 1);
    for (int i = 0; i < len; i++) {
        *(cpy + i) = *(s + i);
    }
    *(cpy + len) = '\0';
    newt->value = cpy;
    newt->next = NULL;
    if (q->tail) {  // if tail is not null
        q->tail->next = newt;
        q->tail = newt;
        q->size += 1;
        return true;
    } else {
        q->head = newt;
        q->tail = newt;
        q->size += 1;
        return true;
    }
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return false;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    IS_NULL_POINTER(q);
    IS_NULL_POINTER(q->head);
    IS_NULL_POINTER(sp);
    //    size_t real_size =
    //        (bufsize > strlen(q->head->value)) ? bufsize :
    //        strlen(q->head->value);
    //    strncpy(sp, q->head->value, bufsize);
    int head_value_len = strlen(q->head->value);
    for (int i = 0; i < bufsize; i++) {
        if (i >= head_value_len) {
            *(sp + i) = '\0';
            break;
        }
        *(sp + i) = *((q->head->value) + i);
    }
    if (head_value_len >= bufsize) {
        *(sp + bufsize - 1) = '\0';
    }

    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);

    q->size -= 1;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    IS_NULL_POINTER(q);
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (!q || q->head == NULL || q->size <= 1) {
        return;
    }
    list_ele_t *left = NULL, *right = q->head->next;
    q->tail = q->head;
    while (right != NULL) {
        q->head->next = left;
        left = q->head;
        q->head = right;
        right = right->next;
    }
    q->head->next = left;
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (!q || !q->head)
        return;

    q->head = merge_sort(q->head);
    return;
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}

list_ele_t *merge_sort(list_ele_t *head)
{
    if (!head || !head->next)
        return head;

    list_ele_t *slow = head, *fast;
    for (fast = head->next; fast && fast->next; fast = fast->next->next) {
        slow = slow->next;
    }

    list_ele_t *mid = slow->next;
    slow->next = NULL;
    return merge(merge_sort(head), merge_sort(mid));
}

list_ele_t *merge(list_ele_t *left, list_ele_t *right)
{
    list_ele_t *head = NULL;
    for (list_ele_t **iter = &head; true; iter = &((*iter)->next)) {
        if (!left) {
            *iter = right;
            break;
        }
        if (!right) {
            *iter = left;
            break;
        }
        if (strcmp(left->value, right->value) < 0) {
            *iter = left;
            left = left->next;
        } else {
            *iter = right;
            right = right->next;
        }
    }

    return head;
}
