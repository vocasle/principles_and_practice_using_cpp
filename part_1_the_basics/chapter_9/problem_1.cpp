#include "name_pairs.h"
#include <iostream>

int main()
{
	Name_pairs np{};
	np.read_names();
	np.read_ages();
	auto unsorted{ np };
	std::cout << np << '\n';
	np.sort();
	std::cout << np << '\n';
	std::cout << "Unsorted equals sorted: "
		<< (np == unsorted ? "yes" : "no")
		<< "\nUnsorted not equals sorted: "
		<< (np != unsorted ? "yes" : "no")
		<< '\n';
	return 0;
}