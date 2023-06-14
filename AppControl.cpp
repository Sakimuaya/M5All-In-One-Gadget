#include "AppControl.h"
#include <Arduino.h>
#include <M5Stack.h>

MdLcd mlcd;
MdWBGTMonitor mwbgt;//温度センサー
MdMusicPlayer mmplay;//
MdMeasureDistance mmdist;
MdDateTime mdtime;

const char* g_str_orange[] = {
    COMMON_ORANGE0_IMG_PATH,
    COMMON_ORANGE1_IMG_PATH,
    COMMON_ORANGE2_IMG_PATH,
    COMMON_ORANGE3_IMG_PATH,
    COMMON_ORANGE4_IMG_PATH,
    COMMON_ORANGE5_IMG_PATH,
    COMMON_ORANGE6_IMG_PATH,
    COMMON_ORANGE7_IMG_PATH,
    COMMON_ORANGE8_IMG_PATH,
    COMMON_ORANGE9_IMG_PATH,
};

const char* g_str_blue[] = {
    COMMON_BLUE0_IMG_PATH,
    COMMON_BLUE1_IMG_PATH,
    COMMON_BLUE2_IMG_PATH,
    COMMON_BLUE3_IMG_PATH,
    COMMON_BLUE4_IMG_PATH,
    COMMON_BLUE5_IMG_PATH,
    COMMON_BLUE6_IMG_PATH,
    COMMON_BLUE7_IMG_PATH,
    COMMON_BLUE8_IMG_PATH,
    COMMON_BLUE9_IMG_PATH,
};

void AppControl::setBtnAFlg(bool flg)
{
    m_flag_btnA_is_pressed = flg;
}

void AppControl::setBtnBFlg(bool flg)
{
    m_flag_btnB_is_pressed = flg;
}

void AppControl::setBtnCFlg(bool flg)
{
    m_flag_btnC_is_pressed = flg;
}

void AppControl::setBtnAllFlgFalse()
{
    m_flag_btnA_is_pressed = false;
    m_flag_btnB_is_pressed = false;
    m_flag_btnC_is_pressed = false;
}

State AppControl::getState()
{
    return m_state;
}

void AppControl::setState(State state)
{
    m_state = state;
}

Action AppControl::getAction()
{
    return m_action;
}

void AppControl::setAction(Action action)
{
    m_action = action;
}

void AppControl::setStateMachine(State state, Action action)
{
    setState(state);
    setAction(action);
}

FocusState AppControl::getFocusState()//この変数の役割がわからない状態（変数ほしいときにそのままよびだすのはNG?)
{
    return m_focus_state;
}

void AppControl::setFocusState(FocusState fs)//多分フォーカス変数変更設定
{
    m_focus_state = fs;
}

void AppControl::displayTitleInit()
{
    mlcd.displayJpgImageCoordinate(TITLE_IMG_PATH,TITLE_X_CRD,TITLE_Y_CRD);
   
}

void AppControl::displayMenuInit()
{
    /*0609に編集*/
   
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH,MENU_DOWN_X_CRD,MENU_DOWN_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH,MENU_DECIDE_X_CRD,MENU_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH,MENU_UP_X_CRD,MENU_UP_Y_CRD);
}

