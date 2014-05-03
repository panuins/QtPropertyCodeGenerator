/*****************************************************************************
 * propertiesgroup.cpp:
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
#include "propertiesgroup.h"

QStringList PropertiesGroup::enumsName() const
{
    QStringList list;
    foreach (EnumType e, m_d->m_enums)
    {
        list.append(e.name());
    }
    return list;
}

QStringList PropertiesGroup::existType() const
{
    QStringList list;
    foreach (Property p, m_d->m_properties)
    {
        list.append(p.realTypeName());
    }
    list.sort();
    list.removeDuplicates();
    return list;
}

int PropertiesGroup::find(const QString &name) const
{
    int i = 0;
    for (; i < m_d->m_properties.size(); i++)
    {
        if (m_d->m_properties.at(i).name() == name)
        {
            return i;
        }
    }
    return -1;
}

QString PropertiesGroup::parentClass() const
{
    QString strParent("");
    switch (m_d->p_typeInderitsInfomation)
    {
    case 1:
        strParent = "QObject";
        break;
    case 2:
    case 4:
        strParent = "QWidget";
        break;
    case 3:
        strParent = "QQuickItem";
        break;
    default:
        break;
    }
    return strParent;
}

QList<Property> PropertiesGroup::propertiesIsType(const QString &var) const
{
    QList<Property> listP;
    foreach (Property p, m_d->m_properties)
    {
        if (p.realTypeName() == var)
        {
            listP.append(p);
        }
    }
    return listP;
}

QStringList PropertiesGroup::propertiesName() const
{
    QStringList list;
    foreach (Property p, m_d->m_properties)
    {
        list.append(p.name());
    }
    return list;
}

void PropertiesGroup::append(const Property &var)
{
    beforeWrite();
    if (!m_d->p_typeOrder.contains(var.realTypeName()))
    {
        m_d->p_typeOrder.append(var.realTypeName());
    }
    m_d->m_properties.append(var);
}

void PropertiesGroup::append(const QList<Property> &var)
{
    beforeWrite();
    foreach (Property p, var)
    {
        if (!m_d->p_typeOrder.contains(p.realTypeName()))
        {
            m_d->p_typeOrder.append(p.realTypeName());
        }
    }
    m_d->m_properties.append(var);
}

void PropertiesGroup::sort()
{
    beforeWrite();
    {
        int i = 0, j = 0;
        QStringList list = this->propertiesName();
        QList<Property> listP;
        list.sort();
        list.removeDuplicates();
        for (; i < list.size(); i++)
        {
            bool found = false;
            for (j = 0; (j < m_d->m_properties.size()) && (!found); j++)
            {
                if (m_d->m_properties.at(j).name() == list.at(i))
                {
                    listP.append(m_d->m_properties.at(j));
                    found = true;
                }
            }
            /*if (!found)
            {
                std::cout << "PropertiesGroup::sort: Can not find property "
                          << list.at(i).toStdString() << std::endl;
            }*/
        }
        m_d->m_properties = listP;
    }
    {
        int i = 0, j = 0;
        QStringList list = this->enumsName();
        QList<EnumType> listE;
        list.sort();
        list.removeDuplicates();
        for (; i < list.size(); i++)
        {
            bool found = false;
            for (j = 0; (j < m_d->m_enums.size()) && (!found); j++)
            {
                if (m_d->m_enums.at(j).name() == list.at(i))
                {
                    listE.append(m_d->m_enums.at(j));
                    found = true;
                }
            }
            /*if (!found)
            {
                std::cout << "PropertiesGroup::sort: Can not find enum type "
                          << list.at(i).toStdString() << std::endl;
            }*/
        }
        m_d->m_enums = listE;
    }
}

QString PropertiesGroup::generateEnumsDeclear() const
{
    QString enums("");
    foreach (EnumType e, m_d->m_enums)
    {
        if (e.enabled())
        {
            enums.append(e.declear() + "\n");
        }
    }
    return enums;
}

