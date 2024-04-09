#pragma once
//在链接器的输入中需要引入E:\install\boost_1_70_0\stage\lib\libboost_filesystem-vc142-mt-gd-x64-1_70.lib文件，
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <boost/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/min.hpp>

#include <boost/algorithm/cxx11/all_of.hpp>

class BoostFileSystem {
public:
	//获取有没有中文
	bool hasChineseCharacters(const std::string& str);
	//打印中文内容，并输出到文件中
	void getChinaText(std::string name);
	//通过地址，获取所有js文件
	void getFileMenu(std::string path);

	//学习filesystem的api
	boost::filesystem::path learnFilesystem(boost::filesystem::path path);
};
class BoostString {
public:
	//学习stringAlgorithm的api
	void stringChange();
};
class BoostRegex {
public:
	//学习正则
	void RegexValue();
};

class BoostThread {
public:
	//学习多线程
	void ThreadProject();
};

//智能指针
class BoostPtr {
public: 
	//作用域指针
	void BoostPtr_scoped();
	//共享指针
	void BoostPtr_shared();
	//介入式指针
	void BoostPtr_Counter();
	//指针容器
	void BoostPtr_model();
};

//函数对象
class funObject {
public:
	//std的bind1st和bind2nd
	void getNewFun();
};

//异步网络编程
class AsynASio {
public:
	//创建服务端
	void createServer();
	//创建客户端socket
	void clientServer();
	//创建ws连接
	void createWs();
};

//存储器,待继续学习？？？？
class AccumulatorLearn {
public:
	void accumulaApi();
};

class AlgorithmApi {
public:
	void allOfAlgor();
};