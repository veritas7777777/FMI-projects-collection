#ifndef WORDBANK_H
#define WORDBANK_H
#pragma warning(disable:4996)
#define LOG(x) std::cout<< x << std::endl;

#include "String.h"
#include <fstream>
#include <iostream>

class WordBank
{
private:
	String word;
	size_t wordCount;

	void free();
	void copyFrom(const WordBank& other);
	void moveFrom(WordBank&& other);

public:
	WordBank();
	WordBank(String Word, size_t WordCount);
	~WordBank();
	WordBank(const WordBank& other);
	WordBank operator=(const WordBank& other);

	WordBank(WordBank&& other) noexcept;
	WordBank& operator=(WordBank&&) noexcept;

	void addNewWords(std::fstream& bank);
	void addWord(std::fstream& bank);
	void removeWord(String& word, std::fstream& bank);
	void getRandomWord(std::fstream& bank);

	void setWord(const String& word);
	String getWord();
	size_t getWordCount();

};
#endif