cmd_arch/arm/mm/abort-ev7.o :=  /home/sebastian/android/sabermod/bin/arm-linux-androideabi-gcc -Wp,-MD,arch/arm/mm/.abort-ev7.o.d  -nostdinc -isystem /home/sebastian/android/sabermod/bin/../lib/gcc/arm-linux-androideabi/4.9.0/include -I/home/sebastian/android/kernel/kernel/arch/arm/include -Iarch/arm/include/generated -Iinclude  -include include/generated/autoconf.h  -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/product/include/hi6620cs_oem_gutl_dsda -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/product/define/hi6620cs_oem_gutl_dsda/config -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/config/nvim/include/gu -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/platform/hi6620cs_asic -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/modem/drv/hi6620/src/comm/inc -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/modem/drv/common/src/comm/inc -I/home/sebastian/android/kernel/kernel/include/hisi/ -I/home/sebastian/android/kernel/kernel/drivers/ -I/home/sebastian/android/kernel/kernel/mm/ -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/drv -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/drv/MODULE_H -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/med -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/vendor/hisi/include/nv/gu/drv -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/platform/balong/ -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/common/ -I/home/sebastian/android/kernel/kernel/drivers/gpu/mali/linux/ -I/home/sebastian/android/kernel/kernel/drivers/hisi/nvim -I/home/sebastian/android/kernel/kernel/drivers/hisi/modem/include/external/efipartition  -I/home/sebastian/android/kernel/kernel/../external/efipartition -I/home/sebastian/android/kernel/kernel/../external/dx/codesafe/src/secure_boot/boot_images_verifier -I/home/sebastian/android/kernel/kernel/../external/dx/host/src/sbromlib -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-hi6620/include -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork  -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float -gdwarf-2     -Wa,-march=armv7-a   -DBSP_CORE_APP -DBSP_COMPILE_ALLY -DBOARD_ASIC -c -o arch/arm/mm/abort-ev7.o arch/arm/mm/abort-ev7.S

source_arch/arm/mm/abort-ev7.o := arch/arm/mm/abort-ev7.S

deps_arch/arm/mm/abort-ev7.o := \
    $(wildcard include/config/verify/permission/fault.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/linkage.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/arm/thumb.h) \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/hwcap.h \
  /home/sebastian/android/kernel/kernel/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \

arch/arm/mm/abort-ev7.o: $(deps_arch/arm/mm/abort-ev7.o)

$(deps_arch/arm/mm/abort-ev7.o):
