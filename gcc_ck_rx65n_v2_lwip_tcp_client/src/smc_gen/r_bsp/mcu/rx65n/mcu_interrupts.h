/*
* Copyright (c) 2011 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
* File Name    : mcu_interrupts.h
* Description  : This module is the control of the interrupt enable.
***********************************************************************************************************************/
/**********************************************************************************************************************
* History : DD.MM.YYYY Version   Description
*         : 01.10.2016 1.00      First Release
*         : 15.05.2017 2.00      Added the following enumeration constant.
*                                - BSP_INT_SRC_EXRAM
*                                - BSP_INT_SRC_BL1_RIIC1_TEI1
*                                - BSP_INT_SRC_BL1_RIIC1_EEI1
*                                - BSP_INT_SRC_AL1_GLCDC_VPOS
*                                - BSP_INT_SRC_AL1_GLCDC_GR1UF
*                                - BSP_INT_SRC_AL1_GLCDC_GR2UF
*                                - BSP_INT_SRC_AL1_DRW2D_DRW_IRQ
*         : 28.02.2019 2.00      Added the following prototype declaration.
*                                - bsp_interrupt_enable_disable
*                                Deleted the following prototype declarations. 
*                                (The following prototype declarations moved to the common file (r_bsp_interrupts.h).)
*                                - bsp_interrupt_open
*                                - R_BSP_InterruptWrite
*                                - R_BSP_InterruptRead
*                                - R_BSP_InterruptControl
*                                Added the following enumeration constant.
*                                - BSP_INT_SRC_GR_INT_TOP
*                                - BSP_INT_SRC_GR_INT_BE0_TOP
*                                - BSP_INT_SRC_GR_INT_BL0_TOP
*                                - BSP_INT_SRC_GR_INT_BL1_TOP
*                                - BSP_INT_SRC_GR_INT_BL2_TOP
*                                - BSP_INT_SRC_GR_INT_AL0_TOP
*                                - BSP_INT_SRC_GR_INT_AL1_TOP
*                                - BSP_INT_SRC_GR_INT_END
*                                - BSP_INT_SRC_BE0_CAN0_ERS0
*                                - BSP_INT_SRC_BE0_CAN1_ERS1
*                                Fixed coding style.
*         : 08.04.2019 2.01      Added the following enumeration constant.
*                                - BSP_INT_SRC_GR_INT_IE0_TOP
*         : 26.07.2019 2.10      Added the following command.
*                                - BSP_INT_CMD_FIT_INTERRUPT_ENABLE
*                                - BSP_INT_CMD_FIT_INTERRUPT_DISABLE
*                                Added the following error code.
*                                - BSP_INT_ERR_INVALID_IPL
*                                Added the following enumeration constant.
*                                - BSP_INT_SRC_EMPTY
*         : 21.11.2023 2.11      Added the following enumeration constant.
*                                - BSP_INT_SRC_BUS_ERROR_ILLEGAL_ACCESS
*                                - BSP_INT_SRC_BUS_ERROR_TIMEOUT
*         : 26.02.2025 2.12      Changed the disclaimer.
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef MCU_INTERRUPTS_H
#define MCU_INTERRUPTS_H

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Available return codes. */
typedef enum
{
    BSP_INT_SUCCESS = 0,
    BSP_INT_ERR_NO_REGISTERED_CALLBACK,     /* There is not a registered callback for this interrupt source */
    BSP_INT_ERR_INVALID_ARG,                /* Illegal argument input */
    BSP_INT_ERR_UNSUPPORTED,                /* Operation is not supported by this API */
    BSP_INT_ERR_GROUP_STILL_ENABLED,        /* Not all group interrupts were disabled so group interrupt was not 
                                               disabled */
    BSP_INT_ERR_INVALID_IPL                 /* Illegal IPL value input */
} bsp_int_err_t;

