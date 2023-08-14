#pragma once

#include "numeric_type.h"

namespace model {
class DoubleType final : public NumericType<Double> {
public:
    DoubleType() noexcept : NumericType<Double>(TypeId::kDouble) {}
    virtual void CastTo(std::byte*& value, INumericType const& to) override {
        CastTo(value, to.GetTypeId());
    }
    virtual void CastTo(std::byte*& value, TypeId to_type) override {
        if (value == nullptr || value == 0 || value == NULL) {
            throw std::logic_error("cannot convert nullpointer");
        }
        switch (to_type) {
            case TypeId::kInt: {
                model::Double data = *reinterpret_cast<model::Double*>(value);
                delete reinterpret_cast<model::Double*>(value);
                model::Int data_int = static_cast<model::Int>(data);
                value = reinterpret_cast<std::byte*>(new model::Int(data_int));
            } break;
            case TypeId::kDouble: {
            } break;
            default: {
                throw std::logic_error("type conversion unsupported");
            } break;
        }
    }
    CompareResult Compare(std::byte const* l, std::byte const* r) const final {
        Double l_val = GetValue(l);
        Double r_val = GetValue(r);

        if (std::abs(l_val - r_val) < std::numeric_limits<Double>::epsilon()) {
            return CompareResult::kEqual;
        }

        if (l_val < r_val) {
            return CompareResult::kLess;
        }

        return CompareResult::kGreater;
    }

    [[nodiscard]] std::unique_ptr<Type> CloneType() const override {
        return std::make_unique<DoubleType>();
    }

    static std::byte* MakeFrom(const std::byte* data, const Type& type) {
        switch (type.GetTypeId()) {
            case TypeId::kDouble:
                return DoubleType().Clone(data);
            case TypeId::kInt:
                return DoubleType().MakeValue(Type::GetValue<Int>(data));
            default:
                return nullptr;
        }
    }
};
}  // namespace model
