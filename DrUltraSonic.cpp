#include "DrUltraSonic.h"
/*0616に編集*/
#include <Arduino.h>

 DrUltraSonic::DrUltraSonic(int echo_pin,int trig_pin)	//	引数で与えられたピン番号を使ってECHOピンを入力、TRIGGERピンを出力に設定する。
    {
        pinMode(echo_pin,INPUT);
        pinMode(trig_pin,OUTPUT);
    }

double DrUltraSonic::measureReturnTime()//超音波が帰ってくるまでの時間取得
{
    double t=0;//超音波が返ってくるまでの時間をμ秒単位で格納　現在はとりあえずゼロを代入している。
    return double(t);
}
