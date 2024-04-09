#include "strText.h"
void StrText::startStrText() {
	StrText::algoString();
}
void StrText::typeChange() {
	//����ת��,�ַ���ת���֣������ᱨ��?
	std::string str = "134";
	int data = boost::lexical_cast<int>(str);
	std::cout << data << std::endl;

	std::string newStr = boost::lexical_cast<std::string>(data);
	std::cout << newStr << std::endl;


	//�����ݸ�ʽ����ռλ�����滻Ϊʵ��ֵ
	std::string x = "123";
	boost::format fmt("Hello, %1%, %2%");
	std::cout << fmt % x %x << std::endl;
}

//������ʽ
void StrText::regexText() {
	boost::regex pattern("(\\d{2})-(\\d{2})-(\\d{4})");
	std::string input = "12-01-2020";
	if (boost::regex_match(input, pattern)) {
		std::cout << "ƥ��ɹ�";
	}
	else {
		std::cout << "ƥ��ʧ��";
	}
}

//�Ը����ı���ת��ΪXML��HTML��??
void StrText::compileText() {
	//�������
	//boost::spirit::qi::rule<std::istream, int> my_rule = boost::spirit::int_;
	////�������������������
	////boost::spirit::parser<std::istream, int> my_parser(my_rule);
	//int result;
	//if (my_parser(std::cin, result))
	//{
	//	// �����ɹ�
	//}
	//else
	//{
	//	// ����ʧ��
	//}
}
//�����ַ������㷨,
void StrText::algoString() {
	//����ַ�������ķ���
	std::string str1("hello word");
	boost::algorithm::to_upper(str1);
	std::cout << str1 << std::endl;
	
	boost::algorithm::replace_first(str1, "WORD", "huanglin");
	std::cout << str1 << std::endl;

	//���ı��ָ�,tokenizerͨ�����������ַ���split��������ַ�
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