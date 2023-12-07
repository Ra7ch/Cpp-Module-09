/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:50:16 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 00:19:11 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void printData (PmergeMe& P, PmergeMe& D) {
	std::vector<int> vec;
	std::deque<int> deq;

	vec = P.getUnsortedVector();
	std::cout << "Before: ";
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	deq = D.getSortedDeque();
	std::cout << "After:  ";
	for (std::deque<int>::iterator it = deq.begin(); it != deq.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	// Print Time

	std::cout << "Time to process a range of "
	          << vec.size()
	          << " elements with std::vector : "
			  << std::fixed
			  << std::setprecision(4)
	          << P.getVectorTime()
	          << " us" << std::endl;

	std::cout << "Time to process a range of "
	          << deq.size()
	          << " elements with std::deque : "
			  << std::fixed
			  << std::setprecision(4)
	          << D.getDequeTime()
	          << " us" << std::endl;
}

int main (int argc, char **argv) {
	std::vector<int> vec;
	std::deque <int> deq;

	try {
		if (argc < 2)
			throw std::runtime_error ("Not enough arguments");
		for (int i = 1; i < argc; i += 1)
			if (std::string(argv[i]).find_first_not_of("0123456789 ") != std::string::npos)
				throw std::runtime_error ("Error: Unvalid Element");
		std::vector<unsigned int>temp;
		for (int i = 1; i < argc; i += 1)
			temp.push_back(atoi(argv[i]));

		std::vector<unsigned int>::iterator itr;
		std::vector<unsigned int>::iterator itr2;
		for (itr = temp.begin(); itr != temp.end(); itr++)
		{
			for (itr2 = itr + 1; itr2 != temp.end(); itr2++)
				if (*itr2 == *itr)
					throw std::runtime_error ("Error: Repeated Number");
		}
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		return 0;
	}
	for (int i = 1; argv[i]; i++)
		vec.push_back(atoi(argv[i]));
	for (int i = 1; argv[i]; i++)
		deq.push_back(atoi(argv[i]));
	
	PmergeMe P (vec);
	PmergeMe D (deq);
	printData (P, D);
}