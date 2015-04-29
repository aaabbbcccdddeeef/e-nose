#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "plot_widget.h"
#include "thread_logic.h"
#include "thread_data_proc.h"
#include "thread_hardware.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

signals:
    void send_to_logic_ststem_para_set(SYSTEM_PARA_SET system_para_set_info);

private slots:
    void on_Quit_Button_clicked();//用于退出程序
    void timerUpdate();//用于更新时间

    void on_pushButton_10_clicked();

    void on_pushButton_clear_current_clicked();

    void on_pushButton_clear_all_clicked();

    void on_pushButton_9_clicked();

public slots:
    /* 接收硬件线程发送来的实时温湿度数据 */
    void recei_fro_hard_realtime_info_update(GUI_REALTIME_INFO realtime_info);

    /* 接收来自硬件线程的恒温实时duty值 */
    void recei_fro_hard_thermostat_duty_update(int duty_info);

    /* 接收来自硬件线程的开启气泵时duty值 */
    void recei_fro_hard_pump_duty_update(int duty_info);

    /* 接收来自硬件线程的电磁阀状态信息 */
    void recei_fro_hard_magnetic_update(MAGNETIC magnetic_info);


private:
    Ui::MainWindow *ui;
    LogicControlThread *logic_thread;
    HardWareControlThread *hardware_thread;
    DataProcessThread *dataprocess_thread;
    QTimer *timer;
    Plot_Widget *plot_widget;
    SYSTEM_STATE system_state;  //系统控制参数
    SYSTEM_PARA_SET system_para_set;
};

#endif // MAINWINDOW_H