QString PropertiesGroup::generateQPropertyDeclear() const
{
    QString qProperty("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            qProperty.append(QString("    ")
                             + p.qPropertyString());
        }
    }
    return qProperty;
}

QString PropertiesGroup::generateReadDeclear() const
{
    QString readDeclear("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            readDeclear.append(QString("    ")
                               + p.readDeclear());
        }
    }
    return readDeclear;
}

QString PropertiesGroup::generateWriteDeclear() const
{
    QString writeDeclear("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            writeDeclear.append(QString("    ")
                                + p.writeDeclear());
        }
    }
    return writeDeclear;
}

QString PropertiesGroup::generateSignalDeclear() const
{
    QString signalDeclear("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled() && p.notify())
        {
            signalDeclear.append(QString("    ")
                                 + p.signalDeclear());
        }
    }
    return signalDeclear;
}

QString PropertiesGroup::generateMemberVariableDeclear() const
{
    QString memberVars("");
    foreach (QString s, m_d->p_typeOrder)
    {
        QList<Property> listP = propertiesIsType(s);
        foreach (Property p, listP)
        {
            if (p.enabled())
            {
                memberVars.append(QString("    ")
                                  + p.memberVariableDeclear());
            }
        }
    }
    return memberVars;
}

QString PropertiesGroup::generateReadFunctionDefine() const
{
    QString readFunctions("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            readFunctions.append(p.readFunctionDefine(m_d->p_className,
                                                      m_d->p_readFunctionIsInline)
                                 + "\n");
        }
    }
    return readFunctions;
}

QString PropertiesGroup::generateWriteFunctionDefine() const
{
    QString writeFunctions("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            writeFunctions.append(p.writeFunctionDefine(
                                      m_d->p_className,
                                      m_d->p_statementsStartWriteProperty,
                                      m_d->p_statementsMiddleWriteProperty,
                                      m_d->p_statementsAfterWriteProperty,
                                      (m_d->p_writeFunctionEmitSignal)
                                      && ((m_d->p_typeInderitsInfomation == 1)
                                          || (m_d->p_typeInderitsInfomation == 2)
                                          || (m_d->p_typeInderitsInfomation == 3)),
                                      m_d->p_writeFunctionIsInline)
                                  + "\n");
        }
    }
    return writeFunctions;
}

QString PropertiesGroup::argumentNameOfThisClass() const
{
    return QString("var");
}

