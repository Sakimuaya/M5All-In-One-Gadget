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
WbgtIndex* index;//アラートを代入する変数のアドレス*///これがわからない状態
int calc_index=0;//WBGTの計算結果を格納する

//index = 0.68 * 温度[℃] ＋ 0.12 * 湿度[%]

}