void AppControl::focusChangeImg(FocusState current_state, FocusState next_state)//現在フォーカスの項目、次のフォーカスの項目
{
    /*0612に編集*/ /*0613に編集*/
    M5.Lcd.clear();//画面を消す関数みつけたらそれに変更
     mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH,MENU_DOWN_X_CRD,MENU_DOWN_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH,MENU_DECIDE_X_CRD,MENU_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH,MENU_UP_X_CRD,MENU_UP_Y_CRD);
    
    /*熱中症フォーカス時*/
    if(current_state==MENU_WBGT)
    {
    mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
         if(next_state==MENU_DATE)
        {   //データフォーカス移動
             mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
             mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
         }
        else if(current_state==MENU_WBGT&&next_state==MENU_MUSIC)
        {//音楽フォーカス移動
             mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
          mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
         }
    }
         /*ミュージックフォーカス時*/
    else if(current_state==MENU_MUSIC)
     {
    mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
        if(next_state==MENU_WBGT)
         {//熱中症フォーカス移動
         mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
         mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
         }
         else if(next_state==MENU_MEASURE)
        {//距離フォーカス移動
                mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
         mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
         }
     }
         /*ミュージック↑*/
        /*距離測定↓**/
     else if(current_state==MENU_MEASURE)
     {
    mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
        mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
        if(next_state==MENU_MUSIC)
        {//音楽フォーカス移動
             mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
            mlcd.displayJpgImageCoordinate(MENU_MUSIC_FOCUS_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
        }
        else if(next_state==MENU_DATE)
        {//時刻フォーカス移動
            mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
            mlcd.displayJpgImageCoordinate(MENU_DATE_FOCUS_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
        }
     }
        /*距離測定↑*/
        /*時刻表示↓*/
     else if(current_state==MENU_DATE)
     {
        mlcd.displayJpgImageCoordinate(MENU_DATE_IMG_PATH,MENU_PATH_X_CRD,MENU_PATH_Y_CRD);
        mlcd.displayJpgImageCoordinate(MENU_MUSIC_IMG_PATH,MENU_MUSIC_X_CRD,MENU_MUSIC_Y_CRD);
        if(next_state==MENU_WBGT)
        {//熱中症フォーカス移動
            mlcd.displayJpgImageCoordinate(MENU_MEASURE_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
            mlcd.displayJpgImageCoordinate(MENU_WBGT_FOCUS_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
        }
        else
        {//距離フォーカス移動
             mlcd.displayJpgImageCoordinate(MENU_WBGT_IMG_PATH,MENU_WBGT_X_CRD,MENU_WBGT_Y_CRD);
            mlcd.displayJpgImageCoordinate(MENU_MEASURE_FOCUS_IMG_PATH,MENU_MEASURE_X_CRD,MENU_MEASURE_Y_CRD);
        }
     }



}

void AppControl::displayWBGTInit()
{//0613に編集//
       M5.Lcd.clear();//画面を消す関数みつけたらそれに変更
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,BUCK_X_CRD,BUCK_Y_CRD);//戻るボタン
    mlcd.displayJpgImageCoordinate(WBGT_TEMPERATURE_IMG_PATH,WBGT_TEMPERATURE_X_CRD,WBGT_TEMPERATURE_Y_CRD);//温度
    mlcd.displayJpgImageCoordinate(WBGT_DEGREE_IMG_PATH,WBGT_DEGREE_X_CRD,WBGT_DEGREE_Y_CRD);//ｃ//なぜか表示されない
    mlcd.displayJpgImageCoordinate(WBGT_HUMIDITY_IMG_PATH,WBGT_HUMIDITY_X_CRD,WBGT_HUMIDITY_Y_CRD);//湿度
     mlcd.displayJpgImageCoordinate(WBGT_PERCENT_IMG_PATH,WBGT_PERCENT_X_CRD,WBGT_PERCENT_Y_CRD);//%
displayTempHumiIndex();

}   

void AppControl::displayTempHumiIndex()//熱中症モニタの画面に温度・湿度・アラートを描画する
{

}

void AppControl::displayMusicInit()//おんがく初期画面
{
    //void M5.Lcd.fillScreen(WHITE);
    M5.Lcd.clear();//画面を消す関数みつけたらそれに変更
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,BUCK_X_CRD,BUCK_Y_CRD);//戻るボタン
    mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOWSTOPPING_X_CRD,MUSIC_NOWSTOPPING_Y_CRD);//now stoping
}

void AppControl::displayMusicStop()//停止画面表示
{
     mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOWSTOPPING_X_CRD,MUSIC_NOWSTOPPING_Y_CRD);//now stoping
}

void AppControl::displayMusicTitle()//音楽タイトル描写
{
    
    MdMusicPlayer musicPlayer;
    char* title = musicPlayer.getTitle();
    mlcd.displayText(title, 10, 120);
}

void AppControl::displayNextMusic()
{
}

void AppControl::displayMusicPlay()
{
}

void AppControl::displayMeasureInit()
{
}

void AppControl::displayMeasureDistance()
{
}

void AppControl::displayDateInit()
{
}

void AppControl::displayDateUpdate()
{
}

