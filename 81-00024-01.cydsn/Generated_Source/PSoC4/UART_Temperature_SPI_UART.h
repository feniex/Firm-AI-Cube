/*******************************************************************************
* File Name: UART_Temperature_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_UART_Temperature_H)
#define CY_SCB_SPI_UART_UART_Temperature_H

#include "UART_Temperature.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define UART_Temperature_SPI_MODE                   (0u)
#define UART_Temperature_SPI_SUB_MODE               (0u)
#define UART_Temperature_SPI_CLOCK_MODE             (0u)
#define UART_Temperature_SPI_OVS_FACTOR             (16u)
#define UART_Temperature_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define UART_Temperature_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define UART_Temperature_SPI_RX_DATA_BITS_NUM       (8u)
#define UART_Temperature_SPI_TX_DATA_BITS_NUM       (8u)
#define UART_Temperature_SPI_WAKE_ENABLE            (0u)
#define UART_Temperature_SPI_BITS_ORDER             (1u)
#define UART_Temperature_SPI_TRANSFER_SEPARATION    (1u)
#define UART_Temperature_SPI_NUMBER_OF_SS_LINES     (1u)
#define UART_Temperature_SPI_RX_BUFFER_SIZE         (8u)
#define UART_Temperature_SPI_TX_BUFFER_SIZE         (8u)

#define UART_Temperature_SPI_INTERRUPT_MODE         (0u)

#define UART_Temperature_SPI_INTR_RX_MASK           (0u)
#define UART_Temperature_SPI_INTR_TX_MASK           (0u)

#define UART_Temperature_SPI_RX_TRIGGER_LEVEL       (7u)
#define UART_Temperature_SPI_TX_TRIGGER_LEVEL       (0u)

#define UART_Temperature_SPI_BYTE_MODE_ENABLE       (0u)
#define UART_Temperature_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define UART_Temperature_SPI_SS0_POLARITY           (0u)
#define UART_Temperature_SPI_SS1_POLARITY           (0u)
#define UART_Temperature_SPI_SS2_POLARITY           (0u)
#define UART_Temperature_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define UART_Temperature_UART_SUB_MODE              (0u)
#define UART_Temperature_UART_DIRECTION             (3u)
#define UART_Temperature_UART_DATA_BITS_NUM         (8u)
#define UART_Temperature_UART_PARITY_TYPE           (2u)
#define UART_Temperature_UART_STOP_BITS_NUM         (2u)
#define UART_Temperature_UART_OVS_FACTOR            (12u)
#define UART_Temperature_UART_IRDA_LOW_POWER        (0u)
#define UART_Temperature_UART_MEDIAN_FILTER_ENABLE  (0u)
#define UART_Temperature_UART_RETRY_ON_NACK         (0u)
#define UART_Temperature_UART_IRDA_POLARITY         (0u)
#define UART_Temperature_UART_DROP_ON_FRAME_ERR     (0u)
#define UART_Temperature_UART_DROP_ON_PARITY_ERR    (0u)
#define UART_Temperature_UART_WAKE_ENABLE           (0u)
#define UART_Temperature_UART_RX_BUFFER_SIZE        (8u)
#define UART_Temperature_UART_TX_BUFFER_SIZE        (8u)
#define UART_Temperature_UART_MP_MODE_ENABLE        (0u)
#define UART_Temperature_UART_MP_ACCEPT_ADDRESS     (0u)
#define UART_Temperature_UART_MP_RX_ADDRESS         (2u)
#define UART_Temperature_UART_MP_RX_ADDRESS_MASK    (255u)

#define UART_Temperature_UART_INTERRUPT_MODE        (2u)

#define UART_Temperature_UART_INTR_RX_MASK          (4u)
#define UART_Temperature_UART_INTR_TX_MASK          (0u)

#define UART_Temperature_UART_RX_TRIGGER_LEVEL      (7u)
#define UART_Temperature_UART_TX_TRIGGER_LEVEL      (0u)

#define UART_Temperature_UART_BYTE_MODE_ENABLE      (0u)
#define UART_Temperature_UART_CTS_ENABLE            (0u)
#define UART_Temperature_UART_CTS_POLARITY          (0u)
#define UART_Temperature_UART_RTS_ENABLE            (0u)
#define UART_Temperature_UART_RTS_POLARITY          (0u)
#define UART_Temperature_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define UART_Temperature_SPI_SLAVE  (0u)
#define UART_Temperature_SPI_MASTER (1u)

/* UART direction enum */
#define UART_Temperature_UART_RX    (1u)
#define UART_Temperature_UART_TX    (2u)
#define UART_Temperature_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define UART_Temperature_SPI_SLAVE_CONST        (1u)
    #define UART_Temperature_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define UART_Temperature_RX_DIRECTION           (1u)
    #define UART_Temperature_TX_DIRECTION           (1u)
    #define UART_Temperature_UART_RX_DIRECTION      (1u)
    #define UART_Temperature_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define UART_Temperature_INTERNAL_RX_SW_BUFFER   (0u)
    #define UART_Temperature_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define UART_Temperature_INTERNAL_RX_BUFFER_SIZE    (UART_Temperature_rxBufferSize + 1u)
    #define UART_Temperature_RX_BUFFER_SIZE             (UART_Temperature_rxBufferSize)
    #define UART_Temperature_TX_BUFFER_SIZE             (UART_Temperature_txBufferSize)

    /* Return true if buffer is provided */
    #define UART_Temperature_CHECK_RX_SW_BUFFER (NULL != UART_Temperature_rxBuffer)
    #define UART_Temperature_CHECK_TX_SW_BUFFER (NULL != UART_Temperature_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define UART_Temperature_SPI_WAKE_ENABLE_CONST  (1u)
    #define UART_Temperature_CHECK_SPI_WAKE_ENABLE  (0u != UART_Temperature_scbEnableWake)
    #define UART_Temperature_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
        #define UART_Temperature_SPI_UART_FIFO_SIZE             (UART_Temperature_FIFO_SIZE)
        #define UART_Temperature_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define UART_Temperature_SPI_UART_FIFO_SIZE (UART_Temperature_GET_FIFO_SIZE(UART_Temperature_CTRL_REG & \
                                                                                    UART_Temperature_CTRL_BYTE_MODE))

        #define UART_Temperature_CHECK_UART_RTS_CONTROL_FLOW \
                    ((UART_Temperature_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != UART_Temperature_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UART_Temperature_UART_FLOW_CTRL_REG)))
    #endif /* (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (UART_Temperature_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define UART_Temperature_SPI_RX_DIRECTION (1u)
        #define UART_Temperature_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
            #define UART_Temperature_SPI_UART_FIFO_SIZE    (UART_Temperature_FIFO_SIZE)
        #else
            #define UART_Temperature_SPI_UART_FIFO_SIZE \
                                           UART_Temperature_GET_FIFO_SIZE(UART_Temperature_SPI_BYTE_MODE_ENABLE)

        #endif /* (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define UART_Temperature_INTERNAL_SPI_RX_SW_BUFFER  (UART_Temperature_SPI_RX_BUFFER_SIZE > \
                                                                UART_Temperature_SPI_UART_FIFO_SIZE)
        #define UART_Temperature_INTERNAL_SPI_TX_SW_BUFFER  (UART_Temperature_SPI_TX_BUFFER_SIZE > \
                                                                UART_Temperature_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define UART_Temperature_INTERNAL_RX_SW_BUFFER  (UART_Temperature_INTERNAL_SPI_RX_SW_BUFFER)
        #define UART_Temperature_INTERNAL_TX_SW_BUFFER  (UART_Temperature_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define UART_Temperature_INTERNAL_RX_BUFFER_SIZE    (UART_Temperature_SPI_RX_BUFFER_SIZE + 1u)
        #define UART_Temperature_RX_BUFFER_SIZE             (UART_Temperature_SPI_RX_BUFFER_SIZE)
        #define UART_Temperature_TX_BUFFER_SIZE             (UART_Temperature_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UART_Temperature_SPI_WAKE_ENABLE_CONST  (0u != UART_Temperature_SPI_WAKE_ENABLE)
        #define UART_Temperature_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define UART_Temperature_UART_RX_DIRECTION (0u != (UART_Temperature_UART_DIRECTION & UART_Temperature_UART_RX))
        #define UART_Temperature_UART_TX_DIRECTION (0u != (UART_Temperature_UART_DIRECTION & UART_Temperature_UART_TX))

        /* Get FIFO size */
        #if (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
            #define UART_Temperature_SPI_UART_FIFO_SIZE    (UART_Temperature_FIFO_SIZE)
        #else
            #define UART_Temperature_SPI_UART_FIFO_SIZE \
                                           UART_Temperature_GET_FIFO_SIZE(UART_Temperature_UART_BYTE_MODE_ENABLE)
        #endif /* (UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define UART_Temperature_INTERNAL_UART_RX_SW_BUFFER  (UART_Temperature_UART_RX_BUFFER_SIZE > \
                                                                UART_Temperature_SPI_UART_FIFO_SIZE)
        #define UART_Temperature_INTERNAL_UART_TX_SW_BUFFER  (UART_Temperature_UART_TX_BUFFER_SIZE > \
                                                                    UART_Temperature_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define UART_Temperature_INTERNAL_RX_SW_BUFFER  (UART_Temperature_INTERNAL_UART_RX_SW_BUFFER)
        #define UART_Temperature_INTERNAL_TX_SW_BUFFER  (UART_Temperature_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define UART_Temperature_INTERNAL_RX_BUFFER_SIZE    (UART_Temperature_UART_RX_BUFFER_SIZE + 1u)
        #define UART_Temperature_RX_BUFFER_SIZE             (UART_Temperature_UART_RX_BUFFER_SIZE)
        #define UART_Temperature_TX_BUFFER_SIZE             (UART_Temperature_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define UART_Temperature_SPI_WAKE_ENABLE_CONST  (0u)
        #define UART_Temperature_UART_WAKE_ENABLE_CONST (0u != UART_Temperature_UART_WAKE_ENABLE)

    #endif /* (UART_Temperature_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define UART_Temperature_SPI_SLAVE_CONST    (UART_Temperature_SPI_MODE == UART_Temperature_SPI_SLAVE)
    #define UART_Temperature_SPI_MASTER_CONST   (UART_Temperature_SPI_MODE == UART_Temperature_SPI_MASTER)

    /* Direction */
    #define UART_Temperature_RX_DIRECTION ((UART_Temperature_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UART_Temperature_SPI_RX_DIRECTION) : (UART_Temperature_UART_RX_DIRECTION))

    #define UART_Temperature_TX_DIRECTION ((UART_Temperature_SCB_MODE_SPI_CONST_CFG) ? \
                                            (UART_Temperature_SPI_TX_DIRECTION) : (UART_Temperature_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define UART_Temperature_CHECK_RX_SW_BUFFER (UART_Temperature_INTERNAL_RX_SW_BUFFER)
    #define UART_Temperature_CHECK_TX_SW_BUFFER (UART_Temperature_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST    (UART_Temperature_INTERNAL_RX_SW_BUFFER)
    #define UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST    (UART_Temperature_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define UART_Temperature_CHECK_SPI_WAKE_ENABLE  (UART_Temperature_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define UART_Temperature_CHECK_UART_RTS_CONTROL_FLOW    (UART_Temperature_SCB_MODE_UART_CONST_CFG && \
                                                             UART_Temperature_UART_RTS_ENABLE)

