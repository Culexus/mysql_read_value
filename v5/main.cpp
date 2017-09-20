#include <iostream>
#include <conio.h>
#include <string>
#include "sqlite3.h"

sqlite3* db_pointer;
sqlite3_stmt* statement;
int return_code;
char* query = "SELECT value1 FROM test WHERE value2 == 3;";

int main()
{
	printf("start\n");

	return_code = sqlite3_open("test.db", &db_pointer);
	printf("openned with code: %i\n", return_code);

	return_code = sqlite3_prepare(db_pointer, query, -1, &statement, 0);
	printf("prepare code: %i\n", return_code);
	{
		int total_columns = sqlite3_column_count(statement);
		printf("columns: %i\n", total_columns);
		int res = 0;
		while (true)
		{
			res = sqlite3_step(statement);
			if (res == SQLITE_ROW)
			{
				for (int i = 0; i < total_columns; i++)
				{
					char* s = (char*)sqlite3_column_text(statement, i);
					printf("value: %s\n", s);
				}
			}
			if (res == SQLITE_DONE || res == SQLITE_ERROR)
			{
				printf("break\n");
				break;
			}
		}
	}

	return_code = sqlite3_close(db_pointer);
	printf("closef with code: %i\n", return_code);

	printf("end\n");
	getchar();
	return 0;
}