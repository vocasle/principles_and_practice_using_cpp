// This file contains solution for exercise 5 of chapter 8

#include "problem_3.h"
#include "problem_5.h"

int main()
{
	std::vector<int32_t> fib_seq;
	fibonacci(0, 1, fib_seq, 5);
	const auto& cfib_seq = fib_seq;
	auto reversed = reverse(cfib_seq);
	print("reversed", reversed);
	print("original", fib_seq);

	reverse(fib_seq);
	print("reversed", fib_seq);
	print("original", fib_seq);
	return 0;
}