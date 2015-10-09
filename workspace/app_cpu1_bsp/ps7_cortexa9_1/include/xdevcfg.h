/******************************************************************************
*
* (c) Copyright 2011-12 Xilinx, Inc. All rights reserved.
*
* This file contains confidential and proprietary information of Xilinx, Inc.
* and is protected under U.S. and international copyright and other
* intellectual property laws.
*
* DISCLAIMER
* This disclaimer is not a license and does not grant any rights to the
* materials distributed herewith. Except as otherwise provided in a valid
* license issued to you by Xilinx, and to the maximum extent permitted by
* applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH ALL
* FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, EXPRESS,
* IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE;
* and (2) Xilinx shall not be liable (whether in contract or tort, including
* negligence, or under any other theory of liability) for any loss or damage
* of any kind or nature related to, arising under or in connection with these
* materials, including for any direct, or any indirect, special, incidental,
* or consequential loss or damage (including loss of data, profits, goodwill,
* or any type of loss or damage suffered as a result of any action brought by
* a third party) even if such damage or loss was reasonably foreseeable or
* Xilinx had been advised of the possibility of the same.
*
* CRITICAL APPLICATIONS
* Xilinx products are not designed or intended to be fail-safe, or for use in
* any application requiring fail-safe performance, such as life-support or
* safety devices or systems, Class III medical devices, nuclear facilities,
* applications related to the deployment of airbags, or any other applications
* that could lead to death, personal injury, or severe property or
* environmental damage (individually and collectively, "Critical
* Applications"). Customer assumes the sole risk and liability of any use of
* Xilinx products in Critical Applications, subject only to applicable laws
* and regulations governing limitations on product liability.
*
* THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE
* AT ALL TIMES.
*
******************************************************************************/
/****************************************************************************/
/**
*
* @file xdevcfg.h
*
* The is the main header file for the Device Configuration Interface of the Zynq
* device. The device configuration interface has three main functionality.
*  1. AXI-PCAP
*  2. Security Policy
*  3. XADC
* This current version of the driver supports only the AXI-PCAP and Security
* Policy blocks. There is a separate driver for XADC.
*
* AXI-PCAP is used for download/upload an encrypted or decrypted bitstream.
* DMA embedded in the AXI PCAP provides the master interface to
* the Device configuration block for any DMA transfers. The data transfer can
* take place between the Tx/RxFIFOs of AXI-PCAP and memory (on chip
* RAM/DDR/peripheral memory).
*
* The current driver only supports the downloading the FPGA bitstream and
* readback of the decrypted image (sort of loopback).
* The driver does not know what information needs to be written to the FPGA to
* readback FPGA configuration register or memory data. The application above the
* driver should take care of creating the data that needs to be downloaded to
* the FPGA so that the bitstream can be readback.
* This driver also does not support the reading of the internal registers of the
* PCAP. The driver has no knowledge of the PCAP internals.
*
* <b> Initialization and Configuration </b>
*
* The device driver enables higher layer software (e.g., an application) to
* communicate with the Device Configuration device.
*
* XDcfg_CfgInitialize() API is used to initialize the Device Configuration
* Interface. The user needs to first call the XDcfg_LookupConfig() API which
* returns the Configuration structure pointer which is passed as a parameter to
* the XDcfg_CfgInitialize() API.
*
* <b>Interrupts</b>
* The Driver implements an interrupt handler to support the interrupts provided
* by this interface.
*
* <b> Threads </b>
*
* This driver is not thread safe. Any needs for threads or thread mutual
* exclusion must be satisfied by the layer above this driver.
*
* <b> Asserts </b>
*
* Asserts are used within all Xilinx drivers to enforce constraints on argument
* values. Asserts can be turned off on a system-wide basis by defining, at
* compile time, the NDEBUG identifier. By default, asserts are turned on and it
* is recommended that users leave asserts on during development.
*
* <b> Building the driver </b>
*
* The XDcfg driver is composed of several source files. This allows the user
* to build and link only those parts of the driver that are necessary.
*
* <br><br>
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who Date     Changes
* ----- --- -------- ---------------------------------------------
* 1.00a hvm 02/07/11 First release
* 2.00a nm  05/31/12 Updated the driver for CR 660835 so that input length for
*		     source/destination to the XDcfg_InitiateDma, XDcfg_Transfer
*		     APIs is words (32 bit) and not bytes.
* 		     Updated the notes for XDcfg_InitiateDma/XDcfg_Transfer APIs
*		     to add information that 2 LSBs of the Source/Destination
*		     address when equal to 2�b01 indicate the last DMA command
*		     of an overall transfer.
*		     Destination Address passed to this API for secure transfers
*		     instead of using 0xFFFFFFFF for CR 662197. This issue was
*		     resulting in the failure of secure transfers of
*		     non-bitstream images.
* 2.01a nm  07/07/12 Updated the XDcfg_IntrClear function to directly
*		     set the mask instead of oring it with the
*		     value read from the interrupt status register
* 		     Added defines for the PS Version bits,
*	             removed the FIFO Flush bits from the
*		     Miscellaneous Control Reg.
*		     Added XDcfg_GetPsVersion, XDcfg_SelectIcapInterface
*		     and XDcfg_SelectPcapInterface APIs for CR 643295
*		     The user has to call the XDcfg_SelectIcapInterface API
*		     for the PL reconfiguration using AXI HwIcap.
*		     Updated the XDcfg_Transfer API to clear the
*		     QUARTER_PCAP_RATE_EN bit in the control register for
*		     non secure writes for CR 675543.
* </pre>
*
******************************************************************************/
#ifndef XDCFG_H		/* prevent circular inclusions */
#define XDCFG_H		/* by using protection macros */

