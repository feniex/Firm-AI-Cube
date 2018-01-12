/*******************************************************************************
* File Name: UART_UDB.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_UART_UDB_H)
#define CY_UART_UART_UDB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define UART_UDB_RX_ENABLED                     (1u)
#define UART_UDB_TX_ENABLED                     (1u)
#define UART_UDB_HD_ENABLED                     (0u)
#define UART_UDB_RX_INTERRUPT_ENABLED           (0u)
#define UART_UDB_TX_INTERRUPT_ENABLED           (0u)
#define UART_UDB_INTERNAL_CLOCK_USED            (1u)
#define UART_UDB_RXHW_ADDRESS_ENABLED           (0u)
#define UART_UDB_OVER_SAMPLE_COUNT              (8u)
#define UART_UDB_PARITY_TYPE                    (0u)
#define UART_UDB_PARITY_TYPE_SW                 (0u)
#define UART_UDB_BREAK_DETECT                   (0u)
#define UART_UDB_BREAK_BITS_TX                  (13u)
#define UART_UDB_BREAK_BITS_RX                  (13u)
#define UART_UDB_TXCLKGEN_DP                    (1u)
#define UART_UDB_USE23POLLING                   (1u)
#define UART_UDB_FLOW_CONTROL                   (0u)
#define UART_UDB_CLK_FREQ                       (0u)
#define UART_UDB_TX_BUFFER_SIZE                 (4u)
#define UART_UDB_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define UART_UDB_CONTROL_REG_REMOVED            (0u)
#else
    #define UART_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct UART_UDB_backupStruct_
{
    uint8 enableState;

    #if(UART_UDB_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End UART_UDB_CONTROL_REG_REMOVED */

} UART_UDB_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void UART_UDB_Start(void) ;
void UART_UDB_Stop(void) ;
uint8 UART_UDB_ReadControlRegister(void) ;
void UART_UDB_WriteControlRegister(uint8 control) ;

void UART_UDB_Init(void) ;
void UART_UDB_Enable(void) ;
void UART_UDB_SaveConfig(void) ;
void UART_UDB_RestoreConfig(void) ;
void UART_UDB_Sleep(void) ;
void UART_UDB_Wakeup(void) ;

/* Only if RX is enabled */
#if( (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) )

    #if (UART_UDB_RX_INTERRUPT_ENABLED)
        #define UART_UDB_EnableRxInt()  CyIntEnable (UART_UDB_RX_VECT_NUM)
        #define UART_UDB_DisableRxInt() CyIntDisable(UART_UDB_RX_VECT_NUM)
        CY_ISR_PROTO(UART_UDB_RXISR);
    #endif /* UART_UDB_RX_INTERRUPT_ENABLED */

    void UART_UDB_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void UART_UDB_SetRxAddress1(uint8 address) ;
    void UART_UDB_SetRxAddress2(uint8 address) ;

    void  UART_UDB_SetRxInterruptMode(uint8 intSrc) ;
    uint8 UART_UDB_ReadRxData(void) ;
    uint8 UART_UDB_ReadRxStatus(void) ;
    uint8 UART_UDB_GetChar(void) ;
    uint16 UART_UDB_GetByte(void) ;
    uint8 UART_UDB_GetRxBufferSize(void)
                                                            ;
    void UART_UDB_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define UART_UDB_GetRxInterruptSource   UART_UDB_ReadRxStatus

#endif /* End (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) */

/* Only if TX is enabled */
#if(UART_UDB_TX_ENABLED || UART_UDB_HD_ENABLED)

    #if(UART_UDB_TX_INTERRUPT_ENABLED)
        #define UART_UDB_EnableTxInt()  CyIntEnable (UART_UDB_TX_VECT_NUM)
        #define UART_UDB_DisableTxInt() CyIntDisable(UART_UDB_TX_VECT_NUM)
        #define UART_UDB_SetPendingTxInt() CyIntSetPending(UART_UDB_TX_VECT_NUM)
        #define UART_UDB_ClearPendingTxInt() CyIntClearPending(UART_UDB_TX_VECT_NUM)
        CY_ISR_PROTO(UART_UDB_TXISR);
    #endif /* UART_UDB_TX_INTERRUPT_ENABLED */

    void UART_UDB_SetTxInterruptMode(uint8 intSrc) ;
    void UART_UDB_WriteTxData(uint8 txDataByte) ;
    uint8 UART_UDB_ReadTxStatus(void) ;
    void UART_UDB_PutChar(uint8 txDataByte) ;
    void UART_UDB_PutString(const char8 string[]) ;
    void UART_UDB_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void UART_UDB_PutCRLF(uint8 txDataByte) ;
    void UART_UDB_ClearTxBuffer(void) ;
    void UART_UDB_SetTxAddressMode(uint8 addressMode) ;
    void UART_UDB_SendBreak(uint8 retMode) ;
    uint8 UART_UDB_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define UART_UDB_PutStringConst         UART_UDB_PutString
    #define UART_UDB_PutArrayConst          UART_UDB_PutArray
    #define UART_UDB_GetTxInterruptSource   UART_UDB_ReadTxStatus

