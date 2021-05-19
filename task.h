#ifndef TASK_H
#define TASK_H
#include <variant.h>
#include <string>
#include <list>
#include <vector>
class Variant;

class Task
{
public:
    Task();
    std::string getTask() const;
    void setTask(const std::string &value);
    int getId() const;
    void setId(int value);
    std::vector<Variant *> getVariants() const;
    void setVariants(const std::vector<Variant *> &value);

private:
    int id;
    std::string task;
    std::vector<Variant*> variants;
};

#endif // TASK_H
