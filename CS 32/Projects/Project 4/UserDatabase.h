#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase();

  private:
    bool m_loaded;
    std::vector<User*> m_users;
    TreeMultimap<std::string, User*> email2User;
};

#endif // USERDATABASE_INCLUDED
