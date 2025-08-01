/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 27.06.2015 1.00     First Release
 *         : 15.05.2017 1.01     Add AES-CMAC
 *         : 30.09.2017 1.03     Add Init/Update/Final API and SHA, RSA
 *         : 28.02.2018 1.04     Change Init/Update/Final API for RX231, add TLS function and 
 *         :                     return values change FIT rules.
 *         : 30.04.2018 1.05     Add TDES, MD5 and RSAES-PKCS1-v1_5 API
 *         : 28.09.2018 1.06     Add RSA Key Generation, AES, TDES, RSA Key update features, RX66T support
 *         : 28.12.2018 1.07     Add RX72T support
 *         : 30.09.2019 1.08     Added support for GCC and IAR compiler, ECC API, RX23W and RX72M
 *         : 31.03.2020 1.09     Added support for AES-CCM, HMAC key generation, ECDH, Key Wrap API, RX66N and RX72N
 *         : 30.06.2020 1.10     Added support for ARC4, ECC(P-384) API
 *         : 30.09.2020 1.11     Added support for DH, ECDHE P-512r1 API, and generalization of KDF.
 *         :                     Added support for Key wrap API with TSIP-Lite.
 *         : 30.06.2021 1.12     Added support for RX23W chip version D
 *         : 31.08.2021 1.13     Added support for RX671
 *         : 22.10.2021 1.14     Added support for TLS1.3
 *         : 31.03.2022 1.15     Added support for TLS1.3(RX72M_RX72N_RX66N)
 *         : 15.09.2022 1.16     Added support for RSA 3k/4k and updated support for TLS1.3
 *         : 20.01.2023 1.17     Added support for TLS1.3 server
 *         : 24.05.2023 1.18     Added support for RX26T
 *         : 30.11.2023 1.19     Update example of Secure Bootloader / Firmware Update
 *         : 28.02.2024 1.20     Applied software workaround of AES-CCM decryption
 *         : 28.06.2024 1.21     Added support for TLS1.2 server
 *         : 10.04.2025 1.22     Added support for RSAES-OAEP, SSH
 *         :                     Updated Firmware Update API
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 *********************************************************************************************************************/
#include "../r_tsip_rx_private.h"

/**********************************************************************************************************************
 Macro definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Typedef definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Imported global variables and functions (from other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 *********************************************************************************************************************/

/**********************************************************************************************************************
 Private global variables and functions
 *********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: RX65NHU_func007
*******************************************************************************************************************/ /**
* @details       RX65NHU func007
* @note          None
*/
void RX65NHU_func007(void)
{
    int32_t iLoop = 0u, jLoop = 0u, kLoop = 0u, oLoop1 = 0u, oLoop2 = 0u, iLoop2 = 0u;
    uint32_t KEY_ADR = 0u, OFS_ADR = 0u;
    (void)iLoop;
    (void)jLoop;
    (void)kLoop;
    (void)iLoop2;
    (void)oLoop1;
    (void)oLoop2;
    (void)KEY_ADR;
    (void)OFS_ADR;
    TSIP.REG_104H.WORD = 0x00003f62u;
    TSIP.REG_D0H.WORD = 0x00000f00u;
    TSIP.REG_C4H.WORD = 0x42f087bfu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[0];
    TSIP.REG_100H.WORD = S_HEAP[1];
    TSIP.REG_100H.WORD = S_HEAP[2];
    TSIP.REG_100H.WORD = S_HEAP[3];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[4];
    TSIP.REG_100H.WORD = S_HEAP[5];
    TSIP.REG_100H.WORD = S_HEAP[6];
    TSIP.REG_100H.WORD = S_HEAP[7];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x00000094u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[8];
    TSIP.REG_100H.WORD = S_HEAP[9];
    TSIP.REG_100H.WORD = S_HEAP[10];
    TSIP.REG_100H.WORD = S_HEAP[11];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[12];
    TSIP.REG_100H.WORD = S_HEAP[13];
    TSIP.REG_100H.WORD = S_HEAP[14];
    TSIP.REG_100H.WORD = S_HEAP[15];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x00000095u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[16];
    TSIP.REG_100H.WORD = S_HEAP[17];
    TSIP.REG_100H.WORD = S_HEAP[18];
    TSIP.REG_100H.WORD = S_HEAP[19];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[20];
    TSIP.REG_100H.WORD = S_HEAP[21];
    TSIP.REG_100H.WORD = S_HEAP[22];
    TSIP.REG_100H.WORD = S_HEAP[23];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x0000009cu;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[24];
    TSIP.REG_100H.WORD = S_HEAP[25];
    TSIP.REG_100H.WORD = S_HEAP[26];
    TSIP.REG_100H.WORD = S_HEAP[27];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[28];
    TSIP.REG_100H.WORD = S_HEAP[29];
    TSIP.REG_100H.WORD = S_HEAP[30];
    TSIP.REG_100H.WORD = S_HEAP[31];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x0000009du;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[32];
    TSIP.REG_100H.WORD = S_HEAP[33];
    TSIP.REG_100H.WORD = S_HEAP[34];
    TSIP.REG_100H.WORD = S_HEAP[35];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[36];
    TSIP.REG_100H.WORD = S_HEAP[37];
    TSIP.REG_100H.WORD = S_HEAP[38];
    TSIP.REG_100H.WORD = S_HEAP[39];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x00000092u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[40];
    TSIP.REG_100H.WORD = S_HEAP[41];
    TSIP.REG_100H.WORD = S_HEAP[42];
    TSIP.REG_100H.WORD = S_HEAP[43];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[44];
    TSIP.REG_100H.WORD = S_HEAP[45];
    TSIP.REG_100H.WORD = S_HEAP[46];
    TSIP.REG_100H.WORD = S_HEAP[47];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x00000093u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[48];
    TSIP.REG_100H.WORD = S_HEAP[49];
    TSIP.REG_100H.WORD = S_HEAP[50];
    TSIP.REG_100H.WORD = S_HEAP[51];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[52];
    TSIP.REG_100H.WORD = S_HEAP[53];
    TSIP.REG_100H.WORD = S_HEAP[54];
    TSIP.REG_100H.WORD = S_HEAP[55];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x0000009au;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[56];
    TSIP.REG_100H.WORD = S_HEAP[57];
    TSIP.REG_100H.WORD = S_HEAP[58];
    TSIP.REG_100H.WORD = S_HEAP[59];
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[60];
    TSIP.REG_100H.WORD = S_HEAP[61];
    TSIP.REG_100H.WORD = S_HEAP[62];
    TSIP.REG_100H.WORD = S_HEAP[63];
    TSIP.REG_00H.WORD = 0x00003223u;
    TSIP.REG_2CH.WORD = 0x0000009bu;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_C4H.WORD = 0x400007bdu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_HEAP[64];
    TSIP.REG_100H.WORD = S_HEAP[65];
    TSIP.REG_100H.WORD = S_HEAP[66];
    TSIP.REG_100H.WORD = S_HEAP[67];
    TSIP.REG_C4H.WORD = 0x00800c45u;
    TSIP.REG_00H.WORD = 0x00002213u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
}
/**********************************************************************************************************************
 End of function ./input_dir/RX65NHU/RX65NHU_func007.prc
 *********************************************************************************************************************/
