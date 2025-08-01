/* Generated configuration header file - do not edit */
/*
* Copyright (C) 2016 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/
/***********************************************************************************************************************
 * File Name    : r_ether_rx_config.h
 * Version      : 1.24
 * Description  : Ethernet module device driver
 ***********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 22.07.2014 1.00     First Release
 *         : 31.03.2016 1.01     Added changes for RX63N.
 *         : 01.10.2016 1.02     Added changes for RX65N.
 *         : 01.10.2017 1.03     Added changes for RX65N-2MB.
 *         : 08.01.2018 1.04     Changed comment.
 *         : 30.07.2019 1.17     Added changes for RX72M.
 *         : 22.11.2019 1.20     Added changes for RX72N.
 *         : 20.11.2021 1.22     Added config macro.
 *         : 20.03.2025 1.24     Changed the disclaimer in program sources
 ***********************************************************************************************************************/

/* Guards against multiple inclusion */
#ifndef R_ETHER_RX_CONFIG_H
    #define R_ETHER_RX_CONFIG_H

/***********************************************************************************************************************
 Macro definitions
 ***********************************************************************************************************************/

/* Ethernet interface select.
 0 = MII  (Media Independent Interface)
 1 = RMII (Reduced Media Independent Interface)
 */
    #define ETHER_CFG_MODE_SEL                          (1)

/* PHY-LSI address setting for ETHER0/1.
 Please set the value 31 ETHER_CFG_CH0_PHY_ADDRESS when use default setting of the RSK+RX63N.
 Please set the value 30 ETHER_CFG_CH0_PHY_ADDRESS when use default setting of the RSK+RX65N/RSK+RX65N_2MB.
 Please set the value 0 ETHER_CFG_CH0_PHY_ADDRESS and value 1 ETHER_CFG_CH1_PHY_ADDRESS when use default
 setting of the RSK+RX64M/RSK+RX71M.
 Please set the value 1 ETHER_CFG_CH0_PHY_ADDRESS and value 2 ETHER_CFG_CH1_PHY_ADDRESS when use default
 setting of the RSK+RX72M.
 Please set the value 1 ETHER_CFG_CH1_PHY_ADDRESS when use default setting of the RSK+RX72N.
 */
/* Please define the PHY-LSI address in the range of 0-31. */
    #define ETHER_CFG_CH0_PHY_ADDRESS                   (5)
    #define ETHER_CFG_CH1_PHY_ADDRESS                   (1)

/* The number of Rx descriptors. */
    #define ETHER_CFG_EMAC_RX_DESCRIPTORS               (4)

/* The number of Tx descriptors. */
    #define ETHER_CFG_EMAC_TX_DESCRIPTORS               (4)

/* Please define the size of the sending and receiving buffer in the value where one frame can surely be stored 
 because the driver is single-frame/single-buffer processing.  */
    #define ETHER_CFG_BUFSIZE                           (1536)  /* Must be 32-byte aligned */

/* EINT interrupt priority level. This definition is not used when EINT interrupt is assigned to Group interrupt. */
/* Please define the interruption level within the range of 1-15. */
    #define ETHER_CFG_EINT_INT_PRIORITY                 (2)

/* Group AL1 interrupt priority level. This definition is not used when EINT interrupt is assigned to Peripheral 
 interrupt. */
/* Please define the interruption level within the range of 1-15. */
    #define ETHER_CFG_AL1_INT_PRIORTY                   (2)

/* The register bus of PHY0/1 for ETHER0/1 select
 0 = The access of the register of PHY uses ETHER0.
 1 = The access of the register of PHY uses ETHER1.

 Please set the value 0 ETHER_CFG_CH0_PHY_ACCESS when use default setting of the RSK+RX63N.
 Please set the value 0 ETHER_CFG_CH0_PHY_ACCESS when use default setting of the RSK+RX65N/RSK+RX65N_2MB.
 Please set the value 1 ETHER_CFG_CH0_PHY_ACCESS and ETHER_CFG_CH1_PHY_ACCESS when use default
 setting of the RSK+RX64M/RSK+RX71M.
 Please set the value 0 ETHER_CFG_CH0_PHY_ACCESS and ETHER_CFG_CH1_PHY_ACCESS when use default setting of the RSK+RX72M.
 Please set the value 1 ETHER_CFG_CH1_PHY_ACCESS when use default setting of the RSK+RX72N.
 */
    #define ETHER_CFG_CH0_PHY_ACCESS                    (0)
    #define ETHER_CFG_CH1_PHY_ACCESS                    (1)

/* Define the access timing of MII/RMII register */
    #define ETHER_CFG_PHY_MII_WAIT                      (8)     /* Please define the value of 1 or more */

/* Define the waiting time for reset completion of PHY-LSI */
    #define ETHER_CFG_PHY_DELAY_RESET                   (0x00020000L)

/**
 * Link status read from LMON bit of ETHERC PSR register.  The state is hardware dependent.
 */
    #define ETHER_CFG_LINK_PRESENT                      (1)

/*  Use LINKSTA signal for detect link status changes
 0 = unused  (use PHY-LSI status register)
 1 = use     (use LINKSTA signal)
 */
    #define ETHER_CFG_USE_LINKSTA                       (1)     /* This setting is reflected in all channels */

/* Definition of whether or not to use KSZ8041NL of the Micrel Inc.
 0 = unused
 1 = use
 */
    #define ETHER_CFG_USE_PHY_KSZ8041NL                 (0)

/* Definition of whether or not to use ICS1894_32 of the Renesas Electronics Corporation.
 0 = unused
 1 = use
 */
    #define ETHER_CFG_USE_PHY_ICS1894_32                (1)

/* Definition of whether or not to use non blocking of PHY Management Station Operation
 0 = unused
 1 = use
*/
    #define ETHER_CFG_NON_BLOCKING                      (0)

/* Define the clock of the PHY Management Station */
    #define ETHER_CFG_PMGI_CLOCK                        (2500000)

/* PHY Management Station Preamble Control
 0 = Disable
 1 = Enable
 */
    #define ETHER_CFG_PMGI_ENABLE_PREAMBLE              (0)

/* Define the Hold Time Adjustment of the PHY Management Station */
    #define ETHER_CFG_PMGI_HOLD_TIME                    (0)

/* Define the Capture Time Adjustment of the PHY Management Station */
    #define ETHER_CFG_PMGI_CAPTURE_TIME                 (0)

/* PMGI interrupt priority level. This definition is not used when PMGI interrupt is assigned to Peripheral
 interrupt. */
    #define ETHER_CFG_PMGI_INT_PRIORTY                  (2)
/***********************************************************************************************************************
 Typedef definitions
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global variables
 ***********************************************************************************************************************/

/***********************************************************************************************************************
 Exported global functions (to be accessed by other files)
 ***********************************************************************************************************************/

#endif /* R_ETHER_RX_CONFIG_H */
