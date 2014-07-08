#ifndef PARAMENTS_CODEFORMAT_H
#define PARAMENTS_CODEFORMAT_H

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
                    .arg(docCommentMemberVariable())

#define CODESCHEME_Property_PreventReentrantVarDeclear \
    QString("bool %1;" CODESCHEME_Indent "%2") \
                .arg(preventReentrantVarName()) \
                .arg(docCommentPreventReentrantMemberVariable())

#define CODESCHEME_Property_ReadFunctionDefine \
    QString("%1%2 %3::%4() const\n" \
            "{\n" \
            CODESCHEME_Indent "return %5;\n" \
            "}\n") \
        .arg(inlineNotation(isInline)) \
        .arg(realTypeName()) \
        .arg(className) \
        .arg(readFunctionName()) \
        .arg(memberVariableName())

#define CODESCHEME_Property_ResetFunctionDefine \
    QString("%1void %2::%3()\n" \
            "{\n" \
            CODESCHEME_Indent "%4(%5);\n" \
            "}\n") \
        .arg(inlineNotation(isInline)) \
        .arg(className) \
        .arg(resetFunctionName()) \
        .arg(writeFunctionName()) \
        .arg(defaultValue().toString())

#define CODESCHEME_Property_WriteFunction_EmitSignalStatement \
    QString("emit %1();").arg(signalName())

