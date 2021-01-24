 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Ahmad Samir Atta
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)


 /*******************************************************************************
 * Container Name : PORT General configuration.
 * Description	  : Module wide configuration parameters of the PORT driver.
 *******************************************************************************/

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option  to enable/disable the API to read out the modules version information. */
#define PORT_VERSION_INFO_API                (STD_ON)

/* Pre-compile option to enable/disable the use of the function "Port_SetPinDirection()" */
#define PORT_SET_PIN_DIRECTION_API	     (STD_ON)

/* Pre-compile option to enable/disable the use of the function "Port_SetPinMode()" */
#define PORT_SET_PIN_MODE_API	             (STD_ON)

/* Number of the configured Port Channels */
#define PORT_CONFIGURED_CHANNLES	       (43U)

/*******************************************************************************
 * Container Name : PortPin
 * Description	  : Configuration of the individual port pins.
 *******************************************************************************/
 /* The initial default direction of the pin (IN or OUT). */
 #define PORT_PIN_DEFAULT_DIRECTION	(PORT_PIN_OUT)
 
 /*The initial direction for each pin*/
 #define PORT_PIN0_DIRECTION	     (PORT_PIN_OUT)  /* portA - P0 */
 #define PORT_PIN1_DIRECTION	     (PORT_PIN_OUT)  /* portA - P1 */
 #define PORT_PIN2_DIRECTION	     (PORT_PIN_OUT)  /* portA - P2 */
 #define PORT_PIN3_DIRECTION	     (PORT_PIN_OUT)  /* portA - P3 */
 #define PORT_PIN4_DIRECTION	     (PORT_PIN_OUT)  /* portA - P4 */
 #define PORT_PIN5_DIRECTION	     (PORT_PIN_OUT)  /* portA - P5 */
 #define PORT_PIN6_DIRECTION	     (PORT_PIN_OUT)  /* portA - P6 */
 #define PORT_PIN7_DIRECTION	     (PORT_PIN_OUT)  /* portA - P7 */
 #define PORT_PIN8_DIRECTION	     (PORT_PIN_OUT)  /* portB - P0 */
 #define PORT_PIN9_DIRECTION	     (PORT_PIN_OUT)  /* portB - P1 */
 #define PORT_PIN10_DIRECTION	     (PORT_PIN_OUT)  /* portB - P2 */
 #define PORT_PIN11_DIRECTION	     (PORT_PIN_OUT)  /* portB - P3 */
 #define PORT_PIN12_DIRECTION	     (PORT_PIN_OUT)  /* portB - P4 */
 #define PORT_PIN13_DIRECTION	     (PORT_PIN_OUT)  /* portB - P5 */
 #define PORT_PIN14_DIRECTION	     (PORT_PIN_OUT)  /* portB - P6 */
 #define PORT_PIN15_DIRECTION	     (PORT_PIN_OUT)  /* portB - P7 */
 #define PORT_PIN16_DIRECTION	     (PORT_PIN_OUT)  /* portC - P0 - JTAG pins */
 #define PORT_PIN17_DIRECTION	     (PORT_PIN_OUT)  /* portC - P1 - JTAG pins */
 #define PORT_PIN18_DIRECTION	     (PORT_PIN_OUT)  /* portC - P2 - JTAG pins */
 #define PORT_PIN19_DIRECTION	     (PORT_PIN_OUT)  /* portC - P3 - JTAG pins */
 #define PORT_PIN20_DIRECTION	     (PORT_PIN_OUT)  /* portC - P4 */
 #define PORT_PIN21_DIRECTION	     (PORT_PIN_OUT)  /* portC - P5 */
 #define PORT_PIN22_DIRECTION	     (PORT_PIN_OUT)  /* portC - P6 */
 #define PORT_PIN23_DIRECTION	     (PORT_PIN_OUT)  /* portC - P7 */
 #define PORT_PIN24_DIRECTION	     (PORT_PIN_OUT)  /* portD - P0 */
 #define PORT_PIN25_DIRECTION	     (PORT_PIN_OUT)  /* portD - P1 */
 #define PORT_PIN26_DIRECTION	     (PORT_PIN_OUT)  /* portD - P2 */
 #define PORT_PIN27_DIRECTION	     (PORT_PIN_OUT)  /* portD - P3 */
 #define PORT_PIN28_DIRECTION	     (PORT_PIN_OUT)  /* portD - P4 */
 #define PORT_PIN29_DIRECTION	     (PORT_PIN_OUT)  /* portD - P5 */
 #define PORT_PIN30_DIRECTION	     (PORT_PIN_OUT)  /* portD - P6 */
 #define PORT_PIN31_DIRECTION	     (PORT_PIN_OUT)  /* portD - P7 */
 #define PORT_PIN32_DIRECTION	     (PORT_PIN_OUT)  /* portE - P0 */
 #define PORT_PIN33_DIRECTION	     (PORT_PIN_OUT)  /* portE - P1 */
 #define PORT_PIN34_DIRECTION	     (PORT_PIN_OUT)  /* portE - P2 */
 #define PORT_PIN35_DIRECTION	     (PORT_PIN_OUT)  /* portE - P3 */
 #define PORT_PIN36_DIRECTION	     (PORT_PIN_OUT)  /* portE - P4 */
 #define PORT_PIN37_DIRECTION	     (PORT_PIN_OUT)  /* portE - P5 */
 #define PORT_PIN38_DIRECTION	     (PORT_PIN_OUT)  /* portF - SW2*/
 #define PORT_PIN39_DIRECTION	     (PORT_PIN_OUT)  /* portF - LED1, Red */
 #define PORT_PIN40_DIRECTION	     (PORT_PIN_OUT)  /* portF - LED2, Blue*/
 #define PORT_PIN41_DIRECTION	     (PORT_PIN_OUT)  /* portF - LED3, Green*/
 #define PORT_PIN42_DIRECTION	     (PORT_PIN_IN)   /* portF - SW1 */

 
 
 /* PORT Configured Port ID's */
 #define PORT_A_NUMBER_ID		(Port_PinType)0
 #define PORT_B_NUMBER_ID		(Port_PinType)1
 #define PORT_C_NUMBER_ID		(Port_PinType)2
 #define PORT_D_NUMBER_ID		(Port_PinType)3
 #define PORT_E_NUMBER_ID		(Port_PinType)4
 #define PORT_F_NUMBER_ID		(Port_PinType)5
 
 /* PORT Configured PortPin Number */
 #define PORT_PIN_0_NUMBER 		(Port_PinType)0
 #define PORT_PIN_1_NUMBER 		(Port_PinType)1
 #define PORT_PIN_2_NUMBER 		(Port_PinType)2
 #define PORT_PIN_3_NUMBER 		(Port_PinType)3
 #define PORT_PIN_4_NUMBER 		(Port_PinType)4
 #define PORT_PIN_5_NUMBER 		(Port_PinType)5
 #define PORT_PIN_6_NUMBER 		(Port_PinType)6
 #define PORT_PIN_7_NUMBER 		(Port_PinType)7
 
 /* To indicate the default direction changeability on a port pin during runtime (ON/OFF) */
 #define PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY		(STD_ON)
 
 /* To indicate Eatch pin direction changeability during runtime (ON/OFF) */
 #define PORT_PIN0_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P0 */
 #define PORT_PIN1_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P1 */
 #define PORT_PIN2_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P2 */
 #define PORT_PIN3_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P3 */
 #define PORT_PIN4_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P4 */
 #define PORT_PIN5_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P5 */
 #define PORT_PIN6_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P6 */
 #define PORT_PIN7_DIRECTION_CHANGEABILITY			(STD_ON)  /* portA - P7 */
 #define PORT_PIN8_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P0 */
 #define PORT_PIN9_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P1 */
 #define PORT_PIN10_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P2 */
 #define PORT_PIN11_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P3 */
 #define PORT_PIN12_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P4 */
 #define PORT_PIN13_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P5 */
 #define PORT_PIN14_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P6 */
 #define PORT_PIN15_DIRECTION_CHANGEABILITY			(STD_ON)  /* portB - P7 */
 #define PORT_PIN16_DIRECTION_CHANGEABILITY			(STD_OFF)  /* portC - P0 - JTAG pins */
 #define PORT_PIN17_DIRECTION_CHANGEABILITY			(STD_OFF)  /* portC - P1 - JTAG pins */
 #define PORT_PIN18_DIRECTION_CHANGEABILITY			(STD_OFF)  /* portC - P2 - JTAG pins */
 #define PORT_PIN19_DIRECTION_CHANGEABILITY			(STD_OFF)  /* portC - P3 - JTAG pins */
 #define PORT_PIN20_DIRECTION_CHANGEABILITY			(STD_ON)  /* portC - P4 */
 #define PORT_PIN21_DIRECTION_CHANGEABILITY			(STD_ON)  /* portC - P5 */
 #define PORT_PIN22_DIRECTION_CHANGEABILITY			(STD_ON)  /* portC - P6 */
 #define PORT_PIN23_DIRECTION_CHANGEABILITY			(STD_ON)  /* portC - P7 */
 #define PORT_PIN24_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P0 */
 #define PORT_PIN25_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P1 */
 #define PORT_PIN26_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P2 */
 #define PORT_PIN27_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P3 */
 #define PORT_PIN28_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P4 */
 #define PORT_PIN29_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P5 */
 #define PORT_PIN30_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P6 */
 #define PORT_PIN31_DIRECTION_CHANGEABILITY			(STD_ON)  /* portD - P7 */
 #define PORT_PIN32_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P0 */
 #define PORT_PIN33_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P1 */
 #define PORT_PIN34_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P2 */
 #define PORT_PIN35_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P3 */
 #define PORT_PIN36_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P4 */
 #define PORT_PIN37_DIRECTION_CHANGEABILITY			(STD_ON)  /* portE - P5 */
 #define PORT_PIN38_DIRECTION_CHANGEABILITY			(STD_ON)  /* portF - SW2*/ 
 #define PORT_PIN39_DIRECTION_CHANGEABILITY			(STD_ON)  /* portF - LED1, Red */ 
 #define PORT_PIN40_DIRECTION_CHANGEABILITY			(STD_ON)  /* portF - LED2, Blue*/ 
 #define PORT_PIN41_DIRECTION_CHANGEABILITY			(STD_ON)  /* portF - LED3, Green*/ 
 #define PORT_PIN42_DIRECTION_CHANGEABILITY			(STD_ON)  /* portF - SW1 */ 
 
 
 /* To indicate the default mode changeability on a port pin during runtime (ON/OFF) */
 #define PORT_PIN_DEFAULT_MODE_CHANGEABILITY			(STD_ON)
 
 /* To indicate Eatch pin direction changeability during runtime (ON/OFF) */
 #define PORT_PIN0_MODE_CHANGEABILITY		(STD_ON)        /* portA - P0 */
 #define PORT_PIN1_MODE_CHANGEABILITY		(STD_ON)        /* portA - P1 */
 #define PORT_PIN2_MODE_CHANGEABILITY		(STD_ON)        /* portA - P2 */
 #define PORT_PIN3_MODE_CHANGEABILITY		(STD_ON)        /* portA - P3 */
 #define PORT_PIN4_MODE_CHANGEABILITY		(STD_ON)        /* portA - P4 */
 #define PORT_PIN5_MODE_CHANGEABILITY		(STD_ON)        /* portA - P5 */
 #define PORT_PIN6_MODE_CHANGEABILITY		(STD_ON)        /* portA - P6 */
 #define PORT_PIN7_MODE_CHANGEABILITY		(STD_ON)        /* portA - P7 */
 #define PORT_PIN8_MODE_CHANGEABILITY		(STD_ON)        /* portB - P0 */
 #define PORT_PIN9_MODE_CHANGEABILITY		(STD_ON)        /* portB - P1 */
 #define PORT_PIN10_MODE_CHANGEABILITY		(STD_ON)        /* portB - P2 */
 #define PORT_PIN11_MODE_CHANGEABILITY		(STD_ON)        /* portB - P3 */
 #define PORT_PIN12_MODE_CHANGEABILITY		(STD_ON)        /* portB - P4 */
 #define PORT_PIN13_MODE_CHANGEABILITY		(STD_ON)        /* portB - P5 */
 #define PORT_PIN14_MODE_CHANGEABILITY		(STD_ON)        /* portB - P6 */
 #define PORT_PIN15_MODE_CHANGEABILITY		(STD_ON)        /* portB - P7 */
 #define PORT_PIN16_MODE_CHANGEABILITY		(STD_OFF)        /* portC - P0 - JTAG pins */
 #define PORT_PIN17_MODE_CHANGEABILITY		(STD_OFF)        /* portC - P1 - JTAG pins */
 #define PORT_PIN18_MODE_CHANGEABILITY		(STD_OFF)        /* portC - P2 - JTAG pins */
 #define PORT_PIN19_MODE_CHANGEABILITY		(STD_OFF)        /* portC - P3 - JTAG pins */
 #define PORT_PIN20_MODE_CHANGEABILITY		(STD_ON)        /* portC - P4 */
 #define PORT_PIN21_MODE_CHANGEABILITY		(STD_ON)        /* portC - P5 */
 #define PORT_PIN22_MODE_CHANGEABILITY		(STD_ON)        /* portC - P6 */
 #define PORT_PIN23_MODE_CHANGEABILITY		(STD_ON)        /* portC - P7 */
 #define PORT_PIN24_MODE_CHANGEABILITY		(STD_ON)        /* portD - P0 */
 #define PORT_PIN25_MODE_CHANGEABILITY		(STD_ON)        /* portD - P1 */
 #define PORT_PIN26_MODE_CHANGEABILITY		(STD_ON)        /* portD - P2 */
 #define PORT_PIN27_MODE_CHANGEABILITY		(STD_ON)        /* portD - P3 */
 #define PORT_PIN28_MODE_CHANGEABILITY		(STD_ON)        /* portD - P4 */
 #define PORT_PIN29_MODE_CHANGEABILITY		(STD_ON)        /* portD - P5 */
 #define PORT_PIN30_MODE_CHANGEABILITY		(STD_ON)        /* portD - P6 */
 #define PORT_PIN31_MODE_CHANGEABILITY		(STD_ON)        /* portD - P7 */
 #define PORT_PIN32_MODE_CHANGEABILITY		(STD_ON)        /* portE - P0 */
 #define PORT_PIN33_MODE_CHANGEABILITY		(STD_ON)        /* portE - P1 */
 #define PORT_PIN34_MODE_CHANGEABILITY		(STD_ON)        /* portE - P2 */
 #define PORT_PIN35_MODE_CHANGEABILITY		(STD_ON)        /* portE - P3 */
 #define PORT_PIN36_MODE_CHANGEABILITY		(STD_ON)        /* portE - P4 */
 #define PORT_PIN37_MODE_CHANGEABILITY		(STD_ON)        /* portE - P5 */
 #define PORT_PIN38_MODE_CHANGEABILITY		(STD_ON)        /* portF - P0 - SW2*/
 #define PORT_PIN39_MODE_CHANGEABILITY		(STD_OFF)        /* portF - P1 - LED1, Red */
 #define PORT_PIN40_MODE_CHANGEABILITY		(STD_ON)        /* portF - P2 - LED2, Blue*/
 #define PORT_PIN41_MODE_CHANGEABILITY		(STD_ON)        /* portF - P3 - LED3, Green*/
 #define PORT_PIN42_MODE_CHANGEABILITY		(STD_OFF)        /* portF - P4 - SW1 */

 
 
 
 /* Port pin mode from mode list for use with "Port_Init()" function. */
 #define PORT_PIN_DEFAULT_MODE				 (PORT_PIN_MODE_DIO)
 
 /**/
 #define PORT_PIN0_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P0 */
 #define PORT_PIN1_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P1 */
 #define PORT_PIN2_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P2 */
 #define PORT_PIN3_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P3 */
 #define PORT_PIN4_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P4 */
 #define PORT_PIN5_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P5 */
 #define PORT_PIN6_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P6 */
 #define PORT_PIN7_MODE		 	 (PORT_PIN_MODE_DIO)    /* portA - P7 */
 #define PORT_PIN8_MODE		 	 (PORT_PIN_MODE_DIO)    /* portB - P0 */
 #define PORT_PIN9_MODE		 	 (PORT_PIN_MODE_DIO)    /* portB - P1 */
 #define PORT_PIN10_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P2 */
 #define PORT_PIN11_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P3 */
 #define PORT_PIN12_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P4 */
 #define PORT_PIN13_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P5 */
 #define PORT_PIN14_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P6 */
 #define PORT_PIN15_MODE		 (PORT_PIN_MODE_DIO)    /* portB - P7 */
 #define PORT_PIN16_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P0 - JTAG pins */
 #define PORT_PIN17_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P1 - JTAG pins */
 #define PORT_PIN18_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P2 - JTAG pins */
 #define PORT_PIN19_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P3 - JTAG pins */
 #define PORT_PIN20_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P4 */
 #define PORT_PIN21_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P5 */
 #define PORT_PIN22_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P6 */
 #define PORT_PIN23_MODE		 (PORT_PIN_MODE_DIO)    /* portC - P7 */
 #define PORT_PIN24_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P0 */
 #define PORT_PIN25_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P1 */
 #define PORT_PIN26_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P2 */
 #define PORT_PIN27_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P3 */
 #define PORT_PIN28_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P4 */
 #define PORT_PIN29_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P5 */
 #define PORT_PIN30_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P6 */
 #define PORT_PIN31_MODE		 (PORT_PIN_MODE_DIO)    /* portD - P7 */
 #define PORT_PIN32_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P0 */
 #define PORT_PIN33_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P1 */
 #define PORT_PIN34_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P2 */
 #define PORT_PIN35_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P3 */
 #define PORT_PIN36_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P4 */
 #define PORT_PIN37_MODE		 (PORT_PIN_MODE_DIO)    /* portE - P5 */
 #define PORT_PIN38_MODE		 (PORT_PIN_MODE_DIO)    /* portF - SW2*/
 #define PORT_PIN39_MODE		 (PORT_PIN_MODE_DIO)    /* portF - LED1, Red */
 #define PORT_PIN40_MODE		 (PORT_PIN_MODE_DIO)    /* portF - LED2, Blue*/
 #define PORT_PIN41_MODE		 (PORT_PIN_MODE_DIO)    /* portF - LED3, Green*/
 #define PORT_PIN42_MODE		 (PORT_PIN_MODE_DIO)    /* portF - SW1 */

 
 /* Port Pin Level default value from Port pin list (PORT_PIN_LEVEL_HIGH/PORT_PIN_LEVEL_LOW) */
 #define PORT_PIN_DEFAULT_LEVEL_VALUE	     (PORT_PIN_LEVEL_LOW)
 
 /* Port Pin Level value for each pin, from Port pin list (PORT_PIN_LEVEL_HIGH/PORT_PIN_LEVEL_LOW) */
 #define PORT_PIN0_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P0 */
 #define PORT_PIN1_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P1 */
 #define PORT_PIN2_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P2 */
 #define PORT_PIN3_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P3 */
 #define PORT_PIN4_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P4 */
 #define PORT_PIN5_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P5 */
 #define PORT_PIN6_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P6 */
 #define PORT_PIN7_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portA - P7 */
 #define PORT_PIN8_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portB - P0 */
 #define PORT_PIN9_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portB - P1 */
 #define PORT_PIN10_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P2 */            
 #define PORT_PIN11_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P3 */            
 #define PORT_PIN12_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P4 */
 #define PORT_PIN13_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P5 */
 #define PORT_PIN14_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P6 */
 #define PORT_PIN15_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portB - P7 */
 #define PORT_PIN16_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portC - P0 - JTAG pins */
 #define PORT_PIN17_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portC - P1 - JTAG pins */
 #define PORT_PIN18_LEVEL_VALUE 	(PORT_PIN_LEVEL_LOW)    /* portC - P2 - JTAG pins */
 #define PORT_PIN19_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portC - P3 - JTAG pins */
 #define PORT_PIN20_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portC - P4 */
 #define PORT_PIN21_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portC - P5 */
 #define PORT_PIN22_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portC - P6 */
 #define PORT_PIN23_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portC - P7 */
 #define PORT_PIN24_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P0 */
 #define PORT_PIN25_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P1 */
 #define PORT_PIN26_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P2 */
 #define PORT_PIN27_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P3 */
 #define PORT_PIN28_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P4 */
 #define PORT_PIN29_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P5 */
 #define PORT_PIN30_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P6 */
 #define PORT_PIN31_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portD - P7 */
 #define PORT_PIN32_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P0 */
 #define PORT_PIN33_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P1 */
 #define PORT_PIN34_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P2 */
 #define PORT_PIN35_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P3 */
 #define PORT_PIN36_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P4 */
 #define PORT_PIN37_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portE - P5 */
 #define PORT_PIN38_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portF - SW2*/
 #define PORT_PIN39_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portF - LED1, Red */
 #define PORT_PIN40_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portF - LED2, Blue*/
 #define PORT_PIN41_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portF - LED3, Green*/
 #define PORT_PIN42_LEVEL_VALUE		(PORT_PIN_LEVEL_LOW)    /* portF - SW1 */

 
 
 /*Port Pin default Resistor (Off/Pull_Up/Pull_Down)*/
 #define PORT_DEFAULT_PIN_RESISTOR 			 (OFF)
 
 /* Port Pin Resistor for each Pin(Off/Pull_Up/Pull_Down) */
 #define PORT_PIN0_RESISTOR	 (OFF)          /* portA - P0 */
 #define PORT_PIN1_RESISTOR	 (OFF)          /* portA - P1 */
 #define PORT_PIN2_RESISTOR	 (OFF)          /* portA - P2 */
 #define PORT_PIN3_RESISTOR	 (OFF)          /* portA - P3 */
 #define PORT_PIN4_RESISTOR	 (OFF)          /* portA - P4 */
 #define PORT_PIN5_RESISTOR	 (OFF)          /* portA - P5 */
 #define PORT_PIN6_RESISTOR	 (OFF)          /* portA - P6 */
 #define PORT_PIN7_RESISTOR	 (OFF)          /* portA - P7 */
 #define PORT_PIN8_RESISTOR	 (OFF)          /* portB - P0 */
 #define PORT_PIN9_RESISTOR	 (OFF)          /* portB - P1 */
 #define PORT_PIN10_RESISTOR     (OFF)	        /* portB - P2 */
 #define PORT_PIN11_RESISTOR     (OFF)	        /* portB - P3 */
 #define PORT_PIN12_RESISTOR     (OFF)	        /* portB - P4 */
 #define PORT_PIN13_RESISTOR     (OFF)	        /* portB - P5 */
 #define PORT_PIN14_RESISTOR     (OFF)	        /* portB - P6 */
 #define PORT_PIN15_RESISTOR     (OFF)	        /* portB - P7 */
 #define PORT_PIN16_RESISTOR     (OFF)	        /* portC - P0 - JTAG pins */
 #define PORT_PIN17_RESISTOR     (OFF)	        /* portC - P1 - JTAG pins */
 #define PORT_PIN18_RESISTOR     (OFF)	        /* portC - P2 - JTAG pins */
 #define PORT_PIN19_RESISTOR     (OFF)	        /* portC - P3 - JTAG pins */
 #define PORT_PIN20_RESISTOR     (OFF)	        /* portC - P4 */
 #define PORT_PIN21_RESISTOR     (OFF)	        /* portC - P5 */
 #define PORT_PIN22_RESISTOR     (OFF)	        /* portC - P6 */
 #define PORT_PIN23_RESISTOR     (OFF)	        /* portC - P7 */
 #define PORT_PIN24_RESISTOR     (OFF)	        /* portD - P0 */
 #define PORT_PIN25_RESISTOR     (OFF)	        /* portD - P1 */
 #define PORT_PIN26_RESISTOR     (OFF)	        /* portD - P2 */
 #define PORT_PIN27_RESISTOR     (OFF)	        /* portD - P3 */
 #define PORT_PIN28_RESISTOR     (OFF)	        /* portD - P4 */
 #define PORT_PIN29_RESISTOR     (OFF)	        /* portD - P5 */
 #define PORT_PIN30_RESISTOR     (OFF)	        /* portD - P6 */
 #define PORT_PIN31_RESISTOR     (OFF)	        /* portD - P7 */
 #define PORT_PIN32_RESISTOR     (OFF)	        /* portE - P0 */
 #define PORT_PIN33_RESISTOR     (OFF)	        /* portE - P1 */
 #define PORT_PIN34_RESISTOR     (OFF)	        /* portE - P2 */
 #define PORT_PIN35_RESISTOR     (OFF)	        /* portE - P3 */
 #define PORT_PIN36_RESISTOR     (OFF)	        /* portE - P4 */
 #define PORT_PIN37_RESISTOR     (OFF)	        /* portE - P5 */
 #define PORT_PIN38_RESISTOR     (OFF)	        /* portF - P0 - SW2*/
 #define PORT_PIN39_RESISTOR     (OFF)	        /* portF - P1 - LED1, Red */
 #define PORT_PIN40_RESISTOR     (OFF)          /* portF - P2 - LED2, Blue*/
 #define PORT_PIN41_RESISTOR     (OFF)          /* portF - P3 - LED3, Green*/
 #define PORT_PIN42_RESISTOR     (PULL_UP)      /* portF - P4 - SW1 */

 
 
 
 
 
 
 /* Port pin mode from mode list. Note that more than one mode is allowed by default. */
 //#define PORT_PIN_MODE
 

 
 
 /*******************************************************************************
 *                           Pin Modes Ranges                                   *
 *******************************************************************************/
