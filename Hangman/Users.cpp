#include "Users.h"
#
void Users::free() {
}

void Users::copyFrom(const Users& other) {
    username = other.username;
    email = other.email;
    password = other.password;
    score = other.score;
}

void Users::moveFrom(Users&& other) {
    username = std::move(other.username);
    email = std::move(other.email);
    password = std::move(other.password);
    score = other.score;
}

Users::Users() 
{
    score = 0;
}

Users::Users(const String& nUsername, const String& nEmail, const String& nPassword, int nScore)
    : username(nUsername), email(nEmail), password(nPassword), score(nScore) {}

Users::~Users() {
    free();
}

Users::Users(const Users& other) {
    copyFrom(other);
}

Users Users::operator=(const Users& other) {
    if (this != &other) {
        free();
        copyFrom(other);
    }
    return *this;
}

Users::Users(Users&& other) noexcept {
    moveFrom(std::move(other));
}

Users& Users::operator=(Users&& other) noexcept {
    if (this != &other) {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void Users::printLeaderboard()
{
    //open file and count users (each user in on separate line)
    std::fstream users("users.txt", std::ios::beg);

    if (!users.is_open()) {
        std::cerr << "Can't open user file" << std::endl;
        return;
    }

    char ch;
    unsigned newLineCounter = 0;
    while (users.get(ch)) { //count \n
        if (ch == '\n') {
            newLineCounter++;
        }
    }

    //create, allocate, make logic for leaderboard
    char** leaderboard = new char* [newLineCounter + 1]; //might not needed
    for (size_t i = 0; i < newLineCounter; ++i) {
        leaderboard[i] = new char[1024];
    }

    users.clear();
    users.seekg(0, std::ios::beg);

    char line[1024];
    char buffer[1024];
    size_t index = 0;
    size_t index2 = 0;
    while (users.getline(line, 1024)) {


        char* usernameptr = strstr(line, "username:") + 9;
        char* scoreptr = strstr(line, "score:") + 6;
        if (usernameptr && scoreptr) {

            size_t usernameLen = strcspn(usernameptr, " ");
            size_t scoreLen = strcspn(scoreptr, " ");
            size_t total = usernameLen + scoreLen + 2;

            usernameptr[usernameLen + 1] = '\0';
            scoreptr[scoreLen + 1] = '\0';

            //warning buffer overrun
            leaderboard[index] = new char[total];
            //warning reading invalid data
            strcpy(leaderboard[index], usernameptr);
            strcat(leaderboard[index], " ");
            strcat(leaderboard[index], scoreptr);
            ++index;
        }
    }

    sortLeaderboard(leaderboard, newLineCounter);

    for (size_t i = 0; i < newLineCounter; ++i) { //print
        LOG(leaderboard[i]);
    }


    for (size_t i = 0; i < newLineCounter; ++i) { //free
        delete[] leaderboard[i];
    }
    delete[] leaderboard;

    users.close();

}

void Users::addUser(String& gusername, String& gpassword, String& gemail)
{
    std::ofstream users("users.txt", std::ios::app);

    if (!users.is_open())
    {
        throw "Can't open user file";
    }

    users << "username:" << gusername.getText() << " ";
    users << "email:" << gemail.getText() << " ";
    users << "password:" << gpassword.getText() << " ";
    users << "score:0" << std::endl;

    users.close();

    Users Player1(gusername, gemail, gpassword, 0);

}

bool Users::login(String& username, String& password)
{
    std::ifstream users("users.txt");
    if (!users.is_open()) {
        throw "Can't open user file";
    }

    char line[1024];

    while (users.getline(line, 1024)) {

        char* one = strstr(line, username.getText());
        char* two = strstr(line, password.getText());

        if (one != NULL && two != NULL) {
            //make new obj with extracted data


            users.close();
            return true;
        }
    }

    users.close();
    return false;
}

bool Users::forgotPassword(String& username, String& email)
{
    std::fstream users("users.txt", std::ios::out | std::ios::in);
    if (!users.is_open()) {
        throw "Can't open user.txt file";
    }

    char line[1024];
    char endOfoldPassIndicator = ' ';
    while (users.getline(line, 1024)) {

        char* one = strstr(line, username.getText());
        char* two = strstr(line, email.getText());

        if (one != NULL && two != NULL) {

            String newPassword;
            std::cout << "Enter new password: ";
            std::cin >> newPassword;

            char* three = strstr(line, password.getText());
            size_t sizeOfoldPassword = password.getSize();
            size_t indexThree = line - three;

            for (size_t i = 0; i < newPassword.getSize(); i++)
            {
                line[indexThree + i] = newPassword[i];

                if (line[indexThree + i] == endOfoldPassIndicator)
                {
                    line[indexThree + i] += newPassword[i];
                }
            }
            users.seekp(users.tellg() - users.gcount()); //got help by AI for this line
            users << line << '\n';

            users.close();
            return true;
        }
    }

    users.close();
    return false;
}

String Users::getPassword()
{
    return this->password;
}

String Users::getUsername()
{
    return this->username;
}

String Users::getEmail()
{
    return this->email;
}

int Users::getScore()
{
    return this->score;
}

void Users::increaseScore()
{
    this->score + 1;
}

void Users::sortLeaderboard(char** leaderboard, size_t numLines)
{
    for (size_t i = 0; i < numLines - 1; ++i) {
        for (size_t j = 0; j < numLines - i - 1; ++j) {
            char* score1 = strchr(leaderboard[j], ':') + 2; //not sure 
            char* score2 = strchr(leaderboard[j + 1], ':') + 2;

            if (atoi(score1) < atoi(score2)) {
                char* temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}