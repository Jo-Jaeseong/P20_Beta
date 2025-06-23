/*
 * temperature.h
 *
 *  Created on: 2022. 10. 20.
 *      Author: CBT
 */

#ifndef SRC_PERIPHERAL_TEMPERATURE_H_
#define SRC_PERIPHERAL_TEMPERATURE_H_

#include <stdio.h>
#include <stdint.h>

extern float Temperature[5];
extern int DoorSettingTemp[3], ChamberSettingTemp[3], ChamberBackSettingTemp[3], VaporizerSettingTemp[3];
extern int CalibrationTemp[4];


uint8_t max6675ReadReg(uint16_t *reg, int Channel);
float max6675Temp(uint16_t reg);
void Check_Temp();
void TempSetting();

#endif /* SRC_PERIPHERAL_TEMPERATURE_H_ */
