#include "scarlet/imgui/ComponentMenu.hpp"
using namespace scarlet;

ComponentMenu::ComponentMenu(std::string title)
{
    this->title = title;
    this->active = false;
}
ComponentMenu::~ComponentMenu()
{
    
}

std::string ComponentMenu::GetTitle()
{
    return this->title;
}
bool ComponentMenu::GetActive()
{
    return this->active;
}

void ComponentMenu::SetTitle(std::string title)
{
    this->title = title;
}
void ComponentMenu::SetActive(bool value)
{
    this->active = value;
}