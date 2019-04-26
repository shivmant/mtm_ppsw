#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLE (1<<0)
#define COUNTER_RESET (1<<1)
#define MR0_INTERRUPT_FLAG (1<<0)
#define INTERRUPT_ON_MR0 (1<<0)
#define RESET_ON_MR0 (1<<1)
#define STOP_ON_MR0 (1<<2)

void InitTimer0(void)
{
	T0TCR=T0TCR|COUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime)
{
	T0TCR=T0TCR|COUNTER_RESET;
	T0TCR=T0TCR&~COUNTER_RESET;
	while(uiTime>T0TC){}
}

void InitTimer0Match0(unsigned int uiDelayTime)
{
	T0TCR=T0TCR|COUNTER_ENABLE;
	T0MR0=uiDelayTime*4;
	T0MCR=T0MCR|RESET_ON_MR0;
	T0MCR=T0MCR|INTERRUPT_ON_MR0;
}

void WaitONTimer0Match0(void)
{
	T0IR=T0IR|MR0_INTERRUPT_FLAG;
	T0TCR=T0TCR|COUNTER_RESET;
	T0TCR=T0TCR&~COUNTER_RESET;
	while(T0IR==0){}
}
