#ifndef SHAREDFUNCTIONS_H
#define SHAREDFUNCTIONS_H

#include <QRegExp>
#include <iostream>

inline bool nameIsCIndentifier(const QString &name)
{
    QRegExp exp(QString("[0-9a-zA-Z_]*"));
    if (!exp.exactMatch(name))
    {
        std::cerr << "nameIsCIndentifier: class name "
                  << name.toStdString() << " is not a valid c++ identifier."
                  << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

#endif // SHAREDFUNCTIONS_H
