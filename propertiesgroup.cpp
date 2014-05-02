#include "propertiesgroup.h"

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

QStringList PropertiesGroup::propertiesName() const
{
    QStringList list;
    foreach (Property p, m_d->m_properties)
    {
        list.append(p.name());
    }
    return list;
}

void PropertiesGroup::sort()
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
            std::cout << "PropertiesGroup::sortProperties: Can not find property "
                      << list.at(i).toStdString() << std::endl;
        }*/
    }
    m_d->m_properties = listP;
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
        if (p.enabled())
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
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            memberVars.append(QString("    ")
                              + p.memberVariableDeclear());
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

QString PropertiesGroup::parentClass() const
{
    QString strParent("");
    switch (m_d->p_typeInderitsInfomation)
    {
    case 1:
        strParent = "QObject";
        break;
    case 2:
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

QString PropertiesGroup::headerFileName() const
{
    return QString("%1.h").arg(m_d->p_className);
}

QString PropertiesGroup::headerFileMarco() const
{
    return QString("%1_H").arg(m_d->p_className.toUpper());
}

QString PropertiesGroup::headerFileContent() const
{
    QString includeFile("");
    if (!m_d->p_inherits.isEmpty())
    {
        if (m_d->p_inherits.startsWith("Q"))
        {
            includeFile = QString("#include <%1>\n\n").arg(m_d->p_inherits);
        }
        else
        {
            includeFile = QString("#include \"%1\"\n\n").arg(m_d->p_inherits);
        }
    }
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
                      "%2"
                      "class %3\n"
                      "{\n"
                      "public:\n"
                      "    %3();\n"
                      "    %3(const %3 &var);\n"
                      "%4\n"
                      "%5\n"
                      "private:\n"
                      "%6"
                      "};\n\n"
                      "%7"
                      "#endif // %1");
            c = c.arg(headerFileMarco())
                    .arg(includeFile)
                    .arg(m_d->p_className)
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
                      "%2"
                      "class %3 : public %4\n"
                      "{\n"
                      "public:\n"
                      "    %3();\n"
                      "    %3(const %3 &var);\n"
                      "%5\n"
                      "%6\n"
                      "private:\n"
                      "%7"
                      "};\n\n"
                      "%8"
                      "#endif // %1");
            c = c.arg(headerFileMarco())
                    .arg(includeFile)
                    .arg(m_d->p_className)
                    .arg(m_d->p_inherits)
                    .arg(generateReadDeclear())
                    .arg(generateWriteDeclear())
                    .arg(generateMemberVariableDeclear())
                    .arg(inlineFunctionsDefine);
            return c;
        }
    }
    else
    {
        QString c("#ifndef %1\n"
                  "#define %1\n\n"
                  "%2"
                  "class %3 : public %4\n"
                  "{\n"
                  "    Q_OBJECT\n"
                  "%6\n"
                  "public:\n"
                  "    explicit %3(%5 *parent = 0);\n"
                  "%7\n"
                  "public slots:\n"
                  "%8\n"
                  "signals:\n"
                  "%9\n"
                  "private:\n"
                  "%10"
                  "};\n\n"
                  "%11"
                  "#endif // %1");
        c = c.arg(headerFileMarco())
                .arg(includeFile)
                .arg(m_d->p_className)
                .arg(m_d->p_inherits)
                .arg(parentClass())
                .arg(generateQPropertyDeclear())
                .arg(generateReadDeclear())
                .arg(generateWriteDeclear())
                .arg(generateSignalDeclear())
                .arg(generateMemberVariableDeclear())
                .arg(inlineFunctionsDefine);
        return c;
    }
}

QString PropertiesGroup::sourceFileName() const
{
    return QString("%1.cpp").arg(m_d->p_className);
}

QString PropertiesGroup::sourceFileDefaultInitial() const
{
    QString memberInit("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            memberInit.append(QString(",\n    ")
                              + p.initialToDefaultValueStatement());
        }
    }
    return memberInit;
}

QString PropertiesGroup::sourceFileCopyInitial() const
{
    QString memberInit("");
    foreach (Property p, m_d->m_properties)
    {
        if (p.enabled())
        {
            memberInit.append(QString(",\n    ")
                              + p.initialToSpecifyValueStatement(
                                  QString("var.%1")
                                  .arg(p.memberVariableName())));
        }
    }
    return memberInit;
}

QString PropertiesGroup::sourceFileContent() const
{
    QString includeFile;
    if (m_d->p_inherits.startsWith("Q"))
    {
        includeFile = QString("<%1>").arg(m_d->p_inherits);
    }
    else
    {
        includeFile = QString("\"%1\"").arg(m_d->p_inherits);
    }
    if (m_d->p_typeInderitsInfomation == 0)
    {
        QString c("#include \"%1\"\n\n"
                  "/**\n"
                  " * @brief 默认构造函数\n"
                  " * @details 默认构造函数。\n"
                  " */\n"
                  "%2::%2()%3\n"
                  "{\n"
                  "};\n\n"
                  "/**\n"
                  " * @brief 拷贝构造函数\n"
                  " * @param var 被拷贝的对象\n"
                  " * @details 拷贝构造函数。\n"
                  " */\n"
                  "%2::%2(const %2 &var)%4\n"
                  "{\n"
                  "};\n\n");
        QString strDefault = sourceFileDefaultInitial();
        QString strCopy = sourceFileCopyInitial();
        if (!strDefault.isEmpty())
        {
            strDefault.replace(0, 1, QString(" :"));
        }
        if (!strCopy.isEmpty())
        {
            strCopy.replace(0, 1, QString(" :"));
        }
        c = c.arg(headerFileName())
                .arg(m_d->p_className)
                .arg(strDefault)
                .arg(strCopy);
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
    else
    {
        QString c("#include \"%1\"\n\n"
                  "/**\n"
                  " * @brief 默认构造函数\n"
                  " * @param parent 父对象\n"
                  " * @details 默认构造函数\n"
                  " */\n"
                  "%2::%2(%3 *parent) :\n"
                  "    %4(parent)%5\n"
                  "{\n"
                  "};\n\n");
        c = c.arg(headerFileName())
                .arg(m_d->p_className)
                .arg(parentClass())
                .arg(m_d->p_inherits)
                .arg(sourceFileDefaultInitial());
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
}

