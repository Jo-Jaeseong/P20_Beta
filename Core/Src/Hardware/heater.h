/*
 * heater.h
 *
 *  Created on: Nov 10, 2022
 *      Author: CBT
 */

#ifndef SRC_HARDWARE_HEATER_H_
#define SRC_HARDWARE_HEATER_H_


#define State1			0
#define State2			1
#define State3			2


extern int TestTempErrorValue;

	/*
	 *
	#define State1			0	슬립
	#define State2			1	대기
	#define State3			2	공정
	*/


void DoorHeater(int onoff);
void ChamberHeater(int onoff);
void ChamberBackHeater(int onoff);
void VaporizerHeater(int onoff);

void HeaterControl();

int DoorHeaterCheck();
int ChamberHeaterCheck();
int ChamberBackHeaterCheck();
int VaporizerHeaterCheck();

#endif /* SRC_HARDWARE_HEATER_H_ */
