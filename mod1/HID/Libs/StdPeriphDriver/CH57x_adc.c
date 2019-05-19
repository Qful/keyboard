/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_adc.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"


/*******************************************************************************
* Function Name  : ADC_ExtSingleChSampInit
* Description    : �ⲿ�źŵ�ͨ��������ʼ��
* Input          : sp:
					refer to ADC_SampClkTypeDef
				   ga:
					refer to ADC_SignalPGATypeDef
* Return         : None
*******************************************************************************/
void ADC_ExtSingleChSampInit( ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga )
{
    R8_ADC_CFG = RB_ADC_POWER_ON			\
                |RB_ADC_BUF_EN				\
                |( sp<<6 )					\
                |( ga<<4 )	;
}

/*******************************************************************************
* Function Name  : ADC_ExtDiffChSampInit
* Description    : �ⲿ�źŲ��ͨ��������ʼ��
* Input          : sp:
					refer to ADC_SampClkTypeDef
				   ga:
					refer to ADC_SignalPGATypeDef
* Return         : None
*******************************************************************************/
void ADC_ExtDiffChSampInit( ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga )
{
    R8_ADC_CFG = RB_ADC_POWER_ON			\
                |RB_ADC_DIFF_EN             \
                |( sp<<6 )					\
                |( ga<<4 )	;
}

/*******************************************************************************
* Function Name  : ADC_InterTSSampInit
* Description    : �����¶ȴ�����������ʼ��
* Input          : None
* Return         : None
*******************************************************************************/
void ADC_InterTSSampInit( void )
{
    R8_TEM_SENSOR |= RB_TEM_SEN_PWR_ON;
    R8_ADC_CHANNEL = CH_INTE_VTEMP;
    R8_ADC_CFG = RB_ADC_POWER_ON			\
                |( 2<<4 )	;
}

/*******************************************************************************
* Function Name  : ADC_InterBATSampInit
* Description    : ���õ�ص�ѹ������ʼ��
* Input          : None
* Return         : None
*******************************************************************************/
void ADC_InterBATSampInit( void )
{
    R8_ADC_CHANNEL = CH_INTE_VBAT;
    R8_ADC_CFG = RB_ADC_POWER_ON			\
                |RB_ADC_BUF_EN				\
                |( 2<<4 )	;
}


/*******************************************************************************
* Function Name  : TouchKey_ChSampInit
* Description    : ��������ͨ��������ʼ��
* Input          : None
* Return         : None
*******************************************************************************/
void TouchKey_ChSampInit( void )
{
    R8_ADC_CFG = RB_ADC_POWER_ON | RB_ADC_BUF_EN | ( 2<<4 );
    R8_TKEY_CTRL = RB_TKEY_PWR_ON;
}

/*******************************************************************************
* Function Name  : ADC_ExcutSingleConver
* Description    : ADCִ�е���ת��
* Input          : None
* Return         : ADCת���������
*******************************************************************************/
UINT16 ADC_ExcutSingleConver( void )
{
    R8_ADC_CONVERT |= RB_ADC_START;
    while( R8_ADC_CONVERT & RB_ADC_START );

    return ( R16_ADC_DATA );
}

/*******************************************************************************
* Function Name  : TouchKey_ExcutSingleConver
* Description    : TouchKeyת��������
* Input          : d:  Touchkey��ŵ�ʱ�䣬��4bit-�ŵ�ʱ�䣬����8bit-���ʱ��
* Return         : ��ǰTouchKey��Ч����
*******************************************************************************/
UINT16 TouchKey_ExcutSingleConver( UINT8 d )
{
    R8_TKEY_CTRL = RB_TKEY_PWR_ON;
    R8_TKEY_CNT = d;
    while( R8_TKEY_CTRL &  RB_TKEY_ACTION );

    return ( R16_ADC_DATA );
}


/*******************************************************************************
* Function Name  : ADC_GetCurrentTS
* Description    : ��ȡ��ǰ�������¶�ֵ���棩
* Input          : ts_v����ǰ�¶ȴ������������
* Return         : ת������¶�ֵ���棩
*******************************************************************************/
UINT8 ADC_GetCurrentTS( UINT16 ts_v )
{
    UINT16  vol_ts;
    UINT16  D85_tem, D85_vol, D25;
    
    vol_ts = (ts_v*1060)>>11;
    D85_tem = (UINT16)((*((PUINT32)ROM_TMP_85C_ADDR)>>16)&0x00ff); 
    D85_vol = *((PUINT16)ROM_TMP_85C_ADDR);
    D25 = *((PUINT32)ROM_TMP_25C_ADDR);
    
    
    return ( D85_tem - ( D85_vol - vol_ts + 8 ) * 16 / D25 );

}



