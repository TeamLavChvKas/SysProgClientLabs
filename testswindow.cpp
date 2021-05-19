#include "resultswindow.h"
#include "test.h"
#include "testswindow.h"
#include "ui_testswindow.h"
#include "variant.h"

#include <QButtonGroup>
#include <QGroupBox>
#include <QRadioButton>

TestsWindow::TestsWindow(QWidget *parent, Test test, int count, int amount, std::vector<Variant *> answers) :
    QDialog(parent),
    ui(new Ui::TestsWindow)
{
    setAmount(amount);
    setCount(count);
    setTest(test);
    setAnswers(answers);
    Task *task1 = test.getTasks().at(count);
    ui->setupUi(this);
    ui->label->setText(QString::fromUtf8(task1->getTask()));
    bg = new QButtonGroup();
    std::vector<Variant *> vars = task1->getVariants();
    int flinch = 0;
    int id = 1;
    for(Variant* v : vars){
        QRadioButton *button = new QRadioButton(this);
        button->setText(QString::fromUtf8(v->getText()));
        button->setGeometry(30, 50+flinch, 100, 100);
        flinch+=20;
        bg->addButton(button, id);
        id+=1;
    }
    bg->button(1)->setChecked(true);
    ui->pushButton->setText("Відповісти");
    setWindowTitle("Питання");
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(press()));
}

TestsWindow::~TestsWindow(){
    delete ui;
}

void TestsWindow::press()
{
    Variant* var;
    var = (test.getTasks().at(count)->getVariants()).at(bg->checkedId()-1);
    answers.push_back(var);
    if(var->getIsCorrect()){
        setAmount(getAmount()+1);
    }
    if((int)test.getTasks().size() != (getCount()+1)){
        TestsWindow *testWindow = new TestsWindow(this, getTest(), getCount()+1, getAmount(), getAnswers());
        testWindow->show();
    }
    else
    {
        // Створюємо форму результату
        ResultsWindow *result = new ResultsWindow(this, getAmount(), test, answers);
        result->show();
    }
    this->close();
}

std::vector<Variant *> TestsWindow::getAnswers() const
{
    return answers;
}

void TestsWindow::setAnswers(const std::vector<Variant *> &value)
{
    answers = value;
}

QButtonGroup *TestsWindow::getBg() const
{
    return bg;
}

void TestsWindow::setBg(QButtonGroup *value)
{
    bg = value;
}

int TestsWindow::getAmount() const
{
    return amount;
}

void TestsWindow::setAmount(int value)
{
    amount = value;
}

int TestsWindow::getCount() const
{
    return count;
}

void TestsWindow::setCount(int value)
{
    count = value;
}

Test TestsWindow::getTest() const
{
    return test;
}

void TestsWindow::setTest(const Test &value)
{
    test = value;
}



