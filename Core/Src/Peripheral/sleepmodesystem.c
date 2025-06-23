/*
 * sleepmodesystem.c
 *
 *  Created on: Dec 11, 2024
 *      Author: CBT_DEV
 */
#include "main.h"
#include "sensor.h"
#include "peripheral.h"
#include "hardware.h"

int SleepModeFlag=0;
int SleepModeStatus=0;
int ActiveWeekday[7];
int ActiveModeTime[2][7];
int SleepModeRunning_Flag=0;

int SleepPageCount;

int SleepModeStatusTemp=0;

void SleepModeInit(){
	ActiveWeekday[1]=1;
	ActiveWeekday[2]=1;
	ActiveWeekday[3]=1;
	ActiveWeekday[4]=1;
	ActiveWeekday[5]=1;
	ActiveWeekday[6]=2;
	ActiveWeekday[0]=2;


	ActiveModeTime[0][1]=7;
	ActiveModeTime[0][2]=7;
	ActiveModeTime[0][3]=7;
	ActiveModeTime[0][4]=7;
	ActiveModeTime[0][5]=7;
	ActiveModeTime[0][6]=7;
	ActiveModeTime[0][0]=7;

	ActiveModeTime[1][1]=17;
	ActiveModeTime[1][2]=17;
	ActiveModeTime[1][3]=17;
	ActiveModeTime[1][4]=17;
	ActiveModeTime[1][5]=17;
	ActiveModeTime[1][6]=13;
	ActiveModeTime[1][0]=13;
}

void SleepModeProcess(){
	// 절전모드 활성화 여부 확인
	GetTime();
	if(SleepModeFlag == 1){
	    // 요일별 절전모드 활성화 여부 확인
	    if(ActiveWeekday[today_date.week] == 1){
	        //절전모드 동작 시간대 확인
	        if(today_date.hour>=ActiveModeTime[0][today_date.week] && today_date.hour < ActiveModeTime[1][today_date.week]){
	            //절전모드 비동작 중
	            SleepModeStatus = 0;
	        }
	        else{
	            //절전모드 동작 중
	        	SleepModeStatusTemp = 1;
	            SleepModeStatus = 1;
	        }
	    }
	    else{
	        //절전모드 활성화
        	SleepModeStatusTemp = 1;
	        SleepModeStatus = 1;
	    }
	}
	else{
	    //전체 절전모드 비활성화
	    SleepModeStatus = 0;
	}

	//동작중 절전모드 비활성화
	if(Running_Flag||SelfTestMode){
		SleepModeStatus=0;
	}

	//절전모드 처리
	if(SleepModeStatus==1){
		//히터 컨트롤
		HeaterControlMode=0;

		//절전 화면 처리
		if(SleepPageCount<=10){
			SleepPageCount++;
		}
		if(SleepPageCount==10){
			SleepModeRunning_Flag=1;
			if(currentpage!=LCD_SLEEPMODE_STOP_MESSAGE_PAGE){
				beforepage=currentpage;
				if(currentpage==LCD_RESERVATION_RUNNING_PAGE){
					DisplayPage(LCD_SLEEPMODE_RESERVATION_PAGE);
				}
				else{
					DisplayPage(LCD_SLEEPMODE_PAGE);
				}
			}
		}
	}
	else{
		if(currentpage==LCD_SLEEPMODE_PAGE){
			DisplayPage(beforepage);
		}
		else if(currentpage==LCD_SLEEPMODE_RESERVATION_PAGE){
			DisplayPage(beforepage);
		}
	}
	if(SleepModeStatus == 0 && SleepModeStatusTemp == 1){
		// 절전모드에서 일반모드로 전환될 때
		HeaterControlMode = 1;
		SleepModeStatusTemp = 0;
	}
}

void SleepModeCancel(){
	//절전 모드 해제
	SleepModeFlag=0;
	SleepModeRunning_Flag=0;
	Inithardware();

	DisplayIcon(0x25,0x10,SleepModeFlag);

	DisplayPage(beforepage);
}
