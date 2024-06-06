#include "String.h"
#pragma warning (disable : 4996)
const size_t MAX_SIZE = 1024;

void String::copy(const String& other)
{
	text = new char[other.size + 1];
	strcpy(text, other.text);
	size = other.size;
}

void String::free()
{
	delete[] text;
}

void String::move(String&& other)
{
	text = other.text;
	other.text = nullptr;
	size = other.size;
}

void String::concat(const String& other)
{
	this->size = this->size + other.size;
	char* newtext = new char[this->size + 1];

	strcpy(newtext, this->text);
	strcat(newtext, other.text);
	delete[] this->text;

	this->text = newtext;
}

void String::resize(size_t newSize)
{
    char* newText = new char[newSize + 1];
    if (text) {
        strncpy(newText, text, newSize);
    }
    newText[newSize] = '\0';

    delete[] text;
    text = newText;
    size = newSize;
}

String::String() : text(nullptr), size(0) {}

String::String(const std::string& str) {
	size = str.size();
	text = new char[size + 1];
	strcpy(text, str.c_str());
}

String::String(const char* text)
{
	this->size = strlen(text);

	this->text = new char[size + 1];
	strcpy(this->text, text);
}

String::String(const String& other)
{
	copy(other);
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

String::~String()
{
	free();
}

char* String::getText() const
{
	return this->text;
}

size_t String::getSize() const
{
	return size;
}

char String::operator[](size_t index) const
{
	if (index >= size)
		throw "Index out of bound";

	return text[index];
}

char& String::operator[](size_t index)
{
	if (index >= size)
		throw "Index out of bound";

	return text[index];
}

String::String(String&& other) noexcept
{
	move(std::move(other));
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other)
	{
		free();
		move(std::move(other));
	}

	return *this;
}

String& String::operator+=(const String& other)
{
	this->concat(other);
	return *this;
}

String& String::operator+=(char c)
{
	char* newText = new char[size + 2];
	std::strcpy(newText, text);
	newText[size] = c;
	newText[size + 1] = '\0';
	delete[] text;
	text = newText;
	++size;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	os << str.text;
	return os;
}

std::istream& operator>>(std::istream& is, String& str)
{
	char buff[MAX_SIZE];

	is >> buff;
	str = buff;

	return is;
}

String operator+(const String& lhs, const String& rhs)
{
	String result(lhs);
	result.concat(rhs);

	return result;
}

bool operator==(const String& lhs, const String& rhs)
{
	return strcmp(lhs.text, rhs.text) == 0;
}

bool operator<(const String& lhs, const String& rhs)
{
	return strcmp(lhs.text, rhs.text) < 0;
}

bool operator>(const String& lhs, const String& rhs)
{
	return strcmp(lhs.text, rhs.text) > 0;
}

bool operator<=(const String& lhs, const String& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(const String& lhs, const String& rhs)
{
	return  !(lhs < rhs);
}

bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}