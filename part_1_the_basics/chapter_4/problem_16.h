//
// Created by Nikita Elsakov on 09.03.2020.
//

#ifndef PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_16_H
#define PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_16_H
#include <map>
#include <vector>
#include <iostream>

template<typename T>
T findMode(const std::__1::vector<T>& v)
{
	T mode;
	auto numOfRepeats = 0;
	std::__1::map<T, int> occurrences;
	for (auto&& el : v)
		occurrences[el]++;
	for (auto&& occurrence : occurrences)
	{
		if (numOfRepeats < occurrence.second)
		{
			numOfRepeats = occurrence.second;
			mode = occurrence.first;
		}
	}
	return mode;
}
#endif //PRINCIPLES_AND_PRACTICE_USING_CPP_PART_1_THE_BASICS_CHAP_3_PROBL_16_H
