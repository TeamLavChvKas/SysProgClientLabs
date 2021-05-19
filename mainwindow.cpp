#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <test.h>
#include <task.h>
#include <variant.h>
#include <testswindow.h>
#include <qfiledialog.h>
#include <qsqldatabase.h>
#include <QSqlQuery>
#include <QTcpSocket>
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    _blockSize = 0;
    name = "Main client";
    sok = new QTcpSocket(this);

    sok->connectToHost(QHostAddress("127.0.0.1"), 2323);


    connect(sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(sok, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));


    getNames();

    ui->setupUi(this);
    ui->label->setText("Оберіть тест, який хочете пройти:");
    QFont font = ui->label->font();
    font.setPixelSize(20);
    ui->label->setFont(font);
    ui->pushButton->setText("Підтвердити");
    ui->pushButton_2->setText("Відкрити тест з файлу");
    setWindowTitle("Стартова сторінка");
    setTests(ui->listWidget);
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (pressMemory()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (pressFile()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::pressMemory()
{
    getTasks(ui->listWidget->currentIndex().row());
    // Створення нової форми з тестами
}

void MainWindow::pressFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Text File", "C:/Temp", "Text files(*.txt)");
    if(!path.isEmpty())
    {
        QFile myFile(path);
        if (myFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
             QTextStream in(&myFile);
             QString taskName = in.readLine();
             Test test1;
             std::vector<Task*> tasks1;
             while(!in.atEnd())
             {
                 Task* task1 = new Task();
                 task1->setTask(taskName.toUtf8().constData());
                 QString var = in.readLine();
                 std::vector<Variant *> vars1;
                 while(var != "")
                 {
                    Variant* var1 = new Variant();
                    var1->setText(var.toUtf8().constData());
                    if(var[0] == '+'){
                        var1->setIsCorrect(true);
                        var1->setText(var1->getText().erase(0,1));
                    }
                    else{
                        var1->setIsCorrect(false);
                    }
                    if(in.atEnd()){
                        vars1.push_back(var1);
                        break;
                    }
                 var = in.readLine();
                 vars1.push_back(var1);
                 }
             task1->setVariants(vars1);
             tasks1.push_back(task1);
             if(in.atEnd()){
                 break;
             }
             taskName = in.readLine();
         }
         test1.setTasks(tasks1);
         myFile.close();
         std::vector<Variant *> answers;
         TestsWindow *test = new TestsWindow(this, test1, 0, 0, answers);
         test->show();
       }
    }
}

void MainWindow::onSokConnected()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << sendName << name;
    sendToServer(arrBlock);
}

void MainWindow::getNames()
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << quint8(2);
    sendToServer(arrBlock);
}

void MainWindow::getTasks(int id)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << quint8(3) << id;
    sendToServer(arrBlock);
}

void MainWindow::onSokDisconnected()
{

}

void MainWindow::onSokReadyRead()
{
    QDataStream in(sok);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;) {
    //если считываем новый блок первые 2 байта это его размер
        if (_blockSize == 0) {
    //если пришло меньше 2 байт ждем пока будет 2 байта
            if (sok->bytesAvailable() < (int)sizeof(quint16)){
                break;}
    //считываем размер (2 байта)
            in >> _blockSize;
        }
    //ждем пока блок прийдет полностью
        if (sok->bytesAvailable() < _blockSize){
            break;}

        quint8 command;
        in >> command;

        switch (command)
        {
    //сервер отправит список пользователей, если авторизация пройдена, в таком случае третий байт равен константе MyClient::comUsersOnline
            case 1:
            {
            }
            break;
    //общее сообщение от сервера
            case 2:
            {
                QString users;
                in >> users;
                if (users == "")
                    return;
                for (QString t : users.split(",")){
                    ui->listWidget->addItem(t);
                }
                ui->listWidget->update();
            }
            break;
            case 3:
            {
                QString names;
                in >> names;

                if (names == "")
                    return;
                std::vector<Task *> tasks;
                QStringList nameslist = names.split(";");
                int i = 0;
                while (i < nameslist.length()-1){
                    Task* task1 = new Task();
                    task1->setTask(nameslist.at(i).toStdString());
                    i++;
                    std::vector<Variant *> variants;
                    while(nameslist.at(i) != " "){
                        Variant* var = new Variant();
                        var->setText(nameslist.at(i).toStdString());
                        std::string plus = "+";
                        if((var->getText().at(var->getText().length()-1)) == plus.at(0)){
                            var->setIsCorrect(true);
                            var->setText(var->getText().erase(var->getText().length()-1));
                        }
                        else{
                            var->setIsCorrect(false);
                        }
                        variants.push_back(var);
                        i++;
                    }
                    task1->setVariants(variants);
                    tasks.push_back(task1);
                    i++;
                }
                std::vector<Variant *> answers;
                Test test1;
                test1.setTasks(tasks);
                TestsWindow *test = new TestsWindow(this, test1, 0, 0, answers);
                test->show();
            }
        }
        _blockSize = 0;
    }
}


void MainWindow::onSokDisplayError(QAbstractSocket::SocketError socketError)
{

}

void MainWindow::sendToServer(QByteArray arrBlock){
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    sok->write(arrBlock);
}



QListWidget *MainWindow::getTests() const
{
    return tests;
}

void MainWindow::setTests(QListWidget *value)
{
    tests = value;
}


