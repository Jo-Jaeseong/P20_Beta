/*
 * reservationsystem.h
 *
 *  Created on: Apr 11, 2024
 *      Author: CBT_DEV
 */

#ifndef SRC_PERIPHERAL_RESERVATIONSYSTEM_H_
#define SRC_PERIPHERAL_RESERVATIONSYSTEM_H_

extern int reservationFlag;
extern int reservationRunningFlag;

void ReservationInit();
void CheckReservationTime();
int Calculate_reserve_time();

#endif /* SRC_PERIPHERAL_RESERVATIONSYSTEM_H_ */