QString PropertiesGroup::headerFileContent() const
{
    QString inlineFunctionsDefine;
    if (m_d->p_readFunctionIsInline)
    {
        inlineFunctionsDefine += generateReadFunctionDefine();
    }
    if (m_d->p_writeFunctionIsInline)
    {
        inlineFunctionsDefine += generateWriteFunctionDefine();
    }
    if (m_d->p_typeInderitsInfomation == 0)
    {
        if (m_d->p_inherits.isEmpty())
        {
            QString c("#ifndef %1\n"
                      "#define %1\n\n"
                      "%2\n"
                      "class %3\n"
                      "{\n"
                      "public:\n"
                      "    %3();\n"
                      "    %3(const %3 &%4);\n"
                      "    ~%3();\n"
                      "    %3 &operator=(const %3 &%4);\n\n"
                      "%5\n"
                      "%6\n"
                      "private:\n"
                      "%7"
                      "};\n\n"
                      "%8"
                      "#endif // %1");
            c = c.arg(headerFileMarco())
                    .arg(headerFileIncludeStatements())
                    .arg(m_d->p_className)
                    .arg(argumentNameOfThisClass())
                    .arg(generateReadDeclear())
                    .arg(generateWriteDeclear())
                    .arg(generateMemberVariableDeclear())
                    .arg(inlineFunctionsDefine);
            return c;
        }
        else
        {
            QString c("#ifndef %1\n"
                      "#define %1\n\n"
                      "%2\n"
                      "class %3 : public %4\n"
                      "{\n"
                      "public:\n"
                      "    %3();\n"
                      "    %3(const %3 &%5);\n"
                      "    ~%3();\n\n"
                      "    %3 &operator=(const %3 &%5);\n\n"
                      "%6\n"
                      "%7\n"
                      "private:\n"
                      "%8"
                      "};\n\n"
                      "%9"
                      "#endif // %1");
            c = c.arg(headerFileMarco())
                    .arg(headerFileIncludeStatements())
                    .arg(m_d->p_className)
                    .arg(m_d->p_inherits)
                    .arg(argumentNameOfThisClass())
                    .arg(generateReadDeclear())
                    .arg(generateWriteDeclear())
                    .arg(generateMemberVariableDeclear())
                    .arg(inlineFunctionsDefine);
            return c;
        }
    }
    else if (m_d->p_typeInderitsInfomation == inherits_QWidget_associateWidthUiFile)
    {
        QString c("#ifndef %1\n"
                  "#define %1\n\n"
                  "%2\n"
                  "namespace Ui {\n"
                  "class %3;\n"
                  "}\n\n"
                  "class %3 : public %4\n"
                  "{\n"
                  "    Q_OBJECT\n"
                  "%5\n"
                  "public:\n"
                  "    explicit %3(%6 *%7 = 0);\n"
                  "    ~%3();\n\n"
                  "%8\n"
                  "public slots:\n"
                  "%9\n"
                  "signals:\n"
                  "%10\n"
                  "private:\n"
                  "    Ui::%3 *ui;\n"
                  "%11"
                  "};\n\n"
                  "%12"
                  "#endif // %1");
        c = c.arg(headerFileMarco())
                .arg(headerFileIncludeStatements())
                .arg(m_d->p_className)
                .arg(m_d->p_inherits)
                .arg(generateQPropertyDeclear())
                .arg(parentClass())
                .arg(qOjbectBasedParentArgumentName())
                .arg(generateReadDeclear())
                .arg(generateWriteDeclear())
                .arg(generateSignalDeclear())
                .arg(generateMemberVariableDeclear())
                .arg(inlineFunctionsDefine);
        return c;
    }
    else
    {
        QString c("#ifndef %1\n"
                  "#define %1\n\n"
                  "%2\n"
                  "class %3 : public %4\n"
                  "{\n"
                  "    Q_OBJECT\n"
                  "%5\n"
                  "public:\n"
                  "    explicit %3(%6 *%7 = 0);\n"
                  "    ~%3();\n\n"
                  "%8\n"
                  "public slots:\n"
                  "%9\n"
                  "signals:\n"
                  "%10\n"
                  "private:\n"
                  "%11"
                  "};\n\n"
                  "%12"
                  "#endif // %1");
        c = c.arg(headerFileMarco())
                .arg(headerFileIncludeStatements())
                .arg(m_d->p_className)
                .arg(m_d->p_inherits)
                .arg(generateQPropertyDeclear())
                .arg(parentClass())
                .arg(qOjbectBasedParentArgumentName())
                .arg(generateReadDeclear())
                .arg(generateWriteDeclear())
                .arg(generateSignalDeclear())
                .arg(generateMemberVariableDeclear())
                .arg(inlineFunctionsDefine);
        return c;
    }
}

QString PropertiesGroup::headerFileIncludeStatements() const
{
    QStringList list;
    QString type;
    QString includes("");
    if (!m_d->p_inherits.isEmpty())
    {
        if (m_d->p_inherits.startsWith("Q"))
        {
            list.append(m_d->p_inherits);
        }
        else
        {
            includes = QString("#include \"%1\"\n").arg(m_d->p_inherits);
        }
    }
    foreach (type, m_d->p_typeOrder)
    {
        if (!type.isEmpty())
        {
            if (type.startsWith("Q"))
            {
                list.append(type);
            }
        }
    }
    list.sort();
    list.removeDuplicates();
    foreach (type, list)
    {
        includes += QString("#include <%1>\n").arg(type);
    }
    return includes;
}

