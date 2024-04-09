#include "mysqlConnect.h"
#include <iostream>
//#include <jdbc/mysql_driver.h>
//#include <jdbc/mysql_connection.h>
//#include <mysql/jdbc.h>
#include <mysql.h>
#include <random>
#include <string>
#include <cstring>
#include <csignal>
void MysqlConnect::connectFun() {
	MYSQL mysql;		//数据库句柄
	MYSQL_RES* res;		//查询结果集
	MYSQL_ROW row;		//记录结果集

	mysql_init(&mysql);	//初始化数据库

	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//设置字符编码

	//连接数据库
	if (mysql_real_connect(&mysql, "127.0.0.1", "hl", "20170808xll", "hl", 3306, NULL, 0) == NULL) {
		std::cout << "数据库连接失败，错误原因：" << mysql_error(&mysql) << std::endl;
		exit(-1);
	}
	else {
		std::cout << "数据库连接成功啦！！！" << std::endl;
	}
	//插入数据,id是key，要唯一
	int id = 22;
	std::string sqlStr = "INSERT INTO people (id, name, age) VALUES (" + std::to_string(id) + ", 'hjkk', 22)";
	if (mysql_query(&mysql, sqlStr.c_str()) != 0) {
		std::cout << "插入数据失败，错误原因：" << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "插入数据成功！" << std::endl;
	}

	//更新数据
	mysql_query(&mysql, "update people set age = 21 where name = 'hjkk'");

	//删除数据
	if (mysql_query(&mysql, "DELETE FROM people WHERE name = 'huanglin'") != 0) {
		std::cout << "删除数据失败，错误原因：" << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "删除数据成功！" << std::endl;
	}

	//查询
	mysql_query(&mysql, "select * from people");

	//获取结果集
	res = mysql_store_result(&mysql);

	//给row赋值，判断row是否为空，不为空就打印数据
	while (row = mysql_fetch_row(res))
	{
		std::cout << "姓名 " << row[1] << " 年龄 " << row[2] << std::endl;
	}

	//释放结果集
	mysql_free_result(res);

	//关闭数据库
	mysql_close(&mysql);

	system("pause");
	/*sql::mysql::MySQL_Driver *driver;
	sql::Connection* con;
	driver = sql::mysql::get_mysql_driver_instance();
	std::cout << "1";
	con = driver->connect("tcp://127.0.0.1:3306", "hl", "20170808xll");
	std::cout << "2";*/
	/*
	
	//选择数据库
	con->setSchema("hl");
	//插入数据
	sql::Statement* stmt = con->createStatement();

	stmt->execute("INSERT INTO people (id, name, age) VALUES (1, 'xulinlin', 22)");

	delete stmt;
	delete con;

	*/

	//try {
	//	con = driver->connect("tcp://localhost:3306", "hl", "20170808xll");
	//	//选择数据库
	//	con->setSchema("hl");
	//	//插入数据
	//	sql::Statement* stmt = con->createStatement();

	//	stmt->execute("INSERT INTO people (id, name, age) VALUES (1, 'xulinlin', 22)");

	//	delete stmt;
	//	delete con;
	//}
	//catch (const std::bad_alloc& e) {
	//	std::cout << "Memory allocation error: " << e.what() << std::endl;
	//}
	//catch (const sql::SQLException& e) {
	//	std::cout << "MySQL error: " << e.what() << std::endl;
	//}
	
	
}
