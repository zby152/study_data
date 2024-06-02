
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

struct checkSum{
        char name[0x30];
        int checkValue;


};
struct checkSum checksum_table[0x100];
int check(char *filename);
int hash(const char *name, int length)
{
  unsigned int v2;
  int i;

  v2 = 1377;
  for ( i = 0; i < length; ++i )
    v2 = name[i] + 17 * v2;
  return v2;
}
int debug = 0;

/*****************************************************************************
 *                               kernel_main
 *****************************************************************************/
/**
 * jmp from kernel.asm::_start. 
 * 
 *****************************************************************************/
PUBLIC int kernel_main()
{
	disp_str("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	int i, j, eflags, prio;
        u8  rpl;
        u8  priv; /* privilege */

	struct task * t;
	struct proc * p = proc_table;

	char * stk = task_stack + STACK_SIZE_TOTAL;

	for (i = 0; i < NR_TASKS + NR_PROCS; i++,p++,t++) {
		if (i >= NR_TASKS + NR_NATIVE_PROCS) {
			p->p_flags = FREE_SLOT;
			continue;
		}

	        if (i < NR_TASKS) {     /* TASK */
                        t	= task_table + i;
                        priv	= PRIVILEGE_TASK;
                        rpl     = RPL_TASK;
                        eflags  = 0x1202;/* IF=1, IOPL=1, bit 2 is always 1 */
			prio    = 15;
                }
                else {                  /* USER PROC */
                        t	= user_proc_table + (i - NR_TASKS);
                        priv	= PRIVILEGE_USER;
                        rpl     = RPL_USER;
                        eflags  = 0x202;	/* IF=1, bit 2 is always 1 */
			prio    = 5;
                }

		strcpy(p->name, t->name);	/* name of the process */
		p->p_parent = NO_TASK;

		if (strcmp(t->name, "INIT") != 0) {
			p->ldts[INDEX_LDT_C]  = gdt[SELECTOR_KERNEL_CS >> 3];
			p->ldts[INDEX_LDT_RW] = gdt[SELECTOR_KERNEL_DS >> 3];

			/* change the DPLs */
			p->ldts[INDEX_LDT_C].attr1  = DA_C   | priv << 5;
			p->ldts[INDEX_LDT_RW].attr1 = DA_DRW | priv << 5;
		}
		else {		/* INIT process */
			unsigned int k_base;
			unsigned int k_limit;
			int ret = get_kernel_map(&k_base, &k_limit);
			assert(ret == 0);
			init_desc(&p->ldts[INDEX_LDT_C],
				  0, /* bytes before the entry point
				      * are useless (wasted) for the
				      * INIT process, doesn't matter
				      */
				  (k_base + k_limit) >> LIMIT_4K_SHIFT,
				  DA_32 | DA_LIMIT_4K | DA_C | priv << 5);

			init_desc(&p->ldts[INDEX_LDT_RW],
				  0, /* bytes before the entry point
				      * are useless (wasted) for the
				      * INIT process, doesn't matter
				      */
				  (k_base + k_limit) >> LIMIT_4K_SHIFT,
				  DA_32 | DA_LIMIT_4K | DA_DRW | priv << 5);
		}

		p->regs.cs = INDEX_LDT_C << 3 |	SA_TIL | rpl;
		p->regs.ds =
			p->regs.es =
			p->regs.fs =
			p->regs.ss = INDEX_LDT_RW << 3 | SA_TIL | rpl;
		p->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;
		p->regs.eip	= (u32)t->initial_eip;
		p->regs.esp	= (u32)stk;
		p->regs.eflags	= eflags;

		p->ticks = p->priority = prio;

		p->p_flags = 0;
		p->p_msg = 0;
		p->p_recvfrom = NO_TASK;
		p->p_sendto = NO_TASK;
		p->has_int_msg = 0;
		p->q_sending = 0;
		p->next_sending = 0;
		p->pid=i;
		for (j = 0; j < NR_FILES; j++)
			p->filp[j] = 0;

		stk -= t->stacksize;
	}

	k_reenter = 0;
	ticks = 0;

	p_proc_ready	= proc_table;

	init_clock();
        init_keyboard();

	restart();

	while(1){}
}


/*****************************************************************************
 *                                get_ticks
 *****************************************************************************/
PUBLIC int get_ticks()
{
	MESSAGE msg;
	reset_msg(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, TASK_SYS, &msg);
	return msg.RETVAL;
}


/**
 * @struct posix_tar_header
 * Borrowed from GNU `tar'
 */
struct posix_tar_header
{				/* byte offset */
	char name[100];		/*   0 */
	char mode[8];		/* 100 */
	char uid[8];		/* 108 */
	char gid[8];		/* 116 */
	char size[12];		/* 124 */
	char mtime[12];		/* 136 */
	char chksum[8];		/* 148 */
	char typeflag;		/* 156 */
	char linkname[100];	/* 157 */
	char magic[6];		/* 257 */
	char version[2];	/* 263 */
	char uname[32];		/* 265 */
	char gname[32];		/* 297 */
	char devmajor[8];	/* 329 */
	char devminor[8];	/* 337 */
	char prefix[155];	/* 345 */
	/* 500 */
};

/*****************************************************************************
 *                                untar
 *****************************************************************************/
/**
 * Extract the tar file and store them.
 * 
 * @param filename The tar file.
 *****************************************************************************/
void untar(const char * filename)
{	
	printf("[extract `%s'\n", filename);
	int fd = open(filename, O_RDWR);
	assert(fd != -1);

	char buf[SECTOR_SIZE * 16];
	int chunk = sizeof(buf);
	int i = 0;
	int bytes = 0;

	while (1) {
		bytes = read(fd, buf, SECTOR_SIZE);
		assert(bytes == SECTOR_SIZE); /* size of a TAR file
					       * must be multiple of 512
					       */
		if (buf[0] == 0) {
			if (i == 0)
				printf("    need not unpack the file.\n");
			break;
		}
		i++;

		struct posix_tar_header * phdr = (struct posix_tar_header *)buf;

		/* calculate the file size */
		char * p = phdr->size;
		int f_len = 0;
		while (*p)
			f_len = (f_len * 8) + (*p++ - '0'); /* octal */

		int bytes_left = f_len;
		int fdout = open(phdr->name, O_CREAT | O_RDWR | O_TRUNC);
		if (fdout == -1) {
			printf("    failed to extract file: %s\n", phdr->name);
			printf(" aborted]\n");
			close(fd);
			return;
		}
		printf("    %s\n", phdr->name);
		while (bytes_left) {
			int iobytes = min(chunk, bytes_left);
			read(fd, buf,
			     ((iobytes - 1) / SECTOR_SIZE + 1) * SECTOR_SIZE);
			bytes = write(fdout, buf, iobytes);
			assert(bytes == iobytes);
			bytes_left -= iobytes;
		}
		close(fdout);
	}

	if (i) {
		lseek(fd, 0, SEEK_SET);
		buf[0] = 0;
		bytes = write(fd, buf, 1);
		assert(bytes == 1);
	}

	close(fd);

	printf(" done, %d files extracted]\n", i);
}

/*****************************************************************************
 *                                shabby_shell
 *****************************************************************************/
/**
 * A very very simple shell.
 * 
 * @param tty_name  TTY file name.
 *****************************************************************************/
void shabby_shell(const char * tty_name)
{
	int fd_stdin  = open(tty_name, O_RDWR);
	assert(fd_stdin  == 0);
	int fd_stdout = open(tty_name, O_RDWR);
	assert(fd_stdout == 1);

	char rdbuf[1024];

	while (1) {
		write(1, "$ ", 2);
		//printf("%d-->",p_proc_ready->pid);
		int r = read(0, rdbuf, 1024);
		rdbuf[r] = 0;

		int argc = 0;
		char * argv[PROC_ORIGIN_STACK];
		char * p = rdbuf;
		char * s;
		int word = 0;
		char ch;
		do {
			ch = *p;
			if (*p != ' ' && *p != 0 && !word) {
				s = p;
				word = 1;
			}
			if ((*p == ' ' || *p == 0) && word) {
				word = 0;
				argv[argc++] = s;
				*p = 0;
			}
			p++;
		} while(ch);
		argv[argc] = 0;
		
		// int fd = open(argv[0], O_RDWR);
		
		// //printf("open@: %s\nfd == %d\n", argv[0], fd);
		// if (fd == -1) {
		// 	if (rdbuf[0]) {
		// 		write(1, "{", 1);
		// 		write(1, rdbuf, r);
		// 		write(1, "}\n", 2);
		// 	}
		// }
		// else {
		// 	close(fd);
		// 	int pid = fork();
		// 	if (pid != 0) { /* parent */
		// 		int s;
		// 		wait(&s);
		// 	}
		// 	else {	/* child */
		// 		//int check_sum = check(argv[0]);
		// 		//if(debug) printf("check_sum : %d\n", check_sum);
		// 		//if(check_sum == 1 )execv(argv[0], argv);
		// 		//else printf("========= checksum error! ========\n");
		// 		execv(argv[0], argv);
				
		// 	}
		// }

		//Use the 1k space storage command
		char* commands[5][32];
		int command_no = 1;
		int command_pointer = 0;	
		int error_commands[32];
		int error_num=0;
		int correct_commands[32];
		int correct_num=0;		
		int choice=1;
		for (int i = 0; i < argc; i++) 
		{	
			if (strcmp(argv[i], "&")) 
			{	
			//If it's not &, store that string as a command	
				commands[command_no - 1][command_pointer++] = argv[i];	
			} 
			else {	
			//Add 0 to the end of the command to identify the end of the command	
				commands[command_no - 1][command_pointer] = 0;		
				command_no++;	
				command_pointer = 0;		
			}	
		}	
			
		//printf("-------------");
		int pid = -1;		
		for (int i = 0; i < command_no; i++) 
		{	
			int fd = open(commands[i][0], O_RDWR);	
			if (fd == -1) 
			{	
				error_commands[error_num++]=i;	
				//printf("-------------");
				continue;
			}
			else {
				correct_commands[correct_num++]=i;
			}	
			close(fd);	
		}
		//Stores the PID of the child process
		int children_pid[correct_num];
		if(choice == 0){
		int child_no=0;
		for(child_no=0; child_no < correct_num; child_no++)
		{
		//Just fork in the main function, not in the child process
		//Prevent fork nesting
			pid=fork();
			if(pid == 0)	
				break;
			children_pid[child_no]=pid;

		}
		if(pid != 0)
		{
			for(int i=0; i<correct_num; i++) 
			{
				while(proc_table[children_pid[i]].p_flags != 1) {};
				proc_table[children_pid[i]].p_flags = 0;
				unblock(&proc_table[children_pid[i]]);
				//printf("------a\n");
			}
			//printf("------b\n");
			for(int i=0; i<correct_num; i++) 
			{	
				int s;
				wait(&s);
			}
		}else if(pid == 0){
			int j=correct_commands[child_no];
			int childpid=getpid();
			//p_proc_ready->p_flags = 1;
			proc_table[childpid].p_flags = 1;
			block(&proc_table[childpid]);
			//printf("<--%d",childpid);
			//proc_table[childpid].p_flags = 1;
			//printf("\n%d++++++++\n",proc_table[childpid].p_flags);
			//proc_table[childpid].p_flags = 1;
			//printf("%d--------B",childpid);
			//block(proc_table+childpid);
			execv(commands[j][0], commands[j]);
		}	
		}else if (choice == 1){
		int child_no=0;
		for(child_no=0; child_no < correct_num; child_no++)
		{
		//Just fork in the main function, not in the child process
		//Prevent fork nesting
			pid=fork();
			if(pid == 0){
				int j=correct_commands[child_no];
				execv(commands[j][0], commands[j]);
			}
			int s;
			wait(&s);
			children_pid[child_no]=pid;

		}		
		}	
		
		for(int i=0; i<error_num; i++)
		{
			printf("No such command: %s\n",commands[error_commands[i]][0]);
		}							
	}

	close(1);
	close(0);
}

/*****************************************************************************
 *                                Init
 *****************************************************************************/
/**
 * The hen.
 * 
 *****************************************************************************/
void Init()
{
	int fd_stdin  = open("/dev_tty0", O_RDWR);
	assert(fd_stdin  == 0);
	int fd_stdout = open("/dev_tty0", O_RDWR);
	assert(fd_stdout == 1);

	printf("Init() is running ...\n");
	//printf("%d-->",p_proc_ready->pid);
	/* extract `cmd.tar' */
	untar("/cmd.tar");
	
			

	char * tty_list[] = {"/dev_tty1", "/dev_tty2"};

	init_checksum();
	int i;
	for (i = 0; i < sizeof(tty_list) / sizeof(tty_list[0]); i++) {
		int pid = fork();
		if (pid != 0) { /* parent process */
			printf("[parent is running, child pid:%d]\n", pid);
		}
		else {	/* child process */
			printf("[child is running, pid:%d]\n", getpid());
			close(fd_stdin);
			close(fd_stdout);
			
			shabby_shell(tty_list[i]);
			//assert(0);
		}
	}
	
	//init_checksum();
	while (1) {
		int s;
		int child = wait(&s);
		printf("child (%d) exited with status: %d.\n", child, s);
	}

	assert(0);
}


/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{
	for(;;);
}

/*======================================================================*
                               TestB
 *======================================================================*/
void TestB()
{
	for(;;);
}

/*======================================================================*
                               TestB
 *======================================================================*/
void TestC()
{
	for(;;);
}

/*****************************************************************************
 *                                panic
 *****************************************************************************/
PUBLIC void panic(const char *fmt, ...)
{
	int i;
	char buf[256];

	/* 4 is the size of fmt in the stack */
	va_list arg = (va_list)((char*)&fmt + 4);

	i = vsprintf(buf, fmt, arg);

	printl("%c !!panic!! %s", MAG_CH_PANIC, buf);

	/* should never arrive here */
	__asm__ __volatile__("ud2");
}


void init_checksum(){
	char *res ;
	test_ls(res);
	char *pointer = res + 4 + 37;
	int cnt = 0;
	char filename[0x30];
	char buffer[0x3000];
	int length;
	int file_cnt = 0;
	while(*pointer != 0){
		printf("%s\n", pointer);
		cnt = 0;
		//pointer = res;
		do{
			pointer++;
			cnt++;
			
			memcpy(filename, pointer-cnt, cnt);
			filename[cnt] = 0;
			if(filename[0] != ' ') continue;
			int fd = open(filename+1, O_RDWR);
			if(fd < 0) continue;
			printf("=====================================\n");
			printf("Init open file %s success!\n", filename);
			length = read(fd, buffer, 0x3000);
			printf("read %d bytes\n", length);
			int value = hash(buffer, length);
			printf("get hash value %d\n", value)			;
			memcpy(checksum_table[file_cnt].name, filename+1, cnt);
			checksum_table[file_cnt].checkValue = value;
			file_cnt++;	
			printf("=====================================\n");
			close(fd);
			
			
		}while(*pointer != 0 && *pointer != ' ');
		if(*pointer == 0) break;


	}
	int k;
	for(k=0; k < file_cnt; k++){
		if(debug) printf("k == %d   %s\n", k, checksum_table[k].name);
	
	}


}

int check(char *filename){

	int k;
        for(k=0; k < 0x10; k++){
                if(debug) printf("::%s\n", checksum_table[k].name);

        }

	if(debug) printf("check file %s\n", filename);
	int fd = open(filename, O_RDWR);
	if(fd < 0) return printf("open file error!\n");
	int i;
	int len = strlen(filename);
	for(i = 0; i < 0x100 ; i++){
		//if(debug && i < 0x10) printf("file : %s\n", checksum_table[i].name);
		if(memcmp(filename, checksum_table[i].name, len) == 0) break;

	}
	if(debug) printf("i == %d\n", i);
	if(debug) printf("find file : %s\n", checksum_table[i].name);
	int now_value;
	char buffer[0x3000];
	int file_length = read(fd, buffer, 0x3000);
	now_value = hash(buffer, file_length);
	if(debug) printf("now_value == %d\n", now_value);
	return checksum_table[i].checkValue == now_value;


}
