#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

UserDatabase::UserDatabase()
{
    m_loaded = false;
}

bool UserDatabase::load(const string& filename)
{
    if (m_loaded){
        return false;
    } else {
        ifstream userDBfile (filename);
        if ( ! userDBfile ) {
            return false;
        }
        string s;
        while (getline(userDBfile, s)){
            string tempName = s;
            string tempEmail;
            int tempIDs;
            std::vector<string> tempHistory;
            getline(userDBfile, tempEmail);
            userDBfile >> tempIDs;
            userDBfile.ignore(10000, '\n');
            for (int i=0; i<tempIDs; i++){
                getline(userDBfile, s);
                tempHistory.push_back(s);
            }
            User* tempUser = new User(tempName, tempEmail, tempHistory);
            m_users.push_back(tempUser);
            email2User.insert(tempEmail, tempUser);
            userDBfile.ignore(10000, '\n');
        }
        m_loaded = true;
        return true;
    }
    return false;
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    if (email2User.find(email).is_valid()){
        User* tempUser = email2User.find(email).get_value();
        if (tempUser->get_email() == email){
            return tempUser;
        }
    }
    return nullptr;  
}

UserDatabase::~UserDatabase(){
    vector<User*>::iterator it = m_users.begin();
    while ( it != m_users.end() ){
        delete *it;
        m_users.erase(it);
        it++;
    }
    m_users.clear();
}
