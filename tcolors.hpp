#ifndef TCOLORS_HPP
#define TCOLORS_HPP

#include <ostream>
#include <sstream>
#include <cstdint>
#include <type_traits>

namespace tcolors {

typedef uint8_t tctype;

enum class Format: tctype {
    DEFAULT         = 0,
    BOLD            = 1,
    DIM             = 2,
    ITALIC          = 3,
    UNDERLINE       = 4,
    BLINK           = 5,
    REVERSE         = 7,
    HIDDEN          = 8,
    RST_BOLD        = 21,
    RST_DIM         = 22,
    RST_UNDERLINE   = 24,
    RST_BLINK       = 25,
    RST_REVERSE     = 27,
    RST_HIDDEN      = 28
};

enum class Foreground: tctype {
    BLACK           = 30,
    RED             = 31,
    GREEN           = 32,
    YELLOW          = 33,
    BLUE            = 34,
    MAGENTA         = 35,
    CYAN            = 36,
    LIGHT_GREY      = 37,
    DEFAULT         = 39,
    DARK_GREY       = 90,
    LIGHT_RED       = 91,
    LIGHT_GREEN     = 92,
    LIGHT_YELLOW    = 93,
    LIGHT_BLUE      = 94,
    LIGHT_MAGENTA   = 95,
    LIGHT_CYAN      = 96,
    WHITE           = 97
};

enum class Background: tctype {
    BLACK           = 40,
    RED             = 41,
    GREEN           = 42,
    YELLOW          = 43,
    BLUE            = 44,
    MAGENTA         = 45,
    CYAN            = 46,
    LIGHT_GRAY      = 47,
    DEFAULT         = 49,
    DARK_GREY       = 100,
    LIGHT_RED       = 101,
    LIGHT_GREEN     = 102,
    LIGHT_YELLOW    = 103,
    LIGHT_BLUE      = 104,
    LIGHT_MAGENTA   = 105,
    LIGHT_CYAN      = 106,
    WHITE           = 107
};

// Not used
enum class Reset: tctype {
    ALL         = 0,
    BOLD        = 21,
    DIM         = 22,
    UNDERLINE   = 24,
    BLINK       = 25,
    REVERSE     = 27,
    HIDDEN      = 28
};

template <typename E>
constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}

// ========================================================================================== //
// class Modifier
// ========================================================================================== //

class Modifier
{
public:
    Modifier(Format fmt):
        _fmt(fmt),
        _fg(Foreground::DEFAULT),
        _bg(Background::DEFAULT),
        _str(makeFormatString(_fmt, _fg, _bg))
    {}
    Modifier(Foreground fg):
        _fmt(Format::DEFAULT),
        _fg(fg),
        _bg(Background::DEFAULT),
        _str(makeFormatString(_fmt, _fg, _bg))
    {}
    Modifier(Background bg):
        _fmt(Format::DEFAULT),
        _fg(Foreground::DEFAULT),
        _bg(bg),
        _str(makeFormatString(_fmt, _fg, _bg))
    {}

    Modifier(Foreground fg, Background bg):
        _fmt(Format::DEFAULT),
        _fg(fg),
        _bg(bg),
        _str(makeFormatString(_fmt, _fg, _bg))
    {}
    Modifier(Format fmt, Foreground fg, Background bg = Background::DEFAULT):
        _fmt(fmt),
        _fg(fg),
        _bg(bg),
        _str(makeFormatString(_fmt, _fg, _bg))
    {}

    friend std::ostream& operator << (std::ostream& os, const Modifier& m) {
        return os << m._str;
    }

    Format format() const { return _fmt; }
    Foreground foreground() const { return _fg; }
    Background background() const { return _bg; }

    const std::string& toString() const { return _str; }
    const char* toChar() const { return _str.c_str(); }

    static std::string makeFormatString(Format fmt,
                                        Foreground fg = Foreground::DEFAULT,
                                        Background bg = Background::DEFAULT) {
        std::stringstream ss;
        ss << "\033["
           << std::to_string(to_underlying(fmt)) << ';'
           << std::to_string(to_underlying(fg))  << ';'
           << std::to_string(to_underlying(bg))  << 'm';
        return ss.str();
    }

private:
    Format _fmt;
    Foreground _fg;
    Background _bg;

