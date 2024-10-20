Group information:
Member 1: Samarendra Pitta - 2885323.
Member 2: Nishitha Ravella - 2885903.

Contribution distribution:

Samarendra Pitta - 50%
Nishitha Ravella - 50%

Project Description:

#This project implements multi threaded banking system with synchronizaion between Read-Write threads. 

#Multiple threads either read or write threads tries to aquire the lock at the same time. implemented multiple scenarios to provide synchronization between them inorder to avoid the race conditions between the shared resources.

#I have implemented like if multiple threads tries to aquire the lock either read or write, if already lock is held by another thread, then i implemented like the thread 
trying to aquire the lock is suspended and pushed into the waiting queue by suspending the threads. These threads are waked up when the lock is released.

#For suppose if the reader thread is currently holding the lock, then if both the reader or writer tries to aquire the lock, then the threads should be suspended
and waked up when the lock is released. These two operations would be executed in a single atomic step.

#This implementation does not have busy waiting, instead i suspended the thread and waked up when the lock is released.

#Case1:
If the reader thread is already in critical section, then if the reader thread comes and tries to aquire the lock. Then at this point I checked for any writer
thread waiting in the writer queue. If any thread present in writing queue, I have given the priority to writer threads to execute first. Else reader thread will enter into the critical section.

#case2: 
if multiple reader threads are active and are present in the critical section then if the writing thread is waiting in the waiitng queue, then I had implemented like 
last reader thread will send the signal to the first writer thread waiting in the queue to wake up to aquire the lock.

#case3:
only one writer thread will be executing in the critical section, where as multiple readers threads can enter into the critical section if and only if there are no waiting or active write threads.

#case4:
aquire the lock in read mode if lock is available otherwise block waiting untill the lock is released.


#How to run the program:

providing the make file, just go to the directory and then type "make" to compile the code.
"make test" - compiles the links and test program
"./test" - run the program
"make clean" - which cleans all the previous object and binary files.


#Test Cases:

#Below provided is the test case which impements synchronization between read and write threads.

#Inintially Reader thread "Thread 20" is executed for 5 iterations.

#Then "thread1" and "thread10" are executed simultaneously. Thread1 executes  writing the shared resource balance for 25 iterations(deposits), 
at that time another writer thread10 comes and it is queued into the writing queue. After completing the thread1 then the priority is given to writer thread10 to execute rather than reader thread.

#After executing writer thread10 then the system checks for any active or writer thread present int he queue. Then signal is sent to reader thread to aquire the lock.

#Here two writer threads are executing consequetively which determines "writer threads are given priority". In the same way "thread2" and "thread11" are executed consequetively
This shows the write threads are prioritzed.

