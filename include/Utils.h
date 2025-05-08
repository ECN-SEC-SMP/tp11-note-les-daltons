#ifndef _UTILS_H_
#define _UTILS_H_

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

#endif /* _UTILS_H_ */
