/*
 * Copyright (c) 2016 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
 * Extension point definitions for stacktrace.c.
 *
 * TRACE_STACK_BOTTOM_CHECK - check the stack trace bottom limit
 */

#if TARGET_UNIX && ENABLE_Symbols
extern int linux_trace_stack_bottom_check(StackFrame * frame);

#define TRACE_STACK_BOTTOM_CHECK { \
    int reach_bottom = linux_trace_stack_bottom_check(frame); \
    if (reach_bottom == 1) { \
        stack->complete = 1; \
        loc_free(down.regs); \
        break; \
    } \
    else if (reach_bottom < 0) { \
        loc_free(down.regs); \
        break; \
    } \
}
#endif  /* (TARGET_UNIX && ENABLE_Symbols) */