QString PropertiesGroup::headerFileMarco() const
{
    return QString("%1_H").arg(m_d->p_className.toUpper());
}

QString PropertiesGroup::headerFileName() const
{
    return QString("%1.h").arg(m_d->p_className.toLower());
}

QString PropertiesGroup::qOjbectBasedParentArgumentName() const
{
    return QString("parent");
}

QString PropertiesGroup::sourceFileAssignmentOperator() const
{
    QString define;
    if (m_d->p_typeInderitsInfomation == 0)
    {
        define = QString("/**\n"
                         " * @brief 赋值运算符\n"
                         " * @param var 要赋值的对象\n"
                         " * @details 赋值运算符。\n"
                         " */\n"
                         "%1 &%1::operator=(const %1 &%2)\n"
                         "{\n"
                         "%3"
                         "    return *this;\n"
                         "}\n")
                .arg(m_d->p_className)
                .arg(argumentNameOfThisClass());
        QString memberInit("");
        foreach (QString s, m_d->p_typeOrder)
        {
            QList<Property> listP = propertiesIsType(s);
            foreach (Property p, listP)
            {
                if (p.enabled())
                {
                    memberInit.append(QString("    %1 = %2.%1;\n")
                                      .arg(p.memberVariableName())
                                      .arg(argumentNameOfThisClass()));
                }
            }
        }
        define = define.arg(memberInit);
        return define;
    }
    else
    {
        return QString("");
    }
}

QString PropertiesGroup::sourceFileContent() const
{
    QString c("");
    if (m_d->p_typeInderitsInfomation == 0)
    {
        c = QString("#include \"%1\"\n\n"
                    "%2\n"
                    "%3\n"
                    "%4\n"
                    "%5\n")
                .arg(headerFileName())
                .arg(sourceFileDefaultConstructor())
                .arg(sourceFileCopyConstructor())
                .arg(sourceFileAssignmentOperator())
                .arg(sourceFileDestructor());
    }
    else if (m_d->p_typeInderitsInfomation == inherits_QWidget_associateWidthUiFile)
    {
        c = QString("#include \"%1\"\n"
                    "#include \"ui_%2\"\n\n"
                    "%3\n"
                    "%4\n")
                .arg(headerFileName())
                .arg(headerFileName().toLower())
                .arg(sourceFileDefaultConstructor())
                .arg(sourceFileDestructor());
    }
    else
    {
        c = QString("#include \"%1\"\n\n"
                    "%2\n"
                    "%3\n")
                .arg(headerFileName())
                .arg(sourceFileDefaultConstructor())
                .arg(sourceFileDestructor());
    }
    if (!m_d->p_readFunctionIsInline)
    {
        c += generateReadFunctionDefine();
    }
    if (!m_d->p_writeFunctionIsInline)
    {
        c += generateWriteFunctionDefine();
    }
    return c;
}

QString PropertiesGroup::sourceFileCopyConstructor() const
{
    QString define;
    if (m_d->p_typeInderitsInfomation == 0)
    {
        define = QString("/**\n"
                         " * @brief 拷贝构造函数\n"
                         " * @param var 被拷贝的对象\n"
                         " * @details 拷贝构造函数。\n"
                         " */\n"
                         "%1::%1(const %1 &%2)%3\n"
                         "{\n"
                         "}\n")
                .arg(m_d->p_className)
                .arg(argumentNameOfThisClass());
        QString memberInit("");
        foreach (QString s, m_d->p_typeOrder)
        {
            QList<Property> listP = propertiesIsType(s);
            foreach (Property p, listP)
            {
                if (p.enabled())
                {
                    memberInit.append(QString(",\n    %1(%2.%1)")
                                      .arg(p.memberVariableName())
                                      .arg(argumentNameOfThisClass()));
                }
            }
            if (memberInit.startsWith(QString(",")))
            {
                memberInit.replace(0, 1, QString(" :"));
            }
        }
        define = define.arg(memberInit);
        return define;
    }
    else
    {
        return QString("");
    }
}

