/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmiEncode.c
  �� �� ��   : ����
  ��������   : 2013��05��06��
  ����޸�   :
  ��������   : �ο�Э���MMI����Ҫ�󣬽�AT/STK���û��·���ҵ�����󣬱���ΪMMI�ַ���
               �ο�Э��22030 Annex B (normative)
  �����б�   :
  �޸���ʷ   :

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "v_typdef.h"
#include "TafTypeDef.h"
#include "TafAppSsa.h"
#include "MnErrorCode.h"
#include "Taf_Tafm_Remote.h"
#include "MnMsgTs.h"
#include "Taf_MmiStrParse.h"
#include "TafMmiEncode.h"
#include "TafStdlib.h"
#include "NasStkInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
#define THIS_FILE_ID                PS_FILE_ID_TAF_MMIENCODE_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
 ������    : g_stTafSsaEncodeProcFunc
 �ṹ˵��  : ��Ϣ���Ӧ����������ӳ���
             usMsgType                       - ���������Ϣ���ͣ�
             TAF_MmiEncodeRegisterMmiString  - ���봦������

  1.��    ��   : 2013��05��06��
    �޸�����   : SS FDN&Call Control
*****************************************************************************/
TAF_MMI_ENCODE_PROC_FUNC_STRU           g_astTafMmiEncodeSsProcFunc[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGPWD_MSG),             TAF_MmiEncodeRegisterPwdMmiString},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASECCENTRY_MSG),       TAF_MmiEncodeEraseCcEntryMmiString},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MmiEncodeRegisterMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MmiEncodeActiveMmiString},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGPWD_REQ),              TAF_MmiEncodeRegisterPwdMmiString},
};

TAF_MMI_OPERATION_TABLE_STRU            g_astTafMmiEventOperationTypeTbl[] = {
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_REGISTERSS_MSG),         TAF_MMI_REGISTER_SS},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ERASESS_MSG),            TAF_MMI_ERASE_SS},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_ACTIVATESS_MSG),         TAF_MMI_ACTIVATE_SS},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_DEACTIVATESS_MSG),       TAF_MMI_DEACTIVATE_SS},
    {TAF_MMI_BuildEventType(WUEPS_PID_AT, TAF_MSG_INTERROGATESS_MSG),      TAF_MMI_INTERROGATE_SS},

    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_REGISTERSS_REQ),          TAF_MMI_REGISTER_SS},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ERASESS_REQ),             TAF_MMI_ERASE_SS},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_ACTIVATESS_REQ),          TAF_MMI_ACTIVATE_SS},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_DEACTIVATESS_REQ),        TAF_MMI_DEACTIVATE_SS},
    {TAF_MMI_BuildEventType(MAPS_STK_PID, STK_SS_INTERROGATESS_REQ),       TAF_MMI_INTERROGATE_SS},
};

/* ASCII to ��ѹ��GSM 7bitת����(��8bit����Ϊ0)��UE�����USSD Request����ת����ѹ��*/
LOCAL VOS_UINT8 g_aucTafMmiDefAsciiToAlphaTbl[] =
{
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x0A,0x2E,0x2E,0x0D,0x2E,0x2E,
0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,0x2E,
0x20,0x21,0x22,0x23,0x02,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,
0x00,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x28,0x2F,0x29,0x2E,0x2D,
0x2F,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x21,0x2F,0x29,0x2D,0x2E
};

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/

/**********************************************************
 �� �� ��  : TAF_MmiGetEventOperationTypeTblSize
 ��������  : ��ȡ�û��¼���ͨ�ò���ҵ�������ӳ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û��¼���ͨ�ò���ҵ�������ӳ���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    �޸�����   : SS FDN&Call Control��Ŀ��
*************************************************************/

VOS_UINT32 TAF_MmiGetEventOperationTypeTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEventOperationTypeTbl) / sizeof(g_astTafMmiEventOperationTypeTbl[0]);

    return ulTblSize;
}

