/*
********************************************************************************
  *Copyright (C), 2019, CunXin_ All Rights Reserved
  *文 件 名: w25qxx.h
  *说    明: 
  *版    本: V000B00D00
  *创建日期: 2019/03/02		01:38:28
  *创 建 人: wansaiyon
  *修改信息：  
================================================================================
  *修 改 人    		  修改日期       	  修改内容 
  *<作者/修改者>      <YYYY/MM/DD>		  <修改内容>
********************************************************************************
*/

#ifndef W25QXX_H_
#define	W25QXX_H_

#ifdef W25QXX_GLOBALS
#define W25QXX_EXT
#else
#define  W25QXX_EXT extern
#endif

#include "Include.h"
//#include "stm32f4xx.h"
//#include "spi.h"
/*================================================================================*/
/*                     	     	MacroDef_01	                                      */
/*================================================================================*/
//W25X系列/Q系列芯片列表	   
//W25Q80  ID  0XEF13
//W25Q16  ID  0XEF14
//W25Q32  ID  0XEF15
//W25Q64  ID  0XEF16	
//W25Q128 ID  0XEF17	
#define W25Q80 	(0XEF13)
#define W25Q16 	(0XEF14)
#define W25Q32 	(0XEF15)
#define W25Q64 	(0XEF16)
#define W25Q128	(0XEF17)

#define W25Q128FV_FLASH_SIZE                  0x1000000 /* 128 MBits => 16MBytes */
#define W25Q128FV_SECTOR_SIZE                 0x10000   /* 256 sectors of 64KBytes */
#define W25Q128FV_SUBSECTOR_SIZE              0x1000    /* 4096 subsectors of 4kBytes */
#define W25Q128FV_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */\

#define W25Q16FV_FLASH_SIZE                  0x200000  /* 16 MBits => 2MBytes */
#define W25Q16FV_SECTOR_SIZE                 0x10000   /* 32 sectors of 64KBytes */
#define W25Q16FV_SUBSECTOR_SIZE              0x1000    /* 4096 subsectors of 4kBytes */
#define W25Q16FV_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */

#define W25Q128FV_DUMMY_CYCLES_READ           4
#define W25Q128FV_DUMMY_CYCLES_READ_QUAD      10

#define W25Q128FV_BULK_ERASE_MAX_TIME         250000
#define W25Q128FV_SECTOR_ERASE_MAX_TIME       3000
#define W25Q128FV_SUBSECTOR_ERASE_MAX_TIME    800
#define W25Qx_TIMEOUT_VALUE 1000

/** 
  * @brief  W25Q128FV Commands  
  */  
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

#define ENTER_QPI_MODE_CMD                   0x38
#define EXIT_QPI_MODE_CMD                    0xFF

/* Identification Operations */
#define READ_ID_CMD                          0x90
#define DUAL_READ_ID_CMD                     0x92
#define QUAD_READ_ID_CMD                     0x94
#define READ_JEDEC_ID_CMD                    0x9F

/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15

#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define QUAD_INPUT_PAGE_PROG_CMD             0x32

/* Erase Operations */
#define SECTOR_ERASE_CMD                     0x20
#define CHIP_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* Flag Status Register */
#define W25Q128FV_FSR_BUSY                    ((uint8_t)0x01)    /*!< busy */
#define W25Q128FV_FSR_WREN                    ((uint8_t)0x02)    /*!< write enable */
#define W25Q128FV_FSR_QE                      ((uint8_t)0x02)    /*!< quad enable */

#define W25Qx_Enable() 			HAL_GPIO_WritePin(W25X16_CS_GPIO_Port, W25X16_CS_Pin, GPIO_PIN_RESET)
#define W25Qx_Disable() 		HAL_GPIO_WritePin(W25X16_CS_GPIO_Port, W25X16_CS_Pin, GPIO_PIN_SET)

#define W25Qx_OK            ((uint8_t)0x00)
#define W25Qx_ERROR         ((uint8_t)0x01)
#define W25Qx_BUSY          ((uint8_t)0x02)
#define W25Qx_TIMEOUT				((uint8_t)0x03)

#define W25QX_WR_LEN				(0x100)
#ifndef W25QX_RD_LEN
#define W25QX_RD_LEN				(0x100)
#endif

/*================================================================================*/
/*                     	     	EnumDef_02	                       	              */
/*================================================================================*/


/*================================================================================*/
/*                     	     	StructDef_03                       	              */
/*================================================================================*/
/**
 * @结构体功能  nor flash结构体
 */
typedef struct {
	uint8_t wData[W25QX_WR_LEN];
	uint8_t rData[W25QX_RD_LEN];
	uint32_t W25Qx_i;
	uint8_t ID[2];
} W25Qx_HandleTypeDef;

/*================================================================================*/
/*                     	     	GlobalVarDef_04                                   */
/*================================================================================*/
/**
 * @全局变量功能    nor flash全局变量,单位：
 * @复位状态			
 * @注意事项
 */
W25QXX_EXT W25Qx_HandleTypeDef hW25Qx;

/*================================================================================*/
/*                     	     	APPFuncDef_05                      	              */
/*================================================================================*/
uint8_t ucBSP_W25Qx_Init(void);
uint8_t ucBSP_W25Qx_WriteEnable(void);
void vBSP_W25Qx_Read_ID(uint8_t *ID);
uint8_t ucBSP_W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size);
uint8_t ucBSP_W25Qx_Write(uint8_t* pData, uint32_t WriteAddr, uint32_t Size);
uint8_t ucBSP_W25Qx_Erase_Block(uint32_t Address);
uint8_t ucBSP_W25Qx_Erase_Chip(void);
#endif /* W25QXX_H_ */
