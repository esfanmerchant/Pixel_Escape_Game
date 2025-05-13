#ifndef USER
#define USER

#include <string>
#include <fstream>
#include <iostream>

class User
{
public:
    std::string username;
    std::string password;
    std::string confirmPassword;

    User();

    bool ValidateRegistration();

    bool ValidateLogin(const std::string &inputUsername, const std::string &inputPassword);

    void SaveToFile();

    bool LoadFromFile(const std::string &inputUsername);
};

#endif
