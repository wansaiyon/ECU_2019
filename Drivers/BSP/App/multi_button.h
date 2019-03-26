/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: multi_button.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/01/23		00:09:46
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef MULTI_BUTTON_H_
#define	MULTI_BUTTON_H_

#ifdef MULTI_BUTTON_GLOBALS
#define MULTI_BUTTON_EXT
#else
#define  MULTI_BUTTON_EXT extern
#endif

#include "Include.h"
//#include "stdint.h"
//#include "string.h"

/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//According to your need to modify the constants.
#define TICKS_INTERVAL    5	//ms
#define DEBOUNCE_TICKS    3	//MAX 8
#define SHORT_TICKS       (300 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/
typedef void (*BtnCallback)(void*);

typedef enum {
	PRESS_DOWN = 0,
	PRESS_UP,
	PRESS_REPEAT,
	SINGLE_CLICK,
	DOUBLE_CLICK,
	LONG_RRESS_START,
	LONG_PRESS_HOLD,
	number_of_event,
	NONE_PRESS
}PressEvent;


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
typedef struct Button {
	uint16_t ticks;
	uint8_t  repeat : 4;
	uint8_t  event : 4;
	uint8_t  state : 3;
	uint8_t  debounce_cnt : 3;
	uint8_t  active_level : 1;
	uint8_t  button_level : 1;
	uint8_t  (*hal_button_Level)(void);
	BtnCallback  cb[number_of_event];
	struct Button* next;
}Button;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/


/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
#ifdef __cplusplus
extern "C" {
	#endif

	void vbutton_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
	void vbutton_attach(struct Button* handle, PressEvent event, BtnCallback cb);
	PressEvent eget_button_event(struct Button* handle);
	int  lbutton_start(struct Button* handle);
	void vbutton_stop(struct Button* handle);
	void vbutton_ticks(void);

	#ifdef __cplusplus
}
#endif


#endif /* MULTI_BUTTON_H_ */

