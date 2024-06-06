#ifndef USERS_H
#define USERS_H
#pragma warning(disable:4996)
#include <fstream>
#include <iostream>
#include "String.h"

#define LOG(x) std::cout<< x << std::endl;

class Users
{
private:
	String password;
	String username;
	String email;
	int score;

	void free();
	void copyFrom(const Users& other);
	void moveFrom(Users&& other);

	void sortLeaderboard(char** leaderboard, size_t numLines);

public:

	Users();
	Users(const String& nUsername, const String& nEmail, const String& nPassword, int nScore);
	~Users();
	Users(const Users& other);
	Users operator=(const Users& other);
	Users(Users&& other) noexcept;
	Users& operator=(Users&& other) noexcept;


	void printLeaderboard();
	void addUser(String& gusername, String& gpassword, String& gemail); //register, can return the obj
	bool login(String& username, String& password);
	bool forgotPassword(String& username, String& email); //also changes the old password

	String getPassword();
	String getUsername();
	String getEmail();
	int getScore();

	void increaseScore();
};

#endif // !USERS_H