#endif /* End UART_UDB_TX_ENABLED || UART_UDB_HD_ENABLED */

#if(UART_UDB_HD_ENABLED)
    void UART_UDB_LoadRxConfig(void) ;
    void UART_UDB_LoadTxConfig(void) ;
#endif /* End UART_UDB_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_UDB) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    UART_UDB_CyBtldrCommStart(void) CYSMALL ;
    void    UART_UDB_CyBtldrCommStop(void) CYSMALL ;
    void    UART_UDB_CyBtldrCommReset(void) CYSMALL ;
    cystatus UART_UDB_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus UART_UDB_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_UDB)
        #define CyBtldrCommStart    UART_UDB_CyBtldrCommStart
        #define CyBtldrCommStop     UART_UDB_CyBtldrCommStop
        #define CyBtldrCommReset    UART_UDB_CyBtldrCommReset
        #define CyBtldrCommWrite    UART_UDB_CyBtldrCommWrite
        #define CyBtldrCommRead     UART_UDB_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UART_UDB) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define UART_UDB_BYTE2BYTE_TIME_OUT (25u)
    #define UART_UDB_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define UART_UDB_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define UART_UDB_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define UART_UDB_SET_SPACE      (0x00u)
#define UART_UDB_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (UART_UDB_TX_ENABLED) || (UART_UDB_HD_ENABLED) )
    #if(UART_UDB_TX_INTERRUPT_ENABLED)
        #define UART_UDB_TX_VECT_NUM            (uint8)UART_UDB_TXInternalInterrupt__INTC_NUMBER
        #define UART_UDB_TX_PRIOR_NUM           (uint8)UART_UDB_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_UDB_TX_INTERRUPT_ENABLED */

    #define UART_UDB_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define UART_UDB_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define UART_UDB_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(UART_UDB_TX_ENABLED)
        #define UART_UDB_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (UART_UDB_HD_ENABLED) */
        #define UART_UDB_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (UART_UDB_TX_ENABLED) */

    #define UART_UDB_TX_STS_COMPLETE            (uint8)(0x01u << UART_UDB_TX_STS_COMPLETE_SHIFT)
    #define UART_UDB_TX_STS_FIFO_EMPTY          (uint8)(0x01u << UART_UDB_TX_STS_FIFO_EMPTY_SHIFT)
    #define UART_UDB_TX_STS_FIFO_FULL           (uint8)(0x01u << UART_UDB_TX_STS_FIFO_FULL_SHIFT)
    #define UART_UDB_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << UART_UDB_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (UART_UDB_TX_ENABLED) || (UART_UDB_HD_ENABLED)*/

#if( (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) )
    #if(UART_UDB_RX_INTERRUPT_ENABLED)
        #define UART_UDB_RX_VECT_NUM            (uint8)UART_UDB_RXInternalInterrupt__INTC_NUMBER
        #define UART_UDB_RX_PRIOR_NUM           (uint8)UART_UDB_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* UART_UDB_RX_INTERRUPT_ENABLED */
    #define UART_UDB_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define UART_UDB_RX_STS_BREAK_SHIFT             (0x01u)
    #define UART_UDB_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define UART_UDB_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define UART_UDB_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define UART_UDB_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define UART_UDB_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define UART_UDB_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define UART_UDB_RX_STS_MRKSPC           (uint8)(0x01u << UART_UDB_RX_STS_MRKSPC_SHIFT)
    #define UART_UDB_RX_STS_BREAK            (uint8)(0x01u << UART_UDB_RX_STS_BREAK_SHIFT)
    #define UART_UDB_RX_STS_PAR_ERROR        (uint8)(0x01u << UART_UDB_RX_STS_PAR_ERROR_SHIFT)
    #define UART_UDB_RX_STS_STOP_ERROR       (uint8)(0x01u << UART_UDB_RX_STS_STOP_ERROR_SHIFT)
    #define UART_UDB_RX_STS_OVERRUN          (uint8)(0x01u << UART_UDB_RX_STS_OVERRUN_SHIFT)
    #define UART_UDB_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << UART_UDB_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define UART_UDB_RX_STS_ADDR_MATCH       (uint8)(0x01u << UART_UDB_RX_STS_ADDR_MATCH_SHIFT)
    #define UART_UDB_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << UART_UDB_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define UART_UDB_RX_HW_MASK                     (0x7Fu)
