//#include "t_lib.h"
//
//
//tcb *running;
//queue *ready;
//tcb *redy;
//
//void t_yield()
//{
//  tcb *tmp = running;
//  
//  
//  tNode *r = getPrevNode(ready);
//
//  running = r->tcb;
//  free(r);
//  insertNode(ready, tmp);
//  swapcontext(tmp->thread_context, running->thread_context);
//  
//  
//}
//
//void t_init()
//{
//  tcb *tmp;
//  ready = init_queue();
//
//  tmp = (tcb *) malloc(sizeof(tcb));
//  tmp->thread_id = 0;
//  tmp->thread_priority = 0;
//  tmp->thread_context = (ucontext_t *)malloc(sizeof(ucontext_t));
//  tmp->next = NULL;
//
//  getcontext(tmp->thread_context);    /* let tmp be the context of main() */
//  running = tmp;
//}
//
//int t_create(void (*fct)(int), int id, int pri)
//{
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
//  insertNode(ready, uc);
//}
//
//
//
//void t_shutdown()
//{
//
//	tcb *r = redy;
//	while (r) {
//		redy = redy->next;
//		free(r);
//		r = redy;
//	}
//
//}
//
//void t_terminate() {
//	tcb *uc = running;
//	tNode *tmp;
//
//
//	free(uc->thread_context->uc_stack.ss_sp);
//	free((ucontext_t *)malloc(sizeof(ucontext_t)));
//	free(uc);
//
//	tmp = getPrevNode(ready);
//	running = tmp->tcb;
//	free(tmp);
//
//	setcontext(running->thread_context);
//
//}
//
//tNode *createNode(tcb *tcb) {
//	tNode *tmp = (tNode*)malloc(sizeof(tNode));
//	tmp->tcb = tcb;
//	tmp->nxt = NULL;
//	return tmp;
//}
//
//queue *init_queue() {
//	queue *tmp = (queue*)malloc(sizeof(queue));
//	tmp->head = tmp->last = NULL;
//	return tmp;
//}
//
//tNode *getPrevNode(queue *q) {
//	if (q->head == NULL)
//	{
//		return NULL;
//	}
//
//	tNode *tmp = q->head;
//	q->head = q->head->nxt;
//
//	if (q->head == NULL)
//	{
//		q->last = NULL;
//	}
//
//	return tmp;
//}
//
//void insertNode(queue *q, tcb *tcb) {
//
//	tNode *tmp = createNode(tcb);
//	
//	if (q->last == NULL) {
//		q->head = q->last = tmp;
//		return;
//	}
//	
//	q->last->nxt = tmp;
//	q->last = tmp;
//}
//
//int sem_init(sem_t **sp, int sem_count)
//{
//	*sp = malloc(sizeof(sem_t));
//	(*sp)->count = sem_count;
//	(*sp)->q = init_queue();
//}
//
//void sem_wait(sem_t *s)
//{
//	sighold();
//	tcb *tmp = running;
//	s->count--;
//
//	if (s->count >= 0) {
//		sigrelse();
//	}
//	
//	else  {
//		
//		insertNode(s->q, tmp);
//
//		tNode *r = getPrevNode(ready);
//		running = r->tcb;
//		free(r);
//
//		swapcontext(tmp->thread_context, running->thread_context);
//		sigrelse();
//
//	}
//}
//
//void sem_signal(sem_t *s)
//{
//	sighold();
//	s->count++;
//
//	if (s->count > 0) {
//		sigrelse();
//	}
//	else {
//		tNode *rdy = getPrevNode(s->q);
//
//		insertNode(ready, rdy->tcb);
//
//		free(rdy);
//		sigrelse();
//
//	}
//}
//
//void sem_destroy(sem_t **s)
//{
//	tcb *tmp;
//	
//	tNode *t = (*s)->q->head;
//	tmp = t->tcb;
//	free(tmp->thread_context->uc_stack.ss_sp);
//	free(tmp->thread_context);
//	free(tmp);	
//	free(t);
//
//	t = t->nxt;
//	free((*s)->q);
//	free(*s);
//}