#endif /* End (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* UART_Temperature_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} UART_Temperature_SPI_INIT_STRUCT;

/* UART_Temperature_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} UART_Temperature_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)
    void UART_Temperature_SpiInit(const UART_Temperature_SPI_INIT_STRUCT *config);
#endif /* (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(UART_Temperature_SCB_MODE_SPI_INC)
    #define UART_Temperature_SpiIsBusBusy() ((uint32) (0u != (UART_Temperature_SPI_STATUS_REG & \
                                                              UART_Temperature_SPI_STATUS_BUS_BUSY)))

    #if (UART_Temperature_SPI_MASTER_CONST)
        void UART_Temperature_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(UART_Temperature_SPI_MASTER_CONST) */

    #if !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
        void UART_Temperature_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */
#endif /* (UART_Temperature_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)
    void UART_Temperature_UartInit(const UART_Temperature_UART_INIT_STRUCT *config);
#endif /* (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(UART_Temperature_SCB_MODE_UART_INC)
    void UART_Temperature_UartSetRxAddress(uint32 address);
    void UART_Temperature_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(UART_Temperature_UART_RX_DIRECTION)
        uint32 UART_Temperature_UartGetChar(void);
        uint32 UART_Temperature_UartGetByte(void);

        #if !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UART_Temperature_UartSetRtsPolarity(uint32 polarity);
            void UART_Temperature_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */
    #endif /* (UART_Temperature_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(UART_Temperature_UART_TX_DIRECTION)
        #define UART_Temperature_UartPutChar(ch)    UART_Temperature_SpiUartWriteTxData((uint32)(ch))
        void UART_Temperature_UartPutString(const char8 string[]);
        void UART_Temperature_UartPutCRLF(uint32 txDataByte);

        #if !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void UART_Temperature_UartEnableCts(void);
            void UART_Temperature_UartDisableCts(void);
            void UART_Temperature_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(UART_Temperature_CY_SCBIP_V0 || UART_Temperature_CY_SCBIP_V1) */
    #endif /* (UART_Temperature_UART_TX_DIRECTION) */
