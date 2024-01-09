#include <iostream>
#include <sstream>
#include <cassert>
#include "BigNum.h"
#include <stdexcept>
#include <functional>

void testBigIntegerInputStream() {
    BigInteger bigInt;
    std::istringstream iss;

    // Test 1: Valid Integer Input
    iss.str("123");
    iss >> bigInt;
    assert(bigInt == BigInteger(123));

    // Test 2: Valid Negative Integer Input
    iss.clear(); // Clear any error flags
    iss.str("-456");
    iss >> bigInt;
    assert(bigInt == BigInteger(-456));

    // Test 3: Input with Leading Whitespace
    iss.clear();
    iss.str("    789");
    iss >> bigInt;
    assert(bigInt == BigInteger(789));

    // Test 4: Input with Trailing Non-numeric Characters
    iss.clear();
    iss.str("345abc");
    iss >> bigInt;
    assert(iss.fail());

    // Test 5: Input with Only Non-numeric Characters
    iss.clear();
    iss.str("xyz");
    iss >> bigInt;
    assert(iss.fail());

    // Test 6: Input with Only a Minus Sign
    iss.clear();
    iss.str("-");
    iss >> bigInt;
    assert(iss.fail());
    iss.clear();
    iss.str("0");
    iss >> bigInt;
    assert(bigInt == BigInteger(0));

    std::cout << "All tests passed for BigInteger input stream operator." << std::endl;
}


std::basic_string<char> BigIntegerToString(BigInteger integer);

std::string toString(const BigInteger& bigInt) {
    std::ostringstream oss;
    //std::cout<<"big int = " << bigInt <<std::endl;
    oss << bigInt;
    return oss.str();
}

std::string toString(const BigRational& bigRational) {
    std::ostringstream oss;
    //std::cout<<"big rational = " << bigRational <<std::endl;
    oss << bigRational;
    return oss.str();
}


std::string vectorToString(const std::vector<int>& v) {
    std::string result;
    for (auto it = v.begin();
        it != v.end(); ++it) {  // Переворачиваем вектор, так как наибольший разряд должен быть впереди
        result += std::to_string(*it);
    }
    return result;
}


void runTest(const std::string& testName, const std::function<std::string()>& testFunction,
    const std::string& expectedOutcome) {
    try {
        std::string outcome = testFunction();
        if (outcome != expectedOutcome) {
            throw std::runtime_error("Test failed. Expected:\n" + expectedOutcome + ", \nbut got:\n" + outcome);
        }
        //std::cout << "Test Passed: " << testName << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Test Failed: " << testName << " - Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cout << "Test Failed: " << testName << " - Unknown Error" << std::endl;
    }
}


