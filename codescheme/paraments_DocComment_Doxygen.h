#ifndef PARAMENTS_DOCCOMMENT_DOXYGEN_H
#define PARAMENTS_DOCCOMMENT_DOXYGEN_H

#define CODESCHEME_Doxygen_Property \
    QString("/*!\n" \
            "    \\property %1::%2\n" \
            "    \\brief %3\n" \
            "    \\details %4\n" \
            " */\n") \
        .arg(className) \
        .arg(name()) \
        .arg(docCommentBrief()) \
        .arg(docCommentDetail())

#define CODESCHEME_Doxygen_Property_Brief \
    QString("This property holds %1.").arg(docBrief())

//#define CODESCHEME_Doxygen_Property_Detail

#define CODESCHEME_Doxygen_Class \
    QString("/*!\n" \
            "    \\class %1\n" \
            "    \\brief %2\n" \
            "    \\details %3\n" \
            " */\n\n") \
        .arg(className()) \
        .arg(replaceFisrtLetterToUpper(docName())) \
        .arg(replaceFisrtLetterToUpper(docDetail()))

#define CODESCHEME_Doxygen_MemberVariable \
    QString("/*!< %1 */") \
                .arg(docName())

#define CODESCHEME_Doxygen_PreventReentrantMemberVariable \
    QString("/*!< Prevent reentrant write function of property %1 when the write funtion executing. */") \
                .arg(docName())

#define CODESCHEME_Doxygen_ReadFunction \
    QString("/*!\n" \
            "    \\fn %1 %2::%3();\n" \
            "    \\brief Return the value of property %4.\n" \
            "    \\return the value of property %4\n" \
            "    \\details return the value of property %4.\n" \
            " */\n") \
        .arg(realTypeName()) \
        .arg(className) \
        .arg(readFunctionName()) \
        .arg(docName())

#define CODESCHEME_Doxygen_ResetFunction \
    QString("/*!\n" \
            "    \\fn void %1::%2();\n" \
            "    \\brief Set the value of property %3 to default value.\n" \
            "    \\details Set the value of property %3 to default value.\n" \
            " */\n") \
        .arg(className) \
        .arg(resetFunctionName()) \
        .arg(docName())

#define CODESCHEME_Doxygen_WriteFunction \
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
        .arg(docName()) \
        .arg(signalDetail) \
        .arg(customDetail)

#define CODESCHEME_Doxygen_AssignmentOperator \
    QString("/*!\n" \
            "    \\fn %1 &%1::operator=(const %1 &%2)\n" \
            "    \\brief Assignment operator.\n" \
            "    \\param %2 object that will be assignment\n" \
            "    \\details Assignment operator.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Doxygen_CopyConstructor \
    QString("/*!\n" \
            "    \\fn %1::%1(const %1 &%2)\n" \
            "    \\brief Copy constructor.\n" \
            "    \\param %2 object that will be copy\n" \
            "    \\details Copy constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Default constructor.\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    \\param %3 pointer to parent object\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1(%2 *%3)\n" \
            "    \\brief Default constructor.\n" \
            "    \\param %3 pointer to parent object\n" \
            "    \\details Default constructor.\n" \
            " */\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_Doxygen_Destructor_Inherits_None \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_Doxygen_Destructor_Inherits_QObject \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_Doxygen_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/*!\n" \
            "    \\fn %1::%1()\n" \
            "    \\brief Destructor.\n" \
            "    \\details Destructor.\n" \
            " */\n") \
        .arg(className())

#define CODESCHEME_Doxygen_FileHeader \
    QString("/*!\n" \
            "    \\file       %1\n" \
            "    \\version    1.0\n" \
            "    \\date       %2\n" \
            "    \\author     unknown\n" \
            "    \\copyright  unknown\n" \
            "    \\brief      %3\n" \
            "    \\details    %4\n" \
            " */\n\n") \
        .arg(fileName) \
        .arg(currentDateTimeString()) \
        .arg(brief) \
        .arg(detail)

#define CODESCHEME_Doxygen_FileHeader_HeaderBrief \
    QString("%1 header file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_Doxygen_FileHeader_HeaderDetail \
    QString("%1 header file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_Doxygen_FileHeader_SourceBrief \
    QString("%1 source file.").arg(replaceFisrtLetterToUpper(docName()))

#define CODESCHEME_Doxygen_FileHeader_SourceDetail \
    QString("%1 source file.").arg(replaceFisrtLetterToUpper(docName()))

#endif // PARAMENTS_DOCCOMMENT_DOXYGEN_H