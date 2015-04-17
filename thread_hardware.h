#ifndef THREAD_HARDWARE_H
#define THREAD_HARDWARE_H

#include <QThread>
#include <QString>
#include <QTimer>

/* 需要实时更新的信息 */
typedef struct{
    QString ds18b20_temp;
    QString sht21_temp;
    QString sht21_humid;
} GUI_REALTIME_INFO;

/*********************硬件控制线程*****************************/
class HardWareControlThread : public QThread
{
    Q_OBJECT
public:
    explicit HardWareControlThread(QObject *parent = 0);
    void stop();

protected:
    void run();

private:
    volatile bool stopped;

signals:
    void send_realtime_info(GUI_REALTIME_INFO);

public slots:

};

#endif // THREAD_HARDWARE_H
