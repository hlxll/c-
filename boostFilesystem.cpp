#include "boostFilesystem.h"
namespace fs = boost::filesystem;
namespace boostStr = boost::algorithm;
namespace bostAsio = boost::asio;
namespace boostAccu = boost::accumulators;
void coutText(std::string value) {
	std::cout << value << std::endl;
}
bool BoostFileSystem::hasChineseCharacters(const std::string& str) {
	for (char c : str) {
		// �ж��ַ��Ƿ�Ϊ�����ַ�
		if ((c & 0x80) && !(c & 0x40)) {
			return true;
		}
	}

	return false;
}
void BoostFileSystem::getChinaText(std::string folderpath) {
	if (folderpath.length() >= 2 && folderpath.substr(folderpath.length() - 3).compare(".js") == 0) {
		/*std::ifstream readFile(folderpath);
		if (readFile) {
			std::string content((std::istreambuf_iterator<char>(readFile)), std::istreambuf_iterator<char>());
			if (hasChineseCharacters(content)) {
				std::cout << "������" << content << std::endl;
			}
			readFile.close();
		}*/
		std::ifstream readFile;
		readFile.open(folderpath);

		//std::locale utf8_locale("en_US.UTF-8");
		//std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
		//readFile.imbue(utf8_locale);

		std::ofstream writeFile;
		writeFile.open("chinese.txt", std::ios::app);
		//writeFile.imbue(utf8_locale);
		if (readFile.is_open()) {
			std::cout << "�����ļ�������" << folderpath << std::endl;
			writeFile << (folderpath + "\n").c_str();
			std::string data;
			int index = 0;

			int moreLine = -1;
			while (getline(readFile, data)) {
				index++;
				if (data.find("/*") != std::string::npos) {
					//����Ҫ��ע�ͷ�ǰ�����ļ���
					moreLine = 1;
					std::vector<std::string> splitStr;
					boostStr::split(splitStr, data, boostStr::is_any_of("/*"));
					if (splitStr.size() > 0 && hasChineseCharacters(splitStr[0])) {
						if (writeFile.is_open()) {
							writeFile << (std::to_string(index) + splitStr[0] + "\n").c_str();
						}
					}
				}else if (data.find("*/") != std::string::npos) {
					//����Ҫ��ע�ͷ�ǰ�����ļ���
					moreLine = -1;
					std::vector<std::string> splitStr;
					boostStr::split(splitStr, data, boostStr::is_any_of("*/"));
					if (splitStr.size() > 1 && hasChineseCharacters(splitStr[1])) {
						if (writeFile.is_open()) {
							writeFile << (std::to_string(index) + splitStr[0] + "\n").c_str();
						}
					}
				}
				else if (hasChineseCharacters(data) && moreLine == -1) {
					std::string lineIndex = "��" + std::to_string(index) + "��";
					if (data.find("//") != std::string::npos) {
						std::vector<std::string> splitStr;
						boostStr::split(splitStr, data, boostStr::is_any_of("//"));
						//����С�//��ע�ͷ��ţ���ע�ͷ���ǰ������ļ������
						if (splitStr.size() > 0 && hasChineseCharacters(splitStr[0])) {
							if (writeFile.is_open()) {
								writeFile << (std::to_string(index) + splitStr[0] + "\n").c_str();
							}
						}
					}
					else {
						if (writeFile.is_open()) {
							writeFile << (std::to_string(index) + data + "\n").c_str();
						}
					}
				}
			}
		}
		else {
			std::cerr << "Failed to open the file." << std::endl;
		}
		readFile.close();
		writeFile.close();
	}
}
void BoostFileSystem::getFileMenu(std::string folderpath) {
	for (const auto& entry : fs::directory_iterator(folderpath)) {
		if (fs::is_regular_file(entry.path())) {
			getChinaText(folderpath + "/" + entry.path().filename().string());
		}
		else if (fs::is_directory(entry.path())) {
			getFileMenu(folderpath + "/" + entry.path().filename().string());
		}
	}
}
fs::path BoostFileSystem::learnFilesystem(fs::path folderpath) {
	//תΪ����·��
	fs::path absolutepath = fs::absolute(folderpath);
	//boost::system::error_code ec;
	//תΪ��׼���Ĳ����������ӵľ���·��
	/*fs::path canonicalPath = fs::canonical(folderpath, ec);
	if (!ec) {
		std::cout << canonicalPath << std::endl;
	}*/

	//������ַ
	//fs::path copyPath(fs::relative("./hl"));
	//fs::path basePath(fs::relative("./Release"));
	//try {
	//	//����Ŀ¼���´���һ���ļ���Ŀ¼ΪcopyPath��Ŀ¼��
	//	fs::copy(basePath, copyPath);
	//}
	//catch (const boost::filesystem::filesystem_error& ex){
	//	std::cout << ex.what() << std::endl;
	//}


	//boost::filesystem::path targetPath("./Release");     // �滻Ϊʵ��Ŀ��·��
	//boost::filesystem::path symlinkPath("./hl_link");   // �滻ΪҪ�����ķ�������·��

	/*try {
		boost::filesystem::create_symlink(targetPath, symlinkPath);
		std::cout << "Symbolic link created successfully." << std::endl;
	}
	catch (const boost::filesystem::filesystem_error& ex) {
		std::cerr << "Error: " << ex.what() << std::endl;
	}*/
	/*fs::path targetPath2 = "./static";
	fs::path linkPath = "./linkPath";
	try {
		fs::create_hard_link(targetPath2, linkPath);
	}
	catch (const boost::filesystem::filesystem_error& ex) {
			std::cerr << "Error: " << ex.what() << std::endl;
	}*/
	//��ǰ����Ŀ¼��·��
	fs::path currentPath = fs::current_path();

	//���·���Ƿ����
	bool hasPath = fs::exists(currentPath);
	if (hasPath) {
		coutText("����");
		try {
			//c++11��֧�֣�17����
			uintmax_t fileSize = fs::file_size(currentPath);
			coutText(std::to_string(fileSize));
		}
		catch (const fs::filesystem_error& ex) {
			std::cerr << "Error: " << ex.what() << std::endl;
		}
	}
	return absolutepath;
}

