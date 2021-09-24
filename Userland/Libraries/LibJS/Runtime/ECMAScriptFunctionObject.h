/*
 * Copyright (c) 2020-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/AST.h>
#include <LibJS/Bytecode/Generator.h>
#include <LibJS/Runtime/FunctionObject.h>

namespace JS {

// 10.2 ECMAScript Function Objects, https://tc39.es/ecma262/#sec-ecmascript-function-objects
class ECMAScriptFunctionObject final : public FunctionObject {
    JS_OBJECT(ECMAScriptFunctionObject, FunctionObject);

public:
    enum class ConstructorKind : u8 {
        Base,
        Derived,
    };

    enum class ThisMode : u8 {
        Lexical,
        Strict,
        Global,
    };

    static ECMAScriptFunctionObject* create(GlobalObject&, FlyString name, Statement const& ecmascript_code, Vector<FunctionNode::Parameter> parameters, i32 m_function_length, Environment* parent_scope, FunctionKind, bool is_strict, bool is_arrow_function = false);

    ECMAScriptFunctionObject(GlobalObject&, FlyString name, Statement const& ecmascript_code, Vector<FunctionNode::Parameter> parameters, i32 m_function_length, Environment* parent_scope, Object& prototype, FunctionKind, bool is_strict, bool is_arrow_function = false);
    virtual void initialize(GlobalObject&) override;
    virtual ~ECMAScriptFunctionObject();

    Statement const& ecmascript_code() const { return m_ecmascript_code; }
    Vector<FunctionNode::Parameter> const& formal_parameters() const { return m_formal_parameters; };

    virtual Value call() override;
    virtual Value construct(FunctionObject& new_target) override;

    virtual const FlyString& name() const override { return m_name; };
    void set_name(const FlyString& name);

    void set_is_class_constructor() { m_is_class_constructor = true; };

    auto& bytecode_executable() const { return m_bytecode_executable; }

    virtual Environment* environment() override { return m_environment; }
    virtual Realm* realm() const override { return m_realm; }

    ConstructorKind constructor_kind() const { return m_constructor_kind; };
    void set_constructor_kind(ConstructorKind constructor_kind) { m_constructor_kind = constructor_kind; }

    ThisMode this_mode() const { return m_this_mode; }

    Object* home_object() const { return m_home_object; }
    void set_home_object(Object* home_object) { m_home_object = home_object; }

protected:
    virtual bool is_strict_mode() const final { return m_strict; }

private:
    virtual bool is_ecmascript_function_object() const override { return true; }
    virtual FunctionEnvironment* create_environment(FunctionObject&) override;
    virtual void visit_edges(Visitor&) override;

    Value execute_function_body();

    // Internal Slots of ECMAScript Function Objects, https://tc39.es/ecma262/#table-internal-slots-of-ecmascript-function-objects
    Environment* m_environment { nullptr };                       // [[Environment]]
    Vector<FunctionNode::Parameter> const m_formal_parameters;    // [[FormalParameters]]
    NonnullRefPtr<Statement> m_ecmascript_code;                   // [[ECMAScriptCode]]
    ConstructorKind m_constructor_kind { ConstructorKind::Base }; // [[ConstructorKind]]
    Realm* m_realm { nullptr };                                   // [[Realm]]
    ThisMode m_this_mode { ThisMode::Global };                    // [[ThisMode]]
    bool m_strict { false };                                      // [[Strict]]
    Object* m_home_object { nullptr };                            // [[HomeObject]]
    bool m_is_class_constructor { false };                        // [[IsClassConstructor]]

    FlyString m_name;
    Optional<Bytecode::Executable> m_bytecode_executable;
    i32 m_function_length { 0 };
    FunctionKind m_kind { FunctionKind::Regular };
    bool m_is_arrow_function { false };
};

}