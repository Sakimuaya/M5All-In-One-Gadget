#include "MdMusicPlayer.h"
#include "AudioFileSourceID3.h"
#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

AudioGeneratorMP3* mp3;
AudioFileSourceSD* file;
AudioOutputI2S* out;
AudioFileSourceID3* id3;

File musicfolder;
File entry;

void MdMusicPlayer::init()
{

    SD.begin();
    musicfolder = SD.open("/music");
    if (!musicfolder) {
        // musicフォルダが無かった場合、開けなかった場合
        Serial.println("musicfolder open error");
    } else {
        entry = musicfolder.openNextFile();
    }
}

char* MdMusicPlayer::getTitle()//音楽タイトル取得/
{
    return (char*)entry.name();
}

void MdMusicPlayer::selectNextMusic()
{
    entry = musicfolder.openNextFile();
    if (!entry) {
        musicfolder.rewindDirectory();
        entry = musicfolder.openNextFile();
        Serial.println("return latestfile");
    }
}

void MdMusicPlayer::prepareMP3()//音楽ファイルの再生に必要なインスタンスの生成とデコードを開始する
{
    file = new AudioFileSourceSD(entry.path());
    id3 = new AudioFileSourceID3(file);
    out = new AudioOutputI2S(0, 1); // Output to builtInDAC
    out->SetOutputModeMono(true);
    out->SetGain(0.045);
    mp3 = new AudioGeneratorMP3();
    mp3->begin(id3, out);
}

bool MdMusicPlayer::isRunningMP3()//音楽ファイル再生中か確認。デコード中ならtrue,そうでないならfalseをかえす
{
    return mp3->isRunning();
}

bool MdMusicPlayer::playMP3()//音楽ファイルを再生する。次のデータがあるならTなければFかえす
{
    return mp3->loop();
}

void MdMusicPlayer::stopMP3()//音楽ファイルのデコードを停止する。
{
    mp3->stop();
}
