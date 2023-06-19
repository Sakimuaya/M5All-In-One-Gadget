#include "MdMeasureDistance.h"

/*0616に編集*/
#include <Arduino.h>
#include "M5All-In-One-Gadget.h"
#include "DrUltraSonic.h"


DrUltraSonic drultraa = DrUltraSonic(ECHO_PIN,TRIG_PIN);



double MdMeasureDistance::getDistance()//変数distanceに超音波センサーから取得した値を距離(cm単位)に変換して格納する。
{
    
    double distance=0;


if(drultraa.measureReturnTime()>=0){
  distance=(340.0/1000000)*drultraa.measureReturnTime()*0.5*100;//mなのでｃｍに直している//

    return double(distance);
}
}

/*

/*超音波測定用関数
    double tm=0;
  double distance=0;
    digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);//10us待つ
  digitalWrite(TRIG_PIN, LOW);

  tm=pulseIn(ECHO_PIN,HIGH);
if(tm>=0){
  distance=(340.0/1000000)*tm*0.5*100;//mなのでｃｍに直している

*/