/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_gpio.c
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
#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(BSP_CORE_APP)
extern unsigned long  platform_have_bbp(void);
#endif

/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : DRV_BBP_GPIO_GET
 功能描述  : 通过GPIO读取拨码状态，决定是否启动协议栈
 输入参数  : void
 输出参数  : 无
 返 回 值  : DRV_NOT_START_UMTS : 不启动协议栈；其他返回值:启动协议栈
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月13日
    作    者   :  
    修改内容   : 新生成函数
*****************************************************************************/
unsigned long DRV_BBP_GPIO_GET(void)
{
    return platform_have_bbp();
#if 0    
#if defined (BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
    return platform_have_bbp();
#endif

#if (defined BSP_CORE_APP)
    return 0;   /* 打桩 */
#endif
#endif
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


