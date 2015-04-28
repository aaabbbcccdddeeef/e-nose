#ifndef QCOMMON_H
#define QCOMMON_H

#include <QString>

enum SYSTEM_STATE{
    STANDBY = 0,    //待机
    PREHEAT,        //预热
    THERMO,         //恒温
    EVAPORATION,    //蒸发
    SAMPLING,       //采样
    CLEAR           //清洗
};

typedef struct{
    float sample_freq;//每个通道的采样频率
    int sample_time;//每个通道的时间长度
    QString filename_prefix;
} SAMPLE;

/* 需要实时更新的信息 */
typedef struct{
    QString ds18b20_temp;
    QString sht21_temp;
    QString sht21_humid;
} GUI_REALTIME_INFO;

typedef struct{
    float preset_temp;//预设温度
    int hold_time;//蒸发时间
    float sample_freq;//每个通道的采样频率
    int sample_time;//每个通道的时间长度
    int evapor_clear_time;//蒸发室清洗时间
    int reac_clear_time;//反应室清洗时间
    int sample_style;
    QString data_file_path;
} SYSTEM_PARA_SET;

enum SAMPLE_STYLE{
    SINGLE = 0,
    CONTINUE
};

#endif // QCOMMON_H
