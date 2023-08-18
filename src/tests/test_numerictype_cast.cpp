
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
TEST_F(NumericCast, GetValueAsDouble) {
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), *dbl_a_ptr.get());
    val = reinterpret_cast<std::byte*>(int_a_ptr.get());
    ASSERT_DOUBLE_EQ(int_type_ref.GetValueAs<model::Double>(val), *int_a_ptr.get());
}
TEST_F(NumericCast, GetValueAsInt) {
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    ASSERT_EQ(dbl_type_ref.GetValueAs<model::Int>(val), (model::Int)*dbl_a_ptr.get());
    val = reinterpret_cast<std::byte*>(int_a_ptr.get());
    ASSERT_EQ(int_type_ref.GetValueAs<model::Int>(val), *int_a_ptr.get());
}
TEST_F(NumericCast, DoubleType_CastTo) {  // TODO changes data inside pointer
    val = reinterpret_cast<std::byte*>(dbl_a_ptr.get());
    dbl_type_ref.CastTo(val, model::DoubleType());
    ASSERT_DOUBLE_EQ(dbl_type_ref.GetValueAs<model::Double>(val), *dbl_a_ptr.get());
    model::Int tmp = (model::Int)(*dbl_a_ptr.get());
    dbl_type_ref.CastTo(val, model::IntType());
    ASSERT_DOUBLE_EQ(int_type_ref.GetValueAs<model::Int>(val), tmp);
}
TEST_F(NumericCast, IntType_CastTo) {
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
=======
#include <gtest/gtest.h>
#include "types.h"
#include <iostream>
namespace tests{
TEST(NumericCast,unit_GetValueAsDouble){
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    model::DoubleType dbl_type;
    model::INumericType & t_ref = dbl_type;
    ASSERT_TRUE(t_ref.GetValueAs<model::Double>(val)==15.15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int(15));
    model::IntType int_type;
    t_ref = int_type;
    ASSERT_TRUE(t_ref.GetValueAs<model::Double>(val)==15.0);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast,unit_GetValueAsInt){
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double(15.15));
    model::DoubleType dbl_type;
    model::INumericType & t_ref = dbl_type;
    ASSERT_TRUE(t_ref.GetValueAs<model::Int>(val)==15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int(15));
    model::IntType int_type;
    t_ref = int_type;
    ASSERT_TRUE(t_ref.GetValueAs<model::Int>(val)==15);
    delete reinterpret_cast<model::Int*>(val);
}
TEST(NumericCast,unit_MakeFromArithmetic){
    model::IntType int_type;
    model::DoubleType dbl_type;
    model::INumericType & type_ref = int_type;
    model::Int int_val = 15;
    model::Double dbl_val = 15.15;
    std::byte* res = type_ref.MakeFromArithmetic(dbl_val);
    ASSERT_TRUE(*reinterpret_cast<model::Int*>(res)==15);
    res = type_ref.MakeFromArithmetic(int_val);
    ASSERT_TRUE(*reinterpret_cast<model::Int*>(res)==15);
    type_ref = dbl_type;
    res = type_ref.MakeFromArithmetic(dbl_val);
    ASSERT_TRUE(*reinterpret_cast<model::Double*>(res)==15.15);
    res = type_ref.MakeFromArithmetic(int_val);
    ASSERT_TRUE(*reinterpret_cast<model::Double*>(res)==15);
}
TEST(NumericCast,unit_DoubleType_CastTo){
    model::DoubleType dbl_type;
    model::INumericType & type_ref = dbl_type;
    std::byte* val = reinterpret_cast<std::byte*>(new model::Double (15.15));
    type_ref.CastTo(val,model::IntType());
    model::Int res = *reinterpret_cast<model::Int*> (val);
    ASSERT_EQ(res,15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Double (15.15));
    type_ref.CastTo(val,model::DoubleType());
    model::Double dbl_res = *reinterpret_cast<model::Double*> (val);
    ASSERT_EQ(dbl_res,15.15);
}
TEST(NumericCast,unit_IntType_CastTo){
    model::IntType dbl_type;
    model::INumericType & type_ref = dbl_type;
    std::byte* val = reinterpret_cast<std::byte*>(new model::Int (15));
    type_ref.CastTo(val,model::DoubleType());
    model::Double res = *reinterpret_cast<model::Double*> (val);
    ASSERT_EQ(res,15);
    delete reinterpret_cast<model::Double*>(val);
    val = reinterpret_cast<std::byte*>(new model::Int (15));
    type_ref.CastTo(val,model::IntType());
    model::Int int_res = *reinterpret_cast<model::Int*> (val);
    ASSERT_EQ(res,15);
    delete reinterpret_cast<model::Double*>(val);
}
TEST(NumericCast,MakeIntFromDouble){ // double -> IntType
    model::Double test_val = 22.9;
    model::IntType int_type;
    model::INumericType & int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val); 
    ASSERT_TRUE(int_type_ref.GetValueAs<model::Int>(get_val)==(model::Int)(test_val));
}
TEST(NumericCast,MakeIntFromInt){ // int -> IntType
    model::Int test_val = 22;
    model::IntType int_type;
    model::INumericType & int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val); 
    ASSERT_TRUE(int_type_ref.GetValueAs<model::Int>(get_val)==(model::Int)(test_val));
}
TEST(NumericCast,MakeDoubleFromDouble){ // double -> DoubleType
    model::Double test_val = 22.9;
    model::DoubleType int_type;
    model::INumericType & int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val); 
    ASSERT_TRUE(int_type_ref.GetValueAs<model::Double>(get_val)==(model::Double)(test_val));
}
TEST(NumericCast,MakeDoubleFromInt){ // int -> DobuleType
    model::Int test_val = 22;
    model::DoubleType int_type;
    model::INumericType & int_type_ref = int_type;
    std::byte* get_val = int_type_ref.MakeFromArithmetic(test_val); 
    ASSERT_TRUE(int_type_ref.GetValueAs<model::Double>(get_val)==(model::Double)(test_val));
}
TEST(NumericCast,CastDoubleToInt){ // DoubleType -> IntType
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte * val = dbl_ref.MakeFromArithmetic(12.8f);
    
    dbl_ref.CastTo(val,int_ref);
    ASSERT_EQ(int_ref.GetValueAs<model::Int>(val),12);
}
TEST(NumericCast,CastDoubleToDouble){ // DoubleType -> DoubleType
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte * val = dbl_ref.MakeFromArithmetic(12.8);
    
    dbl_ref.CastTo(val,dbl_ref);
    ASSERT_EQ(dbl_ref.GetValueAs<model::Double>(val),12.8);
}
TEST(NumericCast,CastIntToDouble){ // IntType -> DoubleType
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte * val = int_ref.MakeFromArithmetic(12);
    int_ref.CastTo(val,dbl_ref);
    ASSERT_EQ(dbl_ref.GetValueAs<model::Double>(val),12);
}
TEST(NumericCast,CastIntToInt){ // IntType -> IntType
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte * val = int_ref.MakeFromArithmetic(12);
    int_ref.CastTo(val,int_ref);
    ASSERT_EQ(int_ref.GetValueAs<model::Int>(val),12);
}
TEST(NumericCast,ArifmeticDoubleCastedToInt){ // DoubleType -> IntType (+,-,*,/)
    std::byte* sum_res ,* mult_res , *div_res  , *sub_res  ;
    sum_res = reinterpret_cast<std::byte*>(new model::Int (8));
    sub_res = reinterpret_cast<std::byte*>(new model::Int (8));
    mult_res = reinterpret_cast<std::byte*>(new model::Int (8));
    div_res = reinterpret_cast<std::byte*>(new model::Int (8));
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte* a = dbl_ref.MakeFromArithmetic(28.8);
    std::byte* b = dbl_ref.MakeFromArithmetic(56.2);
    dbl_ref.CastTo(a,int_ref);
    dbl_ref.CastTo(b,int_ref);
    int_ref.Add(a,b,sum_res);
    int_ref.Sub(a,b,sub_res);
    int_ref.Mul(a,b,mult_res);
    int_ref.Div(a,b,div_res);
    ASSERT_TRUE(int_ref.GetValueAs<model::Int>(sum_res)==28+56);
    ASSERT_TRUE(int_ref.GetValueAs<model::Int>(sub_res)==28-56);
    ASSERT_TRUE(int_ref.GetValueAs<model::Int>(div_res)==28/56);
    ASSERT_TRUE(int_ref.GetValueAs<model::Int>(mult_res)==28*56);
    delete reinterpret_cast<model::Int*>(sum_res);
    delete reinterpret_cast<model::Int*>(sub_res);
    delete reinterpret_cast<model::Int*>(mult_res);
    delete reinterpret_cast<model::Int*>(div_res);
}
TEST(NumericCast,ArifmeticIntCastedToDouble){ // IntType -> DoubleType (+,-,*,/)
    std::byte* sum_res ,* mult_res , *div_res  , *sub_res  ;
    sum_res = reinterpret_cast<std::byte*>(new model::Double (8));
    sub_res = reinterpret_cast<std::byte*>(new model::Double (8));
    mult_res = reinterpret_cast<std::byte*>(new model::Double (8));
    div_res = reinterpret_cast<std::byte*>(new model::Double (8));
    model::DoubleType dbl_type;
    model::IntType    int_type;
    model::INumericType & dbl_ref = dbl_type;
    model::INumericType & int_ref = int_type;
    std::byte* a = int_ref.MakeFromArithmetic(28.8);
    std::byte* b = int_ref.MakeFromArithmetic(56.2);
    int_ref.CastTo(a,dbl_ref);
    int_ref.CastTo(b,dbl_ref);
    dbl_ref.Add(a,b,sum_res);
    dbl_ref.Sub(a,b,sub_res);
    dbl_ref.Mul(a,b,mult_res);
    dbl_ref.Div(a,b,div_res);
    ASSERT_TRUE(dbl_ref.GetValueAs<model::Int>(sum_res)==28+56);
    ASSERT_TRUE(dbl_ref.GetValueAs<model::Int>(sub_res)==28-56);
    ASSERT_TRUE(dbl_ref.GetValueAs<model::Int>(div_res)==28/56);
    ASSERT_TRUE(dbl_ref.GetValueAs<model::Int>(mult_res)==28*56);
    delete reinterpret_cast<model::Double*>(sum_res);
    delete reinterpret_cast<model::Double*>(sub_res);
    delete reinterpret_cast<model::Double*>(mult_res);
    delete reinterpret_cast<model::Double*>(div_res);
}

TEST(NumericCast,CastDoubleToBuiltin){ // DoubleType -> double,int,float
    model::DoubleType dbl_type;
    model::INumericType & dbl_ref = dbl_type;
    std::byte * val = dbl_ref.MakeFromArithmetic(122.41);

    ASSERT_EQ(dbl_ref.GetValueAs<model::Double> (val) ,122.41);
    ASSERT_EQ(dbl_ref.GetValueAs<float> (val) ,122.41f);
    ASSERT_EQ(dbl_ref.GetValueAs<model::Int> (val) ,122);
}
TEST(NumericCast,CastIntToBuiltin){ // IntType -> double,int,float
    model::IntType dbl_type;
    model::INumericType & dbl_ref = dbl_type;
    std::byte * val = dbl_ref.MakeFromArithmetic(122);

    ASSERT_TRUE(dbl_ref.GetValueAs<model::Double> (val) ==122.0);
    ASSERT_TRUE(dbl_ref.GetValueAs<float> (val) ==122.0f);
    ASSERT_TRUE(dbl_ref.GetValueAs<model::Int> (val) ==122);

}
}  // namespace tests
