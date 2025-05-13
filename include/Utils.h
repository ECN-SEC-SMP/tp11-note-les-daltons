#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

/**
 * @brief Generate new random seed (based on time)
 */
void newRandomSeed();

/**
 * @brief Get a random number between 0 to max
 *
 * @param max (IN) Max random number
 * @return int
 */
int getRandomNumber(int max);

/**
 * @brief Sleep for X seconds
 *
 * @param seconds (IN) Sleeping duration in seconds
 */
void sleep(int seconds);

/**
 * @brief Test if a string is a number
 *
 * @param s (IN) String to test
 * @return true if the string is a number
 * @return false else (letters, special chars, empty, ...)
 */
bool is_number(const std::string &s);

/**
 * @brief Trim a string
 * @note This function remove leading and trailing spaces
 * 
 * @param str (IN) Input string 
 * @param whitespace (IN) Space to remove
 * @return std::string result
 */
std::string trim(const std::string &str, const std::string &whitespace = " \t");

/**
 * @brief Reduce a string
 * @note This function remove leading and trailing spaces and replace spaces in string by content of fill argument
 * 
 * @param str (IN) Input string 
 * @param fill (IN) String to replace whitespace in middle of input string
 * @param whitespace (IN) Space to remove
 * @return std::string 
 */
std::string reduce(const std::string &str, const std::string &fill = " ", const std::string &whitespace = " \t");

#endif /* _UTILS_H_ */
