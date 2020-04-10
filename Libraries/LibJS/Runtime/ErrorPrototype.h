/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <LibJS/Runtime/Error.h>

namespace JS {

class ErrorPrototype final : public Object {
public:
    ErrorPrototype();
    virtual ~ErrorPrototype() override;

private:
    virtual const char* class_name() const override { return "ErrorPrototype"; }

    static Value to_string(Interpreter&);

    static Value name_getter(Interpreter&);
    static Value message_getter(Interpreter&);
};

#define DECLARE_ERROR_SUBCLASS_PROTOTYPE(TitleCase, snake_case) \
    class TitleCase final : public Object {                     \
    public:                                                     \
        TitleCase();                                            \
        virtual ~TitleCase() override;                          \
                                                                \
    private:                                                    \
        virtual const char* class_name() const override;        \
    };

#define __JS_ENUMERATE_ERROR_SUBCLASS(TitleCase, snake_case) \
    DECLARE_ERROR_SUBCLASS_PROTOTYPE(TitleCase##Prototype, snake_case##_prototype)
JS_ENUMERATE_ERROR_SUBCLASSES
#undef __JS_ENUMERATE_ERROR_SUBCLASS

}
