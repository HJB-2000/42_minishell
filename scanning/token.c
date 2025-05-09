#include "__scanner.h"

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool isAtEnd(Scanner* scanner) {
    return *scanner->current == '\0';
}

char advance(Scanner* scanner) {
    scanner->current++;
    return scanner->current[-1];
}

char peek(Scanner* scanner) {
    return *scanner->current;
}

char peekNext(Scanner *scanner) {
    if (isAtEnd(scanner)) return '\0';
    return scanner->current[1];
}

void skipWhitespace(Scanner* scanner) {
    while (true) {
      char c = peek(scanner);
      switch (c) {
        case ' ':
        case '\r':
        case '\t':
          advance(scanner);
          break;
        case '\n':
          scanner->line++;
          advance(scanner);
          break;
        case '/':
          if (peekNext(scanner) == '/') {
            // A comment goes until the end of the line.
            while (peek(scanner) != '\n' && !isAtEnd(scanner)) advance(scanner);
        } else {
            return;
        }
          break;
        default:
          return;
      }
    }
}

bool match(Scanner* scanner, char expected) {
    if (isAtEnd(scanner)) return false;
    if (*scanner->current != expected) return false;
    scanner->current++;
    return true;
}

Token makeToken(Scanner* scanner, TokenType type){
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;
    return token;
}

Token errorToken(Scanner* scanner, const char* message) {
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner->line;
    return token;
}

TokenType checkKeyword(Scanner* scanner, int start, int length,
    const char* rest, TokenType type) {

      if (scanner->current - scanner->start == start + length &&
          ft_memcmp(scanner->start + start, rest, length) == 0) {
            return type;
      }

  return TOKEN_IDENTIFIER;
}

TokenType identifierType(Scanner* scanner){

	if (scanner->start[0]) {
		char c = scanner->start[0];
		if(c == 'p') return checkKeyword(scanner, 1, 2, "wd", TOKEN_PWD);
		else if(c == 'u') return checkKeyword(scanner, 1, 4, "nset", TOKEN_UNSET);
		else if(c == 'h') return checkKeyword(scanner, 1, 6, "istory", TOKEN_HISTORY);
		else if(c == 'c'){
			if(scanner->current - scanner->start > 1){
				c = scanner->start[1];
				if(c == 'd') return checkKeyword(scanner, 2, 0, "", TOKEN_CD);
				else if(c == 'l') return checkKeyword(scanner, 2, 3, "ear", TOKEN_CLEAR);
				return TOKEN_IDENTIFIER;
			}	
		}
		else if (c == 'e'){
			if(scanner->current - scanner->start > 1) {
				c = scanner->start[1];
				if (c == 'x'){
					if (scanner->current - scanner->start > 2){
						c = scanner->start[2];
						if(c == 'i') return checkKeyword(scanner, 3, 1, "t", TOKEN_EXIT);
						else if(c == 'p') return checkKeyword(scanner, 3, 3, "ort", TOKEN_EXPORT);
					}
				}
				else if(c == 'n') return checkKeyword(scanner, 2, 1, "v", TOKEN_ENV);
				else if(c == 'c') return checkKeyword(scanner, 2, 2, "ho", TOKEN_ECHO);
				return TOKEN_IDENTIFIER;
			}
  		}
	}
  (void)scanner;
  	return TOKEN_IDENTIFIER;
}
Token identifier(Scanner* scanner) {
  int flag = 0;
  while (isAlpha(peek(scanner)) || isDigit(peek(scanner)) || peek(scanner) == '/'){
    if(peek(scanner) == '/')flag = 1;
    advance(scanner);
  }
  (void)flag;
  // if(flag == 1) return makeToken(scanner, TOKEN_PATH);
  return makeToken(scanner, identifierType(scanner));
}

Token number(Scanner* scanner) {
    while (isDigit(peek(scanner))) advance(scanner);
  
    // Look for a fractional part.
    if (peek(scanner) == '.' && isDigit(peekNext(scanner))) {
      // Consume the ".".
      advance(scanner);
  
      while (isDigit(peek(scanner))) advance(scanner);
    }
  
    return makeToken(scanner, TOKEN_NUMBER);
}

// Token string(Scanner* scanner) {
//     while (peek(scanner) != '"' && !isAtEnd(scanner)) {
//       if (peek(scanner) == '\n') scanner->line++;
//       advance(scanner);
//     }
  
//     if (isAtEnd(scanner)) return errorToken(scanner ,"Unterminated string.");
  
//     // The closing quote.
//     advance(scanner);
//     return makeToken(scanner, TOKEN_STRING);
// }
//-------------------------------------------------------------
Token DoubleQ_string(Scanner* scanner) {
    while (peek(scanner) != '"' && !isAtEnd(scanner)) {
      if (peek(scanner) == '\n') scanner->line++;
      advance(scanner);
    }
  
    if (isAtEnd(scanner)) return errorToken(scanner ,"Unterminated string.");
  
    // The closing quote.
    advance(scanner);
    return makeToken(scanner, TOKEN_DQUOTE);
}

Token SingleQ_string(Scanner* scanner) {
    while (peek(scanner) != '\'' && !isAtEnd(scanner)) {
      if (peek(scanner) == '\n') scanner->line++;
      advance(scanner);
    }
  
    if (isAtEnd(scanner)) return errorToken(scanner ,"Unterminated string.");
  
    // The closing quote.
    advance(scanner);
    return makeToken(scanner, TOKEN_SQUOTE);
}
// Token GroupingToken(Scanner* scanner) {
//   while (peek(scanner) != ')' && !isAtEnd(scanner)) {
//     if (peek(scanner) == '\n') scanner->line++;
//     advance(scanner);
//   }
//   if (isAtEnd(scanner)) return errorToken(scanner ,"Unterminated parthen.");
//   advance(scanner);
//   return makeToken(scanner, TOKEN_GROUP);
// }