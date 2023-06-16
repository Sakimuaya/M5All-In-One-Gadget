#include "MdMeasureDistance.h"
/*0616に編集*/
#include <Arduino.h>



/*

/*超音波測定用関数
double measureDistance()//距離測定する関数
 {
   double tm=0;
  double kyori=0;

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);//10us待つ
  digitalWrite(TRIG_PIN, LOW);

tm=pulseIn(ECHO_PIN,HIGH);
if(tm>=0){
  kyori=(340.0/1000000)*tm*0.5*100;//mなのでｃｍに直している
}

return kyori;
  
}

*/