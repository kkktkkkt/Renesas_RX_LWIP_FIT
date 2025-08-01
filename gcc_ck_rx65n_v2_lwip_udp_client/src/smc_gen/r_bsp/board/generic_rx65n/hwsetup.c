/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : hwsetup.c
* Device(s)    : RX
* H/W Platform : GENERIC_RX65N
* Description  : Defines the initialization routines used each time the MCU is restarted.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History : DD.MM.YYYY Version   Description
*         : 15.05.2017 1.00      First Release
*         : 01.12.2017 1.01      Added EBMAPCR register setting.
*         : 01.07.2018 1.02      Added the initialization function for Smart Configurator.
*         : 27.07.2018 1.03      Modified the comment of bsp_adc_initial_configure.
*         : 28.02.2019 2.00      Added support for GNUC and ICCRX.
*                                Fixed coding style.
*                                Added the following function.
*                                - rom_cache_function_set
*         : 20.11.2020 2.01      Modified the proccess of bsp_adc_initial_configure function.
*         : 21.11.2023 2.02      Added compile switch of BSP_CFG_BOOTLOADER_PROJECT.
*         : 26.02.2025 2.03      Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes   <System Includes> , "Project Includes"
***********************************************************************************************************************/
/* I/O Register and board definitions */
#include "platform.h"
#if BSP_CFG_CONFIGURATOR_SELECT == 1
#include "r_cg_macrodriver.h"
#endif

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
R_BSP_PRAGMA_UNPACK
typedef struct bsp_bsc {
    union {
        uint32_t u_long;
        R_BSP_ATTRIB_STRUCT_BIT_ORDER_LEFT_13(
            uint32_t prerr:1,
            uint32_t :1,
            uint32_t rpstop:1,
            uint32_t :10,
            uint32_t pr5sel:3,
            uint32_t :1,
            uint32_t pr4sel:3,
            uint32_t :1,
            uint32_t pr3sel:3,
            uint32_t :1,
            uint32_t pr2sel:3,
            uint32_t :1,
            uint32_t pr1sel:3
        ) bit;
    } ebmapcr;
} st_bsp_bsc_t;
R_BSP_PRAGMA_PACKOPTION

/***********************************************************************************************************************
Private global variables and functions
***********************************************************************************************************************/
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
/* ROM cache configuration function declaration */
#if BSP_CFG_ROM_CACHE_ENABLE == 1
static void rom_cache_function_set(void);
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/* MCU I/O port configuration function declaration */
static void output_ports_configure(void);

/* Interrupt configuration function declaration */
static void interrupts_configure(void);
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/* MCU peripheral module configuration function declaration */
static void peripheral_modules_enable(void);

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */

/* ADC initial configuration function declaration */
static void bsp_adc_initial_configure(void);

#if defined(BSP_MCU_RX65N_2MB)
/* BUS initial configuration function declaration */
static void bsp_bsc_initial_configure(void);
#endif/* BSP_MCU_RX65N_2MB */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/***********************************************************************************************************************
* Function name: hardware_setup
* Description  : Contains setup functions called at device restart
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
void hardware_setup(void)
{
/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
#if BSP_CFG_ROM_CACHE_ENABLE == 1
    /* Initialize ROM cache function */
    rom_cache_function_set();
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following functions in the bootloader project. */
    output_ports_configure();
    interrupts_configure();
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */
    peripheral_modules_enable();
    bsp_non_existent_port_init();
#if BSP_CFG_BOOTLOADER_PROJECT == 0
    /* Disable the following functions in the bootloader project. */
    bsp_adc_initial_configure();
  #if defined(BSP_MCU_RX65N_2MB)
    bsp_bsc_initial_configure();
  #endif/* BSP_MCU_RX65N_2MB */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */
} /* End of function hardware_setup() */

/* When using the user startup program, disable the following code. */
#if BSP_CFG_STARTUP_DISABLE == 0
#if BSP_CFG_ROM_CACHE_ENABLE == 1
/***********************************************************************************************************************
* Function name: rom_cache_function_set
* Description  : Configures the rom cache function.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void rom_cache_function_set (void)
{
    /* Invalidates the contents of the ROM cache. */
    FLASH.ROMCIV.WORD = 0x0001;
    /* WAIT_LOOP */
    while (FLASH.ROMCIV.WORD != 0x0000)
    {
        /* wait for bit to set */
    }

    /* Enables the ROM cache. */
    FLASH.ROMCE.WORD = 0x0001;
    /* WAIT_LOOP */
    while (FLASH.ROMCE.WORD != 0x0001)
    {
        /* wait for bit to set */
    }
} /* End of function rom_cache_function_set() */
#endif /* BSP_CFG_ROM_CACHE_ENABLE == 1 */
#endif /* BSP_CFG_STARTUP_DISABLE == 0 */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/***********************************************************************************************************************
* Function name: output_ports_configure
* Description  : Configures the port and pin direction settings, and sets the pin outputs to a safe level.
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void output_ports_configure(void)
{
    /* Add code here to setup additional output ports */
    R_BSP_NOP();
} /* End of function output_ports_configure() */

