/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:50:18 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 00:15:39 by raitmous         ###   ########.fr       */
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
	if (vector.size() < 2) {
		return ;
	}

	std::vector<int> Larg;
	std::vector<int> Small;
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

	// 2. Split into larger and smaller elements.
	for (size_t i = 0; i < vector.size(); i++) {
		if ((i % 2) != 0)
			Larg.push_back(vector[i]);
		else
			Small.push_back(vector[i]);
	}

	// 2. Recursively sort larger elements
	PmergeMe::sortVectorFJ(Larg);

	// 4. Insert the unpaired element and sort remaining elements
	if (vector.size() % 2 != 0) {
		Small.push_back(Larg.front());
		Larg.erase(Larg.begin());
	}

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
	if (deque.size() < 2) {
		return ;
	}

	std::deque<int> Larg;
	std::deque<int> Small;
	// 1. Grouping and Pairwise comparison
	size_t mid = deque.size() / 2;
	// Separate the last element if odd
	if (deque.size() % 2 != 0) {
		mid++;
	}

	// Group and compare elements in pairs
	for (size_t i = 0; i < mid - 1; i += 2) {
		if (deque[i] > deque[i + 1]) {
			std::swap(deque[i], deque[i + 1]);
		}
	}

	// 2. Split into larger and smaller elements.
	for (size_t i = 0; i < deque.size(); i++) {
		if ((i % 2) != 0)
			Larg.push_back(deque[i]);
		else
			Small.push_back(deque[i]);
	}

	// 2. Recursively sort larger elements
	PmergeMe::sortDequeFJ(Larg);

	// 4. Insert the unpaired element and sort remaining elements
	if (deque.size() % 2 != 0) {
		Small.push_back(Larg.front());
		Larg.erase(Larg.begin());
	}

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