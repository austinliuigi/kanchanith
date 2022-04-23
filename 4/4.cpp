#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include <utility>
using namespace std;

void printString(string s);
string scramble(string s);
void printGame(string scrambled, string selected);
void play(string s);
void createMap();
void clearScreen();

int main()
{
    string words[] = {"cambodia", "tiger", "huang", "phnom penh", "music", "ares"};
    clearScreen();
    cout << "Welcome! In this game, you will take scrambled words and rearrange them back into their original form.\n"
            "\nAs a clue, each word relates to you, Tan, in some way.\n"
            "\nIf for some reason you ever want to quit the game, hit CTRL-C.\n"
            "\nWhenever you're ready, press enter to start. Good luck!";
    cin.ignore(10000, '\n');
    for (int i = 0; i < (sizeof(words)/sizeof(words[0])); i++)
    {
        play(words[i]);
    }
    createMap();
    clearScreen();
    cout << "Congratulations, you made it to the end of the game!\n"
            "\nYou unlocked a map that shows the location of your gifts.\n"
            "\nTo access it, just view the file 'map.txt' that has been created in your current directory." << endl;
}

void printString(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        cout << char(toupper(s[i])) << " ";
    }
    cout << endl;
}

string scramble(string s)
{
    shuffle(s.begin(), s.end(), random_device());
    return s;
}

void printGame(string scrambled, string selected)
{
    clearScreen();
    printString(scrambled);
    printString(selected);
}

void play(string s)
{
    // Scramble input string
    string scrambled = scramble(s);

    // Create string of underscores
    string underscores = "";
    for (int i = 0; i < scrambled.length(); i++)
        underscores = underscores + "_";

    // Create string to hold user's input
    string selected;

    // Play game
    bool passed = 0;
    while (!passed)
    {
        selected = underscores;
        for (int i = 0; i < s.length(); i++)
        {
            // Print out info
            printGame(scrambled, selected);
            // Get user input
            cout << "\nEnter next character: ";
            string selected_char;
            getline(cin, selected_char);
            if (selected_char.length() != 1)
                i--;
            else
                selected[i] = tolower(selected_char[0]);
        }
        if (selected == s)
        {
            passed = 1;
            printGame(scrambled, selected);
            cout << "\nCorrect! Press enter to continue.";
            cin.ignore(10000, '\n');
        }
        else
        {
            printGame(scrambled, selected);
            cout << "\nSorry, your answer is not correct. Press enter to try again.";
            cin.ignore(10000, '\n');
        }
    }
}

void createMap()
{
    ofstream file;
    file.open("map.txt");
    file << "            |Entrance|\n"
            "            |        |\n"
            "            |        |\n"
            "            |        |\n"
            "            |         ---------------------\n"
            "            |                              |     ------------\n"
            "            |                              |    |            |\n"
            " -----------                              x|    |            |\n"
            "|      x                                   |    |  Bathroom  |\n"
            "|                                          |    |            |\n"
            "|  Kitchen                                 |    |            |\n"
            "|                                           ---- --  -------- -----\n"
            "|                     Living Room\n"
            " -----------\n"
            "            |                               -------  --------------\n"
            " -----------                               |    |              |\n"
            "|     x     |                              |    |              |\n"
            "|           |                              |    |    Blanca    |\n"
            "|  Bedroom  |                              |    |              |\n"
            "|           |                              |    |              |\n"
            "|                                        x |     --------------\n"
            " ------------------------------------------\n";
    file.close();
    return;
}









#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif  // _WIN32
