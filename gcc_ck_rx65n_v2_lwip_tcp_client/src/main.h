/**********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : main.h
 * Description  : 
 *********************************************************************************************************************/

#ifndef MAIN_H
#define MAIN_H

/**********************************************************************************************************************
 * Macro definitions
 *********************************************************************************************************************/
#define TEST_TCP_DEST_PORT      5000   /* define the TCP port */

/*Static IP ADDRESS: IP_ADDR0.IP_ADDR1.IP_ADDR2.IP_ADDR3 */
#define TEST_IP_ADDR0           ((uint8_t) 192U)
#define TEST_IP_ADDR1           ((uint8_t) 168U)
#define TEST_IP_ADDR2           ((uint8_t) 137U)
#define TEST_IP_ADDR3           ((uint8_t) 66U)
/*NETMASK*/
#define TEST_NETMASK_ADDR0      ((uint8_t) 255U)
#define TEST_NETMASK_ADDR1      ((uint8_t) 255U)
#define TEST_NETMASK_ADDR2      ((uint8_t) 255U)
#define TEST_NETMASK_ADDR3      ((uint8_t) 0U)

/*Gateway Address*/
#define TEST_GW_ADDR0           ((uint8_t) 192U)
#define TEST_GW_ADDR1           ((uint8_t) 168U)
#define TEST_GW_ADDR2           ((uint8_t) 137U)
#define TEST_GW_ADDR3           ((uint8_t) 1U)

#define TEST_DEST_IP_ADDR0      ((uint8_t) 192U)
#define TEST_DEST_IP_ADDR1      ((uint8_t) 168U)
#define TEST_DEST_IP_ADDR2      ((uint8_t) 137U)
#define TEST_DEST_IP_ADDR2      ((uint8_t) 11U)
#define TEST_DEST_IP_ADDR3      ((uint8_t) 1U)

#endif /* MAIN_H */
