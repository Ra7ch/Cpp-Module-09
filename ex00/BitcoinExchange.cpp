/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 00:22:56 by raitmous          #+#    #+#             */
/*   Updated: 2023/12/09 15:07:18 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


void BitcoinExchange::error(std::string type)
{
	std::cerr << "Error: " << type << std::endl;
	exit(1);
}

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

void	BitcoinExchange::fillFirstDate(std::string date) {
	std::stringstream   s(date);
	std::string         year, month, day;

	getline(s, year, '-');
	getline(s, month, '-');
	getline(s, day);
	firstDate[0] = atoi(year.c_str());
	firstDate[1] = atoi(month.c_str());
	firstDate[2] = atoi(day.c_str());
}


void BitcoinExchange::BaseFilling() {
	_data = false;
	std::ifstream data("data.csv");
	if (!data.is_open()) 
		error("no data Base provided");

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
		if (!_data)
			BitcoinExchange::fillFirstDate(date);
		_data = true;
	}
	data.close();
}

std::string BitcoinExchange::decreaseDate(std::string date)
{
	std::stringstream   s(date);
	std::string         year, month, day, concatenated;

	getline(s, year, '-');
	getline(s, month, '-');
	getline(s, day);
	int	y = atoi(year.c_str());
	int	m = atoi(month.c_str());
	int	d = atoi(day.c_str());
	if (d > 1)
		d--;
	else if (m > 1)
	{
		d = 31;
		m--;
	}
	else if (y > 2008)
	{
		d = 31;
		m = 12;
		y--;
	}
	std::stringstream conc;
	conc << y << '-' << std::setw(2) << std::setfill('0') << m << '-' << std::setw(2) << std::setfill('0') << d;
	concatenated = conc.str();
	return (concatenated);
}


std::map<std::string, double>::iterator BitcoinExchange::findDate(std::string date)
{
	std::map<std::string, double>::iterator  it = dataBase.find(date);
	
	if (it != dataBase.end())
	{
		return it;
	}
	else
	{
		date = decreaseDate(date);
		it = findDate(date);
	}
	return it;
}

void BitcoinExchange::ReadInput(const std::string& inputFile) {
	std::ifstream input(inputFile.c_str());
	if (!input.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::string line;
	getline(input, line); // Skip the header line
	if (line.compare("date | value") != 0)
		error("Invalid input format.");

	while (getline(input, line)) {
		if (!_data) {
			std::cerr << "Error: No dataBase provided to read from or its empty." << std::endl;
			continue;
		}
		std::istringstream ss(line);
		std::string date;
		double priceDivided;

		// Extract date and price from input line
		getline(ss, date, '|');
		date = trim (date);		

		ss >> priceDivided;
		if (ss.fail()) {
			// Handle missing price
			std::cerr << "Error: Missing price." << std::endl;
			continue;
		}

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
		if (priceDivided < 0 || priceDivided > 1000) {
			if (priceDivided < 0)
				std::cerr << "Error: not a positive number." << std::endl;
			else if (priceDivided > 1000)
				std::cerr << "Error: too large a number." << std::endl;
			continue;
		}

		// Find the closest date in the database
		try {
			std::map<std::string, double>::iterator it = BitcoinExchange::findDate(date);
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
		throw std::runtime_error("Error: invalid date format => ");
	}

	if (date[4] != '-' || date[7] != '-') {
		throw std::runtime_error("Error: invalid date format => ");
	}

	if (!isdigit(date[0]) || !isdigit(date[1]) || !isdigit(date[2]) || !isdigit(date[3])
		|| !isdigit(date[5]) || !isdigit(date[6]) || !isdigit(date[8]) || !isdigit(date[9]) )
		throw std::runtime_error("Error: invalid date format => ");

	// Check individual components
	int year, month, day;

	try {
		year = atoi(date.substr(0, 4).c_str());
		month = atoi(date.substr(5, 2).c_str());
		day = atoi(date.substr(8, 2).c_str());
	} catch (std::exception& e) {
		throw std::runtime_error("Error: invalid date format => ");
	}

	// Validate month range
	if (month < 1 || month > 12) {
		throw std::runtime_error("Error: invalid date format => ");
	}

	// Validate day range (handle leap years)
	static const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (day < 1 || day > 31) {
		throw std::runtime_error("Error: invalid date format => ");
	} else if (month == 2 && day == 29) {
		if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
			// It's a leap year, so February can have 29 days
			return true;
		} else {
			throw std::runtime_error("Error: invalid date format => ");
		}
	} else {
		if (day < 1 || day > daysInMonth[month - 1]) {
        	throw std::runtime_error("Error: invalid date format => ");
		}
	}

	// Validate year range
	if (year < firstDate[0]) {
		throw std::runtime_error("Error: Year out of range: ");
	}
	if (year == firstDate[0] && month < firstDate[1]) {
		throw std::runtime_error("Error: Date out of range: ");
	}
	if (year == firstDate[0] && month == firstDate[1] && day < firstDate[2]) {
		throw std::runtime_error("Error: Date out of range: ");
	}
	return true;
}

BitcoinExchange::~BitcoinExchange () {}
