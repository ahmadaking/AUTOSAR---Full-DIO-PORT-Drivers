 /******************************************************************************
 *
 * Module: PORT
 *
 * File Name: PORT_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - PORT Driver
 *
 * Author: Mohamed Tarek
 ******************************************************************************/

#include "Port.h"
#include "Port_Cfg.h"
//#include "Port_Cbk.h"
#include "tm4c123gh6pm_registers.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between PORT_PBcfg.c and PORT.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


/* PB structure used with Port_Init API */
const Port_ConfigType Port_Configuration = {
					/*Channel_0-portA*/
						PORT_A_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_1*/
						PORT_A_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_2*/
						PORT_A_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_3*/
						PORT_A_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_4*/
						PORT_A_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_5*/
						PORT_A_NUMBER_ID,
						PORT_PIN_5_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_6*/
						PORT_A_NUMBER_ID,
						PORT_PIN_6_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_7*/
						PORT_A_NUMBER_ID,
						PORT_PIN_7_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_8-portB*/
						PORT_B_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_9*/
						PORT_B_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
                                                ,
					/*Channel_10*/
						PORT_B_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_11*/
						PORT_B_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_12*/
						PORT_B_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_13*/
						PORT_B_NUMBER_ID,
						PORT_PIN_5_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_14*/
						PORT_B_NUMBER_ID,
						PORT_PIN_6_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_15*/
						PORT_B_NUMBER_ID,
						PORT_PIN_7_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_16-portC*/
						PORT_C_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_17*/
						PORT_C_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_18*/
						PORT_C_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_19*/
						PORT_C_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_20*/
						PORT_C_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_21*/
						PORT_C_NUMBER_ID,
						PORT_PIN_5_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_22*/
						PORT_C_NUMBER_ID,
						PORT_PIN_6_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_23*/
						PORT_C_NUMBER_ID,
						PORT_PIN_7_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_24-portD*/
						PORT_D_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_25*/
						PORT_D_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_26*/
						PORT_D_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_27*/
						PORT_D_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_28*/
						PORT_D_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_29*/
						PORT_D_NUMBER_ID,
						PORT_PIN_5_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_30*/
						PORT_D_NUMBER_ID,
						PORT_PIN_6_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_31*/
						PORT_D_NUMBER_ID,
						PORT_PIN_7_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_32-portE*/
						PORT_E_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_33*/
						PORT_E_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_34*/
						PORT_E_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_35*/
						PORT_E_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_36*/
						PORT_E_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_37*/
						PORT_E_NUMBER_ID,
						PORT_PIN_5_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_38-portF*/
                        /* SW2*/
						PORT_F_NUMBER_ID,
						PORT_PIN_0_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_39*/
						/* LED1, Red */
						PORT_F_NUMBER_ID,
						PORT_PIN_1_NUMBER,
						PORT_PIN39_MODE,
						PORT_PIN39_DIRECTION,
						PORT_PIN39_RESISTOR,
						PORT_PIN39_LEVEL_VALUE,
						PORT_PIN39_DIRECTION_CHANGEABILITY,
						PORT_PIN39_MODE_CHANGEABILITY
                        ,
					/*Channel_40*/
                        /* LED2, Blue*/
						PORT_F_NUMBER_ID,
						PORT_PIN_2_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_41*/
                        /* LED3, Green*/
						PORT_F_NUMBER_ID,
						PORT_PIN_3_NUMBER,
						PORT_PIN_DEFAULT_MODE,
						PORT_PIN_DEFAULT_DIRECTION,
						PORT_DEFAULT_PIN_RESISTOR,
						PORT_PIN_DEFAULT_LEVEL_VALUE,
						PORT_PIN_DEFAULT_DIRECTION_CHANGEABILITY,
						PORT_PIN_DEFAULT_MODE_CHANGEABILITY
						,
					/*Channel_42*/
						/* SW1 */
						PORT_F_NUMBER_ID,
						PORT_PIN_4_NUMBER,
						PORT_PIN42_MODE,
						PORT_PIN42_DIRECTION,
						PORT_PIN42_RESISTOR,
						PORT_PIN42_LEVEL_VALUE,
						PORT_PIN42_DIRECTION_CHANGEABILITY,
						PORT_PIN42_MODE_CHANGEABILITY
				         }; /* end of structure*/