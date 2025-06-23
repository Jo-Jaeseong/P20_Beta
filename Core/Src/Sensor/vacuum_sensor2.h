/*
 * adc.h
 *
 *  Created on: Oct 25, 2022
 *      Author: CBT
 */

#ifndef SRC_PERIPHERAL_VACUUM_SENSOR_H_
#define SRC_PERIPHERAL_VACUUM_SENSOR_H_

//extern int Pressure;
extern float Pressure;
extern int CalibrationVacuum;
extern int DoorOpenPressure;
extern int PreesureCondition[3];

void Read_Vacuumsensor();
void Init_Vacuumsensor();
void RS485_TX_ENABLE();
void RS485_TX_DISABLE();

#endif /* SRC_PERIPHERAL_VACUUM_SENSOR_H_ */
