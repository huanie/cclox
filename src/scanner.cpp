#include "scanner.h"

#include <unordered_map>

namespace {
  constexpr bool isWhitespace(char c) { return c == ' ' || c == '\t' || c == '\r' || c == '\n'; }

  constexpr bool isDigit(char c) { return c >= '0' && c <= '9'; }

  constexpr bool isAlpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_'; }

  constexpr bool isAlphanumeric(char c) { return isAlpha(c) || isDigit(c); }

  using Lox::TokenType;
  const std::unordered_map<std::string_view, TokenType> keywordTypes {
    { "and", TokenType::And },
    { "break", TokenType::Break },
    { "class", TokenType::Class },
    { "else", TokenType::Else },
    { "false", TokenType::False },
    { "fun", TokenType::Fun },
    { "for", TokenType::For },
    { "if", TokenType::If },
    { "nil", TokenType::Nil },
    { "or", TokenType::Or },
    { "print", TokenType::Print },
    { "return", TokenType::Return },
    { "super", TokenType::Super },
    { "this", TokenType::This },
    { "true", TokenType::True },
    { "var", TokenType::Var },
    { "while", TokenType::While }
  };
}

namespace Lox {
  void Scanner::initialize(const std::string& source, unsigned line) {
    source_ = source;
    offset_ = 0;
    line_ = line;
    lineStart_ = 0;
  }

  Token Scanner::scanToken() {
    for (;;) {
      advanceWhile(isWhitespace);
      if (isAtEnd()) return eofToken();

      tokenOffset_ = offset_;
      tokenLine_ = line_;
      tokenColumn_ = offset_ - lineStart_ + 1;

      const auto next = advance();
      switch (next) {
        case '(':
          return token(TokenType::LeftParen);
        case ')':
          return token(TokenType::RightParen);
        case '{':
          return token(TokenType::LeftBrace);
        case '}':
          return token(TokenType::RightBrace);
        case ',':
          return token(TokenType::Comma);
        case '.':
          return token(TokenType::Dot);
        case '-':
          return token(TokenType::Minus);
        case '+':
          return token(TokenType::Plus);
        case ';':
          return token(TokenType::Semicolon);
        case '/':
          if (advanceIf('/')) {
            advanceTo('\n');
            continue;
          }
          if (advanceIf('*')) {
            if (!advanceTo('*', '/')) return errorToken("Unterminated block comment.");

            continue;
          }
          return token(TokenType::Slash);
        case '*':
          return token(TokenType::Star);
        case '?':
          return token(TokenType::Question);
        case ':':
          return token(TokenType::Colon);
        case '!':
          return token(advanceIf('=') ? TokenType::BangEqual : TokenType::Bang);
        case '=':
          return token(advanceIf('=') ? TokenType::EqualEqual : TokenType::Equal);
        case '>':
          return token(advanceIf('=') ? TokenType::GreaterEqual : TokenType::Greater);
        case '<':
          return token(advanceIf('=') ? TokenType::LessEqual : TokenType::Less);
        case '"':
          return scanString();
        default:
          return
            isDigit(next) ? scanNumber() :
            isAlpha(next) ? scanIdentifierOrKeyword() : errorToken("Unexpected character.");
      }
    }
  }

  Token Scanner::scanString() {
    // Note: Lox only has multiline strings.
    if (!advanceTo('"')) return errorToken("Unterminated string.");

    return token(TokenType::String);
  }

  Token Scanner::scanNumber() {
    advanceWhile(isDigit);

    if (peek() == '.' && isDigit(peekSecond())) {
      advance();
      advance();
      advanceWhile(isDigit);
    }

    return token(TokenType::Number);
  }

  Token Scanner::scanIdentifierOrKeyword() {
    advanceWhile(isAlphanumeric);
    const auto pair = keywordTypes.find(lexeme());
    return token(pair == keywordTypes.end() ? TokenType::Identifier : pair->second);
  }

  Token Scanner::token(TokenType type) const {
    return Token { type, lexeme(), tokenLine_, tokenColumn_ };
  }

  Token Scanner::eofToken() const {
    return Token { TokenType::Eof, {}, line_, offset_ - lineStart_ };
  }

  Token Scanner::errorToken(std::string_view message) const {
    return Token { TokenType::Error, message, line_, offset_ - lineStart_ };
  }

  std::string_view Scanner::lexeme() const {
    return source_.substr(tokenOffset_, offset_ - tokenOffset_);
  }

  bool Scanner::isAtEnd() const {
    return offset_ >= source_.size();
  }

  char Scanner::peek() const {
    return offset_ >= source_.size() ? '\0' : source_[offset_];
  }

  char Scanner::peekSecond() const {
    return offset_ + 1 >= source_.size() ? '\0' : source_[offset_ + 1];
  }

  char Scanner::advance() {
    const auto next = source_[offset_++];

    // Update internal line / column information when we hit a (non-final) newline.
    if (next == '\n' && !isAtEnd()) {
      line_++;
      lineStart_ = offset_;
    }

    return next;
  }

  bool Scanner::advanceIf(char expected) {
    if (peek() != expected) return false;

    advance();
    return true;
  }

  bool Scanner::advanceTo(char expected) {
    while (!isAtEnd()) {
      if (advance() == expected) return true;
    }

    return false;
  }

  bool Scanner::advanceTo(char expected, char expectedSecond) {
    while (!isAtEnd()) {
      if (advance() == expected && advanceIf(expectedSecond)) return true;
    }

    return false;
  }

  void Scanner::advanceWhile(const std::function<bool(char)>& predicate) {
    while (predicate(peek())) advance();
  }
}