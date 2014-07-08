#ifndef PARAMENTS_NAMESCHEME_H
#define PARAMENTS_NAMESCHEME_H

#define CODESCHEME_Property_WriteFunctionArgumentName \
    QString("var")

#define CODESCHEME_Property_ReadFunctionName \
    name()

#define CODESCHEME_Property_ResetFunctionName \
    QString("reset%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Property_WriteFunctionName \
    QString("set%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Property_SignalName \
    QString("%1Changed").arg(name())

#define CODESCHEME_Property_MemberVariableName \
    QString("m_%1").arg(name())

#define CODESCHEME_Property_PreventReentrantVarName \
    QString("m_setting%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Class_ArgumentNameOfThisClass \
    QString("var")

#define CODESCHEME_Class_QOjbectBasedParentArgumentName \
    QString("parent")

#define CODESCHEME_File_HeaderFileMarco \
    QString("%1_H").arg(className().toUpper())

#define CODESCHEME_File_HeaderFileName \
    QString("%1.h").arg(className())

#define CODESCHEME_File_SourceFileName \
    QString("%1.cpp").arg(className())

#endif // PARAMENTS_NAMESCHEME_H
