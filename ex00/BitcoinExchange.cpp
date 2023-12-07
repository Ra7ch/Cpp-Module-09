/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:22:56 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/07 00:50:38 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

std::string trim(const std::string& str) {
	std::string trimmedStr = str;

	// Trim leading spaces
	while (trimmedStr[0] == ' ') {
		trimmedStr.erase(trimmedStr.begin());
	}

	// Trim trailing spaces
	while (trimmedStr[trimmedStr.length() - 1] == ' ') {
		trimmedStr.erase(trimmedStr.end() - 1);
	}

	return trimmedStr;
}

BitcoinExchange::BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator= (const BitcoinExchange& other) {
	if (this != &other) {
		dataBase = other.dataBase;
	}
	return *this;
}

void BitcoinExchange::BaseFilling() {
	std::ifstream data("data.csv");
	if (!data.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	getline(data, line);

	while (getline(data, line)) {
		std::istringstream ss(line);
		std::string date;
		double price;

		// Extract date and price from CSV line
		getline(ss, date, ',');
		ss >> price;

		if (!ss.fail()) {
			// Successfully read the date and price
			dataBase[date] = price;
		} else {
			std::cerr << "Error: Bad input line => " << line << std::endl;
		}
	}
	data.close();
}

void BitcoinExchange::ReadInput(const std::string& inputFile) {
	std::ifstream input(inputFile.c_str());
	if (!input.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	getline(input, line); // Skip the header line

	while (getline(input, line)) {
		std::istringstream ss(line);
		std::string date;
		double priceDivided;

		// Extract date and price from input line
		getline(ss, date, '|');
		date = trim (date);

		ss >> priceDivided;

		try {
			// Check if there is any left charachters after the number.
			if (ss.peek() != EOF)
				throw std::runtime_error("Error: Invalid input");
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			continue;
		}
		// Validate the date format (you might want to add more robust validation)
		try {
			BitcoinExchange::validateDate(date);
		} catch (std::exception &e) {
			std::cerr << e.what() << date << std::endl;
			continue ;
		}

		// Validate the price value
		if (priceDivided <= 0 || priceDivided > 1000) {
			std::cerr << "Error: not a positive number: " << priceDivided << std::endl;
			continue;
		}

		// Find the closest date in the database
		try {
			std::map<std::string, double>::iterator it = dataBase.lower_bound(date);
			if (it == dataBase.end()) 
				throw std::runtime_error("Error: date not found in the database: ");
			double exchangeRate = it->second;
			double result = priceDivided * exchangeRate;
			std::cout << date << " => " << priceDivided << " = " << std::fixed << std::setprecision(2) << result << std::endl;
		} catch (std::exception &e) {
			std::cerr << e.what() << date << std::endl;
		}
	}
	input.close();
}

bool BitcoinExchange::validateDate(const std::string& date) {
	// Check for valid format: YYYY-MM-DD
	if (date.length() != 10) {
		throw std::runtime_error("Error: invalid date format: ");
	}

	if (date[4] != '-' || date[7] != '-') {
		throw std::runtime_error("Error: invalid date format: ");
	}

	// Check individual components
	int year, month, day;

	try {
		year = atoi(date.substr(0, 4).c_str());
		month = atoi(date.substr(5, 2).c_str());
		day = atoi(date.substr(8, 2).c_str());
	} catch (std::exception& e) {
		throw std::runtime_error("Error: invalid date format: ");
	}
	// Validate year range
	if (year < 1900 || year > 2023) {
		throw std::runtime_error("Error: invalid date format: ");
	}

	// Validate month range
	if (month < 1 || month > 12) {
		throw std::runtime_error("Error: invalid date format: ");
	}

	// Validate day range (handle leap years)
	static const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > 31) {
		throw std::runtime_error("Error: invalid date format: ");
	} else if (month == 2 && day == 29) {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			// It's a leap year, so February can have 29 days
			return true;
		} else {
			throw std::runtime_error("Error: invalid date format: ");
		}
	} else {
		if (day < 1 || day > daysInMonth[month - 1]) {
        	throw std::runtime_error("Error: invalid date format: ");
		}
		return true;
	}
}

BitcoinExchange::~BitcoinExchange () {}
