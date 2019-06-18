///*
// * types used by thread library
// */
//#include <stdio.h>
//#include <stdlib.h>
//#include <ucontext.h>
//#include <sys/mman.h>
//#include <signal.h>
//#include <string.h>
//
//struct tcb {
//	int         thread_id;
//	int         thread_priority;
//	ucontext_t *thread_context;
//	struct tcb *next;
//};
//
//typedef struct tcb tcb;
//
//typedef struct tNode {
//	tcb *tcb;
//	struct tNode *nxt;
//}tNode;
//
//typedef struct queue {
//	struct tNode *head, *last;
//}queue;
//
//typedef struct sem_t {
//	int count;
//	queue *q;
//} sem_t;
//
//typedef struct msg {
//	char       *message;
//	int         length;
//	int sender;
//	int receiver;
//	struct msg *next;
//} msg;
//
//typedef struct {
//	struct msg *msgq;
//	sem_t *mutex;
//} mbox;
//
//tNode *createNode(tcb *);
//queue *init_queue();
//void insertNode(queue *, tcb *);
//tNode *getPrevNode(queue *q);