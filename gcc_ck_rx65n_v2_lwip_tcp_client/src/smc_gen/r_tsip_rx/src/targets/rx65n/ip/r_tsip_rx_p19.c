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

#if TSIP_PRV_USE_ARC4 == 1
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
* Function Name: R_TSIP_GenerateArc4RandomKeyIndexSub
*******************************************************************************************************************/ /**
* @details       RX65NHU Generate key for ARC4
* @param[out]    OutData_KeyIndex
* @retval        TSIP_SUCCESS
* @retval        TSIP_ERR_RESOURCE_CONFLICT
* @note          None
*/
e_tsip_err_t R_TSIP_GenerateArc4RandomKeyIndexSub(uint32_t *OutData_KeyIndex)
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
    TSIP.REG_84H.WORD = 0x00001901u;
    TSIP.REG_108H.WORD = 0x00000000u;
    RX65NHU_func100(change_endian_long(0x7e623dfdu), change_endian_long(0xe831a295u), change_endian_long(0xda90f4d4u), change_endian_long(0xf061920au));
    RX65NHU_func103();
    TSIP.REG_104H.WORD = 0x00000052u;
    TSIP.REG_C4H.WORD = 0x01000c84u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_E0H.WORD = 0x80040000u;
    TSIP.REG_00H.WORD = 0x00008213u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    RX65NHU_func100(change_endian_long(0xaff3549au), change_endian_long(0xf7a25361u), change_endian_long(0x806c6547u), change_endian_long(0xf8f9af7bu));
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_04H.WORD = 0x00000613u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[0] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[1] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[2] = TSIP.REG_100H.WORD;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[3] = TSIP.REG_100H.WORD;
    TSIP.REG_A4H.WORD = 0x200c3b0du;
    TSIP.REG_E0H.WORD = 0x81040000u;
    TSIP.REG_00H.WORD = 0x00001813u;
    /* WAIT_LOOP */
    while (0u != TSIP.REG_00H.BIT.B25)
    {
        /* waiting */
    }
    TSIP.REG_1CH.WORD = 0x00001800u;
    TSIP.REG_A4H.WORD = 0x000c0b0cu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x36cede2du);
    TSIP.REG_28H.WORD = 0x00000001u;
    TSIP.REG_28H.WORD = 0x00bf0001u;
    TSIP.REG_2CH.WORD = 0x00000012u;
    TSIP.REG_B0H.WORD = 0x00000f00u;
    TSIP.REG_A4H.WORD = 0x02e487bfu;
    for(iLoop=1; iLoop<65; iLoop=iLoop+4)
    {
        RX65NHU_func100(change_endian_long(0xd1f6a97du), change_endian_long(0x9460cd36u), change_endian_long(0x10ec7a97u), change_endian_long(0x30039b53u));
        RX65NHU_func103();
        TSIP.REG_104H.WORD = 0x00000052u;
        TSIP.REG_C4H.WORD = 0x01000c84u;
        /* WAIT_LOOP */
        while (1u != TSIP.REG_104H.BIT.B31)
        {
            /* waiting */
        }
        TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
        TSIP.REG_00H.WORD = 0x00001213u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        TSIP.REG_00H.WORD = 0x00003113u;
        /* WAIT_LOOP */
        while (0u != TSIP.REG_00H.BIT.B25)
        {
            /* waiting */
        }
        TSIP.REG_1CH.WORD = 0x00001800u;
        RX65NHU_func101(change_endian_long(0xfa1433efu), change_endian_long(0xa7117bb1u), change_endian_long(0xa01e737eu), change_endian_long(0xfe8eea16u));
    }
    RX65NHU_func100(change_endian_long(0x85710f4au), change_endian_long(0x3c0fdb29u), change_endian_long(0x001fa762u), change_endian_long(0x7a948234u));
    TSIP.REG_2CH.WORD = 0x00000022u;
    TSIP.REG_04H.WORD = 0x00000302u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[4] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[5] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[6] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[7] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[8] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[9] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[10] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[11] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[12] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[13] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[14] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[15] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[16] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[17] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[18] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[19] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[20] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[21] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[22] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[23] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[24] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[25] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[26] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[27] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[28] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[29] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[30] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[31] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[32] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[33] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[34] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[35] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[36] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[37] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[38] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[39] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[40] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[41] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[42] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[43] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[44] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[45] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[46] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[47] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[48] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[49] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[50] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[51] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[52] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[53] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[54] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[55] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[56] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[57] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[58] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[59] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[60] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[61] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[62] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[63] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[64] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[65] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[66] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[67] = TSIP.REG_100H.WORD;
    RX65NHU_func100(change_endian_long(0x5c1f13f1u), change_endian_long(0xccb1ae38u), change_endian_long(0x194865fbu), change_endian_long(0x0a7cbf4cu));
    TSIP.REG_104H.WORD = 0x00000351u;
    TSIP.REG_A4H.WORD = 0x000009cdu;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_104H.BIT.B31)
    {
        /* waiting */
    }
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000000u);
    TSIP.REG_100H.WORD = change_endian_long(0x00000010u);
    TSIP.REG_04H.WORD = 0x00000113u;
    /* WAIT_LOOP */
    while (1u != TSIP.REG_04H.BIT.B30)
    {
        /* waiting */
    }
    OutData_KeyIndex[68] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[69] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[70] = TSIP.REG_100H.WORD;
    OutData_KeyIndex[71] = TSIP.REG_100H.WORD;
    RX65NHU_func102(change_endian_long(0x20d6a46du), change_endian_long(0x6175abb1u), change_endian_long(0x5fdfd2d8u), change_endian_long(0x2127fe4eu));
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
/**********************************************************************************************************************
 End of function ./input_dir/RX65NHU/RX65NHU_p19.prc
 *********************************************************************************************************************/
#endif /* #if TSIP_PRV_USE_ARC4 == 1 */
