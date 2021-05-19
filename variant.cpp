#include "variant.h"
#include <task.h>

Variant::Variant()
{

}

std::string Variant::getText() const
{
    return text;
}

void Variant::setText(const std::string &value)
{
    text = value;
}

void Variant::setIsCorrect(bool value)
{
    isCorrect = value;
}

int Variant::getId() const
{
    return id;
}

void Variant::setId(int value)
{
    id = value;
}

bool Variant::getIsCorrect() const
{
    return isCorrect;
}
