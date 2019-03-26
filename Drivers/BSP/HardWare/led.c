/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: led.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/01/22		00:42:07
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define LED_GLOBALS
//#include "Include.h"
#include "led.h"


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
/******************************************************************************
 * @函数名称：Led_Init
 * @函数功能：设置LED闪烁次数、周期
 * @输入参数：
 * 			  ledEn	 ：闪烁使能  
 * 			  period ：闪烁周期	单位10ms
 * 			  cnt	 ：闪烁次数	单位1次
 * @输出参数：void
 * @算法思路：
 * @被调用的函数：
 * @使用资源：
 * @注意事项：cnt输入值需要小于125
 ******************************************************************************/
void vLed_Init(uint8_t ledEn,uint8_t period,uint8_t cnt)
{
	Led.En = ledEn;
	Led.Peroid = period;
	Led.Cnt = 2*cnt;
}

/******************************************************************************
 * @函数名称：Led_Start
 * @函数功能：启动LED闪烁
 * @输入参数：
 * 			  		
 * @输出参数：void
 * @算法思路：
			 1.在10ms中断中调用此函数
			 2.简单的ON,OFF状态机,详见DesignDocument/stateflow_LED
 * @被调用的函数：
 * @使用资源：
 * @注意事项：
 ******************************************************************************/
void vLed_Start(void)
{
	if (Led.Cnt>0)
	{
		Led.Tick++;
		if (Led.Tick>Led.Peroid)
		{
			Led.Tick=0;
			Led.Cnt--;
			switch (Led.En)
			{
				case LED1_GREEN_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
				break;
				case LED2_ORANGE_EN:
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
				break;
				case LED3_ORANGE_EN:
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
				break;
				case LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED3_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED2_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED2_ORANGE_EN|LED3_ORANGE_EN:
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
				break;
				
				case LED2_ORANGE_EN|LED3_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED1_GREEN_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED1_GREEN_EN|LED3_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
				break;
				
				case LED1_GREEN_EN|LED3_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED1_GREEN_EN|LED2_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
				break;
				
				case LED1_GREEN_EN|LED2_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				case LED1_GREEN_EN|LED2_ORANGE_EN|LED3_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
				break;
				
				case LED1_GREEN_EN|LED2_ORANGE_EN|LED3_ORANGE_EN|LED4_ORANGE_EN:
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
					HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
					HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
				break;
				
				default:
				break;
			}
		}
	}
}

void vLed_ShowSlaveID(void)
{
	vLed_Init(LED1_GREEN_EN|LED2_ORANGE_EN|LED3_ORANGE_EN|LED4_ORANGE_EN,LED_PERIOD_SYSINIT,LED_CNT_SYSINIT);
	//TODO
	DelayMs(1000);
	DelayMs(1000);
	if(usMBCRC16(hW25Qx.rData,SIZE_BLOCK1)==0x00)
	{
		vLed_Init(ECUInfo.ledBCDNum,LED_PERIOD_LOW,4);
		uint8_t i=ECUInfo.BeepNum;
		while(i--)
		{
			HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
			DelayMs(100);
			HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
			DelayMs(100);
		}
	}
	else
	{
		uint8_t cnt_ErrLoadFlash=7;
		do
		{
			HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
			DelayMs(50);
			HAL_GPIO_TogglePin(BEEP_GPIO_Port,BEEP_Pin);
			DelayMs(50);
		}while(--cnt_ErrLoadFlash);
	}
}








/*****************************************End of led.c*****************************************/
