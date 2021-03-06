/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: GU_MSPComm.h                                                    */
/*                                                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2010-06                                                             */
/*                                                                           */
/* Description: for Msp Comm code                                            */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/

#ifndef _GU_MSPCOMM_H
#define _GU_MSPCOMM_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum OM_MSG_HOOK_ENUM
{
    OM_MSG_HOOK_GU      = 0,    /*GU 注册钩子函数的时候使用*/
    OM_MSG_HOOK_LTE     = 1,    /*L 注册钩子函数的时候使用*/
    OM_MSG_HOOK_BUTT
};
typedef  VOS_UINT32 OM_MSG_HOOK_ENUM_UINT32;
/*****************************************************************************
  4 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  5 全局变量声明
*****************************************************************************/

extern VOS_MSG_HOOK_FUNC g_apMsgHookFunc[OM_MSG_HOOK_BUTT];


/*****************************************************************************
  6 Function定义
*****************************************************************************/

extern VOS_VOID OM_RegisterMsgHook(VOS_MSG_HOOK_FUNC pfHookFunc, OM_MSG_HOOK_ENUM_UINT32 ulFuncType);




#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _VOS_QUEUE_H */



