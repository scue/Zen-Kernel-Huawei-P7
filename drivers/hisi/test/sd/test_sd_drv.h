/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_sd_drv.h
  版 本 号   : 初稿
  生成日期   : 2012年10月15日
  最近修改   :
  功能描述   : test_sddrv.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2012年11月02日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/



#ifndef __TEST_SD_DRV_H__
#define __TEST_SD_DRV_H__

extern int g_bufferSize;

#define SD_MULTI_BUFFER_SIZE  g_bufferSize

#define ERROR (-1)


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/


/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
int test_sd_write_single(void);
int test_sd_write_multi(int blkcount);
int test_sd_write_all(void);
int test_sd_read_single(void);
int test_sd_read_multi(int blockcount);
int test_sd_read_all(void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of test_sd_drv.h */

