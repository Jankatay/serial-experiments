#pragma once 

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// simple tokenization for four arithmetic operations and parentheses. BNF grammar below
struct Token {
  enum Type {NUM, ADD, SUB, MUL, DIV, POPEN, PCLOSE, TEOF, TEOL, ERR} kind;
  double val = 0;
  Token(double num): kind(NUM), val(num) {}
};

// stream of tokens!!
class TStream {
  istream& source = cin; // reads from here
  bool iseof = false; // source ended
  public:
  TStream(istream& stream): source(stream), iseof(false) {} // read tokens from the given stream
  TStream(): TStream(cin) {} // read inputs from stdin 
  bool eof() { return iseof; } // read inputs from stdin 

  // read an operator into tok
  Token get() {
    Token tok(0);
    char ch = '\0';

    // read from stream
    source >> ch;
    if(source.eof()) { 
      iseof = true;
      tok.val = EOF; 
      tok.kind = Token::TEOF; 
      return tok; 
    }

    // handle operators
    switch(ch) {
      case '(': tok.val = '('; tok.kind = Token::POPEN; return tok;
      case ')': tok.val = ')'; tok.kind = Token::PCLOSE; return tok;
      case '+': tok.val = '+'; tok.kind = Token::ADD; return tok;
      case '-': tok.val = '-'; tok.kind = Token::SUB; return tok;
      case '*': tok.val = '*'; tok.kind = Token::MUL; return tok;
      case '/': tok.val = '/'; tok.kind = Token::DIV; return tok;
      case ';': tok.val = ';'; tok.kind = Token::TEOL; return tok;
    }

    // numbers
    if(isdigit(ch) || (ch == '.')) {
      source.putback(ch);
      source >> tok.val;
      tok.kind = Token::NUM;
    } else tok.kind = Token::ERR; // not in the list :(
  
    return tok;
  }

  // push the token back
  void put_back(const Token& tok) {
    if(tok.kind == Token::ERR) return; // ignore error

    // for numbers, convert them to string and push back one by one
    if(tok.kind == Token::NUM) {
      string s = to_string(tok.val);
      for(char c : s) source.putback(c);
      return;
    }

    // for rest, val hides their implicit char cast
    source.putback(tok.val);
  }
};
