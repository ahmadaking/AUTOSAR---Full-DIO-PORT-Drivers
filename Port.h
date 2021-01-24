 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmad Samir Atta
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Mohamed Tarek's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* PORT Module Id */
#define PORT_MODULE_ID    (120U)

/* PORT Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for PORT Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and PORT Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* PORT Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PORT_Cfg.h does not match the expected version"
#endif

/* Software Version checking between PORT_Cfg.h and PORT.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PORT_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for PORT Init Channel */
#define PORT_INIT_SID                   (uint8)0x00

/* Service ID for PORT Sets the port pin direction */
#define Port_SetPinDirection_SID        (uint8)0x01

/* Service ID for PORT Refreshes port direction */
#define Port_RefreshPortDirection_SID   (uint8)0x02

/* Service ID for PORT GetVersionInfo */
#define Port_GetVersionInfo_SID         (uint8)0x03

/* Service ID for PORT Sets the port pin mode */
#define Port_SetPinMode_SID     		(uint8)0x04

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN 	   				   (uint8)0x0A

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE          (uint8)0x0B

/* API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG				       (uint8)0x0C

/* 
 * API Port_SetPinMode service called
 * when mode is unchangeable.
 */
#define PORT_E_PARAM_INVALID_MODE      		   (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE               (uint8)0x0E

/* API service used without module initialization */
#define PORT_E_UNINIT                   	   (uint8)0x0F

/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                   (uint8)0x10

/*******************************************************************************
 *                              Module Definitions                             *
 *******************************************************************************/

/* GPIO Registers base addresses */
#define GPIO_PORTA_BASE_ADDRESS           0x40004000
#define GPIO_PORTB_BASE_ADDRESS           0x40005000
#define GPIO_PORTC_BASE_ADDRESS           0x40006000
#define GPIO_PORTD_BASE_ADDRESS           0x40007000
#define GPIO_PORTE_BASE_ADDRESS           0x40024000
#define GPIO_PORTF_BASE_ADDRESS           0x40025000

/* GPIO Registers offset addresses */
#define PORT_DATA_REG_OFFSET              0x3FC
#define PORT_DIR_REG_OFFSET               0x400
#define PORT_ALT_FUNC_REG_OFFSET          0x420
#define PORT_PULL_UP_REG_OFFSET           0x510
#define PORT_PULL_DOWN_REG_OFFSET         0x514
#define PORT_DIGITAL_ENABLE_REG_OFFSET    0x51C
#define PORT_LOCK_REG_OFFSET              0x520
#define PORT_COMMIT_REG_OFFSET            0x524
#define PORT_ANALOG_MODE_SEL_REG_OFFSET   0x528
#define PORT_CTL_REG_OFFSET               0x52C


