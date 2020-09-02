#ifndef TIME_H
#define TIME_H
#include <nds.h>
#include "cmath"

class Time
{
    private:
        char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    public:
        Time(int hours, int minutes, int seconds);
        ~Time();

        int hours,
            minutes,
            seconds,
            vblankConsumed,
            milliseconds;

        void setTime(int hours, int minutes, int seconds){
            this->hours = hours;
            this->minutes = minutes;
            this->seconds = seconds;

            this->milliseconds = 0;
            this->vblankConsumed = 0;
        }

        void setVblankConsumed(int vblankConsumed){
            this->vblankConsumed = vblankConsumed;
        }

        int *getBrokenHours(){
            
            
            static int brokenHours[3];

            for(int i = 2; i >= 0; i--){
                int remainder = (hours/(int)std::pow(10.0, i))%10;
                switch(i){
                    case 2:
                        brokenHours[0] = remainder;
                        break;
                    case 1:
                        brokenHours[1] = remainder;
                        break;
                    case 0:
                        brokenHours[2] = remainder;
                        break;
                }
            }
            return brokenHours;
        }

        int* getBrokenMinutes(){
            static int brokenMinutes[2];
            for(int i = 1; i >= 0; i--){
                int remainder = (minutes/(int)std::pow(10, i))%10;
                switch(i){
                    case 1:
                        brokenMinutes[0] = remainder;
                        break;
                    case 0:
                        brokenMinutes[1] = remainder;
                        break;
                }
            }
            char message[2] = {digits[brokenMinutes[0]], digits[brokenMinutes[1]]};
            nocashMessage(message);
            return brokenMinutes;
        }

        int* getBrokenSeconds(){
            static int brokenSeconds[2];
            for(int i = 1; i >= 0; i--){
                int remainder = (seconds/(int)std::pow(10, i))%10;
                switch(i){
                    case 1:
                        brokenSeconds[0] = remainder;
                        break;
                    case 0:
                        brokenSeconds[1] = remainder;
                        break;
                }
            }
            char message[2] = {digits[brokenSeconds[0]], digits[brokenSeconds[1]]};
            nocashMessage(message);
            return brokenSeconds;
        }

        void tickTimeDown1Vblank(int currentVblankCount){
            milliseconds = milliseconds - ((currentVblankCount/60)*1000);
            if(milliseconds <= 0){
                milliseconds = 999 + milliseconds;
                seconds--;
                if(seconds <= 0){
                    seconds = 59 + seconds;
                    minutes--;
                    if(minutes == 0){
                        hours = 59 + minutes;
                        hours--;
                        if(hours == 0){
                            hours = 23 + hours;
                        }
                    }
                }
            }
        }
};

#endif