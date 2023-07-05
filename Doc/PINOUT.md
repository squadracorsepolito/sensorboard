# PINOUT SENSORBOARD REAR/FRONT

## J3 <=> SENS_26PIN 

|# |Schematic      | FRONT Signal         | REAR Signal        | 
|--|---------------|----------------------|--------------------|
|1 |+24            |24V_FrontBoard        |24V_RearBoards      |
|2 |+24            |                      |24V_RearBoards      |
|3 |ANALOG9        |Steering_Sensor       |CoolingPressSX      |
|4 |ANALOG5        |Brake_Press           |                    |
|5 |ANALOG7        |Brake_EXT             |                    |
|6 |ANALOG8        |Throttle1             |                    |
|7 |ANALOG6        |Throttle2             |                    |
|8 |CANH           |CANH_LV_6             |CANH_LV2            |
|9 |CANH           |CANH_LV_7             |                    |
|10|DGND           |GND_24V_FrontBoard    |GND_RearBoards      |
|11|DGND           |GND_Steering_Sensor   |GND_RearBoards      |
|12|DGND           |GND_Brake_Press       |GND_CAN_LV2         |
|13|DGND           |GND_Brake_EXT         |GND_CoolingPressSX  |
|14|CANL           |CANL_LV_6             |CANL_LV2            |
|15|CANL           |CANL_LV_7             |                    |
|16|DGND           |GND_Throttle1         |                    |
|17|DGND           |                      |                    |
|18|DGND           |                      |                    |
|19|+5 Steeering   |5V_Steering_Sensor    |5V_CoolingPressSX   |
|20|SHUTDOWN_IN_1  |SensorShut1_PreInertia|ShutSens_PostBSPD   |
|21|SHUTDOWN_IN_2  |SensorShut_PostInertia|ShutSens_PreFunghi  |
|22|SHUTDOWN_IN_3  |SensorShut_PostBOTS   |ShutSens_PostInvMono|
|23|SHUTDOWN_IN_4  |SensorShut_postCockpit|ShutSens_PostInvFR  |
|24|+5 Brake Press |5V_Brake_Press        |                    |
|25|+5 Strain Brake|5V_Brake_EXT          |                    |
|26|+5 Throttle    |5V_Throttle1          |                    |

