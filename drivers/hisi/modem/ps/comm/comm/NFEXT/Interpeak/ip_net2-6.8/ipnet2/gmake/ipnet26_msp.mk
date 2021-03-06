#############################################################################
#			      IPNET26.MK
#
#     Document no: @(#) $Name: VXWORKS_ITER18A_FRZ10 $ $RCSfile: ipnet26_msp.mk,v $ $Revision: 1.1 $
#     $Source: /home/interpeak/CVSRoot/ipnet2/gmake/ipnet26_msp.mk,v $
#     $State: Exp $ $Locker:  $
#
#     INTERPEAK_COPYRIGHT_STRING
#
#############################################################################

#############################################################################
# DEFINE
###########################################################################

#############################################################################
# OBJECTS
###########################################################################

ifneq ($(IPPORT),lkm)
ifneq ($(IPPORT),las)
# Vrrp daemon
IPLIBOBJECTS_C += ipnet_send_config.o
IPLIBOBJECTS += ipnet_cmd_cga.o
endif
endif


# Compiles the xxx_config.o if the $SKIP_CONFIG macro is either not defined
# or set to anything other than true.
ifneq ($(SKIP_CONFIG),true)
IPLIBOBJECTS    += $(IPLIBOBJECTS_C)
endif

###########################################################################
# END OF IPNET2_MSP.MK
###########################################################################
