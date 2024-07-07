#ifndef COLORMANAGER_HPP
#define COLORMANAGER_HPP

#include <string>

using std::string;

/**
 * @brief Namespace for managing terminal text and background colors.
 *
 * This namespace provides inline functions for various text and background colors
 * to be used in terminal output. It includes standard colors, bright colors,
 * and background colors.
 */

// Why inline?
// Inline constants are preferred for terminal colors for efficiency and ease of use.

namespace Color
{
    /**
     * @brief Reset color to default.
     *
     * @return const string& Reference to the RESET color string.
     */
    inline const string &RESET()
    {
        static const string s = "\033[0m";
        return s;
    }

    // Standard text colors

    /**
     * @brief Black text color.
     *
     * @return const string& Reference to the BLACK color string.
     */
    inline const string &BLACK()
    {
        static const string s = "\033[30m";
        return s;
    }

    /**
     * @brief Red text color.
     *
     * @return const string& Reference to the RED color string.
     */
    inline const string &RED()
    {
        static const string s = "\033[31m";
        return s;
    }

    /**
     * @brief Green text color.
     *
     * @return const string& Reference to the GREEN color string.
     */
    inline const string &GREEN()
    {
        static const string s = "\033[32m";
        return s;
    }

    /**
     * @brief Yellow text color.
     *
     * @return const string& Reference to the YELLOW color string.
     */
    inline const string &YELLOW()
    {
        static const string s = "\033[33m";
        return s;
    }

    /**
     * @brief Blue text color.
     *
     * @return const string& Reference to the BLUE color string.
     */
    inline const string &BLUE()
    {
        static const string s = "\033[34m";
        return s;
    }

    /**
     * @brief Magenta text color.
     *
     * @return const string& Reference to the MAGENTA color string.
     */
    inline const string &MAGENTA()
    {
        static const string s = "\033[35m";
        return s;
    }

    /**
     * @brief Cyan text color.
     *
     * @return const string& Reference to the CYAN color string.
     */
    inline const string &CYAN()
    {
        static const string s = "\033[36m";
        return s;
    }

    /**
     * @brief White text color.
     *
     * @return const string& Reference to the WHITE color string.
     */
    inline const string &WHITE()
    {
        static const string s = "\033[37m";
        return s;
    }

    // Bright text colors

    /**
     * @brief Bright black text color.
     *
     * @return const string& Reference to the BRIGHT_BLACK color string.
     */
    inline const string &BRIGHT_BLACK()
    {
        static const string s = "\033[90m";
        return s;
    }

    /**
     * @brief Bright red text color.
     *
     * @return const string& Reference to the BRIGHT_RED color string.
     */
    inline const string &BRIGHT_RED()
    {
        static const string s = "\033[91m";
        return s;
    }

    /**
     * @brief Bright green text color.
     *
     * @return const string& Reference to the BRIGHT_GREEN color string.
     */
    inline const string &BRIGHT_GREEN()
    {
        static const string s = "\033[92m";
        return s;
    }

    /**
     * @brief Bright yellow text color.
     *
     * @return const string& Reference to the BRIGHT_YELLOW color string.
     */
    inline const string &BRIGHT_YELLOW()
    {
        static const string s = "\033[93m";
        return s;
    }

    /**
     * @brief Bright blue text color.
     *
     * @return const string& Reference to the BRIGHT_BLUE color string.
     */
    inline const string &BRIGHT_BLUE()
    {
        static const string s = "\033[94m";
        return s;
    }

    /**
     * @brief Bright magenta text color.
     *
     * @return const string& Reference to the BRIGHT_MAGENTA color string.
     */
    inline const string &BRIGHT_MAGENTA()
    {
        static const string s = "\033[95m";
        return s;
    }

    /**
     * @brief Bright cyan text color.
     *
     * @return const string& Reference to the BRIGHT_CYAN color string.
     */
    inline const string &BRIGHT_CYAN()
    {
        static const string s = "\033[96m";
        return s;
    }

