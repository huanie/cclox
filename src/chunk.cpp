module;
import std.compat;
import token;

module chunk;

namespace Lox {
  void Chunk::write(OpCode opCode, const Token& token) {
    write(static_cast<std::byte>(opCode));
    positions_.emplace(size() - 1, std::make_pair(token.line, token.column));
  }

  size_t Chunk::addConstant(Value&& value) {
    constants_.push_back(std::move(value));
    return constants_.size() - 1;
  }
}
