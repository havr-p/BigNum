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
//		/*runTest("Default Constructor",
//			[]() { return toString(BigInteger()); },
//			"+0");*/
//		const std::function
//
//		/*runTest("Constructor from int64_t Positive",
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
//			"-1234567890");*/
//
//
//	
//	}
//	catch (const std::exception& e) {
//		std::cerr << "Test failed: " << e.what() << std::endl;
//		return 1;
//	}
//
//	return 0;
//}
