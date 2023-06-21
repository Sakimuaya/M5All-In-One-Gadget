/* インクルードガード */
#pragma once
/*0621*/
#include "M5All-In-One-Gadget.h"
#include <M5Stack.h>

class MdWBGTMonitor // classの定義
{
private: // privateはクラス内からしかアクセスできない
public: // publicはどこからでもアクセス可能
    void init();
    void getWBGT(double* temperature,double* humidity,WbgtIndex* index);

};
