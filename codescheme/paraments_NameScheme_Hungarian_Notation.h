#ifndef PARAMENTS_NAMESCHEME_H
#define PARAMENTS_NAMESCHEME_H

#define CODESCHEME_Property_WriteFunctionArgumentName \
    QString("A%1").arg(typePrefix())

#define CODESCHEME_Property_ReadFunctionName \
    replaceFisrtLetterToUpper(name())

#define CODESCHEME_Property_ResetFunctionName \
    QString("Reset%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Property_WriteFunctionName \
    QString("Set%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Property_SignalName \
    QString("%1Changed").arg(replaceFisrtLetterToLower(name()))

#define CODESCHEME_Property_MemberVariableName \
    QString("m_%1%2").arg(typePrefix()).arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Property_PreventReentrantVarName \
    QString("m_bSetting%1").arg(replaceFisrtLetterToUpper(name()))

#define CODESCHEME_Class_ArgumentNameOfThisClass \
    QString("A%1").arg(replaceFisrtLetterToLower(className()))

#define CODESCHEME_Class_QOjbectBasedParentArgumentName \
    QString("Ap%1Parent").arg(replaceFisrtLetterToLower(parentClass()))

#define CODESCHEME_File_HeaderFileMarco \
    QString("%1_H").arg(className().toUpper())

#define CODESCHEME_File_HeaderFileName \
    QString("%1.h").arg(className())

#define CODESCHEME_File_SourceFileName \
    QString("%1.cpp").arg(className())

#endif // PARAMENTS_NAMESCHEME_H