/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Type definition for Port_PinType used by the PORT APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinModeType used by the PORT APIs to choose port pin mode. */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Enum for defining the direction of a Port Pin. */
typedef enum Port_PinDirectionType
{
   PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: Structure to configure each individual PIN:
 *	1. the PORT Which the pin belongs to. 0, 1, 2, 3, 4 or 5
 *	2. the number of the pin in the PORT.
 *      3. the direction of pin --> INPUT or OUTPUT
 *      4. the internal resistor --> Disable, Pull up or Pull down
 */
typedef struct 
{
    uint8                    port_num;			 	/* Member contains the ID of the Port that this channel belongs to */
    uint8                    pin_num;				/* Member contains the ID of the Pin that this channel belongs to*/
    Port_PinModeType 	     initMode; 				/* Member contains the Pin Mode*/
    Port_PinDirectionType    initDirection;			/* Member contains the Pin Direction*/
    Port_InternalResistor    resistor;				/* Member contains the Pin resistor*/
    uint8 		     initial_value;			/* Member contains the Pin value*/
    boolean		     dirChangeability; 		        /* Member contains the Pin Direction changeability availability*/
    boolean		     modeChangeability; 	  	/* Member contains the Pin Mode changeability availability*/
}Port_ConfigChannel;


 /* Data Structure required for initializing the Port Driver */
typedef struct
{
    Port_ConfigChannel Channels[PORT_CONFIGURED_CHANNLES];
}Port_ConfigType;



/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for PORT Initialization API */
void Port_Init(const Port_ConfigType* ConfigPtr);

/* Function Sets the PORT pin direction*/
#if ( STD_ON == PORT_SET_PIN_DIRECTION_API )
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function to Refreshes port direction.*/
void Port_RefreshPortDirection(void );

/* Function Returns the version information of this module.*/
#if ( STD_ON == PORT_VERSION_INFO_API)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

/* FunctionSets the port pin mode.*/
#if ( STD_ON == PORT_SET_PIN_MODE_API)
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;

/*******************************************************************************
 *                       Port Pins ID number                                    *
 *******************************************************************************/
 /* GPIO PORT-A */
#define GPIO_PORTA_PIN0		(Port_PinType)0x00
#define GPIO_PORTA_PIN1		(Port_PinType)0x01
#define GPIO_PORTA_PIN2		(Port_PinType)0x02
#define GPIO_PORTA_PIN3		(Port_PinType)0x03
#define GPIO_PORTA_PIN4		(Port_PinType)0x04
#define GPIO_PORTA_PIN5		(Port_PinType)0x05
#define GPIO_PORTA_PIN6		(Port_PinType)0x06
#define GPIO_PORTA_PIN7		(Port_PinType)0x07
	
 /* GPIO PORT-B */	
#define GPIO_PORTB_PIN0		(Port_PinType)0x08
#define GPIO_PORTB_PIN1		(Port_PinType)0x09
#define GPIO_PORTB_PIN2		(Port_PinType)0x10
#define GPIO_PORTB_PIN3		(Port_PinType)0x11
#define GPIO_PORTB_PIN4		(Port_PinType)0x12
#define GPIO_PORTB_PIN5		(Port_PinType)0x13
#define GPIO_PORTB_PIN6		(Port_PinType)0x14
#define GPIO_PORTB_PIN7		(Port_PinType)0x15
	
 /* GPIO PORT-C */	
#define GPIO_PORTC_PIN0		(Port_PinType)0x16
#define GPIO_PORTC_PIN1		(Port_PinType)0x17
#define GPIO_PORTC_PIN2		(Port_PinType)0x18
#define GPIO_PORTC_PIN3		(Port_PinType)0x19
#define GPIO_PORTC_PIN4		(Port_PinType)0x20
#define GPIO_PORTC_PIN5		(Port_PinType)0x21
#define GPIO_PORTC_PIN6		(Port_PinType)0x22
#define GPIO_PORTC_PIN7		(Port_PinType)0x23
	
 /* GPIO PORT-D */	
#define GPIO_PORTD_PIN0		(Port_PinType)0x24
#define GPIO_PORTD_PIN1		(Port_PinType)0x25
#define GPIO_PORTD_PIN2		(Port_PinType)0x26
#define GPIO_PORTD_PIN3		(Port_PinType)0x27
#define GPIO_PORTD_PIN4		(Port_PinType)0x28
#define GPIO_PORTD_PIN5		(Port_PinType)0x29
#define GPIO_PORTD_PIN6		(Port_PinType)0x30
#define GPIO_PORTD_PIN7		(Port_PinType)0x31
	
 /* GPIO PORT-E */	
#define GPIO_PORTE_PIN0		(Port_PinType)0x32
#define GPIO_PORTE_PIN1		(Port_PinType)0x33
#define GPIO_PORTE_PIN2		(Port_PinType)0x34
#define GPIO_PORTE_PIN3		(Port_PinType)0x35
#define GPIO_PORTE_PIN4		(Port_PinType)0x36
#define GPIO_PORTE_PIN5		(Port_PinType)0x37

	
 /* GPIO PORT-F */	
#define GPIO_PORTF_PIN0		(Port_PinType)0x38 /* SW2*/
#define GPIO_PORTF_PIN1		(Port_PinType)0x39 /* LED1, Red */
#define GPIO_PORTF_PIN2		(Port_PinType)0x40 /* LED2, Blue*/
#define GPIO_PORTF_PIN3		(Port_PinType)0x41 /* LED3, Green*/
#define GPIO_PORTF_PIN4		(Port_PinType)0x42 /* SW1 */



/* Others */
/* Port Pin Levels */
#define PORT_PIN_LEVEL_LOW 		STD_LOW
#define PORT_PIN_LEVEL_HIGH 	STD_HIGH

#endif /* PORT_H */
