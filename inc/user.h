#pragma once

#include <string>

struct user : public std::enable_shared_from_this<user>
{
    std::string user_id;
    std::string username;
    std::string pasword;
    std::string session_id;
};
