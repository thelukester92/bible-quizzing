#include "Database.h"

Database::Database(const char *filename)
{
	sqlite3_open(filename, &db);
}

Database::~Database()
{
	sqlite3_close(db);
}

int callback(void *a, int argc, char **argv, char **columnNames)
{
	std::map<std::string, std::string> row;
	for(int i = 0; i < argc; i++)
	{
		if(argv[i] != NULL)
		{
			row[columnNames[i]] = argv[i];
		}
		else
		{
			row[columnNames[i]] = "";
		}
	}
	
	((Database *)a)->pushRow(row);
	return 0;
}

void Database::query(const char *q)
{
	char *err = NULL;
	int rc;
	
	results.clear();
	rc = sqlite3_exec(db, q, &callback, (void *)this, &err);
	
	if(rc != SQLITE_OK)
	{
		printf("An error occurred: %s\n", err);
		sqlite3_free(err);
		exit(1);
	}
}

void Database::query(const char *q, std::vector< std::map<std::string, std::string> > &result)
{
	query(q);
	result = results;
}

void Database::pushRow(std::map<std::string, std::string> row)
{
	results.push_back(row);
}