void BoostString::stringChange() {
	std::string str = "apple,bananle,china";
	std::vector<std::string> splitStr;
	boostStr::split(splitStr, str, boostStr::is_any_of(","));
	for (const auto& token : splitStr) {
		coutText(token);
	}
	boostStr::to_upper(str);
	coutText(str);
}
void BoostRegex::RegexValue() {
	boost::regex pattern("abc");
	std::string str = "abcasdlkj";
	//����ƥ����
	boost::smatch resourceList;
	bool hasVal = boost::regex_search(str, resourceList, pattern);
	if (hasVal) {
		coutText("����");
		std::cout << resourceList[0] << std::endl;
	}
}

void boostThreadFun() {
	std::cout << "���߳�" << std::endl;
}
void BoostThread::ThreadProject() {
	boost::thread t1(boostThreadFun);
	t1.join();
}

void BoostPtr::BoostPtr_scoped() {
	//��ռһ������,������ָ��
	boost::scoped_ptr<int> i(new int);
	*i = 1;
	std::cout << *i << std::endl;
	//get�������������ַ
	*i.get() = 2;
	std::cout << *i << std::endl;
	//��һ���µĶ��������³�ʼ��ָ�룬����ǰ���ͷ���������
	i.reset(new int);
	std::cout << *i << std::endl;
}
void BoostPtr::BoostPtr_shared() {
	//���Ժͱ�Ĺ���ָ�빲��һ������,���һ��ָ�����٣�������ͷţ�shared_ptr ���Թ����κ����͵Ķ���
	boost::shared_ptr<int> ptr1(new int(1));
	std::cout << "Value 1: " << *ptr1 << std::endl;
	boost::shared_ptr<int> ptr2 = ptr1;
	std::cout << "Value 2: " << *ptr2 << std::endl;

	*ptr1 = 2;
	std::cout << "Value 2: " << *ptr2 << std::endl;

	//��ָ��,��������shared_ptrָ����������ڣ�û�������ô�
	//����Ҫһ���������������ǲ����������ָ�룬�Ϳ���ʹ����ָ��
	boost::weak_ptr<int> weakPtr(ptr1);
	std::cout << *weakPtr.lock() << std::endl;
	if (boost::shared_ptr<int> shared = weakPtr.lock()) {
		std::cout << *shared << std::endl;
	}
	else {
		std::cout << "��Դ������" << std::endl;
	}
}
class MyObject : public boost::intrusive_ref_counter<MyObject>
{
public:
	int num = 0;
	void doSomething() {
		num++;
	}
};
void BoostPtr::BoostPtr_Counter() {
	//intrusive_ptr����Ķ��������չ��boost::intrusive_ref_counter��
	//����̬����Ķ�������������ָ�빲��һ�����������Ȩ
	boost::intrusive_ptr<MyObject> ptr = new MyObject();
	ptr->doSomething();

	boost::intrusive_ptr<MyObject> ptr1 = ptr;
	ptr->doSomething();
	std::cout << ptr->num << std::endl;
	std::cout << ptr1->num << std::endl;
	ptr.reset();
}

//ָ������
void BoostPtr::BoostPtr_model() {
	boost::ptr_vector<int> vectorPtr;
	vectorPtr.push_back(new int(1));
}

int add(int a, int b) {
	return a + b;
}
void funObject::getNewFun() {
	auto newFun = std::bind1st(std::ptr_fun(add), 5);
	int addNum = newFun(2);
	coutText(std::to_string(addNum));

	//boost��bind����Ҫ��ռλ��������ռλ����ʾתΪ��Ԫ����
	auto newBindFun = boost::bind(add, 10, _1);
	int num = newBindFun(1);
	coutText(std::to_string(num));
}

