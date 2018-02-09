/*******************************************************************************
 * Copyright (c) 2007, 2014 Wind River Systems, Inc. and others.
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 * The Eclipse Public License is available at
 * http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 * You may elect to redistribute this code under either of these licenses.
 *
 * Contributors:
 *     Wind River Systems - initial API and implementation
 *******************************************************************************/

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
