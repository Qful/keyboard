


#ifndef __CH57x_FLASH_H__
#define __CH57x_FLASH_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"
     
#define ROM_UUID_ADDR        0x40608         // chip UID address ( ID-48bit + CKS-16bit )
#define ROM_MAC_ADDR         0x40608         // NET MAC address 48bit

// ��ȡΨһID
void GetUniqueID(PUINT8 buf);                                           /* ��ȡоƬΨһID��С��ģʽ��6B-ID�� 2B-CKS */    
     
// ��ȡ����MAC
void GetMACAddress(PUINT8 buf);                                         /* ��ȡ����MAC��С��ģʽ��6B-MAC */    
	 
// CodeFlash ����
UINT8 CodeFlash_BlockEarse(UINT32 addr);								/* CodeFlash �������һ�β���512B */
UINT8 CodeFlash_WriteDW(UINT32 addr, UINT32 dat);						/* CodeFlash 32bitд����ַ��4�ֽڶ��� */ 
UINT8 CodeFlash_WriteBuf(UINT32 addr, PUINT32 pdat, UINT16 len);		/* CodeFlash �������32bitд����ַ��4�ֽڶ��� */	 
	 
// DataFlash ����
UINT8 DataFlash_BlockEarse(UINT32 addr);								/* DataFlash �������һ�β���512B */	 
UINT8 DataFlash_WriteDW(UINT32 addr, UINT32 dat);						/* DataFlash 32bitд����ַ��4�ֽڶ��� */
	 
	 
	 
	 
#ifdef __cplusplus
}
#endif

#endif  // __CH57x_FLASH_H__	

