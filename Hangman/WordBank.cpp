#include "WordBank.h"
#include <cstdlib>
#include <ctime>

void WordBank::free() {}

void WordBank::copyFrom(const WordBank& other)
{
	this->word = other.word;
	this->wordCount = other.wordCount;
}

void WordBank::moveFrom(WordBank&& other)
{
	this->word = std::move(other.word);
}

WordBank::WordBank()
{
	this->wordCount = 0;
}

WordBank::WordBank(String nWord, size_t nWordCount) :
	word(nWord), wordCount(nWordCount)
{
}

WordBank::~WordBank()
{
	free();
}

WordBank::WordBank(const WordBank& other)
{
	copyFrom(other);
}

WordBank WordBank::operator=(const WordBank& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

WordBank::WordBank(WordBank&& other) noexcept
{
	moveFrom(std::move(other));
}

WordBank& WordBank::operator=(WordBank&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

void WordBank::addNewWords(std::fstream& bank)
{
	bank.open("filename.txt", std::ios::in | std::ios::out | std::ios::app);

	if (!bank.is_open()) {
		throw std::runtime_error("Can't open username.txt file");
	}

	
	bank << "House;Bulgaria;Soccer;Space:Hardword;";
	this->wordCount = this->wordCount+5;
	
}

void WordBank::addWord(std::fstream& bank) {
	// Ensure the file is opened in append mode
	bank.open("filename.txt", std::ios::in | std::ios::out | std::ios::app);

	if (!bank.is_open()) {
		throw std::runtime_error("Can't open username.txt file");
	}

	// Write the new word to the file
	bank << this->word << ";";
	++this->wordCount;

	// Go to the beginning of the file to read and update the word count
	bank.seekg(0, std::ios::beg);
	String currWordCount;
	char ch;

	// Read the current word count
	while (bank.get(ch) && ch != ':') {
		currWordCount += ch;
	}

	if (currWordCount.getSize() == 0) {
		throw std::runtime_error("Failed to read the current word count.");
	}

	// Increment the current word count
	int value = atoi(currWordCount.getText());
	value += 1;
	this->wordCount = static_cast<size_t>(value);
	char buffer[10];
	std::sprintf(buffer, "%d", value);
	currWordCount = buffer;

	// Write the updated word count to the file
	bank.seekp(0, std::ios::beg);
	bank.write(currWordCount.getText(), currWordCount.getSize());
	bank.put(':'); // Ensure the colon is written back

	// Verify the operation
	bank.seekg(0, std::ios::beg);
	String verifyWordCountStr;
	while (bank.get(ch) && ch != ':') {
		verifyWordCountStr += ch;
	}

	int verifyWordCount = atoi(verifyWordCountStr.getText());

	if (verifyWordCount != wordCount) {
		throw std::runtime_error("Mismatch between word count in file");
	}

	bank.close();
}

void WordBank::removeWord(String& word, std::fstream& bank)
{
	bank.std::ios::beg;

	if (!bank.is_open()) {
		throw "Can't open wordbank file";
	}

	//fill string with file content, not very efficient way
	String fileContent;
	char ch;
	while (!bank.eof())
	{
		bank.get(ch);
		fileContent += ch;
	}

	for (size_t i = 0; i < fileContent.getSize(); ++i)
	{
		for (size_t j = 0; j < fileContent.getSize(); ++j)
		{
			if (fileContent[i + j] == word[j])
			{
				if (word[j] == word.getSize() - 1)
				{
					//remove the chars before it untill word.getSize() and break
				}
				continue;
			}

		}
	}


	bank.close();
}

void WordBank::getRandomWord(std::fstream& bank)
{

	int x = static_cast<int>(time(0));
	srand(x);

	if (this->wordCount == 0)
	{
		throw "No words in bank, add words to play";
		return;
	}
	int wordindex = 1 + rand() % this->wordCount;
	

	bank.open("wordbank.txt", std::ios::in | std::ios::out);

	if (!bank.is_open()) {
		throw "Can't open wordbank.txt file";
	}

	char ch;
	int curindex = 0;

	while (bank.get(ch)) {
		if (ch == ';') {

			curindex++;

			if (curindex == wordindex) {
				bank.seekg(-1);

				while (bank.get(ch) && ch != ';') {
					this->word += ch;
				}
				break;
			}
		}
	}

	bank.close();
}

void WordBank::setWord(const String& word)
{
	this->word = word;
}

String WordBank::getWord()
{
	return this->word;
}

size_t WordBank::getWordCount()
{
	return this->wordCount;
}

