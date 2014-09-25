#ifndef PARAMENTS_DOCCOMMENT_PUBLICPARAMS_H
#define PARAMENTS_DOCCOMMENT_PUBLICPARAMS_H

/*
 * function
 * in declare & any
 * 全部在头文件的声明中
 * in declare & in header file only
 * 全部在头文件的声明中
 * in declare & in source file only
 * invalid
 * in define & any
 * 全部在函数的定义中
 * in define & in header file only
 * 在源文件中的函数文档注释放到头文件中，两者分离
 * in define & in source file only
 * 在内联函数文档注释放到源文件中，两者分离
 * independent & any
 * 全部在源文件中分离形式
 * independent & in header file only
 * 全部在头文件中分离形式
 * independent & in source file only
 * 全部在源文件中分离形式
 */

#define CODESCHEME_DocComment_Function_InDeclare 0
#define CODESCHEME_DocComment_Function_InDefine 1
#define CODESCHEME_DocComment_Function_Detached 2

#define CODESCHEME_DocComment_Function_Any 0
#define CODESCHEME_DocComment_Function_InHeaderFileOnly 1
#define CODESCHEME_DocComment_Function_InSourceFileOnly 2

#define CODESCHEME_DocComment_MemberVariable_InDeclare 0
#define CODESCHEME_DocComment_MemberVariable_InHeaderFile 1
#define CODESCHEME_DocComment_MemberVariable_InSourceFile 2

#define CODESCHEME_DocComment_Property_InDeclare 0
#define CODESCHEME_DocComment_Property_InHeaderFile 1
#define CODESCHEME_DocComment_Property_InSourceFile 2

#endif // PARAMENTS_DOCCOMMENT_PUBLICPARAMS_H
