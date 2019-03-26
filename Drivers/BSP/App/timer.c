/*
********************************************************************************
*Copyright (C), 2019, CunXin_ All Rights Reserved
*文 件 名: timer.c
*说    明:
*版    本: V000B00D00
*创建日期: 2019/01/22		00:42:25
*创 建 人: wansaiyon
*修改信息：
================================================================================
*修 改 人    		  修改日期       	  修改内容
*<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#define TIMER_GLOBALS
//#include "Include.h"
#include "timer.h"

/**********************************************************************************/
/*      私有变量声明              	                                		      */
/**********************************************************************************/
#if !defined(EN_FREERTOS)
extern RTC_HandleTypeDef hrtc;
#endif


/**********************************************************************************/
/*      私有函数声明              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      私有函数实现              	                                              */
/**********************************************************************************/





/**********************************************************************************/
/*      公有函数实现	             	                                              */
/**********************************************************************************/
#if !defined(EN_FREERTOS)
/**
  * @brief  Period elapsed callback in non blocking mode 
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *                the configuration information for TIM module.
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if(htim->Instance==TIM1)
  	{
  		t1Tick1ms++;		
				
			HAL_RTC_GetTime(&hrtc,&ECUInfo.ECUOnLineTime.time,RTC_FORMAT_BIN);
			HAL_RTC_GetDate(&hrtc,&ECUInfo.ECUOnLineTime.data,RTC_FORMAT_BIN);
			
			if(t1Tick1ms%10==0)
			{
					tag_10ms=1;
				
					vLed_Start();
					vGet_Key1Event();
					vGet_Key2Event();
			}
			if((t1Tick1ms%100==0) && !ECUInfo.En_IwdgRst)
			{
					tag_100ms=1;
					HAL_IWDG_Refresh(&hiwdg);	
			}
			if(t1Tick1ms%250==0)
			{
					tag_250ms=1;						
			}
			if(t1Tick1ms%500==0)
			{
					tag_500ms=1;			
			}
			if(t1Tick1ms%1000==0)
			{
					tag_1s=1;	
					vECUOnLineTime_Update();			
			}
			if(t1Tick1ms%Period_WrReg1000_Defaul==0)
			{
					tagTime_Reg1000=1;
			}
			
			if(t1Tick1ms%2000==0)
			{
					tag_2s=1;
			}
			if(t1Tick1ms%5000==0)
			{
					tag_5s=1;
			}
			if(t1Tick1ms%10000==0)
			{
					tag_10s=1;
			}
			if(t1Tick1ms%15000==0)
			{
					tag_15s=1;
			}
			if(ECUInfo.nwPara.WriteNw_En && (t1Tick1ms%ECUInfo.nwPara.periodWriteNw==0))
			{
				ECUInfo.nwPara.tag_WriteNw=1;
			}
			if(ECUInfo.nwPara.ReadNw_En && (t1Tick1ms%ECUInfo.nwPara.periodReadNw==0))
			{
				ECUInfo.nwPara.tag_ReadNw=1;
			}
			
  	}
		if(htim->Instance==TIM4)
		{
		}
}
#endif

/*****************************************End of timer.c*****************************************/
