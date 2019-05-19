/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_usbhost.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"
    
/*****************************************************************************
* Function Name  : InitRootDevice
* Description    : ��ʼ��ָ��ROOT-HUB�˿ڵ�USB�豸
* Input          : DataBuf: ö�ٹ����д�ŵ���������Ϣ������
* Return         :
*******************************************************************************/
UINT8 InitRootDevice( PUINT8 DataBuf ) 
{
    UINT8  i, s;
    UINT8  cfg, dv_cls, if_cls;
	
    PRINT( "Reset host port\n" );
    ResetRootHubPort( );  		// ��⵽�豸��,��λ��Ӧ�˿ڵ�USB����
    for ( i = 0, s = 0; i < 100; i ++ ) {  				// �ȴ�USB�豸��λ����������,100mS��ʱ
        mDelaymS( 1 );
        if ( EnableRootHubPort( ) == ERR_SUCCESS ) {  // ʹ�ܶ˿�
            i = 0;
            s ++;  					
            if ( s > 100 ) break;  	// �Ѿ��ȶ�����100mS
        }
    }
    if ( i ) {  										// ��λ���豸û������
        DisableRootHubPort( );
        PRINT( "Disable host port because of disconnect\n" );
        return( ERR_USB_DISCON );
    }
    SetUsbSpeed( ThisUsbDev.DeviceSpeed );  // ���õ�ǰUSB�ٶ�
	
    PRINT( "GetDevDescr: " );
    s = CtrlGetDeviceDescr( DataBuf );  		// ��ȡ�豸������
    if ( s == ERR_SUCCESS )
    {
        for ( i = 0; i < ((PUSB_SETUP_REQ)SetupGetDevDescr)->wLength; i ++ ) 		
       PRINT( "x%02X ", (UINT16)( DataBuf[i] ) );
       PRINT( "\n" ); 
		
       ThisUsbDev.DeviceVID = ((PUSB_DEV_DESCR)DataBuf)->idVendor; //����VID PID��Ϣ
       ThisUsbDev.DevicePID = ((PUSB_DEV_DESCR)DataBuf)->idProduct;
       dv_cls = ( (PUSB_DEV_DESCR)DataBuf ) -> bDeviceClass;
		
       s = CtrlSetUsbAddress( ((PUSB_SETUP_REQ)SetupSetUsbAddr)->wValue );  
       if ( s == ERR_SUCCESS )
       {
           ThisUsbDev.DeviceAddress = ( (PUSB_SETUP_REQ)SetupSetUsbAddr )->wValue;  // ����USB��ַ
    
           PRINT( "GetCfgDescr: " );
           s = CtrlGetConfigDescr( DataBuf );
           if ( s == ERR_SUCCESS ) 
           {
               for ( i = 0; i < ( (PUSB_CFG_DESCR)DataBuf )->wTotalLength; i ++ ) 
               PRINT( "x%02X ", (UINT16)( DataBuf[i] ) );
               PRINT("\n");
/* ��������������,��ȡ�˵�����/���˵��ַ/���˵��С��,���±���endp_addr��endp_size�� */				
               cfg = ( (PUSB_CFG_DESCR)DataBuf )->bConfigurationValue;
               if_cls = ( (PUSB_CFG_DESCR_LONG)DataBuf )->itf_descr.bInterfaceClass;  // �ӿ������
                              
               if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_STORAGE)) {  // ��USB�洢���豸,������ȷ����U��
#ifdef	FOR_ROOT_UDISK_ONLY
                   CH579DiskStatus = DISK_USB_ADDR;
                   return( ERR_SUCCESS );
               }
               else 	return( ERR_USB_UNSUPPORT );
#else
                  s = CtrlSetUsbConfig( cfg );  // ����USB�豸����
                  if ( s == ERR_SUCCESS )
                  {
                      ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                      ThisUsbDev.DeviceType = USB_DEV_CLASS_STORAGE;
                      PRINT( "USB-Disk Ready\n" );
                      SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��
                      return( ERR_SUCCESS );
                  }
               }
               else if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_PRINTER) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass == 0x01 ) {  // �Ǵ�ӡ�����豸
                   s = CtrlSetUsbConfig( cfg );  // ����USB�豸����
                   if ( s == ERR_SUCCESS ) {
//	�豣��˵���Ϣ�Ա����������USB����
                       ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                       ThisUsbDev.DeviceType = USB_DEV_CLASS_PRINTER;
                       PRINT( "USB-Print Ready\n" );
                       SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��    
                       return( ERR_SUCCESS );
                   }
               }
               else if ( (dv_cls == 0x00) && (if_cls == USB_DEV_CLASS_HID) && ((PUSB_CFG_DESCR_LONG)DataBuf)->itf_descr.bInterfaceSubClass <= 0x01 ) {  // ��HID���豸,����/����
//  ���������з�����HID�ж϶˵�ĵ�ַ
//  �����ж϶˵�ĵ�ַ,λ7����ͬ����־λ,��0
                   if_cls = ( (PUSB_CFG_DESCR_LONG)DataBuf ) -> itf_descr.bInterfaceProtocol;
                   s = CtrlSetUsbConfig( cfg );  // ����USB�豸����
                   if ( s == ERR_SUCCESS ) {
//	    					Set_Idle( );
//	�豣��˵���Ϣ�Ա����������USB����
                       ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                       if ( if_cls == 1 ) {
                       ThisUsbDev.DeviceType = DEV_TYPE_KEYBOARD;
//	��һ����ʼ��,�����豸����ָʾ��LED��
                       PRINT( "USB-Keyboard Ready\n" );
                       SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��
                       return( ERR_SUCCESS );
                       }
                       else if ( if_cls == 2 ) {
                           ThisUsbDev.DeviceType = DEV_TYPE_MOUSE;
//	Ϊ���Ժ��ѯ���״̬,Ӧ�÷���������,ȡ���ж϶˿ڵĵ�ַ,���ȵ���Ϣ
                           PRINT( "USB-Mouse Ready\n" );
                            SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��
                           return( ERR_SUCCESS );
                       }
                       s = ERR_USB_UNSUPPORT;
                   }
				        }
               else {   // ���Խ�һ������
                   s = CtrlSetUsbConfig( cfg );  // ����USB�豸����
                   if ( s == ERR_SUCCESS ) {
//	�豣��˵���Ϣ�Ա����������USB����
                       ThisUsbDev.DeviceStatus = ROOT_DEV_SUCCESS;
                       ThisUsbDev.DeviceStatus = dv_cls ? dv_cls : if_cls;
                       SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��
                       return( ERR_SUCCESS );  /* δ֪�豸��ʼ���ɹ� */
                   }
               }
#endif			
            }
       }
    }
	
    PRINT( "InitRootDev Err = %02X\n", (UINT16)s );
#ifdef	FOR_ROOT_UDISK_ONLY
    CH579DiskStatus = DISK_CONNECT;
#else
    ThisUsbDev.DeviceStatus = ROOT_DEV_FAILED;
#endif
    SetUsbSpeed( 1 );  // Ĭ��Ϊȫ��	
    return( s );		
}













