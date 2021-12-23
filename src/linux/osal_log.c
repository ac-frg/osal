/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2017 rt-labs AB, Sweden.
 *
 * This software is licensed under the terms of the BSD 3-clause
 * license. See the file LICENSE distributed with this software for
 * full license information.
 ********************************************************************/

#ifndef BUILD_WITH_AC_LOGGING

#include "osal_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void os_log (uint8_t type, const char * fmt, ...)
{
   va_list list;
   time_t rawtime;
   struct tm timestruct;
   char timestamp[10];

   time (&rawtime);
   localtime_r (&rawtime, &timestruct);
   strftime (timestamp, sizeof (timestamp), "%H:%M:%S", &timestruct);

   switch (LOG_LEVEL_GET (type))
   {
   case LOG_LEVEL_DEBUG:
      printf ("[%s DEBUG] ", timestamp);
      break;
   case LOG_LEVEL_INFO:
      printf ("[%s INFO ] ", timestamp);
      break;
   case LOG_LEVEL_WARNING:
      printf ("[%s WARN ] ", timestamp);
      break;
   case LOG_LEVEL_ERROR:
      printf ("[%s ERROR] ", timestamp);
      break;
   case LOG_LEVEL_FATAL:
      printf ("[%s FATAL] ", timestamp);
      break;
   default:
      break;
   }

   va_start (list, fmt);
   vprintf (fmt, list);
   va_end (list);
   fflush (stdout);
}

#else

#include "osal_ac_log.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

ac_log ac_log_debug_cb = NULL;
ac_log ac_log_info_cb  = NULL;
ac_log ac_log_warn_cb  = NULL;
ac_log ac_log_error_cb = NULL;
ac_log ac_log_fatal_cb = NULL;

void os_log (uint8_t type, const char * fmt, ...)
{
   va_list list;
   // problem when logging is too long
   char buffer[512];

   va_start (list, fmt);
   vsprintf (buffer, fmt, list);
   va_end (list);

   // filter out \r\n (not mandatory, but it's cleaner in the log output)
   size_t len = strlen (buffer);
   if (len == 0)
   {
      return;
   }
   while (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')
   {
      buffer[len - 1] = '\0';
      len--;
      if (len == 0)
      {
         return;
      }
   }

   switch (LOG_LEVEL_GET (type))
   {
   case LOG_LEVEL_DEBUG:
      if (ac_log_debug_cb)
      {
         ac_log_debug_cb (buffer);
      }
      break;
   case LOG_LEVEL_INFO:
      if (ac_log_info_cb)
      {
         ac_log_info_cb (buffer);
      }
      break;
   case LOG_LEVEL_WARNING:
      if (ac_log_warn_cb)
      {
         ac_log_warn_cb (buffer);
      }
      break;
   case LOG_LEVEL_ERROR:
      if (ac_log_error_cb)
      {
         ac_log_error_cb (buffer);
      }
      break;
   case LOG_LEVEL_FATAL:
      if (ac_log_fatal_cb)
      {
         ac_log_fatal_cb (buffer);
      }
      break;
   default:
      break;
   }
}
#endif /* BUILD_WITH_AC_LOGGING */
