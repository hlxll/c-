#include "strText.h"
void StrText::startStrText() {
	StrText::algoString();
}
void StrText::typeChange() {
	//类型转换,字符串转数字，超长会报错?
	std::string str = "134";
	int data = boost::lexical_cast<int>(str);
	std::cout << data << std::endl;

	std::string newStr = boost::lexical_cast<std::string>(data);
	std::cout << newStr << std::endl;


	//对数据格式化，占位符被替换为实际值
	std::string x = "123";
	boost::format fmt("Hello, %1%, %2%");
	std::cout << fmt % x %x << std::endl;
}

//正则表达式
void StrText::regexText() {
	boost::regex pattern("(\\d{2})-(\\d{2})-(\\d{4})");
	std::string input = "12-01-2020";
	if (boost::regex_match(input, pattern)) {
		std::cout << "匹配成功";
	}
	else {
		std::cout << "匹配失败";
	}
}

//对复杂文本的转换为XML，HTML等??
void StrText::compileText() {
	//定义规则
	//boost::spirit::qi::rule<std::istream, int> my_rule = boost::spirit::int_;
	////定义解析器，包含规则
	////boost::spirit::parser<std::istream, int> my_parser(my_rule);
	//int result;
	//if (my_parser(std::cin, result))
	//{
	//	// 解析成功
	//}
	//else
	//{
	//	// 解析失败
	//}
}
//处理字符串的算法,
void StrText::algoString() {
	//许多字符串处理的方法
	std::string str1("hello word");
	boost::algorithm::to_upper(str1);
	std::cout << str1 << std::endl;
	
	boost::algorithm::replace_first(str1, "WORD", "huanglin");
	std::cout << str1 << std::endl;

	//对文本分割,tokenizer通常处理输入字符，split处理输出字符
	std::string text("hello|word|huanglin;");
	boost::tokenizer<> tokenizer(text);
	for (boost::tokenizer<>::iterator it = tokenizer.begin(); it != tokenizer.end(); ++it) {
		std::cout << *it << std::endl;
	}

	std::string textStr("hello|word|huanglin|");
	std::vector<std::string> tokens;
	boost::split(tokens, textStr, boost::is_any_of("|"));
	for (const auto& token : tokens) {
		std::cout << token << std::endl;
	}
}