### FRONT Signals
|Signal Name           |From         |To                       |Gauge |Dir|Notes                                                                                   |
|----------------------|-------------|-------------------------|------|---|----------------------------------------------------------------------------------------|
|CANH_LV_6             |Sens_26Pin.1 |IMU_Calza_Suprema_Plug2.6|24 AWG|IN |CAN                                                                                     |
|CANL_LV_6             |Sens_26Pin.2 |IMU_Calza_Suprema_Plug2.7|24 AWG|IN |CAN                                                                                     |
|GND_CANLV_6           |Sens_26Pin.3 |IMU_Calza_Suprema_Plug2.8|      |-  |CAN                                                                                     |
|CANH_LV_7             |Sens_26Pin.4 |OBD_CANLV.1              |24 AWG|OUT|CAN                                                                                     |
|CANL_LV_7             |Sens_26Pin.5 |OBD_CANLV.2              |24 AWG|OUT|CAN                                                                                     |
|GND_CANLV_7           |Sens_26Pin.6 |OBD_CANLV.N/C            |      |-  |CAN                                                                                     |
|24V_FrontBoard        |Sens_26Pin.7 |S_24VFrontBoard          |22 AWG|IN |POWER                                                                                   |
|GND_24V_FrontBoard    |Sens_26Pin.8 |S_GND_24V_FrontBoard     |22 AWG|IN |POWER                                                                                   |
|Steering_Sensor       |Sens_26Pin.9 |Steering_Sensor.1        |22 AWG|IN |ANALOG, RM08 super small non-contact rotary encoder                                     |
|5V_Steering_Sensor    |Sens_26Pin.10|Steering_Sensor.2        |22 AWG|OUT|POWER                                                                                   |
|GND_Steering_Sensor   |Sens_26Pin.11|Steering_Sensor.3        |22 AWG|OUT|POWER                                                                                   |
|Brake_Press           |Sens_26Pin.12|Brake_Press.1            |22 AWG|IN |ANALOG, Pressione olio freni REAR - TRASDUTTORE PIEZORESISTIVO DI PRESSIONE SPxx-M10x1  |
|5V_Brake_Press        |Sens_26Pin.13|Brake_Press.2            |22 AWG|OUT|POWER                                                                                   |
|GND_Brake_Press       |Sens_26Pin.14|Brake_Press.3            |22 AWG|OUT|POWER                                                                                   |
|Brake_EXT             |Sens_26Pin.15|BrakeExt.1               |22 AWG|IN |ANALOG, straingauge on the break pedal itself and not on the oil loop                   |
|5V_Brake_EXT          |Sens_26Pin.16|BrakeExt.2               |22 AWG|OUT|POWER                                                                                   |
|GND_Brake_EXT         |Sens_26Pin.17|BrakeExt.3               |22 AWG|OUT|POWER                                                                                   |
|Throttle1             |Sens_26Pin.18|Throttle1_Recep.1        |22 AWG|IN |ANALOG, rotary potentionmeter no datasheet                                              |
|5V_Throttle1          |Sens_26Pin.19|Throttle1_Recep.2        |22 AWG|OUT|POWER                                                                                   |
|GND_Throttle1         |Sens_26Pin.20|Throttle1_Recep.3        |22 AWG|OUT|POWER                                                                                   |
|SensorShut1_PreInertia|Sens_26Pin.21|S_SensorShutPreInertia   |22 AWG|IN |GPIO/EXTI                                                                               |
|SensorShut_PostInertia|Sens_26Pin.22|S_SensorShutPostInertia  |22 AWG|IN |GPIO/EXTI                                                                               |
|Throttle2             |Sens_26Pin.23|Throttle2_Recep.1        |22 AWG|IN |ANALOG, rotary potentionmeter no datasheet                                              |
|SensorShut_PostBOTS   |Sens_26Pin.24|S_SensorShutPostBOTS     |22 AWG|IN |GPIO/EXTI                                                                               |
|SensorShut_postCockpit|Sens_26Pin.25|S_SensorShutPostCockpit  |22 AWG|IN |GPIO/EXTI                                                                               |

### REAR Signals
|Signal Name         |From         |To                       |Gauge |Dir |Notes                                                                                                                          |
|--------------------|-------------|-------------------------|------|----|-------------------------------------------------------------------------------------------------------------------------------|
|24V_RearBoards      |Sens_26Pin.1 |Fuse_Out.14              |22 AWG|IN  |POWER                                                                                                                          |
|24V_RearBoards      |Sens_26Pin.2 |TSAC_LV.17               |22 AWG|IN  |POWER                                                                                                                          |
|GND_RearBoards      |Sens_26Pin.3 |Fuse_Out.15              |22 AWG|IN  |POWER                                                                                                                          |
|GND_RearBoards      |Sens_26Pin.4 |TSAC_LV.18               |22 AWG|IN  |POWER                                                                                                                          |
|CANH_LV2            |Sens_26Pin.5 |TSAC_LV.4                |24 AWG|IN  |CAN                                                                                                                            |
|CANL_LV2            |Sens_26Pin.6 |TSAC_LV.5                |24 AWG|IN  |CAN                                                                                                                            |
|GND_CAN_LV2         |Sens_26Pin.7 |TSAC_LV.6                |22 AWG|IN  |CAN                                                                                                                            |
|CoolingPressSX      |Sens_26Pin.10|Sens_PressCoolingSX.1    |22 AWG|IN  |ANALOG, pressure sensor cooling inverters+motors loop left side,TRASDUTTORE PIEZORESISTIVO DI PRESSIONE SPxx-M10x1, 0.5V - 4.5V|
|5V_CoolingPressSX   |Sens_26Pin.11|Sens_PressCoolingSX.2    |22 AWG|OUT |POWER                                                                                                                          |
|GND_CoolingPressSX  |Sens_26Pin.12|Sens_PressCoolingSX.3    |22 AWG|OUT |POWER                                                                                                                          |
|ShutSens_PostBSPD   |Sens_26Pin.23|Derivation_SX.11         |22 AWG|IN  |GPIO/EXTI                                                                                                                      |
|ShutSens_PreFunghi  |Sens_26Pin.24|S_ShutSens_Inv_RL        |22 AWG|IN  |GPIO/EXTI                                                                                                                      |
|ShutSens_PostInvMono|Sens_26Pin.25|Interlock_Inv_Mono_Plug.1|22 AWG|IN  |GPIO/EXTI                                                                                                                      |
|ShutSens_PostInvFR  |Sens_26Pin.26|ShutSens_PostFR_Plug.1   |22 AWG|IN  |GPIO/EXTI                                                                                                                      |

