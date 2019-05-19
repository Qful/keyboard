/********************************** (C) COPYRIGHT *******************************
* File Name          : SLEEP.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/11/12
* Description        : ˯�����ü����ʼ��
*******************************************************************************/




/******************************************************************************/
/* ͷ�ļ����� */
#include "CONFIG.h"
#include "CH57x_common.h"
#include "HAL.h"


/*******************************************************************************
 * @fn          CH57X_LowPower
 *
 * @brief       ����˯��
 *
 * input parameters
 *
 * @param       time-���ѵ�ʱ��㣨RTC����ֵ��
 *
 * output parameters
 *
 * @param       
 *
 * @return      None.
 */
u32 CH57X_LowPower( u32 time )
{
#if (defined (HAL_SLEEP)) && (HAL_SLEEP == TRUE)
  u32 tmp,irq_status,sys_cfg;

  SYS_DisableAllIrq( &irq_status );
  tmp = RTC_GetCycle32k();
  if( time - tmp > 0x51F40 ){ // ���˯�ߵ��ʱ�� 10.24s,����ȥ��
    SYS_RecoverIrq( irq_status );
    PRINT("! t1:%x %x...\n",time,tmp);
    return 1;
  }
  if( (time < tmp) || ((time - tmp) < WAKE_UP_RTC_MAX_TIME) ){ // ���˯�ߵ����ʱ��
    SYS_RecoverIrq( irq_status );
    return 2;
  }    
  RTC_SetTignTime( time );
  SYS_RecoverIrq( irq_status );
#if( DEBUG == Debug_UART1 )
  while((R8_UART1_LSR&RB_LSR_TX_ALL_EMP)== 0 ) __nop();// ʹ���������������ӡ��Ϣ��Ҫ�޸����д���
#endif
// LOW POWER-sleepģʽ
  sys_cfg = R16_CLK_SYS_CFG;
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
  R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT |0x08;		
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
  R16_POWER_PLAN &= (RB_PWR_DCDC_EN|RB_PWR_DCDC_PRE);
  R16_POWER_PLAN |= RB_PWR_PLAN_EN\
                  |RB_PWR_MUST_0010\
                  |RB_PWR_MUST_1\
                  |RB_PWR_CORE\
                  |RB_PWR_RAM2K\
                  |RB_PWR_RAM14K\
                  |RB_PWR_EXTEND;
  R8_SAFE_ACCESS_SIG = 0;
  if( !RTCTigFlag ) __WFI();
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
  R16_CLK_SYS_CFG = sys_cfg; //�ָ�ϵͳ��Ƶ����ֵ
  R8_SAFE_ACCESS_SIG = 0;
#endif
  return 0;
}

/*******************************************************************************
 * @fn          HAL_SleepInit
 *
 * @brief       ����˯�߻��ѵķ�ʽ-RTC���ѣ�����ģʽ
 *
 * input parameters
 *
 * @param       None.
 *
 * output parameters
 *
 * @param       
 *
 * @return      None.
 */
void HAL_SleepInit( void )
{
#if (defined (HAL_SLEEP)) && (HAL_SLEEP == TRUE)
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
  R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
  R8_SLP_WAKE_CTRL  |= RB_SLP_RTC_WAKE; // RTC����
  R8_RTC_MODE_CTRL  |= RB_RTC_TRIG_EN;	// ����ģʽ
  R8_SAFE_ACCESS_SIG = 0;						    // 
  NVIC_EnableIRQ(RTC_IRQn);	
  TMOS_SleepRegister( CH57X_LowPower );
#endif
}
