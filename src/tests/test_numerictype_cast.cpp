#include <memory>

#include <gtest/gtest.h>

#include "types.h"

namespace tests {
struct NumericCast : public ::testing::Test {
protected:
    void SetUp() override {
        dbl_b_ptr.reset(new model::Double(2.79));
        dbl_a_ptr.reset(new model::Double(5.58));
        int_a_ptr.reset(new model::Int(21));
        int_b_ptr.reset(new model::Int(7));
    }
    void TearDown() override {
        dbl_b_ptr.reset(new model::Double(2.79));
        dbl_a_ptr.reset(new model::Double(5.58));
        int_a_ptr.reset(new model::Int(21));
        int_b_ptr.reset(new model::Int(7));
    }
    std::unique_ptr<model::Double> dbl_a_ptr;
    std::unique_ptr<model::Double> dbl_b_ptr;
    std::unique_ptr<model::Int> int_a_ptr;
    std::unique_ptr<model::Int> int_b_ptr;

    model::DoubleType dbl_type;
    model::INumericType& dbl_type_ref = dbl_type;

    model::IntType int_type;
    model::INumericType& int_type_ref = int_type;

    std::byte* val;
};
TEST_F(NumericCast, unit_GetValueAsDouble) {
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), *dbl_a_ptr.get());
    val = reinterpret_cast<std::byte*>(int_a_ptr.get());
    ASSERT_DOUBLE_EQ(int_type_ref.GetValueAs<model::Double>(val), *int_a_ptr.get());
}
TEST_F(NumericCast, unit_GetValueAsInt) {
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    ASSERT_EQ(dbl_type_ref.GetValueAs<model::Int>(val), (model::Int)*dbl_a_ptr.get());
    val = reinterpret_cast<std::byte*>(int_a_ptr.get());
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(val), *int_a_ptr.get());
}
TEST_F(NumericCast, unit_DoubleType_CastTo) {  // TODO changes data inside pointer
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    dbl_type_ref.CastTo(val, model::DoubleType());
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), *dbl_a_ptr.get());
    model::Int tmp = (model::Int)(*dbl_a_ptr.get());
    dbl_type_ref.CastTo(val, model::IntType());
    ASSERT_DOUBLE_EQ(int_type_ref.GetValueAs<model::Int>(val), tmp);
}
TEST_F(NumericCast, unit_IntType_CastTo) {
    val = reinterpret_cast<std::byte*>(int_a_ptr.get());
    int_type_ref.CastTo(val, model::IntType());
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(val), *int_a_ptr.get());
    model::Double tmp = (model::Double)(*int_a_ptr.get());
    int_type_ref.CastTo(val, model::DoubleType());
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), tmp);
}
TEST_F(NumericCast, ArifmeticDoubleCastedToInt) {
    std::unique_ptr<model::Int> sum_res_ptr(new model::Int(-1)), sub_res_ptr(new model::Int(-1)),
            div_res_ptr(new model::Int(-1)), mult_res_ptr(new model::Int(-1));
    std::byte* sum_res = reinterpret_cast<std::byte*>(sum_res_ptr.get());
    std::byte* sub_res = reinterpret_cast<std::byte*>(sub_res_ptr.get());
    std::byte* div_res = reinterpret_cast<std::byte*>(div_res_ptr.get());
    std::byte* mult_res = reinterpret_cast<std::byte*>(mult_res_ptr.get());
    std::byte* a = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    std::byte* b = reinterpret_cast<std::byte*>(dbl_b_ptr.get());
    dbl_type_ref.CastTo(a, int_type_ref);
    dbl_type_ref.CastTo(b, int_type_ref);
    int_type_ref.Add(a, b, sum_res);
    int_type_ref.Sub(a, b, sub_res);
    int_type_ref.Mul(a, b, mult_res);
    int_type_ref.Div(a, b, div_res);
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(sum_res), 5 + 2);
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(sub_res), 5 - 2);
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(div_res), 5 / 2);
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(mult_res), 5 * 2);
}
TEST_F (NumericCast, ArifmeticIntCastedToDouble) {
    std::unique_ptr<model::Double> sum_res_ptr(new model::Double(-1)), sub_res_ptr(new model::Double(-1)),
            div_res_ptr(new model::Double(-1)), mult_res_ptr(new model::Double(-1));
    std::byte* sum_res = reinterpret_cast<std::byte*>(sum_res_ptr.get());
    std::byte* sub_res = reinterpret_cast<std::byte*>(sub_res_ptr.get());
    std::byte* div_res = reinterpret_cast<std::byte*>(div_res_ptr.get());
    std::byte* mult_res = reinterpret_cast<std::byte*>(mult_res_ptr.get());
    std::byte* a = reinterpret_cast<std::byte*>(int_a_ptr.get());
    std::byte* b = reinterpret_cast<std::byte*>(int_b_ptr.get());
    int_type_ref.CastTo(a, dbl_type_ref);
    int_type_ref.CastTo(b, dbl_type_ref);
    dbl_type_ref.Add(a, b, sum_res);
    dbl_type_ref.Sub(a, b, sub_res);
    dbl_type_ref.Mul(a, b, mult_res);
    dbl_type_ref.Div(a, b, div_res);
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(sum_res), 21 + 7);
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(sub_res), 21 - 7);
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(div_res), 21.0 / 7.0);
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(mult_res), 21 * 7);
}
TEST_F(NumericCast, CastDoubleToBuiltin) {
    val = reinterpret_cast<std::byte*> (dbl_a_ptr.get());

    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), 5.58);
    ASSERT_FLOAT_EQ(dbl_type_ref.GetValueAs<float>(val), 5.58f);
    ASSERT_EQ(dbl_type_ref.GetValueAs<model::Int>(val), 5);
}
TEST_F(NumericCast, CastIntToBuiltin) {
    val = reinterpret_cast<std::byte*> (int_a_ptr.get());

    ASSERT_DOUBLE_EQ(int_type_ref.GetValueAs<model::Double>(val), 21.0);
    ASSERT_FLOAT_EQ(int_type_ref.GetValueAs<float>(val), 21.0f);
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(val), 21);
}
}  // namespace tests
