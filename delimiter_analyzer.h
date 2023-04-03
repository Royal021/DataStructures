#pragma once
#include <stack.h>

class DelimiterAnalyzer
{
public:
	enum class TokenType { PAREN, SQUARE, CURLY };
	class Token
	{
	public:
		TokenType type;
		int line_num;
		int char_pos;
	};


	DelimiterAnalyzer(std::string fname);
	void process();
protected:
	ssuds::Stack<Token> mTokenStack;


	bool is_opening(char c);
	bool closing_matches(char c, TokenType opening_type);
};