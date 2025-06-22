/**********************************************************************************************************************
 * Copyright (c) 2025 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *********************************************************************************************************************/
/******************************************************************************
  * @Project rx65n_ck_v2_lwip_driver_tcp_client
  * @brief   tcp echoclient application using LwIP RAW API
  *****************************************************************************/

/* HOW TO USE THIS PROJECT
 * Step 1:
 *   Open the "main.h" file in this project and configure the necessary IP settings and any related parameters.
 * Step 2:
 *   Build the project and establish a debug connection to the target device.
 * Step 3:
 *   After establishing the debug connection, open the "Renesas Virtual debug Console" in e2studio.
 * Step 4:
 *   Open the "tcp_echo_server.py" file located in the Tools folder and set up the HOST IP and PORT configuration.
 * Step 5:
 *   Execute the "tcp_echo_server.py" script on the host PC.
 * Step 6:
 *   Run the project in e2studio and verify that messages are displayed in the "Renesas Virtual debug Console".
 */

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "lwip/debug.h"
#include "lwip/stats.h"
#include "lwip/tcp.h"
#include "lwip/memp.h"

#include "main.h"

#if LWIP_TCP
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint32_t message_count = 0;

u8_t data[100];

struct tcp_pcb *echoclient_pcb = NULL;
extern bool fin_flag;

/* ECHO protocol states */
enum echoclient_states
{
    ES_NOT_CONNECTED = 0,
    ES_CONNECTED,
    ES_RECEIVED,
    ES_CLOSING,
};


/* structure to be passed as argument to the tcp callbacks */
struct echoclient
{
    enum echoclient_states state; /* connection status */
    struct tcp_pcb *pcb;          /* pointer on the current tcp_pcb */
    struct pbuf *p_tx;            /* pointer on pbuf to be transmitted */
};


/* Private function prototypes -----------------------------------------------*/
static err_t echodemo_tcp_client_connected (void *arg, struct tcp_pcb *tpcb, err_t err);
static err_t echodemo_tcp_client_recv (void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err);
static void  echodemo_tcp_client_send (struct tcp_pcb *tpcb, struct echoclient * es);
static err_t echodemo_tcp_client_poll (void *arg, struct tcp_pcb *tpcb);
static err_t echodemo_tcp_client_sent (void *arg, struct tcp_pcb *tpcb, u16_t len);
static void  echodemo_tcp_client_connection_close (struct tcp_pcb *tpcb, struct echoclient * es);
static void  echodemo_tcp_client_err (void *arg, err_t err);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Connects to the TCP echo server
  * @param  None
  * @retval None
  */
void echodemo_tcp_client_connect(void)
{
    ip_addr_t DestIPaddr;

    /* create new tcp pcb */
    echoclient_pcb = tcp_new();

    if (echoclient_pcb != NULL)
    {
        IP4_ADDR( &DestIPaddr, TEST_DEST_IP_ADDR0, TEST_DEST_IP_ADDR1, TEST_DEST_IP_ADDR2, TEST_DEST_IP_ADDR3 );

        /* connect to destination address/port */
        tcp_connect(echoclient_pcb, &DestIPaddr, TEST_TCP_DEST_PORT, echodemo_tcp_client_connected);
    }
}

/**
  * @brief Function called when TCP connection established
  * @param tpcb: pointer on the connection control block
  * @param err: when connection correctly established err should be ERR_OK
  * @retval err_t: returned error
  */
static err_t echodemo_tcp_client_connected(void *arg, struct tcp_pcb *tpcb, err_t err)
{
    struct echoclient *es = NULL;

    if (err == ERR_OK)
    {
        /* allocate structure es to maintain tcp connection information */
        es = (struct echoclient *)mem_malloc(sizeof(struct echoclient));

        if (es != NULL)
        {
            es->state = ES_CONNECTED;
            es->pcb   = tpcb;

            sprintf((char*)data, "sending tcp client message %d", (int)message_count);

            /* allocate pbuf */
            es->p_tx = pbuf_alloc(PBUF_TRANSPORT, strlen((char*)data), PBUF_POOL);

            if (es->p_tx)
            {
                /* copy data to pbuf */
                pbuf_take(es->p_tx, (char*)data, strlen((char*)data));

                /* pass newly allocated es structure as argument to tpcb */
                tcp_arg(tpcb, es);

                /* initialize LwIP tcp_recv callback function */
                tcp_recv(tpcb, echodemo_tcp_client_recv);

                /* initialize LwIP tcp_sent callback function */
                tcp_sent(tpcb, echodemo_tcp_client_sent);

                /* initialize LwIP tcp_poll callback function */
                tcp_poll(tpcb, echodemo_tcp_client_poll, 1);

                /* initialize LwIP tcp_err callback function */
                tcp_err(tpcb, echodemo_tcp_client_err);

                /* send data */
                echodemo_tcp_client_send(tpcb,es);

                return ERR_OK;
            }
        }
        else
        {
            /* close connection */
            echodemo_tcp_client_connection_close(tpcb, es);

            /* return memory allocation error */
            return ERR_MEM;
        }
    }
    else
    {
        /* close connection */
        echodemo_tcp_client_connection_close(tpcb, es);
    }

    return err;
}

/**
  * @brief tcp_receiv callback
  * @param arg: argument to be passed to receive callback
  * @param tpcb: tcp connection control block
  * @param err: receive error code
  * @retval err_t: returned error
  */
