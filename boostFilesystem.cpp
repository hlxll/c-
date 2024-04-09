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
		// 判断字符是否为中文字符
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
				std::cout << "有中文" << content << std::endl;
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
			std::cout << "以下文件有中文" << folderpath << std::endl;
			writeFile << (folderpath + "\n").c_str();
			std::string data;
			int index = 0;

			int moreLine = -1;
			while (getline(readFile, data)) {
				index++;
				if (data.find("/*") != std::string::npos) {
					//还需要将注释符前的中文加入
					moreLine = 1;
					std::vector<std::string> splitStr;
					boostStr::split(splitStr, data, boostStr::is_any_of("/*"));
					if (splitStr.size() > 0 && hasChineseCharacters(splitStr[0])) {
						if (writeFile.is_open()) {
							writeFile << (std::to_string(index) + splitStr[0] + "\n").c_str();
						}
					}
				}else if (data.find("*/") != std::string::npos) {
					//还需要将注释符前的中文加入
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
					std::string lineIndex = "第" + std::to_string(index) + "行";
					if (data.find("//") != std::string::npos) {
						std::vector<std::string> splitStr;
						boostStr::split(splitStr, data, boostStr::is_any_of("//"));
						//如果有‘//’注释符号，把注释符号前面的中文加入进来
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
	//转为绝对路径
	fs::path absolutepath = fs::absolute(folderpath);
	//boost::system::error_code ec;
	//转为标准化的不含符号链接的绝对路径
	/*fs::path canonicalPath = fs::canonical(folderpath, ec);
	if (!ec) {
		std::cout << canonicalPath << std::endl;
	}*/

	//拷贝地址
	//fs::path copyPath(fs::relative("./hl"));
	//fs::path basePath(fs::relative("./Release"));
	//try {
	//	//复制目录，新创建一个文件或目录为copyPath的目录，
	//	fs::copy(basePath, copyPath);
	//}
	//catch (const boost::filesystem::filesystem_error& ex){
	//	std::cout << ex.what() << std::endl;
	//}


	//boost::filesystem::path targetPath("./Release");     // 替换为实际目标路径
	//boost::filesystem::path symlinkPath("./hl_link");   // 替换为要创建的符号链接路径

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
	//当前工作目录的路径
	fs::path currentPath = fs::current_path();

	//检查路径是否存在
	bool hasPath = fs::exists(currentPath);
	if (hasPath) {
		coutText("存在");
		try {
			//c++11不支持，17引入
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
	//保存匹配结果
	boost::smatch resourceList;
	bool hasVal = boost::regex_search(str, resourceList, pattern);
	if (hasVal) {
		coutText("存在");
		std::cout << resourceList[0] << std::endl;
	}
}

void boostThreadFun() {
	std::cout << "多线程" << std::endl;
}
void BoostThread::ThreadProject() {
	boost::thread t1(boostThreadFun);
	t1.join();
}

void BoostPtr::BoostPtr_scoped() {
	//独占一个对象,作用域指针
	boost::scoped_ptr<int> i(new int);
	*i = 1;
	std::cout << *i << std::endl;
	//get返回所含对象地址
	*i.get() = 2;
	std::cout << *i << std::endl;
	//用一个新的对象来重新初始化指针，创建前会释放所含对象
	i.reset(new int);
	std::cout << *i << std::endl;
}
void BoostPtr::BoostPtr_shared() {
	//可以和别的共享指针共享一个对象,最后一个指针销毁，对象才释放，shared_ptr 可以管理任何类型的对象
	boost::shared_ptr<int> ptr1(new int(1));
	std::cout << "Value 1: " << *ptr1 << std::endl;
	boost::shared_ptr<int> ptr2 = ptr1;
	std::cout << "Value 2: " << *ptr2 << std::endl;

	*ptr1 = 2;
	std::cout << "Value 2: " << *ptr2 << std::endl;

	//弱指针,用来监听shared_ptr指针的生命周期，没有其他用处
	//当需要一个与对象关联，但是不依赖对象的指针，就可以使用弱指针
	boost::weak_ptr<int> weakPtr(ptr1);
	std::cout << *weakPtr.lock() << std::endl;
	if (boost::shared_ptr<int> shared = weakPtr.lock()) {
		std::cout << *shared << std::endl;
	}
	else {
		std::cout << "资源不可用" << std::endl;
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
	//intrusive_ptr管理的对象必须扩展自boost::intrusive_ref_counter类
	//管理动态分配的对象，允许多个智能指针共享一个对象的所有权
	boost::intrusive_ptr<MyObject> ptr = new MyObject();
	ptr->doSomething();

	boost::intrusive_ptr<MyObject> ptr1 = ptr;
	ptr->doSomething();
	std::cout << ptr->num << std::endl;
	std::cout << ptr1->num << std::endl;
	ptr.reset();
}

//指针容器
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

	//boost的bind必须要有占位符，几个占位符表示转为几元函数
	auto newBindFun = boost::bind(add, 10, _1);
	int num = newBindFun(1);
	coutText(std::to_string(num));
}

void AsynASio::createServer() {
	bostAsio::io_context io_context;
	
	bostAsio::ip::tcp::endpoint endpoint(bostAsio::ip::make_address("127.0.0.1"), 8810);
	/*open方法接受一个参数，即代表网络协议的协议对象。通过 endpoint.protocol() 获取的协议对象表示了要使用的 IP 地址类型（IPv4 或 IPv6）。
	调用 acceptor.open(endpoint.protocol()) 将打开 acceptor 并指定它将使用的协议*/
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
	// 写入数据示例
	std::string message = "Hello, client!";
	boost::asio::write(socket, boost::asio::buffer(message));
	socket.close();
}


void AsynASio::clientServer() {
	//boost::asio中有WinSock和其他地方引入的WinSock冲突，所有网络编程尽量选择其一
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
	//监听指定的 IP 地址和端口,接受客户端的连接请求
	bostAsio::ip::tcp::acceptor acceptor(io_context);

	//绑定并监听ip和端口
	bostAsio::ip::tcp::endpoint endpoint(bostAsio::ip::make_address("127.0.0.1"), 8810);
	acceptor.open(endpoint.protocol());
	acceptor.bind(endpoint);
	acceptor.listen();

	//接受客户端连接,创建会话,socket是通信的类，里面的很多通信方法
	bostAsio::ip::tcp::socket socket(io_context);
	//接受传入的连接
	acceptor.accept(socket);
	//创建ws会话对象,move返回socket引用类型的对象
	boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws(std::move(socket));

	std::string host;
	std::string target;

	ws.handshake(host, target);

	// 读取数据示例
	boost::beast::flat_buffer buffer;
	ws.read(buffer);
	// 写入数据示例
	std::string message = "Hello, client!";
	ws.write(boost::asio::buffer(message));

	ws.close(boost::beast::websocket::close_code::normal);
}

// 自定义统计量，用于计算偶数的数量
//template<typename Sample>
//struct even_count {
//	using result_type = std::size_t;
//
//	template<typename Args>
//	void operator()(Args const& args) const {
//		if (args[weight] % 2 == 0) { // 如果数据为偶数
//			accs(args) += 1; // 增加偶数计数器
//		}
//	}
//
//	template<typename Args>
//	result_type result(Args const& args) const {
//		return count(accs(args)); // 返回偶数的数量
//	}
//
//private:
//	mutable features::accumulator_set<Sample, stats<tag::count>> accs;
//};

void AccumulatorLearn::accumulaApi() {
	//第一个参数是保存数据的类型，第二个参数是统计方法，第三个参数是可选的权重类型，通过加权数据进行统计计算
	boostAccu::accumulator_set<double, boostAccu::stats< boostAccu::tag::mean, boostAccu::tag::moment<2>, boostAccu::tag::min>> acc;
	//stats定义常见统计量，features定义和组合统计量。
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
		std::cout << "正确" << std::endl;
	}
	else {
		std::cout << "错误" << std::endl;
	}
}