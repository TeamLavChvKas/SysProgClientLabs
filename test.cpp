#include "test.h"

Test::Test()
{

}

int Test::getId() const
{
    return id;
}

void Test::setId(int value)
{
    id = value;
}

std::string Test::getTitle() const
{
    return title;
}

void Test::setTitle(const std::string &value)
{
    title = value;
}

std::vector<Task *> Test::getTasks() const
{
    return tasks;
}

void Test::setTasks(const std::vector<Task *> &value)
{
    tasks = value;
}
