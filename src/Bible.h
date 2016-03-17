#ifndef BIBLE_H
#define BIBLE_H

#include <cstdio>
#include <cstdlib>
#include <string>
#include "Database.h"

class Bible
{
	Database db;
	
	char query[1024];
	std::vector< std::map<std::string, std::string> > result;
	
	public:
		Bible(const char *filename = "resources/bible.sqlite");
		std::string getVerse(int book, int chapter, int verse);
		std::string getVerse(std::string book, int chapter, int verse);
		int getBookId(std::string book);
};

#endif
