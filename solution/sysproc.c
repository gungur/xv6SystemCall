#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_getparentname(void)
{

  int parentbufsize;
  int childbufsize;
  if (argint(2, &parentbufsize) < 0) {
    return -1;
  }
  if (argint(3, &childbufsize) < 0) {
    return -1;
  }
  
  char* parentbuf;
  char* childbuf;
  if (argptr(0, &parentbuf, 256) < 0) {
    return -1;
  }
  if (argptr(1, &childbuf, 256) < 0) {
    return -1;
  }

  if (parentbuf == 0 || childbuf == 0) {
    return -1;
  }

  if (parentbufsize < 1 || childbufsize < 1) {
    return -1;
  }

  strncpy(parentbuf, myproc()->parent->name, parentbufsize);
  strncpy(childbuf, myproc()->name, childbufsize);	

  // argint is for buffersize (int)
  // argstr is for buffers (char*)
  // look in string.c and proc.c

  return 0;
}