#define CODESCHEME_Property_WriteFunctionDefine \
    QString("%1void %2::%3(const %4 &%5)\n" \
            "{\n" \
            "%6" \
            CODESCHEME_Indent "%7 = %8;\n" \
            "%9" \
            "%10" \
            "%11" \
            "}\n") \
        .arg(inlineNotation(isInline)) \
        .arg(className) \
        .arg(writeFunctionName()) \
        .arg(realTypeName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(indentCode(strBeforSetValue, 1)) \
        .arg(memberVariableName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(indentCode(strBetweenSetValueAndEmit, 1)) \
        .arg(emitSignalStatement.isEmpty() ? \
             "" : (QString(CODESCHEME_Indent "%1\n").arg(emitSignalStatement))) \
        .arg(indentCode(strAfterEmit, 1))

#define CODESCHEME_Property_WriteFunctionDefine_PreventReentrant \
    QString("%1void %2::%3(const %4 &%5)\n" \
            "{\n" \
            CODESCHEME_Indent "if (!%12)\n" \
            CODESCHEME_Indent "{\n" \
            CODESCHEME_Indent CODESCHEME_Indent "%12 = true;\n" \
            "%6" \
            CODESCHEME_Indent CODESCHEME_Indent "%7 = %8;\n" \
            "%9" \
            "%10" \
            "%11" \
            CODESCHEME_Indent CODESCHEME_Indent "%12 = false;\n" \
            CODESCHEME_Indent "}\n" \
            "}\n") \
        .arg(inlineNotation(isInline)) \
        .arg(className) \
        .arg(writeFunctionName()) \
        .arg(realTypeName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(indentCode(strBeforSetValue, 2)) \
        .arg(memberVariableName()) \
        .arg(writeFunctionArgumentName()) \
        .arg(indentCode(strBetweenSetValueAndEmit, 2)) \
        .arg(emitSignalStatement.isEmpty() ? \
             "" : (QString(CODESCHEME_Indent CODESCHEME_Indent "%1\n").arg(emitSignalStatement))) \
        .arg(indentCode(strAfterEmit, 2)) \
        .arg(preventReentrantVarName())

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
            "%9\n" \
            "private:\n" \
            CODESCHEME_Indent "Ui::%1 *ui;\n" \
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

#define CODESCHEME_Class_Function_AssignmentOperator \
    QString("%1 &%1::operator=(const %1 &%2)\n" \
            "{\n" \
            "%3" \
            CODESCHEME_Indent "return *this;\n" \
            "}\n") \
        .arg(className()) \
        .arg(argumentNameOfThisClass()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_AssignmentOperator_AssignmentStatements \
    QString(CODESCHEME_Indent "%1 = %2.%1;\n") \
        .arg(p.memberVariableName()) \
        .arg(argumentNameOfThisClass())

#define CODESCHEME_Class_Function_CopyConstructor \
    QString("%1::%1(const %1 &%2)%3\n" \
            "{\n" \
            "}\n") \
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
    QString("%1::%1()%2\n" \
            "{\n" \
            "}\n") \
        .arg(className()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_DefaultConstructor_Inherits_QObject \
    QString("%1::%1(%2 *%3) :\n" \
            CODESCHEME_Indent "%4(%3),\n" \
            CODESCHEME_Indent "ui(new Ui::%1)%5\n" \
            "{\n" \
            CODESCHEME_Indent "ui->setupUi(this);\n" \
            "}\n") \
        .arg(className()) \
        .arg(parentClass()) \
        .arg(qojbectBasedParentArgumentName()) \
        .arg(inherits()) \
        .arg(memberInit)

#define CODESCHEME_Class_Function_DefaultConstructor_Inherits_QWidget_AssociateWithUiFile \
    QString("%1::%1(%2 *%3) :\n" \
            CODESCHEME_Indent "%4(%3)%5\n" \
            "{\n" \
            "}\n") \
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
    QString("%1::~%1()\n" \
            "{\n" \
            "}\n") \
        .arg(className())

#define CODESCHEME_Class_Function_Destructor_Inherits_QObject \
    QString("%1::~%1()\n" \
            "{\n" \
            "}\n") \
        .arg(className())

#define CODESCHEME_Class_Function_Destructor_Inherits_QWidget_AssociateWithUiFile \
    QString("%1::~%1()\n" \
            "{\n" \
            CODESCHEME_Indent "delete ui;\n" \
            "}\n") \
        .arg(className())

#define CODESCHEME_File_IncludeSystemHeaderFileStatement \
    QString("#include <%1>\n").arg(fileName)

#define CODESCHEME_File_IncludeLocalHeaderFileStatement \
    QString("#include \"%1.h\"\n").arg(fileName)

#define CODESCHEME_File_HeaderFileContent \
    QString("%1" \
            "#ifndef %2\n" \
            "#define %2\n\n" \
            "%3\n" \
            "%4\n" \
            "%5" \
            "%6" \
            "%7" \
            "#endif // %2") \
        .arg(headerFileDocCommentHeader()) \
        .arg(headerFileMarco()) \
        .arg(headerFileIncludeStatements()) \
        .arg(classDefine()) \
        .arg(generateInlineReadFunctionDefine()) \
        .arg(generateInlineWriteFunctionDefine()) \
        .arg(generateInlineResetFunctionDefine())

#define CODESCHEME_File_SourceFileContent_Inherits_None \
    QString("%1" \
            "#include \"%2\"\n\n" \
            "%3" \
            "%4" \
            "%5\n" \
            "%6\n" \
            "%7\n" \
            "%8\n" \
            "%9" \
            "%10" \
            "%11") \
        .arg(sourceFileDocCommentHeader()) \
        .arg(headerFileName()) \
        .arg(docCommentClass()) \
        .arg(generateDocCommentPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileCopyConstructor()) \
        .arg(sourceFileAssignmentOperator()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#define CODESCHEME_File_SourceFileContent_Inherits_QObject \
    QString("%1" \
            "#include \"%2\"\n\n" \
            "%3" \
            "%4" \
            "%5\n" \
            "%6\n" \
            "%7" \
            "%8" \
            "%9") \
        .arg(sourceFileDocCommentHeader()) \
        .arg(headerFileName()) \
        .arg(docCommentClass()) \
        .arg(generateDocCommentPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#define CODESCHEME_File_SourceFileContent_Inherits_QWidget_AssociateWithUiFile \
    QString("%1" \
            "#include \"%2\"\n" \
            "#include \"ui_%3\"\n\n" \
            "%4" \
            "%5" \
            "%6\n" \
            "%7\n" \
            "%8" \
            "%9" \
            "%10") \
        .arg(sourceFileDocCommentHeader()) \
        .arg(headerFileName()) \
        .arg(headerFileName().toLower()) \
        .arg(docCommentClass()) \
        .arg(generateDocCommentPropertiesComment()) \
        .arg(sourceFileDefaultConstructor()) \
        .arg(sourceFileDestructor()) \
        .arg(generateReadFunctionDefine()) \
        .arg(generateWriteFunctionDefine()) \
        .arg(generateResetFunctionDefine())

#endif // PARAMENTS_CODEFORMAT_H