void AsynASio::createServer() {
	bostAsio::io_context io_context;
	
	bostAsio::ip::tcp::endpoint endpoint(bostAsio::ip::make_address("127.0.0.1"), 8810);
	/*open��������һ������������������Э���Э�����ͨ�� endpoint.protocol() ��ȡ��Э������ʾ��Ҫʹ�õ� IP ��ַ���ͣ�IPv4 �� IPv6����
	���� acceptor.open(endpoint.protocol()) ���� acceptor ��ָ������ʹ�õ�Э��*/
	/*acceptor.open(endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen();*/
	bostAsio::ip::tcp::acceptor acceptor(io_context, endpoint);
	bostAsio::ip::tcp::socket socket(io_context);
	acceptor.accept(socket);
	char buffer[1024];
	size_t bytes_received = socket.read_some(boost::asio::buffer(buffer));
	std::string received_data(buffer, bytes_received);
	std::cout << received_data << std::endl;
	// д������ʾ��
	std::string message = "Hello, client!";
	boost::asio::write(socket, boost::asio::buffer(message));
	socket.close();
}


void AsynASio::clientServer() {
	//boost::asio����WinSock�������ط������WinSock��ͻ�����������̾���ѡ����һ
	bostAsio::io_context io_context;
	bostAsio::ip::tcp::socket socket(io_context);
	bostAsio::ip::tcp::endpoint endpoint(bostAsio::ip::address::from_string("127.0.0.1"), 1234);
	socket.connect(endpoint);
	std::string data = "data, server";
	socket.write_some(bostAsio::buffer(data));
	std::array<char, 128> buffer;
	size_t bytesReceived = socket.read_some(bostAsio::buffer(buffer));
	io_context.run();
	socket.close();
}

void AsynASio::createWs() {
	bostAsio::io_context io_context;
	//����ָ���� IP ��ַ�Ͷ˿�,���ܿͻ��˵���������
	bostAsio::ip::tcp::acceptor acceptor(io_context);

	//�󶨲�����ip�Ͷ˿�
	bostAsio::ip::tcp::endpoint endpoint(bostAsio::ip::make_address("127.0.0.1"), 8810);
	acceptor.open(endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen();

	//���ܿͻ�������,�����Ự,socket��ͨ�ŵ��࣬����ĺܶ�ͨ�ŷ���
	bostAsio::ip::tcp::socket socket(io_context);
	//���ܴ��������
	acceptor.accept(socket);
	//����ws�Ự����,move����socket�������͵Ķ���
	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws(std::move(socket));

	std::string host;
	std::string target;

	ws.handshake(host, target);

	// ��ȡ����ʾ��
	boost::beast::flat_buffer buffer;
	ws.read(buffer);
	// д������ʾ��
	std::string message = "Hello, client!";
	ws.write(boost::asio::buffer(message));

	ws.close(boost::beast::websocket::close_code::normal);
}

// �Զ���ͳ���������ڼ���ż��������
//template<typename Sample>
//struct even_count {
//	using result_type = std::size_t;
//
//	template<typename Args>
//	void operator()(Args const& args) const {
//		if (args[weight] % 2 == 0) { // �������Ϊż��
//			accs(args) += 1; // ����ż��������
//		}
//	}
//
//	template<typename Args>
//	result_type result(Args const& args) const {
//		return count(accs(args)); // ����ż��������
//	}
//
//private:
//	mutable features::accumulator_set<Sample, stats<tag::count>> accs;
//};

void AccumulatorLearn::accumulaApi() {
	//��һ�������Ǳ������ݵ����ͣ��ڶ���������ͳ�Ʒ����������������ǿ�ѡ��Ȩ�����ͣ�ͨ����Ȩ���ݽ���ͳ�Ƽ���
	boostAccu::accumulator_set<double, boostAccu::stats< boostAccu::tag::mean, boostAccu::tag::moment<2>, boostAccu::tag::min>> acc;
	//stats���峣��ͳ������features��������ͳ������
	acc(1.2);
	acc(2.3);
	acc(3.4);
	acc(4.5);
	std::cout << boostAccu::mean(acc) << std::endl;
	std::cout << boostAccu::moment<2>(acc) << std::endl;
	std::cout << boostAccu::min(acc) << std::endl;
	
}

bool isOdd(int i) {
	return i % 2 == 1;
}
void AlgorithmApi::allOfAlgor() {
	int list[] = {0, 1, 2, 3, 4};	
	if (boostStr::all_of(list+1, list+2, isOdd)) {
		std::cout << "��ȷ" << std::endl;
	}
	else {
		std::cout << "����" << std::endl;
	}
}