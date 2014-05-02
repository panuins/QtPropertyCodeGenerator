#include "property.h"
//#include "classtablemodel.h"
#include <QStringList>
#define SaveSeperator "\t"

inline QString boolToStr(bool b)
{
    return b ? QString("t") : QString("f");
}

inline bool strTobool(const QString &str)
{
    return (str == QString("t")) ? true : false;
}

inline QString replaceFisrtLetterToLower(const QString &str)
{
    QString dest = str;
    QString firstLetter = QString(dest.at(0).toLower());
    dest.replace(0, 1, firstLetter);
    return dest;
}

inline QString replaceFisrtLetterToUpper(const QString &str)
{
    QString dest = str;
    QString firstLetter = QString(dest.at(0).toUpper());
    dest.replace(0, 1, firstLetter);
    return dest;
}

Property::Property() :
    m_type(QVariant::typeToName(QVariant::Invalid)),
    m_revision(PropertyDefaultRevision),
    m_constant(PropertyDefaultConstant),
    m_designable(PropertyDefaultDesignable),
    m_enabled(PropertyDefaultEnabled),
    m_final(PropertyDefaultFinal),
    m_member(PropertyDefaultMember),
    m_notify(PropertyDefaultNotify),
    m_read(PropertyDefaultRead),
    m_reset(PropertyDefaultReset),
    m_scriptable(PropertyDefaultScriptable),
    m_stored(PropertyDefaultStored),
    m_user(PropertyDefaultUser),
    m_write(PropertyDefaultWrite)
{
}

Property::Property(//const QString &className,
                   const QString &name,
                   const QString &type,
                   const QString &typeStringName) :
    //m_className(className),
    m_name(name),
    m_type(type),
    m_typeStringName(typeStringName),
    m_revision(PropertyDefaultRevision),
    m_constant(PropertyDefaultConstant),
    m_designable(PropertyDefaultDesignable),
    m_enabled(PropertyDefaultEnabled),
    m_final(PropertyDefaultFinal),
    m_member(PropertyDefaultMember),
    m_notify(PropertyDefaultNotify),
    m_read(PropertyDefaultRead),
    m_reset(PropertyDefaultReset),
    m_scriptable(PropertyDefaultScriptable),
    m_stored(PropertyDefaultStored),
    m_user(PropertyDefaultUser),
    m_write(PropertyDefaultWrite)
{
}

Property::Property(const Property &p) :
    m_docDetail(p.m_docDetail),
    m_docName(p.m_docName),
    m_name(p.m_name),
    m_type(p.m_type),
    m_typeStringName(p.m_typeStringName),
    m_revision(p.m_revision),
    m_constant(p.m_constant),
    m_designable(p.m_designable),
    m_enabled(p.m_enabled),
    m_final(p.m_final),
    m_member(p.m_member),
    m_notify(p.m_notify),
    m_read(p.m_read),
    m_reset(p.m_reset),
    m_scriptable(p.m_scriptable),
    m_stored(p.m_stored),
    m_user(p.m_user),
    m_write(p.m_write)
{
}

Property &Property::operator=(const Property &p)
{
    m_name = p.m_name;
    m_docName = p.m_docName;
    m_docDetail = p.m_docDetail;
    m_type = p.m_type;
    m_typeStringName = p.m_typeStringName;
    m_revision = p.m_revision;
    m_member = p.m_member;
    m_read = p.m_read;
    m_write = p.m_write;
    m_reset = p.m_reset;
    m_notify = p.m_notify;
    m_designable = p.m_designable;
    m_scriptable = p.m_scriptable;
    m_stored = p.m_stored;
    m_user = p.m_user;
    m_constant = p.m_constant;
    m_final = p.m_final;
    m_enabled = p.m_enabled;
    return *this;
}

