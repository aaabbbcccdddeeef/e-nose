#ifndef THREAD_LOGIC_H
#define THREAD_LOGIC_H

#include <QThread>
#include <QString>
#include <QTimer>
#include "common.h"
#include "qcommon.h"

/*********************逻辑控制线程*****************************/
class LogicControlThread : public QThread
{
    Q_OBJECT
public:
    explicit LogicControlThread(QObject *parent = 0);
    void stop();

protected:
    void run();

private:
    volatile bool stopped;//线程状态控制，true表示线程结束，false表示不结束

    BEEP beep_para;//蜂鸣器控制相关参数
    THERMOSTAT thermostat_para;//加热带控制相关参数
    PUMP pump_para;//气泵控制相关参数
    MAGNETIC magnetic_para;//电磁阀状态控制相关参数
    SAMPLE sample_para;

    SYSTEM_STATE system_state;//系统状态
    SYSTEM_PARA_SET system_para_set;//系统控制参数

    OPERATION_FLAG operation_flag;
    PUSHBUTTON_STATE pushButton_state;
    USER_BUTTON_ENABLE user_button_enable;

    bool read_para_flag;//控制读取参数的时机
    bool open_clicked_flag;//控制蒸发停止的时机,用户点击open后应该先暂时停止恒温
    bool close_clicked_flag;//控制蒸发开始的时机,用户点击close后应该恢复恒温

    QTimer *close_pump_and_reac_timer;
    QTimer *evaporation_timer;

signals:
    /* 发送给硬件控制线程的恒温信号 */
    void send_to_hard_evapor_thermostat(THERMOSTAT thermostat_para);

    /* 发送给硬件线程的蜂鸣器控制信号 */
    void send_to_hard_beep(BEEP beep_para);

    /* 发送给硬件线程的气泵控制信号 */
    void send_to_hard_pump(PUMP pump_para);

    /* 发送给硬件线程的电磁阀控制信号 */
    void send_to_hard_magnetic(MAGNETIC magnetic_para);

    /* 发送给数据处理线程的采样控制信号 */
    void send_to_dataproc_sample(SAMPLE sample_para);

    /* 发送系统状态到GUI线程 */
    void send_to_GUI_pushButton_state(PUSHBUTTON_STATE pushButton_state_para);

    /* set按钮使能计时开始 */
    void send_to_GUI_user_buttton_enable(USER_BUTTON_ENABLE user_button_enable_para);

public slots:
    /* 处理来自硬件线程预热完成的信号 */
    void recei_fro_hardware_preheat_done();

    /* 处理来自硬件线程恒温完成的信号 */
    void recei_fro_hardware_thermostat_done();

    /* 接收GUI线程发送来的系统控制参数 */
    void recei_fro_GUI_system_para_set(SYSTEM_PARA_SET system_para_set_info);

    /* 接收来自数据处理线程的采样完成信号 */
    void recei_fro_hardware_sample_done();

    /* 用户在系统操作面板按下按钮后应该通知逻辑线程产生动作 */
    void recei_fro_GUI_user_button_action(USER_BUTTON_ENABLE user_button_enable_para);

private slots:

    /* 打入样本气体到反应室时可以定时封闭反应室 */
    void close_pump_and_reac();

    /* 处理来自硬件线程蒸发完成的信号 */
    void evapoartion_timeout_done();

};

#endif // THREAD_LOGIC_H
