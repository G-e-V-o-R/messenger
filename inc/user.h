#pragma once

#include <string>
#include <set>

struct user : public std::enable_shared_from_this<user>
{
    std::string id;
    std::string name;
    std::string password;
    std::string session_id;
	std::string net_status;
};