    /**
     * @brief Bright white text color.
     *
     * @return const string& Reference to the BRIGHT_WHITE color string.
     */
    inline const string &BRIGHT_WHITE()
    {
        static const string s = "\033[97m";
        return s;
    }

    // Background colors

    /**
     * @brief Black background color.
     *
     * @return const string& Reference to the BG_BLACK color string.
     */
    inline const string &BG_BLACK()
    {
        static const string s = "\033[40m";
        return s;
    }

    /**
     * @brief Red background color.
     *
     * @return const string& Reference to the BG_RED color string.
     */
    inline const string &BG_RED()
    {
        static const string s = "\033[41m";
        return s;
    }

    /**
     * @brief Green background color.
     *
     * @return const string& Reference to the BG_GREEN color string.
     */
    inline const string &BG_GREEN()
    {
        static const string s = "\033[42m";
        return s;
    }

    /**
     * @brief Yellow background color.
     *
     * @return const string& Reference to the BG_YELLOW color string.
     */
    inline const string &BG_YELLOW()
    {
        static const string s = "\033[43m";
        return s;
    }

    /**
     * @brief Blue background color.
     *
     * @return const string& Reference to the BG_BLUE color string.
     */
    inline const string &BG_BLUE()
    {
        static const string s = "\033[44m";
        return s;
    }

    /**
     * @brief Magenta background color.
     *
     * @return const string& Reference to the BG_MAGENTA color string.
     */
    inline const string &BG_MAGENTA()
    {
        static const string s = "\033[45m";
        return s;
    }

    /**
     * @brief Cyan background color.
     *
     * @return const string& Reference to the BG_CYAN color string.
     */
    inline const string &BG_CYAN()
    {
        static const string s = "\033[46m";
        return s;
    }

    /**
     * @brief White background color.
     *
     * @return const string& Reference to the BG_WHITE color string.
     */
    inline const string &BG_WHITE()
    {
        static const string s = "\033[47m";
        return s;
    }

    // High intensity background colors

    /**
     * @brief Bright black background color.
     *
     * @return const string& Reference to the BG_BRIGHT_BLACK color string.
     */
    inline const string &BG_BRIGHT_BLACK()
    {
        static const string s = "\033[100m";
        return s;
    }

    /**
     * @brief Bright red background color.
     *
     * @return const string& Reference to the BG_BRIGHT_RED color string.
     */
    inline const string &BG_BRIGHT_RED()
    {
        static const string s = "\033[101m";
        return s;
    }

    /**
     * @brief Bright green background color.
     *
     * @return const string& Reference to the BG_BRIGHT_GREEN color string.
     */
    inline const string &BG_BRIGHT_GREEN()
    {
        static const string s = "\033[102m";
        return s;
    }

    /**
     * @brief Bright yellow background color.
     *
     * @return const string& Reference to the BG_BRIGHT_YELLOW color string.
     */
    inline const string &BG_BRIGHT_YELLOW()
    {
        static const string s = "\033[103m";
        return s;
    }

    /**
     * @brief Bright blue background color.
     *
     * @return const string& Reference to the BG_BRIGHT_BLUE color string.
     */
    inline const string &BG_BRIGHT_BLUE()
    {
        static const string s = "\033[104m";
        return s;
    }

    /**
     * @brief Bright magenta background color.
     *
     * @return const string& Reference to the BG_BRIGHT_MAGENTA color string.
     */
    inline const string &BG_BRIGHT_MAGENTA()
    {
        static const string s = "\033[105m";
        return s;
    }

    /**
     * @brief Bright cyan background color.
     *
     * @return const string& Reference to the BG_BRIGHT_CYAN color string.
     */
    inline const string &BG_BRIGHT_CYAN()
    {
        static const string s = "\033[106m";
        return s;
    }

    /**
     * @brief Bright white background color.
     *
     * @return const string& Reference to the BG_BRIGHT_WHITE color string.
     */
    inline const string &BG_BRIGHT_WHITE()
    {
        static const string s = "\033[107m";
        return s;
    }
}

#endif // COLORMANAGER_HPP
