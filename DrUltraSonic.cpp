#include "DrUltraSonic.h"
/*0616に編集*/
#include <Arduino.h>
/*0619*/
#include "M5All-In-One-Gadget.h"

 DrUltraSonic::DrUltraSonic(int echo_pin,int trig_pin)	//	引数で与えられたピン番号を使ってECHOピンを入力、TRIGGERピンを出力に設定する。コンストラクター
    {
        m_echo_pin=echo_pin;
        m_trig_pin=trig_pin;
        pinMode(m_echo_pin,INPUT);
        pinMode(m_trig_pin,OUTPUT);
    }

double DrUltraSonic::measureReturnTime()//超音波が帰ってくるまでの時間取得
{
        double t=0;
    digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);//10us待つ
  digitalWrite(TRIG_PIN, LOW);
  t=pulseIn(ECHO_PIN,HIGH);


    return double(t);
}
