#pragma once
//������������������Ҫ����E:\install\boost_1_70_0\stage\lib\libboost_filesystem-vc142-mt-gd-x64-1_70.lib�ļ���
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
	//��ȡ��û������
	bool hasChineseCharacters(const std::string& str);
	//��ӡ�������ݣ���������ļ���
	void getChinaText(std::string name);
	//ͨ����ַ����ȡ����js�ļ�
	void getFileMenu(std::string path);

	//ѧϰfilesystem��api
	boost::filesystem::path learnFilesystem(boost::filesystem::path path);
};
class BoostString {
public:
	//ѧϰstringAlgorithm��api
	void stringChange();
};
class BoostRegex {
public:
	//ѧϰ����
	void RegexValue();
};

class BoostThread {
public:
	//ѧϰ���߳�
	void ThreadProject();
};

//����ָ��
class BoostPtr {
public: 
	//������ָ��
	void BoostPtr_scoped();
	//����ָ��
	void BoostPtr_shared();
	//����ʽָ��
	void BoostPtr_Counter();
	//ָ������
	void BoostPtr_model();
};

//��������
class funObject {
public:
	//std��bind1st��bind2nd
	void getNewFun();
};

//�첽������
class AsynASio {
public:
	//���������
	void createServer();
	//�����ͻ���socket
	void clientServer();
	//����ws����
	void createWs();
};

//�洢��,������ѧϰ��������
class AccumulatorLearn {
public:
	void accumulaApi();
};

class AlgorithmApi {
public:
	void allOfAlgor();
};