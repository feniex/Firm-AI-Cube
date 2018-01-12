/*******************************************************************************
* File Name: UART_FF_BOOT.h
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

#if !defined(CY_SCB_BOOT_UART_FF_H)
#define CY_SCB_BOOT_UART_FF_H

#include "UART_FF_PVT.h"

#if (UART_FF_SCB_MODE_I2C_INC)
    #include "UART_FF_I2C.h"
#endif /* (UART_FF_SCB_MODE_I2C_INC) */

#if (UART_FF_SCB_MODE_EZI2C_INC)
    #include "UART_FF_EZI2C.h"
#endif /* (UART_FF_SCB_MODE_EZI2C_INC) */

#if (UART_FF_SCB_MODE_SPI_INC || UART_FF_SCB_MODE_UART_INC)
    #include "UART_FF_SPI_UART.h"
#endif /* (UART_FF_SCB_MODE_SPI_INC || UART_FF_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UART_FF_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_FF) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UART_FF_SCB_MODE_I2C_INC)
    #define UART_FF_I2C_BTLDR_COMM_ENABLED     (UART_FF_BTLDR_COMM_ENABLED && \
                                                            (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_FF_I2C_SLAVE_CONST))
#else
     #define UART_FF_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UART_FF_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UART_FF_SCB_MODE_EZI2C_INC)
    #define UART_FF_EZI2C_BTLDR_COMM_ENABLED   (UART_FF_BTLDR_COMM_ENABLED && \
                                                         UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UART_FF_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_FF_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UART_FF_SCB_MODE_SPI_INC)
    #define UART_FF_SPI_BTLDR_COMM_ENABLED     (UART_FF_BTLDR_COMM_ENABLED && \
                                                            (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UART_FF_SPI_SLAVE_CONST))
#else
        #define UART_FF_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UART_FF_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UART_FF_SCB_MODE_UART_INC)
       #define UART_FF_UART_BTLDR_COMM_ENABLED    (UART_FF_BTLDR_COMM_ENABLED && \
                                                            (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UART_FF_UART_RX_DIRECTION && \
                                                              UART_FF_UART_TX_DIRECTION)))
#else
     #define UART_FF_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UART_FF_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UART_FF_BTLDR_COMM_MODE_ENABLED    (UART_FF_I2C_BTLDR_COMM_ENABLED   || \
                                                     UART_FF_SPI_BTLDR_COMM_ENABLED   || \
                                                     UART_FF_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UART_FF_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UART_FF_I2CCyBtldrCommStart(void);
    void UART_FF_I2CCyBtldrCommStop (void);
    void UART_FF_I2CCyBtldrCommReset(void);
    cystatus UART_FF_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_FF_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_FF_SCB_MODE_I2C_CONST_CFG)
        #define UART_FF_CyBtldrCommStart   UART_FF_I2CCyBtldrCommStart
        #define UART_FF_CyBtldrCommStop    UART_FF_I2CCyBtldrCommStop
        #define UART_FF_CyBtldrCommReset   UART_FF_I2CCyBtldrCommReset
        #define UART_FF_CyBtldrCommRead    UART_FF_I2CCyBtldrCommRead
        #define UART_FF_CyBtldrCommWrite   UART_FF_I2CCyBtldrCommWrite
    #endif /* (UART_FF_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UART_FF_EzI2CCyBtldrCommStart(void);
    void UART_FF_EzI2CCyBtldrCommStop (void);
    void UART_FF_EzI2CCyBtldrCommReset(void);
    cystatus UART_FF_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_FF_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UART_FF_SCB_MODE_EZI2C_CONST_CFG)
        #define UART_FF_CyBtldrCommStart   UART_FF_EzI2CCyBtldrCommStart
        #define UART_FF_CyBtldrCommStop    UART_FF_EzI2CCyBtldrCommStop
        #define UART_FF_CyBtldrCommReset   UART_FF_EzI2CCyBtldrCommReset
        #define UART_FF_CyBtldrCommRead    UART_FF_EzI2CCyBtldrCommRead
        #define UART_FF_CyBtldrCommWrite   UART_FF_EzI2CCyBtldrCommWrite
    #endif /* (UART_FF_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UART_FF_SpiCyBtldrCommStart(void);
    void UART_FF_SpiCyBtldrCommStop (void);
    void UART_FF_SpiCyBtldrCommReset(void);
    cystatus UART_FF_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_FF_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UART_FF_SCB_MODE_SPI_CONST_CFG)
        #define UART_FF_CyBtldrCommStart   UART_FF_SpiCyBtldrCommStart
        #define UART_FF_CyBtldrCommStop    UART_FF_SpiCyBtldrCommStop
        #define UART_FF_CyBtldrCommReset   UART_FF_SpiCyBtldrCommReset
        #define UART_FF_CyBtldrCommRead    UART_FF_SpiCyBtldrCommRead
        #define UART_FF_CyBtldrCommWrite   UART_FF_SpiCyBtldrCommWrite
    #endif /* (UART_FF_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UART_FF_UartCyBtldrCommStart(void);
    void UART_FF_UartCyBtldrCommStop (void);
    void UART_FF_UartCyBtldrCommReset(void);
    cystatus UART_FF_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UART_FF_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UART_FF_SCB_MODE_UART_CONST_CFG)
        #define UART_FF_CyBtldrCommStart   UART_FF_UartCyBtldrCommStart
        #define UART_FF_CyBtldrCommStop    UART_FF_UartCyBtldrCommStop
        #define UART_FF_CyBtldrCommReset   UART_FF_UartCyBtldrCommReset
        #define UART_FF_CyBtldrCommRead    UART_FF_UartCyBtldrCommRead
        #define UART_FF_CyBtldrCommWrite   UART_FF_UartCyBtldrCommWrite
    #endif /* (UART_FF_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_BTLDR_COMM_ENABLED)
    #if (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UART_FF_CyBtldrCommStart(void);
        void UART_FF_CyBtldrCommStop (void);
        void UART_FF_CyBtldrCommReset(void);
        cystatus UART_FF_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UART_FF_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UART_FF_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_FF)
        #define CyBtldrCommStart    UART_FF_CyBtldrCommStart
        #define CyBtldrCommStop     UART_FF_CyBtldrCommStop
        #define CyBtldrCommReset    UART_FF_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_FF_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_FF_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_FF) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UART_FF_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UART_FF_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UART_FF_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UART_FF_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UART_FF_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UART_FF_SPI_BYTE_TO_BYTE
    #define UART_FF_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UART_FF_UART_BYTE_TO_BYTE
    #define UART_FF_UART_BYTE_TO_BYTE  (175u)
#endif /* UART_FF_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UART_FF_H) */


/* [] END OF FILE */
