/**********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
　* 2025-06-20: Modified by Kei.K : Change the compiler from CC-RX to GCC
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * File Name    : main.c
 * Description  : Example program for using lwip
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "r_smc_entry.h"
#include "r_ether_rx_if.h"
#include "r_ether_rx_pinset.h"

#include "main.h"

#include "lwip/sys.h"
#include "lwip/init.h"
#include "lwip/opt.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/tcp.h"
#include "lwip/dhcp.h"
#include "lwip/prot/dhcp.h"

#include "lwip/igmp.h"
#include "netif/ethernet.h"

#include "r_lwip_driver_rx_if.h"
#include "r_lwip_driver_rx_config.h"

#if BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true ||  BSP_CFG_MCU_PART_FUNCTION == (0x11)
#include "r_tsip_rx_if.h"
#include "r_tsip_rx_config.h"
#endif /* BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true ||  BSP_CFG_MCU_PART_FUNCTION == (0x11) */

/**********************************************************************************************************************
 * Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Exported global variables
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Private (static) variables and functions
 *********************************************************************************************************************/
void main(void);
extern void echodemo_tcp_client_connect(void);

static struct netif s_netif;

static uint32_t s_ethernet_link_timer = 0;
bool fin_flag = true;

/**********************************************************************************************************************
 * Function Name  @fn   Ethernet_Link_Periodic_Handle
 *********************************************************************************************************************/
void Ethernet_Link_Periodic_Handle(void)
{
    /* Ethernet Link every 100ms */
    if (sys_now() - s_ethernet_link_timer >= 100)
    {
        s_ethernet_link_timer = sys_now();
        R_LWIP_DRIVER_EthernetLinkCheck(&s_netif);
    }
}
/**********************************************************************************************************************
 * End of function Ethernet_Link_Periodic_Handle
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function Name  @fn   main
 *********************************************************************************************************************/
void main(void)
{
    e_lwip_drv_return_t res;
    uint32_t cmt_ch = 0;
    uint32_t eth_ch = 0;
    uint32_t counts = 0;

    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

#if BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true ||  BSP_CFG_MCU_PART_FUNCTION == (0x11)
    R_TSIP_Open(NULL, NULL);
#endif /* BSP_CFG_MCU_PART_ENCRYPTION_INCLUDED == true ||  BSP_CFG_MCU_PART_FUNCTION == (0x11) */
    res = R_LWIP_DRIVER_Open(&cmt_ch, 1);

    while(LWIP_DRV_SUCCESS != res)
    {
        ; /* Nothing to do */
    }

    /* Initialize the LwIP stack */
    lwip_init();

    /* Setting Netif */
#if LWIP_DHCP
    ip_addr_set_zero_ip4(&ipaddr);
    ip_addr_set_zero_ip4(&netmask);
    ip_addr_set_zero_ip4(&gw);
#else
    /* IP address default setting */
    IP4_ADDR(&ipaddr, TEST_IP_ADDR0, TEST_IP_ADDR1, TEST_IP_ADDR2, TEST_IP_ADDR3);
    IP4_ADDR(&netmask, TEST_NETMASK_ADDR0, TEST_NETMASK_ADDR1 , TEST_NETMASK_ADDR2, TEST_NETMASK_ADDR3);
    IP4_ADDR(&gw, TEST_GW_ADDR0, TEST_GW_ADDR1, TEST_GW_ADDR2, TEST_GW_ADDR3);
#endif

    /* add the network interface */
    netif_add(&s_netif, &ipaddr, &netmask, &gw, NULL, &r_lwip_driver_ethernetif_init, &netif_input);

    /* WAIT_LOOP */
    while (ETHER_SUCCESS != R_ETHER_CheckLink_ZC (eth_ch))
    {
        R_BSP_NOP();
    }

    /*  Registers the default network interface */
    netif_set_default(&s_netif);
    netif_set_up(&s_netif);

#if LWIP_DHCP
    /* WAIT_LOOP */
    while (!dhcp_supplied_address(&s_netif))
    {
        Ethernet_Link_Periodic_Handle();

        sys_check_timeouts();

        R_LWIP_DRIVER_Input(&s_netif);

        if(netif_is_link_up(&s_netif) && counts == 0)
        {
            counts++;
            dhcp_start(&s_netif);
        }
    }
#endif

    counts = 0;
    uint32_t delay_time = 0;

    while (1)
    {
#if TEST_CODE
        /* Reset ether test code */
        if (0 == (sys_now() % 10000))
        {
            R_LWIP_DRIVER_EthernetClose(&s_netif);
            printf("reset the Ether CH %d \n", s_netif.name[1] - '0');

            netif_remove(&s_netif);
            netif_add(&s_netif, &ipaddr, &netmask, &gw, NULL, &r_lwip_driver_ethernetif_init, &netif_input);
            netif_set_default(&s_netif);
            netif_set_up(&s_netif);
        }
#endif /* TEST_CODE */

        Ethernet_Link_Periodic_Handle();

        sys_check_timeouts();

        R_LWIP_DRIVER_Input(&s_netif);

        if (netif_is_link_up(&s_netif) && ((uint32_t)(sys_now() - delay_time) >= 500) && fin_flag)
        {
            delay_time = sys_now();
            fin_flag = false;
            counts++;
            echodemo_tcp_client_connect();
        }
    }
}
/**********************************************************************************************************************
 * End of function main
 *********************************************************************************************************************/
