#ifndef PARAMENTS_H
#define PARAMENTS_H

#define START_DIR "."

#define CODESCHEME_Indent "    "

#define CODESCHEME_DateTimeFormat "yyyy-MM-dd, hh:mm"

#define CODESCHEME_DocComment_Comma ", "

#define CODESCHEME_DocComment_Period ". "

#define CODESCHEME_DocComment_ReadOnlyProperty "read-only property"

#define CODESCHEME_DocComment_WriteOnlyProperty "write-only property"

#define CODESCHEME_DocComment_WriteFunction_SignalDetail \
    QString("and send signal %1").arg(signalName())

#define CODESCHEME_Doxygen_Property \
    QString("/**\n" \
            " * @property %1::%2\n" \
            " * @brief %3.\n" \
            " * @details %4\n" \
            " */\n") \
        .arg(className) \
        .arg(name()) \
        .arg(replaceFisrtLetterToUpper(docName())) \
        .arg(replaceFisrtLetterToUpper(detail))

#define CODESCHEME_Doxygen_Class \
    QString("/**\n" \
            " * @class %1\n" \
            " * @brief %2\n" \
            " * @details %3\n" \
            " */\n") \
        .arg(className()) \
        .arg(replaceFisrtLetterToUpper(docName())) \
        .arg(replaceFisrtLetterToUpper(docDetail()))

#define CODESCHEME_Doxygen_MemberVariable \
    QString("/**< %1 */") \
                .arg(docName())

#define CODESCHEME_Doxygen_PreventReentrantMemberVariable \
    QString("/**< Prevent reentrant write function of property %1 when the write funtion executing. */") \
                .arg(docName())

#define CODESCHEME_Doxygen_ReadFunction \
    QString("/**\n" \
            " * @brief Return the value of property %1.\n" \
            " * @return the value of property %1\n" \
            " * @details return the value of property %1.\n" \
            " */\n") \
        .arg(docName())

#define CODESCHEME_Doxygen_ResetFunction \
    QString("/**\n" \
            " * @brief Set the value of property %1 to default value.\n" \
            " * @details Set the value of property %1 to default value.\n" \
            " */\n") \
        .arg(docName())

#define CODESCHEME_Doxygen_WriteFunction \
    QString("/**\n" \
            " * @brief Set the value of property %1.\n" \
            " * @param %2 %1\n" \
            " * @details Set the value of property %1%3%4.\n" \
            " */\n") \
        .arg(docName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(signalDetail) \
        .arg(customDetail)

#define CODESCHEME_Doxygen_AssignmentOperator \
    QString("/**\n" \
            " * @brief Assignment operator.\n" \
            " * @param %1 object that will be assignment\n" \
            " * @details Assignment operator.\n" \
            " */") \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Doxygen_CopyConstructor \
    QString("/**\n" \
            " * @brief Copy constructor.\n" \
            " * @param %1 object that will be copy\n" \
            " * @details Copy constructor.\n" \
            " */\n") \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_None \
    QString("/**\n" \
            " * @brief Default constructor.\n" \
            " * @details Default constructor.\n" \
            " */")

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_QObject \
    QString("/**\n" \
            " * @brief Default constructor.\n" \
            " * @param %1 pointer to parent object\n" \
            " * @details Default constructor.\n" \
            " */") \
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_Doxygen_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/**\n" \
            " * @brief Default constructor.\n" \
            " * @param %1 pointer to parent object\n" \
            " * @details Default constructor.\n" \
            " */")\
        .arg(qojbectBasedParentArgumentName())

#define CODESCHEME_Doxygen_Destructor_Inherits_None \
    QString("/**\n" \
            " * @brief Destructor.\n" \
            " * @details Destructor.\n" \
            " */")

#define CODESCHEME_Doxygen_Destructor_Inherits_QObject \
    QString("/**\n" \
            " * @brief Destructor.\n" \
            " * @details Destructor.\n" \
            " */")

#define CODESCHEME_Doxygen_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("/**\n" \
            " * @brief Destructor.\n" \
            " * @details Destructor.\n" \
            " */")

#define CODESCHEME_Doxygen_FileHeader \
    QString("/**\n" \
            " * @file       %1\n" \
            " * @version    1.0\n" \
            " * @date       %2\n" \
            " * @author     unknown\n" \
            " * @copyright  unknown\n" \
            " *\n" \
            " * @brief      %3\n" \
            " * @details    %4\n" \
            " */\n") \
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

#define CODESCHEME_Property_ReadDeclear \
    QString("%1 %2() const;").arg(realTypeName()).arg(readFunctionName())

