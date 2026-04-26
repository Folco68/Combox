#ifndef PROFILELIST_HPP
#define PROFILELIST_HPP

#include "Profile.hpp"
#include <QList>

class ProfileList
{
  public:
    static ProfileList* instance();
    static void         release();
    QList<Profile*>     list() const;

  private:
    static ProfileList* profilelist;
    ProfileList();

    QList<Profile*> List;
};

#endif // PROFILELIST_HPP
