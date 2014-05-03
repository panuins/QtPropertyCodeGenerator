#ifndef PROPERTYINLINEFUNCTIONS_H
#define PROPERTYINLINEFUNCTIONS_H
#ifdef DEBUG_PROPERTYS_COW_DETAIL
#include <iostream>
#endif

inline Property::Property() :
    m_d(new PropertyData())
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: default constructor. id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(//const QString &className,
                          const QString &name,
                          const QString &type,
                          const QString &typeStringName) :
    m_d(new PropertyData(name, type, typeStringName))
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: constructor(const QString &, "
                 "const QString &, "
                 "const QString &). id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(const Property &p) :
    m_d(p.m_d)
{
    m_d->m_used++;
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: copy constructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline Property::Property(const PropertyData &p) :
    m_d(new PropertyData(p))
{
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: copy constructor(PropertyData). "
                 "used=" << m_d->m_used
              << " id=" << m_d->m_id
              << ". p used=" << p.m_used
              << " p id=" << p.m_id << std::endl;
#endif
}

inline Property::~Property()
{
    m_d->m_used--;
    if (m_d->m_used == 0)
    {
        delete m_d;
    }
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property: destructor. used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
}

inline Property &Property::operator=(const Property &p)
{
    if (p.m_d != m_d)
    {
        p.m_d->m_used++;
        m_d->m_used--;
        if (m_d->m_used == 0)
        {
            delete m_d;
        }
        m_d = p.m_d;
#ifdef DEBUG_PROPERTYS_COW_DETAIL
        std::cout << "Property::operator=. used=" << m_d->m_used
                  << " id=" << m_d->m_id
                  << ". p used=" << p.m_d->m_used
                  << " p id=" << p.m_d->m_id << std::endl;
#endif
    }
    return *this;
}

inline bool Property::constant() const
{
    return m_d->m_constant;
}

inline bool Property::designable() const
{
    return m_d->m_designable;
}

inline QString Property::docDetail() const
{
    return m_d->m_docDetail;
}

inline QString Property::docName() const
{
    return m_d->m_docName;
}

inline bool Property::enabled() const
{
    return m_d->m_enabled;
}

inline bool Property::final() const
{
    return m_d->m_final;
}
inline bool Property::member() const
{
    return m_d->m_member;
}

inline QString Property::name() const
{
    return m_d->m_name;
}

inline bool Property::notify() const
{
    return m_d->m_notify;
}

inline bool Property::read() const
{
    return m_d->m_read;
}

inline QString Property::realTypeName() const
{
    if (m_d->m_typeStringName.isEmpty())
    {
        return m_d->m_type;
    }
    else
    {
        return m_d->m_typeStringName;
    }
}

inline bool Property::reset() const
{
    return m_d->m_reset;
}

inline int Property::revision() const
{
    return m_d->m_revision;
}

inline bool Property::scriptable() const
{
    return m_d->m_scriptable;
}

inline bool Property::stored() const
{
    return m_d->m_stored;
}

inline const QString & Property::type() const
{
    return m_d->m_type;
}

inline QString Property::typeStringName() const
{
    return m_d->m_typeStringName;
}

inline bool Property::user() const
{
    return m_d->m_user;
}

inline bool Property::write() const
{
    return m_d->m_write;
}

inline void Property::setName(const QString &name)
{
    beforeWrite();
    m_d->m_name = name;
}

inline void Property::setType(const QString & type)
{
    beforeWrite();
    m_d->m_type = type;
}

inline void Property::setTypeStringName(const QString &name)
{
    beforeWrite();
    m_d->m_typeStringName = name;
}

inline void Property::setDocName(const QString &name)
{
    beforeWrite();
    m_d->m_docName = name;
}

inline void Property::setDocDetail(const QString &name)
{
    beforeWrite();
    m_d->m_docDetail = name;
}

inline void Property::setMember(bool b)
{
    beforeWrite();
    m_d->m_member = b;
}

inline void Property::setRead(bool b)
{
    beforeWrite();
    m_d->m_read = b;
}

inline void Property::setWrite(bool b)
{
    beforeWrite();
    m_d->m_write = b;
}

inline void Property::setReset(bool b)
{
    beforeWrite();
    m_d->m_reset = b;
}

inline void Property::setNotify(bool b)
{
    beforeWrite();
    m_d->m_notify = b;
}

inline void Property::setRevision(int n)
{
    beforeWrite();
    m_d->m_revision = n;
}

inline void Property::setDesignable(bool b)
{
    beforeWrite();
    m_d->m_designable = b;
}

inline void Property::setScriptable(bool b)
{
    beforeWrite();
    m_d->m_scriptable = b;
}

inline void Property::setStored(bool b)
{
    beforeWrite();
    m_d->m_stored = b;
}

inline void Property::setUser(bool b)
{
    beforeWrite();
    m_d->m_user = b;
}

inline void Property::setConstant(bool b)
{
    beforeWrite();
    m_d->m_constant = b;
}

inline void Property::setEnabled(bool b)
{
    beforeWrite();
    m_d->m_enabled = b;
}

inline void Property::setFinal(bool b)
{
    beforeWrite();
    m_d->m_final = b;
}

inline QString Property::readFunctionName() const
{
    QString s;
    s = replaceFisrtLetterToUpper(m_d->m_name);
    return s;
}

inline QString Property::writeFunctionName() const
{
    QString s;
    s = QString("Set%1").arg(replaceFisrtLetterToUpper(m_d->m_name));
    return s;
}

inline QString Property::signalName() const
{
    return QString("%1Changed").arg(readFunctionName());
}

inline QString Property::memberVariableName() const
{
    QString s;
    s = QString("m_%1%2")
            .arg(typePrefix())
            .arg(replaceFisrtLetterToUpper(m_d->m_name));
    return s;
}

inline QString Property::readDeclear() const
{
    QString s;
    s = QString("%1 %2() const;\n")
            .arg(realTypeName())
            .arg(readFunctionName());
    return s;
}

inline QString Property::writeDeclear() const
{
    QString s;
    s = QString("void %1(const %2 &%3);\n")
            .arg(writeFunctionName())
            .arg(realTypeName())
            .arg(writeFunctionArgumentName());
    return s;
}

inline QString Property::signalDeclear() const
{
    QString s;
    s = QString("void %1();\n").arg(signalName());
    return s;
}

inline QString Property::memberVariableDeclear() const
{
    QString s;
    if (m_d->m_docName.isEmpty())
    {
        s = QString("%1 %2;\n")
                .arg(realTypeName())
                .arg(memberVariableName());
    }
    else
    {
        s = QString("%1 %2;    /**< %3 */\n")
                .arg(realTypeName())
                .arg(memberVariableName())
                .arg(m_d->m_docName);
    }
    return s;
}

inline void Property::beforeWrite()
{
    if (m_d->m_used > 1)
    {
        m_d->m_used--;
        m_d = new PropertyData(*m_d);
#ifdef DEBUG_PROPERTYS_COW_DETAIL
    std::cout << "Property::beforeWrite copy. "
                 "used=" << m_d->m_used
              << " id=" << m_d->m_id << std::endl;
#endif
    }
}

inline QString Property::boolToStr(bool b)
{
    return b ? QString("t") : QString("f");
}

inline bool Property::strTobool(const QString &str)
{
    return (str == QString("t")) ? true : false;
}

inline QString Property::replaceFisrtLetterToLower(const QString &str)
{
    if (!str.isEmpty())
    {
        QString dest = str;
        QString firstLetter = QString(dest.at(0).toLower());
        dest.replace(0, 1, firstLetter);
        return dest;
    }
    else
    {
        return str;
    }
}

inline QString Property::replaceFisrtLetterToUpper(const QString &str)
{
    if (!str.isEmpty())
    {
        QString dest = str;
        QString firstLetter = QString(dest.at(0).toUpper());
        dest.replace(0, 1, firstLetter);
        return dest;
    }
    else
    {
        return str;
    }
}

inline QString Property::writeFunctionArgumentName() const
{
    return QString("A") + typePrefix();
}

#endif // PROPERTYINLINEFUNCTIONS_H
