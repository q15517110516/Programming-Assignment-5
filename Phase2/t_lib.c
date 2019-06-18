//#include "t_lib.h"
//#include "signal.h"
//
//
//
//tcb *running;
//tcb *ready;
//tcb *tail;
//
//void handler(int);
//
//void handler(int sig) {
//	t_yield();
//}
//
//
//void t_yield()
//{
//	sighold(SIGALRM);
//	ualarm(0, 0);
//	tcb *tmp;
//  
//  tmp = running;
//  insert(tmp);
//
//  tcb *r = ready;
//  ready = ready->next;
//  r->next = NULL;
//  running = r;
//  ualarm(1, 0);
//  signal(SIGALRM, handler);
//
//  swapcontext(tmp->thread_context, r->thread_context);
//  sigrelse(SIGALRM);
//
//}
//
//
//void t_init()
//{
//	ready = NULL;
//  tcb *tmp;
//  
//
//  tmp = (tcb *) malloc(sizeof(tcb));
//  tmp->thread_id = 0;
//  tmp->thread_priority = 1;
//  tmp->thread_context = (ucontext_t *)malloc(sizeof(ucontext_t));
//  tmp->next = NULL;
//
//  getcontext(tmp->thread_context);    /* let tmp be the context of main() */
//  running = tmp;
//  signal(SIGALRM, handler);
//  ualarm(1,0);
//
//}
//
//int t_create(void (*fct)(int), int id, int pri)
//{
//	sighold(SIGALRM);
//  size_t sz = 0x10000;
//
//  tcb *uc;
//  uc = (tcb *) malloc(sizeof(tcb));
//
//  uc->thread_id = id;
//  uc->thread_priority = pri;
//  uc->next = NULL;
//  uc->thread_context = (ucontext_t *)malloc(sizeof(ucontext_t));
//
//  getcontext(uc->thread_context);
//
//  uc->uc_stack.ss_sp = mmap(0, sz,
//       PROT_READ | PROT_WRITE | PROT_EXEC,
//       MAP_PRIVATE | MAP_ANON, -1, 0);
//
//  uc->thread_context->uc_stack.ss_sp = malloc(sz);  /* new statement */
//  uc->thread_context->uc_stack.ss_size = sz;
//  uc->thread_context->uc_stack.ss_flags = 0;
//  uc->thread_context->uc_link = running->thread_context;
//  makecontext(uc->thread_context, (void (*)(void)) fct, 1, id);
//  
//  insert(uc);
//  sigrelse(SIGALRM);
//}
//
//void insert(tcb *uc)
//{
//	if (ready == NULL) {
//		ready = tail = uc;
//
//	}
//	else {
//		tail->next = uc;
//		tail = uc;
//		if (uc->thread_priority < ready->thread_priority) {
//			uc->next = ready;
//			ready = uc;
//
//		}
//		else {
//			tcb *tmp = ready;
//			while (tmp->next != NULL && tmp->next->thread_priority <= uc->thread_priority) {
//				tmp = tmp->next;
//
//
//			}
//			uc->next = tmp->next;
//			tmp->next = uc;
//
//		} 
//	}
//}
//
//void t_shutdown()
//{
//	tcb *r = ready;
//	while (r) {
//		ready = ready->next;
//		free(r);
//		r = ready;
//	}
//}
//
//void t_terminate() {
//	running = ready;
//	ready = ready->next;
//	running->next = NULL;
//	setcontext(running->thread_context);
//}