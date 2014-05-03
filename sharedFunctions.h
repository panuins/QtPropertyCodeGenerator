/*****************************************************************************
 * sharedFunctions.h:
 *****************************************************************************
 * Authors: panuins <panuins@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GPLv2 or later as published by the Free Software
 * Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *****************************************************************************/
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
