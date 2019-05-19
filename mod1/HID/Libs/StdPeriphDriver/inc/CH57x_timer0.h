


#ifndef __CH57x_TIMER0_H__
#define __CH57x_TIMER0_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

#define	DataBit_25	(1<<25)	 


/**
  * @brief  TMR0 interrupt bit define
  */

#define	TMR0_3_IT_CYC_END 		0x01				// ���ڽ�����־����׽-��ʱ����ʱ-���ڽ�����PWM-���ڽ���
#define	TMR0_3_IT_DATA_ACT		0x02				// ������Ч��־����׽-�����ݣ�PWM-��Ч��ƽ����
#define	TMR0_3_IT_FIFO_HF 		0x04				// FIFO ʹ�ù��룺��׽- FIFO>=4�� PWM- FIFO<4
#define	TMR1_2_IT_DMA_END 		0x08				// DMA ������֧��TMR1��TMR2
#define	TMR0_3_IT_FIFO_OV 		0x10				// FIFO �������׽- FIFO���� PWM- FIFO��
	 
	 
/**
  * @brief  Configuration PWM effective level repeat times
  */
typedef enum
{
	PWM_Times_1 = 0,					// PWM ��Ч����ظ�1����
	PWM_Times_4,						// PWM ��Ч����ظ�4����
	PWM_Times_8,						// PWM ��Ч����ظ�8����
	PWM_Times_16,						// PWM ��Ч����ظ�16����
}PWM_RepeatTsTypeDef;	


/**
  * @brief  Configuration Cap mode
  */
typedef enum
{
	CAP_NULL = 0,						// ����׽
	Edge_To_Edge,						// �������֮��
	FallEdge_To_FallEdge,				// �½��ص��½���
	RiseEdge_To_RiseEdge,				// �����ص�������
}CapModeTypeDef;	



// ��ʱ�ͼ���
void TMR0_TimerInit( UINT32 t );									/* ��ʱ���ܳ�ʼ�� */	 
void TMR0_EXTSingleCounterInit( UINT32 c );							/* �ⲿ�źż������ܳ�ʼ�� */
#define  TMR0_GetCurrentCount()		R32_TMR0_COUNT	 				/* ��ȡ��ǰ����ֵ�����67108864 */

// PWM����
#define TMR0_PWMCycleCfg( cyc )	    (R32_TMR0_CNT_END=cyc)			/* PWM0 ͨ�����������������, ���67108864 */
void TMR0_PWMInit( PWMX_PolarTypeDef pr, PWM_RepeatTsTypeDef ts );	/* PWM �����ʼ�� */	 
#define TMR0_PWMActDataWidth( d )   (R32_TMR0_FIFO = d)			/* PWM0 ��Ч��������, ���67108864 */
	 
// ��׽����
#define TMR0_CAPTimeoutCfg( cyc )   (R32_TMR0_CNT_END=cyc)			/* CAP0 ��׽��ƽ��ʱ����, ���33554432 */
void TMR0_CapInit( CapModeTypeDef cap );							/* �ⲿ�źŲ�׽���ܳ�ʼ�� */
#define TMR0_CAPGetData( d )		R32_TMR0_FIFO					/* ��ȡ�������� */
#define TMR0_CAPDataCounter()		R8_TMR0_FIFO_COUNT				/* ��ȡ��ǰ�Ѳ������ݸ��� */


#define TMR0_Disable()				(R8_TMR0_CTRL_MOD &= ~RB_TMR_COUNT_EN)		/* �ر� TMR0 */
// refer to TMR0 interrupt bit define
#define	TMR0_ITCfg(s,f)				((s)?(R8_TMR0_INTER_EN|=f):(R8_TMR0_INTER_EN&=~f))		/* TMR0 ��Ӧ�ж�λ������ر� */
// refer to TMR0 interrupt bit define
#define TMR0_ClearITFlag(f)         (R8_TMR0_INT_FLAG |= f)			/* ����жϱ�־ */
#define TMR0_GetITFlag(f)           (R8_TMR0_INT_FLAG&f)			/* ��ѯ�жϱ�־״̬ */


	 
#ifdef __cplusplus
}
#endif

#endif  // __CH57x_TIMER0_H__	

