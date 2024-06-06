#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib> //for system
#include <cstdio>

#include "String.h"
#include "Users.h"
#include "WordBank.h"


#define skip std::cout<<std::endl;

//FORMAT OF FILES
//username.txt: *score*:word1;word2;wood3...         FOR ADDED WORDS CAN BE CONFIGURED MANUALLY 
//users.txt:username:* email:* password:* score:*    COLLECTS USER DATA
//save.txt:

bool logged = false;
bool running = true;
bool inGame = false;
String command;
std::fstream filename("wordbank.txt");
Users User;
WordBank Bank("Smoke", 1);


void clearConsole(); //I didn't write this func

void printStartFunctions();
void printMenu(); //after logging in
void printScreen(const String& guessed, const size_t& index, const String& mask); //combines the print funcs
void printImage(const size_t& index = 0);
void printMask(const String& mask);
void printGuessedLetters(const String& guessed);

void registerUser();
void createFile(const String& username);
bool saveGameToFile(std::fstream& save, const String& mask, const String& wordToGuess, const String& guessed, const size_t& index);

//core funcs
String getRandomWord(std::fstream bank);
std::pair<bool, size_t> inWord(const String& word, char ch); //this is when player submits char
bool solved(const String& mask);
void gaming(); //the actual game logic
void getCommand(const String& command)
{
    if (logged == false)
    {
        if (strcmp(command.getText(), "reg") == 0)
        {
            try
            {
                registerUser();
                //createFile(User.getUsername());

                Bank.addNewWords(filename);
               
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            if (logged)LOG("Logged");
            if (!logged)LOG("Couldn't log in user");
            
        }

        if (strcmp(command.getText(), "login") == 0)
        {
            std::cout << "Input username: ";
            String username;
            std::cin >> username;

            std::cout << "Input password: ";
            String password;
            std::cin >> password;

            if (User.login(username, password))
            {
                logged = true;
            }
            else
            {
                std::cout << "Wrong details" << std::endl;
                throw "Couldn't log in after giving data to login function";
            }
        }

        if (strcmp(command.getText(), "forgot") == 0)
        {
            std::cout << "Input username: ";
            String username;
            std::cin >> username;

            std::cout << "Input email: ";
            String email;
            std::cin >> email;

            if (User.forgotPassword(username, email))
            {
                logged = true;
            }
            else
            {
                throw "Couldn't log in after giving data to login function";
            }
        }

        if (strcmp(command.getText(), "quit") == 0)
        {
            running = false;
            return;
        }

    }

    if (logged)
    {
        if (strcmp(command.getText(), "score") == 0)
        {
            User.printLeaderboard();
        }

        if (strcmp(command.getText(), "add") == 0)
        {
            LOG("");
            std::cout << "Input word to add: ";
            String word;
            std::cin >> word;
            Bank.setWord(word);
            Bank.addWord(filename);
        }

        if (strcmp(command.getText(), "remove") == 0)
        {
            std::cout << "Input word to remove: ";
            String word;
            std::cin >> word;
            Bank.removeWord(word, filename);
        }

        if (strcmp(command.getText(), "quit") == 0)
        {
            running = false;
            return;
        }

        if (strcmp(command.getText(), "load") == 0)
        {

        }

        if (strcmp(command.getText(), "start") == 0)
        {
            gaming();
        }

        if (strcmp(command.getText(), "help") == 0)
        {
            printMenu();
        }
    }
}

int main()
{
    while (running)
    {
        if (logged)
        {
            printMenu();
        }
        if (!logged)
        {
            clearConsole();
            printStartFunctions();
        }
        std::cout << "Input command or type 'help': ";
        std::cin >> command;
        getCommand(command);
        clearConsole();

        if (!running)break;
    }
    return 0;
}

//funcs that print stuff
void clearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void printStartFunctions()
{
    LOG("login #username# #password# - Login");
    skip;
    LOG("reg #username# #email# #password# - Register");
    skip;
    LOG("forgot #username# #email# - Forgot password");
    skip;
    LOG("quit - Quit Game");
    skip;
}
void printMenu()
{
    LOG("start - Starts new game");
    LOG("score - Shows leaderboard");
    LOG("quit - Quit Game");
    LOG("remove - Remove word");
    LOG("save - Saves current play");
    LOG("load - Loads saves");
    LOG("add - Adds new word to the Word Bank file");
}
void printImage(const size_t& index)
{
    {
        switch (index)
        {
        case 0:break;

        case 1:
            LOG("__________________");
            break;

        case 2:
            LOG("   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "___|____________");
            break;

        case 3:
            LOG("    --------\n"
                "   |        |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "___|____________");
            break;

        case 4:
            LOG("    --------\n"
                "   |        |\n"
                "   |        O\n"
                "   |        |\n"
                "   |        |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "___|____________");
            break;

        case 5:
            LOG("    --------\n"
                "   |        |\n"
                "   |        O\n"
                "   |       \\|/\n"
                "   |        |\n"
                "   |\n"
                "   |\n"
                "   |\n"
                "___|____________");
            break;

        case 6:
            LOG("    --------\n"
                "   |        |\n"
                "   |        O\n"
                "   |      \\ | /\n"
                "   |        |\n"
                "   |       / \\\n"
                "   |\n"
                "   |\n"
                "___|____________");
            break;

        default:
            LOG("Invalid stage index.");
            break;
        }
    }
}
void printScreen(const String& guessed, const size_t& index, const String& mask)
{
    clearConsole();
    printMask(mask);
    printGuessedLetters(guessed);
    printImage(index);
}
void printMask(const String& mask)
{
    for (size_t i = 0; i < mask.getSize(); i++)
    {
        std::cout << toupper(mask[i]) << " ";
    }
    std::cout << std::endl;
}
void printGuessedLetters(const String& guessed)
{
    std::cout << "Guessed letters: ";
    for (size_t i = 0; i < guessed.getSize(); i++)
    {
        if (i == 10 || i == 17 || i == 20)std::cout << std::endl;
        std::cout << toupper(guessed[i]) << " ";
    }
    std::cout << std::endl;
}


//files and checks
void registerUser()
{
    {
        std::cout << "Input username: ";
        String username;
        std::cin >> username;

        std::cout << "Input email: ";
        String email;
        std::cin >> email;

        std::cout << "Input password: ";
        String password;
        std::cin >> password;

        Users newUser(username, email, password, 0);
        newUser.addUser(username, password, email);  //write data in file
        if (newUser.login(username, password))logged = true; //check data in file
        else {
            throw "Couldn't log in after giving data to login function";
        }
        User = newUser;
        

    }
}
void createFile(const String& username) {
    size_t usernameLength = username.getSize();

    LOG(usernameLength);
    LOG(logged);

    String newfilename;
    newfilename.resize(usernameLength + 4); // +4 for ".txt" and '\0'
    strcpy(newfilename.getText(), username.getText());
    strcat(newfilename.getText(), ".txt");

    // Close the file stream if it is open
    if (filename.is_open()) {
        filename.close();
    }

    // Rename the file (assuming "name.txt" is the old name)
    if (std::rename("name.txt", newfilename.getText()) != 0) {
        std::perror("Error renaming file");
        throw std::runtime_error("Failed to rename file");
    }

    // Open the file with the new name
    filename.open(newfilename.getText(), std::ios::out | std::ios::in | std::ios::trunc);
    if (!filename.is_open()) {
        throw std::runtime_error("Can't create username.txt file");
    }

    filename << "00:";
    filename.close();
}
bool saveGameToFile(std::fstream& save, const String& mask, const String& wordToGuess, const String& guessed, const size_t& index)
{
    save.std::ios::out;

    if (!save.is_open()) {
        throw "Couldn't open file";
        return false;
    }

    save << wordToGuess << std::endl;
    save << mask << std::endl;
    save << guessed << std::endl;
    save << index << std::endl;

    save.close();
    return true;
}
String getRandomWord(std::fstream bank)
{
    int x = static_cast<int>(time(0));
    srand(x);
    String word;
    size_t size = word.getSize();   

    int wordindex = 1 + rand() % Bank.getWordCount();

    bank.std::ios::beg;

    if (!bank.is_open()) {
        throw "Can't open username.txt file";
    }

    char ch;
    int curindex = 0;

    while (bank.get(ch)) {
        if (ch == ';') {

            curindex++;

            if (curindex == wordindex - 1) { //-1 cuz we count word; word1; word2; ...
                bank.seekg(-1, std::ios::cur); // possible to get the ';' in the word

                while (bank.get(ch) && ch != ';') {
                    word += ch; // !
                }
                break;
            }
        }
    }

    bank.close();
    return word;
}

std::pair<bool, size_t> inWord(const String& word, char ch) {
    for (size_t i = 0; i < word.getSize(); ++i) {
        if (word[i] == ch) {
            return std::make_pair(true, i);
        }
    }
    return std::make_pair(false, static_cast<size_t>(0));
}
bool solved(const String& mask)
{
    char ch = '_';
    for (size_t i = 0; i < mask.getSize(); i++)
    {
        if (mask[i] == ch)return false;
    }
    return true;
}
void gaming()
{
    inGame = true;
    String wordToGuess;
    String guessed;
    guessed = "";
    String mask;
    mask = "";
    size_t index = 0; //how many mistakes
    char ch;
    bool found = false;

    //Bank.getRandomWord(filename);
    //wordToGuess = Bank.getWord();
        
    wordToGuess = "House";
    size_t size = wordToGuess.getSize();
    while (!found)
    {
        printScreen(guessed, index, mask);

        std::cout << "Pick a letter-- > ";
        std::cin >> ch;

        if (ch == '#')
        {
            String toNameFile;
            std::cout << "Enter name of save file: ";
            std::cin >> toNameFile;

            toNameFile = strcat(toNameFile.getText(), ".txt");

            std::fstream save(toNameFile.getText(), std::ios::out, std::ios::trunc);

            if (!save.is_open()) {
                throw "Couldn't open file";
                continue;
            }
            save.close();

            if (saveGameToFile(save, mask, wordToGuess, guessed, index))
            {
                LOG("Save successful !");
            }
            else
            {
                LOG("Problem while saving.");
                continue;
            }

                
        }

        guessed += ch;
        auto pair = inWord(wordToGuess, ch);

        if (!pair.first)
        {
            ++index;
        }
        if (index > 6)
        {
            std::cout << "Sorry, you struck out.";
            inGame = false;
            break;
        }
        else
        {
            if (pair.first)
            {
                mask[pair.second] = ch;
            }
            found = solved(mask);
        }

        if (found)
        {
            std::cout << "Congratulations, you won !";
            User.increaseScore();
            inGame = false;
            break;
        }
    }
}

