/*
 * reservationsystem.c
 *
 *  Created on: Apr 11, 2024
 *      Author: CBT_DEV
 */

#include "main.h"
#include "sensor.h"
#include "peripheral.h"
#include "hardware.h"

int reservationFlag;
int reservationRunningFlag=0;


void ReservationInit(){
	reservationRunningFlag=0;
	reserve_date.year=today_date.year;
	reserve_date.month=today_date.month;
	reserve_date.day=today_date.day;
	reserve_date.hour=today_date.hour;
	reserve_date.minute=today_date.minute;
}


void CheckReservationTime(){
	if(reservationRunningFlag){
		if(reserve_date.month == today_date.month&&reserve_date.day == today_date.day&&reserve_date.hour == today_date.hour&&reserve_date.minute == today_date.minute){
			//알람 체크 다시한 후 스타트
			if(Alarm_Check()==0){
				StartProcess();
				DisplayPage(LCD_RUNNING_PAGE);
			}
			else{
				if(devicealarm[1]==1){
					DisplayPage(LCD_ALARM1_PAGE);
				}
				else if(devicealarm[2]==1){
					DisplayPage(LCD_ALARM2_PAGE);
				}
				else if(devicealarm[3]==1){
					DisplayPage(LCD_ALARM2_PAGE);
				}
				else if(devicealarm[4]==1){
					DisplayPage(LCD_ALARM2_PAGE);
				}
				else if(devicealarm[5]==1){
					DisplayPage(LCD_ALARM2_PAGE);
				}
				else if(devicealarm[11]==1){
					DisplayPage(LCD_ALARM4_PAGE);
				}
				else if(devicealarm[12]==1){
					DisplayPage(LCD_ALARM4_PAGE);
				}
				else if(devicealarm[13]==1){
					DisplayPage(LCD_ALARM4_PAGE);
				}
				else if(devicealarm[6]==1){
					DisplayPage(LCD_ALARM3_PAGE);
				}
				else if(devicealarm[7]==1){
					DisplayPage(LCD_ALARM3_PAGE);
				}
				else if(devicealarm[8]==1){
					DisplayPage(LCD_ALARM3_PAGE);
				}
				else if(devicealarm[9]==1){
					DisplayPage(LCD_ALARM3_PAGE);
				}
				else{
					DisplayPage(LCD_ALARM2_PAGE);
				}
			}
			reservationRunningFlag=0;
		}
	}
}

int Calculate_reserve_time(){
	reserve_date.week=getDayOfWeek(reserve_date.year,reserve_date.month,reserve_date.day);
    // 날짜 비교

    if ((reserve_date.month > today_date.month)||(reserve_date.month == today_date.month && reserve_date.day > today_date.day)) {
        // 예약 날짜가 오늘 날짜보다 미래인 경우
    	if(SleepModeFlag==1){
    		if(ActiveWeekday[reserve_date.week] == 1){
    			//예약 시간 확인
    			if(reserve_date.hour>=ActiveModeTime[0][reserve_date.week]+1 && reserve_date.hour<ActiveModeTime[1][reserve_date.week]){
    				//예약 가능
    				return 1;
    			}
    			else{
    				//절전 모드 충돌 예약 불가
    				return 2;
    			}
    		}
    		else{
    			//절전 모드 충돌 예약 불가
    			return 2;
    		}
    	}
    	else{
    		return 1;
    	}
    }
    else if (reserve_date.month == today_date.month &&reserve_date.day == today_date.day) {
	   // 예약 날짜가 오늘 날짜인 경우
	   int minutes_diff = (reserve_date.hour * 60 + reserve_date.minute) - (today_date.hour * 60 + today_date.minute);
	   if (minutes_diff >= 10) {
	    	if(SleepModeFlag==1){
	    		if(ActiveWeekday[reserve_date.week] == 1){
	    			//예약 시간 확인
	    			if(reserve_date.hour>=ActiveModeTime[0][reserve_date.week]+1 && reserve_date.hour<ActiveModeTime[1][reserve_date.week]){
	    				//예약 가능
	    				return 1;
	    			}
	    			else{
	    				//절전 모드 충돌 예약 불가
	    				return 2;
	    			}
	    		}
	    		else{
	    			//절전 모드 충돌 예약 불가
	    			return 2;
	    		}
	    	}
	    	else{
	    		return 1;
	    	}
	   } else {
		   return 0; // 10분 이하로 남음
	   }
	}
    else {
		return 0; // 예약 날짜가 현재 날짜보다 이전인 경우
	}
}

int getDayOfWeek(int year, int month, int day) {
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	year -= month < 3;
	return (year + year/4 - year/100 + year/400 + t[month-1] + day) % 7;
}
