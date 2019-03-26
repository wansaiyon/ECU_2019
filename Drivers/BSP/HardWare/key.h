/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*文 件 名: key.h
*说    明:
*版    本: V000B00D00
*创建日期: 2019/01/22		00:40:32
*创 建 人: wansaiyon
*修改信息：
================================================================================
*修 改 人    		  修改日期       	  修改内容
*<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
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
//KEY1,KEY2是否按下定义
#define  IS_KEY1_TOUCHED    (HAL_GPIO_ReadPin(B2_GPIO_Port,B2_Pin)==GPIO_PIN_RESET)
#define  IS_KEY2_TOUCHED    (HAL_GPIO_ReadPin(B3_GPIO_Port,B3_Pin)==GPIO_PIN_RESET)

//KEY事件绑定
#define  KEYEVENT_ATTACH(x)		{key->Mode_Now=(x);}

//KEY事件绑定
#define  KEY1EVENT_ATTACH(x)		{Key1.Mode_Now=(x);}
#define  KEY2EVENT_ATTACH(x)		{Key2.Mode_Now=(x);}

//是否进入KEY的某种模式
#define  IS_KEY1MODE(x)				(Key1.Mode_Now==(x))
#define  IS_KEY2MODE(x)				(Key2.Mode_Now==(x))

//KEY模式定义
#define  KEYMODE_NORMAL    		 (0x00)		//正常模式
#define  KEYMODE_SETECUID    	 (0x01) 	//ECU编号模式
#define  KEYMODE_READNW	    	 (0x02) 	//查询无线网络模式
#define  KEYMODE_REWRITENW  	 (0x04) 	//重新写入无线网络C1,C2,C3模式
#define  KEYMODE_REWRITENW_C1  (0x08) 	//重新写入无线网络C1模式
#define  KEYMODE_REWRITENW_C2  (0x10) 	//重新写入无线网络C2模式
#define  KEYMODE_REWRITENW_C3  (0x11) 	//重新写入无线网络C3模式
#define  KEYMODE_VCALIB   		 (0x12) 	//电压校准模式
#define  KEYMODE_RSTZIGBEE_1S	 (0x14) 	//复位Zigbee模式，RST拉低1s
#define  KEYMODE_RSTZIGBEE_5MIN (0x18) 	//复位Zigbee模式，RST拉低5min
#define  KEYMODE_NUMPARTBCU		 (0x20) 	//编号通讯异常BCU模式
#define  KEYMODE_NUMALLBCU		 (0x21) 	//编号所有BCU模式
#define  KEYMODE_PRINTECUINFO	 (0x22) 	//打印显示ECU基本信息模式

//调试模式
#define ECUTESTING			CC2530TEST_UPDOWNRATE
#if defined(ECUTESTING)
#define  KEYMODE_STARTTEST		 (0x24) 	//测试模式,用于通过按键开始实验测试
#endif




//KEY接触，释放、消抖时间定义,单位：10ms
#define  KEY_TOUCH_15S  (1500) 	//15S
#define  KEY_TOUCH_10S  (1000) 	//10S
#define  KEY_TOUCH_5S   (500) 	//5S
#define  KEY_TOUCH_2S   (200) 	//2S
#define  KEY_LEAVE_1s   (100) 	//1S
#define  KEY_LEAVE_2S   (200) 	//2S
#define  KEY_LEAVE_60S  (6000) 	//60S
#define  KEY_FILTER_TOUCH  (2)	//20ms
#define  KEY_FILTER_LEAVE  (3)	//30ms

//KEY返回正常模式定义
#define  KEY_NORMALMODE(x)	Key_Init(x)

//KEY连按次数定义,单位：次
#define  KEY_CNT_SINGLE_CLICK		(1)
#define  KEY_CNT_DOUBLE_CLICK		(2)
#define  KEY_CNT_TRIPLE_CLICK		(3)
#define  KEY_CNT_QUADRUPLE_CLICK	(4)
#define  KEY_CNT_QUINTUPLE_CLICK	(5)
#define  KEY_CNT_SEXTUPLE_CLICK		(6)
#define  KEY_CNT_SEPTUPLE_CLICK		(7)
#define  KEY_CNT_OCTUPLE_CLICK		(8)

//KEY连按、短按、长按时间定义,单位:：10ms
#define  KEY_TOUCHTIME_CLICKPRESS	KEY_TOUCH_2S		//连击要求每次按下时间小于2S
#define  KEY_TOUCHTIME_SHORTPRESS	KEY_TOUCH_5S		//短按要求每次按下时间大于2S，小于5秒
#define  KEY_TOUCHTIME_LONGPRESS	KEY_TOUCH_10S		//长按要求每次按下时间大于5S，小于10秒
/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
* @枚举功能 BCU按键结构体
*/
typedef struct
{
	uint16_t  touchTime;     //按下计时,单位:10ms
	uint16_t  releaseTime;   //离开计时,单位:10ms
	uint8_t			Cnt;     		 //按下次数
	uint8_t    Mode_Pre;     //上次的按键状态
	uint8_t    Mode_Now;     //当前的按键状态
	uint8_t    ModeTime;     //状态计数器,单位:s
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
