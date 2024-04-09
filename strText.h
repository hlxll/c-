#pragma once
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
//#include <boost/spirit/include/qi.hpp>
class StrText {
public:
	void startStrText();
	void typeChange();
	void regexText();
	void compileText();
	void algoString();
};