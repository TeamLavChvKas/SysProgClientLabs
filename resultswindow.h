#ifndef RESULTSWINDOW_H
#define RESULTSWINDOW_H

#include "test.h"
#include "variant.h"

#include <QDialog>

namespace Ui {
class ResultsWindow;
}

class ResultsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsWindow(QWidget *parent, int result, Test test, std::vector<Variant *> answers);
    ~ResultsWindow();

    Test getTest() const;
    void setTest(const Test &value);
    std::vector<Variant *> getAnswers() const;
    void setAnswers(const std::vector<Variant *> &value);
    int getResult() const;
    void setResult(int value);

private slots:
    void pressEnd();
    void pressSave();

private:
    Ui::ResultsWindow *ui;
    Test test;
    std::vector<Variant *> answers;
    int result;
};

#endif // RESULTSWINDOW_H