/* Available interrupts to register a callback for. */
typedef enum
{
    BSP_INT_SRC_EXC_SUPERVISOR_INSTR = 0, /* Occurs when privileged instruction is executed in User Mode */
    BSP_INT_SRC_EXC_UNDEFINED_INSTR,      /* Occurs when MCU encounters an unknown instruction */
    BSP_INT_SRC_EXC_NMI_PIN,              /* NMI Pin interrupt */
    BSP_INT_SRC_EXC_FPU,                  /* FPU exception */
    BSP_INT_SRC_EXC_ACCESS,               /* Access exception */
    BSP_INT_SRC_OSC_STOP_DETECT,          /* Oscillation stop is detected */
    BSP_INT_SRC_WDT_ERROR,                /* WDT underflow/refresh error has occurred */
    BSP_INT_SRC_IWDT_ERROR,               /* IWDT underflow/refresh error has occurred */
    BSP_INT_SRC_LVD1,                     /* Voltage monitoring 1 interrupt */
    BSP_INT_SRC_LVD2,                     /* Voltage monitoring 2 interrupt */
    BSP_INT_SRC_UNDEFINED_INTERRUPT,      /* Interrupt has triggered for a vector that user did not write a handler. */
    BSP_INT_SRC_BUS_ERROR,                /* Bus error: illegal address access or timeout */
    BSP_INT_SRC_BUS_ERROR_ILLEGAL_ACCESS, /* Bus error: illegal address access. Use this when you want to set only Illegal address access detection. */
    BSP_INT_SRC_BUS_ERROR_TIMEOUT,        /* Bus error: timeout. Use this when you want to set only Bus timeout detection. */
    BSP_INT_SRC_RAM,                      /* RAM error interrupt */
    BSP_INT_SRC_EXRAM,                    /* EXRAM error interrupt */

    BSP_INT_SRC_GR_INT_TOP,

    /* IE0 Group Interrupts */
    BSP_INT_SRC_GR_INT_IE0_TOP,

    /* BE0 Group Interrupts */
    BSP_INT_SRC_GR_INT_BE0_TOP,
    BSP_INT_SRC_BE0_CAN0_ERS0,
    BSP_INT_SRC_BE0_CAN1_ERS1,

    /* BL0 Group Interrupts. */
    BSP_INT_SRC_GR_INT_BL0_TOP,
    BSP_INT_SRC_BL0_SCI0_TEI0,
    BSP_INT_SRC_BL0_SCI0_ERI0,
    BSP_INT_SRC_BL0_SCI1_TEI1,
    BSP_INT_SRC_BL0_SCI1_ERI1,
    BSP_INT_SRC_BL0_SCI2_TEI2,
    BSP_INT_SRC_BL0_SCI2_ERI2,
    BSP_INT_SRC_BL0_SCI3_TEI3,
    BSP_INT_SRC_BL0_SCI3_ERI3,
    BSP_INT_SRC_BL0_SCI4_TEI4,
    BSP_INT_SRC_BL0_SCI4_ERI4,
    BSP_INT_SRC_BL0_SCI5_TEI5,
    BSP_INT_SRC_BL0_SCI5_ERI5,
    BSP_INT_SRC_BL0_SCI6_TEI6,
    BSP_INT_SRC_BL0_SCI6_ERI6,
    BSP_INT_SRC_BL0_SCI7_TEI7,
    BSP_INT_SRC_BL0_SCI7_ERI7,
    BSP_INT_SRC_BL0_SCI12_TEI12,
    BSP_INT_SRC_BL0_SCI12_ERI12,
    BSP_INT_SRC_BL0_SCI12_SCIX0,
    BSP_INT_SRC_BL0_SCI12_SCIX1,
    BSP_INT_SRC_BL0_SCI12_SCIX2,
    BSP_INT_SRC_BL0_SCI12_SCIX3,
    BSP_INT_SRC_BL0_QSPI_QSPSSLI,
    BSP_INT_SRC_BL0_CAC_FERRI,
    BSP_INT_SRC_BL0_CAC_MENDI,
    BSP_INT_SRC_BL0_CAC_OVFI,
    BSP_INT_SRC_BL0_DOC_DOPCI,
    BSP_INT_SRC_BL0_PDC_PCFEI,
    BSP_INT_SRC_BL0_PDC_PCERI,

    /* BL1 Group Interrupts. */
    BSP_INT_SRC_GR_INT_BL1_TOP,
    BSP_INT_SRC_BL1_SDHI_CDETI,
    BSP_INT_SRC_BL1_SDHI_CACI,
    BSP_INT_SRC_BL1_SDHI_SDACI,
    BSP_INT_SRC_BL1_MMCIF_CDETIO,
    BSP_INT_SRC_BL1_MMCIF_ERRIO,
    BSP_INT_SRC_BL1_MMCIF_ACCIO,
    BSP_INT_SRC_BL1_POE3_OEI1,
    BSP_INT_SRC_BL1_POE3_OEI2,
    BSP_INT_SRC_BL1_POE3_OEI3,
    BSP_INT_SRC_BL1_POE3_OEI4,
    BSP_INT_SRC_BL1_RIIC0_TEI0,
    BSP_INT_SRC_BL1_RIIC0_EEI0,
    BSP_INT_SRC_BL1_RIIC2_TEI2,
    BSP_INT_SRC_BL1_RIIC2_EEI2,
    BSP_INT_SRC_BL1_S12AD0_S12CMPAI,
    BSP_INT_SRC_BL1_S12AD0_S12CMPBI,
    BSP_INT_SRC_BL1_S12AD1_S12CMPAI1,
    BSP_INT_SRC_BL1_S12AD1_S12CMPBI1,
    BSP_INT_SRC_BL1_SCI8_TEI8,
    BSP_INT_SRC_BL1_SCI8_ERI8,
    BSP_INT_SRC_BL1_SCI9_TEI9,
    BSP_INT_SRC_BL1_SCI9_ERI9,
    BSP_INT_SRC_BL1_RIIC1_TEI1,
    BSP_INT_SRC_BL1_RIIC1_EEI1,

    /* BL2 Group Interrupts. */
    BSP_INT_SRC_GR_INT_BL2_TOP,
    BSP_INT_SRC_BL2_SDSI_SDIOI,

    /* AL0 Group Interrupts. */
    BSP_INT_SRC_GR_INT_AL0_TOP,
    BSP_INT_SRC_AL0_SCI10_TEI10,
    BSP_INT_SRC_AL0_SCI10_ERI10,
    BSP_INT_SRC_AL0_SCI11_TEI11,
    BSP_INT_SRC_AL0_SCI11_ERI11,
    BSP_INT_SRC_AL0_RSPI0_SPII0,
    BSP_INT_SRC_AL0_RSPI0_SPEI0,
    BSP_INT_SRC_AL0_RSPI1_SPII1,
    BSP_INT_SRC_AL0_RSPI1_SPEI1,
    BSP_INT_SRC_AL0_RSPI2_SPII2,
    BSP_INT_SRC_AL0_RSPI2_SPEI2,

    /* AL1 Group Interrupts. */
    BSP_INT_SRC_GR_INT_AL1_TOP,
    BSP_INT_SRC_AL1_EDMAC0_EINT0,
    BSP_INT_SRC_AL1_GLCDC_VPOS,
    BSP_INT_SRC_AL1_GLCDC_GR1UF,
    BSP_INT_SRC_AL1_GLCDC_GR2UF,
    BSP_INT_SRC_AL1_DRW2D_DRW_IRQ,

    BSP_INT_SRC_GR_INT_END,
    BSP_INT_SRC_EMPTY,
    BSP_INT_SRC_TOTAL_ITEMS               /* DO NOT MODIFY! This is used for sizing the interrupt callback array. */
} bsp_int_src_t;

