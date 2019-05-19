


#ifndef __CH57x_CLK_H__
#define __CH57x_CLK_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"

typedef enum
{
	CLK_SOURCE_LSI = 0,
	CLK_SOURCE_LSE,
	CLK_SOURCE_HSE_32MHz,
	CLK_SOURCE_HSE_16MHz,
	CLK_SOURCE_HSE_8MHz,
	CLK_SOURCE_HSI_32MHz,				//�ϵ�Ĭ�����	
	CLK_SOURCE_HSI_16MHz,
	CLK_SOURCE_HSI_8MHz,
	CLK_SOURCE_PLL_40MHz,
	CLK_SOURCE_PLL_32MHz,
	CLK_SOURCE_PLL_24MHz,
	CLK_SOURCE_PLL_20MHz,
	CLK_SOURCE_PLL_16MHz,
	
}SYS_CLKTypeDef;


typedef enum
{
	Clk32M_HSI = 0,
	Clk32M_HSE,
	
}HClk32MTypeDef;

typedef enum
{
	Clk32K_LSI = 0,
	Clk32K_LSE,
	
}LClk32KTypeDef;


#define  MAX_DAY		0x00004000 
#define	 MAX_2_SEC		0x0000A8C0
//#define	 MAX_SEC		0x545FFFFF	


/**
  * @brief  rtc timer mode period define
  */
typedef enum
{
	Period_0_125_S = 0,			// 0.125s ����
	Period_0_25_S,				// 0.25s ����
	Period_0_5_S,				// 0.5s ����
	Period_1_S,					// 1s ����
	Period_2_S,					// 2s ����
	Period_4_S,					// 4s ����
	Period_8_S,					// 8s ����
	Period_16_S,				// 16s ����
}RTC_TMRCycTypeDef;	 
	 

/**
  * @brief  rtc interrupt event define
  */
typedef enum
{
	RTC_TRIG_EVENT = 0,			// RTC �����¼�
	RTC_TMR_EVENT,				// RTC ���ڶ�ʱ�¼�

}RTC_EVENTTypeDef;	 




void SystemInit(void);							/* ϵͳʱ�ӳ�ʼ�� */	 
void SetSysClock( SYS_CLKTypeDef sc);			/* ����ϵͳ����ʱ�� */	
void HClk32M_Select( HClk32MTypeDef hc);		/* 32M ��Ƶʱ����Դ */
void LClk32K_Select( LClk32KTypeDef hc);		/* 32K ��Ƶʱ����Դ */
void SingleCalibrat( UINT8 step );				/* ����У׼ */
void HSE_Calibration_LSI( void );				/* �ⲿ32Mʱ��У׼�ڲ�32Kʱ�� */


/* �ڲ� 32KHz ʱ��У׼ */
/* �ⲿ 32KHz ʱ��г����� */
/* �ڲ� 32MHz ʱ��У׼ */
/* �ⲿ 32MHz ʱ��г����� */
/* PLL ���� */	 
	 
	 
void RTC_InitTime( PUINT32 h, PUINT16 m, PUINT16 s );		/* RTCʱ�ӳ�ʼ����ǰʱ�� */
void RTC_GetTime( PUINT32 ph, PUINT16 pm, PUINT16 ps );		/* ��ȡ��ǰʱ�� */
	 
void RTC_SetCycle32k( UINT32 cyc );							/* ����LSE/LSIʱ�ӣ����õ�ǰRTC ������ */	 
UINT32 RTC_GetCycle32k( void );				                /* ����LSE/LSIʱ�ӣ���ȡ��ǰRTC ������ */

void RTC_TRIGFunCfg( UINT32 cyc );							/* RTC����ģʽ���ü��ʱ��,����LSE/LSIʱ�ӣ�ƥ�������� */
void RTC_TMRFunCfg( RTC_TMRCycTypeDef t );					/* RTC��ʱģʽ���� */

UINT8 RTC_GetITFlag( RTC_EVENTTypeDef f );					/* ��ȡRTC�жϱ�־ */	 
void RTC_ClearITFlag( RTC_EVENTTypeDef f );					/* ���RTC�жϱ�־ */ 

	 

	 
#ifdef __cplusplus
}
#endif

#endif  // __CH57x_CLK_H__	

