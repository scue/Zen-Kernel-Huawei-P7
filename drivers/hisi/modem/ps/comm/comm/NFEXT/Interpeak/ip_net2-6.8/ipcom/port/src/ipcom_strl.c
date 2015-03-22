/*
 ******************************************************************************
 *                     INTERPEAK SOURCE FILE
 *
 *   Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipcom_strl.c,v $ $Revision: 1.2 $
 *   $Source: /home/interpeak/CVSRoot/ipcom/port/src/ipcom_strl.c,v $
 *   $State: Exp $ $Locker:  $
 *
 *   INTERPEAK_COPYRIGHT_STRING
 *   Design and implementation by Lennart Bang <lob@interpeak.se>
 ******************************************************************************
 */


/*
 ****************************************************************************
 * 1                    DESCRIPTION
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 2                    CONFIGURATION
 ****************************************************************************
 */

#include "ipcom_config.h"


/*
 ****************************************************************************
 * 3                    INCLUDE FILES
 ****************************************************************************
 */

#define IPCOM_USE_CLIB_PROTO
#define IPCOM_DMALLOC_C
#include "ipcom_clib.h"


/*
 ****************************************************************************
 * 4                    DEFINES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 5                    TYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 6                    EXTERN PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 7                    LOCAL PROTOTYPES
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 8                    DATA
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 9                    STATIC FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 10                   GLOBAL FUNCTIONS
 ****************************************************************************
 */

/*
 ****************************************************************************
 * 11                   PUBLIC FUNCTIONS
 ****************************************************************************
 */

/*
 *===========================================================================
 *                    ipcom_strlcat
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
#if defined(IPCOM_STRLCAT) && IPCOM_STRLCAT == 1
IP_PUBLIC Ip_size_t
ipcom_strlcat(char *d, const char *s, Ip_size_t size)
 {
     Ip_size_t l1 = ipcom_strlen(d);
     Ip_size_t l2 = ipcom_strlen(s);
     Ip_size_t ret = l1 + l2;

     if (l1 >= size)
         return 0;

     if (l1+l2 >= size)
         l2 = size - (l1 + 1);

     if (l2 > 0)
     {
         ipcom_memcpy(d + l1, s, l2);
         d[l1+l2] = 0;
     }

     return ret;
 }
#else
int ipcom_strlcat_empty_file;
#endif


/*
 *===========================================================================
 *                    ipcom_strlcpy
 *===========================================================================
 * Description:
 * Parameters:
 * Returns:
 *
 */
#if defined(IPCOM_STRLCPY) && IPCOM_STRLCPY == 1
IP_PUBLIC Ip_size_t
ipcom_strlcpy(char *d, const char *s, Ip_size_t size)
{
    Ip_size_t l = ipcom_strlen(s);
    Ip_size_t ret = l;

    if (size <= 0)
        return 0;

    if (l >= size)
        l = size - 1;

    ipcom_memcpy(d, s, l);
    d[l] = 0;

    return ret;
}
#else
int ipcom_strlcpy_empty_file;
#endif


/*
***************************************************************************
 *                      END OF FILE
 ****************************************************************************
 */

