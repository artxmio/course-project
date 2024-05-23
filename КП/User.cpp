#include "User.h"

User::User()
{}


User::User(bool is_admin, string login, string pass, string name, bool u): _is_admin(is_admin), _login(login), _password(pass), _name(name), user_alive(u)
{}

bool User::is_admin() const noexcept
{
    return _is_admin;
}

void User::set_admin(bool w)
{
    this->_is_admin = w;
}

bool User::alive()
{
    return user_alive;
}