/***********************************************************************************************************************
* Function name: interrupts_configure
* Description  : Configures interrupts used
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void interrupts_configure(void)
{
    /* Add code here to setup additional interrupts */
    R_BSP_NOP();
} /* End of function interrupts_configure() */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

/***********************************************************************************************************************
* Function name: peripheral_modules_enable
* Description  : Enables and configures peripheral devices on the MCU
* Arguments    : none
* Return value : none
***********************************************************************************************************************/
static void peripheral_modules_enable(void)
{
    /* Add code here to enable peripherals used by the application */
#if BSP_CFG_CONFIGURATOR_SELECT == 1
    /* Smart Configurator initialization function */
    R_Systeminit();
#endif
} /* End of function peripheral_modules_enable() */

#if BSP_CFG_BOOTLOADER_PROJECT == 0
/* Disable the following functions in the bootloader project. */
/***********************************************************************************************************************
* Function name: bsp_adc_initial_configure
* Description  : Configures the ADC initial settings
* Arguments    : none
* Return value : none
* Note         : This function should be called when the PSW.I bit is 0 (interrupt disabled).
*                This function should be called when the ADCSR.ADST bit is 0.
***********************************************************************************************************************/
static void bsp_adc_initial_configure(void)
{
    uint32_t tmp_mstp;

    /* Protect off. */
    SYSTEM.PRCR.WORD = 0xA502;

    /* Store the value of the MSTPCR. */
    tmp_mstp = MSTP(S12AD1);

    /* Release from the module-stop state */
    MSTP(S12AD1) = 0;

    if(0 != MSTP(S12AD1))
    {
        R_BSP_NOP();
    }

    /* Writing to the A/D conversion time setting register is enabled. */
    S12AD1.ADSAMPR.BYTE = 0x03;

    /* Sets conversion time for middle-speed for S12AD unit 1. */
    S12AD1.ADSAM.WORD = 0x0020;

    /* Writing to the A/D conversion time setting register is disabled. */
    S12AD1.ADSAMPR.BYTE = 0x02;

    /* Restore the value of the MSTPCR. */
    MSTP(S12AD1) = tmp_mstp;

    /* Protect on. */
    SYSTEM.PRCR.WORD = 0xA500;
} /* End of function bsp_adc_initial_configure() */

#if defined(BSP_MCU_RX65N_2MB)
/***********************************************************************************************************************
* Function name: bsp_bsc_initial_configure
* Description  : Configures the BUS initial settings
* Arguments    : none
* Return value : none
* Note         : The EBMAPCR register is only available for products with at least 1.5 Mbytes of code flash memory.
***********************************************************************************************************************/
static void bsp_bsc_initial_configure(void)
{
    st_bsp_bsc_t bsp_bsc;

    /* Setting priority when bus right request contention occurs. */
    bsp_bsc.ebmapcr.u_long     = BSC.EBMAPCR.LONG;
    bsp_bsc.ebmapcr.bit.pr1sel = BSP_CFG_EBMAPCR_1ST_PRIORITY;
    bsp_bsc.ebmapcr.bit.pr2sel = BSP_CFG_EBMAPCR_2ND_PRIORITY;
    bsp_bsc.ebmapcr.bit.pr3sel = BSP_CFG_EBMAPCR_3RD_PRIORITY;
    bsp_bsc.ebmapcr.bit.pr4sel = BSP_CFG_EBMAPCR_4TH_PRIORITY;
    bsp_bsc.ebmapcr.bit.pr5sel = BSP_CFG_EBMAPCR_5TH_PRIORITY;

    /* Set to EBMAPCR register */
    BSC.EBMAPCR.LONG = bsp_bsc.ebmapcr.u_long;
} /* End of function bsp_bsc_initial_configure() */
#endif/* BSP_MCU_RX65N_2MB */
#endif /* BSP_CFG_BOOTLOADER_PROJECT == 0 */

