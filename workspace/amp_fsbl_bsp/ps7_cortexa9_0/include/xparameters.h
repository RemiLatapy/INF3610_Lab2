
/*******************************************************************
*
* CAUTION: This file is automatically generated by libgen.
* Version: Xilinx EDK 14.4 EDK_P.49d
* DO NOT EDIT.
*
* Copyright (c) 1995-2012 Xilinx, Inc.  All rights reserved.

* 
* Description: Driver parameters
*
*******************************************************************/

#include "xparameters_ps.h"

#define STDIN_BASEADDRESS 0xE0001000
#define STDOUT_BASEADDRESS 0xE0001000

/******************************************************************/

#define XPAR_INTC_MAX_NUM_INTR_INPUTS 4
#define XPAR_XINTC_HAS_IPR 1
#define XPAR_XINTC_HAS_SIE 1
#define XPAR_XINTC_HAS_CIE 1
#define XPAR_XINTC_HAS_IVR 1
#define XPAR_XINTC_USE_DCR 0
/* Definitions for driver INTC */
#define XPAR_XINTC_NUM_INSTANCES 1

/* Definitions for peripheral AXI_INTC_0 */
#define XPAR_AXI_INTC_0_DEVICE_ID 0
#define XPAR_AXI_INTC_0_BASEADDR 0x41800000
#define XPAR_AXI_INTC_0_HIGHADDR 0x4180FFFF
#define XPAR_AXI_INTC_0_KIND_OF_INTR 0xFFFFFFFF
#define XPAR_AXI_INTC_0_HAS_FAST 0
#define XPAR_AXI_INTC_0_IVAR_RESET_VALUE 0x00000010


/******************************************************************/

#define XPAR_INTC_SINGLE_BASEADDR 0x41800000
#define XPAR_INTC_SINGLE_HIGHADDR 0x4180FFFF
#define XPAR_INTC_SINGLE_DEVICE_ID XPAR_AXI_INTC_0_DEVICE_ID
#define XPAR_FIT_TIMER_1S_INTERRUPT_MASK 0X000001
#define XPAR_AXI_INTC_0_FIT_TIMER_1S_INTERRUPT_INTR 0
#define XPAR_IRQ_GEN_1_IRQ_MASK 0X000002
#define XPAR_AXI_INTC_0_IRQ_GEN_1_IRQ_INTR 1
#define XPAR_FIT_TIMER_5S_INTERRUPT_MASK 0X000004
#define XPAR_AXI_INTC_0_FIT_TIMER_5S_INTERRUPT_INTR 2
#define XPAR_IRQ_GEN_0_IRQ_MASK 0X000008
#define XPAR_AXI_INTC_0_IRQ_GEN_0_IRQ_INTR 3

/******************************************************************/

/* Canonical definitions for peripheral AXI_INTC_0 */
#define XPAR_INTC_0_DEVICE_ID XPAR_AXI_INTC_0_DEVICE_ID
#define XPAR_INTC_0_BASEADDR 0x41800000
#define XPAR_INTC_0_HIGHADDR 0x4180FFFF
#define XPAR_INTC_0_KIND_OF_INTR 0xFFFFFFFF
#define XPAR_INTC_0_HAS_FAST 0
#define XPAR_INTC_0_IVAR_RESET_VALUE 0x00000010


/******************************************************************/


/* Definitions for peripheral IRQ_GEN_0 */
#define XPAR_IRQ_GEN_0_BASEADDR 0x78600000
#define XPAR_IRQ_GEN_0_HIGHADDR 0x7860FFFF


/* Definitions for peripheral IRQ_GEN_1 */
#define XPAR_IRQ_GEN_1_BASEADDR 0x78620000
#define XPAR_IRQ_GEN_1_HIGHADDR 0x7862FFFF


/* Definitions for peripheral PS7_AFI_0 */
#define XPAR_PS7_AFI_0_S_AXI_BASEADDR 0xF8008000
#define XPAR_PS7_AFI_0_S_AXI_HIGHADDR 0xF8008FFF


/* Definitions for peripheral PS7_AFI_1 */
#define XPAR_PS7_AFI_1_S_AXI_BASEADDR 0xF8009000
#define XPAR_PS7_AFI_1_S_AXI_HIGHADDR 0xF8009FFF


