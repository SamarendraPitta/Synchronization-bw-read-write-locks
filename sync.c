/*
 * NAME, etc.
 *
 * sync.c
 *
 * Synchronization routines for SThread
 */

#define _REENTRANT

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sched.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "sthread.h"

/*
 * Atomic operations for x86 architecture.
 */
static inline int test_and_set_bit(volatile unsigned long *addr)
{
	int oldval;
	__asm__ __volatile__("xchgl %0, %1"
			: "=r"(oldval), "+m"(*(addr))	/* output */
			: "0"(1)						/* input */
			: "memory"	/* clobbered: changing contents of memory */
			);
	return oldval;
}
static inline void clear_bit(volatile unsigned long *addr)
{
	unsigned long oldval;
	__asm__ __volatile__("xchgl %0, %1"
			: "=r"(oldval), "+m"(*(addr))	/* output */
			: "0"(0)						/* input */
			: "memory"	/* clobbered: changing contents of memory */
			);
}

/*
 * rwlock routines
 */

// Initialize a queue
static void Queue_Initialization(queue_t *queue) {
    queue->front_node = NULL;
    queue->rear_node = NULL;
}

// Enqueue a thread
static int Queue_Enqueue(queue_t *q, sthread_t thread) {
	//printf("Thread %p is being enqueued into the wait queue\n", (void *)thread);
	//The below line will allocates the block of memory to newly created node.
    queue_node_t *NewNode = malloc(sizeof(queue_node_t));
	if(NewNode == NULL){
		printf("memory allocation failed");
		return -1;
	}
	//assigning the thread to new node and new node next will be null
    NewNode->thread = thread;
    NewNode->next = NULL;

    if (q->rear_node == NULL) {		
        q->front_node = NewNode;		//assignning new node to both front_node and rear_node because the queue is empty
		q->rear_node = NewNode;
    } else {
        q->rear_node->next = NewNode;		//a new node is always appended at the rear_node end. So next node of rear_node will be the new node and after assignning new node will be the rear_node node.
        q->rear_node = NewNode;
    }
	return 0;
}

// Dequeue a thread
static sthread_t Dequeue(queue_t *q) {
    if (q->front_node == NULL) 	//if queue is empty, returning null
		return NULL;

    queue_node_t *temp_node = q->front_node;
    sthread_t thread = temp_node->thread;

    q->front_node = q->front_node->next;
    if (q->front_node == NULL){
		q->rear_node = NULL;
    }
    free(temp_node);
    return thread;
}

int sthread_rwlock_init(sthread_rwlock_t *rwlock)
{
	//intializing the values for counter variable and flags
    rwlock->readers_count = 0;
    rwlock->writers_count = 0;
	//initializing the queue to null
    Queue_Initialization(&rwlock->writer_queue);
	Queue_Initialization(&rwlock->reader_queue);
	rwlock->waiting_writers = 0;
    return 0;
}

int sthread_rwlock_destroy(sthread_rwlock_t *rwlock)
{
	//freeing all the resources related to this structure
    while (Dequeue(&rwlock->reader_queue) != NULL);		//Freeing all remaining nodes left in the queue
    while (Dequeue(&rwlock->writer_queue) != NULL);
    return 0;
}

int sthread_read_lock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
	//In this, if current the lock is not held by writer and if there are no eaiting writers, then the reader are executed.
	//else, if the writers are waiting in the queue then the reader thread are queued and then the thread is suspended and wake up after the writer releases the lock.
    while (1) {
        if (rwlock->writers_count == 0 && rwlock->waiting_writers == 0) {
			printf("executing readers thread \n");
            rwlock->readers_count++;
            return 0;
        }
		//printf("lock aquired by writer thread,reader thread are queued \n");
        Queue_Enqueue(&rwlock->reader_queue, sthread_self());		//Reader thread is pushed into the queue.
        sthread_suspend();					//Thread is suspended
    }
	return 0;
}

//This function will try to aquire the lock by reader lock without blocking, where the lock is already held by writer thread.
int sthread_read_try_lock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
	//Here providing the writers priority.
	//rwwlock->writers_count >0 means this ensures that reader threads are blocked when the current active thread is writer.
	//rwlock->waiting_writers->0 means the reader threads are blocked, if there are any writers waiting for the lock, even if writer thread does not hold the lock.
	//This shows that we are giving the writer thread priority.
    if (rwlock->writers_count == 0 && rwlock->waiting_writers == 0) {
        rwlock->readers_count++;
		return 0;
    }
    return 1;
}

int sthread_read_unlock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
    rwlock->readers_count--;		//Decrementing the active readers.
	//After allthe readers completed execution, then if the writing waiting in the queue then the last executing reader thread will send a signal to wake up the first writer thread waiting in the queue.
    
	if (rwlock->readers_count == 0 && rwlock->waiting_writers > 0) {	//writer priority if there are any waiting writer thread, giving priority to execute them first.
        sthread_t next_writer = Dequeue(&rwlock->writer_queue);		//dequeue the waiting writer threads
        if (next_writer) {
            rwlock->writers_count++;
            rwlock->waiting_writers--;			//decrementing the waiting writer threads count. 
            sthread_wake(next_writer);			//waking up the writing thread to aquire the lock
        }
    }
    return 0;
}

int sthread_write_lock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
    rwlock->waiting_writers++;		//writer trying to aquire the lock..incrementing the waiting writer count intiailly
    while (1) {
		//chekcing for any active reader or writer, if not incrementing the writer count, and after executing the thread decrementting the waiting writers.
        if (rwlock->readers_count == 0 && rwlock->writers_count == 0) {
            rwlock->writers_count++;
			printf("executing writer thread \n");
            rwlock->waiting_writers--;
            return 0;
        }
		//If there are any active readers or writer then the writer thread is added into the queue and then it is suspended untill the lock is released.
        Queue_Enqueue(&rwlock->writer_queue, sthread_self());
        sthread_suspend();
    }
	return 0;
}

int sthread_write_try_lock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
	//writer thread tries to aquire the lock when there is no active read or write thread.
	//if aquired then incrementing the active writer count since it will be active.
    if (rwlock->readers_count == 0 && rwlock->writers_count == 0) {
        rwlock->writers_count++;
        return 0;
    }
    return 1;
}

int sthread_write_unlock(sthread_rwlock_t *rwlock)
{
	if(rwlock == NULL){
		return -1;
	}
    rwlock->writers_count--;
	//here in this givving priority to writer threads.
    if (rwlock->waiting_writers > 0) {
		//if there are waiting writer threads in the queue, that particular thread is removed form the queue and giving a signal to wake up to aquire the lock.
        sthread_t next_writer = Dequeue(&rwlock->writer_queue);
        if (next_writer) {
            rwlock->writers_count++;
            rwlock->waiting_writers--;
            sthread_wake(next_writer);
        }
    } else {
		//else waking up the reader thread by removing the threads form the queue..
		//Here in this we are allowing all the reader threads to aquire the lock and execute, so used while loop to allow.
		//but where as for waiting writer threads only oe thread from the queue is waked up to enter into critical section.
        while (rwlock->reader_queue.front_node) {
            sthread_t next_reader = Dequeue(&rwlock->reader_queue);
            rwlock->readers_count++;
            sthread_wake(next_reader);
        }
    }
    return 0;
}