## J4 <=> SENS_34PIN 

|# |Schematic        |FRONT Signal       | REAR Signal           |
------------------------------------------------------------------
|1 |ANALOG2          |
|2 |ANALOG3          |
|3 |ANALOG4          |
|4 |ANALOG1          |
|5 |NTC2-            |
|6 |NTC2+            |
|7 |NTC1+            |
|8 |NTC1-            |
|9 |NTC3+            |
|10|POTENTIOMETER1   |
|11|Strain +5        |
|12|Strain +5        |
|13|Strain +5        |
|14|DGND             |
|15|DGND             |
|16|DGND             |
|17|THERMOCOUPLE2_CJ2|
|18|POTENTIOMETER2   |
|19|+5 Strain        |
|20|+5 Strain        |
|21|+5 Strain        |
|22|DGND             |
|23|DGND             |
|24|DGND             |
|25|NTC4+            |
|26|NTC5+            |
|27|NTC5-            |
|28|NTC6+            |
|29|NTC6-            |
|30|THERMOCOUPLE1_CJ1|
|31|THERMOCOUPLE1_CJ2|
|32|THERMOCOUPLE2_CJ1|
|33|NTC3-            |
|34|NTC4-            |

### FRONT Signals
|Signal Name           |From         |To                        |Gauge |Dir|Notes                                                                   |
|----------------------|-------------|--------------------------|------|---|------------------------------------------------------------------------|
|NTC9-                 |Sens_34Pin.1 |NTC_Connectors_Recep.1    |22 AWG|IN |ANALOG                                                                  |
|NTC9+                 |Sens_34Pin.2 |NTC_Connectors_Recep.2    |22 AWG|OUT|ANALOG                                                                  |
|NTC10-                |Sens_34Pin.3 |NTC_Connectors_Recep.3    |22 AWG|IN |ANALOG                                                                  |
|NTC10+                |Sens_34Pin.4 |NTC_Connectors_Recep.4    |22 AWG|OUT|ANALOG                                                                  |
|NTC7-                 |Sens_34Pin.5 |NTC7_FL_Recep.1           |22 AWG|IN |ANALOG                                                                  |
|NTC7+                 |Sens_34Pin.6 |NTC7_FL_Recep.2           |22 AWG|OUT|ANALOG                                                                  |
|NTC8-                 |Sens_34Pin.7 |NTC8_FR_Recep.1           |22 AWG|IN |ANALOG                                                                  |
|NTC8+                 |Sens_34Pin.8 |NTC8_FR_Recep.2           |22 AWG|OUT|ANALOG                                                                  |
|Pot_DamperSX          |Sens_34Pin.13|Pot_DamperSX_Recep.1      |22 AWG|IN |ANALOG,inside the wheel suspension, POTENZIOMETRO LINEARE DIA9,5-xx     | 
|5V_PotDamperSX        |Sens_34Pin.14|Pot_DamperSX_Recep.2      |22 AWG|OUT|POWER                                                                   |
|GND_PotDamperSX       |Sens_34Pin.15|Pot_DamperSX_Recep.3      |22 AWG|OUT|POWER                                                                   |
|Pot_DamperDx          |Sens_34Pin.16|Pot_DamperDX_Recep.1      |22 AWG|IN |ANALOG,inside the wheel suspension, POTENZIOMETRO LINEARE DIA9,5-xx     |
|5V_PotDamperDX        |Sens_34Pin.17|Pot_DamperDX_Recep.2      |22 AWG|OUT|POWER                                                                   |
|GND_PotDamperDX       |Sens_34Pin.18|Pot_DamperDX_Recep.3      |22 AWG|OUT|POWER                                                                   |
|Straingauge_PushSX    |Sens_34Pin.19|Straingauge_PushSX_Recep.1|22 AWG|IN |ANALOG, force on front left wheel pushorad ("braccetto"), no-datasheet  |
|5V_Straingauge_PushSX |Sens_34Pin.20|Straingauge_PushSX_Recep.2|22 AWG|OUT|POWER                                                                   |
|GND_Straingauge_PushSX|Sens_34Pin.21|Straingauge_PushSX_Recep.3|22 AWG|OUT|POWER                                                                   |
|Straingauge_PushDX    |Sens_34Pin.22|Straingauge_PushDX_Recep.1|22 AWG|IN |ANALOG, force on front right wheel pushorad ("braccetto"), no-datasheet |
|5V_Straingauge_PushDX |Sens_34Pin.23|Straingauge_PushDX_Recep.2|22 AWG|OUT|POWER                                                                   |
|GND_Straingauge_PushDX|Sens_34Pin.24|Straingauge_PushDX_Recep.3|22 AWG|OUT|POWER                                                                   |
|Straingauge_TieSX     |Sens_34Pin.25|Straingauge_TieSX.1       |22 AWG|IN |ANALOG, force on front left wheel tie road ("braccetto"), no-datasheet  |
|5V_Straingauge_TieSX  |Sens_34Pin.26|Straingauge_TieSX.2       |22 AWG|OUT|POWER                                                                   |
|GND_Straingauge_TieDX |Sens_34Pin.27|Straingauge_TieSX.3       |22 AWG|OUT|POWER                                                                   |
|Straingauge_TieDX     |Sens_34Pin.28|Straingauge_TieDX.1       |22 AWG|IN |ANALOG, force on front right wheel tie road ("braccetto"), no-datasheet |
|5V_Straingauge_TieDX  |Sens_34Pin.29|Straingauge_TieDX.2       |22 AWG|OUT|POWER                                                                   |
|GND_Straingauge_TieDX |Sens_34Pin.30|Straingauge_TieDX.3       |22 AWG|OUT|POWER                                                                   |
|TMC_FL+               |Sens_34Pin.31|Thermocouple_BrakeSX.1    |22 AWG|OUT|ANALOG, front breaks, no-datasheet                                      |
|TMC_FL-               |Sens_34Pin.32|Thermocouple_BrakeSX.2    |22 AWG|IN |ANALOG, front breaks, no-datasheet                                      |
|TMC_FR-               |Sens_34Pin.33|Thermocouple_BrakeDX.1    |22 AWG|OUT|ANALOG, front breaks, no-datasheet                                      |
|TMC_FR+               |Sens_34Pin.34|Thermocouple_BrakeDX.2    |22 AWG|IN |ANALOG, front breaks, no-datasheet                                      |
### REAR Signals
|Signal Name        |From         |To                  |Gauge |Dir|Notes                                                                 |
|-------------------|-------------|--------------------|------|---|----------------------------------------------------------------------|
|PotenziometroDX    |Sens_34Pin.1 |Pot_DamperDX.1      |22 AWG|IN |ANALOG,inside the wheel suspension, POTENZIOMETRO LINEARE DIA9,5-xx   |
|5V_PotenziometroDX |Sens_34Pin.2 |Pot_DamperDX.2      |22 AWG|OUT|POWER                                                                 |
|GND_PotenziometroDX|Sens_34Pin.3 |Pot_DamperDX.3      |22 AWG|OUT|POWER                                                                 |
|PotenziometroSX    |Sens_34Pin.4 |Pot_DamperSX.1      |22 AWG|IN |ANALOG,inside the wheel suspension, POTENZIOMETRO LINEARE DIA9,5-xx   |
|5V_PotenziometroSX |Sens_34Pin.5 |Pot_DamperSX.2      |22 AWG|OUT|POWER                                                                 |
|GND_PotenziometroSX|Sens_34Pin.6 |Pot_DamperSX.3      |22 AWG|OUT|POWER                                                                 |
|StraingaugeDX1     |Sens_34Pin.7 |Straingauge_PushDX.1|22 AWG|IN |ANALOG, force on rear right wheel pushorad ("braccetto"), no-datasheet|
|5V_StraingaugeDX1  |Sens_34Pin.8 |Straingauge_PushDX.2|22 AWG|OUT|POWER                                                                 |
|GND_StraingaugeDX1 |Sens_34Pin.9 |Straingauge_PushDX.3|22 AWG|OUT|POWER                                                                 |
|StraingaugeSX1     |Sens_34Pin.10|Straingauge_PushSX.1|22 AWG|IN |ANALOG, force on rear left wheel pushorad ("braccetto"), no-datasheet |
|5V_StraingaugeSX1  |Sens_34Pin.11|Straingauge_PushSX.2|22 AWG|OUT|POWER                                                                 |
|GND_StraingaugeSX1 |Sens_34Pin.12|Straingauge_PushSX.3|22 AWG|OUT|POWER                                                                 |
|StraingaugeDX2     |Sens_34Pin.13|Straingauge_TieDX.1 |22 AWG|IN |ANALOG, force on rear right wheel tie road ("braccetto"), no-datasheet|
|5V_StraingaugeDX2  |Sens_34Pin.14|Straingauge_TieDX.2 |22 AWG|OUT|POWER                                                                 |
|GND_StraingaugeDX2 |Sens_34Pin.15|Straingauge_TieDX.3 |22 AWG|OUT|POWER                                                                 |
|NTC1+              |Sens_34Pin.16|Rear_Right.1        |22 AWG|OUT|ANALOG                                                                | 
|NTC1-              |Sens_34Pin.17|Rear_Right.2        |22 AWG|IN |ANALOG                                                                |
|StraingaugeSX2     |Sens_34Pin.18|Straingauge_TieSX.1 |22 AWG|IN |ANALOG, force on rear left wheel tie road ("braccetto"), no-datasheet |
|5V_StraingaugeSX2  |Sens_34Pin.19|Straingauge_TieSX.2 |22 AWG|OUT|POWER                                                                 |
|GND_StraingaugeSX2 |Sens_34Pin.20|Straingauge_TieSX.3 |22 AWG|OUT|POWER                                                                 |
|NTC2+              |Sens_34Pin.21|Rear_Right.3        |22 AWG|OUT|ANALOG                                                                |
|NTC2-              |Sens_34Pin.22|Rear_Right.4        |22 AWG|IN |ANALOG                                                                |
|NTC3+              |Sens_34Pin.23|Rear_Right.5        |22 AWG|OUT|ANALOG                                                                |
|NTC3-              |Sens_34Pin.24|Rear_Right.6        |22 AWG|IN |ANALOG                                                                |
|NTC4+              |Sens_34Pin.25|Rear_Right.7        |22 AWG|OUT|ANALOG                                                                |
|NTC5+              |Sens_34Pin.26|NTC5_DX.1           |22 AWG|OUT|ANALOG                                                                |
|NTC5-              |Sens_34Pin.27|NTC5_DX.2           |22 AWG|IN |ANALOG                                                                |
|NTC6+              |Sens_34Pin.28|NTC6_SX.1           |22 AWG|OUT|ANALOG                                                                |
|NTC6-              |Sens_34Pin.29|NTC6_SX.2           |22 AWG|IN |ANALOG                                                                |
|NTC4-              |Sens_34Pin.34|Rear_Right.8        |22 AWG|IN |ANALOG                                                                |