#endif /* (UART_Temperature_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(UART_Temperature_RX_DIRECTION)
    uint32 UART_Temperature_SpiUartReadRxData(void);
    uint32 UART_Temperature_SpiUartGetRxBufferSize(void);
    void   UART_Temperature_SpiUartClearRxBuffer(void);
#endif /* (UART_Temperature_RX_DIRECTION) */

/* Common APIs TX direction */
#if(UART_Temperature_TX_DIRECTION)
    void   UART_Temperature_SpiUartWriteTxData(uint32 txData);
    void   UART_Temperature_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 UART_Temperature_SpiUartGetTxBufferSize(void);
    void   UART_Temperature_SpiUartClearTxBuffer(void);
#endif /* (UART_Temperature_TX_DIRECTION) */

CY_ISR_PROTO(UART_Temperature_SPI_UART_ISR);

#if(UART_Temperature_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(UART_Temperature_UART_WAKEUP_ISR);
#endif /* (UART_Temperature_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   UART_Temperature_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 UART_Temperature_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   UART_Temperature_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 UART_Temperature_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST)
        #define UART_Temperature_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    UART_Temperature_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define UART_Temperature_GetWordFromRxBuffer(idx) UART_Temperature_rxBufferInternal[(idx)]

    #endif /* (UART_Temperature_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST)
        #define UART_Temperature_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        UART_Temperature_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define UART_Temperature_GetWordFromTxBuffer(idx) UART_Temperature_txBufferInternal[(idx)]

    #endif /* (UART_Temperature_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (UART_Temperature_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define UART_Temperature_SPI_MODE_MOTOROLA      (0x00u)