/***************************** Include Files *********************************/

#include "xdevcfg_hw.h"
#include "xstatus.h"
#include "xil_assert.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************** Constant Definitions *****************************/

/* Types of PCAP transfers */

#define XDCFG_NON_SECURE_PCAP_WRITE		1
#define XDCFG_SECURE_PCAP_WRITE			2
#define XDCFG_PCAP_READBACK			3
#define XDCFG_CONCURRENT_SECURE_READ_WRITE	4
#define XDCFG_CONCURRENT_NONSEC_READ_WRITE	5


/**************************** Type Definitions *******************************/
/**
* The handler data type allows the user to define a callback function to
* respond to interrupt events in the system. This function is executed
* in interrupt context, so amount of processing should be minimized.
*
* @param	CallBackRef is the callback reference passed in by the upper
*		layer when setting the callback functions, and passed back to
*		the upper layer when the callback is invoked. Its type is
*		unimportant to the driver component, so it is a void pointer.
* @param	Status is the Interrupt status of the XDcfg device.
*/
typedef void (*XDcfg_IntrHandler) (void *CallBackRef, u32 Status);

/**
 * This typedef contains configuration information for the device.
 */
typedef struct {
	u16 DeviceId;		/**< Unique ID of device */
	u32 BaseAddr;		/**< Base address of the device */
} XDcfg_Config;

/**
 * The XDcfg driver instance data.
 */
typedef struct {
	XDcfg_Config Config;	/**< Hardware Configuration */
	u32 IsReady;		/**< Device is initialized and ready */
	u32 IsStarted;		/**< Device Configuration Interface
				  * is running
				  */
	XDcfg_IntrHandler StatusHandler;  /* Event handler function */
	void *CallBackRef;	/* Callback reference for event handler */
} XDcfg;

/****************************************************************************/
/**
*
* Unlock the Device Config Interface block.
*
* @param	InstancePtr is a pointer to the instance of XDcfg driver.
*
* @return	None.
*
* @note		C-style signature:
*		void XDcfg_Unlock(XDcfg* InstancePtr)
*
*****************************************************************************/
#define XDcfg_Unlock(InstancePtr)					\
	XDcfg_WriteReg((InstancePtr)->Config.BaseAddr, 			\
	XDCFG_UNLOCK_OFFSET, XDCFG_UNLOCK_DATA)



/****************************************************************************/
/**
*
* Get the version number of the PS from the Miscellaneous Control Register.
*
* @param	InstancePtr is a pointer to the instance of XDcfg driver.
*
* @return	Version of the PS.
*
* @note		C-style signature:
*		void XDcfg_GetPsVersion(XDcfg* InstancePtr)
*
*****************************************************************************/
#define XDcfg_GetPsVersion(InstancePtr)					\
	((XDcfg_ReadReg((InstancePtr)->Config.BaseAddr, 		\
			XDCFG_MCTRL_OFFSET)) & 				\
			XDCFG_MCTRL_PCAP_PS_VERSION_MASK) >> 		\
			XDCFG_MCTRL_PCAP_PS_VERSION_SHIFT



/****************************************************************************/
/**
*
* Read the multiboot config register value.
*
* @param	InstancePtr is a pointer to the instance of XDcfg driver.
*
* @return	None.
*
* @note		C-style signature:
*		u32 XDcfg_ReadMultiBootConfig(XDcfg* InstancePtr)
*
*****************************************************************************/
#define XDcfg_ReadMultiBootConfig(InstancePtr)			\
	XDcfg_ReadReg((InstancePtr)->Config.BaseAddr + 		\
			XDCFG_MULTIBOOT_ADDR_OFFSET)