bool Property::operator==(const Property &p) const
{
    return (m_name == p.m_name)
            && (m_docName == p.m_docName)
            && (m_docDetail == p.m_docDetail)
            && (m_typeStringName == p.m_typeStringName)
            && (m_type == p.m_type)
            && (m_revision == p.m_revision)
            && (m_member == p.m_member)
            && (m_read == p.m_read)
            && (m_write == p.m_write)
            && (m_reset == p.m_reset)
            && (m_notify == p.m_notify)
            && (m_designable == p.m_designable)
            && (m_scriptable == p.m_scriptable)
            && (m_stored == p.m_stored)
            && (m_user == p.m_user)
            && (m_constant == p.m_constant)
            && (m_final == p.m_final)
            && (m_enabled == p.m_enabled);
}

bool Property::operator!=(const Property &p) const
{
    return !((m_name == p.m_name)
             && (m_docName == p.m_docName)
             && (m_docDetail == p.m_docDetail)
             && (m_typeStringName == p.m_typeStringName)
             && (m_type == p.m_type)
             && (m_revision == p.m_revision)
             && (m_member == p.m_member)
             && (m_read == p.m_read)
             && (m_write == p.m_write)
             && (m_reset == p.m_reset)
             && (m_notify == p.m_notify)
             && (m_designable == p.m_designable)
             && (m_scriptable == p.m_scriptable)
             && (m_stored == p.m_stored)
             && (m_user == p.m_user)
             && (m_constant == p.m_constant)
             && (m_final == p.m_final)
             && (m_enabled == p.m_enabled));
}

QString Property::typePrefix() const
{
    std::string strTypeName = m_type.toStdString();
    const char *typeName = strTypeName.c_str();
    QVariant::Type typeId = QVariant::nameToType(typeName);
    QString s = m_typeStringName.isEmpty() ? m_type : m_typeStringName;
    if (typeId == QVariant::Bool)
    {
        s = QString("b");
    }
    else if (typeId == QVariant::Double)
    {
        if (m_typeStringName.isEmpty())
        {
            s = QString("d");
        }
        else if (m_typeStringName == QString("float"))
        {
            s = QString("f");
        }
        else
        {
            s = replaceFisrtLetterToLower(s);
        }
    }
    else if (typeId == QVariant::Int)
    {
        if (m_typeStringName.isEmpty())
        {
            s = QString("n");
        }
        else if ((m_typeStringName == QString("char"))
                 || (m_typeStringName == QString("qint8")))
        {
            s = QString("c");
        }
        else if ((m_typeStringName == QString("unsigned char"))
                 || (m_typeStringName == QString("quint8")))
        {
            s = QString("uc");
        }
        else if ((m_typeStringName == QString("short"))
                 || (m_typeStringName == QString("qint16")))
        {
            s = QString("st");
        }
        else if ((m_typeStringName == QString("quint16")))
        {
            s = QString("w");
        }
        else if ((m_typeStringName == QString("qint32")))
        {
            s = QString("l");
        }
        else if ((m_typeStringName == QString("quint32")))
        {
            s = QString("dw");
        }
        else if ((m_typeStringName == QString("qint64")))
        {
            s = QString("nl");
        }
        else if ((m_typeStringName == QString("quint64")))
        {
            s = QString("unl");
        }
    }
    else
    {
        s = replaceFisrtLetterToLower(s);
    }
    return s;
}

QString Property::toString() const
{
    QString str;
    str = QString("%1"SaveSeperator
                  "%2"SaveSeperator
                  "%3"SaveSeperator
                  "%4"SaveSeperator
                  "%5"SaveSeperator)
            .arg(m_type)
            .arg(m_name)
            .arg(m_typeStringName)
            .arg(m_docName)
            .arg(m_docDetail);
    str += boolToStr(m_member);
    str += QString(SaveSeperator);
    str += boolToStr(m_read);
    str += QString(SaveSeperator);
    str += boolToStr(m_write);
    str += QString(SaveSeperator);
    str += boolToStr(m_reset);
    str += QString(SaveSeperator);
    str += boolToStr(m_notify);
    str += QString(SaveSeperator);
    str += QString::number(m_revision);
    str += QString(SaveSeperator);
    str += boolToStr(m_designable);
    str += QString(SaveSeperator);
    str += boolToStr(m_scriptable);
    str += QString(SaveSeperator);
    str += boolToStr(m_stored);
    str += QString(SaveSeperator);
    str += boolToStr(m_user);
    str += QString(SaveSeperator);
    str += boolToStr(m_constant);
    str += QString(SaveSeperator);
    str += boolToStr(m_final);
    str += QString(SaveSeperator);
    str += boolToStr(m_enabled);
    return str;
}

