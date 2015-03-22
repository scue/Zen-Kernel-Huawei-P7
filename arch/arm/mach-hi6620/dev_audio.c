/*audio device declare and register*/
#include <linux/platform_device.h>
#include <linux/io.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <mach/irqs.h>
#include <mach/io.h>
#include <mach/dma.h>
#include <linux/gpio.h>
#include <mach/clk_name_interface.h>
#include <drv_regulator_user.h>
#include <mach/sound/spk_5vboost.h>
#include <mach/sound/tpa6132.h>
#include <mach/sound/es305.h>
#include <linux/i2c.h>
#include <drv_regulator_user.h>

#include <sound/hi6421_common.h>
#include <hsad/config_mgr.h>



/*device : hi6620-hifi*/
static struct resource hifi_resources[] = {
};

static struct platform_device hifi_device = {
	.name = "hi6620-hifi",
	.id	= -1,
	.num_resources	= ARRAY_SIZE(hifi_resources),
	.resource	= hifi_resources,
};


#ifdef CONFIG_SND_ASP
/*device : hi6620-aspdigital (platform)*/
static struct resource aspdigital_resources[] = {
    {
        .name       = "asp_irq",
        .start      = IRQ_ASP,
        .end        = IRQ_ASP,
        .flags      = IORESOURCE_IRQ,
    },
    {
        .name       = "asp_base",
        .start      = REG_BASE_ASP,
        .end        = REG_BASE_ASP + REG_ASP_IOSIZE - 1,
        .flags      = IORESOURCE_MEM,
    },
};

static struct platform_device aspdigital_device = {
    .name = "hi6620-aspdigital",
    .id = -1,
    .num_resources = ARRAY_SIZE(aspdigital_resources),
    .resource = aspdigital_resources,
};

/*device : digital_audio (hi6421 codec)*/
static struct platform_device hisik3_digital_audio_device = {
	.name	= "digital-audio",
	.id	= -1,
};
#endif

#ifdef CONFIG_HI6421_CODEC
/*device : hi6421-codec*/
static struct hi6421_codec_platform_data hi6421_codec_plat_data = {
    .clk_name       = CLK_PMUSSI,
    .regulator_name = AUDIO_CODEC_ANALOG_1P8V_VDD,   /* "audio-vcc" */
    .reg_base_name  = "hi6421_base",
	.gpio_reset     = GPIO_6_3,
	.gpio_label     = "hi6421",
#ifdef CONFIG_MFD_HI6421_IRQ
	.irq[0] = IRQ_HEADSET_PLUG_OUT,
	.irq[1] = IRQ_HEADSET_PLUG_IN,
	.irq[2] = IRQ_BSD_BTN_PRESS_DOWN,
	.irq[3] = IRQ_BSD_BTN_PRESS_UP,
#endif
};

static struct resource pmuspi_resources[] = {
	{
		.name	= "hi6421_base",
		.start	= REG_BASE_PMUSPI_SFT,
		.end	= REG_BASE_PMUSPI_SFT + REG_PMUSPI_SFT_IOSIZE - 1,
		.flags	= IORESOURCE_MEM,
	}
};

static struct platform_device hi6421_codec_device = {
	.name	= "hi6421-codec",
	.id	= -1,
	.num_resources	= ARRAY_SIZE(pmuspi_resources),
	.resource	= &pmuspi_resources,
	.dev = {
		.platform_data	= &hi6421_codec_plat_data,
	},
};
#endif

#ifdef CONFIG_HI6401_CODEC
/*device : hi6401-codec*/
static struct hi6401_codec_platform_data hi6401_codec_plat_data = {
    .clk_name        = CLK_PMUSSI,
    .regulator_name  = AUDIO_CODEC_ANALOG_1P8V_VDD,   /* "audio-vcc" */
    .reg_base_name   = "hi6401_base",
	.gpio_label      = "hi6401",
    .gpio_dvdd_1v8   = GPIO_6_7,
    .gpio_avdd_1v8   = GPIO_6_6,
    .gpio_avdd_3v15  = GPIO_6_5,
#ifdef CONFIG_MACH_HI6620OEM
    .iomux_name      = "block_codec",
    .reg_dvdd_1v8    = CODEC_IO_VDD,
    .reg_avdd_1v8    = AUDIO_CODEC_ANALOG_1P8V_VDD,
    .reg_avdd_3v15   = CODEC_AVDD_VDD,
#endif
};

static struct resource pmussi_resources[] = {
	{
		.name	= "hi6401_base",
		.start	= REG_BASE_PMUSSI,
		.end	= REG_BASE_PMUSSI + REG_PMUSSI_IOSIZE - 1,
		.flags	= IORESOURCE_MEM,
	}
};

static struct platform_device hi6401_codec_device = {
	.name	= "hi6401-codec",
	.id	= -1,
	.num_resources	= ARRAY_SIZE(pmussi_resources),
	.resource	= pmussi_resources,
	.dev = {
		.platform_data	= &hi6401_codec_plat_data,
	},
};
#endif

