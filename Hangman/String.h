#ifndef STRING_H
#define STRING_H
#pragma warning(disable:4996)
#include <cstring>
#include <fstream>
#include <iostream>

class String
{
private:
	char* text;
	size_t size;

	void copy(const String& other);
	void free();
	void move(String&& other);
	void concat(const String& other);
	

public:
	String();
	String(const std::string& str);
	String(const char* text);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	char* getText() const;
	size_t getSize() const;

	char operator[](size_t index) const;
	char& operator[](size_t index);

	String(String&& other) noexcept;
	String& operator=(String&& other) noexcept;

	String& operator+=(const String& other);
	String& operator+=(char c);

	friend std::ostream& operator<<(std::ostream& os, const String& other);
	friend std::istream& operator>>(std::istream& os, String& other);
	friend String operator+(const String& lhs, const String& rhs);
	friend bool operator==(const String& lhs, const String& rhs);
	friend bool operator<(const String& lhs, const String& rhs);
	friend bool operator>(const String& lhs, const String& rhs);
	friend bool operator<=(const String& lhs, const String& rhs);
	friend bool operator>=(const String& lhs, const String& rhs);
	friend bool operator!=(const String& lhs, const String& rhs);

	void resize(size_t newSize);
};

#endif // !STRING_H