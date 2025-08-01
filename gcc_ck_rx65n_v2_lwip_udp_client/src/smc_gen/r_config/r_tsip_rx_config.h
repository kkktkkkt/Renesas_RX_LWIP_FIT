/* Generated configuration header file - do not edit */
/*
 * Copyright (c) 2015 Renesas Electronics Corporation and/or its affiliates
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
/**********************************************************************************************************************
 * File Name    : r_tsip_rx_config.h
 * Version      : 1.22
 * Description  : Configuration options for the r_tsip_rx module.
 *********************************************************************************************************************/
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
 *         : 31.03.2020 1.09     Added support for AES-CCM, HMAC key generation, ECDH, Key wrap API, RX66N and RX72N
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
 Macro definitions
 *********************************************************************************************************************/

#ifndef R_TSIP_RX_CONFIG_HEADER_FILE
#define R_TSIP_RX_CONFIG_HEADER_FILE

/* For AES operation. */
#define TSIP_AES_128_ECB_ENCRYPT    (0)
#define TSIP_AES_256_ECB_ENCRYPT    (0)
#define TSIP_AES_128_ECB_DECRYPT    (0)
#define TSIP_AES_256_ECB_DECRYPT    (0)
#define TSIP_AES_128_CBC_ENCRYPT    (0)
#define TSIP_AES_256_CBC_ENCRYPT    (0)
#define TSIP_AES_128_CBC_DECRYPT    (0)
#define TSIP_AES_256_CBC_DECRYPT    (0)
#define TSIP_AES_128_CTR            (0)
#define TSIP_AES_256_CTR            (0)
#define TSIP_AES_128_GCM_ENCRYPT    (0)
#define TSIP_AES_256_GCM_ENCRYPT    (0)
#define TSIP_AES_128_GCM_DECRYPT    (0)
#define TSIP_AES_256_GCM_DECRYPT    (0)
#define TSIP_AES_128_CMAC           (0)
#define TSIP_AES_256_CMAC           (0)
#define TSIP_AES_128_CCM_ENCRYPT    (0)
#define TSIP_AES_256_CCM_ENCRYPT    (0)
#define TSIP_AES_128_CCM_DECRYPT    (0)
#define TSIP_AES_256_CCM_DECRYPT    (0)
#define TSIP_AES_128_KEY_WRAP       (0)
#define TSIP_AES_256_KEY_WRAP       (0)

/* For TDES operation. */
#define TSIP_TDES_ECB_ENCRYPT   (0)
#define TSIP_TDES_ECB_DECRYPT   (0)
#define TSIP_TDES_CBC_ENCRYPT   (0)
#define TSIP_TDES_CBC_DECRYPT   (0)

/* For ARC4 operation. */
#define TSIP_ARC4_ENCRYPT   (0)
#define TSIP_ARC4_DECRYPT   (0)

/* For HASH operation. */
#define TSIP_SHA_1      (0)
#define TSIP_SHA_256    (0)
#define TSIP_MD5        (0)

/* For HMAC operation. */
#define TSIP_SHA_1_HMAC     (0)
#define TSIP_SHA_256_HMAC   (0)

/* For RSA operation. */
#define TSIP_RSAES_1024         (0)
#define TSIP_RSAES_2048         (0)
#define TSIP_RSAES_3072         (0)
#define TSIP_RSAES_4096         (0)
#define TSIP_RSASSA_1024        (0)
#define TSIP_RSASSA_2048        (0)
#define TSIP_RSASSA_3072        (0)
#define TSIP_RSASSA_4096        (0)
    /* 5*(key_length/2) is recommended by NIST FIPS186-4, 5120 is for key_length = 2048. *2 means the margin. */
#define TSIP_RSA_RETRY_COUNT_FOR_RSA_KEY_GENERATION (5120*2)

/* For ECC operation. */
#define TSIP_ECDSA_P192            (0)
#define TSIP_ECDSA_P224            (0)
#define TSIP_ECDSA_P256            (0)
#define TSIP_ECDSA_P384            (0)
#define TSIP_ECDH_P256             (0)
#define TSIP_USER_SHA_384_ENABLED  (0)
#define TSIP_USER_SHA_384_FUNCTION (user_sha384_function)

/* For TLS. */
#define TSIP_TLS    (0)

/* Firmware update. */
#define TSIP_SECURE_BOOT        (0)
#define TSIP_FIRMWARE_UPDATE    (0)

/* For multi threading */
#define TSIP_MULTI_THREADING                    (0)
#define TSIP_MULTI_THREADING_LOCK_FUNCTION      (user_lock_function)
#define TSIP_MULTI_THREADING_UNLOCK_FUNCTION    (user_unlock_function)

/* Key update. */
#if defined BSP_MCU_RX231 || defined BSP_MCU_RX23W || defined BSP_MCU_RX26T || \
    defined BSP_MCU_RX66T || defined BSP_MCU_RX72T
#define TSIP_INSTALL_KEY_RING_INDEX (0) /* 0-15 */
#else
#define TSIP_INSTALL_KEY_RING_INDEX (1) /* 0-15 */
#endif

#endif /* R_TSIP_RX_CONFIG_HEADER_FILE */
