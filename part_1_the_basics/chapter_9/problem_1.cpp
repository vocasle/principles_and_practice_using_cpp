#include "name_pairs.h"

int main()
{
	Name_pairs np{};
	np.read_names();
	np.read_ages();
	np.print();
	np.sort();
	np.print();
	return 0;
}