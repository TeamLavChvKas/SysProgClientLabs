#include "resultswindow.h"
#include "test.h"
#include "ui_resultswindow.h"
#include "variant.h"

#include <QFile>
#include <QFileDialog>

ResultsWindow::ResultsWindow(QWidget *parent, int result, Test test, std::vector<Variant *> answers) :
    QDialog(parent),
    ui(new Ui::ResultsWindow)
{
    setResult(result);
    setTest(test);
    setAnswers(answers);
    ui->setupUi(this);
    std::string st = "Ваш результат: ";
    st.append(std::to_string(result));
    ui->label->setText(QString::fromUtf8(st));
    ui->pushButton->setText("Закінчити");
    ui->pushButton_2->setText("Зберегти відповіді");
    setWindowTitle("Результат");
    connect(ui->pushButton, SIGNAL (released()),this, SLOT (pressEnd()));
    connect(ui->pushButton_2, SIGNAL (released()),this, SLOT (pressSave()));
}

ResultsWindow::~ResultsWindow()
{
    delete ui;
}

void ResultsWindow::pressEnd()
{
    this->close();
}

void ResultsWindow::pressSave()
{
    QString path = QFileDialog::getSaveFileName(this, "Save Text File", "C:/Temp", "Text files(*.txt)");
    if(!path.isEmpty())
    {
    QFile myFile(path);
    if (myFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&myFile);
        QString allText = "";
        for(int i = 0; i < test.getTasks().size(); i++)
        {
             allText.append(QString::fromUtf8(test.getTasks().at(i)->getTask()));
             allText.append("\n");
             allText.append(QString::fromUtf8(answers.at(i)->getText()));
             allText.append("\n");
        }
        allText.append("Result: ");
        allText.append(QString::number(getResult()));
        out << allText;
        myFile.close();
        }
    }
    this->close();
}

int ResultsWindow::getResult() const
{
    return result;
}

void ResultsWindow::setResult(int value)
{
    result = value;
}

std::vector<Variant *> ResultsWindow::getAnswers() const
{
    return answers;
}

void ResultsWindow::setAnswers(const std::vector<Variant *> &value)
{
    answers = value;
}

Test ResultsWindow::getTest() const
{
    return test;
}

void ResultsWindow::setTest(const Test &value)
{
    test = value;
}
