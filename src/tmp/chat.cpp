
#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace std;

void testsql(void)
{
int test_int1;
string test_string1;
string test_string2;

try {
sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

driver = get_driver_instance();
con = driver->connect("tcp://127.0.0.1:3306", "root", "xxxx");
con->setSchema("factions");

stmt = con->createStatement();
res = stmt->executeQuery("SELECT accountid, account_name, account_password FROM accounts WHERE accountid = 7");

while (res->next())
{
test_int1 = res->getInt(1);
test_string1 = res->getString(2);
test_string2 = res->getString(3);

cout << "this is the test integer : " << test_int1 << endl;
cout << "this is the test username : " << test_string1 << endl;
cout << "this is the test password : " << test_string2 << endl;
cout << "will it allow me to go back one entry? : " << res->getString(1) << endl;
cout << res->getString(1) << endl;
}

delete res;
delete stmt;
delete con;

} catch (sql::SQLException &e) {
cout << "# ERR: SQLException in " << __FILE__;
cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
cout << "# ERR: " << e.what();
cout << " (MySQL error code: " << e.getErrorCode();
cout << ", SQLState: " << e.getSQLState() << " )" << endl;
}

cout << endl;
}