#define UART_Temperature_SPI_MODE_TI_COINCIDES  (0x01u)
#define UART_Temperature_SPI_MODE_TI_PRECEDES   (0x11u)
#define UART_Temperature_SPI_MODE_NATIONAL      (0x02u)
#define UART_Temperature_SPI_MODE_MASK          (0x03u)
#define UART_Temperature_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define UART_Temperature_SPI_MODE_NS_MICROWIRE  (UART_Temperature_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define UART_Temperature_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define UART_Temperature_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define UART_Temperature_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define UART_Temperature_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define UART_Temperature_BITS_ORDER_LSB_FIRST   (0u)
#define UART_Temperature_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define UART_Temperature_SPI_TRANSFER_SEPARATED     (0u)
#define UART_Temperature_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define UART_Temperature_SPI_SLAVE_SELECT0    (UART_Temperature_SCB__SS0_POSISTION)
#define UART_Temperature_SPI_SLAVE_SELECT1    (UART_Temperature_SCB__SS1_POSISTION)
#define UART_Temperature_SPI_SLAVE_SELECT2    (UART_Temperature_SCB__SS2_POSISTION)
#define UART_Temperature_SPI_SLAVE_SELECT3    (UART_Temperature_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define UART_Temperature_SPI_SS_ACTIVE_LOW  (0u)
#define UART_Temperature_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define UART_Temperature_UART_MODE_STD          (0u)
#define UART_Temperature_UART_MODE_SMARTCARD    (1u)
#define UART_Temperature_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define UART_Temperature_UART_RX    (1u)
#define UART_Temperature_UART_TX    (2u)
#define UART_Temperature_UART_TX_RX (3u)

