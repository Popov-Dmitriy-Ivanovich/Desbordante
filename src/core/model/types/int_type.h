#pragma once

#include "double_type.h"
#include "numeric_type.h"
namespace model {
class IntType final : public NumericType<Int> {
public:
    virtual void CastTo(std::byte*& value, INumericType const& to) override {
        CastTo(value, to.GetTypeId());
    }
    virtual void CastTo(std::byte*& value, TypeId to_type) override {
        if (value == nullptr || value == 0 || value == NULL) {
            throw std::logic_error("cannot convert nullpointer");
        }
        switch (to_type) {
            case TypeId::kDouble: {
                model::Int data = *reinterpret_cast<model::Int*>(value);
                delete reinterpret_cast<model::Int*>(value);
                value = reinterpret_cast<std::byte*>(
                        new model::Double(static_cast<model::Double>(data)));
                ;
            } break;
            case TypeId::kInt: {
            } break;
            default: {
                throw std::logic_error("type conversion unsupported");
            } break;
        }
    }
    IntType() noexcept : NumericType<Int>(TypeId::kInt) {}

    [[nodiscard]] std::unique_ptr<Type> CloneType() const override {
        return std::make_unique<IntType>();
    }
};

}  // namespace model

