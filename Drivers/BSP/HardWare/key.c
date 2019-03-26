/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*�� �� ��: key.c
*˵    ��:
*��    ��: V000B00D00
*��������: 2019/01/22		00:41:57
*�� �� ��: wansaiyon
*�޸���Ϣ��
================================================================================
*�� �� ��    		  �޸�����       	  �޸�����
*<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#define KEY_GLOBALS
//#include "Include.h"
#include "key.h"


/**********************************************************************************/
/*      ˽�б�������              	                                		      */
/**********************************************************************************/
//TODO Delete
extern void vHAL_WriteReg1000(UART_HandleTypeDef *huart,CoordinatorX_TypeDef cx,REG1000_TypeDef reg1000Type,CC2530NWADD_TypeDef nwAddType);


/**********************************************************************************/
/*      ˽�к�������              	                                              */
/**********************************************************************************/
static void vGet_ClickPressEvent_Key1(Key_TypeDef *key);
static void vGet_ClickPressEvent_Key2(Key_TypeDef *key);
static void vNotice_ShortLongPressEvent_Key1(Key_TypeDef *key);
static void vNotice_ShortLongPressEvent_Key2(Key_TypeDef *key);


/**********************************************************************************/
/*      ˽�к���ʵ��              	                                              */
/**********************************************************************************/

/******************************************************************************
 * @�������ƣ�Get_ClickPressEvent_Key1
 * @�������ܣ���ȡ�㰴�¼�
 * @���������void  		
 * @���������void
 * @�㷨˼·��
			�㰴�ַ�Ϊ��������˫�����������Ļ�
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע���������ʱҪ��ÿ�ΰ��µ�ʱ������2s,�����������1s
 ******************************************************************************/