/* UART parity enum */
#define UART_Temperature_UART_PARITY_EVEN   (0u)
#define UART_Temperature_UART_PARITY_ODD    (1u)
#define UART_Temperature_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define UART_Temperature_UART_STOP_BITS_1   (2u)
#define UART_Temperature_UART_STOP_BITS_1_5 (3u)
#define UART_Temperature_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define UART_Temperature_UART_IRDA_LP_OVS16     (16u)
#define UART_Temperature_UART_IRDA_LP_OVS32     (32u)
#define UART_Temperature_UART_IRDA_LP_OVS48     (48u)
#define UART_Temperature_UART_IRDA_LP_OVS96     (96u)
#define UART_Temperature_UART_IRDA_LP_OVS192    (192u)
#define UART_Temperature_UART_IRDA_LP_OVS768    (768u)
#define UART_Temperature_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define UART_Temperature_UART_MP_MARK       (0x100u)
#define UART_Temperature_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define UART_Temperature_UART_CTS_ACTIVE_LOW    (0u)
#define UART_Temperature_UART_CTS_ACTIVE_HIGH   (1u)
#define UART_Temperature_UART_RTS_ACTIVE_LOW    (0u)
#define UART_Temperature_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define UART_Temperature_INTR_RX_ERR        (UART_Temperature_INTR_RX_OVERFLOW    | \
                                             UART_Temperature_INTR_RX_UNDERFLOW   | \
                                             UART_Temperature_INTR_RX_FRAME_ERROR | \
                                             UART_Temperature_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for UART_Temperature_UartGetByte() */
#define UART_Temperature_UART_RX_OVERFLOW       (UART_Temperature_INTR_RX_OVERFLOW << 8u)
#define UART_Temperature_UART_RX_UNDERFLOW      (UART_Temperature_INTR_RX_UNDERFLOW << 8u)
#define UART_Temperature_UART_RX_FRAME_ERROR    (UART_Temperature_INTR_RX_FRAME_ERROR << 8u)
#define UART_Temperature_UART_RX_PARITY_ERROR   (UART_Temperature_INTR_RX_PARITY_ERROR << 8u)
#define UART_Temperature_UART_RX_ERROR_MASK     (UART_Temperature_UART_RX_OVERFLOW    | \
                                                 UART_Temperature_UART_RX_UNDERFLOW   | \
                                                 UART_Temperature_UART_RX_FRAME_ERROR | \
                                                 UART_Temperature_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const UART_Temperature_SPI_INIT_STRUCT  UART_Temperature_configSpi;
    extern const UART_Temperature_UART_INIT_STRUCT UART_Temperature_configUart;
#endif /* (UART_Temperature_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define UART_Temperature_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & UART_Temperature_INTR_SLAVE_SPI_BUS_ERROR)
#define UART_Temperature_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & UART_Temperature_INTR_MASTER_SPI_DONE)
#define UART_Temperature_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UART_Temperature_INTR_SLAVE_SPI_BUS_ERROR)

