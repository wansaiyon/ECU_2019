/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: view.c
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/14		20:09:11
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/
  

#define VIEW_GLOBALS
#include "Include.h"


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

#if defined(EN_VIEWSTMSTD)
VIEW_EXT void vC1_CntView_Debug(void)
{
	cN1=Coordinator[0].rxCntNow[1-1];
	cN2=Coordinator[0].rxCntNow[2-1];
	cN3=Coordinator[0].rxCntNow[3-1];
	cN4=Coordinator[0].rxCntNow[4-1];
	cN5=Coordinator[0].rxCntNow[5-1];
	cN6=Coordinator[0].rxCntNow[6-1];
	cN7=Coordinator[0].rxCntNow[7-1];
	cN8=Coordinator[0].rxCntNow[8-1];
	cN9=Coordinator[0].rxCntNow[9-1];
	cN10=Coordinator[0].rxCntNow[10-1];
	cN11=Coordinator[0].rxCntNow[11-1];
	cN12=Coordinator[0].rxCntNow[12-1];
	cN13=Coordinator[0].rxCntNow[13-1];
	cN14=Coordinator[0].rxCntNow[14-1];
	cN15=Coordinator[0].rxCntNow[15-1];
	cN16=Coordinator[0].rxCntNow[16-1];
	cN17=Coordinator[0].rxCntNow[17-1];
	cN18=Coordinator[0].rxCntNow[18-1];
	cN19=Coordinator[0].rxCntNow[19-1];
	cN20=Coordinator[0].rxCntNow[20-1];
	cN21=Coordinator[0].rxCntNow[21-1];
	cN22=Coordinator[0].rxCntNow[22-1];
	cN23=Coordinator[0].rxCntNow[23-1];
	cN24=Coordinator[0].rxCntNow[24-1];
	cN25=Coordinator[0].rxCntNow[25-1];
	cN26=Coordinator[0].rxCntNow[26-1];
	cN27=Coordinator[0].rxCntNow[27-1];
	cN28=Coordinator[0].rxCntNow[28-1];
	cN29=Coordinator[0].rxCntNow[29-1];
	cN30=Coordinator[0].rxCntNow[30-1];
	cN31=Coordinator[0].rxCntNow[31-1];
	cN32=Coordinator[0].rxCntNow[32-1];
	cN33=Coordinator[0].rxCntNow[33-1];
	cN34=Coordinator[0].rxCntNow[34-1];
	cN35=Coordinator[0].rxCntNow[35-1];
	cN36=Coordinator[0].rxCntNow[36-1];
	cN37=Coordinator[0].rxCntNow[37-1];
	cN38=Coordinator[0].rxCntNow[38-1];
	cN39=Coordinator[0].rxCntNow[39-1];
	cN40=Coordinator[0].rxCntNow[40-1];
}
VIEW_EXT void vC2_CntView_Debug(void)
{
	cNN1=Coordinator[1].rxCntNow[1-1];
	cNN2=Coordinator[1].rxCntNow[2-1];
	cNN3=Coordinator[1].rxCntNow[3-1];
	cNN4=Coordinator[1].rxCntNow[4-1];
	cNN5=Coordinator[1].rxCntNow[5-1];
	cNN6=Coordinator[1].rxCntNow[6-1];
	cNN7=Coordinator[1].rxCntNow[7-1];
	cNN8=Coordinator[1].rxCntNow[8-1];
	cNN9=Coordinator[1].rxCntNow[9-1];
	cNN10=Coordinator[1].rxCntNow[10-1];
	cNN11=Coordinator[1].rxCntNow[11-1];
	cNN12=Coordinator[1].rxCntNow[12-1];
	cNN13=Coordinator[1].rxCntNow[13-1];
	cNN14=Coordinator[1].rxCntNow[14-1];
	cNN15=Coordinator[1].rxCntNow[15-1];
	cNN16=Coordinator[1].rxCntNow[16-1];
	cNN17=Coordinator[1].rxCntNow[17-1];
	cNN18=Coordinator[1].rxCntNow[18-1];
	cNN19=Coordinator[1].rxCntNow[19-1];
	cNN20=Coordinator[1].rxCntNow[20-1];
	cNN21=Coordinator[1].rxCntNow[21-1];
	cNN22=Coordinator[1].rxCntNow[22-1];
	cNN23=Coordinator[1].rxCntNow[23-1];
	cNN24=Coordinator[1].rxCntNow[24-1];
	cNN25=Coordinator[1].rxCntNow[25-1];
	cNN26=Coordinator[1].rxCntNow[26-1];
	cNN27=Coordinator[1].rxCntNow[27-1];
	cNN28=Coordinator[1].rxCntNow[28-1];
	cNN29=Coordinator[1].rxCntNow[29-1];
	cNN30=Coordinator[1].rxCntNow[30-1];
	cNN31=Coordinator[1].rxCntNow[31-1];
	cNN32=Coordinator[1].rxCntNow[32-1];
	cNN33=Coordinator[1].rxCntNow[33-1];
	cNN34=Coordinator[1].rxCntNow[34-1];
	cNN35=Coordinator[1].rxCntNow[35-1];
	cNN36=Coordinator[1].rxCntNow[36-1];
	cNN37=Coordinator[1].rxCntNow[37-1];
	cNN38=Coordinator[1].rxCntNow[38-1];
	cNN39=Coordinator[1].rxCntNow[39-1];
	cNN40=Coordinator[1].rxCntNow[40-1];
}
VIEW_EXT void vC3_CntView_Debug(void)
{
	cNNN1=Coordinator[2].rxCntNow[1-1];
	cNNN2=Coordinator[2].rxCntNow[2-1];
	cNNN3=Coordinator[2].rxCntNow[3-1];
	cNNN4=Coordinator[2].rxCntNow[4-1];
	cNNN5=Coordinator[2].rxCntNow[5-1];
	cNNN6=Coordinator[2].rxCntNow[6-1];
	cNNN7=Coordinator[2].rxCntNow[7-1];
	cNNN8=Coordinator[2].rxCntNow[8-1];
	cNNN9=Coordinator[2].rxCntNow[9-1];
	cNNN10=Coordinator[2].rxCntNow[10-1];
	cNNN11=Coordinator[2].rxCntNow[11-1];
	cNNN12=Coordinator[2].rxCntNow[12-1];
	cNNN13=Coordinator[2].rxCntNow[13-1];
	cNNN14=Coordinator[2].rxCntNow[14-1];
	cNNN15=Coordinator[2].rxCntNow[15-1];
	cNNN16=Coordinator[2].rxCntNow[16-1];
	cNNN17=Coordinator[2].rxCntNow[17-1];
	cNNN18=Coordinator[2].rxCntNow[18-1];
	cNNN19=Coordinator[2].rxCntNow[19-1];
	cNNN20=Coordinator[2].rxCntNow[20-1];
	cNNN21=Coordinator[2].rxCntNow[21-1];
	cNNN22=Coordinator[2].rxCntNow[22-1];
	cNNN23=Coordinator[2].rxCntNow[23-1];
	cNNN24=Coordinator[2].rxCntNow[24-1];
	cNNN25=Coordinator[2].rxCntNow[25-1];
	cNNN26=Coordinator[2].rxCntNow[26-1];
	cNNN27=Coordinator[2].rxCntNow[27-1];
	cNNN28=Coordinator[2].rxCntNow[28-1];
	cNNN29=Coordinator[2].rxCntNow[29-1];
	cNNN30=Coordinator[2].rxCntNow[30-1];
	cNNN31=Coordinator[2].rxCntNow[31-1];
	cNNN32=Coordinator[2].rxCntNow[32-1];
	cNNN33=Coordinator[2].rxCntNow[33-1];
	cNNN34=Coordinator[2].rxCntNow[34-1];
	cNNN35=Coordinator[2].rxCntNow[35-1];
	cNNN36=Coordinator[2].rxCntNow[36-1];
	cNNN37=Coordinator[2].rxCntNow[37-1];
	cNNN38=Coordinator[2].rxCntNow[38-1];
	cNNN39=Coordinator[2].rxCntNow[39-1];
	cNNN40=Coordinator[2].rxCntNow[40-1];
}
#endif

















/*****************************************End of view.c*****************************************/
