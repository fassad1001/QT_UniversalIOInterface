#ifndef LINEEDITACTION_H
#define LINEEDITACTION_H

#include <QWidgetAction>
#include <QLineEdit>
#include <QHBoxLayout>

class LineEditAction : public QWidgetAction
{
    Q_OBJECT

private:
    QLineEdit *pLineEdit;
public:
    LineEditAction();
    QLineEdit* getLineEdit();
};

#endif // LINEEDITACTION_H
