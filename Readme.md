# TerminalColors

TerminalColors is a C++ only-header library to print formatted text in terminals.

**Requirements**
* C++17 or above.
* A terminal compatible with escape sequences. Otherwise trash will be printed on screen.

## Basic Usage

The simplest way to color a string is by using the function **COLORIZE** of the class **ColorString**:
```CPP
  using namespace tcolors;
  //  Foreground
  std::cout  <<  ColorString::COLORIZE("Hello world!",  Foreground::RED) << std::endl;
  //  Foreground  and  backgound
  std::cout  <<  ColorString::COLORIZE("Hello world!",  Foreground::RED,  Background::BLACK) << std::endl;
  ```

The **ColorString::FORMATIZE** function can be used to format the text:
```CPP
  using namespace tcolors;
  //  Only  Format
  std::cout  <<  ColorString::FORMATIZE("Hello world!",  Format::BOLD)  <<  std::endl;
  //  Format  and  Foreground
  std::cout  <<  ColorString::FORMATIZE("Hello world!",  Format::BOLD,  Foreground::YELLOW)  <<  std::endl;
  //  Format,  Foreground  and  Background
  std::cout  <<  ColorString::FORMATIZE("Hello world!",  Format::BOLD,  Foreground::YELLOW,  Background::CYAN)  <<  std::endl;
```

## Advanced usage

## Format options

The following table shows a list of all available modifiers.

|    Format    | Foreground   | Background   |
| :----------: | :----------: | :----------: |
|DEFAULT       |BLACK         |BLACK         |
|BOLD          |RED           |RED           |
|DIM           |GREEN         |GREEN         |
|ITALIC        |YELLOW        |YELLOW        |
|UNDERLINE     |BLUE          |BLUE          |
|BLINK         |MAGENTA       |MAGENTA       |
|REVERSE       |CYAN          |CYAN          |
|HIDDEN        |LIGHT_GREY    |LIGHT_GREY    |
|RST_BOLD      |DEFAULT       |DEFAULT       |
|RST_DIM       |DARK_GREY     |DARK_GREY     |
|RST_UNDERLINE |LIGHT_RED     |LIGHT_RED     |
|RST_BLINK     |LIGHT_GREEN   |LIGHT_GREEN   |
|RST_REVERSE   |LIGHT_YELLOW  |LIGHT_YELLOW  |
|RST_HIDDEN    |LIGHT_BLUE    |LIGHT_BLUE    |
|              |LIGHT_MAGENTA |LIGHT_MAGENTA |
|              |LIGHT_CYAN    |LIGHT_CYAN    |
|              |WHITE         |WHITE         |

Modifiers starting with "RST_" reset the modifier that follows it. The DEFAULT modifier resets all previous formats/colors to terminal defaults.

