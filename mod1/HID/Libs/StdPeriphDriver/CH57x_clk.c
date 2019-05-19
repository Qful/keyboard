/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_clk.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
* Function Name  : SystemInit
* Description    : ϵͳʱ��Ĭ�ϳ�ʼ��
* Input          : None			   				
* Return         : None
*******************************************************************************/
void SystemInit(void)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = (2<<6)|0x08;			// 32M -> Fsys
}

/*******************************************************************************
* Function Name  : SetSysClock
* Description    : ����ϵͳ����ʱ��
* Input          : sc: ϵͳʱ��Դѡ��
					refer to SYS_CLKTypeDef
* Return         : None
*******************************************************************************/
void SetSysClock( SYS_CLKTypeDef sc)
{	
    switch( sc )
    {
        case CLK_SOURCE_LSI:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R8_CK32K_CONFIG &= ~RB_CLK_OSC32K_XT;
            R16_CLK_SYS_CFG = (3<<6)|0x08;
            break;
        case CLK_SOURCE_LSE:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R8_CK32K_CONFIG |= RB_CLK_OSC32K_XT;
            R16_CLK_SYS_CFG = (3<<6)|0x08;
            break;
        case CLK_SOURCE_HSE_32MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(2<<6)|0x08;
            break;
        case CLK_SOURCE_HSE_16MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(0<<6)|0x02;
            break;
        case CLK_SOURCE_HSE_8MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(0<<6)|0x04;
            break;
        case CLK_SOURCE_HSI_32MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = (2<<6)|0x08;
            break;
        case CLK_SOURCE_HSI_16MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = (0<<6)|0x02;
            break;
        case CLK_SOURCE_HSI_8MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = (0<<6)|0x04;
            break;
        case CLK_SOURCE_PLL_40MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(1<<6)|12;
            break;
        case CLK_SOURCE_PLL_32MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(1<<6)|15;
            break;
        case CLK_SOURCE_PLL_24MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(1<<6)|20;
            break;
        case CLK_SOURCE_PLL_20MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(1<<6)|24;
            break;
        case CLK_SOURCE_PLL_16MHz:
        	R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    		R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(1<<6)|30;
            break;
        default :
            break;		
    }	
}


/*******************************************************************************
* Function Name  : HClk32M_Select
* Description    : 32M ��Ƶʱ����Դ
* Input          : hc: 
					Clk32M_HSI   -   ѡ���ڲ�32M
					Clk32M_HSE   -   ѡ���ⲿ32M
* Return         : None
*******************************************************************************/
void HClk32M_Select( HClk32MTypeDef hc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;	
    if( hc == Clk32M_HSI)
        R16_CLK_SYS_CFG &= ~RB_CLK_OSC32M_XT;
    else
        R16_CLK_SYS_CFG |= RB_CLK_OSC32M_XT;
}

/*******************************************************************************
* Function Name  : LClk32K_Select
* Description    : 32K ��Ƶʱ����Դ
* Input          : hc: 
					Clk32K_LSI   -   ѡ���ڲ�32M
					Clk32K_LSE   -   ѡ���ⲿ32M
* Return         : None
*******************************************************************************/
void LClk32K_Select( LClk32KTypeDef hc)
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;	
    if( hc == Clk32K_LSI)
        R16_CLK_SYS_CFG &= ~RB_CLK_OSC32M_XT;
    else
        R16_CLK_SYS_CFG |= RB_CLK_OSC32M_XT;
}

/*******************************************************************************
* Function Name  : HSE_Calibration_LSI
* Description    : �ⲿ32Mʱ��У׼�ڲ�32Kʱ��
* Input          : None
* Return         : None
*******************************************************************************/
void HSE_Calibration_LSI( void )
{
	UINT16  a1, a2, a, cnt;
	
	cnt = 0;
	a = 0;
    a2 = 0;
    while(1)
    {  
    	cnt ++;
        a1 = a2;
        SingleCalibrat(3);     // �ֵ�
        a2 = R16_INT32K_TUNE;   
        if((a1>a2)?((a1-a2)<=3):((a2-a1)<=3)) a++;
        else    a = 0;
        if( a>3 || cnt>10 )   break;
    }             
    
    cnt = 0;
    while(1)
    {  
    	cnt ++;
        a1 = a2;
        SingleCalibrat(1);     // ΢��
        a2 = R16_INT32K_TUNE;    
        if((a1>a2)?((a1-a2)<=1):((a2-a1)<=1)) a++;
        else    a = 0;
        if( a>2 || cnt>10 )   break;
    }                    
}