/* Definitions for peripheral PS7_AFI_2 */
#define XPAR_PS7_AFI_2_S_AXI_BASEADDR 0xF800A000
#define XPAR_PS7_AFI_2_S_AXI_HIGHADDR 0xF800AFFF


/* Definitions for peripheral PS7_AFI_3 */
#define XPAR_PS7_AFI_3_S_AXI_BASEADDR 0xF800B000
#define XPAR_PS7_AFI_3_S_AXI_HIGHADDR 0xF800BFFF


/* Definitions for peripheral PS7_DDR_0 */
#define XPAR_PS7_DDR_0_S_AXI_BASEADDR 0x00100000
#define XPAR_PS7_DDR_0_S_AXI_HIGHADDR 0x1FFFFFFF
#define XPAR_PS7_DDR_0_S_AXI_HP0_BASEADDR 0x00000000
#define XPAR_PS7_DDR_0_S_AXI_HP0_HIGHADDR 0x1FFFFFFF
#define XPAR_PS7_DDR_0_S_AXI_HP1_BASEADDR 0x00000000
#define XPAR_PS7_DDR_0_S_AXI_HP1_HIGHADDR 0x1FFFFFFF
#define XPAR_PS7_DDR_0_S_AXI_HP2_BASEADDR 0x00000000
#define XPAR_PS7_DDR_0_S_AXI_HP2_HIGHADDR 0x1FFFFFFF
#define XPAR_PS7_DDR_0_S_AXI_HP3_BASEADDR 0x00000000
#define XPAR_PS7_DDR_0_S_AXI_HP3_HIGHADDR 0x1FFFFFFF


/* Definitions for peripheral PS7_DDRC_0 */
#define XPAR_PS7_DDRC_0_S_AXI_BASEADDR 0xF8006000
#define XPAR_PS7_DDRC_0_S_AXI_HIGHADDR 0xF8006FFF


/* Definitions for peripheral PS7_IOP_BUS_CONFIG_0 */
#define XPAR_PS7_IOP_BUS_CONFIG_0_S_AXI_BASEADDR 0xE0200000
#define XPAR_PS7_IOP_BUS_CONFIG_0_S_AXI_HIGHADDR 0xE0200FFF


/* Definitions for peripheral PS7_QSPI_LINEAR_0 */
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_BASEADDR 0xFC000000
#define XPAR_PS7_QSPI_LINEAR_0_S_AXI_HIGHADDR 0xFCFFFFFF


/* Definitions for peripheral PS7_RAM_0 */
#define XPAR_PS7_RAM_0_S_AXI_BASEADDR 0x00000000
#define XPAR_PS7_RAM_0_S_AXI_HIGHADDR 0x0002FFFF
#define XPAR_PS7_RAM_0_S_AXI_HP0_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_0_S_AXI_HP0_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_0_S_AXI_HP1_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_0_S_AXI_HP1_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_0_S_AXI_HP2_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_0_S_AXI_HP2_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_0_S_AXI_HP3_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_0_S_AXI_HP3_HIGHOCM_HIGHADDR 0xFFFFFDFF


/* Definitions for peripheral PS7_RAM_1 */
#define XPAR_PS7_RAM_1_S_AXI_BASEADDR 0xFFFF0000
#define XPAR_PS7_RAM_1_S_AXI_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_1_S_AXI_HP0_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_1_S_AXI_HP0_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_1_S_AXI_HP1_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_1_S_AXI_HP1_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_1_S_AXI_HP2_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_1_S_AXI_HP2_HIGHOCM_HIGHADDR 0xFFFFFDFF
#define XPAR_PS7_RAM_1_S_AXI_HP3_HIGHOCM_BASEADDR 0xFFFC0000
#define XPAR_PS7_RAM_1_S_AXI_HP3_HIGHOCM_HIGHADDR 0xFFFFFDFF


/* Definitions for peripheral PS7_SD_0 */
#define XPAR_PS7_SD_0_S_AXI_BASEADDR 0xE0100000
#define XPAR_PS7_SD_0_S_AXI_HIGHADDR 0xE0100FFF


/* Definitions for peripheral PS7_SLCR_0 */
#define XPAR_PS7_SLCR_0_S_AXI_BASEADDR 0xF8000000
#define XPAR_PS7_SLCR_0_S_AXI_HIGHADDR 0xF8000FFF


