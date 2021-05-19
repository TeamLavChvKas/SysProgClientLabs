#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <test.h>
#include <QAbstractSocket>
#include <qtcpsocket.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    std::vector<Test> getTestsList() const;

    QListWidget *getTests() const;
    void setTests(QListWidget *value);


    void sendToServer(QByteArray  arrBlock);
    static const quint8 sendName = 1;
    static const quint8 testsStringList = 2;
    static const quint8 getTestss = 3;
    void getNames();
    void getTasks(int id);

private slots:
    void pressMemory();
    void pressFile();

    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);


private:
    QListWidget* tests;
    Ui::MainWindow *ui;

    QTcpSocket *sok;
    quint16 _blockSize;
    QString name;
};
#endif // MAINWINDOW_H