# J5
|#|Schematic  |Notes             |From          |To              |Gauge |
-------------------------------------------------------------------------
|1|ANALOG1    |BrakePress_Rear   |Sens_Segnali.1|BSPD.14         |22 AWG|
|2|ANALOG10   |PressCoolingDX    |Sens_Sensori.1|DerivationDX.1  |22 AWG|
|3|+24        |24V_RearBoards    |Sens_Segnali.7|TLBInverter_LV.2|22 AWG|
|4|BRAKE_LIGHT|BrakeLight_Control|Sens_Segnali.5|DerivationSX.7  |22 AWG|
|5|GND_ESD    |
|6|CAN_H      |CANH_LV           |Sens_Segnali.2|VIBoard_LV.3    |24 AWG|
|7|CAN_L      |CANL_LV           |Sens_Segnali.3|VIBoard_LV.4    |24 AWG|
|8|DGND       |
# J6
|#|Schematic  |Notes             |From          |To              |Gauge |
-------------------------------------------------------------------------
|1|+24        |
|2|SI1926DL D2|
|3|DGND       |
|4|+5         |5V_PressCoolingDX |Sens_Sensori.2|DerivationDX.2  |22 AWG|
|5|GND_ESD    |
|6|BSPD_ERROR |BSPD_Error        |Sens_Segnali.6|BSPD.3          |22 AWG|
|7|DGND       |
|8|+5         |5V_PressCoolingDX |Sens_Sensori.2|DerivationDX.2  |22 AWG|

