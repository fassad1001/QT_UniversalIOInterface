#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>

class CTextEdit : public QTextEdit
{
    Q_OBJECT
private:
    int maxCountSimbolLine;
    int maxCountLine;
public:
    explicit CTextEdit(QWidget *parent = 0);
    explicit CTextEdit(const QString &text, QWidget *parent = 0);

    void SetMaxCountSimbolLine(int value);
    void SetMaxCountLine(int value);

    int MaxCountSimbolLine();
    int MaxCountLine();
protected:
    virtual void keyPressEvent(QKeyEvent *e);

private slots:
    void textChanged();
};

#endif // TEXTEDIT_H