static void vGet_ClickPressEvent_Key1(Key_TypeDef *key)
{
	if(Key1.releaseTime>KEY_LEAVE_1s)
	{
		switch (Key1.Cnt)
		{
			case KEY_CNT_SINGLE_CLICK:
			//singleClick��attach something
			KEY1EVENT_ATTACH(KEYMODE_NORMAL);
			#if defined(PRINT_KEY)
			printf("\r\nKey1 singleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
			
			case KEY_CNT_DOUBLE_CLICK:
			//doubleClick��attach something
			KEY1EVENT_ATTACH(KEYMODE_SETECUID);
			#if defined(PRINT_KEY)
			printf("\r\nKey1 doubleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;		
			
			case KEY_CNT_TRIPLE_CLICK:
			//tripleClick��attach something
			#if defined(ECUTESTING)
			KEY1EVENT_ATTACH(KEYMODE_STARTTEST);
			#endif
			#if defined(PRINT_KEY)
			printf("\r\nKey1 tripleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;

			case KEY_CNT_QUINTUPLE_CLICK:
			//quintupleClick��attach something
			KEY1EVENT_ATTACH(KEYMODE_PRINTECUINFO);
			#if defined(PRINT_KEY)
			printf("\r\nKey1 quintupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;

#if 0					
			case KEY_CNT_QUADRUPLE_CLICK:
			//quadrupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey1 quadrupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
			
			case KEY_CNT_QUINTUPLE_CLICK:
			//quintupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey1 quintupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
			
			case KEY_CNT_SEXTUPLE_CLICK:
			//sextupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey1 sextupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
			
			case KEY_CNT_SEPTUPLE_CLICK:
			//septupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey1 septupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
			
			case KEY_CNT_OCTUPLE_CLICK:
			//octupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey1 octupleClick,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
			Key1.Cnt = 0;
			break;
#endif
			default:
			Key1.Cnt = 0;
			break;
		}
	}
}

/******************************************************************************
 * @�������ƣ�Get_ClickPressEvent_Key2
 * @�������ܣ���ȡ�㰴�¼�
 * @���������void  		
 * @���������void
 * @�㷨˼·��
			�㰴�ַ�Ϊ��������˫�����������Ļ�
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע���������ʱҪ��ÿ�ΰ��µ�ʱ������2s,�����������1s
 ******************************************************************************/
static void vGet_ClickPressEvent_Key2(Key_TypeDef *key)
{
	if(Key2.releaseTime>KEY_LEAVE_1s)
	{
		switch (Key2.Cnt)
		{
			case KEY_CNT_SINGLE_CLICK:
			//singleClick��attach something
			KEY2EVENT_ATTACH(KEYMODE_NORMAL);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 singleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
			case KEY_CNT_DOUBLE_CLICK:
			//doubleClick��attach something
			KEY2EVENT_ATTACH(KEYMODE_REWRITENW_C1);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 doubleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
		
			case KEY_CNT_TRIPLE_CLICK:
			//tripleClick��attach something
			KEY2EVENT_ATTACH(KEYMODE_REWRITENW_C2);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 tripleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
			case KEY_CNT_QUADRUPLE_CLICK:
			//quadrupleClick��attach something
			KEY2EVENT_ATTACH(KEYMODE_REWRITENW_C3);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 quadrupleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
			case KEY_CNT_QUINTUPLE_CLICK:
			//quintupleClick��attach something
			KEY2EVENT_ATTACH(KEYMODE_REWRITENW);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 quintupleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;			
#if 0			
			case KEY_CNT_SEXTUPLE_CLICK:
			//sextupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey2 sextupleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
			case KEY_CNT_SEPTUPLE_CLICK:
			//septupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey2 septupleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
			
			case KEY_CNT_OCTUPLE_CLICK:
			//octupleClick��attach something
			#if defined(PRINT_KEY)
			printf("\r\nKey2 octupleClick,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
			Key2.Cnt = 0;
			break;
#endif
			default:
			Key2.Cnt = 0;
			break;
		}
	}
}

/******************************************************************************
 * @�������ƣ�Notice_ShortLongPressEvent_Key1
 * @�������ܣ������û��̰�������ʱ�䵽�ˣ������ɿ�������
 * @���������
 * 			  		
 * @���������void
 * @�㷨˼·��
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע�����
 ******************************************************************************/
static void vNotice_ShortLongPressEvent_Key1(Key_TypeDef *key)
{
	if (Key1.touchTime>KEY_TOUCHTIME_CLICKPRESS)
	{
		#if defined(PRINT_KEY)
		printf("\r\nNotice_Key1ShortPress\r\n");
		#endif
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		if(Key1.touchTime>KEY_TOUCHTIME_SHORTPRESS)
		{
			#if defined(PRINT_KEY)
			printf("\r\nNotice_Key1LongPress\r\n");
			#endif
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
		}
	}
}

/******************************************************************************
 * @�������ƣ�Notice_ShortLongPressEvent_Key2
 * @�������ܣ������û��̰�������ʱ�䵽�ˣ������ɿ�������
 * @���������
 * 			  		
 * @���������void
 * @�㷨˼·��
 * @�����õĺ�����
 * @ʹ����Դ��
 * @ע�����
 ******************************************************************************/
static void vNotice_ShortLongPressEvent_Key2(Key_TypeDef *key)
{
	if (Key2.touchTime>KEY_TOUCHTIME_CLICKPRESS)
	{
		#if defined(PRINT_KEY)
		printf("\r\nNotice_Key2ShortPress\r\n");
		#endif
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		if (Key2.touchTime>KEY_TOUCHTIME_SHORTPRESS)
		{
			#if defined(PRINT_KEY)
			printf("\r\nNotice_Key2LongPress\r\n");
			#endif
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
		}
	}
}

/**********************************************************************************/
/*      ���к���ʵ��	             	                                              */
/**********************************************************************************/

/******************************************************************************
* @�������ƣ�void Key_Init(Key_TypeDef *key)
* @�������ܣ���ʼ��
* @���������
* @���������
* @�㷨˼·��
* @ʹ����Դ��
* @ע�����
******************************************************************************/
void vKey_Init(Key_TypeDef *key)
{
	UNUSED(vKey_Init);//TODO Delete
	key->Mode_Pre=KEYMODE_NORMAL;
	key->Mode_Now=KEYMODE_NORMAL;
	key->ModeTime=0;
}

/******************************************************************************
* @�������ƣ�Get_Key1Event
* @�������ܣ���ȡ�����󶨣������¼�
* @���������
* @���������
* @�㷨˼·��
			1.����ȡ�İ����¼���Ϊ�����ࣺ�㰴���̰�������
				a���㰴�ַ�Ϊ��������˫�����������Ļ�
				b���̰���2~5s
				c��������5~10s
			2.��10ms��ʱ���ж��л�ȡ�����¼�
			3.�󶨰����¼���TODO����û��ʲô�ɶ��ԣ�
* @ʹ����Դ��
* @ע�����
******************************************************************************/
void vGet_Key1Event(void)
{
	vGet_ClickPressEvent_Key1(&Key1);//����¼���������˫�����������Ļ���
	if(IS_KEY1_TOUCHED)
	{
		Key1.touchTime++;
		Key1.releaseTime=0;
		vNotice_ShortLongPressEvent_Key1(&Key1);
	}
	else if(!IS_KEY1_TOUCHED)
	{
		Key1.releaseTime++;
		//debouce
		if((Key1.touchTime<=KEY_FILTER_TOUCH) || (Key1.releaseTime<KEY_FILTER_LEAVE))return;
		
		//shortPress��attach something
		if((Key1.touchTime<KEY_TOUCHTIME_SHORTPRESS) && (Key1.touchTime>KEY_TOUCHTIME_CLICKPRESS))
		{
			KEY1EVENT_ATTACH(KEYMODE_NUMPARTBCU);
			#if defined(PRINT_KEY)
			printf("\r\nKey1 shortPress,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
		}
		//longPress��attach something
		else if((Key1.touchTime<KEY_TOUCHTIME_LONGPRESS) && (Key1.touchTime>KEY_TOUCHTIME_SHORTPRESS))
		{
			KEY1EVENT_ATTACH(KEYMODE_NUMALLBCU);
			#if defined(PRINT_KEY)
			printf("\r\nKey1 longPress,Key1.Mode:0x%0X\r\n",Key1.Mode_Now);
			#endif
		}
		//clickPress��KeyCnt++
		else if (Key1.touchTime<KEY_TOUCHTIME_CLICKPRESS)
		{
			Key1.Cnt++;
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
			HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		}
		Key1.touchTime=0;
	}
}

/******************************************************************************
* @�������ƣ�Get_Key2Event
* @�������ܣ���ȡ�����󶨣������¼�
* @���������
* @���������
* @�㷨˼·��
			1.����ȡ�İ����¼���Ϊ�����ࣺ�㰴���̰�������
				a���㰴�ַ�Ϊ��������˫�����������Ļ�
				b���̰���2~5s
				c��������5~10s
			2.��10ms��ʱ���ж��л�ȡ�����¼�
			3.�󶨰����¼�
* @ʹ����Դ��
* @ע�����
******************************************************************************/
void vGet_Key2Event(void)
{
	vGet_ClickPressEvent_Key2(&Key2);//����¼���������˫�����������Ļ���
	if(IS_KEY2_TOUCHED)
	{
		Key2.touchTime++;
		Key2.releaseTime=0;
		vNotice_ShortLongPressEvent_Key2(&Key2);
	}
	else if(!IS_KEY2_TOUCHED)
	{
		Key2.releaseTime++;
		//debouce
		if((Key2.touchTime<=KEY_FILTER_TOUCH) || (Key2.releaseTime<KEY_FILTER_LEAVE))return;
		
		//shortPress���̰��¼���attach something
		if((Key2.touchTime<KEY_TOUCHTIME_SHORTPRESS) && (Key2.touchTime>KEY_TOUCHTIME_CLICKPRESS))
		{
			KEY2EVENT_ATTACH(KEYMODE_READNW);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 shortPress,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
		}
		//longPress�������¼���attach something
		else if((Key2.touchTime<KEY_TOUCHTIME_LONGPRESS) && (Key2.touchTime>KEY_TOUCHTIME_SHORTPRESS))
		{
			KEY2EVENT_ATTACH(KEYMODE_RSTZIGBEE_5MIN);
			#if defined(PRINT_KEY)
			printf("\r\nKey2 longPress,Key2.Mode:0x%0X\r\n",Key2.Mode_Now);
			#endif
		}
		//clickPress������¼�,KeyCnt++
		else if (Key2.touchTime<KEY_TOUCHTIME_CLICKPRESS)
		{
			Key2.Cnt++;
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
			HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
			HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		}
		Key2.touchTime=0;
	}
}

/******************************************************************************
* @�������ƣ�void KeyEvent_Proc(void)
* @�������ܣ���Ӧ����ͬ�İ����¼�
* @���������
* @���������
* @�㷨˼·��
* @ʹ����Դ��
* @ע�����
******************************************************************************/
void vKeyEvent_Proc( Key_TypeDef *key )
{
	if(key==&Key1)
	{
		switch(Key1.Mode_Now)
		{
			case KEYMODE_NUMPARTBCU:
			
			break;			
			case KEYMODE_NUMALLBCU:
			
			break;
			
			case KEYMODE_SETECUID:
				vLed_Init(LED1_GREEN_EN,LED_PERIOD_NUMECU,LED_CNT_NUMECU);
				ECUMODE_ATTACH(ECUMODE_CfgNw);
			break;
			
			case KEYMODE_PRINTECUINFO:
				SetBit(ECUInfo.print,BIT_PRINT_FLASHMEMORY);
				vPrint_ECUInformation();
				KEY1EVENT_ATTACH(KEYMODE_NORMAL);
			break;
			
			#if defined(ECUTESTING)
			case KEYMODE_STARTTEST:
				//TODO Delete,�������������еð���ʵ�鷢������
				#if defined(CC2530TEST_UPDOWNRATE)
				if(tagTime_Reg1000)
				{
					tagTime_Reg1000=0x00;
					HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
					vHAL_WriteReg1000(&Coordinator1_Usart,CC2530PA2S_C1,REG1000_M2O_RSTBCU,NWADD_USERDEF);
					vHAL_WriteReg1000(&Coordinator2_Usart,CC2530PA2S_C2,REG1000_M2O_RSTBCU,NWADD_USERDEF);
					vHAL_WriteReg1000(&Coordinator3_Usart,CC2530PA2S_C3,REG1000_M2O_RSTBCU,NWADD_USERDEF);
				}
				#endif
				break;
			#endif
			
			default:
			break;
		}
	}
	if(key==&Key2)
	{
		switch(Key2.Mode_Now)
		{
			case KEYMODE_READNW:
				ECUMODE_ATTACH(ECUMODE_ReadNw);		
			break;
			
			case KEYMODE_RSTZIGBEE_5MIN:
			
			break;
			
			case KEYMODE_REWRITENW_C1:
				ECUMODE_ATTACH(ECUMODE_CfgNw);
				ECUInfo.nwPara.WriteNw_En =WRITENW_C1_EN;
			
			break;
			
			case KEYMODE_REWRITENW_C2:
				ECUMODE_ATTACH(ECUMODE_CfgNw);
				ECUInfo.nwPara.WriteNw_En =WRITENW_C2_EN;
			
			break;
			
			case KEYMODE_REWRITENW_C3:
				ECUMODE_ATTACH(ECUMODE_CfgNw);
				ECUInfo.nwPara.WriteNw_En =WRITENW_C3_EN;
			
			break;
			
			case KEYMODE_REWRITENW:
				ECUMODE_ATTACH(ECUMODE_CfgNw);
				ECUInfo.nwPara.WriteNw_En =WRITENW_C1_EN|WRITENW_C2_EN|WRITENW_C3_EN;
			break;
			
			default:
			break;
		}
	}
}



/*****************************************End of key.c*****************************************/