#endif /* End (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) */

/* Control Register definitions */
#define UART_UDB_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define UART_UDB_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define UART_UDB_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define UART_UDB_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define UART_UDB_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define UART_UDB_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define UART_UDB_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define UART_UDB_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define UART_UDB_CTRL_HD_SEND               (uint8)(0x01u << UART_UDB_CTRL_HD_SEND_SHIFT)
#define UART_UDB_CTRL_HD_SEND_BREAK         (uint8)(0x01u << UART_UDB_CTRL_HD_SEND_BREAK_SHIFT)
#define UART_UDB_CTRL_MARK                  (uint8)(0x01u << UART_UDB_CTRL_MARK_SHIFT)
#define UART_UDB_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << UART_UDB_CTRL_PARITY_TYPE0_SHIFT)
#define UART_UDB_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << UART_UDB_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define UART_UDB_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define UART_UDB_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define UART_UDB_SEND_BREAK                         (0x00u)
#define UART_UDB_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define UART_UDB_REINIT                             (0x02u)
#define UART_UDB_SEND_WAIT_REINIT                   (0x03u)

#define UART_UDB_OVER_SAMPLE_8                      (8u)
#define UART_UDB_OVER_SAMPLE_16                     (16u)

#define UART_UDB_BIT_CENTER                         (UART_UDB_OVER_SAMPLE_COUNT - 2u)

#define UART_UDB_FIFO_LENGTH                        (4u)
#define UART_UDB_NUMBER_OF_START_BIT                (1u)
#define UART_UDB_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define UART_UDB_TXBITCTR_BREAKBITS8X   ((UART_UDB_BREAK_BITS_TX * UART_UDB_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define UART_UDB_TXBITCTR_BREAKBITS ((UART_UDB_BREAK_BITS_TX * UART_UDB_OVER_SAMPLE_COUNT) - 1u)

#define UART_UDB_HALF_BIT_COUNT   \
                            (((UART_UDB_OVER_SAMPLE_COUNT / 2u) + (UART_UDB_USE23POLLING * 1u)) - 2u)
#if (UART_UDB_OVER_SAMPLE_COUNT == UART_UDB_OVER_SAMPLE_8)
    #define UART_UDB_HD_TXBITCTR_INIT   (((UART_UDB_BREAK_BITS_TX + \
                            UART_UDB_NUMBER_OF_START_BIT) * UART_UDB_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define UART_UDB_RXBITCTR_INIT  ((((UART_UDB_BREAK_BITS_RX + UART_UDB_NUMBER_OF_START_BIT) \
                            * UART_UDB_OVER_SAMPLE_COUNT) + UART_UDB_HALF_BIT_COUNT) - 1u)

#else /* UART_UDB_OVER_SAMPLE_COUNT == UART_UDB_OVER_SAMPLE_16 */
    #define UART_UDB_HD_TXBITCTR_INIT   ((8u * UART_UDB_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define UART_UDB_RXBITCTR_INIT      (((7u * UART_UDB_OVER_SAMPLE_COUNT) - 1u) + \
                                                      UART_UDB_HALF_BIT_COUNT)
#endif /* End UART_UDB_OVER_SAMPLE_COUNT */

#define UART_UDB_HD_RXBITCTR_INIT                   UART_UDB_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 UART_UDB_initVar;
#if (UART_UDB_TX_INTERRUPT_ENABLED && UART_UDB_TX_ENABLED)
    extern volatile uint8 UART_UDB_txBuffer[UART_UDB_TX_BUFFER_SIZE];
    extern volatile uint8 UART_UDB_txBufferRead;
    extern uint8 UART_UDB_txBufferWrite;