/******************************************************************/

/* Definitions for driver DEVCFG */
#define XPAR_XDCFG_NUM_INSTANCES 1

/* Definitions for peripheral PS7_DEV_CFG_0 */
#define XPAR_PS7_DEV_CFG_0_DEVICE_ID 0
#define XPAR_PS7_DEV_CFG_0_BASEADDR 0xF8007000
#define XPAR_PS7_DEV_CFG_0_HIGHADDR 0xF8007FFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_DEV_CFG_0 */
#define XPAR_XDCFG_0_DEVICE_ID XPAR_PS7_DEV_CFG_0_DEVICE_ID
#define XPAR_XDCFG_0_BASEADDR 0xF8007000
#define XPAR_XDCFG_0_HIGHADDR 0xF8007FFF


/******************************************************************/

/* Definitions for driver DMAPS */
#define XPAR_XDMAPS_NUM_INSTANCES 2

/* Definitions for peripheral PS7_DMA_NS */
#define XPAR_PS7_DMA_NS_DEVICE_ID 0
#define XPAR_PS7_DMA_NS_BASEADDR 0xF8004000
#define XPAR_PS7_DMA_NS_HIGHADDR 0xF8004FFF


/* Definitions for peripheral PS7_DMA_S */
#define XPAR_PS7_DMA_S_DEVICE_ID 1
#define XPAR_PS7_DMA_S_BASEADDR 0xF8003000
#define XPAR_PS7_DMA_S_HIGHADDR 0xF8003FFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_DMA_NS */
#define XPAR_XDMAPS_0_DEVICE_ID XPAR_PS7_DMA_NS_DEVICE_ID
#define XPAR_XDMAPS_0_BASEADDR 0xF8004000
#define XPAR_XDMAPS_0_HIGHADDR 0xF8004FFF

/* Canonical definitions for peripheral PS7_DMA_S */
#define XPAR_XDMAPS_1_DEVICE_ID XPAR_PS7_DMA_S_DEVICE_ID
#define XPAR_XDMAPS_1_BASEADDR 0xF8003000
#define XPAR_XDMAPS_1_HIGHADDR 0xF8003FFF


/******************************************************************/

/* Definitions for driver EMACPS */
#define XPAR_XEMACPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_ETHERNET_0 */
#define XPAR_PS7_ETHERNET_0_DEVICE_ID 0
#define XPAR_PS7_ETHERNET_0_BASEADDR 0xE000B000
#define XPAR_PS7_ETHERNET_0_HIGHADDR 0xE000BFFF
#define XPAR_PS7_ETHERNET_0_ENET_CLK_FREQ_HZ 125000000
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_1000MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_1000MBPS_DIV1 1
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_100MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_100MBPS_DIV1 5
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_10MBPS_DIV0 8
#define XPAR_PS7_ETHERNET_0_ENET_SLCR_10MBPS_DIV1 50


/******************************************************************/

/* Canonical definitions for peripheral PS7_ETHERNET_0 */
#define XPAR_XEMACPS_0_DEVICE_ID XPAR_PS7_ETHERNET_0_DEVICE_ID
#define XPAR_XEMACPS_0_BASEADDR 0xE000B000
#define XPAR_XEMACPS_0_HIGHADDR 0xE000BFFF
#define XPAR_XEMACPS_0_ENET_CLK_FREQ_HZ 125000000
#define XPAR_XEMACPS_0_ENET_SLCR_1000Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_1000Mbps_DIV1 1
#define XPAR_XEMACPS_0_ENET_SLCR_100Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_100Mbps_DIV1 5
#define XPAR_XEMACPS_0_ENET_SLCR_10Mbps_DIV0 8
#define XPAR_XEMACPS_0_ENET_SLCR_10Mbps_DIV1 50


/******************************************************************/

/* Definitions for driver GPIOPS */
#define XPAR_XGPIOPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_GPIO_0 */
#define XPAR_PS7_GPIO_0_DEVICE_ID 0
#define XPAR_PS7_GPIO_0_BASEADDR 0xE000A000
#define XPAR_PS7_GPIO_0_HIGHADDR 0xE000AFFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_GPIO_0 */
#define XPAR_XGPIOPS_0_DEVICE_ID XPAR_PS7_GPIO_0_DEVICE_ID
#define XPAR_XGPIOPS_0_BASEADDR 0xE000A000
#define XPAR_XGPIOPS_0_HIGHADDR 0xE000AFFF


