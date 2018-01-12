/*******************************************************************************
* File Name: UART_Out_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UART_Out_H)
#define CY_SCB_BOOT_UART_Out_H

#include "UART_Out_PVT.h"

#if (UART_Out_SCB_MODE_I2C_INC)
    #include "UART_Out_I2C.h"
#endif /* (UART_Out_SCB_MODE_I2C_INC) */

#if (UART_Out_SCB_MODE_EZI2C_INC)
    #include "UART_Out_EZI2C.h"
#endif /* (UART_Out_SCB_MODE_EZI2C_INC) */

#if (UART_Out_SCB_MODE_SPI_INC || UART_Out_SCB_MODE_UART_INC)
    #include "UART_Out_SPI_UART.h"
#endif /* (UART_Out_SCB_MODE_SPI_INC || UART_Out_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UART_Out_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Out) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UART_Out_SCB_MODE_I2C_INC)
    #define UART_Out_I2C_BTLDR_COMM_ENABLED     (UART_Out_BTLDR_COMM_ENABLED && \
                                                            (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_Out_I2C_SLAVE_CONST))
#else
     #define UART_Out_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_Out_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UART_Out_SCB_MODE_EZI2C_INC)
    #define UART_Out_EZI2C_BTLDR_COMM_ENABLED   (UART_Out_BTLDR_COMM_ENABLED && \
                                                         UART_Out_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UART_Out_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_Out_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UART_Out_SCB_MODE_SPI_INC)
    #define UART_Out_SPI_BTLDR_COMM_ENABLED     (UART_Out_BTLDR_COMM_ENABLED && \
                                                            (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_Out_SPI_SLAVE_CONST))
#else
        #define UART_Out_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UART_Out_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UART_Out_SCB_MODE_UART_INC)
       #define UART_Out_UART_BTLDR_COMM_ENABLED    (UART_Out_BTLDR_COMM_ENABLED && \
                                                            (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UART_Out_UART_RX_DIRECTION && \
                                                              UART_Out_UART_TX_DIRECTION)))
#else
     #define UART_Out_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_Out_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UART_Out_BTLDR_COMM_MODE_ENABLED    (UART_Out_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_Out_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_Out_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_Out_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UART_Out_I2CCyBtldrCommStart(void);
    void UART_Out_I2CCyBtldrCommStop (void);
    void UART_Out_I2CCyBtldrCommReset(void);
    cystatus UART_Out_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Out_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Out_SCB_MODE_I2C_CONST_CFG)
        #define UART_Out_CyBtldrCommStart   UART_Out_I2CCyBtldrCommStart
        #define UART_Out_CyBtldrCommStop    UART_Out_I2CCyBtldrCommStop
        #define UART_Out_CyBtldrCommReset   UART_Out_I2CCyBtldrCommReset
        #define UART_Out_CyBtldrCommRead    UART_Out_I2CCyBtldrCommRead
        #define UART_Out_CyBtldrCommWrite   UART_Out_I2CCyBtldrCommWrite
    #endif /* (UART_Out_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_Out_EzI2CCyBtldrCommStart(void);
    void UART_Out_EzI2CCyBtldrCommStop (void);
    void UART_Out_EzI2CCyBtldrCommReset(void);
    cystatus UART_Out_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Out_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Out_SCB_MODE_EZI2C_CONST_CFG)
        #define UART_Out_CyBtldrCommStart   UART_Out_EzI2CCyBtldrCommStart
        #define UART_Out_CyBtldrCommStop    UART_Out_EzI2CCyBtldrCommStop
        #define UART_Out_CyBtldrCommReset   UART_Out_EzI2CCyBtldrCommReset
        #define UART_Out_CyBtldrCommRead    UART_Out_EzI2CCyBtldrCommRead
        #define UART_Out_CyBtldrCommWrite   UART_Out_EzI2CCyBtldrCommWrite
    #endif /* (UART_Out_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_Out_SpiCyBtldrCommStart(void);
    void UART_Out_SpiCyBtldrCommStop (void);
    void UART_Out_SpiCyBtldrCommReset(void);
    cystatus UART_Out_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Out_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Out_SCB_MODE_SPI_CONST_CFG)
        #define UART_Out_CyBtldrCommStart   UART_Out_SpiCyBtldrCommStart
        #define UART_Out_CyBtldrCommStop    UART_Out_SpiCyBtldrCommStop
        #define UART_Out_CyBtldrCommReset   UART_Out_SpiCyBtldrCommReset
        #define UART_Out_CyBtldrCommRead    UART_Out_SpiCyBtldrCommRead
        #define UART_Out_CyBtldrCommWrite   UART_Out_SpiCyBtldrCommWrite
    #endif /* (UART_Out_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_Out_UartCyBtldrCommStart(void);
    void UART_Out_UartCyBtldrCommStop (void);
    void UART_Out_UartCyBtldrCommReset(void);
    cystatus UART_Out_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_Out_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UART_Out_SCB_MODE_UART_CONST_CFG)
        #define UART_Out_CyBtldrCommStart   UART_Out_UartCyBtldrCommStart
        #define UART_Out_CyBtldrCommStop    UART_Out_UartCyBtldrCommStop
        #define UART_Out_CyBtldrCommReset   UART_Out_UartCyBtldrCommReset
        #define UART_Out_CyBtldrCommRead    UART_Out_UartCyBtldrCommRead
        #define UART_Out_CyBtldrCommWrite   UART_Out_UartCyBtldrCommWrite
    #endif /* (UART_Out_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_BTLDR_COMM_ENABLED)
    #if (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UART_Out_CyBtldrCommStart(void);
        void UART_Out_CyBtldrCommStop (void);
        void UART_Out_CyBtldrCommReset(void);
        cystatus UART_Out_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_Out_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_Out_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Out)
        #define CyBtldrCommStart    UART_Out_CyBtldrCommStart
        #define CyBtldrCommStop     UART_Out_CyBtldrCommStop
        #define CyBtldrCommReset    UART_Out_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_Out_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_Out_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_Out) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_Out_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UART_Out_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UART_Out_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UART_Out_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UART_Out_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UART_Out_SPI_BYTE_TO_BYTE
    #define UART_Out_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UART_Out_UART_BYTE_TO_BYTE
    #define UART_Out_UART_BYTE_TO_BYTE  (171u)
#endif /* UART_Out_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UART_Out_H) */


/* [] END OF FILE */