/* 0- Port Pin configured for DIO. It shall be used under control of the DIO driver. */
#define PORT_PIN_MODE_DIO		                    (Port_PinModeType)0

/* 1- Port Pin used for CAN driver */
#define PORT_PIN_MODE_CAN		                    (Port_PinModeType)1

/* 2- Port Pin used by UART_1x driver */
#define PORT_PIN_MODE_UART_1x		                 (Port_PinModeType)2

/* 3- Port Pin used by UART_1x driver */
#define PORT_PIN_MODE_UART_0234567x		             (Port_PinModeType)3

/* 4- Port Pin used by UART_TS driver */
#define PORT_PIN_MODE_UART_TS		                 (Port_PinModeType)4

/* 5- Port Pin used by Synchronous Serial Interface 0 (SSI = SPI) driver */
#define PORT_PIN_MODE_SSI_1		                     (Port_PinModeType)5

/* 6- Port Pin used by Synchronous Serial Interface 1 (SSI = SPI) driver */
#define PORT_PIN_MODE_SSI_2		                    (Port_PinModeType)6

/* 7- Port Pin used by Synchronous Serial Interface 2 (SSI = SPI) driver */
#define PORT_PIN_MODE_SSI_3		                    (Port_PinModeType)7

/* 8- Port Pin configured for DIO. It shall be used under control of the general purpose timer driver. */
#define PORT_PIN_MODE_DIO_GPT	                    (Port_PinModeType)8

