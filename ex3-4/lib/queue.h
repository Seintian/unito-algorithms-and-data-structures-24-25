#ifndef _QUEUE_H
#define _QUEUE_H

#ifndef _HASHTABLE_H_

/**
 * @brief Enum to define return status codes.
 * 
 * RETURN_FAILURE: Indicates a failure with a value of -1.
 * RETURN_SUCCESS: Indicates success with a value of 0.
 */
typedef enum _ReturnType {
    RETURN_FAILURE = -1,
    RETURN_SUCCESS = 0

} ReturnType;

#endif // _HASHTABLE_H_

typedef struct queue *Queue;

/**
 * @brief Creates a new queue.
 *
 * This function allocates memory for a new queue and initializes its front and rear pointers to NULL.
 *
 * @return pointer to the newly created queue, or NULL if memory allocation fails.
 */
Queue queue_create(void);

/**
 * @brief Checks if the queue is empty.
 *
 * This function checks whether the given queue is empty by examining if the front of the queue is NULL.
 *
 * @param q A pointer to the queue to check.
 * @return integer 1 if the queue is empty, 0 if it is not, and RETURN_FAILURE if the queue is NULL.
 */
int queue_is_empty(Queue q);

/**
 * @brief Retrieves the data from the front of the queue.
 *
 * @param q A pointer to the queue whose first element is returned.
 * @return A pointer to the data at the front of the queue, or NULL if the queue is empty or NULL.
 */
void* queue_first(Queue q);

/**
 * @brief Enqueues an element into the queue.
 *
 * This function adds a new element to the end of the queue and updates the front
 * and rear pointers accordingly.
 *
 * @param q A pointer to the queue to which the element will be added.
 * @param el The element to be added to the queue.
 * @return RETURN_SUCCESS if the element was successfully enqueued, RETURN_FAILURE on failure.
 */
ReturnType queue_enqueue(Queue q, void* el);

/**
 * @brief Dequeues an element from the queue.
 *
 * This function removes the front element from the queue, updates the front
 * and rear pointers accordingly, and returns its data.
 *
 * @param q A pointer to the queue from which to dequeue an element.
 * @return A pointer to the data of the dequeued element, or NULL if the queue is empty or NULL.
 */
void* queue_dequeue(Queue q);

/**
 * @brief Frees the queue.
 *
 * This function deallocates memory for the queue structure. Note that it does not 
 * deallocate memory for the elements present in the queue.
 *
 * @param q A pointer to the queue to be freed. If the queue is NULL,
 *          the function returns -1.
 *
 * @return RETURN_SUCCESS if the queue was successfully freed, RETURN_FAILURE if the queue was NULL.
 */
ReturnType queue_free(Queue q);

#endif // _QUEUE_H