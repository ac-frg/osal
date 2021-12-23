#ifndef OSAL_AC_LOG_H
#define OSAL_AC_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "osal_log.h"

typedef void (*ac_log) (const char *msg);

// connect these callbacks to get logging from the stack
extern ac_log ac_log_debug_cb;
extern ac_log ac_log_info_cb;
extern ac_log ac_log_warn_cb;
extern ac_log ac_log_error_cb;
extern ac_log ac_log_fatal_cb;

#ifdef __cplusplus
}
#endif

#endif /* OSAL_AC_LOG_H */