/*bool Property::writeToSql(QSqlQuery &query)
{
    query.addBindValue(m_name);
    query.addBindValue(m_type);
    query.addBindValue(m_typeStringName);
    query.addBindValue(m_docName);
    query.addBindValue(m_docDetail);
    query.addBindValue(m_member);
    query.addBindValue(m_read);
    query.addBindValue(m_write);
    query.addBindValue(m_reset);
    query.addBindValue(m_notify);
    query.addBindValue(m_revision);
    query.addBindValue(m_designable);
    query.addBindValue(m_scriptable);
    query.addBindValue(m_stored);
    query.addBindValue(m_user);
    query.addBindValue(m_constant);
    query.addBindValue(m_final);
    query.addBindValue(m_enabled);
    return query.exec();
}*/

QString Property::qPropertyString() const
{
    QString str;

    str = QString("Q_PROPERTY(%1 %2")
            .arg(realTypeName())
            .arg(m_name);
#define AddBoolProperty(MEMBER, MARCO, QTNAME) \
    if (m_##MEMBER != PropertyDefault##MARCO) \
    { \
    str += QString(" ") + #QTNAME + QString(" ") \
    + ((m_##MEMBER) ? "true" : "false"); \
}
    AddBoolProperty(member, Member, MEMBER);
    if (m_member)
    {
        str += QString(" MEMBER ") + memberVariableName();
    }
    if (m_read)
    {
        str += QString(" READ ") + readFunctionName();
    }
    if (m_write)
    {
        str += QString(" WRITE ") + writeFunctionName();
    }
    AddBoolProperty(reset, Reset, RESET);
    if (m_notify)
    {
        str += QString(" NOTIFY ") + signalName();
    }
    if (m_revision != PropertyDefaultRevision)
    {
        str += QString(" REVISION %1").arg(m_revision);
    }
    AddBoolProperty(designable, Designable, DESIGNABLE);
    AddBoolProperty(scriptable, Scriptable, SCRIPTABLE);
    AddBoolProperty(stored, Stored, STORED);
    AddBoolProperty(user, User, USER);
    if (m_constant != PropertyDefaultConstant)
    {
        str += QString(" CONSTANT");
    }
    if (m_final != PropertyDefaultFinal)
    {
        str += QString(" FINAL");
    }
    str += QString(")\n");
    return str;
}

QString Property::readFunctionName() const
{
    QString s;
    s = replaceFisrtLetterToUpper(m_name);
    return s;
}

QString Property::writeFunctionName() const
{
    QString s;
    s = QString("Set%1").arg(replaceFisrtLetterToUpper(m_name));
    return s;
}

QString Property::signalName() const
{
    return QString("%1Changed").arg(readFunctionName());
}

QString Property::memberVariableName() const
{
    QString s;
    s = QString("m_%1%2")
            .arg(typePrefix())
            .arg(replaceFisrtLetterToUpper(m_name));
    return s;
}

QString Property::readDeclear() const
{
    QString s;
    s = QString("%1 %2() const;\n")
            .arg(realTypeName())
            .arg(readFunctionName());
    return s;
}

QString Property::writeDeclear() const
{
    QString s;
    s = QString("void %1(const %2 &%3);\n")
            .arg(writeFunctionName())
            .arg(realTypeName())
            .arg(writeFunctionArgumentName());
    return s;
}

QString Property::signalDeclear() const
{
    QString s;
    s = QString("void %1();\n").arg(signalName());
    return s;
}

QString Property::memberVariableDeclear() const
{
    QString s;
    s = QString("%1 %2;    /**< %3 */\n")
            .arg(realTypeName())
            .arg(memberVariableName())
            .arg(m_docName);
    return s;
}

QString Property::readFunctionDefine(const QString &className,
                                     bool isInline) const
{
    QString s("");
    if (!m_docName.isEmpty())
    {
        s += QString("/**\n"
                     " * @brief 返回属性%1的值\n"
                     " * @return 属性%2的值\n"
                     " * @details 返回属性%3的值\n"
                     " */\n")
                .arg(m_docName)
                .arg(m_docName)
                .arg(m_docName);
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += QString("%1 %2::%3() const\n"
                 "{\n"
                 "    return %4;\n"
                 "}\n")
            .arg(realTypeName())
            .arg(className)
            .arg(readFunctionName())
            .arg(memberVariableName());
    return s;
}

QString Property::writeFunctionDefine(const QString &className,
                                      const QString &strBeforSetValue,
                                      const QString &strBetweenSetValueAndEmit,
                                      const QString &strAfterEmit,
                                      bool emitSignal,
                                      bool isInline) const
{
    QString s("");
    if (!m_docName.isEmpty())
    {
        s += QString("/**\n"
                     " * @brief 设置属性%1的值\n"
                     " * @param %2 %3\n"
                     " * @details 设置属性%4的值")
                .arg(m_docName)
                .arg(writeFunctionArgumentName())
                .arg(m_docName)
                .arg(m_docName);
        if (!m_docDetail.isEmpty())
        {
            s += QString("，") + m_docDetail;
        }
        if (emitSignal)
        {
            s += "，并发射信号" + signalName();
        }
        s += "。\n"
                " */\n";
    }
    if (isInline)
    {
        s += "inline ";
    }
    s += QString("void %1::%2(const %3 &%4)\n"
                 "{\n"
                 "%5"
                 "    %6 = %7;\n"
                 "%8")
            .arg(className)
            .arg(writeFunctionName())
            .arg(realTypeName())
            .arg(writeFunctionArgumentName())
            .arg(strBeforSetValue)
            .arg(memberVariableName())
            .arg(writeFunctionArgumentName())
            .arg(strBetweenSetValueAndEmit);
    if (emitSignal)
    {
        s += QString("    emit %1();\n").arg(signalName());
    }
    s += strAfterEmit;
    s += QString("}\n");
    return s;
}

Property Property::fromString(const QString &str)
{
    QStringList list = str.split(QChar(SaveSeperator[0]));
    Property p(list.at(1),
               list.at(0),
               list.at(2));
    int i = 3;
    p.setDocName(list.at(i));
    i++;
    p.setDocDetail(list.at(i));
    i++;
    p.setMember(strTobool(list.at(i)));
    i++;
    p.setRead(strTobool(list.at(i)));
    i++;
    p.setWrite(strTobool(list.at(i)));
    i++;
    p.setReset(strTobool(list.at(i)));
    i++;
    p.setNotify(strTobool(list.at(i)));
    i++;
    p.setRevision(list.at(i).toInt());
    i++;
    p.setDesignable(strTobool(list.at(i)));
    i++;
    p.setScriptable(strTobool(list.at(i)));
    i++;
    p.setStored(strTobool(list.at(i)));
    i++;
    p.setUser(strTobool(list.at(i)));
    i++;
    p.setConstant(strTobool(list.at(i)));
    i++;
    p.setFinal(strTobool(list.at(i)));
    i++;
    p.setEnabled(strTobool(list.at(i)));
    return p;
}

QString Property::writeFunctionArgumentName() const
{
    return QString("A") + typePrefix();
}
