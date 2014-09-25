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
            "    %4\n" \
            " */\n") \
        .arg(className) \
        .arg(name()) \
        .arg(docCommentBrief()) \
        .arg(docCommentDetail())

#define CODESCHEME_DocCommentContent_Property_Brief \
    QString("%1.").arg(docBrief())

//#define CODESCHEME_DocCommentContent_Property_Detail

#define CODESCHEME_DocCommentContent_Class \
    QString("/*!\n" \
            "    \\class %1\n" \
            "    \\brief %2\n" \
            "    %3\n" \
            " */\n\n") \
        .arg(className()) \
        .arg(replaceFisrtLetterToUpper(docName())) \
        .arg(replaceFisrtLetterToUpper(docDetail()))

#define CODESCHEME_DocCommentContent_MemberVariable \
    QString("/*!\n" \
            "    \\variable %1::%2\n" \
            "    \\brief Member variable of property %3.\n" \
            " */\n\n") \
        .arg(className) \
        .arg(memberVariableName()) \
        .arg(docName())

#define CODESCHEME_DocCommentContent_PreventReentrantMemberVariable \
    QString("/*!\n" \
            "    \\variable %1::%2\n" \
            "    \\brief Prevent reentrant write function of property %3 when the write funtion executing.\n" \
            " */\n\n") \
        .arg(className) \
        .arg(memberVariableName()) \
        .arg(docName())

#define CODESCHEME_DocCommentContent_ReadFunction QString()

#define CODESCHEME_DocCommentContent_ResetFunction QString()

#define CODESCHEME_DocCommentContent_WriteFunction QString()

#define CODESCHEME_DocCommentContent_AssignmentOperator \
    QString("/*!\n" \
            "    \\fn %1 &%1::operator=(const %1 &%2)\n" \
            "    \\brief Assignment operator.\n" \
            "    Assignment operator.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_DocCommentContent_CopyConstructor \
    QString("/*!\n" \
            "    \\fn %1::%1(const %1 &%2)\n" \
            "    \\brief Copy constructor.\n" \
            "    Copy constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Default constructor.\n" \
            "    Default constructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_DocCommentContent_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_DocCommentContent_FileHeader QString()

#define CODESCHEME_DocCommentContent_FileHeader_HeaderBrief QString()

#define CODESCHEME_DocCommentContent_FileHeader_HeaderDetail QString()

#define CODESCHEME_DocCommentContent_FileHeader_SourceBrief QString()

#define CODESCHEME_DocCommentContent_FileHeader_SourceDetail QString()

#endif // PARAMENTS_DOCCOMMENT_CONTENT_H
