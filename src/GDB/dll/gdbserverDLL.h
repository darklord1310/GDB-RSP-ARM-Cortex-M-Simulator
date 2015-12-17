/*
    GDB RSP and ARM Simulator

    Copyright (C) 2015 Wong Yan Yin, <jet_wong@hotmail.com>,
    Jackson Teh Ka Sing, <jackson_dmc69@hotmail.com>

    This file is part of GDB RSP and ARM Simulator.

    This program is free software, you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY, without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef gdbserverDLL_H
#define gdbserverDLL_H

#include "jni.h"
#include "dllExportImport.h"
#include "stateRSP.h"

/* Make sure functions are exported with C linkage under C++ compilers. */

#ifdef __cplusplus
extern "C"
{
#endif


/* Declare our Add function using the above definitions. */
GDBSERVER_EX void GDBSERVER_CALL gdbserverMain(RspData *rspData, char *data);

JNIEXPORT jint JNICALL Java_ArmJNI_gdbserver(JNIEnv *env, jobject obj, jdouble period);


#ifdef __cplusplus
} // __cplusplus defined.
#endif

#endif // gdbserverDLL_H