/******************************************************************/

/* Definitions for driver QSPIPS */
#define XPAR_XQSPIPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_QSPI_0 */
#define XPAR_PS7_QSPI_0_DEVICE_ID 0
#define XPAR_PS7_QSPI_0_BASEADDR 0xE000D000
#define XPAR_PS7_QSPI_0_HIGHADDR 0xE000DFFF
#define XPAR_PS7_QSPI_0_QSPI_CLK_FREQ_HZ 200000000


/******************************************************************/

/* Canonical definitions for peripheral PS7_QSPI_0 */
#define XPAR_XQSPIPS_0_DEVICE_ID XPAR_PS7_QSPI_0_DEVICE_ID
#define XPAR_XQSPIPS_0_BASEADDR 0xE000D000
#define XPAR_XQSPIPS_0_HIGHADDR 0xE000DFFF
#define XPAR_XQSPIPS_0_QSPI_CLK_FREQ_HZ 200000000


/******************************************************************/

/* Definitions for Fabric interrupts connected to ps7_scugic_0 */

/******************************************************************/

/* Canonical definitions for Fabric interrupts connected to ps7_scugic_0 */

/******************************************************************/

/* Definitions for driver SCUGIC */
#define XPAR_XSCUGIC_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SCUGIC_0 */
#define XPAR_PS7_SCUGIC_0_DEVICE_ID 0
#define XPAR_PS7_SCUGIC_0_BASEADDR 0xF8F00100
#define XPAR_PS7_SCUGIC_0_HIGHADDR 0xF8F001FF
#define XPAR_PS7_SCUGIC_0_DIST_BASEADDR 0xF8F01000


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUGIC_0 */
#define XPAR_SCUGIC_0_DEVICE_ID XPAR_PS7_SCUGIC_0_DEVICE_ID
#define XPAR_SCUGIC_0_CPU_BASEADDR 0xF8F00100
#define XPAR_SCUGIC_0_CPU_HIGHADDR 0xF8F001FF
#define XPAR_SCUGIC_0_DIST_BASEADDR 0xF8F01000


/******************************************************************/

/* Definitions for driver SCUTIMER */
#define XPAR_XSCUTIMER_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SCUTIMER_0 */
#define XPAR_PS7_SCUTIMER_0_DEVICE_ID 0
#define XPAR_PS7_SCUTIMER_0_BASEADDR 0xF8F00600
#define XPAR_PS7_SCUTIMER_0_HIGHADDR 0xF8F0061F


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUTIMER_0 */
#define XPAR_XSCUTIMER_0_DEVICE_ID XPAR_PS7_SCUTIMER_0_DEVICE_ID
#define XPAR_XSCUTIMER_0_BASEADDR 0xF8F00600
#define XPAR_XSCUTIMER_0_HIGHADDR 0xF8F0061F


/******************************************************************/

/* Definitions for driver SCUWDT */
#define XPAR_XSCUWDT_NUM_INSTANCES 1

/* Definitions for peripheral PS7_SCUWDT_0 */
#define XPAR_PS7_SCUWDT_0_DEVICE_ID 0
#define XPAR_PS7_SCUWDT_0_BASEADDR 0xF8F00620
#define XPAR_PS7_SCUWDT_0_HIGHADDR 0xF8F006FF


/******************************************************************/

/* Canonical definitions for peripheral PS7_SCUWDT_0 */
#define XPAR_SCUWDT_0_DEVICE_ID XPAR_PS7_SCUWDT_0_DEVICE_ID
#define XPAR_SCUWDT_0_BASEADDR 0xF8F00620
#define XPAR_SCUWDT_0_HIGHADDR 0xF8F006FF


/******************************************************************/

/* Definitions for driver TTCPS */
#define XPAR_XTTCPS_NUM_INSTANCES 3

