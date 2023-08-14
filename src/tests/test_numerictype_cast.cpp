#include <iostream>

#include <gtest/gtest.h>

#include "types.h"

namespace tests {
TEST(NumericCast, unit_GetValueAsDouble) {
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    model::DoubleType dbl_type;
    model::INumericType& t_ref = dbl_type;
    EXPECT_TRUE(t_ref.GetValueAs<model::Double>(val) == 15.15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int(15));
    model::IntType int_type;
    t_ref = int_type;
    EXPECT_TRUE(t_ref.GetValueAs<model::Double>(val) == 15.0);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast, unit_GetValueAsInt) {
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    model::DoubleType dbl_type;
    model::INumericType& t_ref = dbl_type;
    EXPECT_TRUE(t_ref.GetValueAs<model::Int>(val) == 15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int(15));
    model::IntType int_type;
    t_ref = int_type;
    EXPECT_TRUE(t_ref.GetValueAs<model::Int>(val) == 15);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast, unit_MakeFromArithmetic) {
    model::IntType int_type;
    model::DoubleType dbl_type;
    model::INumericType& type_ref = int_type;
    model::Int int_val = 15;
    model::Double dbl_val = 15.15;

    std::byte* res = type_ref.MakeFromArithmetic(dbl_val);
    EXPECT_TRUE(*reinterpret_cast<model::Int*>(res) == 15);
    delete reinterpret_cast<model::Int*>(res);

    res = type_ref.MakeFromArithmetic(int_val);
    EXPECT_TRUE(*reinterpret_cast<model::Int*>(res) == 15);
    delete reinterpret_cast<model::Int*>(res);

    type_ref = dbl_type;
    res = type_ref.MakeFromArithmetic(dbl_val);
    EXPECT_TRUE(*reinterpret_cast<model::Double*>(res) == 15.15);
    delete reinterpret_cast<model::Double*>(res);

    res = type_ref.MakeFromArithmetic(int_val);
    EXPECT_TRUE(*reinterpret_cast<model::Double*>(res) == 15);
    delete reinterpret_cast<model::Double*>(res);
}
TEST(NumericCast, unit_DoubleType_CastTo) {
    model::DoubleType dbl_type;
    model::INumericType& type_ref = dbl_type;
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    type_ref.CastTo(val, model::IntType());
    model::Int res = *reinterpret_cast<model::Int*>(val);
    EXPECT_EQ(res, 15);
    delete reinterpret_cast<model::Int*>(val);
    val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    type_ref.CastTo(val, model::DoubleType());
    model::Double dbl_res = *reinterpret_cast<model::Double*>(val);
    EXPECT_EQ(dbl_res, 15.15);
    delete reinterpret_cast<model::Double*>(val);
}
TEST(NumericCast, unit_IntType_CastTo) {
    model::IntType dbl_type;
    model::INumericType& type_ref = dbl_type;
    std::byte* val = reinterpret_cast<std::byte*>(new model::Int(15));
    type_ref.CastTo(val, model::DoubleType());
    model::Double res = *reinterpret_cast<model::Double*>(val);
    EXPECT_EQ(res, 15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int(15));
    type_ref.CastTo(val, model::IntType());
    model::Int int_res = *reinterpret_cast<model::Int*>(val);
    EXPECT_EQ(int_res, 15);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast, MakeIntFromDouble) {  // double -> IntType
    model::Double test_val = 22.9;
    model::IntType int_type;
    model::INumericType& int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val);
    EXPECT_TRUE(int_type_ref.GetValueAs<model::Int>(get_val) == (model::Int)(test_val));
    delete reinterpret_cast<model::Int*>(get_val);
}
TEST(NumericCast, MakeIntFromInt) {  // int -> IntType
    model::Int test_val = 22;
    model::IntType int_type;
    model::INumericType& int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val);
    EXPECT_TRUE(int_type_ref.GetValueAs<model::Int>(get_val) == (model::Int)(test_val));
    delete reinterpret_cast<model::Int*>(get_val);
}
TEST(NumericCast, MakeDoubleFromDouble) {  // double -> DoubleType
    model::Double test_val = 22.9;
    model::DoubleType int_type;
    model::INumericType& int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val);
    EXPECT_TRUE(int_type_ref.GetValueAs<model::Double>(get_val) == (model::Double)(test_val));
    delete reinterpret_cast<model::Double*>(get_val);
}
TEST(NumericCast, MakeDoubleFromInt) {  // int -> DobuleType
    model::Int test_val = 22;
    model::DoubleType int_type;
    model::INumericType& int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val);
    EXPECT_TRUE(int_type_ref.GetValueAs<model::Double>(get_val) == (model::Double)(test_val));
    delete reinterpret_cast<model::Double*>(get_val);
}
TEST(NumericCast, CastDoubleToInt) {  // DoubleType -> IntType
    model::DoubleType dbl_type;
    model::IntType int_type;
    model::INumericType& dbl_ref = dbl_type;
    model::INumericType& int_ref = int_type;
    std::byte* val = dbl_ref.MakeFromArithmetic(12.8f);

    dbl_ref.CastTo(val, int_ref);
    EXPECT_EQ(int_ref.GetValueAs<model::Int>(val), 12);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast, CastDoubleToDouble) {  // DoubleType -> DoubleType
    model::DoubleType dbl_type;
    model::INumericType& dbl_ref = dbl_type;
    std::byte* val = dbl_ref.MakeFromArithmetic(12.8);
    dbl_ref.CastTo(val, dbl_ref);
    EXPECT_EQ(dbl_ref.GetValueAs<model::Double>(val), 12.8);
    delete reinterpret_cast<model::Double*>(val);
}
TEST(NumericCast, CastIntToDouble) {  // IntType -> DoubleType
    model::DoubleType dbl_type;
    model::IntType int_type;
    model::INumericType& dbl_ref = dbl_type;
    model::INumericType& int_ref = int_type;
    std::byte* val = int_ref.MakeFromArithmetic(12);
    int_ref.CastTo(val, dbl_ref);
    EXPECT_EQ(dbl_ref.GetValueAs<model::Double>(val), 12);
    delete reinterpret_cast<model::Double*>(val);
}
TEST(NumericCast, CastIntToInt) {  // IntType -> IntType
    model::IntType int_type;
    model::INumericType& int_ref = int_type;
    std::byte* val = int_ref.MakeFromArithmetic(12);
    int_ref.CastTo(val, int_ref);
    EXPECT_EQ(int_ref.GetValueAs<model::Int>(val), 12);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast, ArifmeticDoubleCastedToInt) {  // DoubleType -> IntType (+,-,*,/)
    std::byte *sum_res, *mult_res, *div_res, *sub_res;
    sum_res = reinterpret_cast<std::byte*>(new model::Int(8));
    sub_res = reinterpret_cast<std::byte*>(new model::Int(8));
    mult_res = reinterpret_cast<std::byte*>(new model::Int(8));
    div_res = reinterpret_cast<std::byte*>(new model::Int(8));
    model::DoubleType dbl_type;
    model::IntType int_type;
    model::INumericType& dbl_ref = dbl_type;
    model::INumericType& int_ref = int_type;
    std::byte* a = dbl_ref.MakeFromArithmetic(28.8);
    std::byte* b = dbl_ref.MakeFromArithmetic(56.2);
    dbl_ref.CastTo(a, int_ref);
    dbl_ref.CastTo(b, int_ref);
    int_ref.Add(a, b, sum_res);
    int_ref.Sub(a, b, sub_res);
    int_ref.Mul(a, b, mult_res);
    int_ref.Div(a, b, div_res);
    EXPECT_TRUE(int_ref.GetValueAs<model::Int>(sum_res) == 28 + 56);
    EXPECT_TRUE(int_ref.GetValueAs<model::Int>(sub_res) == 28 - 56);
    EXPECT_TRUE(int_ref.GetValueAs<model::Int>(div_res) == 28 / 56);
    EXPECT_TRUE(int_ref.GetValueAs<model::Int>(mult_res) == 28 * 56);
    delete reinterpret_cast<model::Int*>(sum_res);
    delete reinterpret_cast<model::Int*>(sub_res);
    delete reinterpret_cast<model::Int*>(mult_res);
    delete reinterpret_cast<model::Int*>(div_res);
    delete reinterpret_cast<model::Int*>(a);
    delete reinterpret_cast<model::Int*>(b);
}
TEST(NumericCast, ArifmeticIntCastedToDouble) {  // IntType -> DoubleType (+,-,*,/)
    std::byte *sum_res, *mult_res, *div_res, *sub_res;
    sum_res = reinterpret_cast<std::byte*>(new model::Double(8));
    sub_res = reinterpret_cast<std::byte*>(new model::Double(8));
    mult_res = reinterpret_cast<std::byte*>(new model::Double(8));
    div_res = reinterpret_cast<std::byte*>(new model::Double(8));
    model::DoubleType dbl_type;
    model::IntType int_type;
    model::INumericType& dbl_ref = dbl_type;
    model::INumericType& int_ref = int_type;
    std::byte* a = int_ref.MakeFromArithmetic(28.8);
    std::byte* b = int_ref.MakeFromArithmetic(56.2);
    int_ref.CastTo(a, dbl_ref);
    int_ref.CastTo(b, dbl_ref);
    dbl_ref.Add(a, b, sum_res);
    dbl_ref.Sub(a, b, sub_res);
    dbl_ref.Mul(a, b, mult_res);
    dbl_ref.Div(a, b, div_res);
    EXPECT_TRUE(dbl_ref.GetValueAs<model::Double>(sum_res) == 28.0 + 56.0);
    EXPECT_TRUE(dbl_ref.GetValueAs<model::Double>(sub_res) == 28.0 - 56.0);
    EXPECT_TRUE(dbl_ref.GetValueAs<model::Double>(div_res) == 28.0 / 56.0);
    EXPECT_TRUE(dbl_ref.GetValueAs<model::Double>(mult_res) == 28.0 * 56.0);
    delete reinterpret_cast<model::Double*>(sum_res);
    delete reinterpret_cast<model::Double*>(sub_res);
    delete reinterpret_cast<model::Double*>(mult_res);
    delete reinterpret_cast<model::Double*>(div_res);
    delete reinterpret_cast<model::Double*>(a);
    delete reinterpret_cast<model::Double*>(b);
}

TEST(NumericCast, CastDoubleToBuiltin) {  // DoubleType -> double,int,float
    model::DoubleType dbl_type;
    model::INumericType& dbl_ref = dbl_type;
    std::byte* val = dbl_ref.MakeFromArithmetic(122.41);

    EXPECT_EQ(dbl_ref.GetValueAs<model::Double>(val), 122.41);
    EXPECT_EQ(dbl_ref.GetValueAs<float>(val), 122.41f);
    EXPECT_EQ(dbl_ref.GetValueAs<model::Int>(val), 122);
    delete reinterpret_cast<model::Double*>(val);
}
TEST(NumericCast, CastIntToBuiltin) {  // IntType -> double,int,float
    model::IntType dbl_type;
    model::INumericType& dbl_ref = dbl_type;
    std::byte* val = dbl_ref.MakeFromArithmetic(122);

    EXPECT_TRUE(dbl_ref.GetValueAs<model::Double>(val) == 122.0);
    EXPECT_TRUE(dbl_ref.GetValueAs<float>(val) == 122.0f);
    EXPECT_TRUE(dbl_ref.GetValueAs<model::Int>(val) == 122);
    delete reinterpret_cast<model::Int*>(val);
}

}  // namespace tests
