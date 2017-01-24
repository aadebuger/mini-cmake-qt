#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qtimer.h>
#include <QDebug>
#include <QHash>
#include <QVariant>
#include <QLinkedList>
#include <QMessageBox>
#include <math.h>
#include <vector>
#include <future>
#include "curl_easy.h"
#include "curl_exception.h"
#include "curl_easy.h"
#include "curl_form.h"
#include "curl_ios.h"
#include "curl_exception.h"


#include <glog/logging.h>
using namespace std;
using curl::curl_easy;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
      qDebug("This is a debug message");
    
    QTimer *timer = new QTimer( this );
    connect( timer, SIGNAL(timeout()), this , SLOT(update()) );
    timer->start( 2000); // 2秒单触发定时器
      timerId = startTimer(20000);
}

MainWindow::~MainWindow()
{
     killTimer(timerId);
}

void MainWindow::update()
{
    qDebug("update");
}
void MainWindow::timerEvent(QTimerEvent *event)
{
    qDebug() << "Update...";
    
    
    std::future<string> httpfuture = async(launch::async,
          []() -> string
          {
  
              CURL *curl;
              string url ="http://api.qkzhi.com/1.1/classes/Todo";
              CURLcode res;
              long siteSize = 0;
              ostringstream str;
              // Create a curl_ios object, passing the stream object.
              curl_ios<ostringstream> writer(str);
              
              curl_easy easy(writer);
              // Add some option to the easy handle
              easy.add<CURLOPT_URL>(url.c_str());
              easy.add<CURLOPT_FOLLOWLOCATION>(1L);
              
              if(1) {
                  // setup
                  
                  try {
                      // Execute the request.
                      easy.perform();
                  } catch (curl_easy_exception error) {
                      // If you want to get the entire error stack we can do:
                      curlcpp_traceback errors = error.get_traceback();
                      // Otherwise we could print the stack like this:
                      error.print_traceback();
                      // Note that the printing the stack will erase it
                  }
                  
              }
                 cout<<str.str()<<endl;
                 cout<<"hello";
              return str.str();
              
              
          });
    string str = httpfuture.get();
//    emit progressChanged("Some info");
    QMessageBox::information(this,"About",str.c_str());
    
}
void MainWindow::onProgressChanged(QString info)
{
        QMessageBox::information(this,"About1", info);
}
