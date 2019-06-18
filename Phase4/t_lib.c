//#include "t_lib.h"
//
//tcb *ready_head_0, *rhead, *main_c; 
//tcb *ready_head_1; 
//tcb *sem_queue_head; 
//tcb_m *mhead;
//tcb *running;
//
//
//
//struct messageNode *GetMsgNode(int len)
//{
//	struct messageNode *newMsg = (struct messageNode*)malloc(sizeof(struct messageNode));
//	newMsg->len = len;
//	newMsg->message = (char*)malloc(1024 * sizeof(char));
//	newMsg->sender = 0;
//	newMsg->receiver = 0;
//	newMsg->next = NULL;
//	return newMsg;
//}
//
//tcb* GetNewNode(int pri)
//{
//	size_t sz = 0x10000;
//	tcb* newNode = (tcb*)malloc(sizeof(tcb));
//	newNode->thread_priority = pri;
//	newNode->buffer = GetMsgNode(0);
//	getcontext(&newNode->thread_context); 
//	newNode->thread_context.uc_stack.ss_sp = malloc(sz);  
//	newNode->thread_context.uc_stack.ss_size = sz;
//	newNode->thread_context.uc_stack.ss_flags = 0;
//	newNode->thread_context.uc_link = 0;	
//	sem_init(&(newNode->msg_sem), 1);
//	newNode->next = NULL;
//	return newNode;
//}
//
//tcb_m* GetNewMonitorNode(int id)
//{
//	tcb_m* newMonitorNode = (tcb_m*)malloc(sizeof(tcb_m));
//	newMonitorNode->tid = id;
//	newMonitorNode->loc = NULL;
//	newMonitorNode->next = NULL;
//
//	return newMonitorNode;
//}
//
//
//
//void handler(int sig)
//{
//
//	scheduler();
//
//}
//
//void scheduler()
//{
//
//	tcb* tmp0 = ready_head_0;
//	tcb* tmp1 = ready_head_1;
//	tcb* last_running = rhead;
//	if (last_running->thread_priority == 0)
//	{
//		if (ready_head_0 == NULL)
//		{
//			return;
//		}
//		else
//		{
//			if (ready_head_0->next == NULL)
//			{
//				tmp0 = ready_head_0;
//				ready_head_0 = rhead;
//				rhead = tmp0;
//			}
//			else
//			{
//				tmp0 = ready_head_0;
//				last_running = rhead;
//				while (tmp0->next != NULL)
//					tmp0 = tmp0->next;	
//				tmp0->next = last_running;
//				rhead->next = NULL;
//				rhead = ready_head_0;
//				ready_head_0 = ready_head_0->next;
//				rhead->next = NULL;
//
//			}
//		}
//
//		swapcontext(&last_running->thread_context, &rhead->thread_context);
//	}
//	else 
//		if (ready_head_0 == NULL)
//		{
//			if (tmp1 == NULL)
//			{
//				tmp1 = last_running;
//				last_running->next = NULL;
//				rhead = tmp1;
//				rhead->next = NULL;
//				if (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//			}
//			else
//			{
//				while (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//				tmp1->next = last_running;
//				last_running->next = NULL;
//				rhead = ready_head_1;
//				if (ready_head_1->next != NULL)
//					ready_head_1 = ready_head_1->next;
//			}
//		}
//		else
//		{
//			
//			if (tmp1 == NULL)
//			{
//				tmp1 = last_running;
//				last_running->next = NULL;
//				rhead = tmp0;
//
//				if (ready_head_0->next != NULL)
//					ready_head_0 = ready_head_0->next;
//				else
//					ready_head_0 = NULL;
//				rhead->next = NULL;
//			}
//			else
//			{
//				while (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//				tmp1->next = last_running;
//				last_running->next = NULL;
//				rhead = ready_head_0;
//				if (ready_head_0->next != NULL)
//					ready_head_0 = ready_head_0->next;
//				else
//					ready_head_0 = NULL;
//			}
//		}
//
//		swapcontext(&last_running->thread_context, &rhead->thread_context);
//	
//
//}
//
//void InsertAtTail_0(tcb* newNode)
//{
//	tcb* temp = ready_head_0;
//	if (ready_head_0 == NULL)
//	{
//		ready_head_0 = newNode;
//		return;
//	}
//	while (temp->next != NULL)
//		temp = temp->next; 
//	temp->next = newNode;
//}
//
//void InsertAtTail_1(tcb* newNode)
//{
//	tcb* temp = ready_head_1;
//	if (ready_head_1 == NULL)
//	{
//		ready_head_1 = newNode;
//		return;
//	}
//	while (temp->next != NULL)
//		temp = temp->next; 
//	temp->next = newNode;
//}
//
//
//void t_init()
//{
//	signal(SIGALRM, scheduler);
//
//	main_c = (tcb *)malloc(sizeof(tcb));
//	tcb_m* temp = GetNewMonitorNode(0);
//
//	getcontext(&(main_c->thread_context));
//	main_c->thread_priority = 1;
//
//	
//	temp->loc = main_c;
//	temp->tid = 0;
//	temp->next = NULL;
//
//	mhead = temp;
//	rhead = main_c;
//}
//
//
//
//int t_create(void(*fct)(int), int id, int pri)
//{
//
//	tcb_m *temp1 = GetNewMonitorNode(id);
//	tcb_m* temp2 = mhead;
//
//	tcb *temp = GetNewNode(pri);
//
//	temp->thread_id = id;
//	makecontext(&temp->thread_context, (void(*) (void))fct, 1, id);
//
//	
//	while (temp2->next != NULL)
//		temp2 = temp2->next;
//
//	temp1->loc = temp;
//	temp1->tid = temp->thread_id;
//	temp1->next = NULL;
//
//	temp2->next = temp1;
//
//	
//	if (pri == 0)
//		InsertAtTail_0(temp);
//	else
//		InsertAtTail_1(temp);
//
//}
//
//
//void t_yield()
//{
//
//	tcb* tmp0 = ready_head_0;
//	tcb* tmp1 = ready_head_1;
//	tcb* last_running = rhead;
//
//	if (last_running->thread_priority == 0) 
//	{
//		if (ready_head_0 == NULL)
//		{
//			
//			return;
//		}
//		else
//		{
//			
//			if (ready_head_0->next == NULL)
//			{
//				
//				tmp0 = ready_head_0;
//				ready_head_0 = rhead;
//				rhead = tmp0;
//				
//			}
//			else
//			{
//				
//				tmp0 = ready_head_0;
//				last_running = rhead;
//				while (tmp0->next != NULL)
//					tmp0 = tmp0->next;	
//				tmp0->next = last_running;
//				rhead->next = NULL;
//				rhead = ready_head_0;
//				ready_head_0 = ready_head_0->next;
//				rhead->next = NULL;
//
//				
//			}
//		}
//	}
//	else 
//	{
//		if (ready_head_0 == NULL)
//		{
//			
//			if (tmp1 == NULL)
//			{
//				tmp1 = last_running;
//				last_running->next = NULL;
//				rhead = tmp1;
//				rhead->next = NULL;
//				if (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//			}
//			else
//			{
//				while (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//
//				tmp1->next = last_running;
//				last_running->next = NULL;
//				rhead = ready_head_1;
//
//				if (ready_head_1->next != NULL)
//					ready_head_1 = ready_head_1->next;
//			}
//		}
//		else
//		{
//			
//			if (tmp1 == NULL)
//			{
//				tmp1 = last_running;
//				last_running->next = NULL;
//				rhead = tmp0;
//
//				if (ready_head_0->next != NULL)
//					ready_head_0 = ready_head_0->next;
//				else
//					ready_head_0 = NULL;
//				rhead->next = NULL;
//			}
//			else
//			{
//				while (tmp1->next != NULL)
//					tmp1 = tmp1->next;
//				tmp1->next = last_running;
//				last_running->next = NULL;
//				rhead = ready_head_0;
//				if (ready_head_0->next != NULL)
//					ready_head_0 = ready_head_0->next;
//				else
//					ready_head_0 = NULL;
//			}
//		}
//		swapcontext(&last_running->thread_context, &rhead->thread_context);
//	}
//}
//
//
//void t_terminate()
//{
//	tcb *temp1 = rhead, *tmp0 = ready_head_0, *tmp1 = ready_head_1;
//	int pri = rhead->thread_priority;
//
//
//	if (ready_head_0 != NULL)
//	{
//		rhead = ready_head_0;
//		if (ready_head_0->next != NULL)
//			ready_head_0 = ready_head_0->next;
//		else
//			ready_head_0 = NULL;
//	}
//	else
//	{
//		rhead = ready_head_1;
//		if (ready_head_1->next != NULL)
//			ready_head_1 = ready_head_1->next;
//		else
//			ready_head_1 = NULL;
//	}
//	free(temp1);
//	setcontext(&rhead->thread_context);
//}
//
//void t_shutdown()
//{
//
//	tcb* temp1 = ready_head_0;
//	rhead = NULL;
//	free(rhead);
//	if (ready_head_0 != NULL)
//	{
//		while (ready_head_0->next != NULL)
//		{
//			ready_head_0 = ready_head_0->next;
//			free(temp1);
//			temp1 = ready_head_0;
//		}
//		free(ready_head_0);
//	}
//	temp1 = ready_head_1;
//	if (ready_head_1 != NULL)
//	{
//		while (ready_head_1->next != NULL)
//		{
//			ready_head_1 = ready_head_1->next;
//			free(temp1);
//			temp1 = ready_head_1;
//		}
//		free(ready_head_1);
//	}
//
//}
//
//
//
//int sem_init(sem_t **sp, int sem_count)
//{
//
//	*sp = malloc(sizeof(sem_t));
//	(*sp)->count = sem_count;
//	(*sp)->q = NULL;
//
//}
//
//
//void sem_wait(sem_t *s)
//{
//
//	tcb *stmp = s->q;
//	tcb *last_running = rhead;
//	tcb *tmp1 = ready_head_1;
//	tcb *tmp0 = ready_head_0;
//	s->count = s->count - 1;
//	if (s->count < 0)
//	{
//		if (s->q == NULL)
//		{
//			s->q = rhead;
//			s->q->next = NULL;
//		}
//		else
//		{
//			while (stmp->next != NULL)
//				stmp = stmp->next;
//			stmp->next = rhead;
//			last_running->next = NULL;
//		}
//	
//
//		if (ready_head_0 != NULL)
//		{
//		
//			rhead = ready_head_0;
//			ready_head_0 = ready_head_0->next;
//			rhead->next = NULL;
//		}
//		else	
//		{
//			
//			if (ready_head_1 != 0)
//			{
//				rhead = ready_head_1;
//				ready_head_1 = ready_head_1->next;
//				rhead->next = NULL;
//			}
//			
//		}
//	}
//	
//	swapcontext(&last_running->thread_context, &rhead->thread_context);
//}
//
//void sem_signal(sem_t *s)
//{
//
//	tcb *stmp = s->q;
//	tcb *last_running = rhead;
//	tcb *tmp1 = ready_head_1;
//	tcb *tmp0 = ready_head_0;
//	s->count = s->count + 1;
//	if (s->count <= 0)
//	{
//
//		if (s->q->thread_priority == 0)
//		{
//			while (tmp0->next != NULL)
//				tmp0 = tmp0->next;	
//			tmp0->next = stmp;		
//			if (s->q->next != NULL)
//				s->q = s->q->next;
//			stmp->next = NULL;
//		}
//		else
//		{
//			while (tmp1->next != NULL)
//				tmp1 = tmp1->next;	
//			tmp1->next = stmp;		
//			if (s->q->next != NULL)
//				s->q = s->q->next;
//			stmp->next = NULL;
//		}
//	}
//	
//	
//	sigrelse(SIGALRM);
//}
//
//
//void sem_destroy(sem_t **s)
//{
//	free(*s);
//}
//
//
//
//int mbox_create(mbox **mb)
//{
//	*mb = malloc(sizeof(mbox));
//	sem_init(&(*mb)->mbox_sem, 1);
//	(*mb)->msg = NULL;
//}
//
//
//void mbox_destroy(mbox **mb)
//{
//	sem_destroy(&(*mb)->mbox_sem);
//	free(*mb);
//}
//
//
//
//
//void mbox_withdraw(mbox *mb, char *msg, int *len)
//{
//	
//	struct messageNode *temp;
//	temp = mb->msg;
//
//	char *msgg = malloc(1024);
//
//
//	sem_wait(mb->mbox_sem);
//	
//	strcpy(msgg, temp->message);
//	*len = temp->len;
//	strcpy(msg, msgg);
//
//	if (mb->msg->next != NULL)
//		mb->msg = mb->msg->next;
//
//	
//	sem_signal(mb->mbox_sem);
//}
//void mbox_deposit(mbox *mb, char *msg, int len)
//{
//	struct messageNode *temp, *temp1;
//	char *msgg = malloc(1024);
//
//	int a = len;
//
//	strcpy(msgg, msg);
//
//	temp1 = mb->msg;
//
//	sem_wait(mb->mbox_sem);
//	if (mb->msg == NULL)
//	{
//		mb->msg = GetMsgNode(len);
//		strcpy(mb->msg->message, msgg);
//		mb->msg->len = a;
//		mb->msg->next = NULL;
//	}
//	else
//	{
//		temp = GetMsgNode(len);
//
//		strcpy(temp->message, msgg);
//		temp->len = a;
//		temp->next = NULL;
//
//		while (temp1->next != NULL)
//			temp1 = temp1->next;
//
//		temp1->next = temp;
//
//	}
//
//	sem_signal(mb->mbox_sem);
//
//}
//
//
//
//void receive(int *tid, char *msg, int *len)
//{
//	
//	tcb_m *temp = mhead;
//	tcb *temp1;
//	
//
//	char *msgg = malloc(1024);
//
//	
//	while (temp != NULL)   
//	{
//		if (temp->tid == rhead->thread_id)
//		{
//			temp1 = temp->loc;    
//
//			if (temp1->buffer->next == NULL)
//			{
//				*len = 0;
//				*tid = 0;
//				return;
//			}
//			else if (*tid == 0)
//			{
//				
//				sem_wait(temp1->msg_sem);
//				
//				*len = temp1->buffer->next->len;
//				*tid = temp1->buffer->next->sender;
//				strcpy(msg, temp1->buffer->next->message);
//				
//				sem_signal(temp1->msg_sem);
//
//				if (temp1->buffer->next != NULL)
//					temp1->buffer = temp1->buffer->next;
//
//				strcpy(msg, msgg);
//				return;
//			}
//			else
//			{
//				while (temp1->buffer->next->next != NULL)
//				{
//					if (*tid == temp1->buffer->next->sender)
//					{
//						
//						sem_wait(temp1->msg_sem);
//						
//						*len = temp1->buffer->next->len;
//						strcpy(msg, temp1->buffer->next->message);
//						
//						sem_signal(temp1->msg_sem);
//
//						if (temp1->buffer->next != NULL)
//							temp1->buffer = temp1->buffer->next;
//
//						strcpy(msg, msgg);
//						return;
//
//					}
//					else
//					{
//						temp1->buffer->next = temp1->buffer->next->next;
//					}
//
//				}
//				return;
//			}
//		}
//		else   
//		{
//			temp = temp->next;      
//		}
//	}
//}
//
//void send(int tid, char *msg, int len)
//{
//	tcb_m *temp = mhead;
//	tcb *temp1;
//	struct messageNode *temp2;
//	struct messageNode *node = GetMsgNode(len);
//
//	char *msgg = malloc(1024);
//	strcpy(msgg, msg);
//
//	
//	while (temp != NULL)
//	{
//		if (temp->tid == tid)
//		{
//			temp1 = temp->loc;     
//
//			
//			temp2 = temp1->buffer;      
//
//			strcpy(node->message, msg);
//			node->len = len;
//			node->receiver = tid;
//			node->sender = rhead->thread_id;
//			node->next = NULL;
//
//			if (temp2->message == NULL)
//			{
//				
//				sem_wait(temp1->msg_sem);
//				
//				temp2 = node;
//			
//				sem_signal(temp1->msg_sem);
//			}
//			else
//			{
//				while (temp2->next != NULL)
//					temp2 = temp2->next;
//
//				
//				sem_wait(temp1->msg_sem);
//			
//				temp2->next = node;
//				
//				sem_signal(temp1->msg_sem);
//
//				break;
//			}
//		}
//		else
//		{
//			if (temp->next != NULL)
//				temp = temp->next;
//		}
//	}
//}