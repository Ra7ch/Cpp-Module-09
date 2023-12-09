/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:50:18 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/09 07:14:39 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe () {}
PmergeMe::PmergeMe (std::vector<int>& V, std::deque<int>& L) : unsortedVector(V), unsortedDeque(L) {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator= (const PmergeMe& other) {
	if (this != &other) {
		unsortedVector = other.unsortedVector;
		sortedVector = other.sortedVector;
		unsortedDeque = other.unsortedDeque;
		sortedDeque = other.sortedDeque;
		dequeTime = other.dequeTime;
		vectorTime = other.vectorTime;
	}
	return *this;
}


PmergeMe::PmergeMe (std::vector<int>& V) : unsortedVector(V) {
	sortedVector = unsortedVector;
	clock_t start = clock();
	sortVectorFJ(sortedVector);
	clock_t end = clock();
	vectorTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

PmergeMe::PmergeMe (std::deque<int>& D) : unsortedDeque(D) {
	sortedDeque = unsortedDeque;
	std::clock_t start = std::clock();
	sortDequeFJ(sortedDeque);
	std::clock_t end = std::clock();
	dequeTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}


void PmergeMe::sortVector(std::vector<int>& vector) {
	if (vector.size() < 2)
		return ;
	size_t mid = vector.size() / 2;
	std::vector<int> left;
	std::vector<int> right;

	for (size_t i = 0; i < mid; i++) {
		left.push_back(vector[i]);
	}
	for (size_t i = mid; i < vector.size(); i++) {
		right.push_back(vector[i]);
	}
	PmergeMe::sortVector(left);
	PmergeMe::sortVector(right);

	PmergeMe::mergeVector(vector, left, right, mid, vector.size() - mid);
}

void PmergeMe::mergeVector (std::vector<int>& vector, std::vector<int>& left, std::vector<int>& right, int leftBoundary, int rightBoundary) {
	int leftIndex = 0;
	int rightIndex = 0;
	int vectorIndex = 0;

	while (leftIndex < leftBoundary && rightIndex < rightBoundary) {
		if (left[leftIndex] <= right[rightIndex])
			vector[vectorIndex++] = left[leftIndex++];
		else
			vector[vectorIndex++] = right[rightIndex++];
	}
	while (leftIndex < leftBoundary)
		vector[vectorIndex++] = left[leftIndex++];
	while (rightIndex < rightBoundary)
		vector[vectorIndex++] = right[rightIndex++];
}

// sorting with deque .
void PmergeMe::sortDeque(std::deque<int>& deque) {
	if (deque.size() < 2)
		return;

	size_t mid = deque.size() / 2;
	std::deque<int> left;
	std::deque<int> right;

	for (size_t i = 0; i < mid; i++) {
		left.push_back(deque[i]);
	}
	for (size_t i = mid; i < deque.size(); i++) {
		right.push_back(deque[i]);
	}
	PmergeMe::sortDeque(left);
	PmergeMe::sortDeque(right);

	PmergeMe::mergeDeque(deque, left, right, mid, deque.size() - mid);
}

void PmergeMe::mergeDeque(std::deque<int>& deque, std::deque<int>& left, std::deque<int>& right, int leftBoundary, int rightBoundary) {
	int leftIndex = 0;
	int rightIndex = 0;
	int dequeIndex = 0;

	while (leftIndex < leftBoundary && rightIndex < rightBoundary) {
		if (left[leftIndex] <= right[rightIndex]) {
			deque[dequeIndex++] = left[leftIndex++];
		} else {
			deque[dequeIndex++] = right[rightIndex++];
		}
	}
	while (leftIndex < leftBoundary) {
		deque[dequeIndex++] = left[leftIndex++];
	}
	while (rightIndex < rightBoundary) {
		deque[dequeIndex++] = right[rightIndex++];
	}
}

// Sorting with Ford-Johnson algorithm for std::vector
void PmergeMe::sortVectorFJ(std::vector<int> &vector) {
	bool odd = false;
	if (vector.size() < 2) {
		return ;
	}

	// 1. Grouping and Pairwise comparison
	size_t mid = vector.size() / 2;
	// Separate the last element if odd
	if (vector.size() % 2 != 0) {
		mid++;
	}

	// Group and compare elements in pairs
	for (size_t i = 0; i < vector.size() - 1; i += 2) {
		if (vector[i] > vector[i + 1]) {
			std::swap(vector[i], vector[i + 1]);
		}
	}
	
	// Vector for storing paired elements
	std::vector<std::pair<int, int> > pairs;

	// 1. Pairwise comparison
	for (size_t i = 0; i < vector.size(); i += 2) {
		if (i < vector.size() - 1) {
			// Create a pair with the two elements
			std::pair <int, int > p(vector[i + 1], vector[i]);
			pairs.push_back(p);
		} else {
			// If odd number of elements, add the last element as a pair with itself
			odd = true;
			std::pair <int, int > p(vector[i], vector[i]);
			pairs.push_back(p);
		}
	}
  

	// 2. Split into larger and smaller elements.
	std::vector<int > Larg;
	std::vector<int> Small;
	for (size_t i = 0; i < pairs.size(); i++) {
		Larg.push_back(pairs[i].first);
		Small.push_back(pairs[i].second);
	}


	// 2. Recursively sort larger elements
	PmergeMe::sortVectorFJ(Larg);

	// 4. Insert the unpaired element and sort remaining elements
	if (odd == true) {
		Small.pop_back();
	}
/////////////////////////////////////
	// insert the element paired with the smalles of Larg
	for (size_t i = 0; i < pairs.size() - 1; i++)
	{
		if (pairs[i].first == Larg[0]) {
			Larg.insert (Larg.begin(), Small[i]);
			Small.erase (Small.begin() + i);
			break ;
		}
	}
//////////////////////////////////////
	// 5. Merge the sorted Larg elements with the Small elements
	// using insertion sort with binary search for efficiency
	for (size_t i = 0; i < Small.size(); i++) {
		// Perform binary search to find insertion position
		int left = 0;
		int right = Larg.size() - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (Small[i] < Larg[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		// Insert element at the found position
		Larg.insert(Larg.begin() + left, Small[i]);
	}
	vector = Larg;
}

// Sorting with Ford-Johnson algorithm for std::deque
void PmergeMe::sortDequeFJ(std::deque<int> &deque) {
	bool odd = false;
	if (deque.size() < 2) {
		return ;
	}

	// 1. Grouping and Pairwise comparison
	size_t mid = deque.size() / 2;
	// Separate the last element if odd
	if (deque.size() % 2 != 0) {
		mid++;
	}

	// Group and compare elements in pairs
	for (size_t i = 0; i < deque.size() - 1; i += 2) {
		if (deque[i] > deque[i + 1]) {
			std::swap(deque[i], deque[i + 1]);
		}
	}
	
	// deque for storing paired elements
	std::deque<std::pair<int, int> > pairs;

	// 1. Pairwise comparison
	for (size_t i = 0; i < deque.size(); i += 2) {
		if (i < deque.size() - 1) {
			// Create a pair with the two elements
			std::pair <int, int > p(deque[i + 1], deque[i]);
			pairs.push_back(p);
		} else {
			// If odd number of elements, add the last element as a pair with itself
			odd = true;
			std::pair <int, int > p(deque[i], deque[i]);
			pairs.push_back(p);
		}
	}
  

	// 2. Split into larger and smaller elements.
	std::deque<int > Larg;
	std::deque<int> Small;
	for (size_t i = 0; i < pairs.size(); i++) {
		Larg.push_back(pairs[i].first);
		Small.push_back(pairs[i].second);
	}


	// 2. Recursively sort larger elements
	PmergeMe::sortDequeFJ(Larg);

	// 4. Insert the unpaired element and sort remaining elements
	if (odd == true) {
		Small.pop_back();
	}
/////////////////////////////////////
	// insert the element paired with the smalles of Larg
	for (size_t i = 0; i < pairs.size() - 1; i++)
	{
		if (pairs[i].first == Larg[0]) {
			Larg.insert (Larg.begin(), Small[i]);
			Small.erase (Small.begin() + i);
			break ;
		}
	}
//////////////////////////////////////
	// 5. Merge the sorted Larg elements with the Small elements
	// using insertion sort with binary search for efficiency
	for (size_t i = 0; i < Small.size(); i++) {
		// Perform binary search to find insertion position
		int left = 0;
		int right = Larg.size() - 1;
		while (left <= right) {
			int mid = (left + right) / 2;
			if (Small[i] < Larg[mid]) {
				right = mid - 1;
			} else {
				left = mid + 1;
			}
		}
		// Insert element at the found position
		Larg.insert(Larg.begin() + left, Small[i]);
	}
	deque = Larg;
}


// Geters.
std::vector<int> PmergeMe::getUnsortedVector () const {
	return (unsortedVector);
}
std::vector<int> PmergeMe::getSortedVector () const {
	return (sortedVector);
}
std::deque<int> PmergeMe::getUnsortedDeque () const {
	return (unsortedDeque);
}
std::deque<int> PmergeMe::getSortedDeque () const {
	return (sortedDeque);
}
double PmergeMe::getVectorTime() const {
	return (vectorTime);
}
double PmergeMe::getDequeTime() const {
	return (dequeTime);
}

PmergeMe::~PmergeMe () {}



///////////////////////////////////////////////////////////////////////
// std::vector <std::pair<int, int> > PmergeMe::getSortedVectorPair () const { return sortedVectorPair; }

// ////////////////////////////////////////
// // Sorting with Ford-Johnson algorithm for std::deque
// void PmergeMe::sortDequeFJ(std::deque<int> &deque) {
// 	if (deque.size() < 2) {
// 		return ;
// 	}

// 	std::deque<int> Larg;
// 	std::deque<int> Small;
// 	// 1. Grouping and Pairwise comparison
// 	size_t mid = deque.size() / 2;
// 	// Separate the last element if odd
// 	if (deque.size() % 2 != 0) {
// 		mid++;
// 	}

// 	// Group and compare elements in pairs
// 	for (size_t i = 0; i < mid - 1; i += 2) {
// 		if (deque[i] > deque[i + 1]) {
// 			std::swap(deque[i], deque[i + 1]);
// 		}
// 	}

// 	// 2. Split into larger and smaller elements.
// 	for (size_t i = 0; i < deque.size(); i++) {
// 		if ((i % 2) != 0)
// 			Larg.push_back(deque[i]);
// 		else
// 			Small.push_back(deque[i]);
// 	}

// 	// 2. Recursively sort larger elements
// 	PmergeMe::sortDequeFJ(Larg);

// 	// 4. Insert the unpaired element and sort remaining elements
// 	if (deque.size() % 2 != 0) {
// 		Small.push_back(Larg.front());
// 		Larg.erase(Larg.begin());
// 	}

// 	// 5. Merge the sorted Larg elements with the Small elements
// 	// using insertion sort with binary search for efficiency
// 	for (size_t i = 0; i < Small.size(); i++) {
// 		// Perform binary search to find insertion position
// 		int left = 0;
// 		int right = Larg.size() - 1;
// 		while (left <= right) {
// 		int mid = (left + right) / 2;
// 		if (Small[i] < Larg[mid]) {
// 			right = mid - 1;
// 		} else {
// 			left = mid + 1;
// 		}
// 		}
// 		// Insert element at the found position
// 		Larg.insert(Larg.begin() + left, Small[i]);
// 	}
// 	deque = Larg;
// }

// PmergeMe::PmergeMe (std::vector <std::pair<int, int> >& Vp) : unsortedVectorPair(Vp) {
// 	sortedVectorPair = unsortedVectorPair;
// 	clock_t start = clock();
// 	PmergeMe::sortVectorFJPair(sortedVectorPair);
// 	clock_t end = clock();
// 	vectorTime = 1000000.0 * (end - start) / CLOCKS_PER_SEC;
// }

// void PmergeMe::sortVectorPairFJ (std::vector <std::pair<int, int>* >& vector)
// {
// 	bool odd = false;
	
// 	if (vector.size() < 2)
// 		return ;
	
// 	size_t mid = vector.size() / 2;
// 	// Separate the last element if odd
// 	if (vector.size() % 2 != 0) {
// 		mid++;
// 	}
	
// 	//std::vector <std::pair <std::pair<std::pair<int, int>*, int>, std::pair<std::pair<int, int>*, int> > > pairs;

// 	for (size_t i = 0; i < mid - 1; i += 2) {
// 		if (vector[i]->first > vector[i + 1]->first)
// 			std::swap (vector[i], vector[i + 1]);
// 	}
	
// 	for (size_t i = 0; i < vector.size(); i += 2) {
// 	if (i < vector.size() - 1) {
// 			// Create a pair with the two elements
// 			//std::pair <std::pair<int, int>*, int> p(vector[i], i);
// 			//std::pair <std::pair<int, int>* , int> p2(vector[i + 1], i);
// 			//std::pair <std::pair<std::pair<int, int>*, int>, std::pair<std::pair<int, int>*, int> > p3(p, p2);
// 			vector[i]->second = i;
// 			vector[i + 1]->second = i;
// 			//pairs.push_back(p3);
// 		} else {
// 			// If odd number of elements, add the last element as a pair with itself
// 			//std::pair <std::pair<int, int>*, int> p(vector[i], i);
// 			//std::pair <std::pair<std::pair<int, int>*, int>, std::pair<std::pair<int, int>*, int> > p2(p, p);
// 			vector[i]->second = i + 1;
// 			//pairs.push_back(p2);
// 			odd = true;
// 		}
// 	}

// 	// 2. Split into larger and smaller elements.
// 	//for (size_t i = 0; i < pairs.size(); i++)
// 	//pairs[0].first.first = 100;
// 	 std::vector<std::pair<int, int>* > Larg;
// 	 std::vector<std::pair<int, int>* > Small;
// 	// for (size_t i = 0; i < pairs.size(); i++) {
// 	// 	std::cout << "i = " << pairs[i].first.first->first << ", i+1 = " << pairs[i].second.first->first << std::endl;
// 	// 	Larg.push_back(pairs[i].second.first);
// 	// 	Small.push_back(pairs[i].first.first);
// 	// }

// 	///////////

// 	// 2. Split into larger and smaller elements.
// 	for (size_t i = 0; i < vector.size(); i++) {
// 		if ((i % 2) != 0)
// 			Larg.push_back(vector[i]);
// 		else
// 			Small.push_back(vector[i]);
// 	}
// 	///////

// 	// std::vector <std::pair <int, int > * > P;
	
// 	// for (size_t i = 0; i < Larg.size(); i++) {
// 	// 	P.push_back(Larg[i]);
// 	// }
// 	// 2. Recursively sort larger elements
// 	PmergeMe::sortVectorPairFJ(Larg);
	
// 	// 3. erase the repeated element in Small if its odd
// 	//if (odd)
// 	//	Small.pop_back();
// 	if (vector.size() % 2 != 0) {
// 		Small.push_back(Larg.front());
// 		Larg.erase(Larg.begin());
// 	}

// 	// 4. Insert the paired element with the first of larg, because we know its the smallest
// 	// int j = Larg[0]->second;
// 	// for (size_t i = 0; i < Small.size(); i++) {
// 	// 	if (Small[i]->second == j) {
// 	// 		Larg.insert (Larg.begin(), Small[i]);
// 	// 		Small.erase(Small.begin() + i);
// 	// 	}
// 	// }
	


// 	// 5. Merge the sorted Larg elements with the Small elements
// 	// using insertion sort with binary search for efficiency
// 	for (size_t i = 0; i < Small.size(); i++) {
// 		// Perform binary search to find insertion position
// 		size_t k = 0;
// 		while (k < Larg.size() - 1) {
// 			if (Larg[k]->second == Small[i]->second)
// 				break ;
// 			k++;
// 		}
// 		int left = 0;
// 		int right = Larg.size() - 1;
// 		while (left <= right) {
// 			int mid = (left + right) / 2;
// 			if (Small[i] < Larg[mid]) {
// 				right = mid - 1;
// 			} else {
// 				left = mid + 1;
// 			}
// 		}
// 		// Insert element at the found position
// 		Larg.insert(Larg.begin() + left, Small[i]);
// 	}
// 	vector = Larg;
// 	for (size_t i = 0; i < Larg.size(); i++)
// 		std::cout << Larg[i]->first << " ";
// 	std::cout << std::endl;
// 	std::cout << "S = ";
// 	for (size_t i = 0; i < Small.size(); i++)
// 		std::cout << Small[i]->first << " ";
// 	std::cout << std::endl;
// }



// void PmergeMe::sortVectorFJPair(std::vector<std::pair<int, int> > &vector) {
// 	if (vector.size() < 2) {
// 		return ;
// 	}

// 	// 1. Grouping and Pairwise comparison
// 	size_t mid = vector.size() / 2;
// 	// Separate the last element if odd
// 	if (vector.size() % 2 != 0) {
// 		mid++;
// 	}

// 	// Group and compare elements in pairs
// 	for (size_t i = 0; i < vector.size() - 1; i += 2) {
// 		if (vector[i] > vector[i + 1]) {
// 			std::swap(vector[i], vector[i + 1]);
// 		}
// 	}
	
// 	// Vector for storing paired elements
// 	std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > pairs;

// 	// 1. Pairwise comparison
// 	for (size_t i = 0; i < vector.size(); i += 2) {
// 		if (i < vector.size() - 1) {
// 			// Create a pair with the two elements
// 			std::pair <std::pair<int, int>, std::pair<int, int> > p(vector[i], vector[i + 1]);
// 			pairs.push_back(p);
// 		} else {
// 			// If odd number of elements, add the last element as a pair with itself
// 			std::pair <std::pair<int, int>, std::pair<int, int> > p(vector[i], vector[i]);
// 			pairs.push_back(p);
// 		}
// 	}
  

// 	// 2. Split into larger and smaller elements.
// 	std::vector<std::pair<int, int> > Larg;
// 	std::vector<std::pair<int, int> > Small;
// 	for (size_t i = 0; i < pairs.size(); i++) {
// 		//std::pair <std::pair<int, int> > p (pairs[i].first);
// 		Larg.push_back(pairs[i].first);
// 		Small.push_back(pairs[i].second);
// 		Larg[i].second = i;
// 		Small[i].second = i;
// 	}


// 	// 2. Recursively sort larger elements
// 	PmergeMe::sortVectorFJPair(Larg);

// 	// 4. Insert the unpaired element and sort remaining elements
// 	if (vector.size() % 2 != 0) {
// 		Small.pop_back();
// 		//Small.push_back(Larg.front());
// 		//Larg.erase(Larg.begin());
// 	}

// 	//4. Insert the paired element with the first of larg, because we know its the smallest
// 	//size_t j = Larg[0].second;
// 	//for (size_t i = 0; i < Small.size(); i++) {
// 	//	if (Small[i].second == j) {
// 	//Larg.insert (Larg.begin(), Small[j]);
// 	//Small.erase(Small.begin() + j);
// 	//		Small.erase(Small.begin() + i);
// 	//	}
// 	//}
// 	std::cout << " P = ";
// 	for (size_t i = 0; i < pairs.size(); i++)
// 		std::cout << pairs[i].first.first << " ";
// 	std::cout << std::endl;

// 	// 5. Merge the sorted Larg elements with the Small elements
// 	// using insertion sort with binary search for efficiency
// 	for (size_t i = 0; i < Small.size(); i++) {
// 		// Perform binary search to find insertion position
// 		// if (i == j)
// 		// 	continue;
// 		int left = 0;
// 		int right = Larg.size() - 1;
// 		while (left <= right) {
// 			int mid = (left + right) / 2;
// 			if (Small[i] < Larg[mid]) {
// 				right = mid - 1;
// 			} else {
// 				left = mid + 1;
// 			}
// 		}
// 		// Insert element at the found position
// 		Larg.insert(Larg.begin() + left, Small[i]);
// 	}
// 	vector = Larg;
// 	for (size_t i = 0; i < Larg.size(); i++)
// 		std::cout << Larg[i].first << " ";
// 	std::cout << std::endl;
// 	std::cout << "S = ";
// 	for (size_t i = 0; i < Small.size(); i++)
// 		std::cout << Small[i].first << " ";
// 	std::cout << std::endl;
// }