    std::string _str;

public:
    static constexpr char const * DEFAULT = "\033[0m";

};  // class Modifier

// ========================================================================================== //
// class ColorString
// ========================================================================================== //

class ColorString
{
public:
    ColorString(const std::string& str, Format fmt):
        _str(str),
        _modifier(fmt)
    {}
    ColorString(const std::string& str, Foreground fg):
        _str(str),
        _modifier(fg)
    {}
    ColorString(const std::string& str, Background bg):
        _str(str),
        _modifier(bg)
    {}

    ColorString(const std::string& str, Foreground fg, Background bg):
        _str(str),
        _modifier(fg, bg)
    {}
    ColorString(const std::string& str, Format fmt, Foreground fg,
                Background bg = Background::DEFAULT):
        _str(str),
        _modifier(fmt, fg, bg)
    {}
    ColorString(const std::string& str, Modifier& modifier):
        _str(str),
        _modifier(modifier)
    {}

    /** Returns the original string. */
    const std::string& str() const { return _str; }
    /** Returns the formated string as std::string. */
    std::string toString() const { return getFormatedString(_str, _modifier.format(), _modifier.foreground(), _modifier.background()); }
    /** Returns the formated string as const char*. */
    const char* toChar() const { return _str.c_str(); }
    const Modifier& modifier() const { return _modifier; }

    friend std::ostream& operator << (std::ostream& os, const ColorString& cs) {
        os << cs._modifier << cs._str << Modifier::DEFAULT;
        return os;
    }

    static std::string getFormatedString(const std::string& str, Format fmt,
                                         Foreground fg = Foreground::DEFAULT,
                                         Background bg = Background::DEFAULT) {
        std::stringstream ss;
        ss << "\033["
           << std::to_string(to_underlying(fmt)) << ';'
           << std::to_string(to_underlying(fg))  << ';'
           << std::to_string(to_underlying(bg))  << 'm'
           << str << Modifier::DEFAULT;
        return ss.str();
    }

private:
    std::string _str;
    Modifier _modifier;

public:
    static constexpr auto COLORIZE = [](const std::string& str, Foreground fg, Background bg = Background::DEFAULT) { return getFormatedString(str, Format::DEFAULT, fg, bg); };
    static constexpr auto FORMATIZE = [](const std::string& str, Format fmt, Foreground fg = Foreground::DEFAULT, Background bg = Background::DEFAULT) { return getFormatedString(str, fmt, fg, bg); };

    static constexpr auto BLACK = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::BLACK, Background::DEFAULT); };
    static constexpr auto RED = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::RED, Background::DEFAULT); };
    static constexpr auto GREEN = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::GREEN, Background::DEFAULT); };
    static constexpr auto YELLOW = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::YELLOW, Background::DEFAULT); };
    static constexpr auto BLUE = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::BLUE, Background::DEFAULT); };
    static constexpr auto MAGENTA = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::MAGENTA, Background::DEFAULT); };
    static constexpr auto CYAN = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::CYAN, Background::DEFAULT); };
    static constexpr auto WHITE = [](const std::string& str) { return getFormatedString(str, Format::DEFAULT, Foreground::WHITE, Background::DEFAULT); };

    static constexpr auto BOLD_BLACK = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::BLACK, Background::DEFAULT); };
    static constexpr auto BOLD_RED = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::RED, Background::DEFAULT); };
    static constexpr auto BOLD_GREEN = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::GREEN, Background::DEFAULT); };
    static constexpr auto BOLD_YELLOW = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::YELLOW, Background::DEFAULT); };
    static constexpr auto BOLD_BLUE = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::BLUE, Background::DEFAULT); };
    static constexpr auto BOLD_MAGENTA = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::MAGENTA, Background::DEFAULT); };
    static constexpr auto BOLD_CYAN = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::CYAN, Background::DEFAULT); };
    static constexpr auto BOLD_WHITE = [](const std::string& str) { return getFormatedString(str, Format::BOLD, Foreground::WHITE, Background::DEFAULT); };

};  // class ColorString

}   // namespace tcolors

#endif // TCOLORS_HPP
