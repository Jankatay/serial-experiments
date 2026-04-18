#include <iostream>
#include "token.hpp"

// expression: term EOF
//   | expression "+" term
//   | expression "-" term
double expression(TStream& tokens);

// term: primary
//   | term "*" primary
//   | term "/" primary
double term(TStream& tokens);

// primary: double
//   | "(" expression ")"
double primary(TStream& tokens);


int main() {
  TStream tokens{};
  cout << "= " << expression(tokens) << endl;
  return 0;
}


// Handle adding and subtracting
// check declaration for BNF definition
double expression(TStream& tokens) {
  double expval = term(tokens); // term -> expression
  while(true) { // will change to simple recursion later
    Token next = tokens.get();
    switch(next.kind) { 
      case Token::ADD: expval += term(tokens); continue;
      case Token::SUB: expval -= term(tokens); continue;
      case Token::TEOF: return expval;
      default: tokens.put_back(next); return expval;
    }
  }
}

// Handle multiplying and dividing 
double term(TStream& tokens) {
  double termval = primary(tokens); // primary -> term
  while(true) { // no idea why not simple recursion
    Token next = tokens.get();
    switch(next.kind) { 
      case Token::MUL: termval *= primary(tokens); continue;
      case Token::DIV: termval /= primary(tokens); continue;
      default: tokens.put_back(next); return termval;
    }
  }
}

// Handle numbers and parentheses
double primary(TStream& tokens) {
  // numbers
  Token t = tokens.get();
  if(t.kind == Token::NUM) return t.val;

  // invalid
  if(t.kind != Token::POPEN) {
    cerr << "Error -> primary() - " << __FILE__ << ":" << __LINE__ << endl;
    exit(EXIT_FAILURE);
  }

  // get num 
  double ret = expression(tokens);

  // missing parentheses
  if(tokens.get().kind != Token::PCLOSE) {
    cerr << "Unclosed parentheses" << endl;
    exit(EXIT_FAILURE);
  }

  // invalid again
  return ret;
}

