#ifndef VARIANT_H
#define VARIANT_H

#include <task.h>
#include <string>
class Task;

class Variant
{
public:
    Variant();
    std::string getText() const;
    void setText(const std::string &value);
    void setIsCorrect(bool value);
    int getId() const;
    void setId(int value);
    bool getIsCorrect() const;

private:
    int id;
    std::string text;
    bool isCorrect;
};

#endif // VARIANT_H
