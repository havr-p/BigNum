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
	for (auto it = v.rbegin(); it != v.rend(); ++it) {  // Переворачиваем вектор, так как наибольший разряд должен быть впереди
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
		std::cout << "Test Passed: " << testName << std::endl;
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

		//runTest("Test 1", []() {
		//	return vectorToString(naive_mul({ 1, 2, 3 }, { 4, 5, 6 }));
		//	}, "56088");  // Ожидаемый результат: "56088"
		//runTest("Multiplication with Zero", []() {
		//	return vectorToString(naive_mul({ 0 }, { 1, 2, 3, 4, 5 }));
		//	}, "0");  // Ожидаемый результат: "0"

		//	// Тестирование умножения однозначных чисел
		//runTest("Single Digit Multiplication", []() {
		//	return vectorToString(naive_mul({ 9 }, { 9 }));
		//	}, "81");  // Ожидаемый результат: "81"

		//	// Тестирование умножения чисел разной длины
		//runTest("Multiplication of Different Lengths", []() {
		//	return vectorToString(naive_mul({ 1, 2, 3 }, { 4 }));
		//	}, "492");  // Ожидаемый результат: "492"

		//	// Тестирование умножения больших чисел
		//runTest("Large Number Multiplication", []() {
		//	return vectorToString(naive_mul({ 9, 8, 7, 6, 5 }, { 5, 4, 3, 2, 1 }));
		//	}, "5185478065");  // Ожидаемый результат: "5185478065"

		//runTest("Division by Zero",
		//	[]() -> std::string {
		//		try {
		//			BigInteger fromInt64Positive = BigInteger(1234567890);
		//			BigInteger division = fromInt64Positive / BigInteger(0); // Divide by zero
		//			return "No exception";
		//		}
		//		catch (const std::exception&) {
		//			return "Exception caught";
		//		}
		//	},
		//	"Exception caught");

		//runTest("Modulo Operation",
		//	[]() {
		//		BigInteger modulo = BigInteger(100) % BigInteger(30);
		//		return toString(modulo);
		//	},
		//	"10");

		//runTest("Compound Assignment += Operator",
		//	[]() {
		//		BigInteger a = 100;
		//		a += BigInteger(50);
		//		return toString(a);
		//	},
		//	"150");

		//runTest("Compound Assignment -= Operator",
		//	[]() {
		//		BigInteger a = 150;
		//		a -= BigInteger(20);
		//		return toString(a);
		//	},
		//	"130");

		//runTest("Compound Assignment *= Operator",
		//	[]() {
		//		BigInteger a = 130;
		//		a *= BigInteger(2);
		//		return toString(a);
		//	},
		//	"260");

		//runTest("Compound Assignment /= Operator",
		//	[]() {
		//		BigInteger a = 260;
		//		a /= BigInteger(10);
		//		return toString(a);
		//	},
		//	"26");

		//runTest("Compound Assignment %= Operator",
		//	[]() {
		//		BigInteger a = 26;
		//		a %= BigInteger(5);
		//		return toString(a);
		//	},
		//	"1");



	
	}
	catch (const std::exception& e) {
		std::cerr << "Test failed: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}