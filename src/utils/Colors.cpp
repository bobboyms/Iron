#include "../headers/Colors.h"

std::string color::colorText(const std::string &text, const std::string &colorCode)
{
    return colorCode + text + "\033[0m";
}