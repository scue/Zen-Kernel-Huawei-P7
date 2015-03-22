/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : FcACoreCReset.c
  �� �� ��   : ����
  ��������   : 2013��4��22��
  ����޸�   :
  ��������   : C�˵�����λ��FcACore�Ĵ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��22��
    �޸�����   : �����ļ�

******************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "Fc.h"
#include "FcInterface.h"
#include "FcIntraMsg.h"
#include "FcACoreCReset.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_ACORE_CRESET_FLOW_CTRL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
VOS_UINT32      g_ulFcACoreCResetDoneSem;    /* FcACore��ɻص������ź��� */



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : FC_ACORE_CResetSendNotify
 ��������  : ����C�˸�λ����ģ��֪ͨFcACore���и�λ�������߷��͸�λ�ɹ���֪ͨ
 �������  : FC_MSG_TYPE_ENUM_UINT16     usMsgName      ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��22��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  FC_ACORE_CResetSendNotify(FC_MSG_TYPE_ENUM_UINT16     usMsgName)
{
    FC_ACORE_CRESET_IND_STRU    *pstMsg;

    /* ������Ϣ�ڴ� */
    pstMsg = (FC_ACORE_CRESET_IND_STRU *) VOS_AllocMsg( UEPS_PID_FLOWCTRL_A,
        sizeof(FC_ACORE_CRESET_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    if ( VOS_NULL_PTR == pstMsg )
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetSendNotify, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = usMsgName;

    /* ������Ϣ */
    VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : FC_ACORE_CResetCallback
 ��������  : FcACore��Ҫע�ᵽ����C�˸�λ�ӿ��еĻص�����
 �������  : DRV_RESET_CALLCBFUN_MOMENT enParam ָʾʱ��λ����ǰ���Ǹ�λ�ɹ���
             int userdata                       �û��Զ�������
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��22��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_INT FC_ACORE_CResetCallback(DRV_RESET_CALLCBFUN_MOMENT enParam, VOS_INT userdata)
{
    VOS_UINT32                   ulResult;


    if ( DRV_RESET_CALLCBFUN_RESET_BEFORE == enParam )      /* ��λ����ʱ���� */
    {
        FC_ACORE_CResetSendNotify(ID_FC_ACORE_CRESET_START_IND);

        ulResult = VOS_SmP(g_ulFcACoreCResetDoneSem, FC_ACORE_CRESET_TIMEOUT_LEN);
        if (VOS_OK != ulResult)
        {
            FC_LOG1(PS_PRINT_ERROR,
                          "FC_ACORE_CRESET_Callback, wait g_ulFcACoreResetDoneSem timeout! ulResult = %d\r\n", (VOS_INT32)ulResult);

            return VOS_ERR;
        }
    }
    else if ( DRV_RESET_CALLCBFUN_RESET_AFTER == enParam )   /* ��λ�ɹ������ */
    {
        FC_ACORE_CResetSendNotify(ID_FC_ACORE_CRESET_END_IND);
    }
    else
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetCallback, enParam invalid !\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : FC_ACORE_CResetProc
 ��������  : FcACore�յ�����C�˸�λ���̴���ģ�鷢���ĸ�λ����λ�ɹ���֪ͨ��Ĵ�������
 �������  : FC_ACORE_CRESET_MOMENT_ENUM_UINT8 enCResetMoment ָʾʱ��λ����ǰ���Ǹ�λ�ɹ���
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��22��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 FC_ACORE_CResetProc(FC_ACORE_CRESET_MOMENT_ENUM_UINT8 enCResetMoment)
{
    VOS_UINT32                          ulFcPointLoop;
    FC_POINT_STRU                      *pFcPoint;
    VOS_UINT32                          ulResult;
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;
    FC_ACORE_CRESET_RSP_STRU           *pstMsg;
    VOS_UINT32                          ulRspResult;


    ulRspResult         = 0;

    if ( FC_ACORE_CRESET_BEFORE_RESET == enCResetMoment )
    {
        usMsgName           = ID_FC_ACORE_CRESET_START_RSP;

        /* ��λ����ʱ����ÿ�����ص㣬ִ�����ص����ⲿģ��ע���reset���� */
        for ( ulFcPointLoop = 0; ulFcPointLoop < g_stFcPointMgr.ulPointNum; ulFcPointLoop++ )
        {
            pFcPoint    = &g_stFcPointMgr.astFcPoint[ulFcPointLoop];

            if ( pFcPoint->pRstFunc != VOS_NULL_PTR )
            {
                ulResult     = pFcPoint->pRstFunc(pFcPoint->ulParam1, pFcPoint->ulParam2);
                ulRspResult |= ulResult ;
                FC_MNTN_TracePointFcEvent(ID_FC_MNTN_ACORE_CRESET_START_FC, pFcPoint, VOS_TRUE, ulResult);
            }
        }
    }
    else if ( FC_ACORE_CRESET_AFTER_RESET == enCResetMoment )
    {
        usMsgName           = ID_FC_ACORE_CRESET_END_RSP;
    }
    else
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetProc, enCResetMoment invalid !\n");
        return VOS_ERR;
    }

    /* ������Ϣ�ڴ�: */
    pstMsg = (FC_ACORE_CRESET_RSP_STRU *) VOS_AllocMsg( UEPS_PID_FLOWCTRL_A,
        sizeof(FC_ACORE_CRESET_RSP_STRU) - VOS_MSG_HEAD_LENGTH );

    if(VOS_NULL_PTR == pstMsg)
    {
        FC_LOG(PS_PRINT_ERROR,"FC_ACORE_CResetProc, Alloc Msg Fail\n");
        return VOS_ERR;
    }

    /*��д��Ϣ����:*/
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = UEPS_PID_FLOWCTRL_A;
    pstMsg->usMsgName       = usMsgName;
    pstMsg->ulResult        = ulRspResult;

    /*������Ϣ:*/
    VOS_SendMsg(UEPS_PID_FLOWCTRL, pstMsg);

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : FC_ACORE_CResetRcvStartRsp
 ��������  : �յ�ID_FC_ACORE_CRESET_START_RSP��Ϣ��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��22��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID FC_ACORE_CResetRcvStartRsp(VOID)
{
    VOS_SmV(g_ulFcACoreCResetDoneSem);

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
