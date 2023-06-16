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
    /*0612に編集*/ /*0613に編集*//*
    M5.Lcd.clear();//画面を消す関数みつけたらそれに変更
     mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DOWN_IMG_PATH,MENU_DOWN_X_CRD,MENU_DOWN_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_DECIDE_IMG_PATH,MENU_DECIDE_X_CRD,MENU_DECIDE_Y_CRD);
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_UP_IMG_PATH,MENU_UP_X_CRD,MENU_UP_Y_CRD);
    重ね張りいけたので上記のものはなかったことに*/
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
     mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,WBGT_BACK_X_CRD,WBGT_BACK_Y_CRD);//戻るボタン
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
    mlcd.fillBackgroundWhite();

}

void AppControl::displayMusicStop()//停止画面表示
{
     mlcd.displayJpgImageCoordinate(MUSIC_NOWSTOPPING_IMG_PATH,MUSIC_NOTICE_X_CRD,MUSIC_NOTICE_Y_CRD);//now stoping
         mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,MUSIC_BACK_X_CRD,MUSIC_BACK_Y_CRD);//戻るボタン
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_NEXT_IMG_PATH,MUSIC_NEXT_X_CRD,MUSIC_NEXT_Y_CRD);//次の曲
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_PLAY_IMG_PATH,MUSIC_PLAY_X_CRD,MUSIC_PLAY_Y_CRD);//再生ボタン
}

void AppControl::displayMusicTitle()//音楽タイトル描写
{
     
    mlcd.displayText(mmplay.getTitle(), MUSIC_TITLE_X_CRD, MUSIC_TITLE_Y_CRD);
}

void AppControl::displayNextMusic()//次のファイルを描写する
{
    mmplay.selectNextMusic();//取得したタイトルをつぎのタイトルに変更していると予想
    displayMusicTitle();

}

void AppControl::displayMusicPlay()//音楽再生画面の描写
{
         mlcd.fillBackgroundWhite();
         mlcd.displayJpgImageCoordinate(MUSIC_NOWPLAYING_IMG_PATH,MUSIC_NOTICE_X_CRD,MUSIC_NOTICE_Y_CRD);//now playing
            mlcd.displayJpgImageCoordinate(COMMON_BUTTON_STOP_IMG_PATH,MUSIC_STOP_X_CRD,MUSIC_STOP_Y_CRD);//停止ボタン	
/*0615にかいたもの*/
        // mmplay.prepareMP3();
      // if( ! mmplay.isRunningMP3())
      // {
      //  mmplay.playMP3();
      // }
      
}

void AppControl::displayMeasureInit()//距離の初期画面
{
    mlcd.fillBackgroundWhite();//画面を白く
   mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,MEASURE_BACK_X_CRD,MEASURE_BACK_Y_CRD);//戻るボタン
    mlcd.displayJpgImageCoordinate(MEASURE_NOTICE_IMG_PATH,MEASURE_NOTICE_X_CRD,MEASURE_NOTICE_Y_CRD);//測定中の画面

}

void AppControl::displayMeasureDistance()//測定した距離を画面に出す
{
}

void AppControl::displayDateInit()//時刻の初期画面
{
    mlcd.fillBackgroundWhite();
    mlcd.displayJpgImageCoordinate(COMMON_BUTTON_BACK_IMG_PATH,DATE_BACK_X_CRD,DATE_BACK_Y_CRD);//戻るボタン
    mlcd.displayJpgImageCoordinate(DATE_NOTICE_IMG_PATH,DATE_NOTICE_X_CAD,DATE_NOTICE_Y_CAD);//文字
}

void AppControl::displayDateUpdate()//現在の時刻の描写
{
}

void AppControl::controlApplication()//すべての機能のコントロール
{
    mmplay.init();
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
            displayMusicInit();//初期画面
            displayMusicTitle();//タイトル描写
            setStateMachine(MUSIC_STOP,DO);
                break;

            case DO: 
            
            displayMusicStop();
            if(m_flag_btnB_is_pressed==true)//戻るボタンを押したとき
            {
            setStateMachine(MUSIC_STOP,EXIT);
            }
            else if(m_flag_btnC_is_pressed==true)//次の曲ボタンを押したとき、
            {
               displayNextMusic();
                AppControl::setBtnAllFlgFalse();


            }
            else if (m_flag_btnA_is_pressed==true)
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
            else  if(m_flag_btnA_is_pressed==true)
            {
                AppControl::setBtnAllFlgFalse();
            setStateMachine(MUSIC_PLAY,ENTRY);
            }

                break;

            default:
                break;
            }

            break;

        case MUSIC_PLAY:

            switch (getAction()) {
            case ENTRY:
                displayMusicPlay();

            setStateMachine(MUSIC_PLAY,DO);
                break;

            case DO:
            displayMusicTitle();
            mmplay.prepareMP3();//音楽ファイルの再生に必要なインスタンスの生成とデコードを開始する
            /*0615にかいたもの*/
            while( (mmplay.isRunningMP3()))
            {
                if(mmplay.playMP3());
                
                else {
                    mmplay.stopMP3();//音楽停止
                    setStateMachine(MUSIC_PLAY,EXIT);
                }
                if(m_flag_btnA_is_pressed==true)
            {    AppControl::setBtnAllFlgFalse();
                  mmplay.stopMP3();//音楽停止

                setStateMachine(MUSIC_PLAY,EXIT);
            }
            }



            if(  !mmplay.isRunningMP3())//音楽が止まったのならば停止画面に移動
              {setStateMachine(MUSIC_PLAY,EXIT);
              }
            

            
                break;

            case EXIT:

             

                setStateMachine(MUSIC_STOP,ENTRY);
            }
            
                break;

            default:
                break;
            }

            break;




        case MEASURE:

            switch (getAction()) {
            case ENTRY:
            displayMeasureInit();//距離の初期画面

            setStateMachine(MEASURE,DO);
                break;

            case DO:
            if(m_flag_btnB_is_pressed==true)//戻るボタンを押したとき
            {
            setStateMachine(MEASURE,EXIT);
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

        case DATE:

            switch (getAction()) {
            case ENTRY:
            displayDateInit();//時刻の初期画面


            setStateMachine(DATE,DO);

                break;

            case DO:
            if(m_flag_btnB_is_pressed==true)//戻るボタンを押したとき
            {
            setStateMachine(DATE,EXIT);
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

        default:
            break;
        }
    }
}