/* Available commands for R_BSP_InterruptControl() function. */
typedef enum
{
    BSP_INT_CMD_CALL_CALLBACK = 0,        /* Calls registered callback function if one exists */
    BSP_INT_CMD_INTERRUPT_ENABLE,         /* Enables a given interrupt (Available for NMI pin, FPU, and Bus Error) */
    BSP_INT_CMD_INTERRUPT_DISABLE,        /* Disables a given interrupt (Available for FPU, and Bus Error) */
    BSP_INT_CMD_GROUP_INTERRUPT_ENABLE,   /* Enables a group interrupt when a group interrupt source is given. The
                                             pdata argument should give the IPL to be used using the bsp_int_ctrl_t
                                             type. If a group interrupt is enabled multiple times with different IPL
                                             levels it will use the highest given IPL. */
    BSP_INT_CMD_GROUP_INTERRUPT_DISABLE,  /* Disables a group interrupt when a group interrupt source is given.
                                             This will only disable a group interrupt when all interrupt
                                             sources for that group are already disabled. */
    BSP_INT_CMD_FIT_INTERRUPT_ENABLE,     /* Enables interrupt by control of IPL. */
    BSP_INT_CMD_FIT_INTERRUPT_DISABLE     /* Disables interrupt by control of IPL. */
} bsp_int_cmd_t;

/* Type to be used for pdata argument in Control function. */
typedef union
{
    uint32_t ipl;                         /* Used at the following times.
                                             - When enabling an interrupt to set that interrupt's priority level 
                                               by BSP_INT_CMD_GROUP_INTERRUPT_ENABLE command.
                                             - When disabling an interrupt to save that interrupt's priority level 
                                               by BSP_INT_CMD_FIT_INTERRUPT_DISABLE command.
                                             - When enabling an interrupt to set that interrupt's priority level 
                                               by BSP_INT_CMD_FIT_INTERRUPT_ENABLE command. */
} bsp_int_ctrl_t;

/* Easy to use typedef for callback functions. */
typedef void (*bsp_int_cb_t)(void *);

/* This structure is the common one that is passed as the 'void *' argument to callback functions when an
 * exception occurs.
 */
typedef struct
{
    bsp_int_src_t vector;         /* Which vector caused this interrupt */
} bsp_int_cb_args_t;

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/
bsp_int_err_t bsp_interrupt_enable_disable(bsp_int_src_t vector, bool enable);

#endif /* MCU_INTERRUPTS_H */