void AppControl::controlApplication()
{
    while (1) {

        switch (getState()) {
        case TITLE:
            switch (getAction()) {
            case ENTRY:
                /*
                ** まずはここにタイトル画面の表示処理を呼び出してみよう。
                ** タイトル画面表示の関数はdisplayTitleInit()である。
                ** この関数の中身はまだ何もないので、この関数にタイトル画面表示処理を書いてみよう。
                */
                displayTitleInit();
                setStateMachine(TITLE,DO);

                break;

            case DO:
                  if(m_flag_btnA_is_pressed==true||m_flag_btnB_is_pressed==true||m_flag_btnC_is_pressed==true)
                  {setStateMachine(TITLE,EXIT);}
                  else{}
                  AppControl::setBtnAllFlgFalse();
                break;

            case EXIT:
             M5.Lcd.clear();//画面を消す関数みつけたらそれに変更
                setStateMachine(MENU,ENTRY);
            
                break;

            default:
                break;
            }

            break;

        case MENU:

            switch (getAction()) {
            case ENTRY:
                displayMenuInit();
                setStateMachine(MENU,DO);
                break;

            case DO:
//最初のifは現在のフォーカスで分岐、次のifは押したボタンで分岐
           //熱中症フォーカス//
            if(getFocusState()==MENU_WBGT)
            {    Serial.println("熱中症フォーカス");
                //Aボタンは↑、Cボタンは↓
                //下のifは熱中症フォーカスの時の内容。↓
                if(m_flag_btnA_is_pressed==true)
                {
                AppControl::setBtnAllFlgFalse();
                focusChangeImg(MENU_WBGT, MENU_DATE);
                setFocusState(MENU_DATE);
                 }
                 if(m_flag_btnC_is_pressed==true)
                 {
                  AppControl::setBtnAllFlgFalse();
                  focusChangeImg(MENU_WBGT, MENU_MUSIC);
                  setFocusState(MENU_MUSIC);
                 }
                  if(m_flag_btnB_is_pressed==true)
                   {
                AppControl::setBtnAllFlgFalse();
                setStateMachine(MENU,EXIT);
                  }
            }
                    /*熱中症フォーカス↑*/
                    /*ミュージックフォーカス時の表示*/
            else if(getFocusState()==MENU_MUSIC)
            {    Serial.println("音楽フォーカス");
                //下のifはミュージックフォーカスの時の内容。↓
                if(m_flag_btnA_is_pressed==true)
                {
                AppControl::setBtnAllFlgFalse();
                focusChangeImg(MENU_MUSIC, MENU_WBGT);
                setFocusState(MENU_WBGT);
                 }
                 if(m_flag_btnC_is_pressed==true)
                 {
                  AppControl::setBtnAllFlgFalse();
                  focusChangeImg(MENU_MUSIC, MENU_MEASURE);
                  setFocusState(MENU_MEASURE);
                 }
                  if(m_flag_btnB_is_pressed==true)
                   {
                AppControl::setBtnAllFlgFalse();
                setStateMachine(MENU,EXIT);
                  }
            }
            //ミュージック↑//
            //距離測定フォーカス//
            else if(getFocusState()==MENU_MEASURE)
            {    Serial.println("距離フォーカス");
                if(m_flag_btnA_is_pressed==true)
                {
                AppControl::setBtnAllFlgFalse();
                focusChangeImg(MENU_MEASURE, MENU_MUSIC);
                setFocusState(MENU_MUSIC);
                 }
                 if(m_flag_btnC_is_pressed==true)
                 {
                  AppControl::setBtnAllFlgFalse();
                  focusChangeImg(MENU_MEASURE, MENU_DATE);
                  setFocusState(MENU_DATE);
                 }
                  if(m_flag_btnB_is_pressed==true)
                   {
                AppControl::setBtnAllFlgFalse();
                displayWBGTInit();
                setStateMachine(MENU,EXIT);
                  }
            }
            //距離測定↑//
            //時刻表示//
            else if(getFocusState()==MENU_DATE)
            {    Serial.println("時刻フォーカス");
           if(m_flag_btnA_is_pressed==true)
                {
                AppControl::setBtnAllFlgFalse();
                  focusChangeImg(MENU_DATE, MENU_MEASURE);
                  setFocusState(MENU_MEASURE);
                 }
                 if(m_flag_btnC_is_pressed==true)
                 {
                  AppControl::setBtnAllFlgFalse();
                focusChangeImg(MENU_DATE, MENU_WBGT);
                setFocusState(MENU_WBGT);
                 }
                 if(m_flag_btnB_is_pressed==true)
                   {
                AppControl::setBtnAllFlgFalse();
                displayWBGTInit();
                setStateMachine(MENU,EXIT);
                  }

            }
            //時刻表示↑//
                break;
            
            case EXIT:
           switch (getFocusState()) {
            case MENU_WBGT :
            setStateMachine(WBGT,ENTRY);
            break;

              case MENU_MUSIC:
            setStateMachine(MUSIC_STOP,ENTRY);
            break;

              case MENU_MEASURE:
            setStateMachine(MEASURE,ENTRY);
            break;

            default:
            setStateMachine(DATE,ENTRY);
                break;

           }

            default:
                break;
            
         }
            break;



//ここからはそれぞれのメニューの中身//
        case WBGT:

            switch (getAction()) {
            case ENTRY:
            displayWBGTInit();
            setStateMachine(WBGT,DO);
                break;

            case DO:
           
            if(m_flag_btnB_is_pressed==true)
            {
            AppControl::setBtnAllFlgFalse();
            setStateMachine(WBGT,EXIT);
            }
                break;

            case EXIT:
            setStateMachine(MENU,ENTRY);
                break;

            default:
                break;
            }

            break;

        case MUSIC_STOP:
            switch (getAction()) {
            case ENTRY:
            displayMusicInit();
            setStateMachine(MUSIC_STOP,DO);

                break;

            case DO: 
            displayMusicTitle();
            displayMusicStop();
            if(m_flag_btnB_is_pressed==true)
            {
            setStateMachine(MUSIC_STOP,EXIT);
            }

                break;

            case EXIT:
            if(m_flag_btnB_is_pressed==true)
            {
                AppControl::setBtnAllFlgFalse();
            setStateMachine(MENU,ENTRY);
            }

                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case MEASURE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

            break;

        case DATE:

            switch (getAction()) {
            case ENTRY:
                break;

            case DO:
                break;

            case EXIT:
                break;

            default:
                break;
            }

        default:
            break;
        }
    }
}
