/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_SYS.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : SYS_GetInfoSta
* Description    : ��ȡ��ǰϵͳ��Ϣ״̬
* Input          : i: 
					refer to SYS_InfoStaTypeDef
* Return         : DISABLE  -  �ر�
				   ENABLE   -  ����
*******************************************************************************/
UINT8 SYS_GetInfoSta( SYS_InfoStaTypeDef i )
{
    if(i == STA_SAFEACC_ACT)		
        return (R8_SAFE_ACCESS_SIG & RB_SAFE_ACC_ACT);
    else  
        return (R8_GLOB_CFG_INFO&(1<<i));
}

/*******************************************************************************
* Function Name  : SYS_ResetExecute
* Description    : ִ��ϵͳ�����λ
* Input          : None
* Return         : None
*******************************************************************************/
void SYS_ResetExecute( void )
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_RST_WDOG_CTRL |= RB_SOFTWARE_RESET;
}

/*******************************************************************************
* Function Name  : SYS_DisableAllIrq
* Description    : �ر������жϣ���������ǰ�ж�ֵ
* Input          : pirqv����ǰ�����ж�ֵ
* Return         : None
*******************************************************************************/
void SYS_DisableAllIrq( PUINT32 pirqv)
{
	*pirqv = NVIC->ISER[0];
	NVIC->ICER[0] = 0xffffffff;
}

/*******************************************************************************
* Function Name  : SYS_RecoverIrq
* Description    : �ָ�֮ǰ�رյ��ж�ֵ
* Input          : irq_status����ǰ�����ж�ֵ
* Return         : None
*******************************************************************************/
void SYS_RecoverIrq( UINT32 irq_status )
{
	NVIC->ISER[0] = irq_status;
}

/*******************************************************************************
* Function Name  : SYS_GetSysTickCnt
* Description    : ��ȡ��ǰϵͳ(SYSTICK)����ֵ
* Input          : None
* Return         : ��ǰ����ֵ
*******************************************************************************/
UINT32 SYS_GetSysTickCnt( void )
{
	return(SysTick->VAL );
}

/*******************************************************************************
* Function Name  : DelsyUs
* Description    : uS ��ʱ
* Input          : t: ʱ�����
* Return         : None
*******************************************************************************/
void DelsyUs( UINT16 t )
{
    UINT16 i, j;

    for(j=0; j<t; j++)
    {

#if     (FREQ_SYS == 40000000)	
    for(i=0; i<4; i++)		__nop();

#elif       (FREQ_SYS == 32000000)		
    i = 2;
    while(i--)	{ __nop();	__nop(); }		

#elif       (FREQ_SYS == 24000000)		
    i = 1;
    while(i--)	{ __nop();	__nop(); }

 #elif       (FREQ_SYS == 20000000)		
    for(i=0; i<1; i++)		__nop();

 #elif       (FREQ_SYS == 16000000)			
    __nop(); __nop();	__nop(); __nop();
    __nop(); __nop();   __nop(); __nop(); __nop();

#elif       (FREQ_SYS == 8000000)		
    __nop(); __nop();
    
#endif			
    
    }	
}

/*******************************************************************************
* Function Name  : DelsyMs
* Description    : mS ��ʱ
* Input          : t: ʱ�����
* Return         : None
*******************************************************************************/
void DelsyMs( UINT16 t )
{
    UINT16 i;

    for(i=0; i<t; i++)
        DelsyUs(1000);
}

#if( defined  DEBUG)
int fputc( int c, FILE *f )
{
#if  DEBUG == Debug_UART0
  while( R8_UART0_TFC == UART_FIFO_SIZE );                        /* �ȴ����ݷ��� */
  R8_UART0_THR = c;                                               /* �������� */
#elif DEBUG == Debug_UART1       
  while( R8_UART1_TFC == UART_FIFO_SIZE );                        /* �ȴ����ݷ��� */
  R8_UART1_THR = c;                                               /* �������� */
#elif DEBUG == Debug_UART2       
  while( R8_UART2_TFC == UART_FIFO_SIZE );                        /* �ȴ����ݷ��� */
  R8_UART2_THR = c;                                               /* �������� */
#elif DEBUG == Debug_UART3       
  while( R8_UART3_TFC == UART_FIFO_SIZE );                        /* �ȴ����ݷ��� */
  R8_UART3_THR = c;                                               /* �������� */
#endif
  return( c );
}
#endif
