//#ifndef _UTILS_H
//#define _UTILS_H

void play_tone(int volume, int delay_ms){
    analogWrite(6, volume);
    delay(delay_ms);
    analogWrite(6, 0);
//    delay(delay_ms);
}
