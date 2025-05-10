/**
 * @file Menu.h
 * @author Louis Vaillant (louis.vaillant@eleves.ec-nantes.fr)
 * @brief Menu manager
 * @version 0.1
 * @date 2025-04-29
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <vector>
#include <string>
#include <functional>

class Menu
{
public:
    /// @brief Callback function type
    typedef std::function<bool(int, Menu *)> MenuCallback_t;

private:
    /// @brief Options of the menu
    std::vector<std::string> options;
    /// @brief Arguments of the options
    std::vector<std::string> options_args;
    /// @brief Title of the menu
    std::string title;
    /// @brief Color of the selected option
    int colorSelection;
    /// @brief Color of the selected option
    /// @note 0 = 'q to quit', 1 = 'timeout'
    int mode;
    /// @brief Delay time in seconds
    /// @note Used only in mode 1
    int timeout;
    /// @brief Reset the timeout on key press
    bool reset_timeout_on_key_press;
    /// @brief Cancel the timeout on key press
    bool cancel_timeout_on_key_press;
    /// @brief Prevent the deplacement of the cursor
    bool prevent_deplacement;
    /// @brief Prevent the argument of the selected option
    bool prevent_argument;
    /// @brief Prevent quit when enter key is pressed
    bool prevent_quit_on_enter;
    /// @brief Quit key char
    /// @note 0 to disable the quit key
    char quitKey;
    /// @brief Callback function for the selected option
    std::vector<MenuCallback_t> callbacks;
    /// @brief Current position of the selected option
    int current_option = -1;
    /// @brief Remaining time in seconds
    /// @note Used only in mode 1
    int remaining_time = 0;

private:
    /**
     * @brief Print the menu
     *
     * @param pos (IN) Position of the selected option
     */
    void printMenu(int pos);

public:
    /**
     * @brief Construct a new Menu object
     *
     * @param title (IN) Title of the menu (default: "Menu")
     * @param mode (IN) Mode of the menu (default: 0)
     * @note Mode: 0 = 'q to quit', 1 = 'timeout'
     */
    Menu(std::string title = "Menu", int mode = 0);
    ~Menu();
    /**
     * @brief Add an option to the menu
     *
     * @param option (IN) Option to add
     *
     * @return (Menu*) Pointer to the Menu object
     */
    Menu &addOption(const std::string &option, MenuCallback_t func = nullptr);
    /**
     * @brief Set the Color Selection object
     *
     * @param color (IN) Color of the selected option (default: 32)
     * @note 32 = green, 31 = red, 33 = yellow, 34 = blue, 35 = magenta, 36 = cyan
     *
     * @return (Menu*) Pointer to the Menu object
     */
    Menu &setColorSelection(int color);

    /**
     * @brief Executes the main logic of the menu.
     *
     * This method is responsible for running the menu system, handling user input,
     * and performing the corresponding actions based on the selected options.
     *
     * @return (int) Returns the index of the selected option or -1 if the menu is exited.
     */
    int run();

    /**
     * @brief Get options of the menu
     *
     * @return (std::vector<std::string>) Options of the menu
     */
    std::vector<std::string> &getOptions();
    /**
     * @brief Get the arguments of the options
     *
     * @return (std::vector<std::string>) Arguments of the options
     */
    std::vector<std::string> &getOptionsArgs();
    /**
     * @brief Set the timeout for the menu
     *
     * @param timeout (IN) Timeout in seconds
     * @note This function is used only in mode 1
     *
     * @return Menu*
     */
    Menu &setTimeout(int timeout);
    /**
     * @brief Set the title of the menu
     *
     * @param title (IN) Title of the menu
     * @return Menu*
     */
    Menu &setTitle(const std::string &title);
    /**
     * @brief Enable/Disable the reset of the timeout on key press
     *
     * @param reset (IN) Reset the timeout on key press (default: true)
     * @note This function is used only in mode 1
     *
     * @return Menu*
     */
    Menu &resetTimeoutOnKeyPress(bool reset = true);
    /**
     * @brief Enable/Disable the cancel of the timeout on key press
     *
     * @param reset (IN) Cancel the timeout on key press (default: true)
     * @note This function is used only in mode 1
     *
     * @return Menu*
     */
    Menu &cancelTimeoutOnKeyPress(bool reset = true);
    /**
     * @brief Prevent the deplacement of the cursor
     *
     * @param prevent (IN) Prevent the deplacement of the cursor (default: true)
     *
     * @return Menu*
     */
    Menu &preventDeplacement(bool prevent = true);
    /**
     * @brief Prevent the argument of the selected option
     *
     * @param prevent (IN) Prevent the argument of the selected option (default: true)
     *
     * @return Menu*
     */
    Menu &preventArguments(bool prevent = true);
    /**
     * @brief Prevent quit when enter key is pressed
     *
     * @param prevent (IN) Prevent quit when enter key is pressed (default: true)
     * @return Menu*
     */
    Menu &preventQuitOnEnter(bool prevent = true);
    /**
     * @brief Set the mode of the menu
     *
     * @param mode (IN) Mode of the menu : 0 = 'q to quit', 1 = 'timeout' (default: 0)
     * @return Menu*
     */
    Menu &setMode(int mode = 0);
    /**
     * @brief Set the quit key char
     *
     * @param key (IN) Quit key char (default: 'q')
     * @note 0 to disable the quit key
     *
     * @return Menu*
     */
    Menu &setQuitKey(char key = 'q');
    /**
     * @brief Set the position of selected option
     * 
     * @param pos (IN) Position of selected option
     * @return Menu& 
     */
    Menu &setOptionPos(int pos);
    /**
     * @brief Clear the screen
     *
     * @note This function uses ANSI escape codes to clear the screen.
     */
    static void clear();
    /**
     * @brief Set the terminal settings for raw input
     */
    static void setTerminal();
    /**
     * @brief Reset the terminal settings to normal
     */
    static void resetTerminal();
    /**
     * @brief Set the terminal to non-blocking mode
     *
     * @param enable (IN) Enable or disable non-blocking mode
     */
    static void set_nonblocking(bool enable);
    /**
     * @brief Display the menu
     */
    void displayMenu();
};