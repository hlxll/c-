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
	MYSQL mysql;		//���ݿ���
	MYSQL_RES* res;		//��ѯ�����
	MYSQL_ROW row;		//��¼�����

	mysql_init(&mysql);	//��ʼ�����ݿ�

	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");	//�����ַ�����

	//�������ݿ�
	if (mysql_real_connect(&mysql, "127.0.0.1", "hl", "20170808xll", "hl", 3306, NULL, 0) == NULL) {
		std::cout << "���ݿ�����ʧ�ܣ�����ԭ��" << mysql_error(&mysql) << std::endl;
		exit(-1);
	}
	else {
		std::cout << "���ݿ����ӳɹ���������" << std::endl;
	}
	//��������,id��key��ҪΨһ
	int id = 22;
	std::string sqlStr = "INSERT INTO people (id, name, age) VALUES (" + std::to_string(id) + ", 'hjkk', 22)";
	if (mysql_query(&mysql, sqlStr.c_str()) != 0) {
		std::cout << "��������ʧ�ܣ�����ԭ��" << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "�������ݳɹ���" << std::endl;
	}

	//��������
	mysql_query(&mysql, "update people set age = 21 where name = 'hjkk'");

	//ɾ������
	if (mysql_query(&mysql, "DELETE FROM people WHERE name = 'huanglin'") != 0) {
		std::cout << "ɾ������ʧ�ܣ�����ԭ��" << mysql_error(&mysql) << std::endl;
	}
	else {
		std::cout << "ɾ�����ݳɹ���" << std::endl;
	}

	//��ѯ
	mysql_query(&mysql, "select * from people");

	//��ȡ�����
	res = mysql_store_result(&mysql);

	//��row��ֵ���ж�row�Ƿ�Ϊ�գ���Ϊ�վʹ�ӡ����
	while (row = mysql_fetch_row(res))
	{
		std::cout << "���� " << row[1] << " ���� " << row[2] << std::endl;
	}

	//�ͷŽ����
	mysql_free_result(res);

	//�ر����ݿ�
	mysql_close(&mysql);

	system("pause");
	/*sql::mysql::MySQL_Driver *driver;
	sql::Connection* con;
	driver = sql::mysql::get_mysql_driver_instance();
	std::cout << "1";
	con = driver->connect("tcp://127.0.0.1:3306", "hl", "20170808xll");
	std::cout << "2";*/
	/*
	
	//ѡ�����ݿ�
	con->setSchema("hl");
	//��������
	sql::Statement* stmt = con->createStatement();

	stmt->execute("INSERT INTO people (id, name, age) VALUES (1, 'xulinlin', 22)");

	delete stmt;
	delete con;

	*/

	//try {
	//	con = driver->connect("tcp://localhost:3306", "hl", "20170808xll");
	//	//ѡ�����ݿ�
	//	con->setSchema("hl");
	//	//��������
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
