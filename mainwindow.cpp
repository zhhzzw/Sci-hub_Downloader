#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtNetwork"
#include <QRegExp>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::slot_replayFinished(QNetworkReply *reply)
{
    QRegExp regExp("http:[\\S]+doi=\\S+&key=\\w+");
    QTextCodec *codec = QTextCodec::codecForName("utf8");
        //使用utf8编码, 这样可以显示中文
    QString str = codec->toUnicode(reply->readAll());
    int pos = regExp.indexIn(str);
    QStringList list = regExp.capturedTexts();
    QString DownloadUrl = list[0];
    QDesktopServices::openUrl(QUrl(DownloadUrl));
    reply->deleteLater();//最后要释放replay对象

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Download_clicked()
{
    QString Sci_hub_Url ="http://93.174.95.27/scimag/ads.php?doi=";
    QString Article_Url = ui->ArticleUrl->toPlainText();
    //创建管理器
    QNetworkAccessManager *manager = new QNetworkAccessManager();
    //创建请求
    QNetworkRequest request;
    request.setUrl(QUrl(Sci_hub_Url+Article_Url));
    request.setHeader(QNetworkRequest::UserAgentHeader,"Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN) AppleWebKit/533.21.1 (KHTML, like Gecko) Version/5.0.5 Safari/533.21.1");
    //发送get请求
    QNetworkReply *reply = manager->get(request);
    connect(manager, SIGNAL(finished(QNetworkReply    *)), this, SLOT(slot_replayFinished(QNetworkReply*)));
    //QDesktopServices::openUrl(QUrl(Sci_hub_Url+'//'+Article_Url));
}