/****************************************************************************/
/**
*
* Selects ICAP interface for reconfiguration after the initial configuration
* of the PL.
*
* @param	InstancePtr is a pointer to the instance of XDcfg driver.
*
* @return	None.
*
* @note		C-style signature:
*		void XDcfg_SelectIcapInterface(XDcfg* InstancePtr)
*
*****************************************************************************/
#define XDcfg_SelectIcapInterface(InstancePtr)				  \
	XDcfg_WriteReg((InstancePtr)->Config.BaseAddr, XDCFG_CTRL_OFFSET,   \
	((XDcfg_ReadReg((InstancePtr)->Config.BaseAddr, XDCFG_CTRL_OFFSET)) \
	& ( ~XDCFG_CTRL_PCAP_PR_MASK)))

/****************************************************************************/
/**
*
* Selects PCAP interface for reconfiguration after the initial configuration
* of the PL.
*
* @param	InstancePtr is a pointer to the instance of XDcfg driver.
*
* @return	None.
*
* @note		C-style signature:
*		void XDcfg_SelectPcapInterface(XDcfg* InstancePtr)
*
*****************************************************************************/
#define XDcfg_SelectPcapInterface(InstancePtr)				   \
	XDcfg_WriteReg((InstancePtr)->Config.BaseAddr, XDCFG_CTRL_OFFSET,    \
	((XDcfg_ReadReg((InstancePtr)->Config.BaseAddr, XDCFG_CTRL_OFFSET))  \
	| XDCFG_CTRL_PCAP_PR_MASK))



/************************** Function Prototypes ******************************/

/*
 * Lookup configuration in xdevcfg_sinit.c.
 */
XDcfg_Config *XDcfg_LookupConfig(u16 DeviceId);

/*
 * Selftest function in xdevcfg_selftest.c
 */
int XDcfg_SelfTest(XDcfg *InstancePtr);

/*
 * Interface functions in xdevcfg.c
 */
int XDcfg_CfgInitialize(XDcfg *InstancePtr,
			 XDcfg_Config *ConfigPtr, u32 EffectiveAddress);

void XDcfg_EnablePCAP(XDcfg *InstancePtr);

void XDcfg_DisablePCAP(XDcfg *InstancePtr);

void XDcfg_SetControlRegister(XDcfg *InstancePtr, u32 Mask);

u32 XDcfg_GetControlRegister(XDcfg *InstancePtr);

void XDcfg_SetLockRegister(XDcfg *InstancePtr, u32 Data);

u32 XDcfg_GetLockRegister(XDcfg *InstancePtr);

void XDcfg_SetConfigRegister(XDcfg *InstancePtr, u32 Data);

u32 XDcfg_GetConfigRegister(XDcfg *InstancePtr);

void XDcfg_SetStatusRegister(XDcfg *InstancePtr, u32 Data);

u32 XDcfg_GetStatusRegister(XDcfg *InstancePtr);

void XDcfg_SetRomShadowRegister(XDcfg *InstancePtr, u32 Data);

u32 XDcfg_GetSoftwareIdRegister(XDcfg *InstancePtr);

void XDcfg_SetMiscControlRegister(XDcfg *InstancePtr, u32 Mask);

u32 XDcfg_GetMiscControlRegister(XDcfg *InstancePtr);

u32 XDcfg_IsDmaBusy(XDcfg *InstancePtr);

void XDcfg_InitiateDma(XDcfg *InstancePtr, u32 SourcePtr, u32 DestPtr,
				u32 SrcWordLength, u32 DestWordLength);

u32 XDcfg_Transfer(XDcfg *InstancePtr,
				void *SourcePtr, u32 SrcWordLength,
				void *DestPtr, u32 DestWordLength,
				u32 TransferType);

/*
 * Interrupt related function prototypes implemented in xdevcfg_intr.c
 */
void XDcfg_IntrEnable(XDcfg *InstancePtr, u32 Mask);

void XDcfg_IntrDisable(XDcfg *InstancePtr, u32 Mask);

u32 XDcfg_IntrGetEnabled(XDcfg *InstancePtr);

u32 XDcfg_IntrGetStatus(XDcfg *InstancePtr);

void XDcfg_IntrClear(XDcfg *InstancePtr, u32 Mask);

void XDcfg_InterruptHandler(XDcfg *InstancePtr);

void XDcfg_SetHandler(XDcfg *InstancePtr, void *CallBackFunc,
				void *CallBackRef);

#ifdef __cplusplus
}
#endif

#endif	/* end of protection macro */