## Catia
|Notes             |From          |To              |Gauge |
-----------------------------------------------------------
|BrakePress_Rear   |Sens_Segnali.1|BSPD.14         |22 AWG|x ANALOG- Pressione olio freni REAR - senza alimentazioni perche' rilancio dai sensori BSPD - TRASDUTTORE PIEZORESISTIVO DI PRESSIONE SPxx-M10x1
|CANH_LV           |Sens_Segnali.2|VIBoard_LV.3    |24 AWG|x CAN
|CANL_LV           |Sens_Segnali.3|VIBoard_LV.4    |24 AWG|x CAN
|GND_CAN_LV        |Sens_Segnali.4|VIBoard_LV.N/C  |      |- CAN
|BrakeLight_Control|Sens_Segnali.5|DerivationSX.7  |22 AWG|x BRAKE_LIGHT as for schematic - comando da dspace per accendere la brake light - GPIO OUT
|BSPD_Error        |Sens_Segnali.6|BSPD.3          |22 AWG|v BSPD_ERROR as by schematic - in interrupt - funzionamento bspd
|24V_RearBoards    |Sens_Segnali.7|TLBInverter_LV.2|22 AWG|x POWER_OUT -> alimentare schede dentro la derivation box
|GND_RearBoards    |Sens_Segnali.8|TLBInverter_LV.3|22 AWG|x POWER_OUT -> alimentare schede dentro la derivation box
|PressCoolingDX    |Sens_Sensori.1|DerivationDX.1  |22 AWG|x ANALOG_IN (sensore di pressione) (TRASDUTTORE PIEZORESISTIVO DI PRESSIONE SPxx-M10x1) 0.5V - 4.5V - connettore J5
|5V_PressCoolingDX |Sens_Sensori.2|DerivationDX.2  |22 AWG|o PWR_OUT 
|GND_PressCoolingDX|Sens_Sensori.3|DerivationDX.3  |22 AWG|o PWR_OUT