sam_legion@LEGION:~/project2_final/sthread/sthread$ make
make: 'libsthread.a' is up to date.
sam_legion@LEGION:~/project2_final/sthread/sthread$ make test
make: 'test' is up to date.
sam_legion@LEGION:~/project2_final/sthread/sthread$ ./test
executing readers thread
thread20 ===> Reader thread iteration 0, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 1, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 2, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 3, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 4, balance = 10000
executing writer thread
thread1 ===> Deposit thread iteration 0
executing writer thread
thread1 ===> Deposit thread iteration 1
executing writer thread
thread1 ===> Deposit thread iteration 2
executing writer thread
thread1 ===> Deposit thread iteration 3
executing writer thread
thread1 ===> Deposit thread iteration 4
executing writer thread
thread1 ===> Deposit thread iteration 5
executing writer thread
thread1 ===> Deposit thread iteration 6
executing writer thread
thread1 ===> Deposit thread iteration 7
executing writer thread
thread1 ===> Deposit thread iteration 8
executing writer thread
thread1 ===> Deposit thread iteration 9
executing writer thread
thread1 ===> Deposit thread iteration 10
executing writer thread
thread1 ===> Deposit thread iteration 11
executing writer thread
thread1 ===> Deposit thread iteration 12
executing writer thread
thread1 ===> Deposit thread iteration 13
executing writer thread
thread1 ===> Deposit thread iteration 14
executing writer thread
thread1 ===> Deposit thread iteration 15
executing writer thread
thread1 ===> Deposit thread iteration 16
executing writer thread
thread1 ===> Deposit thread iteration 17
executing writer thread
thread1 ===> Deposit thread iteration 18
executing writer thread
thread1 ===> Deposit thread iteration 19
executing writer thread
thread1 ===> Deposit thread iteration 20
executing writer thread
thread1 ===> Deposit thread iteration 21
executing writer thread
thread1 ===> Deposit thread iteration 22
executing writer thread
thread1 ===> Deposit thread iteration 23
executing writer thread
thread1 ===> Deposit thread iteration 24
executing writer thread
thread10 ===> Withdrawal thread iteration 0
executing writer thread
thread10 ===> Withdrawal thread iteration 1
executing writer thread
thread10 ===> Withdrawal thread iteration 2
executing writer thread
thread10 ===> Withdrawal thread iteration 3
executing writer thread
thread10 ===> Withdrawal thread iteration 4
executing writer thread
thread10 ===> Withdrawal thread iteration 5
executing writer thread
thread10 ===> Withdrawal thread iteration 6
executing writer thread
thread10 ===> Withdrawal thread iteration 7
executing writer thread
thread10 ===> Withdrawal thread iteration 8
executing writer thread
thread10 ===> Withdrawal thread iteration 9
executing writer thread
thread10 ===> Withdrawal thread iteration 10
executing writer thread
thread10 ===> Withdrawal thread iteration 11
executing writer thread
thread10 ===> Withdrawal thread iteration 12
executing writer thread
thread10 ===> Withdrawal thread iteration 13
executing writer thread
thread10 ===> Withdrawal thread iteration 14
executing writer thread
thread10 ===> Withdrawal thread iteration 15
executing writer thread
thread10 ===> Withdrawal thread iteration 16
executing writer thread
thread10 ===> Withdrawal thread iteration 17
executing writer thread
thread10 ===> Withdrawal thread iteration 18
executing writer thread
thread10 ===> Withdrawal thread iteration 19
executing writer thread
thread10 ===> Withdrawal thread iteration 20
executing writer thread
thread10 ===> Withdrawal thread iteration 21
executing writer thread
thread10 ===> Withdrawal thread iteration 22
executing writer thread
thread10 ===> Withdrawal thread iteration 23
executing writer thread
thread10 ===> Withdrawal thread iteration 24
executing readers thread
thread21 ===> Reader thread iteration 0, balance = 10000
executing readers thread
thread21 ===> Reader thread iteration 1, balance = 10000
executing readers thread
thread21 ===> Reader thread iteration 2, balance = 10000
executing readers thread
thread21 ===> Reader thread iteration 3, balance = 10000
executing readers thread
thread21 ===> Reader thread iteration 4, balance = 10000
executing writer thread
thread2 ===> Deposit thread iteration 0
executing writer thread
thread2 ===> Deposit thread iteration 1
executing writer thread
thread2 ===> Deposit thread iteration 2
executing writer thread
thread2 ===> Deposit thread iteration 3
executing writer thread
thread2 ===> Deposit thread iteration 4
executing writer thread
thread2 ===> Deposit thread iteration 5
executing writer thread
thread2 ===> Deposit thread iteration 6
executing writer thread
thread2 ===> Deposit thread iteration 7
executing writer thread
thread2 ===> Deposit thread iteration 8
executing writer thread
thread2 ===> Deposit thread iteration 9
executing writer thread
thread2 ===> Deposit thread iteration 10
executing writer thread
thread2 ===> Deposit thread iteration 11
executing writer thread
thread2 ===> Deposit thread iteration 12
executing writer thread
thread2 ===> Deposit thread iteration 13
executing writer thread
thread2 ===> Deposit thread iteration 14
executing writer thread
thread2 ===> Deposit thread iteration 15
executing writer thread
thread2 ===> Deposit thread iteration 16
executing writer thread
thread2 ===> Deposit thread iteration 17
executing writer thread
thread2 ===> Deposit thread iteration 18
executing writer thread
thread2 ===> Deposit thread iteration 19
executing writer thread
thread2 ===> Deposit thread iteration 20
executing writer thread
thread2 ===> Deposit thread iteration 21
executing writer thread
thread2 ===> Deposit thread iteration 22
executing writer thread
thread2 ===> Deposit thread iteration 23
executing writer thread
thread2 ===> Deposit thread iteration 24
executing writer thread
thread11 ===> Withdrawal thread iteration 0
executing writer thread
thread11 ===> Withdrawal thread iteration 1
executing writer thread
thread11 ===> Withdrawal thread iteration 2
executing writer thread
thread11 ===> Withdrawal thread iteration 3
executing writer thread
thread11 ===> Withdrawal thread iteration 4
executing writer thread
thread11 ===> Withdrawal thread iteration 5
executing writer thread
thread11 ===> Withdrawal thread iteration 6
executing writer thread
thread11 ===> Withdrawal thread iteration 7
executing writer thread
thread11 ===> Withdrawal thread iteration 8
executing writer thread
thread11 ===> Withdrawal thread iteration 9
executing writer thread
thread11 ===> Withdrawal thread iteration 10
executing writer thread
thread11 ===> Withdrawal thread iteration 11
executing writer thread
thread11 ===> Withdrawal thread iteration 12
executing writer thread
thread11 ===> Withdrawal thread iteration 13
executing writer thread
thread11 ===> Withdrawal thread iteration 14
executing writer thread
thread11 ===> Withdrawal thread iteration 15
executing writer thread
thread11 ===> Withdrawal thread iteration 16
executing writer thread
thread11 ===> Withdrawal thread iteration 17
executing writer thread
thread11 ===> Withdrawal thread iteration 18
executing writer thread
thread11 ===> Withdrawal thread iteration 19
executing writer thread
thread11 ===> Withdrawal thread iteration 20
thread11 ===> Withdrawal thread iteration 20
executing readers thread
thread22 ===> Reader thread iteration 0, balance = 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004
the balnce is 10004


