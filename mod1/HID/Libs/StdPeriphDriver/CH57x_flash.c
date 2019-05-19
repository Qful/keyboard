/********************************** (C) COPYRIGHT *******************************
* File Name          : CH57x_flash.c
* Author             : WCH
* Version            : V1.0
* Date               : 2018/12/15
* Description 
*******************************************************************************/

#include "CH57x_common.h"

/*******************************************************************************
* Function Name  : GetUniqueID
* Description    : ��ȡоƬΨһID��С��ģʽ��6B-ID�� 2B-CKS
* Input          : buf: �洢8�ֽڣ�ǰ6�ֽڣ�С�ˣ�ID����2�ֽڣ�С�ˣ�У���
* Return         : None
*******************************************************************************/
void GetUniqueID(PUINT8 buf)
{
    PUINT8  pID;
    UINT8   i;
    
    pID = (PUINT8)ROM_UUID_ADDR;
    for(i=0; i<8; i++)
    {
        *buf++ = *pID++;
    }    
}

/*******************************************************************************
* Function Name  : GetMACAddress
* Description    : ��ȡ����MAC��С��ģʽ��6B-MAC
* Input          : buf: �洢6�ֽڣ�6�ֽڣ�С�ˣ����� MAC
* Return         : None
*******************************************************************************/
void GetMACAddress(PUINT8 buf)
{
    PUINT8  pMAC;
    UINT8   i;
    
    pMAC = (PUINT8)ROM_MAC_ADDR;
    for(i=0; i<6; i++)
    {
        *buf++ = *pMAC++;
    }    
}

/*******************************************************************************
* Function Name  : CodeFlash_BlockEarse
* Description    : CodeFlash �������һ�β���512B
* Input          : addr: 32λ��ַ����Ҫ512����		   				
* Return         : FAILED  - ����
				   SUCCESS - �ɹ�
*******************************************************************************/
UINT8 CodeFlash_BlockEarse(UINT32 addr)
{
    UINT16  status = 0;

    if( addr & (0x200-1) )          return FAILED;

    R32_FLASH_ADDR = addr;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10|RB_ROM_DATA_WE|RB_ROM_CODE_WE;
    R8_FLASH_COMMAND = ROM_CMD_ERASE;
    status = R16_FLASH_STATUS;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if( status == RB_ROM_ADDR_OK )  return SUCCESS;
    else                            return FAILED;
}


/*******************************************************************************
* Function Name  : CodeFlash_WriteDW
* Description    : CodeFlash ˫��д����ַ��4�ֽڶ���
* Input          : addr: 32λ��ַ����Ҫ4����
				    dat: 32λд������
* Return         : FAILED  - ����
				   SUCCESS - �ɹ�
*******************************************************************************/
UINT8 CodeFlash_WriteDW(UINT32 addr, UINT32 dat)
{
    UINT16  status = 0;

    if( addr & (4-1) )              return FAILED;

    R32_FLASH_ADDR = addr;
    R32_FLASH_DATA = dat;	
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10|RB_ROM_DATA_WE|RB_ROM_CODE_WE;
    R8_FLASH_COMMAND = ROM_CMD_PROG;		
    status = R16_FLASH_STATUS;
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if( status == RB_ROM_ADDR_OK )  return SUCCESS;
    else                            return FAILED;
}

/*******************************************************************************
* Function Name  : CodeFlash_WriteBuf
* Description    : CodeFlash �������˫��д��
* Input          : addr: 32λ��ַ����Ҫ4����
				   pdat: ��д�����ݻ������׵�ַ
				    len: ��д�������ֽڳ���
* Return         : FAILED  - ����
				   SUCCESS - �ɹ�
*******************************************************************************/
UINT8 CodeFlash_WriteBuf(UINT32 addr, PUINT32 pdat, UINT16 len)
{
    UINT32  add = addr;
    PUINT32 p32 = pdat;
    UINT16  status = 0, i;	

    if( addr & (4-1) )              return FAILED;

    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10|RB_ROM_DATA_WE|RB_ROM_CODE_WE;
    for(i=0; i<len; i+=4)
    {
        R32_FLASH_ADDR = add;
        R32_FLASH_DATA = *p32++;		
        R8_FLASH_COMMAND = ROM_CMD_PROG;		
        add += 4;
        status = R16_FLASH_STATUS;
        if( status != RB_ROM_ADDR_OK )  break;
    }
    R8_FLASH_PROTECT = RB_ROM_WE_MUST_10;

    if( status == RB_ROM_ADDR_OK )  return SUCCESS;
    else                            return FAILED;
}

/*******************************************************************************
* Function Name  : DataFlash_BlockEarse
* Description    : DataFlash �������һ�β���512B
* Input          : addr: 32λ��ַ����Ҫ512����		   				
* Return         : FAILED  - ����
				   SUCCESS - �ɹ�
*******************************************************************************/
UINT8 DataFlash_BlockEarse(UINT32 addr)
{
    if( addr & (0x200-1) )          return FAILED;
    if( addr >= DATA_FLASH_SIZE )   return FAILED;

    return ( CodeFlash_BlockEarse(DATA_FLASH_ADDR+addr) );
	
}

/*******************************************************************************
* Function Name  : DataFlash_WriteDW
* Description    : DataFlash ˫��д����ַ��4�ֽڶ���
* Input          : addr: 32λ��ַ����Ҫ4����
				    dat: 32λд������
* Return         : FAILED  - ����
				   SUCCESS - �ɹ�
*******************************************************************************/
UINT8 DataFlash_WriteDW(UINT32 addr, UINT32 dat)
{
	
    if( addr & (4-1) )                  return FAILED;
    if( addr >= DATA_FLASH_SIZE )       return FAILED;

    return ( CodeFlash_WriteDW(DATA_FLASH_ADDR+addr, dat) );
}







