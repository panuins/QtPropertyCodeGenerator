#ifndef PARAMENTS_BASE_H
#define PARAMENTS_BASE_H

#define CODESCHEME_Indent "    "

#define CODESCHEME_InlineNotation "inline "

#define CODESCHEME_DateTimeFormat "yyyy-MM-dd, hh:mm"

//#define CODESCHEME_DocComment_Use_Doxygen
//#define CODESCHEME_DocComment_Use_QDoc

#define CODESCHEME_DocComment_Comma ", "

#define CODESCHEME_DocComment_Period ". "

#define CODESCHEME_DocComment_ReadOnlyProperty QString("This is a read-only property")

#define CODESCHEME_DocComment_WriteOnlyProperty QString("This is a write-only property")

#define CODESCHEME_DocComment_WriteFunction_SignalDetail \
    QString("and send signal %1").arg(signalName())

#include "paraments_DocComment_Content.h"
#include "paraments_NameScheme.h"
#include "paraments_CodeFormat.h"

#endif // PARAMENTS_BASE_H
