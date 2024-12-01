#ifndef DLGSETTINGS_HPP
#define DLGSETTINGS_HPP

#include <QDialog>

namespace Ui {
    class DlgSettings;
}

class DlgSettings: public QDialog
{
    Q_OBJECT

  public:
    static bool execDlgSettings(QWidget* parent);

  private:
    explicit DlgSettings(QWidget* parent);
    ~DlgSettings();
    Ui::DlgSettings* ui;
};

#endif // DLGSETTINGS_HPP
