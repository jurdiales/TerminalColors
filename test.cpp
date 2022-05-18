#include <iostream>
#include "tcolors.hpp"

using namespace std;
using namespace tcolors;

int main()
{
    // Create a ColorString
    ColorString redString("Hello world!", Foreground::RED, Background::WHITE);
    cout << redString << endl;

    // ColorString predefined
    cout << ColorString::RED("Hello world!") << endl;
    cout << ColorString::BOLD_RED("Hello world!") << endl;
    cout << ColorString::BLUE("Hello world!") << endl;
    cout << ColorString::BOLD_BLUE("Hello world!") << endl;

    cout << ColorString::COLORIZE("Hello world!", Foreground::BLACK, Background::YELLOW) << endl;
    cout << ColorString::FORMATIZE("Hello world!", Format::ITALIC, Foreground::CYAN) << endl;

    Modifier br = Modifier(Format::ITALIC, Foreground::YELLOW);
    cout << br << "Hello world!" << Modifier::DEFAULT << endl;

    cout << "Hello World!" << endl;

    // Foreground
    cout << ColorString::COLORIZE("Hello world!", Foreground::RED) << endl;
    // Foreground and backgound
    cout << ColorString::COLORIZE("Hello world!", Foreground::RED, Background::BLACK) << endl;

    // Only Format
    cout << ColorString::FORMATIZE("Hello world!", Format::BOLD) << endl;
    // Format and Foreground
    cout << ColorString::FORMATIZE("Hello world!", Format::BOLD, Foreground::YELLOW) << endl;
    // Format, Foreground and Background
    cout << ColorString::FORMATIZE("Hello world!", Format::BOLD, Foreground::YELLOW, Background::CYAN) << endl;

    return 0;
}
