#include "CTextEdit.h"
#include <QTextBlock>
#include <QKeyEvent>

CTextEdit::CTextEdit(QWidget *parent) :
    QTextEdit(parent), maxCountSimbolLine(100), maxCountLine(2)
{
    connect(this, SIGNAL(textChanged()), SLOT(textChanged()));
}

CTextEdit::CTextEdit(const QString &text, QWidget *parent) :
    QTextEdit(text, parent), maxCountSimbolLine(100), maxCountLine(2)
{
    connect(this, SIGNAL(textChanged()), SLOT(textChanged()));
}

void CTextEdit::keyPressEvent(QKeyEvent *e)
{
    if ((e->key() == Qt::Key_Enter || e->key() == 16777220) && document()->blockCount() == maxCountLine) {
        return;
    }

    QTextEdit::keyPressEvent(e);
}

void CTextEdit::textChanged()
{
    int sumLenght = 0;
    for (int i = 0; i < 2; i++) {
        QTextBlock textBlock = document()->findBlockByLineNumber(i);
        if (textBlock.length() > maxCountSimbolLine) {
            QTextCursor cursor(textBlock);
            cursor.setPosition(maxCountSimbolLine + sumLenght);
            cursor.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
            cursor.removeSelectedText();
        }

        sumLenght += textBlock.length();
    }
}

void CTextEdit::SetMaxCountSimbolLine(int value)
{
    maxCountSimbolLine = value;
}

void CTextEdit::SetMaxCountLine(int value)
{
    maxCountLine = value;
}

int CTextEdit::MaxCountSimbolLine()
{
    return maxCountSimbolLine;
}

int CTextEdit::MaxCountLine()
{
    return maxCountLine;
}
