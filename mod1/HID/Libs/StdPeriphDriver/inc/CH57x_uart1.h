


#ifndef __CH57x_UART1_H__
#define __CH57x_UART1_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"


/** 
  * @brief	LINE error and status define
  */     
#define  STA_ERR_BREAK      RB_LSR_BREAK_ERR       // ���ݼ������     
#define  STA_ERR_FRAME      RB_LSR_FRAME_ERR       // ����֡����     
#define  STA_ERR_PAR        RB_LSR_PAR_ERR         // ��żУ��λ����
#define  STA_ERR_FIFOOV     RB_LSR_OVER_ERR        // �����������  
     
#define  STA_TXFIFO_EMP     RB_LSR_TX_FIFO_EMP     // ��ǰ����FIFO�գ����Լ�����䷢������
#define  STA_TXALL_EMP      RB_LSR_TX_ALL_EMP      // ��ǰ���з������ݶ��������     
#define  STA_RECV_DATA      RB_LSR_DATA_RDY        // ��ǰ�н��յ�����


/**
  * @brief  Configuration UART TrigByte num
  */     
typedef enum
{
	UART_1BYTE_TRIG = 0,        // 1�ֽڴ���
	UART_2BYTE_TRIG,            // 2�ֽڴ���
	UART_4BYTE_TRIG,            // 4�ֽڴ���
	UART_7BYTE_TRIG,            // 7�ֽڴ���
	
}UARTByteTRIGTypeDef;     
     
	 
void UART1_DefInit( void );	 							/* ����Ĭ�ϳ�ʼ������ */
void UART1_BaudRateCfg( UINT32 baudrate );	 			/* ���ڲ��������� */
void UART1_ByteTrigCfg( UARTByteTRIGTypeDef b );         /* �����ֽڴ����ж����� */
void UART1_INTCfg( UINT8 s,  UINT8 i );		            /* �����ж����� */
void UART1_Reset( void );								/* ���������λ */
	
#define UART1_GetITFlag()       (R8_UART1_IIR&RB_IIR_INT_MASK)          /* ��ȡ��ǰ�жϱ�־ */
// please refer to LINE error and status define
#define UART1_GetLinSTA()       (R8_UART1_LSR)          /* ��ȡ��ǰͨѶ״̬ */

#define	UART1_SendByte(b)		(R8_UART1_THR = b)		/* ���ڵ��ֽڷ��� */
void UART1_SendString( PUINT8 buf, UINT16 l );			/* ���ڶ��ֽڷ��� */
#define	UART1_RecvByte()		    (R8_UART1_RBR)          /* ���ڶ�ȡ���ֽ� */
UINT16 UART1_RecvString( PUINT8 buf );					/* ���ڶ�ȡ���ֽ� */
	 
	 
#ifdef __cplusplus
}
#endif

#endif  // __CH57x_UART1_H__	