#endif /* (UART_UDB_TX_INTERRUPT_ENABLED && UART_UDB_TX_ENABLED) */
#if (UART_UDB_RX_INTERRUPT_ENABLED && (UART_UDB_RX_ENABLED || UART_UDB_HD_ENABLED))
    extern uint8 UART_UDB_errorStatus;
    extern volatile uint8 UART_UDB_rxBuffer[UART_UDB_RX_BUFFER_SIZE];
    extern volatile uint8 UART_UDB_rxBufferRead;
    extern volatile uint8 UART_UDB_rxBufferWrite;
    extern volatile uint8 UART_UDB_rxBufferLoopDetect;
    extern volatile uint8 UART_UDB_rxBufferOverflow;
    #if (UART_UDB_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 UART_UDB_rxAddressMode;
        extern volatile uint8 UART_UDB_rxAddressDetected;
    #endif /* (UART_UDB_RXHW_ADDRESS_ENABLED) */
#endif /* (UART_UDB_RX_INTERRUPT_ENABLED && (UART_UDB_RX_ENABLED || UART_UDB_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define UART_UDB__B_UART__AM_SW_BYTE_BYTE 1
#define UART_UDB__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define UART_UDB__B_UART__AM_HW_BYTE_BY_BYTE 3
#define UART_UDB__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define UART_UDB__B_UART__AM_NONE 0

#define UART_UDB__B_UART__NONE_REVB 0
#define UART_UDB__B_UART__EVEN_REVB 1
#define UART_UDB__B_UART__ODD_REVB 2
#define UART_UDB__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define UART_UDB_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define UART_UDB_NUMBER_OF_STOP_BITS    (1u)

#if (UART_UDB_RXHW_ADDRESS_ENABLED)
    #define UART_UDB_RX_ADDRESS_MODE    (0u)
    #define UART_UDB_RX_HW_ADDRESS1     (0u)
    #define UART_UDB_RX_HW_ADDRESS2     (0u)
#endif /* (UART_UDB_RXHW_ADDRESS_ENABLED) */

#define UART_UDB_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << UART_UDB_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_BREAK_SHIFT) \
                                        | (0 << UART_UDB_RX_STS_OVERRUN_SHIFT))

