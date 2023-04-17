# SENS_26PIN <=> J3

|# |Schematic      |Notes               |From         |To                       |Gauge |
----------------------------------------------------------------------------------------
|1 |+24            |24V_RearBoards      |Sens_26Pin.1 |Fuse_Out.14              |22 AWG|
|2 |+24            |24V_RearBoards      |Sens_26Pin.2 |TSAC_LV.17               |22 AWG|
|3 |ANALOG9        |
|4 |ANALOG5        |
|5 |ANALOG7        |
|6 |ANALOG8        |
|7 |ANALOG6        |
|8 |CAN_H          |
|9 |CAN_H          |
|10|DGND           |
|11|DGND           |
|12|DGND           |
|13|DGND           |
|14|CANL           |
|15|CANL           |
|16|DGND           |
|17|DGND           |
|18|DGND           |
|19|+5 Steeering   |
|20|SHUTDOWN_IN_1  |
|21|SHUTDOWN_IN_2  |
|22|SHUTDOWN_IN_3  |
|23|SHUTDOWN_IN_4  |
|24|+5 Brake Press |
|25|+5 Strain Brake|
|26|+5 Throttle    |

|Notes               |From         |To                       |Gauge |
---------------------------------------------------------------------
|24V_RearBoards      |Sens_26Pin.1 |Fuse_Out.14              |22 AWG|x
|24V_RearBoards      |Sens_26Pin.2 |TSAC_LV.17               |22 AWG|x
|GND_RearBoards      |Sens_26Pin.3 |Fuse_Out.15              |22 AWG|x
|GND_RearBoards      |Sens_26Pin.4 |TSAC_LV.18               |22 AWG|x
|CANH_LV2            |Sens_26Pin.5 |TSAC_LV.4                |24 AWG|
|CANL_LV2            |Sens_26Pin.6 |TSAC_LV.5                |24 AWG|
|GND_CAN_LV2         |Sens_26Pin.7 |TSAC_LV.6                |22 AWG|
|CoolingPressSX      |Sens_26Pin.10|Sens_PressCoolingSX.1    |22 AWG|
|5V_CoolingPressSX   |Sens_26Pin.11|Sens_PressCoolingSX.2    |22 AWG|
|GND_CoolingPressSX  |Sens_26Pin.12|Sens_PressCoolingSX.3    |22 AWG|
|ShutSens_PostBSPD   |Sens_26Pin.23|Derivation_SX.11         |22 AWG|
|ShutSens_PreFunghi  |Sens_26Pin.24|S_ShutSens_Inv_RL        |22 AWG|
|ShutSens_PostInvMono|Sens_26Pin.25|Interlock_Inv_Mono_Plug.1|22 AWG|
|ShutSens_PostInvFR  |Sens_26Pin.26|ShutSens_PostFR_Plug.1   |22 AWG|

# SENS_34PIN <=> J4
|Notes              |From         |To                  |Gauge |
---------------------------------------------------------------
|PotenziometroDX    |Sens_34Pin.1 |Pot_DamperDX.1      |22 AWG|
|5V_PotenziometroDX |Sens_34Pin.2 |Pot_DamperDX.2      |22 AWG|
|GND_PotenziometroDX|Sens_34Pin.3 |Pot_DamperDX.3      |22 AWG|
|PotenziometroSX    |Sens_34Pin.4 |Pot_DamperSX.1      |22 AWG|
|5V_PotenziometroSX |Sens_34Pin.5 |Pot_DamperSX.2      |22 AWG|
|GND_PotenziometroSX|Sens_34Pin.6 |Pot_DamperSX.3      |22 AWG|
|StraingaugeDX1     |Sens_34Pin.7 |Straingauge_PushDX.1|22 AWG|
|5V_StraingaugeDX1  |Sens_34Pin.8 |Straingauge_PushDX.2|22 AWG|
|GND_StraingaugeDX1 |Sens_34Pin.9 |Straingauge_PushDX.3|22 AWG|
|StraingaugeSX1     |Sens_34Pin.10|Straingauge_PushSX.1|22 AWG|
|5V_StraingaugeSX1  |Sens_34Pin.11|Straingauge_PushSX.2|22 AWG|
|GND_StraingaugeSX1 |Sens_34Pin.12|Straingauge_PushSX.3|22 AWG|
|StraingaugeDX2     |Sens_34Pin.13|Straingauge_TieDX.1 |22 AWG|
|5V_StraingaugeDX2  |Sens_34Pin.14|Straingauge_TieDX.2 |22 AWG|
|GND_StraingaugeDX2 |Sens_34Pin.15|Straingauge_TieDX.3 |22 AWG|
|NIC1+              |Sens_34Pin.16|Rear_Right.1        |22 AWG|
|NIC1-              |Sens_34Pin.17|Rear_Right.2        |22 AWG|
|StraingaugeSX2     |Sens_34Pin.18|Straingauge_TieSX.1 |22 AWG|
|5V_StraingaugeSX2  |Sens_34Pin.19|Straingauge_TieSX.2 |22 AWG|
|GND_StraingaugeSX2 |Sens_34Pin.20|Straingauge_TieSX.3 |22 AWG|
|NTC2+              |Sens_34Pin.21|Rear_Right.3        |22 AWG|
|NTC2-              |Sens_34Pin.22|Rear_Right.4        |22 AWG|
|NTC3+              |Sens_34Pin.23|Rear_Right.5        |22 AWG|
|NTC3-              |Sens_34Pin.24|Rear_Right.6        |22 AWG|
|NTC4+              |Sens_34Pin.25|Rear_Right.7        |22 AWG|
|NTC5+              |Sens_34Pin.26|NTC5_DX.1           |22 AWG|
|NTC5-              |Sens_34Pin.27|NTC5_DX.2           |22 AWG|
|NTC6+              |Sens_34Pin.28|NTC6_SX.1           |22 AWG|
|NTC6-              |Sens_34Pin.29|NTC6_SX.2           |22 AWG|
|NTC4-              |Sens_34Pin.34|Rear_Right.8        |22 AWG|

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

|Notes             |From          |To              |Gauge |
-----------------------------------------------------------
|BrakePress_Rear   |Sens_Segnali.1|BSPD.14         |22 AWG|x
|CANH_LV           |Sens_Segnali.2|VIBoard_LV.3    |24 AWG|x
|CANL_LV           |Sens_Segnali.3|VIBoard_LV.4    |24 AWG|x
|GND_CAN_LV        |Sens_Segnali.4|VIBoard_LV.N/C  |      |-
|BrakeLight_Control|Sens_Segnali.5|DerivationSX.7  |22 AWG|x
|BSPD_Error        |Sens_Segnali.6|BSPD.3          |22 AWG|v
|24V_RearBoards    |Sens_Segnali.7|TLBInverter_LV.2|22 AWG|x
|GND_RearBoards    |Sens_Segnali.8|TLBInverter_LV.3|22 AWG|
|PressCoolingDX    |Sens_Sensori.1|DerivationDX.1  |22 AWG|x
|5V_PressCoolingDX |Sens_Sensori.2|DerivationDX.2  |22 AWG|o
|GND_PressCoolingDX|Sens_Sensori.3|DerivationDX.3  |22 AWG|
