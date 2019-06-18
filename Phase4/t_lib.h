///*
// * types used by thread library
// */
//#include <stdio.h>
//#include <stdlib.h>
//#include <ucontext.h>
//#include <signal.h>
//#include <sys/mman.h>
//#include <string.h>
//
//
//struct tcb {
//	int         thread_id;
//	int         thread_priority;
//	ucontext_t  thread_context;
//	struct messageNode *buffer;
//	struct tcb *next;
//	struct sem_t *msg_sem;
//};
//
//typedef struct tcb tcb;
//
//typedef struct {
//	int count;
//	tcb *q;
//} sem_t;
//
//struct messageNode {
//	char *message;     // copy of the message 
//	int  len;          // length of the message 
//	int  sender;       // TID of sender thread 
//	int  receiver;     // TID of receiver thread 
//	struct messageNode *next; // pointer to next node 
//};
//
//typedef struct {
//	struct messageNode  *msg;       // message queue
//	sem_t               *mbox_sem;
//} mbox;
//
//struct tcb_m {
//	int tid; // tid of the tcb to point to
//	tcb *loc;
//	struct tcb_m *next;
//};
//
//typedef struct tcb_m tcb_m;
//
//
