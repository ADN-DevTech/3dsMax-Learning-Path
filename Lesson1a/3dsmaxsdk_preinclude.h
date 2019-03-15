//**************************************************************************/
// Copyright (c) 1998-2018 Autodesk, Inc.
// All rights reserved.
// 
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: Include this file before including any 3ds Max SDK files. It 
//              define the macros required to add linkable todo compile-time 
//              messages. Therefore if you use this TODO macro, it will emit
//              a message that you can click on, and visual studio will open
//              the file and line where the message is.
// AUTHOR: Jean-Francois Yelle - created Mar.20.2007
//***************************************************************************/

// useful for #pragma message
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define TODO(x) __FILE__ "(" STRING(__LINE__) "): TODO: "x

