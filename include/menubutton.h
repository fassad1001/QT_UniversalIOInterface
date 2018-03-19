#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QMenu>
#include "lineeditaction.h"
#include <QPair>
#include <QDebug>

class MenuButton : public QPushButton
{
    Q_OBJECT

private:
    QVector<QPair<QString, int> > items;
    QVector<QPair<QString, QVector<QPair<QString, int> >* > > submenus;
    QMenu *menu;
    bool searchable;

public:
    MenuButton(QString title, bool isSearchable = true);
    ~MenuButton();
    void addItems(QVector<QPair<QString, int> >  _addItems);
    void addSubMenus(QVector<QPair<QString, QVector<QPair<QString, int> >* > > _menus);
    void setupMenu();
    void setupSubMenus();

public slots:
    void onClicked();
    void onSearchTextChanged(QString text);
    void menuActionTriggered(QAction* action);

signals:
    void itemClicked(QString name, int id);
};

#endif // MENUBUTTON_H
