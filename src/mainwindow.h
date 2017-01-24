#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QScopedPointer>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
         public slots:
    void onProgressChanged(QString info);
private:
    QScopedPointer<Ui::MainWindow> ui;
    void timerEvent(QTimerEvent *event);
    void update();
     int timerId;

};

#endif
