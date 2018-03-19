#include "lineeditaction.h"

LineEditAction::LineEditAction() : QWidgetAction(NULL)
{
    QWidget *wdgt = new QWidget();
    QHBoxLayout *l = new QHBoxLayout();
    pLineEdit = new QLineEdit();
    l->addWidget(pLineEdit);
    wdgt->setLayout(l);

    setDefaultWidget(wdgt);
}

QLineEdit* LineEditAction::getLineEdit()
{
    return pLineEdit;
}