/**********************************************************
 �� �� ��  : MMI_GetSsOporationTblAddr
 ��������  : ��ȡ�û��¼���ͨ�ò���ҵ�������ӳ����ĵĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û��¼���ͨ�ò���ҵ�������ӳ����ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    �޸�����   : SS FDN&Call Control��Ŀ��
*************************************************************/
TAF_MMI_OPERATION_TABLE_STRU *TAF_MmiGetEventOperationTypeTblAddr(VOS_VOID)
{
    return g_astTafMmiEventOperationTypeTbl;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiGetCurrAsciiToAlphaTableAddr
 ��������  : ��ȡ��ǰ��Assic��Alpha��ת����ָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ��Assic��Alpha��ת����ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��5��17��
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8*   TAF_MmiGetCurrAsciiToAlphaTableAddr(VOS_VOID)
{
    return g_aucTafMmiDefAsciiToAlphaTbl;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeOperationType
 ��������  : �����û��¼�����ҵ�������
 �������  : VOS_UINT32                          ulEventType - �û��¼�
 �������  : MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType - ҵ��������ַ���
 �� �� ֵ  : VOS_TRUE       - ��ȡ�����ɹ�
             VOS_FALSE      - ��ȡ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiGetOperationType(
    VOS_UINT32                          ulEventType,
    MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    TAF_MMI_OPERATION_TABLE_STRU       *pstEventOperationType = VOS_NULL_PTR;

    /* ��ȡ�¼���Ӧ�Ĳ������� */
    ulTableSize           = TAF_MmiGetEventOperationTypeTblSize();
    pstEventOperationType = TAF_MmiGetEventOperationTypeTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (ulEventType == pstEventOperationType->ulEventType)
        {
            *penSsOpType = pstEventOperationType->enSsOpType;
            return VOS_TRUE;
        }

        pstEventOperationType++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeOperationTypeString
 ��������  : �����û��¼�����ҵ��������ַ���
 �������  : VOS_UINT32                          ulEventType- �û��¼�
 �������  : VOS_CHAR                           *pOutMmiStr - ҵ��������ַ���
             VOS_UINT32                         *pulLength  - ҵ��������ַ�������
 �� �� ֵ  : VOS_TRUE       - ��ȡ�����ɹ�
             VOS_FALSE      - ��ȡ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeOperationTypeString(
    VOS_UINT32                          ulEventType,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    MN_MMI_SS_OP_Tbl_STRU              *pstOperationType      = VOS_NULL_PTR;

    /* ��ȡ�¼���Ӧ�Ĳ������� */
    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);

    /* ��ȡҵ���������ʧ�ܣ����ر���ʧ�� */
    if (VOS_FALSE == ulRet)
    {

        return VOS_FALSE;
    }


    /* ��ȡ����ҵ����������ַ��� */
    ulTableSize       = MMI_GetOporationTypeTblSize();
    pstOperationType  = MMI_GetOporationTypeTblAddr();
    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (enSsOpType == pstOperationType->enSsOpType)
        {
            *pulLength = VOS_StrLen((VOS_CHAR *)pstOperationType->pcSsOpStr);
            VOS_StrNCpy((VOS_CHAR *)pcOutMmiStr,
                        (VOS_CHAR *)pstOperationType->pcSsOpStr,
                        *pulLength);
            return VOS_TRUE;
        }

        pstOperationType++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeBS
 ��������  : ��ȡBS��Ϣ��������
 �������  : TAF_SS_BASIC_SERVICE_STRU          *pstBsService   - ����ҵ��ṹ
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����BS�ִ�
             VOS_UINT32                         *pulBSLength    - BS�ִ�����
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeBS(
    TAF_SS_BASIC_SERVICE_STRU          *pstBsService,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulBSLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_BS_TABLE_STRU               *pstBsType = VOS_NULL_PTR;

    /* ��ȡBS�ַ��� */
    ulTableSize = MMI_GetBSTblSize();
    pstBsType   = MMI_GetBSTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if ((pstBsType->ucNetBsCode == pstBsService->BsServiceCode)
         && (pstBsType->ucNetBsType == pstBsService->BsType))
        {
            *pulBSLength = VOS_StrLen((VOS_CHAR *)pstBsType->pcMmiBs);
            VOS_StrNCpy(pcOutMmiStr, pstBsType->pcMmiBs, *pulBSLength);
            return VOS_TRUE;
        }

        pstBsType++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeSC
 ��������  : ����SS CODE������SC�ֶ�
 �������  : TAF_SS_CODE                         ucSsCode       - SS CODE
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����SC�ִ�
             VOS_UINT32                         *pulScLength    - SC�ִ�����
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeSC(
    TAF_SS_CODE                         ucSsCode,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulScLength
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    MN_MMI_SC_TABLE_STRU               *pstSCType;

    /* ��ȡSC�ַ��� */
    ulTableSize = MMI_GetSCTblSize();
    pstSCType   = MMI_GetSCTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstSCType->ucNetSc == ucSsCode)
        {
            *pulScLength = VOS_StrLen((VOS_CHAR *)pstSCType->pcMmiSc);
            VOS_StrNCpy(pcOutMmiStr, pstSCType->pcMmiSc, *pulScLength);
            return VOS_TRUE;
        }

        pstSCType++;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeDN
 ��������  : ���ݵ�ַ�ṹ������DN�ֶ�
 �������  : TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo- ע����Ϣ������ַ
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����DN�ִ�
             VOS_UINT32                         *pulDNLength    - DN�ִ�����
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MmiEncodeDN(
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulDNLength
)
{
    VOS_UINT32                          ulNumberLength;

    ulNumberLength = VOS_StrLen((VOS_CHAR *)pstRegisterInfo->aucFwdToNum);
    if (ulNumberLength > TAF_SS_MAX_FORWARDED_TO_NUM_LEN)
    {
        ulNumberLength = TAF_SS_MAX_FORWARDED_TO_NUM_LEN;
    }

    VOS_StrNCpy(pcOutMmiStr, (VOS_CHAR *)pstRegisterInfo->aucFwdToNum, ulNumberLength);

    /* ����Ŀ�ĺ�����Ӻ����ַ������*DN�ͳ��� */
    *pulDNLength = ulNumberLength;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodePW
 ��������  : ��������ṹ������PW�ֶ�
 �������  : VOS_UINT8                          *pucPassword     - ���룬����ΪTAF_SS_MAX_PASSWORD_LEN
             VOS_UINT32                          ulPasswordLength- ���볤��
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����PW�ִ�
             VOS_UINT32                         *pulPWLength    - PW�ִ�����
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MmiEncodePW(
    VOS_UINT8                          *pucPassword,
    VOS_UINT32                          ulPasswordLength,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulPWLength
)
{

    /* ���������ַ��� */
    PS_MEM_CPY(pcOutMmiStr, pucPassword, ulPasswordLength);

    *pulPWLength = ulPasswordLength;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeCfnrTimerLen
 ��������  : ����ʮ����ʱ������T�ֶ�
 �������  : VOS_UINT8                           ucTime         - ʮ����ʱ��
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����T�ִ�
             VOS_UINT32                         *pulLength      - T�ִ�����
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeCfnrTimerLen(
    VOS_UINT8                           ucTime,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucTime, pcOutMmiStr, pulLength);
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeCcbsIndex
 ��������  : ����ʮ���ƺ�����������n�ֶ�
 �������  : VOS_UINT8                           ucCallIndex    - ʮ���ƺ�������
 �������  : VOS_CHAR                           *pcOutMmiStr    - �����n�ִ�
             VOS_UINT32                         *pulLength      - n�ִ�����
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeCcbsIndex(
    VOS_UINT8                           ucCallIndex,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulLength
)
{
    return TAF_STD_Itoa(ucCallIndex, pcOutMmiStr, pulLength);

}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeRegisterMmiString
 ��������  : �����û�ע����Ϣ�ṹ������Mmi�ִ�
 �������  : VOS_UINT32                          ulEventType- �û��¼�
             VOS_VOID                           *pPara      - �������Ͷ�Ӧ�Ĳ����ṹ
 �������  : VOS_CHAR                           *pcOutMmiStr- �����MMI�ִ�
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeRegisterMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo = VOS_NULL_PTR;

    /*
    ֻ�к���ת����Ҫע��������漰����^CMMI,+CCFC
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.082
            CFU                     21              DN      BS   -
            CF Busy                 67              DN      BS   -
            CF No Reply             61              DN      BS   T
            CF Not Reachable        62              DN      BS   -

            all CF                  002             DN      BS   T
            all conditional CF      004             DN      BS   T

    */
    ulPos           = 0;
    pstRegisterInfo = (TAF_SS_REGISTERSS_REQ_STRU *)pPara;

    /* ���ͨ��ע�����ǰ׺: ** */
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid usMsgType.");
        return ulRet;
    }

    /* ׷��SC�ַ���: */
    ulRet = TAF_MmiEncodeSC(pstRegisterInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid SsCode.");
        return ulRet;
    }
    ulPos += ulStrLength;

    /* ׷��DN�ַ���: *����ת����������Ӻ���    */
    /* �������ҵ���ַ��������* */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if ((VOS_TRUE == pstRegisterInfo->OP_NumType)
     && (VOS_TRUE == pstRegisterInfo->OP_FwdToNum))
    {
        TAF_MmiEncodeDN(pstRegisterInfo, (pcOutMmiStr + ulPos), &ulStrLength);
        ulPos += ulStrLength;
    }
    else
    {
        return VOS_FALSE;
    }

    /* �����Ӻ����ַ��������뺯��û���ӵ�ַ��Э��Ҳû����ȷ���ӵ�ַ��ʽ��
    ���ṩ */

    /* ������ת�ƻ���æת��û��BS����ʱֱ��׷��#����������û��BSҲҪ���* */
    if ((VOS_FALSE == pstRegisterInfo->OP_BsService)
     && (VOS_FALSE == pstRegisterInfo->OP_NoRepCondTime))
    {
        /* ׷��#  */
        *(pcOutMmiStr + ulPos) = '#';

        return VOS_TRUE;
    }

    /* ׷��BS�ַ���: *BS     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    if (VOS_TRUE == pstRegisterInfo->OP_BsService)
    {
        ulRet = TAF_MmiEncodeBS(&(pstRegisterInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid BS parameter.");
            return ulRet;
        }
        ulPos += ulStrLength;
    }

    /*
    ����ת�ƣ���������ת���Լ���Ӧ��ת����Ҫ�ж�ʱ�������û���Ӧ��ת��
    ׷��T�ַ���: *T */
    if ((TAF_ALL_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_ALL_COND_FORWARDING_SS_CODE == pstRegisterInfo->SsCode)
     || (TAF_CFNRY_SS_CODE == pstRegisterInfo->SsCode))
    {
        if (VOS_TRUE != pstRegisterInfo->OP_NoRepCondTime)
        {
            return VOS_FALSE;
        }

        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeCfnrTimerLen(pstRegisterInfo->NoRepCondTime,
                                          (pcOutMmiStr + ulPos),
                                          &ulStrLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeRegisterMmiString: invalid T parameter.");
            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeActiveMmiString
 ��������  : �����û�������Ϣ�ṹ������Mmi�ִ�
             ��Ϊɾ�������ȥ����Ͳ�ѯ����ṹ��ͬ������һ�����봦������
 �������  : VOS_UINT32                          ulEventType- �û��¼�����������ɾ�������ȥ����Ͳ�ѯ����
             VOS_VOID                           *pPara      - �������Ͷ�Ӧ�Ĳ����ṹ
 �������  : VOS_CHAR                           *pcOutMmiStr- �����MMI�ִ�
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeActiveMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulStrLength;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    TAF_SS_ACTIVATESS_REQ_STRU         *pstActiveInfo = VOS_NULL_PTR;

    /*
    �漰����^CMMI,+CCFC,+CCWA,
    +CLIR,+CLIP,+COLP
    1)����ת�Ƽ��ȥ����Ͳ�ѯ��ɾ��������������ҪDN��T����
      �������BS��������ҪΪDN��������*�����򣬲���д*
    2)��������ҵ�񼤻��ȥ�����ʽ���£���ѯ��������Ҫ����
    22.088
        Supplementary   Service     Service Code    SIA     SIB SIC
            BAOC                    33              PW      BS  -
            BAOIC                   331             PW      BS  -
            BAOIC exc home          332             PW      BS  -
            BAIC                    35              PW      BS  -
            BAIC roaming            351             PW      BS  -

            all Barring Serv.       330             PW      BS  -
            Outg. Barr. Serv.       333             PW      BS
            Inc. Barr. Serv.        353             PW      BS
    3)CCBS��ѯ��������Ҫn����
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
    4)���еȴ��ļ��ȥ����Ͳ�ѯ
    22.083
            WAIT                    43              BS      -   -
    */
    /* ���ͨ�ü���(*)��ȥ����(#)����ѯ����ǰ׺(*#)��ɾ������ǰ׺(##):  */
    ulPos = 0;
    ulRet = TAF_MmiEncodeOperationTypeString(ulEventType, pcOutMmiStr, &ulPos);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid usMsgType.");
        return ulRet;
    }

    pstActiveInfo = (TAF_SS_ACTIVATESS_REQ_STRU *)pMsg;

    /* ׷��SC�ַ���: SC */
    ulRet = TAF_MmiEncodeSC(pstActiveInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulStrLength;

    if ((VOS_FALSE == pstActiveInfo->OP_Password)
     && (VOS_FALSE == pstActiveInfo->OP_BsService))
    {
        /* ׷��#  */
        *(pcOutMmiStr + ulPos) = '#';
        ulPos                  += sizeof('#');

        return ulRet;
    }

    ulRet = TAF_MmiGetOperationType(ulEventType, &enSsOpType);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: operation type.");
        return ulRet;
    }

    /* ׷��PW�ַ���: *PW */
    if ((TAF_ALL_BARRING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
      && ((TAF_MMI_ACTIVATE_SS == enSsOpType)
       || (TAF_MMI_DEACTIVATE_SS == enSsOpType)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        if (VOS_TRUE == pstActiveInfo->OP_Password)
        {
            TAF_MmiEncodePW(pstActiveInfo->aucPassword,
                            TAF_SS_MAX_PASSWORD_LEN,
                            (pcOutMmiStr + ulPos),
                            &ulStrLength);

            ulPos += ulStrLength;
        }
    }

    /* ����ת�ƴ���BS����ʱ����ҪΪDN��������* */
    if (TAF_ALL_FORWARDING_SS_CODE == (TAF_SS_CODE_MASK & (pstActiveInfo->SsCode)))
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    }

    /* ׷��BS�ַ���: *BS     */

    if (VOS_TRUE == pstActiveInfo->OP_BsService)
    {
        TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

        ulRet = TAF_MmiEncodeBS(&(pstActiveInfo->BsService),
                                (pcOutMmiStr + ulPos),
                                &ulStrLength);

        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeActiveMmiString: invalid BS parameter!");

            return ulRet;
        }

        ulPos += ulStrLength;
    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeDeactiveMmiString
 ��������  : �����û�ע����������Ϣ�ṹ������Mmi�ִ�
 �������  : VOS_UINT32                          ulEventType- �û��¼�
             VOS_VOID                           *pPara      - �������Ͷ�Ӧ�Ĳ����ṹ
 �������  : VOS_CHAR                           *pcOutMmiStr- �����MMI�ִ�
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeRegisterPwdMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulRet;
    TAF_SS_REGPWD_REQ_STRU             *pstRegisterPwdInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulSCLength;

    /*
       �漰����^CMMI,+CPWD
       ���ע�����������ǰ׺: **03���˴���SsCode��ʾ�������ͣ�
       �����������������ע����Ϣ������ֱ�Ӹ�ֵ**03

    22030 6.5.4 Registration of new password
        * 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        where, for Barring Services, ZZ = 330;
        for a common password for all appropriate services, delete the ZZ, entering:
        * 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
    */
    VOS_StrCpy(pcOutMmiStr, TAF_MMI_REGISTER_PASSWORD);
    ulPos              = VOS_StrLen(TAF_MMI_REGISTER_PASSWORD);

    pstRegisterPwdInfo = (TAF_SS_REGPWD_REQ_STRU *)pMsg;

    /* ׷��SC�ַ���: *SC */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    ulRet = TAF_MmiEncodeSC(pstRegisterPwdInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeRegisterPwdMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;


    /* ׷�Ӿ�PW�ַ���: *OLDPASSWORD    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucOldPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷����PW�ַ���: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷����PWȷ���ַ���: *NEWPASSWORD     */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);

    VOS_StrNCpy((VOS_CHAR *)(pcOutMmiStr + ulPos), (VOS_CHAR *)pstRegisterPwdInfo->aucNewPwdStrCnf, TAF_SS_MAX_PASSWORD_LEN);
    ulPos += TAF_SS_MAX_PASSWORD_LEN;

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeEraseCcEntryMmiString
 ��������  : �����û�ɾ��CCBS��Ϣ�ṹ������Mmi�ִ�
 �������  : VOS_UINT32                          ulEventType- �û��¼�
             VOS_VOID                           *pPara     - �������Ͷ�Ӧ�Ĳ����ṹ
 �������  : VOS_CHAR                           *pcOutMmiStr- �����MMI�ִ�
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeEraseCcEntryMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    TAF_SS_ERASECC_ENTRY_REQ_STRU      *pstEraseCcEntryInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPos;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulSCLength;
    VOS_UINT32                          ulIndexLength;

    /*
       �漰����^CMMI
    CCBSȥ����ָ��INDEX��CCBS������ʽ#37*n#
    CCBSȥ����CCBS������ʽ#37#
        Supplementary   Service     Service Code    SIA     SIB SIC
    22.093
            CCBS                    37              n   See Section 4.5.5               where n=1-5
            ��Ϊ����ͨ�õ�ע�ᣬɾ���������ȥ������Ϣ�У����Բ�����ͨ�ýӿڻ�ȡ������
    */
    VOS_StrCpy(pcOutMmiStr, "#");
    ulPos               = VOS_StrLen("#");

    pstEraseCcEntryInfo = (TAF_SS_ERASECC_ENTRY_REQ_STRU *)pPara;

    /* ׷��SC�ַ���: */
    ulRet = TAF_MmiEncodeSC(pstEraseCcEntryInfo->SsCode,
                            (pcOutMmiStr + ulPos),
                            &ulSCLength);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid SC parameter.");
        return ulRet;
    }
    ulPos += ulSCLength;

    /* ����OP_CcbsIndex��CcbsIndex����*n    */
    TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos);
    if (VOS_TRUE == pstEraseCcEntryInfo->OP_CcbsIndex)
    {

        /* ת���������͵�INDEXΪ�ַ����� */
        ulRet = TAF_MmiEncodeCcbsIndex(pstEraseCcEntryInfo->CcbsIndex,
                               (pcOutMmiStr + ulPos),
                               &ulIndexLength);
        if (VOS_TRUE != ulRet)
        {
            MN_WARN_LOG("TAF_MmiEncodeEraseCcEntryMmiString: invalid CcbsIndex.");
            return ulRet;
        }
        ulPos += ulIndexLength;

    }

    /* ׷��#  */
    *(pcOutMmiStr + ulPos) = '#';

    return VOS_TRUE;
}

/**********************************************************
 �� �� ��  : TAF_MmiEncodeSsProcFuncTblAddr
 ��������  : ��ȡ����ҵ����봦��������ӳ����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ҵ����봦��������ӳ����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    �޸�����   : SS FDN&Call Control��Ŀ��
*************************************************************/
TAF_MMI_ENCODE_PROC_FUNC_STRU *TAF_MmiEncodeSsProcFuncTblAddr(VOS_VOID)
{
    return g_astTafMmiEncodeSsProcFunc;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeSsProcFuncTblSize
 ��������  : ��ȡ����ҵ����봦��������ӳ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ҵ����봦��������ӳ�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeSsProcFuncTblSize(VOS_VOID)
{
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astTafMmiEncodeSsProcFunc) / sizeof(g_astTafMmiEncodeSsProcFunc[0]);

    return ulTblSize;
}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeMmiString
 ��������  : ����SS�������Լ���������������Mmi�ִ�
        �ο�Э��:
        22030 6.5.2 Structure of the MMI
        Activation              *SC*SI#
        Deactivation            #SC*SI#
        Interrogation           #SC*SI#
        Registration            *SC*SI# and **SC*SI#
        Erasure                 ##SC*SI#

        The UE shall determine from the context whether, an entry of a single *,
        activation or registration was intended.
        For example, a call forwarding request with a single * would be
        interpreted as registration if containing a forwarded-to number,
        or an activation if not.

        22030 6.5.4 Registration of new password
        Procedure:
        * 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 * ZZ * OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #

        where, for Barring Services, ZZ = 330;
        for a common password for all appropriate services, delete the ZZ, entering:
        * 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE shall also support the alternative procedure:
        ** 03 ** OLD_PASSWORD * NEW_PASSWORD * NEW_PASSWORD #
        The UE will then indicate to the user whether the new password request
        has been successful or not. If the new password request is rejected
        (e.g. due to entry of incorrect old password) the old password remains
        unchanged, until it is successfully changed by correctly repeating the
        procedure. Refer to 3GPP TS 22.004 [2] regarding repeated entry of
        incorrect password.

        22030 Annex B (normative):
        Codes for defined Supplementary Services

 �������  : VOS_VOID                           *pPara      - ҵ��������Ϣ
 �������  : VOS_CHAR                           *pcOutMmiStr- �����MMI�ִ�
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MmiEncodeMmiString(
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pcOutMmiStr
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTableSize;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulEventType;
    TAF_MMI_ENCODE_PROC_FUNC            pMsgProcFunc = VOS_NULL_PTR;
    TAF_MMI_ENCODE_PROC_FUNC_STRU      *pstMapTbl    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppReq    = VOS_NULL_PTR;

    /* ��ȡָ����Ϣ����Ϣ�������� */
    pstAppReq   = (MN_APP_REQ_MSG_STRU *)pPara;
    ulEventType = TAF_MMI_BuildEventType(pstAppReq->ulSenderPid, pstAppReq->usMsgName);

    /* ��ȡ������������ȡ��LOOPֵ���жϺ���ָ���Ƿ�Ϊ�� */
    ulTableSize = TAF_MmiEncodeSsProcFuncTblSize();
    pstMapTbl   = TAF_MmiEncodeSsProcFuncTblAddr();

    for (ulLoop = 0; ulLoop < ulTableSize; ulLoop++)
    {
        if (pstMapTbl->ulEventType == ulEventType)
        {
            pMsgProcFunc = pstMapTbl->pMsgProcFunc;
            break;
        }

        pstMapTbl++;
    }

    if (VOS_NULL_PTR == pMsgProcFunc)
    {
        return VOS_FALSE;
    }

    ulRet = pMsgProcFunc(ulEventType, pstAppReq->aucContent, pcOutMmiStr);

    return ulRet;

}

/*****************************************************************************
 �� �� ��  : TAF_MmiEncodeUssdMessage
 ��������  : ����USSD�ִ����ݽ���7bit����
 �������  : pstPara-----�����USSD�ַ�����ָ��
 �������  : pstPara-----ָ�����ת�����USSD�ַ�����ָ��
 �� �� ֵ  : VOS_TRUE       - ����ɹ�
             VOS_FALSE      - ����ʧ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    �޸�����   : V9R1 STK����
*****************************************************************************/

VOS_UINT32 TAF_MmiEncodeUssdMessage (
    TAF_SS_USSD_STRING_STRU            *pstPara
)
{
    VOS_UINT8                           aucTmp[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          ulEncodeLen;
    VOS_UINT8                           aucTemp_buffer[TAF_SS_MAX_UNPARSE_PARA_LEN];
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurTransTbl = VOS_NULL_PTR;

    PS_MEM_SET(aucTmp, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    PS_MEM_SET(aucTemp_buffer, 0 , TAF_SS_MAX_UNPARSE_PARA_LEN);
    ulEncodeLen = 0;

    /* �ж�������ַ����Ƿ񳬳�,7bit����ʱ�182���ַ� */
    if (pstPara->usCnt > TAF_SS_MAX_USSDSTRING_LEN)
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: string is too long");
        return VOS_FALSE;
    }

    /* convert from ascii coding into GSM default-alphabet
       coding with 1 char per byte  */
    pucCurTransTbl      = TAF_MmiGetCurrAsciiToAlphaTableAddr();
    for (i = 0; i < pstPara->usCnt; i++)
    {
        aucTemp_buffer[i]   = pucCurTransTbl[pstPara->aucUssdStr[i]];
    }

    /* ѭ���ṹ,ת����7bit���뷽ʽ */
    if (VOS_OK != TAF_STD_Pack7Bit(aucTemp_buffer, pstPara->usCnt, 0, aucTmp, &ulEncodeLen))
    {
        MN_WARN_LOG("TAF_MmiEncodeUssdMessage: TAF_STD_Pack7Bit Error");
    }

    /* �ж��Ƿ���7��λ�Ŀ���,����ж����7��λ�����'0001101' */
    if (TAF_MMI_BITS_PER_SEPTET == (pstPara->usCnt % TAF_MMI_BITS_PER_OCTET))
    {
       aucTmp[ulEncodeLen - 1] = aucTmp[ulEncodeLen - 1] | TAF_MMI_USSD_7BIT_PAD;
    }

    pstPara->usCnt = (VOS_UINT16)ulEncodeLen;
    PS_MEM_CPY(pstPara->aucUssdStr, aucTmp, pstPara->usCnt);

    return VOS_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
