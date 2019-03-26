/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*�� �� ��: key.h
*˵    ��:
*��    ��: V000B00D00
*��������: 2019/01/22		00:40:32
*�� �� ��: wansaiyon
*�޸���Ϣ��
================================================================================
*�� �� ��    		  �޸�����       	  �޸�����
*<����/�޸���>      <YYYY/MM/DD>		  <�޸�����>
********************************************************************************
*/

#ifndef KEY_H_
#define	KEY_H_

#ifdef KEY_GLOBALS
#define KEY_EXT
#else
#define  KEY_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
#define KEY_DEBUG
//KEY1,KEY2�Ƿ��¶���
#define  IS_KEY1_TOUCHED    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
#define  IS_KEY2_TOUCHED    (HAL_GPIO_ReadPin(B3_GPIO_Port,B3_Pin)==GPIO_PIN_RESET)

//KEY�¼���
#define  KEYEVENT_ATTACH(x)		{key->Mode_Now=(x);}

//KEY�¼���
#define  KEY1EVENT_ATTACH(x)		{Key1.Mode_Now=(x);}
#define  KEY2EVENT_ATTACH(x)		{Key2.Mode_Now=(x);}

//�Ƿ����KEY��ĳ��ģʽ
#define  IS_KEY1MODE(x)				(Key1.Mode_Now==(x))
#define  IS_KEY2MODE(x)				(Key2.Mode_Now==(x))

//KEYģʽ����
#define  KEYMODE_NORMAL    		 (0x00)		//����ģʽ
#define  KEYMODE_SETECUID    	 (0x01) 	//ECU���ģʽ
#define  KEYMODE_READNW	    	 (0x02) 	//��ѯ��������ģʽ
#define  KEYMODE_REWRITENW  	 (0x04) 	//����д����������C1,C2,C3ģʽ
#define  KEYMODE_REWRITENW_C1  (0x08) 	//����д����������C1ģʽ
#define  KEYMODE_REWRITENW_C2  (0x10) 	//����д����������C2ģʽ
#define  KEYMODE_REWRITENW_C3  (0x11) 	//����д����������C3ģʽ
#define  KEYMODE_VCALIB   		 (0x12) 	//��ѹУ׼ģʽ
#define  KEYMODE_RSTZIGBEE_1S	 (0x14) 	//��λZigbeeģʽ��RST����1s
#define  KEYMODE_RSTZIGBEE_5MIN (0x18) 	//��λZigbeeģʽ��RST����5min
#define  KEYMODE_NUMPARTBCU		 (0x20) 	//���ͨѶ�쳣BCUģʽ
#define  KEYMODE_NUMALLBCU		 (0x21) 	//�������BCUģʽ
#define  KEYMODE_PRINTECUINFO	 (0x22) 	//��ӡ��ʾECU������Ϣģʽ

//����ģʽ
#define ECUTESTING			CC2530TEST_UPDOWNRATE
#if defined(ECUTESTING)
#define  KEYMODE_STARTTEST		 (0x24) 	//����ģʽ,����ͨ��������ʼʵ�����
#endif




//KEY�Ӵ����ͷš�����ʱ�䶨��,��λ��10ms
#define  KEY_TOUCH_15S  (1500) 	//15S
#define  KEY_TOUCH_10S  (1000) 	//10S
#define  KEY_TOUCH_5S   (500) 	//5S
#define  KEY_TOUCH_2S   (200) 	//2S
#define  KEY_LEAVE_1s   (100) 	//1S
#define  KEY_LEAVE_2S   (200) 	//2S
#define  KEY_LEAVE_60S  (6000) 	//60S
#define  KEY_FILTER_TOUCH  (2)	//20ms
#define  KEY_FILTER_LEAVE  (3)	//30ms

//KEY��������ģʽ����
#define  KEY_NORMALMODE(x)	Key_Init(x)

//KEY������������,��λ����
#define  KEY_CNT_SINGLE_CLICK		(1)
#define  KEY_CNT_DOUBLE_CLICK		(2)
#define  KEY_CNT_TRIPLE_CLICK		(3)
#define  KEY_CNT_QUADRUPLE_CLICK	(4)
#define  KEY_CNT_QUINTUPLE_CLICK	(5)
#define  KEY_CNT_SEXTUPLE_CLICK		(6)
#define  KEY_CNT_SEPTUPLE_CLICK		(7)
#define  KEY_CNT_OCTUPLE_CLICK		(8)

//KEY�������̰�������ʱ�䶨��,��λ:��10ms
#define  KEY_TOUCHTIME_CLICKPRESS	KEY_TOUCH_2S		//����Ҫ��ÿ�ΰ���ʱ��С��2S
#define  KEY_TOUCHTIME_SHORTPRESS	KEY_TOUCH_5S		//�̰�Ҫ��ÿ�ΰ���ʱ�����2S��С��5��
#define  KEY_TOUCHTIME_LONGPRESS	KEY_TOUCH_10S		//����Ҫ��ÿ�ΰ���ʱ�����5S��С��10��
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @ö�ٹ��� BCU�����ṹ��
*/
typedef struct
{
	uint16_t  touchTime;     //���¼�ʱ,��λ:10ms
	uint16_t  releaseTime;   //�뿪��ʱ,��λ:10ms
	uint8_t			Cnt;     		 //���´���
	uint8_t    Mode_Pre;     //�ϴεİ���״̬
	uint8_t    Mode_Now;     //��ǰ�İ���״̬
	uint8_t    ModeTime;     //״̬������,��λ:s
}Key_TypeDef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
KEY_EXT Key_TypeDef Key1;
KEY_EXT Key_TypeDef Key2;
/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
KEY_EXT void vKey_Init(Key_TypeDef *key);
KEY_EXT void vGet_Key1Event(void);
KEY_EXT void vGet_Key2Event(void);
KEY_EXT void vKeyEvent_Proc(Key_TypeDef *key);
#endif /* KEY_H_ */
