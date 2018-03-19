#include "menubutton.h"

MenuButton::MenuButton(QString title, bool isSearchable)
{
    setText(title + " ▼");
    connect(this, SIGNAL(clicked()), this, SLOT(onClicked()));
    searchable = isSearchable;
    menu = new QMenu();
}

MenuButton::~MenuButton()
{
    qDebug()<<"~MenuButton";
    delete menu;
}

void MenuButton::addItems(QVector<QPair<QString, int> > _addItems)
{
    for(int i = 0; i < _addItems.length(); i++)
        items.push_back(QPair<QString, int>(_addItems[i].first, _addItems[i].second));
    setupMenu();
}

void MenuButton::onClicked()
{
    menu->exec(mapToGlobal(QPoint(0, height())));
}

void MenuButton::setupMenu()
{
    //menu = new QMenu();
    if(searchable)
    {
        LineEditAction* leAction = new LineEditAction();
        leAction->setFont(this->font());
        menu->addAction(leAction);
        connect(leAction->getLineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)));
    }      
    for(int i = 0; i < items.length(); i++)
    {
        QAction *act = menu->addAction(items[i].first);
        act->setFont(this->font());
        act->setData(items[i].second);
    }
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionTriggered(QAction*)));
}

void MenuButton::addSubMenus(QVector<QPair<QString, QVector<QPair<QString, int> >* > > _menus)
{
    for(int i = 0; i < _menus.length(); i++)
    {
        QVector<QPair<QString, int> >* v = new QVector<QPair<QString, int> >();
        for(int j = 0; j < _menus.at(i).second->length(); j++)
        {
            v->push_back(QPair<QString, int>(_menus.at(i).second->at(j).first, _menus.at(i).second->at(j).second));
            items.push_back(QPair<QString, int>(_menus.at(i).second->at(j).first, _menus.at(i).second->at(j).second));
        }
        submenus.push_back(QPair<QString, QVector<QPair<QString, int> >* >(_menus.at(i).first, v));
    }

    setupSubMenus();
}

void MenuButton::setupSubMenus()
{
    menu->clear();
    //menu = new QMenu();
    if(searchable)
    {
        LineEditAction* leAction = new LineEditAction();
        leAction->setFont(this->font());
        menu->addAction(leAction);
        connect(leAction->getLineEdit(), SIGNAL(textChanged(QString)), this, SLOT(onSearchTextChanged(QString)));
    }
    for(int i = 0; i < submenus.length(); i++)
    {
        QMenu* submenu = new QMenu(submenus.at(i).first);
        QVector<QPair<QString, int> >* menuline = submenus.at(i).second;
        for(int j = 0; j < menuline->length(); j++)
        {
            QAction* act = submenu->addAction(menuline->at(j).first);
            act->setFont(this->font());
            act->setData(menuline->at(j).second);
        }
        connect(submenu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionTriggered(QAction*)));
        menu->addMenu(submenu);
    }
    menu->setFont(this->font());
    connect(menu, SIGNAL(triggered(QAction*)), this, SLOT(menuActionTriggered(QAction*)));
}

void MenuButton::onSearchTextChanged(QString text)
{
    if(text.isEmpty() && submenus.length() > 0)
    {
        setupSubMenus();
        return;
    }
    foreach (QAction* act, menu->actions()) {
        if(!act->inherits("LineEditAction"))
            menu->removeAction(act);
    }
    //foreach (QString s, items) {
    for(int i = 0; i < items.length(); i++)
    {
        if(items[i].first.toLower().contains(text.toLower()))
        {
            QAction* a = menu->addAction(items[i].first);
            a->setData(items[i].second);

        }
    }
}

void MenuButton::menuActionTriggered(QAction *action)
{
    emit itemClicked(action->text(), action->data().toInt());
}
