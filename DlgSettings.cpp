#include "DlgSettings.hpp"
#include "Settings.hpp"
#include "ui_DlgSettings.h"

DlgSettings::DlgSettings(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::DlgSettings)
{
    ui->setupUi(this);
    ui->EditTopLeft->setText(Settings::instance()->topLeft());
    ui->EditTopCenter->setText(Settings::instance()->topCenter());
    ui->EditTopRight->setText(Settings::instance()->topRight());
    ui->EditMiddleLeft->setText(Settings::instance()->middleLeft());
    ui->EditMiddleRight->setText(Settings::instance()->middleRight());
    ui->EditBottomLeft->setText(Settings::instance()->bottomLeft());
    ui->EditBottomCenter->setText(Settings::instance()->bottomCenter());
    ui->EditBottomRight->setText(Settings::instance()->bottomRight());
    ui->SpinBoxEmptyLines->setValue(Settings::instance()->emptyLines());
    ui->SpinBoxWidth->setValue(Settings::instance()->width());
    ui->CheckAutoCopy->setChecked(Settings::instance()->autoCopyToClipboard());
    ui->KeySequenceCopy->setKeySequence(Settings::instance()->copyShortcut());

    connect(ui->ButtonOK, &QPushButton::clicked, this, [this]() { accept(); });
    connect(ui->ButtonCancel, &QPushButton::clicked, this, [this]() { reject(); });
}

DlgSettings::~DlgSettings()
{
    delete ui;
}

bool DlgSettings::execDlgSettings(QWidget* parent)
{
    DlgSettings* Dlg    = new DlgSettings(parent);
    int          RetVal = Dlg->exec();
    if (RetVal == QDialog::Accepted) {
        Settings::instance()->setTopLeft(Dlg->ui->EditTopLeft->text());
        Settings::instance()->setTopCenter(Dlg->ui->EditTopCenter->text());
        Settings::instance()->setTopRight(Dlg->ui->EditTopRight->text());
        Settings::instance()->setMiddleLeft(Dlg->ui->EditMiddleLeft->text());
        Settings::instance()->setMiddleRight(Dlg->ui->EditMiddleRight->text());
        Settings::instance()->setBottomLeft(Dlg->ui->EditBottomLeft->text());
        Settings::instance()->setBottomCenter(Dlg->ui->EditBottomCenter->text());
        Settings::instance()->setBottomRight(Dlg->ui->EditBottomRight->text());
        Settings::instance()->setEmptyLines(Dlg->ui->SpinBoxEmptyLines->value());
        Settings::instance()->setWidth(Dlg->ui->SpinBoxWidth->value());
        Settings::instance()->setautoCopyToClipboard(Dlg->ui->CheckAutoCopy->isChecked());
        Settings::instance()->setCopyShortcut(Dlg->ui->KeySequenceCopy->keySequence().toString());
    }
    delete Dlg;
    return RetVal == QDialog::Accepted;
}
