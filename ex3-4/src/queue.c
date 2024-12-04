#include <stdlib.h>
#include "queue.h"


/**
 * @typedef QueueElem
 * @brief A pointer to a struct queueElem, representing an element in the queue.
 */
typedef struct queueElem *QueueElem;

/**
 * @struct queueElem
 * @brief Represents an element in the queue.
 * 
 * @var queueElem::data
 * A void pointer to the data stored in the queue element.
 * @var queueElem::next
 * A pointer to the next element in the queue.
 */
struct queueElem {
    void *data;
    QueueElem next;
};

/**
 * @struct queue 
 * @brief Represents a queue.
 * 
 * @var queue::front
 * The front element of the queue.
 * @var queue::rear
 * The rear element of the queue.
 */
struct queue {
    QueueElem front;
    QueueElem rear;
};

Queue queue_create(void) {
    Queue q = (Queue) malloc(sizeof(struct queue));
    if (!q)
        return NULL;

    q -> front = NULL;
    q -> rear = NULL;
    return q;
}

int queue_is_empty(Queue q) {
    if (!q) 
        return RETURN_FAILURE;

    return q -> front == NULL;
}

void* queue_first(Queue q) {
    if (!q || !q -> front) 
        return NULL;

    return q -> front -> data;
}

ReturnType queue_enqueue(Queue q, void* el) {
    if (!q) 
        return RETURN_FAILURE;

    QueueElem newElem = (QueueElem) malloc(sizeof(struct queueElem));
    if (!newElem)
        return RETURN_FAILURE;

    newElem -> data = el;
    newElem -> next = NULL;

    if (!q -> rear) {
        q -> front = q -> rear = newElem;

        return RETURN_SUCCESS;
    }

    q -> rear -> next = newElem;
    q -> rear = newElem;

    return RETURN_SUCCESS;
}

ReturnType queue_dequeue(Queue q) {
    if (!q || !q -> front)
        return RETURN_FAILURE; 

    QueueElem tmp = q -> front;

    q -> front = q -> front -> next;

    if (!q -> front)
        q -> rear = NULL;

    free(tmp);

    return RETURN_SUCCESS;
}

ReturnType queue_free(Queue q) {
    if (!q) 
        return RETURN_FAILURE;

    QueueElem current = q -> front;
    while (current) {
        QueueElem tmp = current;
        current = current -> next;
        free(tmp);
    }

    free(q);

    return RETURN_SUCCESS;
}