#pragma once

#include "token.h"
#include <cstddef>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace Lox {

  using Value = std::variant<std::monostate, bool, double, std::string>;

  enum class OpCode : unsigned char {
    Constant,
    Nil,
    True,
    False,
    Pop,
    DefineGlobal,
    SetGlobal,
    GetGlobal,
    SetLocal,
    GetLocal,
    Equal,
    NotEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,
    Add,
    Subtract,
    Multiply,
    Divide,
    Negative,
    Not,
    Print,
    Jump,
    JumpIfTrue,
    JumpIfFalse,
    Loop,
    Return
  };

  class Chunk {
  public:
    constexpr std::byte read(size_t offset) const { return bytecode_[offset]; }
    void write(std::byte byte) { bytecode_.push_back(byte); }
    void write(OpCode opCode, const Token& token);
    void patch(size_t offset, std::byte byte) { bytecode_[offset] = byte; }

    constexpr size_t size() const noexcept { return bytecode_.size(); }

    Value getConstant(size_t index) const { return constants_[index]; }
    size_t addConstant(Value&& value);

    std::pair<unsigned, unsigned> getPosition(size_t offset) const { return positions_.find(offset)->second; }

  private:
    std::vector<std::byte> bytecode_ {};
    std::vector<Value> constants_ {};
    std::unordered_map<size_t, std::pair<unsigned, unsigned>> positions_ {};
  };
}
