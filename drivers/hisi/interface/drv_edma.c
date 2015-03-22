/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_edma.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年3月2日
  最近修改   :
  功能描述   : 底软给上层软件封装的接口层
  修改历史   :
  1.日    期   : 2012年3月2日
    作    者   : 
    修改内容   : 新建Drvinterface.c
    
  2.日    期   : 2013年2月19日
    作    者   : 
    修改内容   : 由Drvinterface.c拆分所得

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "BSP.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 函数声明
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : DRV_EDMA_BBP_SAMPLE_REBOOT
 功能描述  : BBP采数使用重启接口，重启后系统会停留在fastboot阶段，以便导出采集数据，
             SFT平台A核使用，其他直接返回-1
 输入参数  : NA
 输出参数  : 无
 返 回 值  : OK-执行重启，ERROR-不执行重启
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013年1月5日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 DRV_EDMA_BBP_SAMPLE_REBOOT(BSP_VOID)
{
    return BSP_ERROR;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