/*******************************************************************************
* Function Name  : SingleCalibrat
* Description    : ����У׼
* Input          : step��������С
* Return         : None
*******************************************************************************/
void SingleCalibrat( UINT8 step )
{
    UINT16  i, j;
    UINT16  c1, c2;
    UINT16  rev;
    UINT8   st = step;

	rev = R16_CLK_SYS_CFG;
    j = 5*16000000/32000;				// ���ֵ(��Ҫ��Ƶ)
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = RB_CLK_OSC32M_XT|(0<<6)|0x02;		// 16M

    /* У׼ */
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_OSC_CAL_CTRL = RB_OSC_CNT_EN;
    c2 = 0xffff;

    while(1)
    {	
        while(!(R8_OSC_CAL_CTRL&RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT;			// ʵʱУ׼�����ֵ

        while(R8_OSC_CAL_CTRL&RB_OSC_CNT_HALT);		
        while(!(R8_OSC_CAL_CTRL&RB_OSC_CNT_HALT));
        i = R16_OSC_CAL_CNT;			// ʵʱУ׼�����ֵ		

        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
        R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
        if( i > j )
        {
            R16_INT32K_TUNE += st;			// ˵�� RC Ƶ��ƫ��
            c1 = c2;
            c2 = i-j;
        }
        else
        {
            R16_INT32K_TUNE += st;			// ˵�� RC Ƶ��ƫ��
            c1 = c2;
            c2 = j-i;
        }

        if(c1 < c2)
        {
            R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
            R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
            if( i > j )     R16_INT32K_TUNE += st;			// ����У��ȥ
            else            R16_INT32K_TUNE += st;			// ����У��ȥ			
            break;
        }
    }

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R16_CLK_SYS_CFG = rev;
    R8_OSC_CAL_CTRL = 0;
}



/*******************************************************************************
* Function Name  : RTCInitTime
* Description    : RTCʱ�ӳ�ʼ����ǰʱ��
* Input          : ph: ����ʱ�� - Сʱ
					MAX_H = 393192
				   pm: ����ʱ�� - ����
					MAX_M = 59
				   ps: ����ʱ�� - ��
				    MAX_S = 59
* Return         : None
*******************************************************************************/
void RTC_InitTime( PUINT32 ph, PUINT16 pm, PUINT16 ps )
{
    UINT32  t;
    UINT16  day, sec2, t32k;

    day = *ph/24;
    sec2 = (*ph%24)*1800+*pm*30+*ps/2;
    t32k = (*ps&1)?(0x8000):(0);
    t = sec2;
    t = t<<16 | t32k;

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		// ���밲ȫģʽ
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;		
    R32_RTC_TRIG = day;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_HI;
    R32_RTC_TRIG = t;	
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG0;
}

/*******************************************************************************
* Function Name  : RTC_GetTime
* Description    : ��ȡ��ǰʱ��
* Input          : ph: ��ȡ����ʱ�� - Сʱ
					MAX_H = 393192
				   pm: ��ȡ����ʱ�� - ����
					MAX_M = 59
				   ps: ��ȡ����ʱ�� - ��
				    MAX_S = 59
* Return         : None
*******************************************************************************/
void RTC_GetTime( PUINT32 ph, PUINT16 pm, PUINT16 ps )
{
    UINT32  t;
    UINT16  day, sec2, t32k;

    day = R32_RTC_CNT_DAY & 0x3FFF;
    sec2 = R16_RTC_CNT_2S; 
    t32k = R16_RTC_CNT_32K;

    t = sec2*2 + ((t32k<0x8000)?0:1);		// 
    *ph = day*24 + t/3600;
    *pm = t%3600/60;
    *ps = t%60;
}

/*******************************************************************************
* Function Name  : RTC_SetCycle32k
* Description    : ����LSE/LSIʱ�ӣ����õ�ǰRTC ������
* Input          : cyc: �������ڼ�����ֵ - cycle
					MAX_CYC = 0xA8BFFFFF = 2831155199
* Return         : None
*******************************************************************************/
void RTC_SetCycle32k( UINT32 cyc )
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;		
    R32_RTC_TRIG = cyc;
    R8_RTC_MODE_CTRL |= RB_RTC_LOAD_LO;
}

/*******************************************************************************
* Function Name  : RTC_GetCycle32k
* Description    : ����LSE/LSIʱ�ӣ���ȡ��ǰRTC ������
* Input          : None
* Return         : ���ص�ǰ��������MAX_CYC = 0xA8BFFFFF = 2831155199
*******************************************************************************/
UINT32 RTC_GetCycle32k( void )
{
    UINT32 i;
    
    i = R32_RTC_CNT_32K;
    if( i!=R32_RTC_CNT_32K )
        return (R32_RTC_CNT_32K);
    else
        return (i);
}

/*******************************************************************************
* Function Name  : RTC_TMRFunCfg
* Description    : RTC��ʱģʽ����
* Input          : t: 
					refer to RTC_TMRCycTypeDef
* Return         : None
*******************************************************************************/
void RTC_TMRFunCfg( RTC_TMRCycTypeDef t )
{
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R8_RTC_MODE_CTRL &= ~(RB_RTC_TMR_EN|RB_RTC_TMR_MODE);
    R8_RTC_MODE_CTRL |= RB_RTC_TMR_EN | (t);
}

/*******************************************************************************
* Function Name  : RTC_TRIGFunCfg
* Description    : RTCʱ�䴥��ģʽ����
* Input          : cyc: ��Ե�ǰʱ��Ĵ������ʱ�䣬����LSE/LSIʱ��������
* Return         : None
*******************************************************************************/
void RTC_TRIGFunCfg( UINT32 cyc )
{
    UINT32 t;

    t = RTC_GetCycle32k() + cyc;
    if( t&0xFFFF )	t = t+0x10000;
    if ( t>=((UINT32)MAX_2_SEC<<16))	t = t-((UINT32)MAX_2_SEC<<16);	

    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG1;		
    R8_SAFE_ACCESS_SIG = SAFE_ACCESS_SIG2;
    R32_RTC_TRIG = t;
    R8_RTC_MODE_CTRL |= RB_RTC_TRIG_EN;
}

/*******************************************************************************
* Function Name  : RTC_GetITFlag
* Description    : ��ȡRTC�жϱ�־
* Input          : f: 
					refer to RTC_EVENTTypeDef
* Return         : �жϱ�־״̬:
					0     -  	δ�����¼�
				   (!0)   -  	�����¼�
*******************************************************************************/
UINT8 RTC_GetITFlag( RTC_EVENTTypeDef f )
{
    if( f == RTC_TRIG_EVENT )
        return ( R8_RTC_FLAG_CTRL & RB_RTC_TRIG_FLAG );
    else 
        return ( R8_RTC_FLAG_CTRL & RB_RTC_TMR_FLAG );
}

/*******************************************************************************
* Function Name  : RTC_ClearITFlag
* Description    : ���RTC�жϱ�־
* Input          : f: 
					refer to RTC_EVENTTypeDef
* Return         : None
*******************************************************************************/
void RTC_ClearITFlag( RTC_EVENTTypeDef f )
{
    switch( f ) 
    {
        case RTC_TRIG_EVENT:
            R8_RTC_FLAG_CTRL = RB_RTC_TRIG_CLR;
            break;
        case RTC_TMR_EVENT:
            R8_RTC_FLAG_CTRL = RB_RTC_TMR_CLR;
            break;
        default :
            break;
    }
}





