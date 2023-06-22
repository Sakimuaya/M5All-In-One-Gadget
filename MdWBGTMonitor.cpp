#include "MdWBGTMonitor.h"

/*0620に編集*/
#include <Arduino.h>
#include "DrTHSensor.h"

DrTHSensor dthsen;//コンストラクタがある場合は右辺にコンストラクター呼び出しを記述。引数がある場合は渡す

void MdWBGTMonitor::init()//温度センサーの初期化
{
dthsen.init();
}

void MdWBGTMonitor::getWBGT(double* temperature,double* humidity,WbgtIndex* index)//取得した温湿度を基に、アラートの分類分けを行う
{
/*double* temperature;//取得した温度を代入する変数のアドレス
double* humidity;//取得した湿度を代入する変数のアドレス
WbgtIndex* index;//アラートを代入する変数のアドレス*/

dthsen.init();
dthsen.getTempHumi(temperature,humidity);//このままだとエラーがおきてしまう
int calc_index=0;//WBGTの計算結果を格納する
calc_index=0.68* *temperature+0.12* *humidity;


//index = 0.68 * 温度[℃] ＋ 0.12 * 湿度[%]

if(calc_index<=15){
    *index=SAFE;
}else if(calc_index<=24){
    *index=ATTENTION;
}else if(calc_index<=27){
    *index=ALERT; 
}else if(calc_index<=30){
    *index=HIGH_ALERT; 
}else if(calc_index>=31){  
    *index=HIGH_ALERT;
}


}//関数の括弧です（あとでコメント消す）