static err_t echodemo_tcp_client_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err)
{
    struct echoclient *es = NULL;
    err_t ret_err;

    LWIP_ASSERT("arg != NULL",arg != NULL);

    es = (struct echoclient *)arg;

    /* if we receive an empty tcp frame from server => close connection */
    if (p == NULL)
    {
        /* remote host closed connection */
        es->state = ES_CLOSING;
        if (es->p_tx == NULL)
        {
            /* we're done sending, close connection */
            echodemo_tcp_client_connection_close(tpcb, es);
        }
        else
        {
            /* send remaining data*/
            echodemo_tcp_client_send(tpcb, es);
        }

        ret_err = ERR_OK;
    }
    /* else : a non empty frame was received from echo server but for some reason err != ERR_OK */
    else if (err != ERR_OK)
    {
        /* free received pbuf*/
        pbuf_free(p);

        ret_err = err;
    }
    else if (es->state == ES_CONNECTED)
    {
        /* increment message count */
        message_count++;

        static char str[101]="";

        if (p->len < 100)
        {
            strncpy(str,p->payload,p->len);
            str[p->len] = '\0';
            printf("Received data: %s\n",str);

            /* Get netif for checking the I/F number */
            struct netif *netif = ip_current_input_netif();

            if ('0' == netif->name[1])
            {
                fin_flag = true;
            }
        }

        /* Acknowledge data reception */
        tcp_recved(tpcb, p->tot_len);

        pbuf_free(p);
        echodemo_tcp_client_connection_close(tpcb, es);

        ret_err = ERR_OK;
    }

    /* data received when connection already closed */
    else
    {
        /* Acknowledge data reception */
        tcp_recved(tpcb, p->tot_len);

        /* free pbuf and do nothing */
        pbuf_free(p);

        ret_err = ERR_OK;
    }

    return ret_err;
}

/**
  * @brief function used to send data
  * @param  tpcb: tcp control block
  * @param  es: pointer on structure of type echoclient containing info on data
  *             to be sent
  * @retval None
  */
static void echodemo_tcp_client_send(struct tcp_pcb *tpcb, struct echoclient * es)
{
    struct pbuf *ptr   = NULL;
    err_t       wr_err = ERR_OK;

    while ((wr_err == ERR_OK) &&
           (es->p_tx != NULL) &&
           (es->p_tx->len <= tcp_sndbuf(tpcb)))
    {
        /* get pointer on pbuf from es structure */
        ptr = es->p_tx;

        /* enqueue data for transmission */
        wr_err = tcp_write(tpcb, ptr->payload, ptr->len, 1);

        if (wr_err == ERR_OK)
        {
            /* continue with next pbuf in chain (if any) */
            es->p_tx = ptr->next;

            if (es->p_tx != NULL)
            {
                /* increment reference count for es->p */
                pbuf_ref(es->p_tx);
            }

            /* free pbuf: will free pbufs up to es->p (because es->p has a reference count > 0) */
            pbuf_free(ptr);
        }
        else if (wr_err == ERR_MEM)
        {
            /* we are low on memory, try later, defer to poll */
            es->p_tx = ptr;
        }
        else
        {
            /* other problem ?? */
        }
    }
}

/**
  * @brief  This function implements the tcp_poll callback function
  * @param  arg: pointer on argument passed to callback
  * @param  tpcb: tcp connection control block
  * @retval err_t: error code
  */
static err_t echodemo_tcp_client_poll(void *arg, struct tcp_pcb *tpcb)
{
    err_t ret_err;
    struct echoclient *es = (struct echoclient *)arg;

    if (es != NULL)
    {
        if (es->p_tx != NULL)
        {
            /* there is a remaining pbuf (chain) , try to send data */
            echodemo_tcp_client_send(tpcb, es);
        }
        else
        {
            /* no remaining pbuf (chain)  */
            if (es->state == ES_CLOSING)
            {
                /* close tcp connection */
                echodemo_tcp_client_connection_close(tpcb, es);
            }
        }

        ret_err = ERR_OK;
    }
    else
    {
        /* nothing to be done */
        tcp_abort(tpcb);

        ret_err = ERR_ABRT;
    }

    return ret_err;
}

/**
  * @brief  This function is called when the TCP network error happened.
  * @param  arg: pointer on argument passed to callback
  * @param  err: error code
  * @retval err_t: returned error code
  */
static void echodemo_tcp_client_err (void *arg, err_t err)
{
    printf("called err func: %d \n",err );
    struct echoclient *es = (struct echoclient *)arg;

    switch (err)
    {
        case ERR_RST:
        case ERR_CLSD:
            echodemo_tcp_client_connection_close(es->pcb, es);
            break;
    }
}

/**
  * @brief  This function implements the tcp_sent LwIP callback (called when ACK
  *         is received from remote host for sent data)
  * @param  arg: pointer on argument passed to callback
  * @param  tcp_pcb: tcp connection control block
  * @param  len: length of data sent
  * @retval err_t: returned error code
  */
static err_t echodemo_tcp_client_sent(void *arg, struct tcp_pcb *tpcb, u16_t len)
{
    struct echoclient *es = (struct echoclient *)arg;

    LWIP_UNUSED_ARG(len);

    if (es->p_tx != NULL)
    {
        /* still got pbufs to send */
        echodemo_tcp_client_send(tpcb, es);
    }

    return ERR_OK;
}

/**
  * @brief This function is used to close the tcp connection with server
  * @param tpcb: tcp connection control block
  * @param es: pointer on echoclient structure
  * @retval None
  */
static void echodemo_tcp_client_connection_close(struct tcp_pcb *tpcb, struct echoclient * es )
{
    /* remove callbacks */
    tcp_recv(tpcb, NULL);
    tcp_sent(tpcb, NULL);
    tcp_poll(tpcb, NULL, 0);

    if (es != NULL)
    {
        mem_free(es);
    }

    /* close tcp connection */
    tcp_close(tpcb);
}

#endif /* LWIP_TCP */