#define UART_UDB_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << UART_UDB_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << UART_UDB_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << UART_UDB_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << UART_UDB_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_UDB_CONTROL_REG \
                            (* (reg8 *) UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define UART_UDB_CONTROL_PTR \
                            (  (reg8 *) UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_UDB_TX_ENABLED)
    #define UART_UDB_TXDATA_REG          (* (reg8 *) UART_UDB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_UDB_TXDATA_PTR          (  (reg8 *) UART_UDB_BUART_sTX_TxShifter_u0__F0_REG)
    #define UART_UDB_TXDATA_AUX_CTL_REG  (* (reg8 *) UART_UDB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_UDB_TXDATA_AUX_CTL_PTR  (  (reg8 *) UART_UDB_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define UART_UDB_TXSTATUS_REG        (* (reg8 *) UART_UDB_BUART_sTX_TxSts__STATUS_REG)
    #define UART_UDB_TXSTATUS_PTR        (  (reg8 *) UART_UDB_BUART_sTX_TxSts__STATUS_REG)
    #define UART_UDB_TXSTATUS_MASK_REG   (* (reg8 *) UART_UDB_BUART_sTX_TxSts__MASK_REG)
    #define UART_UDB_TXSTATUS_MASK_PTR   (  (reg8 *) UART_UDB_BUART_sTX_TxSts__MASK_REG)
    #define UART_UDB_TXSTATUS_ACTL_REG   (* (reg8 *) UART_UDB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define UART_UDB_TXSTATUS_ACTL_PTR   (  (reg8 *) UART_UDB_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(UART_UDB_TXCLKGEN_DP)
        #define UART_UDB_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_UDB_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define UART_UDB_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define UART_UDB_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define UART_UDB_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_UDB_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define UART_UDB_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_UDB_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define UART_UDB_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define UART_UDB_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) UART_UDB_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* UART_UDB_TXCLKGEN_DP */

#endif /* End UART_UDB_TX_ENABLED */

#if(UART_UDB_HD_ENABLED)

    #define UART_UDB_TXDATA_REG             (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_UDB_TXDATA_PTR             (  (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__F1_REG )
    #define UART_UDB_TXDATA_AUX_CTL_REG     (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define UART_UDB_TXDATA_AUX_CTL_PTR     (  (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_UDB_TXSTATUS_REG           (* (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_REG )
    #define UART_UDB_TXSTATUS_PTR           (  (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_REG )
    #define UART_UDB_TXSTATUS_MASK_REG      (* (reg8 *) UART_UDB_BUART_sRX_RxSts__MASK_REG )
    #define UART_UDB_TXSTATUS_MASK_PTR      (  (reg8 *) UART_UDB_BUART_sRX_RxSts__MASK_REG )
    #define UART_UDB_TXSTATUS_ACTL_REG      (* (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_UDB_TXSTATUS_ACTL_PTR      (  (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End UART_UDB_HD_ENABLED */

#if( (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) )
    #define UART_UDB_RXDATA_REG             (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_UDB_RXDATA_PTR             (  (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__F0_REG )
    #define UART_UDB_RXADDRESS1_REG         (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_UDB_RXADDRESS1_PTR         (  (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__D0_REG )
    #define UART_UDB_RXADDRESS2_REG         (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_UDB_RXADDRESS2_PTR         (  (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__D1_REG )
    #define UART_UDB_RXDATA_AUX_CTL_REG     (* (reg8 *) UART_UDB_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define UART_UDB_RXBITCTR_PERIOD_REG    (* (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_UDB_RXBITCTR_PERIOD_PTR    (  (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define UART_UDB_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_UDB_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define UART_UDB_RXBITCTR_COUNTER_REG   (* (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__COUNT_REG )
    #define UART_UDB_RXBITCTR_COUNTER_PTR   (  (reg8 *) UART_UDB_BUART_sRX_RxBitCounter__COUNT_REG )

    #define UART_UDB_RXSTATUS_REG           (* (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_REG )
    #define UART_UDB_RXSTATUS_PTR           (  (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_REG )
    #define UART_UDB_RXSTATUS_MASK_REG      (* (reg8 *) UART_UDB_BUART_sRX_RxSts__MASK_REG )
    #define UART_UDB_RXSTATUS_MASK_PTR      (  (reg8 *) UART_UDB_BUART_sRX_RxSts__MASK_REG )
    #define UART_UDB_RXSTATUS_ACTL_REG      (* (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define UART_UDB_RXSTATUS_ACTL_PTR      (  (reg8 *) UART_UDB_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) */

#if(UART_UDB_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define UART_UDB_INTCLOCK_CLKEN_REG     (* (reg8 *) UART_UDB_IntClock__PM_ACT_CFG)
    #define UART_UDB_INTCLOCK_CLKEN_PTR     (  (reg8 *) UART_UDB_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define UART_UDB_INTCLOCK_CLKEN_MASK    UART_UDB_IntClock__PM_ACT_MSK
#endif /* End UART_UDB_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(UART_UDB_TX_ENABLED)
    #define UART_UDB_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End UART_UDB_TX_ENABLED */

#if(UART_UDB_HD_ENABLED)
    #define UART_UDB_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End UART_UDB_HD_ENABLED */

#if( (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) )
    #define UART_UDB_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define UART_UDB_WAIT_1_MS      UART_UDB_BL_CHK_DELAY_MS   

#define UART_UDB_TXBUFFERSIZE   UART_UDB_TX_BUFFER_SIZE
#define UART_UDB_RXBUFFERSIZE   UART_UDB_RX_BUFFER_SIZE

#if (UART_UDB_RXHW_ADDRESS_ENABLED)
    #define UART_UDB_RXADDRESSMODE  UART_UDB_RX_ADDRESS_MODE
    #define UART_UDB_RXHWADDRESS1   UART_UDB_RX_HW_ADDRESS1
    #define UART_UDB_RXHWADDRESS2   UART_UDB_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define UART_UDB_RXAddressMode  UART_UDB_RXADDRESSMODE
#endif /* (UART_UDB_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define UART_UDB_initvar                    UART_UDB_initVar

#define UART_UDB_RX_Enabled                 UART_UDB_RX_ENABLED
#define UART_UDB_TX_Enabled                 UART_UDB_TX_ENABLED
#define UART_UDB_HD_Enabled                 UART_UDB_HD_ENABLED
#define UART_UDB_RX_IntInterruptEnabled     UART_UDB_RX_INTERRUPT_ENABLED
#define UART_UDB_TX_IntInterruptEnabled     UART_UDB_TX_INTERRUPT_ENABLED
#define UART_UDB_InternalClockUsed          UART_UDB_INTERNAL_CLOCK_USED
#define UART_UDB_RXHW_Address_Enabled       UART_UDB_RXHW_ADDRESS_ENABLED
#define UART_UDB_OverSampleCount            UART_UDB_OVER_SAMPLE_COUNT
#define UART_UDB_ParityType                 UART_UDB_PARITY_TYPE

#if( UART_UDB_TX_ENABLED && (UART_UDB_TXBUFFERSIZE > UART_UDB_FIFO_LENGTH))
    #define UART_UDB_TXBUFFER               UART_UDB_txBuffer
    #define UART_UDB_TXBUFFERREAD           UART_UDB_txBufferRead
    #define UART_UDB_TXBUFFERWRITE          UART_UDB_txBufferWrite
#endif /* End UART_UDB_TX_ENABLED */
#if( ( UART_UDB_RX_ENABLED || UART_UDB_HD_ENABLED ) && \
     (UART_UDB_RXBUFFERSIZE > UART_UDB_FIFO_LENGTH) )
    #define UART_UDB_RXBUFFER               UART_UDB_rxBuffer
    #define UART_UDB_RXBUFFERREAD           UART_UDB_rxBufferRead
    #define UART_UDB_RXBUFFERWRITE          UART_UDB_rxBufferWrite
    #define UART_UDB_RXBUFFERLOOPDETECT     UART_UDB_rxBufferLoopDetect
    #define UART_UDB_RXBUFFER_OVERFLOW      UART_UDB_rxBufferOverflow