#define CODESCHEME_Property_ResetDeclear \
    QString("void %1();").arg(resetFunctionName())

#define CODESCHEME_Property_WriteDeclear \
    QString("void %1(const %2 &%3);") \
                .arg(writeFunctionName()) \
                .arg(realTypeName()) \
                .arg(writeFunctionArgumentName())

#define CODESCHEME_Property_SignalDeclear \
    QString("void %1();").arg(signalName())

#define CODESCHEME_Property_MemberVariableDeclear \
    QString("%1 %2;" CODESCHEME_Indent "%3") \
                    .arg(realTypeName()) \
                    .arg(memberVariableName()) \
                    .arg(doxygenCommentMemberVariable())

#define CODESCHEME_Property_PreventReentrantVarDeclear \
    QString("bool %1;" CODESCHEME_Indent "%2") \
                .arg(preventReentrantVarName()) \
                .arg(doxygenCommentPreventReentrantMemberVariable())

#define CODESCHEME_Property_ReadFunctionDefine \
    QString("%1 %2::%3() const\n" \
            "{\n" \
            CODESCHEME_Indent "return %4;\n" \
            "}\n") \
        .arg(realTypeName()) \
        .arg(className) \
        .arg(readFunctionName()) \
        .arg(memberVariableName())

#define CODESCHEME_Property_ResetFunctionDefine \
    QString("void %1::%2()\n" \
            "{\n" \
            CODESCHEME_Indent "%3(%4);\n" \
            "}\n") \
        .arg(className) \
        .arg(resetFunctionName()) \
        .arg(writeFunctionName()) \
        .arg(defaultValue().toString())

#define CODESCHEME_Property_WriteFunction_EmitSignalStatement \
    QString("emit %1();").arg(signalName())

