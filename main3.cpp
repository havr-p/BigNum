#include <iostream>
#include <sstream>
#include <cassert>
#include "BigNum.h"
#include <stdexcept>
#include <functional>


std::string toString(const BigInteger& bigInt) {
    std::ostringstream oss;
    oss << bigInt;
    return oss.str();
}


std::string vectorToString(const std::vector<int>& v) {
    std::string result;
    for (auto it = v.begin(); it != v.end(); ++it) {  // Переворачиваем вектор, так как наибольший разряд должен быть впереди
        result += std::to_string(*it);
    }
    return result;
}


void runTest(const std::string& testName, const std::function<std::string()>& testFunction, const std::string& expectedOutcome) {
    try {
        std::string outcome = testFunction();
        if (outcome != expectedOutcome) {
            throw std::runtime_error("Test failed. Expected: " + expectedOutcome + ", but got: " + outcome);
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

//std::vector<int> multiply(std::string& t, std::string& b) {
//	int tsize = static_cast<int>(t.size());
//	int bsize = static_cast<int>(b.size());
//
//	std::vector<int> pos(static_cast<int>(tsize + bsize), 0);
//	for (int i = tsize - 1; i >= 0; i--) {
//		for (int j = bsize - 1; j >= 0; j--) {
//			int mul = (t[i] - '0') * (b[j] - '0');
//			int p1 = i + j, p2 = i + j + 1;
//			int sum = mul + pos[p2];
//			pos[p1] += sum / 10;
//			pos[p2] = sum % 10;
//		}
//	}
//	std::vector<int> res;
//	for ( int p : pos) if (!(res.size() == 0 && p == 0)) res.push_back(p);
//
//	std::reverse(res.begin(), res.end());
//	return res;
//}


int main() {
    try {
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


    //Equals
    assert(BigInteger("4") == BigInteger("4"));
    assert(BigInteger("-3") == BigInteger("-3"));
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
    BigInteger negNum("-9");
    

    std::cout << "All sqrt tests passed successfully." << std::endl;

    std::cout << "BigInteger ran successfully." << std::endl;

    return 0;
}