#endif /* End UART_UDB_RX_ENABLED */

#ifdef UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define UART_UDB_CONTROL                UART_UDB_CONTROL_REG
#endif /* End UART_UDB_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(UART_UDB_TX_ENABLED)
    #define UART_UDB_TXDATA                 UART_UDB_TXDATA_REG
    #define UART_UDB_TXSTATUS               UART_UDB_TXSTATUS_REG
    #define UART_UDB_TXSTATUS_MASK          UART_UDB_TXSTATUS_MASK_REG
    #define UART_UDB_TXSTATUS_ACTL          UART_UDB_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(UART_UDB_TXCLKGEN_DP)
        #define UART_UDB_TXBITCLKGEN_CTR        UART_UDB_TXBITCLKGEN_CTR_REG
        #define UART_UDB_TXBITCLKTX_COMPLETE    UART_UDB_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define UART_UDB_TXBITCTR_PERIOD        UART_UDB_TXBITCTR_PERIOD_REG
        #define UART_UDB_TXBITCTR_CONTROL       UART_UDB_TXBITCTR_CONTROL_REG
        #define UART_UDB_TXBITCTR_COUNTER       UART_UDB_TXBITCTR_COUNTER_REG
    #endif /* UART_UDB_TXCLKGEN_DP */
#endif /* End UART_UDB_TX_ENABLED */

#if(UART_UDB_HD_ENABLED)
    #define UART_UDB_TXDATA                 UART_UDB_TXDATA_REG
    #define UART_UDB_TXSTATUS               UART_UDB_TXSTATUS_REG
    #define UART_UDB_TXSTATUS_MASK          UART_UDB_TXSTATUS_MASK_REG
    #define UART_UDB_TXSTATUS_ACTL          UART_UDB_TXSTATUS_ACTL_REG
#endif /* End UART_UDB_HD_ENABLED */

#if( (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) )
    #define UART_UDB_RXDATA                 UART_UDB_RXDATA_REG
    #define UART_UDB_RXADDRESS1             UART_UDB_RXADDRESS1_REG
    #define UART_UDB_RXADDRESS2             UART_UDB_RXADDRESS2_REG
    #define UART_UDB_RXBITCTR_PERIOD        UART_UDB_RXBITCTR_PERIOD_REG
    #define UART_UDB_RXBITCTR_CONTROL       UART_UDB_RXBITCTR_CONTROL_REG
    #define UART_UDB_RXBITCTR_COUNTER       UART_UDB_RXBITCTR_COUNTER_REG
    #define UART_UDB_RXSTATUS               UART_UDB_RXSTATUS_REG
    #define UART_UDB_RXSTATUS_MASK          UART_UDB_RXSTATUS_MASK_REG
    #define UART_UDB_RXSTATUS_ACTL          UART_UDB_RXSTATUS_ACTL_REG
#endif /* End  (UART_UDB_RX_ENABLED) || (UART_UDB_HD_ENABLED) */

#if(UART_UDB_INTERNAL_CLOCK_USED)
    #define UART_UDB_INTCLOCK_CLKEN         UART_UDB_INTCLOCK_CLKEN_REG
#endif /* End UART_UDB_INTERNAL_CLOCK_USED */

#define UART_UDB_WAIT_FOR_COMLETE_REINIT    UART_UDB_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_UART_UDB_H */


/* [] END OF FILE */