#define CODESCHEME_Property_WriteFunctionDefine_PreventReentrant \
    QString("void %1::%2(const %3 &%4)\n" \
            "{\n" \
            CODESCHEME_Indent "if (!%11)\n" \
            CODESCHEME_Indent "{\n" \
            CODESCHEME_Indent CODESCHEME_Indent "%11 = true;\n" \
            "%5" \
            CODESCHEME_Indent CODESCHEME_Indent "%6 = %7;\n" \
            "%8" \
            CODESCHEME_Indent CODESCHEME_Indent "%9\n" \
            "%10" \
            CODESCHEME_Indent CODESCHEME_Indent "%11 = false;\n" \
            CODESCHEME_Indent "}\n" \
            "}\n") \
        .arg(className) \
        .arg(writeFunctionName()) \
        .arg(realTypeName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(strBeforSetValue) \
        .arg(memberVariableName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(strBetweenSetValueAndEmit) \
        .arg(emitSignalStatement) \
        .arg(strAfterEmit) \
        .arg(preventReentrantVarName())

#define CODESCHEME_Property_WriteFunctionDefine \
    QString("void %1::%2(const %3 &%4)\n" \
            "{\n" \
            "%5" \
            CODESCHEME_Indent "%6 = %7;\n" \
            "%8" \
            CODESCHEME_Indent "%9\n" \
            "%10" \
            "}\n") \
        .arg(className) \
        .arg(writeFunctionName()) \
        .arg(realTypeName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(strBeforSetValue) \
        .arg(memberVariableName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(strBetweenSetValueAndEmit) \
        .arg(emitSignalStatement) \
        .arg(strAfterEmit)

#define CODESCHEME_Class_ArgumentNameOfThisClass \
    QString("var")

#define CODESCHEME_Class_QOjbectBasedParentArgumentName \
    QString("parent")

#define CODESCHEME_Class_Define_Inherits_None \
    QString("class %1\n" \
            "{\n" \
            "public:\n" \
            CODESCHEME_Indent "%1();\n" \
            CODESCHEME_Indent "%1(const %1 &%2);\n" \
            CODESCHEME_Indent "~%1();\n" \
            CODESCHEME_Indent "%1 &operator=(const %1 &%2);\n\n" \
            "%3\n" \
            "%4\n" \
            "%5\n" \
            "private:\n" \
            "%6" \
            "};\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass()) \
        .arg(generateReadDeclear()) \
        .arg(generateWriteDeclear()) \
        .arg(generateResetDeclear()) \
        .arg(generateMemberVariableDeclear())

#define CODESCHEME_Class_Define_Inherits_NonQObjectClass \
    QString("class %1 : public %2\n" \
            "{\n" \
            "public:\n" \
            CODESCHEME_Indent "%1();\n" \
            CODESCHEME_Indent "%1(const %1 &%3);\n" \
            CODESCHEME_Indent "~%1();\n\n" \
            CODESCHEME_Indent "%1 &operator=(const %1 &%3);\n\n" \
            "%4\n" \
            "%5\n" \
            "%6\n" \
            "private:\n" \
            "%7" \
            "};\n") \
        .arg(className()) \
        .arg(inherits()) \
        .arg(argumentNameOfThisClass()) \
        .arg(generateReadDeclear()) \
        .arg(generateWriteDeclear()) \
        .arg(generateResetDeclear()) \
        .arg(generateMemberVariableDeclear())

#define CODESCHEME_Class_Define_Inherits_QObject \
    QString("class %1 : public %2\n" \
            "{\n" \
            CODESCHEME_Indent "Q_OBJECT\n" \
            "%3\n" \
            "public:\n" \
            CODESCHEME_Indent "explicit %1(%4 *%5 = 0);\n" \
            CODESCHEME_Indent "~%1();\n\n" \
            "%6\n" \
            "public slots:\n" \
            "%7" \
            "%8\n" \
            "signals:\n" \
            "%9\n" \
            "private:\n" \
            "%10" \
            "};\n") \
        .arg(className()) \
        .arg(inherits()) \
        .arg(generateQPropertyDeclear()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName()) \
        .arg(generateReadDeclear()) \
        .arg(generateWriteDeclear()) \
        .arg(generateResetDeclear()) \
        .arg(generateSignalDeclear()) \
        .arg(generateMemberVariableDeclear())

#define CODESCHEME_Class_Define_Inherits_QWidget_AssociateWithUiFile \
    QString("namespace Ui {\n" \
            "class %1;\n" \
            "}\n\n" \
            "class %1 : public %2\n" \
            "{\n" \
            CODESCHEME_Indent "Q_OBJECT\n" \
            "%3\n" \
            "public:\n" \
            CODESCHEME_Indent "explicit %1(%4 *%5 = 0);\n" \
            CODESCHEME_Indent "~%1();\n\n" \
            "%6\n" \
            "public slots:\n" \
            "%7" \
            "%8\n" \
            "signals:\n" \
            "%8\n" \
            "private:\n" \
            CODESCHEME_Indent "Ui::%1 *ui;\n" \
            "%9" \
            "};\n") \
        .arg(className()) \
        .arg(inherits()) \
        .arg(generateQPropertyDeclear()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName()) \
        .arg(generateReadDeclear()) \
        .arg(generateWriteDeclear()) \
        .arg(generateResetDeclear()) \
        .arg(generateSignalDeclear()) \
        .arg(generateMemberVariableDeclear())

#define CODESCHEME_Class_Function_AssignmentOperator \
    QString("%1\n" \
            "%2 &%2::operator=(const %2 &%3)\n" \
            "{\n" \
            "%4" \
            CODESCHEME_Indent "return *this;\n" \
            "}\n") \
        .arg(doxygenCommentAssignmentOperator()) \
        .arg(className()) \
        .arg(argumentNameOfThisClass()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_AssignmentOperator_AssignmentStatements \
    QString(CODESCHEME_Indent "%1 = %2.%1;\n") \
        .arg(p.memberVariableName()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Class_Function_CopyConstructor \
    QString("%1\n" \
            "%2::%2(const %2 &%3)%4\n" \
            "{\n" \
            "}\n") \
        .arg(doxygenCommentCopyConstructor()) \
        .arg(className()) \
        .arg(argumentNameOfThisClass()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_CopyConstructor_MemberInitStatements \
    QString(",\n" CODESCHEME_Indent "%1(%2.%1)") \
        .arg(p.memberVariableName()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Class_Function_CopyConstructor_PreventReentrantMemberInitStatements \
    QString(",\n" CODESCHEME_Indent "%1(false)") \
        .arg(p.preventReentrantVarName())

#define CODESCHEME_Class_Function_DefaultConstructor_Inherits_None \
    QString("%1\n" \
            "%2::%2()%3\n" \
            "{\n" \
            "}\n") \
        .arg(doxygenCommentDefaultConstructor()) \
        .arg(className()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_DefaultConstructor_Inherits_QObject \
    QString("%1\n" \
            "%2::%2(%3 *%4) :\n" \
            CODESCHEME_Indent "%5(%4),\n" \
            CODESCHEME_Indent "ui(new Ui::%2)%6\n" \
            "{\n" \
            CODESCHEME_Indent "ui->setupUi(this);\n" \
            "}\n") \
        .arg(doxygenCommentDefaultConstructor()) \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName()) \
        .arg(inherits()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("%1\n" \
            "%2::%2(%3 *%4) :\n" \
            CODESCHEME_Indent "%5(%4)%6\n" \
            "{\n" \
            "}\n") \
        .arg(doxygenCommentDefaultConstructor()) \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName()) \
        .arg(inherits()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_DefaultConstructor_MemberInitStatements \
    QString(",\n" CODESCHEME_Indent "%1(%2)") \
        .arg(p.memberVariableName()) \
        .arg(p.defaultValue().toString())

#define CODESCHEME_Class_Function_DefaultConstructor_PreventReentrantMemberInitStatements \
    QString(",\n" CODESCHEME_Indent "%1(false)") \
        .arg(p.preventReentrantVarName())

#define CODESCHEME_Class_Function_Destructor_Inherits_None \
    QString("%1\n" \
            "%2::~%2()\n" \
            "{\n" \
            "}\n") \
        .arg(doxygenCommentDestructor()) \
        .arg(className())

#define CODESCHEME_Class_Function_Destructor_Inherits_QObject \
    QString("%1\n" \
            "%2::~%2()\n" \
            "{\n" \
            "}\n") \
        .arg(doxygenCommentDestructor()) \
        .arg(className())

#define CODESCHEME_Class_Function_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("%1\n" \
            "%2::~%2()\n" \
            "{\n" \
            CODESCHEME_Indent "delete ui;\n" \
            "}\n") \
        .arg(doxygenCommentDestructor()) \
        .arg(className())

#define CODESCHEME_File_IncludeSystemHeaderFileStatement \
    QString("#include <%1>\n").arg(fileName)

#define CODESCHEME_File_IncludeLocalHeaderFileStatement \
    QString("#include \"%1.h\"\n").arg(fileName)

#define CODESCHEME_File_HeaderFileContent \
    QString("%1\n" \
            "#ifndef %2\n" \
            "#define %2\n\n" \
            "%3\n" \
            "%4\n" \
            "%5" \
            "%6" \
            "%7" \
            "#endif // %2") \
        .arg(headerFileDoxygenHeader()) \
        .arg(headerFileMarco()) \
        .arg(headerFileIncludeStatements()) \
        .arg(classDefine()) \
        .arg(generateInlineReadFunctionDefine()) \
        .arg(generateInlineWriteFunctionDefine()) \
        .arg(generateInlineResetFunctionDefine())

#define CODESCHEME_File_HeaderFileMarco \
    QString("%1_H").arg(className().toUpper())

#define CODESCHEME_File_HeaderFileName \
    QString("%1.h").arg(className())

#define CODESCHEME_File_SourceFileContent_Inherits_None \
    QString("%1\n" \
            "#include \"%2\"\n\n" \
            "%3\n" \
            "%4\n" \
            "%5\n" \
            "%6\n" \
            "%7\n" \
            "%8\n" \
            "%9\n" \
            "%10\n" \
            "%11\n") \
        .arg(sourceFileDoxygenHeader()) \
        .arg(headerFileName()) \
        .arg(doxygenCommentClass()) \
        .arg(generateDoxygenPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileCopyConstructor()) \
        .arg(sourceFileAssignmentOperator()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#define CODESCHEME_File_SourceFileContent_Inherits_QObject \
    QString("%1\n" \
            "#include \"%2\"\n\n" \
            "%3\n" \
            "%4\n" \
            "%5\n" \
            "%6\n" \
            "%7\n" \
            "%8\n" \
            "%9\n") \
        .arg(sourceFileDoxygenHeader()) \
        .arg(headerFileName()) \
        .arg(doxygenCommentClass()) \
        .arg(generateDoxygenPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#define CODESCHEME_File_SourceFileContent_Inherits_QWidget_AssociateWithUiFile \
    QString("%1\n" \
            "#include \"%2\"\n" \
            "#include \"ui_%3\"\n\n" \
            "%4\n" \
            "%5\n" \
            "%6\n" \
            "%7\n" \
            "%8\n" \
            "%9\n" \
            "%10\n") \
        .arg(sourceFileDoxygenHeader()) \
        .arg(headerFileName()) \
        .arg(headerFileName().toLower()) \
        .arg(doxygenCommentClass()) \
        .arg(generateDoxygenPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#define CODESCHEME_File_SourceFileName \
    QString("%1.cpp").arg(className())

#endif // PARAMENTS_H
