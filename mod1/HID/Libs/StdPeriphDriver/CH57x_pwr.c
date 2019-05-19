/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_pwr.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : PWR_DCDCCfg
* Description    : �����ڲ�DC/DC��Դ�����ڽ�Լϵͳ����
* Input          : s:  
                    ENABLE  - ��DCDC��Դ
                    DISABLE - �ر�DCDC��Դ   				
* Return         : None
*******************************************************************************/
void PWR_DCDCCfg( UINT8 s )
{
    if(s == DISABLE)
    {		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN &= ~(RB_PWR_DCDC_EN|RB_PWR_DCDC_PRE);		// ��· DC/DC 
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;		
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN |= RB_PWR_DCDC_PRE;
        DelsyUs(10);
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R16_POWER_PLAN |= RB_PWR_DCDC_EN;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;			
    }
}

/*******************************************************************************
* Function Name  : PWR_UnitModCfg
* Description    : �ɿص�Ԫģ��ĵ�Դ����
* Input          : s:  
                    ENABLE  - ��   
                    DISABLE - �ر�
                   unit:
                    please refer to unit of controllable power supply 				
* Return         : None
*******************************************************************************/
void PWR_UnitModCfg( UINT8 s, UINT8 unit )
{
    if(s == DISABLE)		//�ر�
    {
    	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if(unit&UNIT_ETH_PHY)		R8_SLP_WAKE_CTRL &= ~RB_SLP_ETH_WAKE;
        R8_HFCK_PWR_CTRL &= ~(unit&0x1c);
        R8_CK32K_CONFIG &= ~(unit&0x03);
    }
    else					//��
    {
    	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if(unit&UNIT_ETH_PHY)		R8_SLP_WAKE_CTRL |= RB_SLP_ETH_WAKE;
        R8_HFCK_PWR_CTRL |= (unit&0x1c);
        R8_CK32K_CONFIG |= (unit&0x03);
    }
}

/*******************************************************************************
* Function Name  : PWR_PeriphClkCfg
* Description    : ����ʱ�ӿ���λ
* Input          : s:  
                    ENABLE  - ������ʱ��   
                    DISABLE - �ر�����ʱ��
                   perph:
                    please refer to Peripher CLK control bit define						
* Return         : None
*******************************************************************************/
void PWR_PeriphClkCfg( UINT8 s, UINT16 perph )
{
    if( s == DISABLE )
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL |= perph;
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R32_SLEEP_CONTROL &= ~perph;
    }
}

/*******************************************************************************
* Function Name  : PWR_PeriphWakeUpCfg
* Description    : ˯�߻���Դ����
* Input          : s:  
                    ENABLE  - �򿪴�����˯�߻��ѹ���   
                    DISABLE - �رմ�����˯�߻��ѹ���
                   perph:
                    RB_SLP_USB_WAKE	    -  USB Ϊ����Դ
                    RB_SLP_ETH_WAKE	    -  ETH Ϊ����Դ
                    RB_SLP_RTC_WAKE	    -  RTC Ϊ����Դ
                    RB_SLP_GPIO_WAKE	-  GPIO Ϊ����Դ
                    RB_SLP_BAT_WAKE	    -  BAT Ϊ����Դ
                    ALL     -  ��������
* Return         : None
*******************************************************************************/
void PWR_PeriphWakeUpCfg( UINT8 s, UINT16 perph )
{
    if( s == DISABLE )
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL &= ~perph;		
    }
    else
    {
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        R8_SLP_WAKE_CTRL |= perph;
    }
}

/*******************************************************************************
* Function Name  : LowPower_Idle
* Description    : �͹���-Idleģʽ
* Input          : None
* Return         : None
*******************************************************************************/
void LowPower_Idle( void )
{
    SCB -> SCR &= ~SCB_SCR_SLEEPDEEP_Msk;				// sleep
    __WFI();
}

/*******************************************************************************
* Function Name  : LowPower_Halt_1
* Description    : �͹���-Halt_1ģʽ
* Input          : None
* Return         : None
*******************************************************************************/
void LowPower_Halt_1( void )
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL &= ~RB_SLP_ROM_PWR_DN;		// flash����
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;				//deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Halt_2
* Description    : �͹���-Halt_2ģʽ
* Input          : None
* Return         : None
*******************************************************************************/
void LowPower_Halt_2( void )
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_SLP_POWER_CTRL |= RB_SLP_ROM_PWR_DN;			// flashͣ��
    R8_SAFE_ACCESS_SIG = 0;

    SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;				//deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Sleep
* Description    : �͹���-Sleepģʽ
* Input          : rm:
                    RB_PWR_RAM2K	-	���2K SRAM ����
                    RB_PWR_RAM14K	-	0x20004000 - 0x20007800 14K SRAM ����
                    RB_PWR_EXTEND	-	USB��RF ��Ԫ�������򹩵�
                   NULL	-	���ϵ�Ԫ���ϵ�
* Return         : None
*******************************************************************************/
void LowPower_Sleep( UINT8 rm )
{	
	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = (R16_CLK_SYS_CFG&0xff00)|8;
	
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN &= (RB_PWR_DCDC_EN|RB_PWR_DCDC_PRE);
    R16_POWER_PLAN |= RB_PWR_PLAN_EN		\
                    |RB_PWR_MUST_0010		\
                    |RB_PWR_MUST_1			\
                    |RB_PWR_CORE            \
                    |rm;    
    R8_SAFE_ACCESS_SIG = 0;

	SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;				//deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0;
}

/*******************************************************************************
* Function Name  : LowPower_Shutdown
* Description    : �͹���-Shutdownģʽ
* Input          : rm:
                    RB_PWR_RAM2K	-	���2K SRAM ����
                   NULL	-	���ϵ�Ԫ���ϵ�
* Return         : None
*******************************************************************************/
void LowPower_Shutdown( UINT8 rm )
{	
	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = (R16_CLK_SYS_CFG&0xff00)|8;
	
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_POWER_PLAN &= (RB_PWR_DCDC_EN|RB_PWR_DCDC_PRE);
    R16_POWER_PLAN |= RB_PWR_PLAN_EN		\
                    |RB_PWR_MUST_0010		\
                    |RB_PWR_MUST_1			\
                    |rm;
    R8_SAFE_ACCESS_SIG = 0;                

	SCB -> SCR |= SCB_SCR_SLEEPDEEP_Msk;				//deep sleep
    __WFI();
    R8_SAFE_ACCESS_SIG = 0; 
}






