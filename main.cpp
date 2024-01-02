//#include <iostream>
//#include <sstream>
//#include <cassert>
//#include "BigNum.h"  
//#include <stdexcept>
//#include <functional>
//
//
//std::string toString(const BigInteger& bigInt) {
//	std::ostringstream oss;
//	oss << bigInt;
//	return oss.str();
//}
//
//void runTest(const std::string& testName,
//	const std::function<std::string()>& testFunction,
//	const std::string& expectedOutcome) {
//	try {
//		std::string outcome = testFunction();
//		if (outcome != expectedOutcome) {
//			throw std::runtime_error("Test failed. Expected: " + expectedOutcome + ", but got: " + outcome);
//		}
//		std::cout << "Test Passed: " << testName << std::endl;
//	}
//	catch (const std::exception& e) {
//		std::cout << "Test Failed: " << testName << " - Exception: " << e.what() << std::endl;
//	}
//	catch (...) {
//		std::cout << "Test Failed: " << testName << " - Unknown Error" << std::endl;
//	}
//}
//
//int main() {
//	try {
//		runTest("Default Constructor",
//			[]() { return toString(BigInteger()); },
//			"+0");
//
//		runTest("Constructor from int64_t Positive",
//			[]() { return toString(BigInteger(1234567890)); },
//			"+1234567890");
//
//		runTest("Constructor from int64_t Zero",
//			[]() { return toString(BigInteger(0)); },
//			"+0");
//
//		runTest("Constructor from int64_t Negative",
//			[]() { return toString(BigInteger(-1234567890)); },
//			"-1234567890");
//
//		runTest("Constructor from std::string Positive",
//			[]() { return toString(BigInteger("+1234567890")); },
//			"+1234567890");
//
//		runTest("Constructor from std::string Negative",
//			[]() { return toString(BigInteger("-1234567890")); },
//			"-1234567890");
//
//
//		//runTest("Constructor from std::string Leading Zeroes",
//		//	[]() { return toString(BigInteger("000012345")); },
//		//	"+12345");
//
//		//runTest("Constructor from std::string Only Zeroes",
//		//	[]() { return toString(BigInteger("0000")); },
//		//	"+0");
//
//		//runTest("Constructor from std::string - Empty String", []() {
//		//	try {
//		//		BigInteger fromStringEmpty("");
//		//		return "No exception thrown";
//		//	}
//		//	catch (const std::exception&) {
//		//		return "Expected exception thrown";
//		//	}
//		//	}, "Expected exception thrown");
//
//		//runTest("Constructor from std::string - String with Whitespace", []() {
//		//	try {
//		//		BigInteger fromStringWhitespace(" 123 ");
//		//		return "No exception thrown";
//		//	}
//		//	catch (const std::exception&) {
//		//		return "Expected exception thrown";
//		//	}
//		//	}, "Expected exception thrown");
//
//		//runTest("Constructor from std::string - Non-Numeric String", []() {
//		//	try {
//		//		BigInteger fromStringNonNumeric("abc");
//		//		return "No exception thrown";
//		//	}
//		//	catch (const std::exception&) {
//		//		return "Expected exception thrown";
//		//	}
//		//	}, "Expected exception thrown");
//		//runTest("Copy Constructor", []() {
//		//	BigInteger original(12345);
//		//	BigInteger copy = original;  // Using the copy constructor
//		//	if (toString(copy) != toString(original))
//		//		return "Copy does not match original";
//
//		//	original = BigInteger(54321); // Changing the original
//		//	if (toString(copy) == toString(original))
//		//		return "Copy matches original after modification";
//
//		//	return "Success";
//		//	}, "Success");
//
//		//runTest("Copy Assignment Operator", []() {
//		//	BigInteger original(-98765);
//		//	BigInteger copy;
//		//	copy = original;  // Using the copy assignment operator
//		//	if (toString(copy) != toString(original))
//		//		return "Copy does not match original";
//
//		//	original = BigInteger(-56789); // Changing the original
//		//	if (toString(copy) == toString(original))
//		//		return "Copy matches original after modification";
//
//		//	return "Success";
//		//	}, "Success");
//
//
//		////    // Unary + Operator
//		////    BigInteger unaryPlus = +fromInt64Positive;
//		////    assert(toString(unaryPlus) == "1234567890");
//
//		////    // Unary - Operator
//		////    BigInteger unaryMinus = -fromInt64Positive;
//		////    assert(toString(unaryMinus) == "-1234567890");
//
//		//	// Binary Arithmetic Operators (+, -, *, /, %)
//
//		//BigInteger fromInt64Positive = BigInteger(-1234567890);
//		//BigInteger fromInt64Negative = BigInteger(-1234567890);
//		//BigInteger sum = fromInt64Positive + fromInt64Negative;
//		//assert(toString(sum) == "0");
//
//		//BigInteger difference = fromInt64Positive - fromInt64Negative;
//		//assert(toString(difference) == "2469135780");
//
//		//BigInteger product = fromInt64Positive * fromInt64Negative;
//		//assert(toString(product) == "-1524157875019052100");
//
//		//try {
//		//	BigInteger division = fromInt64Positive / BigInteger(0); // Divide by zero
//		//	assert(false);  // Should not reach here
//		//}
//		//catch (const std::exception&) {
//		//	// Expected exception
//		//}
//
//		//BigInteger modulo = BigInteger(100) % BigInteger(30);
//		//assert(toString(modulo) == "10");
//
//		////    // Compound Assignment Operators (+=, -=, *=, /=, %=)
//		////    BigInteger a = 100;
//		////    a += BigInteger(50);
//		////    assert(toString(a) == "150");
//
//		////    a -= BigInteger(20);
//		////    assert(toString(a) == "130");
//
//		////    a *= BigInteger(2);
//		////    assert(toString(a) == "260");
//
//		////    a /= BigInteger(10);
//		////    assert(toString(a) == "26");
//
//		////    a %= BigInteger(5);
//		////    assert(toString(a) == "1");
//
//		////    // Additional tests for multiplication algorithm, division, etc. can be added here
//
//		//   // std::cout << "All tests passed successfully." << std::endl;
//	}
//	catch (const std::exception& e) {
//		std::cerr << "Test failed: " << e.what() << std::endl;
//		return 1;
//	}
//
//	return 0;
//}