Test Case2 :
writer priority: another exmaple for writer priority
after thread1, thread 2 starts executing because writer thread is prioritized.
sam_legion@LEGION:~/group27_p2$ ./test
executing readers thread
thread20 ===> Reader thread iteration 0, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 1, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 2, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 3, balance = 10000
executing readers thread
thread20 ===> Reader thread iteration 4, balance = 10000
executing writer thread
thread1 ===> Deposit thread iteration 0
executing writer thread
thread1 ===> Deposit thread iteration 1
executing writer thread
thread1 ===> Deposit thread iteration 2
executing writer thread
thread1 ===> Deposit thread iteration 3
executing writer thread
thread1 ===> Deposit thread iteration 4
executing writer thread
thread1 ===> Deposit thread iteration 5
executing writer thread
thread1 ===> Deposit thread iteration 6
executing writer thread
thread1 ===> Deposit thread iteration 7
executing writer thread
thread1 ===> Deposit thread iteration 8
executing writer thread
thread1 ===> Deposit thread iteration 9
executing writer thread
thread1 ===> Deposit thread iteration 10
executing writer thread
thread1 ===> Deposit thread iteration 11
executing writer thread
thread1 ===> Deposit thread iteration 12
executing writer thread
thread1 ===> Deposit thread iteration 13
executing writer thread
thread1 ===> Deposit thread iteration 14
executing writer thread
thread1 ===> Deposit thread iteration 15
executing writer thread
thread1 ===> Deposit thread iteration 16
executing writer thread
thread1 ===> Deposit thread iteration 17
executing writer thread
thread1 ===> Deposit thread iteration 18
executing writer thread
thread1 ===> Deposit thread iteration 19
executing writer thread
thread1 ===> Deposit thread iteration 20
executing writer thread
thread1 ===> Deposit thread iteration 21
executing writer thread
thread1 ===> Deposit thread iteration 22
executing writer thread
thread1 ===> Deposit thread iteration 23
executing writer thread
thread1 ===> Deposit thread iteration 24
executing writer thread
thread2 ===> Deposit thread iteration 0
the balnce is 10026
the balnce is 10026

#Bonus:
I have implemented the bonus that is writer threads are prioritzed.

#Existing Bugs:
Every thing is implemented, No existing bugs.
Have implemented bonus point also.