/* Definitions for peripheral PS7_TTC_0 */
#define XPAR_PS7_TTC_0_DEVICE_ID 0
#define XPAR_PS7_TTC_0_BASEADDR 0XF8001000
#define XPAR_PS7_TTC_0_TTC_CLK_FREQ_HZ 88888885
#define XPAR_PS7_TTC_0_TTC_CLK_CLKSRC 0
#define XPAR_PS7_TTC_1_DEVICE_ID 1
#define XPAR_PS7_TTC_1_BASEADDR 0XF8001004
#define XPAR_PS7_TTC_1_TTC_CLK_FREQ_HZ 88888885
#define XPAR_PS7_TTC_1_TTC_CLK_CLKSRC 0
#define XPAR_PS7_TTC_2_DEVICE_ID 2
#define XPAR_PS7_TTC_2_BASEADDR 0XF8001008
#define XPAR_PS7_TTC_2_TTC_CLK_FREQ_HZ 88888885
#define XPAR_PS7_TTC_2_TTC_CLK_CLKSRC 0


/******************************************************************/

/* Canonical definitions for peripheral PS7_TTC_0 */
#define XPAR_XTTCPS_0_DEVICE_ID XPAR_PS7_TTC_0_DEVICE_ID
#define XPAR_XTTCPS_0_BASEADDR 0xF8001000
#define XPAR_XTTCPS_0_TTC_CLK_FREQ_HZ 88888885
#define XPAR_XTTCPS_0_TTC_CLK_CLKSRC 0

#define XPAR_XTTCPS_1_DEVICE_ID XPAR_PS7_TTC_1_DEVICE_ID
#define XPAR_XTTCPS_1_BASEADDR 0xF8001004
#define XPAR_XTTCPS_1_TTC_CLK_FREQ_HZ 88888885
#define XPAR_XTTCPS_1_TTC_CLK_CLKSRC 0

#define XPAR_XTTCPS_2_DEVICE_ID XPAR_PS7_TTC_2_DEVICE_ID
#define XPAR_XTTCPS_2_BASEADDR 0xF8001008
#define XPAR_XTTCPS_2_TTC_CLK_FREQ_HZ 88888885
#define XPAR_XTTCPS_2_TTC_CLK_CLKSRC 0


/******************************************************************/

/* Definitions for driver UARTPS */
#define XPAR_XUARTPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_UART_1 */
#define XPAR_PS7_UART_1_DEVICE_ID 0
#define XPAR_PS7_UART_1_BASEADDR 0xE0001000
#define XPAR_PS7_UART_1_HIGHADDR 0xE0001FFF
#define XPAR_PS7_UART_1_UART_CLK_FREQ_HZ 50000000
#define XPAR_PS7_UART_1_HAS_MODEM 0


/******************************************************************/

/* Canonical definitions for peripheral PS7_UART_1 */
#define XPAR_XUARTPS_0_DEVICE_ID XPAR_PS7_UART_1_DEVICE_ID
#define XPAR_XUARTPS_0_BASEADDR 0xE0001000
#define XPAR_XUARTPS_0_HIGHADDR 0xE0001FFF
#define XPAR_XUARTPS_0_UART_CLK_FREQ_HZ 50000000
#define XPAR_XUARTPS_0_HAS_MODEM 0


/******************************************************************/

/* Definitions for driver USBPS */
#define XPAR_XUSBPS_NUM_INSTANCES 1

/* Definitions for peripheral PS7_USB_0 */
#define XPAR_PS7_USB_0_DEVICE_ID 0
#define XPAR_PS7_USB_0_BASEADDR 0xE0002000
#define XPAR_PS7_USB_0_HIGHADDR 0xE0002FFF


/******************************************************************/

/* Canonical definitions for peripheral PS7_USB_0 */
#define XPAR_XUSBPS_0_DEVICE_ID XPAR_PS7_USB_0_DEVICE_ID
#define XPAR_XUSBPS_0_BASEADDR 0xE0002000
#define XPAR_XUSBPS_0_HIGHADDR 0xE0002FFF


/******************************************************************/

/* Definition for CPU ID */
#define XPAR_CPU_ID 0

/* Definitions for peripheral PS7_CORTEXA9_0 */
#define XPAR_PS7_CORTEXA9_0_CPU_CLK_FREQ_HZ 533333374


/******************************************************************/

/* Canonical definitions for peripheral PS7_CORTEXA9_0 */
#define XPAR_CPU_CORTEXA9_0_CPU_CLK_FREQ_HZ 533333374


/******************************************************************/

