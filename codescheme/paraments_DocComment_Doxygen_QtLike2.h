#ifndef PARAMENTS_DOCCOMMENT_CONTENT_H
#define PARAMENTS_DOCCOMMENT_CONTENT_H

#include "../paraments_DocComment_PublicParams.h"

#define CODESCHEME_DocCommentContent_Function_Attachment CODESCHEME_DocComment_Function_InDefine
#define CODESCHEME_DocCommentContent_Function_Pos CODESCHEME_DocComment_Function_Any
#define CODESCHEME_DocCommentContent_MemberVariable_Pos CODESCHEME_DocComment_MemberVariable_InDeclare
#define CODESCHEME_DocCommentContent_Property_Pos CODESCHEME_DocComment_Property_InSourceFile

#define CODESCHEME_DocCommentContent_Property \
    QString("/*!\n" \
            "    \\property %1::%2\n" \
            "    \\brief %3\n" \
            "    \\details %4\n" \
            " */\n") \
        .arg(className) \
        .arg(name()) \
        .arg(docCommentBrief()) \
        .arg(docCommentDetail())

#define CODESCHEME_DocCommentContent_Property_Brief \
    QString("This property holds %1.").arg(replacedDocBrief())

//#define CODESCHEME_DocCommentContent_Property_Detail

#define CODESCHEME_DocCommentContent_Class \
    QString("/*!\n" \
            "    \\class %1\n" \
            "    \\brief %2\n" \
            "    \\details %3\n" \
            " */\n\n") \
        .arg(className()) \
        .arg(replaceFisrtLetterToUpper(replacedDocName())) \
        .arg(replaceFisrtLetterToUpper(replacedDocDetail()))

#define CODESCHEME_DocCommentContent_MemberVariable \
    QString("/*!< %1 */") \
                .arg(replacedDocName())

#define CODESCHEME_DocCommentContent_PreventReentrantMemberVariable \
    QString("/*!< Prevent reentrant write function of property %1 when the write funtion executing. */") \
                .arg(replacedDocName())

#define CODESCHEME_DocCommentContent_ReadFunction \
    QString("/*!\n" \
            "    \\fn %1 %2::%3()\n" \
            "    \\brief Return the value of property %4.\n" \
            "    \\return the value of property %4\n" \
            "    \\details return the value of property %4.\n" \
            " */\n") \
        .arg(realTypeName()) \
        .arg(className) \
        .arg(readFunctionName()) \
        .arg(replacedDocName())

#define CODESCHEME_DocCommentContent_ResetFunction \
    QString("/*!\n" \
            "    \\fn void %1::%2()\n" \
            "    \\brief Set the value of property %3 to default value.\n" \
            "    \\details Set the value of property %3 to default value.\n" \
            " */\n") \
        .arg(className) \
        .arg(resetFunctionName()) \
        .arg(replacedDocName())

#define CODESCHEME_DocCommentContent_WriteFunction \
    QString("/*!\n" \
            "    \\fn void %1::%2(const %3 &%4)\n" \
            "    \\brief Set the value of property %5.\n" \
            "    \\param %4 %5\n" \
            "    \\details Set the value of property %5%6%7.\n" \
            " */\n") \
        .arg(className) \
        .arg(writeFunctionName()) \
        .arg(realTypeName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(replacedDocName()) \
        .arg(signalDetail) \
        .arg(customDetail)

#define CODESCHEME_DocCommentContent_AssignmentOperator \
    QString("/*!\n" \
            "    \\fn %1 &%1::operator=(const %1 &%2)\n" \
            "    \\brief Assignment operator.\n" \
            "    \\param %2 object that will be assignment\n" \
            "    \\details Assignment operator.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_DocCommentContent_CopyConstructor \
    QString("/*!\n" \
            "    \\fn %1::%1(const %1 &%2)\n" \
            "    \\brief Copy constructor.\n" \
            "    \\param %2 object that will be copy\n" \
            "    \\details Copy constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Default constructor.\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    \\param %3 pointer to parent object\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    \\param %3 pointer to parent object\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_FileHeader \
    QString("/*!\n" \
            "    \\file       %1\n" \
            "    \\version    1.0\n" \
            "    \\date       %2\n" \
            "    \\author     unknown\n" \
            "    \\copyright  unknown\n" \
            "\n" \
            "    \\brief      %3\n" \
            "    \\details    %4\n" \
            " */\n\n") \
        .arg(fileName) \
        .arg(currentDateTimeString()) \
        .arg(brief) \
        .arg(detail)

#define CODESCHEME_DocCommentContent_FileHeader_HeaderBrief \
    QString("%1 header file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_DocCommentContent_FileHeader_HeaderDetail \
    QString("%1 header file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_DocCommentContent_FileHeader_SourceBrief \
    QString("%1 source file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_DocCommentContent_FileHeader_SourceDetail \
    QString("%1 source file.").arg(replaceFisrtLetterToUpper(docName()))

#endif // PARAMENTS_DOCCOMMENT_CONTENT_H
