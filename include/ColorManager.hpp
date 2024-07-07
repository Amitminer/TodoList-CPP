#ifndef COLORMANAGER_HPP
#define COLORMANAGER_HPP

#include <string>

using std::string;

/**
 * @brief Namespace for managing terminal text and background colors.
 *
 * This namespace provides constants for various text and background colors
 * to be used in terminal output. It includes standard colors, bright colors,
 * and background colors.
 */
namespace ColorManager {
    // Reset color
    const string RESET = "\033[0m"; ///< Reset color to default.

    // Standard text colors
    const string BLACK = "\033[30m"; ///< Black text color.
    const string RED = "\033[31m"; ///< Red text color.
    const string GREEN = "\033[32m"; ///< Green text color.
    const string YELLOW = "\033[33m"; ///< Yellow text color.
    const string BLUE = "\033[34m"; ///< Blue text color.
    const string MAGENTA = "\033[35m"; ///< Magenta text color.
    const string CYAN = "\033[36m"; ///< Cyan text color.
    const string WHITE = "\033[37m"; ///< White text color.

    // Bright text colors
    const string BRIGHT_BLACK = "\033[90m"; ///< Bright black text color.
    const string BRIGHT_RED = "\033[91m"; ///< Bright red text color.
    const string BRIGHT_GREEN = "\033[92m"; ///< Bright green text color.
    const string BRIGHT_YELLOW = "\033[93m"; ///< Bright yellow text color.
    const string BRIGHT_BLUE = "\033[94m"; ///< Bright blue text color.
    const string BRIGHT_MAGENTA = "\033[95m"; ///< Bright magenta text color.
    const string BRIGHT_CYAN = "\033[96m"; ///< Bright cyan text color.
    const string BRIGHT_WHITE = "\033[97m"; ///< Bright white text color.

    // Background colors
    const string BG_BLACK = "\033[40m"; ///< Black background color.
    const string BG_RED = "\033[41m"; ///< Red background color.
    const string BG_GREEN = "\033[42m"; ///< Green background color.
    const string BG_YELLOW = "\033[43m"; ///< Yellow background color.
    const string BG_BLUE = "\033[44m"; ///< Blue background color.
    const string BG_MAGENTA = "\033[45m"; ///< Magenta background color.
    const string BG_CYAN = "\033[46m"; ///< Cyan background color.
    const string BG_WHITE = "\033[47m"; ///< White background color.

    // High intensity background colors
    const string BG_BRIGHT_BLACK = "\033[100m"; ///< Bright black background color.
    const string BG_BRIGHT_RED = "\033[101m"; ///< Bright red background color.
    const string BG_BRIGHT_GREEN = "\033[102m"; ///< Bright green background color.
    const string BG_BRIGHT_YELLOW = "\033[103m"; ///< Bright yellow background color.
    const string BG_BRIGHT_BLUE = "\033[104m"; ///< Bright blue background color.
    const string BG_BRIGHT_MAGENTA = "\033[105m"; ///< Bright magenta background color.
    const string BG_BRIGHT_CYAN = "\033[106m"; ///< Bright cyan background color.
    const string BG_BRIGHT_WHITE = "\033[107m"; ///< Bright white background color.
}

#endif // COLORMANAGER_HPP