QString PropertiesGroup::sourceFileDefaultConstructor() const
{
    QString memberInit("");
    QString define;
    if (m_d->p_typeInderitsInfomation == 0)
    {
        define = QString("/**\n"
                         " * @brief 默认构造函数\n"
                         " * @details 默认构造函数。\n"
                         " */\n"
                         "%1::%1()%2\n"
                         "{\n"
                         "}\n")
                .arg(m_d->p_className);
    }
    else if (m_d->p_typeInderitsInfomation == inherits_QWidget_associateWidthUiFile)
    {
        define = QString("/**\n"
                         " * @brief 默认构造函数\n"
                         " * @param parent 父对象\n"
                         " * @details 默认构造函数\n"
                         " */\n"
                         "%1::%1(%2 *%3) :\n"
                         "    %4(%3),\n"
                         "    ui(new Ui::%1)%5\n"
                         "{\n"
                         "    ui->setupUi(this);\n"
                         "}\n")
                .arg(m_d->p_className)
                .arg(parentClass())
                .arg(qOjbectBasedParentArgumentName())
                .arg(m_d->p_inherits);
    }
    else
    {
        define = QString("/**\n"
                         " * @brief 默认构造函数\n"
                         " * @param parent 父对象\n"
                         " * @details 默认构造函数\n"
                         " */\n"
                         "%1::%1(%2 *%3) :\n"
                         "    %4(%3)%5\n"
                         "{\n"
                         "}\n")
                .arg(m_d->p_className)
                .arg(parentClass())
                .arg(qOjbectBasedParentArgumentName())
                .arg(m_d->p_inherits);
    }
    foreach (QString s, m_d->p_typeOrder)
    {
        QList<Property> listP = propertiesIsType(s);
        foreach (Property p, listP)
        {
            if (p.enabled())
            {
                if (!p.defaultValue().toString().isEmpty())
                {
                    memberInit.append(QString(",\n    %1(%2)")
                                      .arg(p.memberVariableName())
                                      .arg(p.defaultValue().toString()));
                }
            }
        }
        if (m_d->p_typeInderitsInfomation == 0)
        {
            if (memberInit.startsWith(QString(",")))
            {
                memberInit.replace(0, 1, QString(" :"));
            }
        }
    }
    define = define.arg(memberInit);
    return define;
}

QString PropertiesGroup::sourceFileDestructor() const
{
    QString define;
    if (m_d->p_typeInderitsInfomation == 0)
    {
        define = QString("/**\n"
                         " * @brief 析构函数\n"
                         " * @details 析构函数。\n"
                         " */\n"
                         "%1::~%1()\n"
                         "{\n"
                         "}\n")
                .arg(m_d->p_className);
    }
    else if (m_d->p_typeInderitsInfomation == inherits_QWidget_associateWidthUiFile)
    {
        define = QString("/**\n"
                         " * @brief 析构函数\n"
                         " * @details 析构函数。\n"
                         " */\n"
                         "%1::~%1()\n"
                         "{\n"
                         "    delete ui;\n"
                         "}\n")
                .arg(m_d->p_className);
    }
    else
    {
        define = QString("/**\n"
                         " * @brief 析构函数\n"
                         " * @details 析构函数。\n"
                         " */\n"
                         "%1::~%1()\n"
                         "{\n"
                         "}\n")
                .arg(m_d->p_className);
    }
    return define;
}

QString PropertiesGroup::sourceFileName() const
{
    return QString("%1.cpp").arg(m_d->p_className.toLower());
}