/* 9- Port Pin used by Analog Comparator driver */
#define PORT_PIN_MODE_ANALOG_COMP		            (Port_PinModeType)9

/* 10- Port Pin used by System Control & Clocks NMI driver */
#define PORT_PIN_MODE_SYS_CONTROL_CLOCKS_NMI		(Port_PinModeType)10

/* 11- Port Pin used by I2C driver */
#define PORT_PIN_MODE_I2C		                    (Port_PinModeType)11

/* 12- Port Pin used by PWM_0 driver */
#define PORT_PIN_MODE_PWM_0		                    (Port_PinModeType)12

/* 13- Port Pin used by PWM_1 driver */
#define PORT_PIN_MODE_PWM_1		                    (Port_PinModeType)13

/* 14- Port Pin used for USB driver. */
#define PORT_PIN_MODE_USB		                    (Port_PinModeType)14

/* 15- Port Pin used for Quadrature Encoder Interface driver. */
#define PORT_PIN_MODE_QEI		                    (Port_PinModeType)15

/* 16- Port Pin used for JTAG/SWD/SWO driver. */
#define PORT_PIN_MODE_JTAG_SWD_SWO		            (Port_PinModeType)16

/* 17- Port Pin used for Core (Trace) driver. */
#define PORT_PIN_MODE_CORE_TRACE		            (Port_PinModeType)17

/* 18- Port Pin used for ADC driver. */
#define PORT_PIN_MODE_ADC		                    (Port_PinModeType)18

 #endif  /* DIO_CFG_H */
