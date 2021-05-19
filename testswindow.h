#ifndef TESTSWINDOW_H
#define TESTSWINDOW_H

#include <QDialog>
#include <test.h>
#include <list>
#include <QButtonGroup>

namespace Ui {
class TestsWindow;
}

class TestsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit TestsWindow(QWidget *parent, Test test, int count, int amount, std::vector<Variant *> answers);
    ~TestsWindow();

    Test getTest() const;
    void setTest(const Test &value);
    int getCount() const;
    void setCount(int value);
    int getAmount() const;
    void setAmount(int value);
    QButtonGroup *getBg() const;
    void setBg(QButtonGroup *value);
    std::vector<Variant *> getAnswers() const;
    void setAnswers(const std::vector<Variant *> &value);

private slots:
    void press();

private:
    Ui::TestsWindow *ui;
    Test test;
    int count;
    int amount;
    std::vector<Variant *> answers;
    QButtonGroup* bg;
};

#endif // TESTSWINDOW_H
