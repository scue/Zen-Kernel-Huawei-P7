cmd_arch/arm/vfp/vfphw.o :=  /home/sebastian/android/sabermod/bin/arm-linux-androideabi-gcc -Wp,-MD,arch/arm/vfp/.vfphw.o.d  -nostdinc -isystem /home/sebastian/android/sabermod/bin/../lib/gcc/arm-linux-androideabi/4.9.0/include -I/home/sebastian/android/kernel/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h  -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/product/include/hi6620cs_oem_gutl_dsda -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/product/define/hi6620cs_oem_gutl_dsda/config -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/nvim/include/gu -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/platform/hi6620cs_asic -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/modem/drv/hi6620/src/comm/inc -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/modem/drv/common/src/comm/inc -I/home/sebastian/android/kernel/kernel/include/hisi/ -I/home/sebastian/android/kernel/kernel/drivers/ -I/home/sebastian/android/kernel/kernel/mm/ -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/drv -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/drv/MODULE_H -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/med -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/nv/gu/drv -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/platform/balong/ -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/common/ -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/linux/ -I/home/sebastian/android/kernel/kernel/drivers/hisi/nvim -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/external/efipartition  -I/home/sebastian/android/kernel/kernel/../external/efipartition -I/home/sebastian/android/kernel/kernel/../external/dx/codesafe/src/secure_boot/boot_images_verifier -I/home/sebastian/android/kernel/kernel/../external/dx/host/src/sbromlib -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi6620/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -D__LINUX_ARM_ARCH__=7 -march=armv7-a -include asm/unified.h -Wa,-mfpu=softvfp+vfp -gdwarf-2        -DBSP_CORE_APP -DBSP_COMPILE_ALLY -DBOARD_ASIC -c -o arch/arm/vfp/vfphw.o arch/arm/vfp/vfphw.S

source_arch/arm/vfp/vfphw.o := arch/arm/vfp/vfphw.S

deps_arch/arm/vfp/vfphw.o := \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/preempt.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/vfpv3.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/thread_info.h \
    $(wildcard include/config/arm/thumbee.h) \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/fpstate.h \
    $(wildcard include/config/iwmmxt.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/vfpmacros.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/hwcap.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/vfp.h \
  arch/arm/vfp/../kernel/entry-header.S \
    $(wildcard include/config/frame/pointer.h) \
    $(wildcard include/config/alignment/trap.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/32v6k.h) \
    $(wildcard include/config/have/hw/breakpoint.h) \
  include/linux/init.h \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/hotplug.h) \
  include/linux/linkage.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/linkage.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/asm-offsets.h \
  include/generated/asm-offsets.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/errno.h \
  include/asm-generic/errno.h \
  include/asm-generic/errno-base.h \

arch/arm/vfp/vfphw.o: $(deps_arch/arm/vfp/vfphw.o)

$(deps_arch/arm/vfp/vfphw.o):
