
    #include "./includes/User.h"
    #include <string>
    #include <fstream>
    #include <iostream>

    using namespace std;

    User::User() : username(""), password(""), confirmPassword("") {}


    bool User::ValidateRegistration()
    {
        return password == confirmPassword;
    }


    bool User::ValidateLogin(const string &inputUsername, const string &inputPassword)
    {
        return (inputUsername == username && inputPassword == password);
    }


    void User::SaveToFile()
    {
        ofstream file("./files/"+ username + ".txt");
        if (file.is_open())
        {
            file << username << endl; 
            file << password << endl; 
            file.close();
            cout << "Registration successful! User data saved." << endl;
        }
        else
        {
            cerr << "Failed to save user data." << endl;
        }
    }

    bool User::LoadFromFile(const string &inputUsername)
    {
        ifstream file("./files/" + inputUsername + ".txt");
        if (file.is_open())
        {
            getline(file, username);
            getline(file, password);
            file.close();
            return true;
        }
        else
        {
            cerr << "No user found with that username!" << endl;
            return false;
        }
    }
