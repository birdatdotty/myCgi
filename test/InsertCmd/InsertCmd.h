#ifndef INSERTCMD_H
#define INSERTCMD_H

#include <QString>
#include <QStringList>

class InsertCmd {
public:
    InsertCmd(QString& obj, QString& script): script(script) {
        QChar ch;
        int prefixSize = obj.size()+1; // 'Obj\0' - 4 symbols
        for (i = prefixSize; i < script.size(); i++) {
            ch = script[i];
            // specsymbol: '\'
            if (testEsc(ch)) {} // if (itsEsc) word += ch;
            // char:
            else if (
                    ((ch >= 'A') && (ch <= 'Z'))
                    ||
                    ((ch >= 'a') && (ch <= 'z'))
                    ||
                    ((ch >= 0x30) && (ch <= 0x39))
                    ||
                    (ch == '_')
               ) word += ch;
            // specsymbol: '"', ')', or '('
            else if (testQuot(ch)) {} // if (itsQuot == true) then word += ch
            else if (ch == '(') {
                wordFinish();
                itsArg = true;
                _args.clear();
            }
            else if (ch == ')') {
                wordFinish();
                itsArg = false;
                invokableArgs << _args;
                _args.clear();
            }
            // finish:
            else {
                wordFinish();

            }
        }
        i = invokable.size();
    }
    int count() const {
        return i;
    }
    QString fun(int i) const {
        return invokable.at(i);
    }
    QStringList args(int i) const {
        return invokableArgs.at(i);
    }

private:
    int i;
    QString word;
    QString method;
    QStringList _args;

    bool itsArg = false;
    bool itsQuot = false;
    bool itsEsc = false;

    QString script;
    QList<QString> invokable;
    QList<QStringList> invokableArgs;

    bool testEsc(QChar& ch) {
        if (itsEsc) {
            word += ch;
            itsEsc = false;

            return true;
        }
        if (ch == '\\') {
            itsEsc = true;
            return true;
        }

        itsEsc = false;
        return false;
    }
    bool testQuot(QChar& ch) {
        if (ch == '"') {
            itsQuot = !itsQuot;
            return true;
        }

        if (itsQuot) {
            word += ch;

            return true;
        }

        return false;
    }
    void wordFinish() {
        if (word.size() > 0) {
            if (itsArg)
                _args.append(word);
            else
                invokable << word;
        }

        word.clear();
    }

};

#endif // INSERTCMD_H
