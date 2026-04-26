#include "ProfileList.hpp"

ProfileList* ProfileList::profilelist = nullptr;

ProfileList* ProfileList::instance()
{
    if (profilelist == nullptr) {
        profilelist = new ProfileList;
    }
    return profilelist;
}

void ProfileList::release()
{
    if (profilelist != nullptr) {
        delete profilelist;
        profilelist = nullptr;
    }
}

ProfileList::ProfileList()
{
}

QList<Profile*> ProfileList::list() const
{
    return this->List;
}
