#pragma once

#include <iostream>
#include <string>
#include <type_traits>

namespace cpp_printer::detail
{
    namespace color
    {
        inline constexpr const char* reset = "\033[0m";
        inline constexpr const char* foreground = "\033[38;2;248;248;242m";
        inline constexpr const char* name = foreground;
        inline constexpr const char* syntax = foreground;
        inline constexpr const char* number = "\033[38;2;189;147;249m";
        inline constexpr const char* text = "\033[38;2;80;250;123m";
        inline constexpr const char* character = "\033[38;2;80;250;123m";
        inline constexpr const char* keyword = "\033[38;2;255;121;198m";
        inline constexpr const char* function = "\033[38;2;139;233;253m";
        inline constexpr const char* comment = "\033[38;2;98;114;164m";
        inline constexpr const char* background = "\033[48;2;40;42;54m";
    }

    inline void print_name(std::ostream& output, const std::string& value)
    {
        output << color::name << value << color::reset;
    }

    inline void print_syntax(std::ostream& output, const char* value)
    {
        output << color::syntax << value << color::reset;
    }

    inline void print_value(std::ostream& output, const char* value)
    {
        output << color::text << '"' << value << '"' << color::reset;
    }

    template <std::size_t Size>
    void print_value(std::ostream& output, const char (&value)[Size])
    {
        print_value(output, static_cast<const char*>(value));
    }

    template <typename T>
    void print_value(std::ostream& output, const T& value)
    {
        using Value = std::remove_cv_t<std::remove_reference_t<T>>;

        if constexpr (std::is_same_v<Value, std::string>)
        {
            output << color::text << '"' << value << '"' << color::reset;
        }
        else if constexpr (std::is_same_v<Value, char>)
        {
            output << color::character << '\'' << value << '\'' << color::reset;
        }
        else if constexpr (std::is_arithmetic_v<Value>)
        {
            output << color::number << value << color::reset;
        }
        else
        {
            output << value;
        }
    }
}
