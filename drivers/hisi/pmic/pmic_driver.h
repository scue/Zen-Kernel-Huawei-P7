/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pmic_driver.h
  版 本 号   : 初稿
  作    者   :  
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : pmic_driver.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    作    者   :  
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#ifndef __PMIC_DRIVER_H__
#define __PMIC_DRIVER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <linux/spinlock_types.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>

#include  "pmic_common.h"
#include  "soc_smart_interface.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define         PMIC_STATUS_ON          (0x201305)
#define         PMIC_STATUS_OFF         (-1)
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
typedef struct __PMU_DATA__
{
     struct platform_device *pdev;
     BSP_U32                version ;
     spinlock_t             pmic_spinlock ;
}PMU_DATA;

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
extern int          pmic_power_status(int channel_id);
extern COMMON_RES*  pmic_get_channel_res_by_id(int id);
extern int          pmic_power_switch( int id,int onoff);
extern int          pmic_list_vol_tab( int id ,unsigned int selector );
extern int          pmic_get_voltage(int id);
extern int          pmic_set_voltage(int id ,int min_uV, int max_uV, unsigned *selector);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pmic_driver.h */
