#include <iostream>
#include <unistd.h>
#include <thread>
#include <future>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <fcntl.h>
#endif

#include "Menu.h"

#ifdef _WIN32
static DWORD originalMode;
#endif

Menu::Menu(std::string title, int mode)
    : title(title), colorSelection(32), mode(mode), timeout(10), reset_timeout_on_key_press(true),
      cancel_timeout_on_key_press(true), prevent_deplacement(false), prevent_argument(false), quitKey(0), // default color green and timeout 10 seconds
      current_option(0)
{
}

Menu::~Menu() {}

Menu &Menu::addOption(const std::string &option, MenuCallback_t func)
{
    this->options.push_back(option);
    this->options_args.push_back("");
    if (func)
    {
        this->callbacks.push_back(func);
    }
    else
    {
        this->callbacks.push_back([](int, Menu *)
                                  { return false; }); // default callback
    }
    return *this;
}

Menu &Menu::setColorSelection(int color)
{
    this->colorSelection = color;
    return *this;
}

std::vector<std::string> &Menu::getOptions()
{
    return this->options;
}

std::vector<std::string> &Menu::getOptionsArgs()
{
    return this->options_args;
}

Menu &Menu::setTimeout(int timeout)
{
    this->timeout = timeout;
    return *this;
}

Menu &Menu::setTitle(const std::string &title)
{
    this->title = title;
    return *this;
}

Menu &Menu::resetTimeoutOnKeyPress(bool reset)
{
    this->reset_timeout_on_key_press = reset;
    return *this;
}

Menu &Menu::cancelTimeoutOnKeyPress(bool reset)
{
    this->cancel_timeout_on_key_press = reset;
    return *this;
}

Menu &Menu::preventDeplacement(bool prevent)
{
    this->prevent_deplacement = prevent;
    return *this;
}

Menu &Menu::preventArguments(bool prevent)
{
    this->prevent_argument = prevent;
    return *this;
}

Menu &Menu::preventQuitOnEnter(bool prevent)
{
    this->prevent_quit_on_enter = prevent;
    return *this;
}

Menu &Menu::setMode(int mode)
{
    this->mode = mode;
    if (mode == 1)
    {
        this->timeout = 10;                       // default timeout
        this->reset_timeout_on_key_press = true;  // default reset timeout on key press
        this->cancel_timeout_on_key_press = true; // default cancel timeout on key press
        this->setQuitKey(0);
    }
    return *this;
}

Menu &Menu::setQuitKey(char key)
{
    this->quitKey = key;
    return *this;
}

Menu &Menu::setOptionPos(int pos)
{
    this->current_option = pos - 1;
    return *this;
}

void Menu::printMenu(int pos)
{
    // Print the title of the menu
    std::cout << this->title << std::endl; // reset color

    // Print each option with its index
    for (size_t i = 0; i < options.size(); ++i)
    {
        if ((int)i == pos)
            std::cout << "\033[1;37m\033[" << this->colorSelection << "m";
        std::cout << i + 1 << ". " << this->options[i] << " " << this->options_args[i] << std::endl;
        if ((int)i == pos)
            std::cout << "\033[0m"; // reset
    }
}

void Menu::clear()
{
    // std::cout << "\033[2J\033[1;1H";
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Menu::setTerminal()
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hStdin, &originalMode);

    DWORD newMode = originalMode;
    newMode &= ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT); // Disable echo and line input
    SetConsoleMode(hStdin, newMode);
    SetConsoleOutputCP(CP_UTF8);
#else
    // use system call to make terminal not echo keystrokes
    system("/bin/stty -echo");
    // use system call to make terminal send all keystrokes directly to stdin
    system("/bin/stty raw");
#endif
}

void Menu::resetTerminal()
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(hStdin, originalMode);
#else
    // use system call to set terminal behaviour to more normal behaviour
    system("/bin/stty cooked");
    // use system call to make terminal echo keystrokes
    system("/bin/stty echo");
#endif
}

void Menu::set_nonblocking(bool enable)
{
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    if (enable)
        mode &= ~ENABLE_LINE_INPUT; // disables line buffering (somewhat like non-blocking)
    else
        mode |= ENABLE_LINE_INPUT; // re-enable line buffering (blocking mode)
    SetConsoleMode(hStdin, mode);
#else
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (enable)
        fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
    else
        fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
#endif
}

