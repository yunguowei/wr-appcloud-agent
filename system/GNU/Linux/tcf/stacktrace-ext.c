/*******************************************************************************
 * Copyright (c) 2016 Wind River Systems, Inc. and others.
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

#include <tcf/config.h>

#if TARGET_UNIX && ENABLE_Symbols
#include <tcf/framework/cpudefs.h>
#include <tcf/services/symbols.h>
#include <tcf/services/stacktrace-ext.h>

int linux_trace_stack_bottom_check(StackFrame * frame) {
    uint64_t pc = 0;
    Symbol * symbol = NULL;
    ContextAddress size = 0;
    ContextAddress entry = 0;

    if (!context_has_state(frame->ctx)) return 0;

    if (read_reg_value(frame, get_PC_definition(frame->ctx), &pc) < 0) return -1;

    if (find_symbol_by_name(frame->ctx, STACK_NO_FRAME, 0, "main", &symbol) < 0) return -1;
    if ((symbol != NULL) && (get_symbol_size (symbol, &size) < 0)) return -1;
    if ((symbol != NULL) && (get_symbol_address(symbol, &entry) < 0)) return -1;
    if ((pc >= entry) && (pc < (entry + size)))  return 1;

    if (find_symbol_by_name(frame->ctx, STACK_NO_FRAME, 0, "start_thread", &symbol) < 0) return -1;
    if ((symbol != NULL) && (get_symbol_size (symbol, &size) < 0)) return -1;
    if ((symbol != NULL) && (get_symbol_address(symbol, &entry) < 0)) return -1;
    if ((pc >= entry) && (pc < (entry + size))) return 1;
    return 0;
}
#endif
