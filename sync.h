/*
 * NAME, etc.
 *
 * sync.h
 */

#ifndef _STHREAD_SYNC_H_
#define _STHREAD_SYNC_H_
#include "sthread.h"

//Defining the queue structure
typedef struct queue_node {
    sthread_t thread;
    struct queue_node *next;
} queue_node_t;

typedef struct {
    queue_node_t *front_node;
    queue_node_t *rear_node;
} queue_t;

//The Structure for Read-Write lock implementation
typedef struct sthread_rwlock_struct {
    volatile unsigned long lock;  // lock for protecting shared data
    int waiting_writers;          // indicates number of waiting writers in the queue
    queue_t reader_queue;         // Queue for readers
    queue_t writer_queue;         // queue for writers
	int readers_count;                  // Displays number of active readers in the critical section
    int writers_count;                  // number of active writer that is 0 or 1. BCZ we allow only one writer thread to access the shared resource right
} sthread_rwlock_t;

typedef struct sthread_rwlock_struct sthread_rwlock_t;

int sthread_rwlock_init(sthread_rwlock_t *rwlock);
int sthread_rwlock_destroy(sthread_rwlock_t *rwlock);
int sthread_read_lock(sthread_rwlock_t *rwlock);
int sthread_read_try_lock(sthread_rwlock_t *rwlock);
int sthread_read_unlock(sthread_rwlock_t *rwlock);
int sthread_write_lock(sthread_rwlock_t *rwlock);
int sthread_write_try_lock(sthread_rwlock_t *rwlock);
int sthread_write_unlock(sthread_rwlock_t *rwlock);

#endif
