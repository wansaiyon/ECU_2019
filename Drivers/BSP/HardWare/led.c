/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *�� �� ��: led.c
  *˵    ��: 
  *��    ��: V000B00D00
  *��������: 2019/01/22		00:42:07
  *�� �� ��: wansaiyon
  *�޸���Ϣ��  
================================================================================
  *�� �� ��    		  �޸�����       	  �޸����� 
  *<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#define LED_GLOBALS
//#include "Include.h"
#include "led.h"


/**********************************************************************************/
/*      ˽�б�������              	                                		      */
/**********************************************************************************/



/**********************************************************************************/
/*      ˽�к�������              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      ˽�к���ʵ��              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      ���к���ʵ��	             	                                              */
/**********************************************************************************/
/******************************************************************************
 * @�������ƣ�Led_Init
 * @�������ܣ�����LED��˸����������
 * @���������
 * 			  ledEn	 ����˸ʹ��  
 * 			  period ����˸����	��λ10ms
 * 			  cnt	 ����˸����	��λ1��
 * @���������void
 * @�㷨˼·��
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע�����cnt����ֵ��ҪС��125
 ******************************************************************************/
void vLed_Init(uint8_t ledEn,uint8_t period,uint8_t cnt)
{
	Led.En = ledEn;
	Led.Peroid = period;
	Led.Cnt = 2*cnt;
}

/******************************************************************************
 * @�������ƣ�Led_Start
 * @�������ܣ�����LED��˸
 * @���������
 * 			  		
 * @���������void
 * @�㷨˼·��
			 1.��10ms�ж��е��ô˺���
			 2.�򵥵�ON,OFF״̬��,���DesignDocument/stateflow_LED
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע�����
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
