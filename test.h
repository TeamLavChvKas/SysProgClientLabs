#ifndef TEST_H
#define TEST_H

#include <task.h>
#include <string>
#include <vector>



class Test
{
public:
    Test();
    int getId() const;
    void setId(int value);
    std::string getTitle() const;
    void setTitle(const std::string &value);
    std::vector<Task *> getTasks() const;
    void setTasks(const std::vector<Task *> &value);

private:
    int id;
    std::string title;
    std::vector<Task *> tasks;
};

#endif // TEST_H
