/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/10
* Description        : ��������Ӧ��������������ϵͳ��ʼ��
*******************************************************************************/


/******************************************************************************/
/* ͷ�ļ����� */
#include "CONFIG.h"
#include "CH57x_common.h"
#include "CH57xBLE_LIB.h"
#include "HAL.h"
#include "hiddev.h"
#include "hidkbd.h"

/*********************************************************************
 * GLOBAL TYPEDEFS
 */

pTaskEventHandlerFn tasksArr[] = {
  TMOS_CbTimerProcessEvent,
  HAL_ProcessEvent,
  LL_ProcessEvent,
  L2CAP_ProcessEvent,
  GAP_ProcessEvent,	
  GATT_ProcessEvent,                                                
  SM_ProcessEvent,                                                 
  GAPBondMgr_ProcessEvent,                                         
  GATTServApp_ProcessEvent,                                        
  GAPRole_PeripheralProcessEvent,  
  
  HidDev_ProcessEvent,
  HidEmu_ProcessEvent,                                 
};
tmosTaskID TASK_CNT =  sizeof( tasksArr ) / sizeof( tasksArr[0] );

/*********************************************************************
 * @fn      TMOS_InitTasks
 *
 * @brief   This function invokes the initialization function for each task.
 *
 * @param   void
 *
 * @return  none
 */
void TMOS_InitTasks( void )
{
  UINT8 taskID = 0;
  /* tmos Task */
  TMOS_Init( taskID++ );
  /* Hal Task */
  Hal_Init( taskID++ );
  /* LL Task */
  LL_Init( taskID++ );
  /* L2CAP Task */
  L2CAP_Init( taskID++ );
  /* GAP Task */
  GAP_Init( taskID++ );
  /* GATT Task */
  GATT_Init( taskID++ );
  /* SM Task */
  SM_Init( taskID++ );
  GAPBondMgr_Init( taskID++ );
  GATTServApp_Init( taskID++ );
   /* Role */
  GAPRole_PeripheralInit( taskID++ );
  
  /* hid */
  HidDev_Init(taskID++);
  /* Application */
  HidEmu_Init(taskID++);
}

/*******************************************************************************
* Function Name  : main
* Description    : ������
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main( void ) 
{
#ifdef DEBUG
  GPIOA_SetBits(GPIO_Pin_9);
  GPIOA_ModeCfg(GPIO_Pin_9, GPIO_ModeOut_PP_5mA);
  UART1_DefInit( );
#endif   
  PRINT("%s\n",VER_LIB);
  CH57X_BLEInit( );
	TMOS_InitTasks( );
	while(1){
		TMOS_SystemProcess( );
	}
}

/******************************** endfile @ main ******************************/
