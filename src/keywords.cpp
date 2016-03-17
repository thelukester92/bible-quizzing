#include <vector>
#include <map>
#include <iostream>
#include "Database.h"
using namespace std;

int main()
{
	Database db("resources/bible.sqlite");
	vector<map<string, string> > result;
	
	db.query("SELECT * FROM verses WHERE book = 60", result);
	for(size_t i = 0; i < result.size(); i++)
	{
		cout << "1 Peter\t" << result[i]["chapter"] << "\t" << result[i]["verse"] << "\t" << result[i]["text"] << endl;
	}
	
	return 0;
}
