/*
 * wpa_supplicant/hostapd - Default include files
 * Copyright (c) 2005-2006, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 *
 * This header file is included into all C files so that commonly used header
 * files can be selected with OS specific ifdef blocks in one place instead of
 * having to have OS/C library specific selection in many files.
 */

#ifndef INCLUDES_H
#define INCLUDES_H

/* Include possible build time configuration before including anything else */
#include "build_config.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#ifndef _WIN32_WCE
#include <signal.h>
#include <sys/types.h>
#include <errno.h>
#endif /* _WIN32_WCE */


#ifndef _MSC_VER
#include <unistd.h>
#endif /* _MSC_VER */

#ifdef _MSC_VER
#include <io.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <sys/stat.h>

#define open _open
#define fdopen _fdopen

#define S_IRUSR _S_IREAD
#define S_IWUSR _S_IWRITE
#define S_IRGRP 0
#define S_IWGRP 0
#define S_IROTH 0
#endif

#ifndef CONFIG_NATIVE_WINDOWS
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#ifndef __vxworks
#include <sys/uio.h>
#include <sys/time.h>
#endif /* __vxworks */

#endif /* CONFIG_NATIVE_WINDOWS */

#endif /* INCLUDES_H */
