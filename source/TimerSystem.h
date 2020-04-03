#ifndef TIME_H
#define TIME_H

class Time
{
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