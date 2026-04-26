#ifndef PROFILE_HPP
#define PROFILE_HPP

#include <QString>

class Profile
{
  public:
    //    Profile();
    QString name() const;
    QString topLeft() const;
    QString top() const;
    QString topRight() const;
    QString left() const;
    QString right() const;
    QString bottomLeft() const;
    QString bottom() const;
    QString bottomRight() const;

  private:
    QString Name;
    QString TopLeft;
    QString Top;
    QString TopRight;
    QString Left;
    QString Right;
    QString BottomLeft;
    QString Bottom;
    QString BottomRight;
};

#endif // PROFILE_HPP