#define UART_Temperature_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~UART_Temperature_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define UART_Temperature_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((UART_Temperature_UART_IRDA_LP_OVS16   == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS16 : \
         ((UART_Temperature_UART_IRDA_LP_OVS32   == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS32 : \
          ((UART_Temperature_UART_IRDA_LP_OVS48   == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS48 : \
           ((UART_Temperature_UART_IRDA_LP_OVS96   == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS96 : \
            ((UART_Temperature_UART_IRDA_LP_OVS192  == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS192 : \
             ((UART_Temperature_UART_IRDA_LP_OVS768  == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS768 : \
              ((UART_Temperature_UART_IRDA_LP_OVS1536 == (oversample)) ? UART_Temperature_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          UART_Temperature_CTRL_OVS_IRDA_LP_OVS16)))))))

#define UART_Temperature_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (UART_Temperature_UART_RX & (direction))) ? \
                                                                     (UART_Temperature_RX_CTRL_ENABLED) : (0u))

#define UART_Temperature_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (UART_Temperature_UART_TX & (direction))) ? \
                                                                     (UART_Temperature_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define UART_Temperature_CTRL_SPI      (UART_Temperature_CTRL_MODE_SPI)
#define UART_Temperature_SPI_RX_CTRL   (UART_Temperature_RX_CTRL_ENABLED)
#define UART_Temperature_SPI_TX_CTRL   (UART_Temperature_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define UART_Temperature_SPI_SS_POLARITY \
             (((uint32) UART_Temperature_SPI_SS0_POLARITY << UART_Temperature_SPI_SLAVE_SELECT0) | \
              ((uint32) UART_Temperature_SPI_SS1_POLARITY << UART_Temperature_SPI_SLAVE_SELECT1) | \
              ((uint32) UART_Temperature_SPI_SS2_POLARITY << UART_Temperature_SPI_SLAVE_SELECT2) | \
              ((uint32) UART_Temperature_SPI_SS3_POLARITY << UART_Temperature_SPI_SLAVE_SELECT3))

#if(UART_Temperature_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define UART_Temperature_SPI_DEFAULT_CTRL \
                    (UART_Temperature_GET_CTRL_OVS(UART_Temperature_SPI_OVS_FACTOR) | \
                     UART_Temperature_GET_CTRL_BYTE_MODE (UART_Temperature_SPI_BYTE_MODE_ENABLE) | \
                     UART_Temperature_GET_CTRL_EC_AM_MODE(UART_Temperature_SPI_WAKE_ENABLE)      | \
                     UART_Temperature_CTRL_SPI)

    #define UART_Temperature_SPI_DEFAULT_SPI_CTRL \
                    (UART_Temperature_GET_SPI_CTRL_CONTINUOUS    (UART_Temperature_SPI_TRANSFER_SEPARATION)       | \
                     UART_Temperature_GET_SPI_CTRL_SELECT_PRECEDE(UART_Temperature_SPI_SUB_MODE &                   \
                                                                  UART_Temperature_SPI_MODE_TI_PRECEDES_MASK)     | \
                     UART_Temperature_GET_SPI_CTRL_SCLK_MODE     (UART_Temperature_SPI_CLOCK_MODE)                | \
                     UART_Temperature_GET_SPI_CTRL_LATE_MISO_SAMPLE(UART_Temperature_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     UART_Temperature_GET_SPI_CTRL_SCLK_CONTINUOUS(UART_Temperature_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     UART_Temperature_GET_SPI_CTRL_SSEL_POLARITY (UART_Temperature_SPI_SS_POLARITY)               | \
                     UART_Temperature_GET_SPI_CTRL_SUB_MODE      (UART_Temperature_SPI_SUB_MODE)                  | \
                     UART_Temperature_GET_SPI_CTRL_MASTER_MODE   (UART_Temperature_SPI_MODE))

    /* RX direction */
    #define UART_Temperature_SPI_DEFAULT_RX_CTRL \
                    (UART_Temperature_GET_RX_CTRL_DATA_WIDTH(UART_Temperature_SPI_RX_DATA_BITS_NUM)     | \
                     UART_Temperature_GET_RX_CTRL_BIT_ORDER (UART_Temperature_SPI_BITS_ORDER)           | \
                     UART_Temperature_GET_RX_CTRL_MEDIAN    (UART_Temperature_SPI_MEDIAN_FILTER_ENABLE) | \
                     UART_Temperature_SPI_RX_CTRL)

    #define UART_Temperature_SPI_DEFAULT_RX_FIFO_CTRL \
                    UART_Temperature_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UART_Temperature_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define UART_Temperature_SPI_DEFAULT_TX_CTRL \
                    (UART_Temperature_GET_TX_CTRL_DATA_WIDTH(UART_Temperature_SPI_TX_DATA_BITS_NUM) | \
                     UART_Temperature_GET_TX_CTRL_BIT_ORDER (UART_Temperature_SPI_BITS_ORDER)       | \
                     UART_Temperature_SPI_TX_CTRL)

    #define UART_Temperature_SPI_DEFAULT_TX_FIFO_CTRL \
                    UART_Temperature_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UART_Temperature_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define UART_Temperature_SPI_DEFAULT_INTR_SPI_EC_MASK   (UART_Temperature_NO_INTR_SOURCES)

    #define UART_Temperature_SPI_DEFAULT_INTR_I2C_EC_MASK   (UART_Temperature_NO_INTR_SOURCES)
    #define UART_Temperature_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (UART_Temperature_SPI_INTR_RX_MASK & UART_Temperature_INTR_SLAVE_SPI_BUS_ERROR)

    #define UART_Temperature_SPI_DEFAULT_INTR_MASTER_MASK \
                    (UART_Temperature_SPI_INTR_TX_MASK & UART_Temperature_INTR_MASTER_SPI_DONE)

    #define UART_Temperature_SPI_DEFAULT_INTR_RX_MASK \
                    (UART_Temperature_SPI_INTR_RX_MASK & (uint32) ~UART_Temperature_INTR_SLAVE_SPI_BUS_ERROR)

    #define UART_Temperature_SPI_DEFAULT_INTR_TX_MASK \
                    (UART_Temperature_SPI_INTR_TX_MASK & (uint32) ~UART_Temperature_INTR_MASTER_SPI_DONE)

#endif /* (UART_Temperature_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define UART_Temperature_CTRL_UART      (UART_Temperature_CTRL_MODE_UART)
#define UART_Temperature_UART_RX_CTRL   (UART_Temperature_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define UART_Temperature_UART_TX_CTRL   (UART_Temperature_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(UART_Temperature_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(UART_Temperature_UART_MODE_IRDA == UART_Temperature_UART_SUB_MODE)

        #define UART_Temperature_DEFAULT_CTRL_OVS   ((0u != UART_Temperature_UART_IRDA_LOW_POWER) ?              \
                                (UART_Temperature_UART_GET_CTRL_OVS_IRDA_LP(UART_Temperature_UART_OVS_FACTOR)) : \
                                (UART_Temperature_CTRL_OVS_IRDA_OVS16))

    #else

        #define UART_Temperature_DEFAULT_CTRL_OVS   UART_Temperature_GET_CTRL_OVS(UART_Temperature_UART_OVS_FACTOR)

    #endif /* (UART_Temperature_UART_MODE_IRDA == UART_Temperature_UART_SUB_MODE) */

    #define UART_Temperature_UART_DEFAULT_CTRL \
                                (UART_Temperature_GET_CTRL_BYTE_MODE  (UART_Temperature_UART_BYTE_MODE_ENABLE)  | \
                                 UART_Temperature_GET_CTRL_ADDR_ACCEPT(UART_Temperature_UART_MP_ACCEPT_ADDRESS) | \
                                 UART_Temperature_DEFAULT_CTRL_OVS                                              | \
                                 UART_Temperature_CTRL_UART)

    #define UART_Temperature_UART_DEFAULT_UART_CTRL \
                                    (UART_Temperature_GET_UART_CTRL_MODE(UART_Temperature_UART_SUB_MODE))

    /* RX direction */
    #define UART_Temperature_UART_DEFAULT_RX_CTRL_PARITY \
                                ((UART_Temperature_UART_PARITY_NONE != UART_Temperature_UART_PARITY_TYPE) ?      \
                                  (UART_Temperature_GET_UART_RX_CTRL_PARITY(UART_Temperature_UART_PARITY_TYPE) | \
                                   UART_Temperature_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define UART_Temperature_UART_DEFAULT_UART_RX_CTRL \
                    (UART_Temperature_GET_UART_RX_CTRL_MODE(UART_Temperature_UART_STOP_BITS_NUM)                    | \
                     UART_Temperature_GET_UART_RX_CTRL_POLARITY(UART_Temperature_UART_IRDA_POLARITY)                | \
                     UART_Temperature_GET_UART_RX_CTRL_MP_MODE(UART_Temperature_UART_MP_MODE_ENABLE)                | \
                     UART_Temperature_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(UART_Temperature_UART_DROP_ON_PARITY_ERR) | \
                     UART_Temperature_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(UART_Temperature_UART_DROP_ON_FRAME_ERR)   | \
                     UART_Temperature_UART_DEFAULT_RX_CTRL_PARITY)

    #define UART_Temperature_UART_DEFAULT_RX_CTRL \
                                (UART_Temperature_GET_RX_CTRL_DATA_WIDTH(UART_Temperature_UART_DATA_BITS_NUM)        | \
                                 UART_Temperature_GET_RX_CTRL_MEDIAN    (UART_Temperature_UART_MEDIAN_FILTER_ENABLE) | \
                                 UART_Temperature_GET_UART_RX_CTRL_ENABLED(UART_Temperature_UART_DIRECTION))

    #define UART_Temperature_UART_DEFAULT_RX_FIFO_CTRL \
                                UART_Temperature_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(UART_Temperature_UART_RX_TRIGGER_LEVEL)

    #define UART_Temperature_UART_DEFAULT_RX_MATCH_REG  ((0u != UART_Temperature_UART_MP_MODE_ENABLE) ?          \
                                (UART_Temperature_GET_RX_MATCH_ADDR(UART_Temperature_UART_MP_RX_ADDRESS) | \
                                 UART_Temperature_GET_RX_MATCH_MASK(UART_Temperature_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define UART_Temperature_UART_DEFAULT_TX_CTRL_PARITY (UART_Temperature_UART_DEFAULT_RX_CTRL_PARITY)

    #define UART_Temperature_UART_DEFAULT_UART_TX_CTRL \
                                (UART_Temperature_GET_UART_TX_CTRL_MODE(UART_Temperature_UART_STOP_BITS_NUM)       | \
                                 UART_Temperature_GET_UART_TX_CTRL_RETRY_NACK(UART_Temperature_UART_RETRY_ON_NACK) | \
                                 UART_Temperature_UART_DEFAULT_TX_CTRL_PARITY)

    #define UART_Temperature_UART_DEFAULT_TX_CTRL \
                                (UART_Temperature_GET_TX_CTRL_DATA_WIDTH(UART_Temperature_UART_DATA_BITS_NUM) | \
                                 UART_Temperature_GET_UART_TX_CTRL_ENABLED(UART_Temperature_UART_DIRECTION))

    #define UART_Temperature_UART_DEFAULT_TX_FIFO_CTRL \
                                UART_Temperature_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(UART_Temperature_UART_TX_TRIGGER_LEVEL)

    #define UART_Temperature_UART_DEFAULT_FLOW_CTRL \
                        (UART_Temperature_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(UART_Temperature_UART_RTS_FIFO_LEVEL) | \
                         UART_Temperature_GET_UART_FLOW_CTRL_RTS_POLARITY (UART_Temperature_UART_RTS_POLARITY)   | \
                         UART_Temperature_GET_UART_FLOW_CTRL_CTS_POLARITY (UART_Temperature_UART_CTS_POLARITY)   | \
                         UART_Temperature_GET_UART_FLOW_CTRL_CTS_ENABLE   (UART_Temperature_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define UART_Temperature_UART_DEFAULT_INTR_I2C_EC_MASK  (UART_Temperature_NO_INTR_SOURCES)
    #define UART_Temperature_UART_DEFAULT_INTR_SPI_EC_MASK  (UART_Temperature_NO_INTR_SOURCES)
    #define UART_Temperature_UART_DEFAULT_INTR_SLAVE_MASK   (UART_Temperature_NO_INTR_SOURCES)
    #define UART_Temperature_UART_DEFAULT_INTR_MASTER_MASK  (UART_Temperature_NO_INTR_SOURCES)
    #define UART_Temperature_UART_DEFAULT_INTR_RX_MASK      (UART_Temperature_UART_INTR_RX_MASK)
    #define UART_Temperature_UART_DEFAULT_INTR_TX_MASK      (UART_Temperature_UART_INTR_TX_MASK)

#endif /* (UART_Temperature_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define UART_Temperature_SPIM_ACTIVE_SS0    (UART_Temperature_SPI_SLAVE_SELECT0)
#define UART_Temperature_SPIM_ACTIVE_SS1    (UART_Temperature_SPI_SLAVE_SELECT1)
#define UART_Temperature_SPIM_ACTIVE_SS2    (UART_Temperature_SPI_SLAVE_SELECT2)
#define UART_Temperature_SPIM_ACTIVE_SS3    (UART_Temperature_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_UART_Temperature_H */


/* [] END OF FILE */
