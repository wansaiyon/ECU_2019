/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: flashmemory.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/08		06:27:59
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define FLASHMEMORY_GLOBALS
//#include "Include.h"
#include "flashmemory.h"

/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/



/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/
void vLoad_FlashMemory(void)
{
	uint32_t i;
	uint16_t tempcrc;
	UNUSED(i);
	UNUSED(tempcrc);
	#if defined(PRINT_FLASHMEMORY)
	printf("\r\n SPI_W25Qxxx Loading... \r\n");
  #else
	if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
		printf("\r\n SPI_W25Qxxx Loading... \r\n");
	#endif
	
  /*##-1- Read the device ID  ########################*/ 
  ucBSP_W25Qx_Init();
  vBSP_W25Qx_Read_ID(hW25Qx.ID);
	#if defined(PRINT_FLASHMEMORY)
  printf(" W25Qxxx ID Is : 0x%02X 0x%02X \r\n",hW25Qx.ID[0],hW25Qx.ID[1]);
	#else
	if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
		printf(" W25Qxxx ID Is : 0x%02X 0x%02X \r\n",hW25Qx.ID[0],hW25Qx.ID[1]);
	#endif
	
	#if 0 
  /*##-2- Erase Block ##################################*/ 
  if(BSP_W25Qx_Erase_Block(0) == W25Qx_OK)
      printf(" Erase Block ok\r\n");
  else
      Error_Handler();
   
  /*##-3- Written to the flash ########################*/ 
  /* fill buffer */
  for(i =0;i<0xFF-2;i ++)
  {
		hW25Qx.wData[i] = i;
		hW25Qx.rData[i] = 0;
  }
	tempcrc=ModBusCRC(hW25Qx.wData,0xFF-2);
	hW25Qx.wData[0xFF-2] = (uint8_t)(tempcrc>>8);
	hW25Qx.wData[0xFF-1] = (uint8_t)tempcrc;
   
  if(BSP_W25Qx_Write(hW25Qx.wData,0x00,0x08)== W25Qx_OK)
      printf(" Write ok\r\n");
  else
      Error_Handler();
	#endif

  /*##-4- Read the flash     ########################*/ 
  if(ucBSP_W25Qx_Read(hW25Qx.rData,FLASHADDR_BLOCK1,SIZE_BLOCK1)== W25Qx_OK)
	{
		#if defined(PRINT_FLASHMEMORY)
      printf(" Read Ok\r\n");
		#else
		if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
			printf(" Read Ok\r\n");
		#endif
	}
  else
      Error_Handler();
	
  #if defined(PRINT_FLASHMEMORY) 
  printf(" Read Data : \r\n");
  for(i =0;i<SIZE_BLOCK1;i++)
      printf(" 0x%02X  ",hW25Qx.rData[i]);
  printf("\r\n");
	#else
	if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
	{
		printf(" Read Data : \r\n");
		for(i =0;i<SIZE_BLOCK1;i++)
				printf(" 0x%02X  ",hW25Qx.rData[i]);
		printf("\r\n");
	}
	#endif
   
  /*##-5- check date          ########################*/    
//  if(memcmp(hW25Qx.wData,hW25Qx.rData,0xFF) == 0 ) 
	if(usMBCRC16(hW25Qx.rData,SIZE_BLOCK1)==0x00)
	{
		#if defined(PRINT_FLASHMEMORY)
			printf(" SPI_W25Qxxx Load Ok \r\n\r\n");
		#else
		if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
			printf(" SPI_W25Qxxx Load Ok \r\n\r\n");
		#endif
	}
  else
	{
		#if defined(PRINT_FLASHMEMORY)
			printf(" SPI_W25Qxxx Load Err \r\n\r\n");
		#else
		if(GetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY))
			printf(" SPI_W25Qxxx Load Err \r\n\r\n");
		#endif
	}
	
	/*##- 6- assignment         ########################*/    
	#if defined(EN_W25Q16)
	ECUInfo.slaveID =hW25Qx.rData[0];
	ECUInfo.battJarNum =hW25Qx.rData[1];
	ECUInfo.nwPara.nwNum_C[0] =hW25Qx.rData[2];
	ECUInfo.nwPara.nwNum_C[1] =hW25Qx.rData[3];
	ECUInfo.nwPara.nwNum_C[2] =hW25Qx.rData[4];	
	#else	
	ECUInfo.slaveID =15;
	ECUInfo.battJarNum =120;
	ECUInfo.nwPara.nwNum_C[0] =4;
	ECUInfo.nwPara.nwNum_C[1] =12;
	ECUInfo.nwPara.nwNum_C[2] =28;
	#endif

//	ECUInfo.hall.HALL_A_Charge=hW25Qx.rData[5];
//	ECUInfo.hall.HALL_V_Charge=hW25Qx.rData[6];
//	ECUInfo.hall.HALL_A_DisCharge=hW25Qx.rData[7];
//	ECUInfo.hall.HALL_V_DisCharge=hW25Qx.rData[8];
//	ECUInfo.hall.HALL_A_LeakageCurr=hW25Qx.rData[9];
//	ECUInfo.hall.HALL_V_LeakageCurr=hW25Qx.rData[10];
}








/*****************************************End of flashmemory.c*****************************************/

