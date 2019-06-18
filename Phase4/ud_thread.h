///*
// * thread library function prototypes
// */
//typedef void sem_t;  // for semaphore
//typedef void mbox;   // for mailbox
//
//struct messageNode *GetMsgNode(int len);
//struct tcb* GetNewNode(int pri);
//struct tcb_m* GetNewMonitorNode(int id);
//void handler(int sig);
//void scheduler();
//void t_init();
//int t_create(void(*fct)(int), int id, int pri);
//void t_yield();
//void t_terminate();
//void t_shutdown();
//int sem_init(sem_t **sp, int sem_count);
//void sem_wait(sem_t *s);
//void sem_signal(sem_t *s);
//void sem_destroy(sem_t **s);
//int mbox_create(mbox **mb);
//void mbox_destroy(mbox **mb);
//void mbox_withdraw(mbox *mb, char *msg, int *len);
//void mbox_deposit(mbox *mb, char *msg, int len);
//void receive(int *tid, char *msg, int *len);
//void send(int tid, char *msg, int len);
