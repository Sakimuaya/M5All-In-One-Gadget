/* インクルードガード */
#pragma once

// アドレス指定
#define SHT31_ADDR 0x45 //温湿度センサーのI2Cアドレス
#define SOFT_RESET_MSB 0x30 //ソフトリセットコマンドのMSB部	
#define SOFT_RESET_LSB 0xA2 //ソフトリセットコマンドのLSB部	
#define CLEAR_STATUS_REGISTER_MSB 0x30 //ステータスレジスタのデータ消去コマンドのMSB部	
#define CLEAR_STATUS_REGISTER_LSB 0x41 //ステータスレジスタのデータ消去コマンドのLSB部	
#define SINGLE_SHOT_HIGH_MSB 0x24  //単発測定コマンドのMSB部
#define SINGLE_SHOT_HIGH_LSB 0x00 //単発測定コマンドのLSB部	

class DrTHSensor // classの定義
{
private: // privateはクラス内からしかアクセスできない
    void initAesht3x();

public: // publicはどこからでもアクセス可能
    void init();
    void getTempHumi(double* temperature, double* humidity);
};