#ifdef CONFIG_MFD_HI6421_IRQ
static struct resource hi6421_irq_resources[] = {
	{
		.start		= REG_BASE_PMUSPI_SFT,
		.end		= REG_BASE_PMUSPI_SFT + REG_PMUSPI_SFT_IOSIZE - 1,
		.flags		= IORESOURCE_MEM,
	},
	{
		.start		= IRQ_GPIO10_0,
		.end		= IRQ_GPIO10_0,
		.flags		= IORESOURCE_IRQ,
	},
};

static struct platform_device hi6421_irq_device = {
	.name		= "hi6421-irq",
	.id			= 0,
	.dev.platform_data	= NULL,
	.num_resources		= ARRAY_SIZE(hi6421_irq_resources),
	.resource       =  hi6421_irq_resources,
};
#endif

#ifdef CONFIG_HI6421_CODEC
/*device : hi6620-hi6421*/
static u64 audio_card_dmamask = DMA_BIT_MASK(32);

static struct platform_device hi6620_hi6421_device = {
	.name = "hi6620_hi6421",
	.id   = -1,
	.dev = {
		.dma_mask	= &audio_card_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	},
};
#endif

#ifdef CONFIG_HI6401_CODEC
/*device : hi6620-hi6401*/
static u64 audio_card_dmamask = DMA_BIT_MASK(32);

static struct platform_device hi6620_hi6401_device = {
	.name = "hi6620_hi6401",
	.id   = -1,
	.dev = {
		.dma_mask	= &audio_card_dmamask,
		.coherent_dma_mask	= DMA_BIT_MASK(32),
	},
};
#endif

#ifdef CONFIG_SND_HIFI_LPP
static struct platform_device hifi_dsp_device = {
	.name = "hifi_dsp_misc",
	.id	= -1,
};
#endif

#ifdef CONFIG_TPA6132
/* TPA6132 */
static struct tpa6132_platform_data tpa6132_pdata = {
	.gpio_tpa6132_en    = GPIO_5_1,
};
static struct platform_device tpa6132_device = {
	.name    = TPA6132_NAME,
	.id      = 0,
	.dev     = {
		.platform_data = &tpa6132_pdata,
	},
};
#endif

#ifdef CONFIG_SPK_5VBOOST
static struct spk_5vboost_platform_data spk_5vboost_pdata = {
	.gpio_5vboost_en    = GPIO_7_4,/* 139 */
};

static struct platform_device spk_5vboost_device = {
	.name    = SPK_5VBOOST_NAME,
	.id      = 0,
	.dev     = {
		.platform_data = &spk_5vboost_pdata,
	},
};
#endif

/* please add platform device in the struct.*/
static struct platform_device *plat_audio_dev[] __initdata = {
    &hifi_device,
#ifdef CONFIG_SND_ASP
    &aspdigital_device,
	&hisik3_digital_audio_device,
#endif
#ifdef CONFIG_MFD_HI6421_IRQ
    &hi6421_irq_device,
#endif
#ifdef CONFIG_HI6421_CODEC
    &hi6421_codec_device,
    &hi6620_hi6421_device,
#endif
#ifdef CONFIG_HI6401_CODEC
    &hi6401_codec_device,
    &hi6620_hi6401_device,
#endif
    /*add other device here*/
#ifdef CONFIG_SND_HIFI_LPP
    &hifi_dsp_device,
#endif
#ifdef CONFIG_TPA6132
    &tpa6132_device,
#endif
#ifdef CONFIG_SPK_5VBOOST
    &spk_5vboost_device,
#endif
};

#ifdef CONFIG_HI6401_CODEC

static void set_audio_gpio(void)
{
    int ret = 0;
    int gpio_intr = 0;
    int gpio_reset = 0;

    ret = get_hw_config_int("audio/gpio_codec_reset", &gpio_reset, NULL);
    if (false == ret) {
        printk("gpio_reset value not found !\n");
        hi6401_codec_plat_data.gpio_reset = GPIO_6_3;
    } else {
        hi6401_codec_plat_data.gpio_reset = gpio_reset;
    }

#ifdef CONFIG_MACH_HI6620OEM	
    ret = get_hw_config_int("audio/gpio_intr", &gpio_intr, NULL);
    if (false == ret) {
        printk("gpio_intr value not found !\n");
        hi6401_codec_plat_data.gpio_intr = GPIO_0_7;
    } else {
        hi6401_codec_plat_data.gpio_intr = gpio_intr;
    }
#endif
}

#endif

static int __init plat_audio_dev_init(void)
{
    int ret = 0;

    set_audio_gpio();
    ret = platform_add_devices(plat_audio_dev, ARRAY_SIZE(plat_audio_dev));

    return ret;
};

arch_initcall(plat_audio_dev_init);

