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
* Function Name: R_TSIP_Tls13GeneratePreSharedKeySub
*******************************************************************************************************************/ /**
* @details       RX65NHU TLS1.3 PreSharedKey Generation
* @param[in]     InData_Cmd
* @param[in]     InData_Handle
* @param[in]     InData_RMaster_SecretKeyIndex
* @param[in]     InData_TicketNonceLen
* @param[in]     InData_TicketNonce
* @param[out]    OutData_PreSharedKeyIndex
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_FAIL
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @retval        TSIP_ERR_KEY_SET
* @note          None
*/
e_tsip_err_t R_TSIP_Tls13GeneratePreSharedKeySub(uint32_t *InData_Cmd, uint32_t *InData_Handle, uint32_t *InData_RMaster_SecretKeyIndex, uint32_t *InData_TicketNonceLen, uint32_t *InData_TicketNonce, uint32_t *OutData_PreSharedKeyIndex)
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
    #if TSIP_MULTI_THREADING == 1
    TSIP_MULTI_THREADING_LOCK_FUNCTION();
    #endif /* TSIP_MULTI_THREADING == 1 */
    if (0x0u != (TSIP.REG_1BCH.WORD & 0x1fu))
    {
        #if TSIP_MULTI_THREADING == 1
        TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
        #endif /* TSIP_MULTI_THREADING == 1 */
        return TSIP_ERR_RESOURCE_CONFLICT;
    }
    TSIP.REG_84H.WORD = 0x0000ef01u;
    TSIP.REG_108H.WORD = 0x00000000u;
    TSIP.REG_C4H.WORD = 0x200e1a0du;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = S_RAM[16+0 + 0];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 1];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 2];
    TSIP.REG_100H.WORD = S_RAM[16+0 + 3];
    TSIP.REG_28H.WORD = 0x00870001u;
    TSIP.REG_104H.WORD = 0x00000068u;
    TSIP.REG_E0H.WORD = 0x80010200u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = InData_TicketNonceLen[0];
    TSIP.REG_ECH.WORD = 0x3420aa00u;
    TSIP.REG_ECH.WORD = 0x00000100u;
    TSIP.REG_E0H.WORD = 0x00000080u;
    TSIP.REG_1CH.WORD = 0x00A60000u;
    RX65NHU_func100(change_endian_long(0x45c033aeu), change_endian_long(0x08c5f189u), change_endian_long(0xdfff4964u), change_endian_long(0x6992360du));
    TSIP.REG_1CH.WORD = 0x00400000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (1u == (TSIP.REG_1CH.BIT.B22))
    {
        RX65NHU_func102(change_endian_long(0x64070dceu), change_endian_long(0x076d78b0u), change_endian_long(0x978321f7u), change_endian_long(0xb283c90eu));
        TSIP.REG_1BCH.WORD = 0x00000040u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_18H.BIT.B12)
        {
            /* waiting */
        }
        #if TSIP_MULTI_THREADING == 1
        TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
        #endif /* TSIP_MULTI_THREADING == 1 */
        return TSIP_ERR_FAIL;
    }
    else
    {
        TSIP.REG_104H.WORD = 0x00000068u;
        TSIP.REG_E0H.WORD = 0x80010000u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Cmd[0];
        RX65NHU_func401();
        TSIP.REG_104H.WORD = 0x00000368u;
        TSIP.REG_E0H.WORD = 0x80040280u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Handle[0];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Handle[1];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Handle[2];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_Handle[3];
        RX65NHU_func072();
        TSIP.REG_C4H.WORD = 0x400c0b0cu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = change_endian_long(0x096026d8u);
        TSIP.REG_104H.WORD = 0x00000762u;
        TSIP.REG_D0H.WORD = 0x00000100u;
        TSIP.REG_C4H.WORD = 0x02f087bfu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[0];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[1];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[2];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[3];
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[4];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[5];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[6];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[7];
        TSIP.REG_E0H.WORD = 0x80080000u;
        TSIP.REG_00H.WORD = 0x00008223u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_C4H.WORD = 0x000007bdu;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[8];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[9];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[10];
        TSIP.REG_100H.WORD = InData_RMaster_SecretKeyIndex[11];
        TSIP.REG_C4H.WORD = 0x00900c45u;
        TSIP.REG_00H.WORD = 0x00002213u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX65NHU_func100(change_endian_long(0xa6c57b21u), change_endian_long(0x789a0721u), change_endian_long(0x81100767u), change_endian_long(0x8d5a89f5u));
        TSIP.REG_1CH.WORD = 0x00400000u;
        TSIP.REG_1D0H.WORD = 0x00000000u;
        if (1u == (TSIP.REG_1CH.BIT.B22))
        {
            RX65NHU_func102(change_endian_long(0xe3594f36u), change_endian_long(0x4cfee7ccu), change_endian_long(0x3c98e055u), change_endian_long(0x1042075au));
            TSIP.REG_1BCH.WORD = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_18H.BIT.B12)
            {
                /* waiting */
            }
            #if TSIP_MULTI_THREADING == 1
            TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
            #endif /* TSIP_MULTI_THREADING == 1 */
            return TSIP_ERR_KEY_SET;
        }
        else
        {
            TSIP.REG_104H.WORD = 0x00000058u;
            TSIP.REG_E0H.WORD = 0x800103a0u;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0x000000efu);
            RX65NHU_func101(change_endian_long(0x9350e30bu), change_endian_long(0xcd8324e6u), change_endian_long(0x1e218e9bu), change_endian_long(0x1727573eu));
            RX65NHU_func073(InData_TicketNonce);
            RX65NHU_func100(change_endian_long(0x942c223fu), change_endian_long(0x284f22e3u), change_endian_long(0x915c5ec3u), change_endian_long(0x5587bba9u));
            TSIP.REG_C4H.WORD = 0x00082b8du;
            TSIP.REG_E0H.WORD = 0x81040280u;
            TSIP.REG_00H.WORD = 0x00002813u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_C4H.WORD = 0x400c0b0cu;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0x44f612dfu);
            TSIP.REG_D0H.WORD = 0x00000100u;
            TSIP.REG_C4H.WORD = 0x02e087bfu;
            TSIP.REG_00H.WORD = 0x00002523u;
            TSIP.REG_74H.WORD = 0x00000008u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_00H.BIT.B25)
            {
                /* waiting */
            }
            TSIP.REG_1CH.WORD = 0x00001800u;
            TSIP.REG_104H.WORD = 0x00000352u;
            TSIP.REG_C4H.WORD = 0x000009cdu;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_104H.BIT.B31)
            {
                /* waiting */
            }
            TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
            TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
            TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
            TSIP.REG_100H.WORD = change_endian_long(0x00000002u);
            TSIP.REG_04H.WORD = 0x00000232u;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_04H.BIT.B30)
            {
                /* waiting */
            }
            OutData_PreSharedKeyIndex[0] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[1] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[2] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[3] = TSIP.REG_100H.WORD;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_04H.BIT.B30)
            {
                /* waiting */
            }
            OutData_PreSharedKeyIndex[4] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[5] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[6] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[7] = TSIP.REG_100H.WORD;
            /* WAIT_LOOP */
            while (1u != TSIP.REG_04H.BIT.B30)
            {
                /* waiting */
            }
            OutData_PreSharedKeyIndex[8] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[9] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[10] = TSIP.REG_100H.WORD;
            OutData_PreSharedKeyIndex[11] = TSIP.REG_100H.WORD;
            RX65NHU_func102(change_endian_long(0x908b3b8bu), change_endian_long(0x32eda1ffu), change_endian_long(0xca31f7e5u), change_endian_long(0xc00168d1u));
            TSIP.REG_1BCH.WORD = 0x00000040u;
            /* WAIT_LOOP */
            while (0u != TSIP.REG_18H.BIT.B12)
            {
                /* waiting */
            }
            #if TSIP_MULTI_THREADING == 1
            TSIP_MULTI_THREADING_UNLOCK_FUNCTION();
            #endif /* TSIP_MULTI_THREADING == 1 */
            return TSIP_SUCCESS;
        }
    }
}
/**********************************************************************************************************************
 End of function ./input_dir/RX65NHU/RX65NHU_pef_r3.prc
 *********************************************************************************************************************/
