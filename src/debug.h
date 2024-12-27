#pragma once

#include "chunk.h"

namespace Lox {

  class ChunkPrinter {
  public:
    void print(const Chunk& chunk, std::string_view name);

  private:
    void printInstruction();

    const Chunk* chunk_;
    size_t offset_ { 0 };
  };
}
