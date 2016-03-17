#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <map>
#include "../dependencies/sqlite3.h"

class Database
{
	sqlite3 *db;
	std::vector< std::map<std::string, std::string> > results;
	
	public:
		Database(const char *filename);
		~Database();
		
		void query(const char *q);
		void query(const char *q, std::vector< std::map<std::string, std::string> > &result);
		
		void pushRow(std::map<std::string, std::string> row);
};

#endif