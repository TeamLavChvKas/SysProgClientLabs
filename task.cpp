#include "task.h"

Task::Task()
{
}

std::string Task::getTask() const
{
    return task;
}

void Task::setTask(const std::string &value)
{
    task = value;
}

int Task::getId() const
{
    return id;
}

void Task::setId(int value)
{
    id = value;
}

std::vector<Variant *> Task::getVariants() const
{
    return variants;
}

void Task::setVariants(const std::vector<Variant *> &value)
{
    variants = value;
}
