#include "User.h"

User::User()
{}

User::User(bool is_admin, string login, string pass): _is_admin(is_admin), _login(login), _password(pass)
{}

bool User::is_admin() const
{
    return _is_admin;
}
