#include "problem_2.h"
#include "problem_3.h"

int main()
{
	std::vector<int32_t> fib_seq;
	fibonacci(0, 1, fib_seq, 100);
	print("fib:", fib_seq);
	return 0;
}