int main() {
    try {
        runTest("Multiplication of Opposite Signs",
            []() { return toString(BigRational("-1", "2") * BigRational("1", "2")); },
            "-1/4");
        runTest("Constructor from std::string Positive invalid 9",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("-") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("--") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("-a") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("-abc") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("+-") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("+") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        assert(toString(-BigInteger(std::numeric_limits<int64_t>::min())) == "9223372036854775808");
        assert(toString(BigInteger(std::numeric_limits<int64_t>::min())) == "-9223372036854775808");
        assert(toString(-BigRational(1, std::numeric_limits<int64_t>::min())) == "1/9223372036854775808");

        testBigIntegerInputStream();
        runTest("String Constructor with Leading Zeroes",
            []() { return toString(BigRational("0005", "0025")); },
            "1/5");
        runTest("Subtraction Operator",
            []() { return toString(BigRational(1, 2) - BigRational(1, 3)); },
            "1/6");
        runTest("max int64",
            []() {
                BigInteger a = BigInteger(std::numeric_limits<int64_t>::max());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;

                return toString(a);
            },
            "9223372036854775807");
        runTest("max int64 negative",
            []() {
                BigInteger a = BigInteger(-std::numeric_limits<int64_t>::max());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;

                return toString(a);
            },
            "-9223372036854775807");
        runTest("max int64 negative",
            []() {
                BigInteger a = BigInteger(std::numeric_limits<int64_t>::min());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;
                a = -a;

                return toString(a);
            },
            "9223372036854775808");
        runTest("Default Constructor",
            []() { return toString(BigInteger()); },
            "0");

        runTest("Constructor from int64_t Positive",
            []() { return toString(BigInteger(1234567890)); },
            "1234567890");

        runTest("Constructor from int64_t Zero",
            []() { return toString(BigInteger(0)); },
            "0");

        runTest("Constructor from int64_t Negative",
            []() { return toString(BigInteger(-1234567890)); },
            "-1234567890");

        runTest("Constructor from std::string Positive",
            []() { return toString(BigInteger("+1234567890")); },
            "1234567890");
        runTest("Constructor from std::string Positive invalid",
            []() {
                try {
                    BigInteger("+1a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");

        runTest("Constructor from std::string Positive invalid 1",
            []() {
                try {
                    BigInteger("-1a");
                    return "good";
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");

        runTest("Constructor from std::string Positive invalid 2",
            []() {
                try {
                    BigInteger("+000001a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 3",
            []() {
                try {
                    BigInteger("+1a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 4",
            []() {
                try {
                    BigInteger("-0001a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 5",
            []() {
                try {
                    BigInteger("-a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 6",
            []() {
                try {
                    BigInteger("+a");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 7",
            []() {
                try {
                    BigInteger("+0000a5");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 8",
            []() {
                try {
                    BigInteger("-0000a5");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 9",
            []() {
                try {
                    BigInteger("-");
                    std::cout << " my name is test" << BigInteger("-") << std::endl;
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 10",
            []() {
                try {
                    BigInteger("");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 11",
            []() {
                try {
                    BigInteger("    ");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");
        runTest("Constructor from std::string Positive invalid 12",
            []() {
                try {
                    BigInteger("    43");
                }
                catch (const std::exception&) {
                    return "ex";
                }
            },
            "ex");

        runTest("Constructor from std::string Negative",
            []() { return toString(BigInteger("-1234567890")); },
            "-1234567890");

        runTest("Constructor from std::string Leading Zeroes",
            []() { return toString(BigInteger("000012345")); },
            "12345");

        runTest("Constructor from std::string Only Zeroes",
            []() { return toString(BigInteger("0000")); },
            "0");
        runTest("Constructor from std::string Only Zeroes +",
            []() { return toString(BigInteger("+0000")); },
            "0");
        runTest("Constructor from std::string Only Zeroes -",
            []() { return toString(BigInteger("-0000")); },
            "0");
        runTest("Constructor from std::string leading zeroes and -",
            []() { return toString(BigInteger("-000012")); },
            "-12");
        runTest("Constructor from std::string leading zeroes and -",
            []() { return toString(BigInteger("+000012")); },
            "12");
        runTest("Constructor from std::string leading zeroes and -",
            []() { return toString(BigInteger("+12")); },
            "12");

        runTest("Constructor from std::string - Empty String", []() {
            try {
                BigInteger fromStringEmpty("");
                return "No exception thrown";
            }
            catch (const std::exception&) {
                return "Expected exception thrown";
            }
            }, "Expected exception thrown");

        runTest("Constructor from std::string - String with Whitespace", []() {
            try {
                BigInteger fromStringWhitespace(" 123 ");
                return "No exception thrown";
            }
            catch (const std::exception&) {
                return "Expected exception thrown";
            }
            }, "Expected exception thrown");

        runTest("Constructor from std::string - Non-Numeric String", []() {
            try {
                BigInteger fromStringNonNumeric("abc");
                return "No exception thrown";
            }
            catch (const std::exception&) {
                return "Expected exception thrown";
            }
            }, "Expected exception thrown");
        runTest("Copy Constructor", []() {
            BigInteger original(12345);
            BigInteger copy = original;  // Using the copy constructor
            if (toString(copy) != toString(original))
                return "Copy does not match original";

            original = BigInteger(54321); // Changing the original
            if (toString(copy) == toString(original))
                return "Copy matches original after modification";

            return "Success";
            }, "Success");

        runTest("Copy Assignment Operator", []() {
            BigInteger original(-98765);
            BigInteger copy;
            copy = original;  // Using the copy assignment operator
            if (toString(copy) != toString(original))
                return "Copy does not match original";

            original = BigInteger(-56789); // Changing the original
            if (toString(copy) == toString(original))
                return "Copy matches original after modification";

            return "Success";
            }, "Success");


        runTest("Unary + Operator on Positive Integer",
            []() {
                BigInteger fromInt64Positive = BigInteger(1234567890);
                BigInteger unaryPlus = +fromInt64Positive;
                return toString(unaryPlus);
            },
            "1234567890");

        runTest("Unary - Operator on Positive Integer",
            []() {
                BigInteger fromInt64Positive = BigInteger(1234567890);
                BigInteger unaryMinus = -fromInt64Positive;
                return toString(unaryMinus);
            },
            "-1234567890");

        runTest("Addition Resulting in Zero",
            []() {
                BigInteger fromInt64Positive = BigInteger(1234567890);
                BigInteger fromInt64Negative = BigInteger(-1234567890);
                BigInteger sum = fromInt64Positive + fromInt64Negative;
                return toString(sum);
            },
            "0");

        runTest("Subtraction Resulting in Positive Number",
            []() {
                BigInteger fromInt64Positive = BigInteger(1234567890);
                BigInteger fromInt64Negative = BigInteger(-1234567890);
                BigInteger difference = fromInt64Positive - fromInt64Negative;
                return toString(difference);
            },
            "2469135780");

        runTest("Multiplication Resulting in Negative Number: 1234567890 * (-1234567890)",
            []() {
                BigInteger fromInt64Positive = BigInteger(1234567890);
                BigInteger fromInt64Negative = BigInteger(-1234567890);
                BigInteger product = fromInt64Positive * fromInt64Negative;
                return toString(product);
            },
            "-1524157875019052100");
        runTest("2*3",
            []() {
                BigInteger fromInt64Positive = BigInteger(2);
                BigInteger fromInt64Negative = BigInteger(3);
                BigInteger product = fromInt64Positive * fromInt64Negative;
                return toString(product);
            },
            "6");
        runTest("1*12",
            []() {
                BigInteger fromInt64Positive = BigInteger(1);
                BigInteger fromInt64Negative = BigInteger(12);
                BigInteger product = fromInt64Positive * fromInt64Negative;
                return toString(product);
            },
            "12");
        runTest("-1*1",
            []() {
                BigInteger fromInt64Positive = BigInteger(1);
                BigInteger fromInt64Negative = BigInteger(-1);
                BigInteger product = fromInt64Positive * fromInt64Negative;
                return toString(product);
            },
            "-1");

        runTest("9*9",
            []() {
                BigInteger fromInt64Positive = BigInteger(9);
                BigInteger fromInt64Negative = BigInteger(9);
                BigInteger product = fromInt64Positive * fromInt64Negative;
                return toString(product);
            },
            "81");

        runTest("Test 1", []() {
            return vectorToString(naive_mul({ 1, 2, 3 }, { 4, 5, 6 }));
            }, "56088");  // Ожидаемый результат: "56088"


            // Тестирование умножения однозначных чисел
        runTest("Single Digit Multiplication", []() {
            return vectorToString(naive_mul({ 9 }, { 9 }));
            }, "81");  // Ожидаемый результат: "81"

            // Тестирование умножения чисел разной длины
        runTest("Multiplication of Different Lengths", []() {
            return vectorToString(naive_mul({ 1, 2, 3 }, { 4 }));
            }, "492");  // Ожидаемый результат: "492"

            // Тестирование умножения больших чисел
        runTest("Large Number Multiplication", []() {
            return vectorToString(naive_mul({ 9, 8, 7, 6, 5 }, { 5, 4, 3, 2, 1 }));
            }, "5365013565");  // Ожидаемый результат: "5185478065"

        runTest("Division by Zero",
            []() -> std::string {
                try {
                    BigInteger fromInt64Positive = BigInteger(1234567890);
                    BigInteger division = fromInt64Positive / BigInteger(0); // Divide by zero
                    return "No exception";
                }
                catch (const std::exception&) {
                    return "Exception caught";
                }
            },
            "Exception caught");

        runTest("Modulo Operation",
            []() {
                BigInteger modulo = BigInteger(100) % BigInteger(30);
                return toString(modulo);
            },
            "10");

        runTest("Compound Assignment += Operator",
            []() {
                BigInteger a = 100;
                a += BigInteger(50);
                return toString(a);
            },
            "150");

        runTest("Compound Assignment -= Operator",
            []() {
                BigInteger a = 150;
                a -= BigInteger(20);
                return toString(a);
            },
            "130");

        runTest("Compound Assignment *= Operator",
            []() {
                BigInteger a = 130;
                a *= BigInteger(2);
                return toString(a);
            },
            "260");

        runTest("Compound Assignment /= Operator",
            []() {
                BigInteger a = 260;
                a /= BigInteger(10);
                return toString(a);
            },
            "26");

        runTest("Compound Assignment %= Operator",
            []() {
                BigInteger a = 26;
                a %= BigInteger(5);
                return toString(a);
            },
            "1");
        runTest("1000000000 and +1000000000",
            []() {
                BigInteger a = BigInteger("1000000000");
                auto b = BigInteger("+1000000000");
                return (a == b) ? "true" : "false";
            },
            "true");

        runTest("substract 123 and 3",
            []() {
                BigInteger a = BigInteger("123");
                auto b = BigInteger("+3");
                return toString(a - b);
            },
            "120");
        runTest("substract 2147483647 and 2147483648",
            []() {
                BigInteger a = BigInteger("2147483647");
                auto b = BigInteger("2147483648");
                return toString(a - b);
            },
            "-1");
        runTest("substract 2147483647 and 0",
            []() {
                BigInteger a = BigInteger("2147483647");
                auto b = BigInteger("0");
                return toString(a - b);
            },
            "2147483647");
        runTest("substract 2147483647 and 2147483647",
            []() {
                BigInteger a = BigInteger("2147483647");
                auto b = BigInteger("2147483647");
                return toString(a - b);
            },
            "0");


        //-123, +0, 0000, -00012
        runTest("min int64",
            []() {
                BigInteger a = BigInteger(std::numeric_limits<int64_t>::min());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;

                return toString(a);
            },
            "-9223372036854775808");
        runTest("min int64 / min int 64",
            []() {
                BigInteger a = BigInteger(std::numeric_limits<int64_t>::min());
                BigInteger b = BigInteger(std::numeric_limits<int64_t>::min());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;

                return toString(a / b);
            },
            "1");
        runTest("max int64 / min int 64",
            []() {
                BigInteger a = BigInteger(std::numeric_limits<int64_t>::max());
                BigInteger b = BigInteger(std::numeric_limits<int64_t>::min());
                //std::cout<<std::numeric_limits<int64_t>::min()<<std::endl;

                return toString(a / b);
            },
            "0");


    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }


    //part 2


    assert(toString((BigInteger(50) + BigInteger(32))) == "82");
    assert(toString((BigInteger(5) + BigInteger(622))) == "627");
    assert(toString((BigInteger("-33") + BigInteger("8"))) == "-25");
    assert(toString((BigInteger("15535") + BigInteger("0"))) == "15535");
    assert(toString((BigInteger("126") + BigInteger("39285"))) == "39411");
    assert(toString((BigInteger("0") + BigInteger("0"))) == "0");
    //assert(BigInteger(5) + 10 == 15);
    //assert(BigInteger("-41") + 40 == -1);
    BigInteger ad1(600);
    ad1 += BigInteger(100);
    assert(toString(ad1) == "700");
    //assert(ad1 == 700);

    //Subtraction
    assert(toString((BigInteger("50") - BigInteger("32"))) == "18");
    assert(toString((BigInteger("50") - BigInteger("60"))) == "-10");
    assert(toString((BigInteger("0") - BigInteger("46"))) == "-46");
    assert(toString((BigInteger("50") - BigInteger("50"))) == "0");
    assert(toString((BigInteger("482847") - BigInteger("89787941"))) == "-89305094");
    assert(toString((BigInteger("6828") - BigInteger("1"))) == "6827");
    assert(toString((BigInteger("100") - BigInteger("50"))) == "50");
    assert(toString((BigInteger("42") - BigInteger("49"))) == "-7");
    //assert((BigInteger("100") - BigInteger("5")) == 95);
    BigInteger sb1 = BigInteger(200);
    sb1 -= BigInteger(40);
    assert(sb1 == BigInteger(160));
    sb1 = sb1 - BigInteger(180);
    assert(toString(sb1) == "-20");
    sb1 -= BigInteger(20);
    assert(sb1 == BigInteger(-40));

    //Multiplication
    assert(toString((BigInteger("4") * BigInteger("12"))) == "48");
    assert(toString((BigInteger("3002") * BigInteger("1"))) == "3002");
    assert(toString((BigInteger("99") * BigInteger("0"))) == "0");
    assert(toString((BigInteger("-5") * BigInteger("5"))) == "-25");
    assert(toString((BigInteger("-33") * BigInteger("-2"))) == "66");
    assert(toString((BigInteger("283") * BigInteger("382871"))) == "108352493");


    //Division
//    assert(BigInteger("25").divide(BigInteger("5")) == 5);
//    assert(BigInteger("48").divide(BigInteger("6")) == 8);
//    assert(BigInteger("100").divide(BigInteger("5")) == 20);
//    BigInteger dv1 = 100;
//    dv1 /= 25;
//    assert(dv1 == 4);
//    dv1 = dv1 / dv1;
//    assert(dv1 == 1);
//    dv1 /= 1;
//    assert(dv1 == 1);
//    dv1 = -5;
//    dv1 /= 5;
//    assert(dv1 == -1);
//    dv1 = 3000;
//    dv1 /= 300;
//    assert(dv1 == 10);
//    dv1 = 25485;
//    dv1 /= 5;
//    assert(dv1 == "5097");

    //Division
    assert(BigInteger("100") / BigInteger("100") == BigInteger(1));
    assert(BigInteger("100") / BigInteger("20") == BigInteger(5));
    assert(BigInteger("100") / BigInteger("5") == BigInteger(20));
    assert(BigInteger("100") / BigInteger("1") == BigInteger(100));
    assert(BigInteger("100") / BigInteger("-1") == BigInteger(-100));
    assert(BigInteger("-100") / BigInteger("1") == BigInteger(-100));
    assert(-BigInteger("-100") / BigInteger("1") == BigInteger(100));

    assert(BigInteger("100000000000000000000000000000000") / BigInteger("100000000000000000000000000000000") ==
        BigInteger(1));
    assert(BigInteger("100000000000000000000000000000000") / BigInteger("10000000000000000000000000000000") ==
        BigInteger(10));


    //Equals
    assert(BigInteger("4") == BigInteger("4"));
    assert(BigInteger("-3") == BigInteger("-3"));
    assert(BigInteger("3") == -BigInteger("-3"));
    assert(BigInteger("0") == BigInteger("0"));
    assert(BigInteger("938283828178273") == BigInteger("938283828178273"));
    assert(BigInteger("-938283828178273") == BigInteger("-938283828178273"));
    assert(BigInteger("938283828178273") == BigInteger("0000938283828178273"));
    assert(BigInteger("00000938283828178273") == BigInteger("938283828178273"));
    assert(BigInteger("-938283828178273") == BigInteger("-00938283828178273"));
    assert(BigInteger("00938283828178273") == BigInteger("0000938283828178273"));

    //Greater than
    assert(BigInteger("5") > BigInteger("2"));
    assert(BigInteger("30") > BigInteger("-40"));
    assert(BigInteger("-5") > BigInteger("-10"));
    assert(BigInteger("0") > BigInteger("-1"));

    //Less than
    assert(BigInteger("10") < BigInteger("20"));
    assert(BigInteger("-5") < BigInteger("0"));
    assert(BigInteger("30") < BigInteger("30000"));

    //Greater than or equal to
    assert(BigInteger("5") >= BigInteger("0"));
    assert(BigInteger("-5") >= BigInteger("-5"));
    assert(BigInteger("-5") >= BigInteger("-10"));
    assert(BigInteger("0") >= BigInteger("0"));
    assert(BigInteger("32") >= BigInteger("-32"));
    assert(BigInteger("2") >= BigInteger("0001"));

    //Less than or equal to
    assert(BigInteger("5") <= BigInteger("10"));
    assert(BigInteger("0") <= BigInteger("0"));
    assert(BigInteger("-5") <= BigInteger("0"));
    assert(BigInteger("30") <= BigInteger("30"));
    assert(BigInteger("400") <= BigInteger("392342"));

    //Index

    BigInteger c(10);
    c = BigInteger(5);
    assert(c == BigInteger(5));
    assert(c == BigInteger("5"));
    c = BigInteger("83833");
    //assert(c == 83833);
    assert(c == BigInteger(83833));
    assert(c == BigInteger("83833"));

    //Equals testing
    BigInteger d(40);
    assert(d == BigInteger("40"));
    assert(d == BigInteger(40));

    const double tolerance = 1e-10;

    // Test sqrt with a positive number
    BigInteger posNum("16");
    std::cout << std::abs(posNum.sqrt() - 4.0) << std::endl;
    assert(std::abs(posNum.sqrt() - 4.0) < tolerance);

    // Test sqrt with zero
    BigInteger zeroNum("0");
    assert(std::abs(zeroNum.sqrt() - 0.0) < std::numeric_limits<double>::epsilon());
    BigInteger num169("169");
    assert(std::abs(num169.sqrt() - 13.0) < std::numeric_limits<double>::epsilon());

    // Test sqrt with a large number
    BigInteger largeNum("12345678901234567890");
    try {
        double result = largeNum.sqrt();
        assert(std::isfinite(result));  // Should be finite if no exception is thrown
    }
    catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "Number is too large");
    }

    // Test sqrt with a negative number


    std::cout << "All sqrt tests passed successfully." << std::endl;

    //% operator
    BigInteger f(169);
    assert(f % BigInteger(13) == BigInteger(0));
    f = BigInteger(2000);
    assert(f % BigInteger(1999) == BigInteger(1));
    runTest("Positive Modulus Test", []() { return toString(BigInteger("50") % BigInteger("7")); }, "1");

    // Negative Numbers
    runTest("Negative Modulus Test", []() { return toString(BigInteger("-50") % BigInteger("7")); }, "-1");
    runTest("Mixed Sign Modulus Test", []() { return toString(BigInteger("50") % BigInteger("-7")); }, "1");
    auto v = std::numeric_limits<int64_t>::max();
    auto MinusvPlusOne = std::numeric_limits<int64_t>::min();
    f = BigInteger((int64_t)v);
    auto fMinus = BigInteger(MinusvPlusOne);
    //assert(f % fMinus == BigInteger(0));

    runTest("max max edgecase modulus", []() {
        auto v = std::numeric_limits<int64_t>::max();
        auto f = BigInteger((int64_t)v);
        return toString(f % f);
        }, "0");
    runTest("max min edgecase modulus", []() {
        auto v = std::numeric_limits<int64_t>::max();
        auto MinusvPlusOne = std::numeric_limits<int64_t>::min();
        auto max = BigInteger((int64_t)v);
        auto min = BigInteger(MinusvPlusOne);
        return toString(max % min);
        }, "9223372036854775807");
    runTest("min min edgecase modulus", []() {
        auto v = std::numeric_limits<int64_t>::max();
        auto MinusvPlusOne = std::numeric_limits<int64_t>::min();
        auto max = BigInteger((int64_t)v);
        auto min = BigInteger(MinusvPlusOne);
        return toString(min % min);
        }, "0");
    runTest("min max edgecase modulus", []() {
        auto v = std::numeric_limits<int64_t>::max();
        auto MinusvPlusOne = std::numeric_limits<int64_t>::min();
        auto max = BigInteger((int64_t)v);
        auto min = BigInteger(MinusvPlusOne);
        return toString(min % max);
        }, "-1");

    std::cout << "BigInteger ran successfully." << std::endl;
    std::cout << "\n BigRational started.\n" << std::endl;


    // Test for Constructor from int64_t
    runTest("Constructor from int64_t",
        []() { return toString(BigRational(5, 2)); },
        "5/2");
    //     printf("max %lld min %lld\n", std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::min());
    runTest("Constructor from int64_t",
        []() { return toString(BigRational(6, 2)); },
        "3");
    runTest("Constructor from int64_t max / max",
        []() {
            return toString(BigRational(std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max()));
        },
        "1");
    runTest("Constructor from int64_t max / min",
        []() {
            return toString(BigRational(std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::min()));
        },
        "-9223372036854775807/9223372036854775808");
    runTest("Constructor from int64_t min / min",
        []() {
            return toString(BigRational(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max()));
        },
        "-9223372036854775808/9223372036854775807");
    runTest("Constructor from int64_t min / min",
        []() {
            return toString(BigRational(std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::min()));
        },
        "1");

    runTest("Constructor from string max / max",
        []() { return toString(BigRational("9223372036854775807", "9223372036854775807")); },
        "1");
    runTest("Constructor from string more than max",
        []() {
            return toString(BigRational("100000000000000000000000000000000", "100000000000000000000000000000000"));
        },
        "1");
    runTest("Constructor from string more than max",
        []() {
            return toString(BigRational("100000000000000000000000000000000", "10000000000000000000000000000000"));
        },
        "10");
    runTest("Constructor from string more than max",
        []() {
            return toString(BigRational("10000000000000000000000000000000", "100000000000000000000000000000000"));
        },
        "1/10");
    // //Test for Constructor from std::string
    runTest("Constructor from std::string",
        []() { return toString(BigRational("5", "2")); },
        "5/2");

    ////// Test for Unary Plus Operator
    runTest("Unary Plus Operator",
        []() { return toString(+BigRational(3, 4)); },
        "3/4");

    runTest("Unary Plus Operator",
        []() { return toString(+BigRational(3, 4)); },
        "3/4");

    //// Test for Unary Minus Operator
    runTest("Unary Minus Operator",
        []() { return toString(-BigRational(3, 4)); },
        "-3/4");

    //// Tests for Addition Operator
    runTest("Addition Operator",
        []() { return toString(BigRational(1, 2) + BigRational(1, 3)); },
        "5/6");

    //// Tests for Subtraction Operator
    runTest("Subtraction Operator",
        []() { return toString(BigRational(1, 2) - BigRational(1, 3)); },
        "1/6");

    //// Tests for Multiplication Operator
    runTest("Multiplication Operator",
        []() { return toString(BigRational(1, 2) * BigRational(2, 3)); },
        "1/3");

    //// Tests for Division Operator
    runTest("Division Operator",
        []() { return toString(BigRational(1, 2) / BigRational(2, 3)); },
        "3/4");

    //// Tests for Equality Operator
    runTest("Equality Operator",
        []() { return toString(BigRational(4, 2) == BigRational(2, 1)); },
        "1");

    //// Tests for Inequality Operator
    runTest("Inequality Operator",
        []() { return toString(BigRational(5, 3) != BigRational(2, 1)); },
        "1");

    //// Tests for Less Than Operator
    runTest("Less Than Operator",
        []() { return toString(BigRational(1, 2) < BigRational(2, 3)); },
        "1");

    //// Tests for Greater Than Operator
    runTest("Greater Than Operator",
        []() { return toString(BigRational(2, 3) > BigRational(1, 2)); },
        "1");

    //// Tests for Less Than or Equal Operator
    runTest("Less Than or Equal Operator",
        []() { return toString(BigRational(1, 2) <= BigRational(2, 3)); },
        "1");

    runTest("Less Than or Equal Operator",
        []() { return toString(BigRational(1, 2) <= BigRational(2, 4)); },
        "1");

    //// Tests for Greater Than or Equal Operator
    runTest("Greater Than or Equal Operator",
        []() { return toString(BigRational(2, 3) >= BigRational(1, 2)); },
        "1");

    //// Compound Assignment Operators Tests
    runTest("Compound Addition Assignment",
        []() {
            BigRational a(1, 2);
            a += BigRational(1, 3);
            return toString(a);
        },
        "5/6");

    runTest("Compound Subtraction Assignment",
        []() {
            BigRational a(1, 2);
            a -= BigRational(1, 3);
            return toString(a);
        },
        "1/6");
    //
    runTest("Compound Multiplication Assignment",
        []() {
            BigRational a(1, 2);
            a *= BigRational(2, 3);
            return toString(a);
        },
        "1/3");

    runTest("Compound Division Assignment",
        []() {
            BigRational a(1, 2);
            a /= BigRational(2, 3);
            return toString(a);
        },
        "3/4");

    //// More Constructor Tests
    runTest("Zero Denominator Constructor",
        []() {
            try {
                return toString(BigRational(1, 0));
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "invalid argument - zero denominator.");

    runTest("Negative Denominator Constructor",
        []() { return toString(BigRational(1, -2)); },
        "-1/2");

    runTest("Both Negative Constructor",
        []() { return toString(BigRational(-1, -2)); },
        "1/2");

    runTest("String Constructor with Zero",
        []() { return toString(BigRational("0", "1")); },
        "0");

    //    runTest("String Constructor with Negative",
    //            []() { return toString(BigRational("-1", "2")); },
    //            "-1/2");

    //// Tests for Invalid String Constructor
    runTest("Invalid String Constructor",
        []() {
            try {
                return toString(BigRational("a", "b"));
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "received bad formatted string");

    //// Tests for Output Stream Operator
    runTest("Output Stream Operator",
        []() {
            std::ostringstream os;
            os << BigRational(3, 4);
            return os.str();
        },
        "3/4");

    //// Special Cases Tests
    runTest("Zero Numerator",
        []() { return toString(BigRational(0, 1)); },
        "0");

    //// Tests for Sqrt Function
    runTest("Sqrt Function Positive",
        []() {
            try {
                return std::to_string(BigRational(4, 1).sqrt());
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "2.000000");

    runTest("Sqrt Function Negative",
        []() {
            try {
                return std::to_string(BigRational(-4, 1).sqrt());
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "invalid argument - negative number.");

    // Test for iSqrt Function (If SUPPORT_ISQRT is enabled)
#if SUPPORT_ISQRT == 1
    runTest("iSqrt Function Positive",
        []() {
            try {
                return toString(BigRational(16, 1).isqrt());
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "4");
#endif

    //// More Tests for Arithmetic Operators
    runTest("Addition with Zero",
        []() { return toString(BigRational(1, 2) + BigRational(0, 1)); },
        "1/2");

    runTest("Subtraction Resulting Zero",
        []() { return toString(BigRational(1, 2) - BigRational(1, 2)); },
        "0");

    runTest("Multiplication with Zero",
        []() { return toString(BigRational(1, 2) * BigRational(0, 1)); },
        "0");

    runTest("Division by One",
        []() { return toString(BigRational(1, 2) / BigRational(1, 1)); },
        "1/2");

    // Edge Cases Tests
    runTest("Large Number Addition",
        []() { return toString(BigRational("99999999", "1") + BigRational("1", "1")); },
        "100000000");

    runTest("Large Number Subtraction",
        []() { return toString(BigRational("100000000", "1") - BigRational("1", "1")); },
        "99999999");

    runTest("Large Number Multiplication",
        []() { return toString(BigRational("10000", "1") * BigRational("10000", "1")); },
        "100000000");

    runTest("Large Number Division",
        []() { return toString(BigRational("100000000", "1") / BigRational("10000", "1")); },
        "10000");

    // More Edge Cases Tests - todo THIS test
    runTest("Addition of Opposite Signs",
        []() { return toString(BigRational("-1", "2") + BigRational("1", "2")); },
        "0");

    runTest("Subtraction of Similar Signs",
        []() { return toString(BigRational("-1", "2") - BigRational("-1", "2")); },
        "0");

    runTest("Multiplication of Opposite Signs",
        []() { return toString(BigRational("-1", "2") * BigRational("1", "2")); },
        "-1/4");

    runTest("Division of Opposite Signs",
        []() { return toString(BigRational("1", "2") / BigRational("1", "2")); },
        "1");

    //Completing 40 Tests
    runTest("String Constructor with Leading Zeroes",
        []() { return toString(BigRational("0005", "0025")); },
        "1/5");

    runTest("Zero Denominator in String Constructor",
        []() {
            try {
                return toString(BigRational("1", "0000"));
            }
            catch (std::exception& e) {
                return std::string(e.what());
            }
        },
        "invalid argument - zero denominator.");


    runTest("Add and assign 1", []() {
        BigInteger num1("85241964353410"), num2("617705612502427"), num3;
        num3 += num1;
        return toString(num3);
        }, "85241964353410");
    runTest("Add and assign 2", []() {
        BigInteger num1("85241964353410"), num2("617705612502427"), num3;
        num3 += num1;
        num3 += num2;
        return toString(num3);
        }, "702947576855837");
    // ... remaining Add and assign tests ...

    // Subtract and assign tests
    runTest("Subtract and assign 1", []() {
        BigInteger num1("169523540030343"), num2("849991085752380"), num3;
        num3 -= num1;
        return toString(num3);
        }, "-169523540030343");
    // ... remaining Subtract and assign tests ...

    // Multiply and assign tests
    runTest("Multiply and assign 1", []() {
        BigInteger num1("169523540030343"), num2("849991085752380"), num3 = 1;
        num3 *= num1;
        return toString(num3);
        }, "169523540030343");
    // ... remaining Multiply and assign tests ...

    // Divide and assign tests
    runTest("Divide and assign 1", []() {
        BigInteger num1("1695235400303"), num2("-14409349785097830054018446630"), num3(
            "99609344092229394637577667754049630552571016118837570372569130682");
        num3 /= num1;
        return toString(num3);
        }, "58758414362055909808086078831411583704925762083687648");
    // ... remaining Divide and assign tests ...

    // Modulo and assign tests
    runTest("Modulo and assign 1", []() {
        BigInteger num1("82548281880706855287"), num2("-3093004007127403784763865131496495744552"), num3(
            "28759936859007420850030703143893813386234625466713870488148000919");
        num3 %= num2;
        return toString(num3);
        }, "2998899812449910677529571999817489505831");
    // ... remaining Modulo and assign tests ...
    assert(BigInteger("00012") == BigInteger("+00012"));
    assert(BigInteger("00012") == -BigInteger("-00012"));
    assert(BigInteger("+00012") == -BigInteger("-00012"));
    assert("123" == ((BigInteger(123) + BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) + BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) + BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) + BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) - BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) - BigInteger(0)).toString()));
    assert("123" == ((BigInteger(123) - BigInteger(0)).toString()));
    assert("-123" == ((BigInteger(0) - BigInteger(123)).toString()));
    assert("0" == BigIntegerToString(BigInteger(0)));
    assert("0" == BigIntegerToString(BigInteger(0)));
    assert("0" == BigIntegerToString(BigInteger(0)));
    assert("1" == BigIntegerToString(BigInteger(1)));
    assert("1" == BigIntegerToString(BigInteger(1)));
    assert("1" == BigIntegerToString(BigInteger(1)));
    assert("-1" == BigIntegerToString(BigInteger(-1)));
    assert("-1" == BigIntegerToString(BigInteger(-1)));
    assert("-1" == BigIntegerToString(BigInteger(-1)));
    assert("123456789" == BigIntegerToString(BigInteger(123456789)));
    assert("123456789" == BigIntegerToString(BigInteger(123456789)));
    assert("123456789" == BigIntegerToString(BigInteger(123456789)));
    assert("-123456789" == BigIntegerToString(BigInteger(-123456789)));
    assert("-123456789" == BigIntegerToString(BigInteger(-123456789)));
    assert("-123456789" == BigIntegerToString(BigInteger(-123456789)));
    assert("2147483647" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::max())));
    assert("2147483647" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::max())));
    assert("2147483647" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::max())));
    assert("-2147483648" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::min())));
    assert("-2147483648" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::min())));
    assert("-2147483648" == BigIntegerToString(BigInteger(std::numeric_limits<int32_t>::min())));
    assert("9223372036854775807" == BigIntegerToString(BigInteger(std::numeric_limits<int64_t>::max())));
    assert("9223372036854775807" == BigIntegerToString(BigInteger(std::numeric_limits<int64_t>::max())));
    assert("9223372036854775807" == BigIntegerToString(BigInteger(std::numeric_limits<int64_t>::max())));
    assert("-9223372036854775808" == BigIntegerToString(BigInteger(std::numeric_limits<int64_t>::min())));
    assert("0" == BigInteger("0").toString());
    assert("0" == BigInteger("0").toString());
    assert("0" == BigInteger("0").toString());
    assert("0" == BigInteger("-0").toString());
    assert("0" == BigInteger("-0").toString());
    assert("0" == BigInteger("-0").toString());
    assert("1" == BigInteger("1").toString());
    assert("1" == BigInteger("1").toString());
    assert("1" == BigInteger("1").toString());
    assert("-1" == BigInteger("-1").toString());
    assert("-1" == BigInteger("-1").toString());
    assert("-1" == BigInteger("-1").toString());
    assert("1000000000" == BigInteger("1000000000").toString());
    assert("1000000000" == BigInteger("1000000000").toString());
    assert("1000000000" == BigInteger("1000000000").toString());
    assert("-1000000000" == BigInteger("-1000000000").toString());
    assert("-1000000000" == BigInteger("-1000000000").toString());
    assert("-1000000000" == BigInteger("-1000000000").toString());
    assert("0" != BigInteger("1").toString());
    assert("0" != BigInteger("1").toString());
    assert("0" != BigInteger("1").toString());
    assert("0" != BigInteger("-1").toString());
    assert("0" != BigInteger("-1").toString());
    assert("0" != BigInteger("-1").toString());
    assert("1" != BigInteger("2").toString());
    assert("1" != BigInteger("2").toString());
    assert("1" != BigInteger("2").toString());
    assert("-1" != BigInteger("1").toString());
    assert("-1" != BigInteger("1").toString());
    assert("-1" != BigInteger("1").toString());
    assert("1000000000" != BigInteger("1000000001").toString());
    assert("1000000000" != BigInteger("1000000001").toString());
    assert("1000000000" != BigInteger("1000000001").toString());
    assert("-1000000000" != BigInteger("-1000000001").toString());
    assert("-1000000000" != BigInteger("-1000000001").toString());
    assert("-1000000000" != BigInteger("-1000000001").toString());
    assert(toString(BigInteger(std::numeric_limits<int64_t>::min())) == toString(BigInteger("-9223372036854775808")));
    assert(BigInteger("0") == BigInteger(0));
    assert("-1" == BigInteger("-1").toString());
    //assert(BigInteger("00012") == BigInteger("+00012") == -BigInteger("-00012"));
    //unary minus
    assert((-BigInteger(0)).toString() == "0");
    std::cout << toString(-BigRational(0, 2)) << std::endl;
    assert(toString(-BigRational(0, 2)) == "0");
    runTest("Constructor from std::string Positive invalid 1",
        []() {
            try {
                BigInteger("1    ");
                return "good";
            }
            catch (const std::exception&) {
                return "ex";
            }
        },
        "ex");
    runTest("Constructor from std::string Positive invalid 1",
        []() {
            try {
                BigInteger("  1    ");
                return "good";
            }
            catch (const std::exception&) {
                return "ex";
            }
        },
        "ex");

    assert(toString(-BigRational(0, -2)) == "0");
    assert(toString(-BigRational(1, -2)) == "1/2");
    assert(toString(-BigRational(1, std::numeric_limits<int64_t>::min())) == "1/9223372036854775808");


    return 0;
}

std::string BigIntegerToString(BigInteger integer) {
    return toString(integer);
}