void Menu::displayMenu()
{
    Menu::resetTerminal();

    Menu::clear();
    this->printMenu(this->current_option);
    std::cout << std::endl;
    std::cout << "Press arrow keys to move." << std::endl;
    std::cout << "Press enter to select an option." << std::endl;
    if (this->quitKey != 0)
        std::cout << "Press '" << this->quitKey << "' to quit." << std::endl;
    if (mode == 1)
        std::cout << "Wait for \033[31m" << this->remaining_time << "\033[0m seconds." << std::endl;

    Menu::setTerminal();
}

int Menu::run()
{
    int c = 0;
    bool is_running = true;
    bool timeout_cancelled = false;
    // this->current_option = 0;

    std::cout << "\033[?25l"; // hide cursor
    // std::cout << "\033[?1049h"; // switch to alternate screen buffer

    time_t start_time = time(nullptr);
    this->remaining_time = this->timeout;

    while (is_running)
    {
        this->displayMenu();

        if (mode == 1 && !timeout_cancelled)
        {
            Menu::set_nonblocking(true);
            c = getchar();
            Menu::set_nonblocking(false);
            if (time(nullptr) - start_time >= this->timeout)
            {
                is_running = false;
            }
            else
            {
                remaining_time = this->timeout - (time(nullptr) - start_time);
            }
        }
        else
        {
#ifdef _WIN32
            c = _getch();
#else
            c = getchar();
#endif
        }

        if (cancel_timeout_on_key_press && mode == 1 && c != -1)
        {
            mode = 0; // cancel timeout
            timeout_cancelled = true;
        }
        else if (reset_timeout_on_key_press && mode == 1 && c != -1)
        {
            start_time = time(nullptr);
            remaining_time = this->timeout;
        }

        switch (c)
        {
#ifdef _WIN32
        case 224:
            if (prevent_deplacement)
                break;
            c = _getch();
            switch (c)
                {
                case 72: // up arrow
                    this->current_option--;
                    if (this->current_option < 0)
                        this->current_option = 0;
                    break;
                case 80: // down arrow
                    this->current_option++;
                    if (this->current_option > (int)options.size() - 1)
                        this->current_option = (int)options.size() - 1;
                    break;
                }
            break;
#else
        case 27: // escape
            if (prevent_deplacement)
                break;
            c = getchar();
            if (c == 91) // [
            {
                c = getchar();
                switch (c)
                {
                case 65: // up arrow
                    this->current_option--;
                    if (this->current_option < 0)
                        this->current_option = 0;
                    break;
                case 66: // down arrow
                    this->current_option++;
                    if (this->current_option > (int)options.size() - 1)
                        this->current_option = (int)options.size() - 1;
                    break;
                }
            }
            break;
#endif
        case 3: // CTRL+C
            is_running = false;
            break;
        case '\r': // enter
            // is_running = false;
            if (this->current_option >= 0 && this->current_option < (int)this->options.size())
            {
                Menu::resetTerminal();
                is_running = this->callbacks[this->current_option](this->current_option, this); // call the callback function
                Menu::setTerminal();
            }
            break;
        case 'q': // quit
            if (this->quitKey == 0)
                break; // if quit key is not set, ignore
            if (mode == 0)
            {
                this->current_option = -1; // set pos to -1 to indicate quit
                is_running = false;
            }
            else
            {
                if (!prevent_argument)
                    if (this->current_option >= 0 && this->current_option < (int)this->options.size())
                        this->options_args[this->current_option] += c; // add character to the selected option
            }
            break;
        case 127: // backspace
            if (!prevent_argument)
                if (this->current_option >= 0 && this->current_option < (int)this->options.size() && this->options_args[this->current_option].length() > 0)
                    this->options_args[this->current_option].pop_back(); // remove last character from the selected option
            break;
        default:
            if (!prevent_argument)
                if (this->current_option >= 0 && this->current_option < (int)this->options.size() && c != -1)
                    this->options_args[this->current_option] += c; // add character to the selected option
            break;
        }

        Menu::resetTerminal();
    }

    // std::cout << "\033[?1049l"; // switch back to normal screen buffer
    std::cout << "\033[?25h"; // show cursor
    // Menu::clear();

    return this->current_option < 0 ? this->current_option : this->current_option + 1; // return the selected option index
}