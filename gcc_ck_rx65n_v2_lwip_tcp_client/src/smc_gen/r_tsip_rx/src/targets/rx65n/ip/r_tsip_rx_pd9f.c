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

#if TSIP_PRV_USE_TDES == 1
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
* Function Name: R_TSIP_TdesEncryptDecryptFinalSub
*******************************************************************************************************************/ /**
* @details       RX65NHU TDES Encryption/Decryption with ECB/CBC/CTR Mode Final
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_FAIL
* @note          None
*/
e_tsip_err_t R_TSIP_TdesEncryptDecryptFinalSub(void)
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
    if (0x00000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX65NHU_func101(change_endian_long(0x5fa48179u), change_endian_long(0x17580a3bu), change_endian_long(0x317e38a7u), change_endian_long(0x78385ab1u));
    }
    else if (0x01000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX65NHU_func101(change_endian_long(0x423e4c1au), change_endian_long(0x191839bau), change_endian_long(0x082df165u), change_endian_long(0xa8f07f14u));
    }
    else if (0x02000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX65NHU_func101(change_endian_long(0x842f252au), change_endian_long(0x418b94a5u), change_endian_long(0x5dc77490u), change_endian_long(0x18a6694bu));
    }
    else if (0x03000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX65NHU_func101(change_endian_long(0x3da648bfu), change_endian_long(0x29a2bc9cu), change_endian_long(0xbf8939a4u), change_endian_long(0xcfec81a5u));
    }
    else if (0x04000000u == (TSIP.REG_1CH.WORD & 0xff000000u))
    {
        RX65NHU_func101(change_endian_long(0x3ce53d77u), change_endian_long(0x4331e45cu), change_endian_long(0xaaae78e2u), change_endian_long(0x6d5907e3u));
    }
    RX65NHU_func100(change_endian_long(0x12c2fdc5u), change_endian_long(0x5f4dd82cu), change_endian_long(0x03cde2bau), change_endian_long(0x27e53524u));
    TSIP.REG_1CH.WORD = 0x00400000u;
    TSIP.REG_1D0H.WORD = 0x00000000u;
    if (1u == (TSIP.REG_1CH.BIT.B22))
    {
        RX65NHU_func102(change_endian_long(0x73e6b547u), change_endian_long(0x05ac777cu), change_endian_long(0x3d9d60c7u), change_endian_long(0x6a62006bu));
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
        RX65NHU_func102(change_endian_long(0xbc7fe533u), change_endian_long(0x04874314u), change_endian_long(0xaab539c9u), change_endian_long(0x4a423607u));
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
/**********************************************************************************************************************
 End of function ./input_dir/RX65NHU/RX65NHU_pd9f.prc
 *********************************************************************************************************************/
#endif /* #if TSIP_PRV_USE_TDES == 1 */
