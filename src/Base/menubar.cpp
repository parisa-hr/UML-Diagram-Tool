#include "menubar.h"
#include "ui_menubar.h"
#include "mainmenu.h"
#include <QAction>
#include <QToolButton>
#include <qfontdatabase.h>

MenuBar::MenuBar(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MenuBar)
{
    ui->setupUi(this);
    _mainMenu = new MainMenu;
    _mainMenu->hide();

    /// add Font combobox

    ui->comboSize->setEditable(true);

    const QList<int>  standardSizes = QFontDatabase::standardSizes();

    for (int size : standardSizes)
    {
        ui->comboSize->addItem(QString::number(size));
    }

    ui->comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));
}

MenuBar::~MenuBar()
{
    delete ui;
}

void  MenuBar::on_toolButton_clicked()
{
    emit  CloseWindow();
}

void  MenuBar::on_tb_Menu_clicked()
{
    if (_mainMenu->isVisible())
    {
        _mainMenu->hide();

        return;
    }

    auto  pos = mapToGlobal(QPoint(0, 60));

    _mainMenu->move(pos);
    _mainMenu->show();
}

MainMenu * MenuBar::getMainMenu() const
{
    return _mainMenu;
}

void  MenuBar::addToolButton(QAction *action)
{
    QToolButton *toolButton = new QToolButton;

    toolButton->setAutoRaise(true);
    toolButton->setIconSize(QSize(32, 32));

    toolButton->setDefaultAction(action);

    ui->DiagramMenu->addWidget(toolButton);
}

void  MenuBar::on_tb_Pan_clicked(bool checked)
{
    if (checked)
    {
        emit  SetCursorPan();
        ui->tb_Select->setChecked(false);
    }
    else
    {
        emit  SetCursorSelect();
    }
}

void  MenuBar::on_tb_Select_clicked()
{
    emit  SetCursorSelect();

    ui->tb_Pan->setChecked(false);
}

void  MenuBar::on_tb_changeColor_clicked()
{
}

void  MenuBar::on_tb_addText_clicked()
{
    emit  addText();
}