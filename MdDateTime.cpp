#include "MdDateTime.h"

MdDateTime::MdDateTime()//コンストラクターSerial2を9600bpsで開く。

{
    Serial2.begin(9600);
}

String MdDateTime::readDate()//現在の日付取得
{
    int i = 0;
    char c = 0;
    while (Serial2.available() > 0) {
        c = Serial2.read();
        gps.encode(c);
    }
    char date[11];
    snprintf(date, sizeof(date), "%04d/%02d/%02d", gps.date.year(), gps.date.month(), gps.date.day());
    Serial.println(date);
    return String(date);
}

String MdDateTime::readTime()//現在の時刻取得
{
    int i = 0;
    char c = 0;
    while (Serial2.available() > 0) {
        c = Serial2.read();
        gps.encode(c);
    }
    char time[11];
    snprintf(time, sizeof(time), "%02d:%02d:%02d", gps.time.hour() + 9, gps.time.minute(), gps.time.second());
    Serial.println(time);
    return String(time);
}