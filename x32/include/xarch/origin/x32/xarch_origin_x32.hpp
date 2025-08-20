#pragma once

#include <array>
#include <cstdint>

#include <functional>
#include <unordered_map>
#include <xuci/base_architecture.hpp>
#include <xuci/types/memory.hpp>

namespace xarch::origin::x32 {

class XarchOrigin_x32 : public xuci::BaseArchitecture {
protected:
  union Register32 {
    uint32_t l = 0; // long
    uint16_t w[2];  // words
    uint8_t b[4];   // bytes
  };

  using XOX32_Instruction = std::function<void(XarchOrigin_x32 *)>;

  std::array<Register32, 16> gprs; // General Purpose Registers
  std::uint32_t IP;                // Instruction Pointer
  std::uint8_t SR;                 // Status Register

  xuci::Memory<std::uint32_t> vmu;

  std::unordered_map<std::uint32_t, XOX32_Instruction> instruction_set;

  // INST(2) + DES(4) + A(4) + B(4) = 14 bytes
  std::array<std::uint8_t, 14> entry;

  std::uint16_t current_instruction;

  std::uint8_t des_long_offset = 0; // [0-15]
  std::uint8_t des_word_offset = 0; // [16, 46]
  std::uint8_t des_byte_offset = 0; // [47, 110]

  std::uint8_t a_reg_long_offset = 0; // [0-15]
  std::uint8_t a_reg_word_offset = 0; // [16, 46]
  std::uint8_t a_reg_byte_offset = 0; // [47, 110]

  std::uint8_t b_reg_long_offset = 0; // [0-15]
  std::uint8_t b_reg_word_offset = 0; // [16, 46]
  std::uint8_t b_reg_byte_offset = 0; // [47, 110]

  std::uint32_t a_val = 0;
  std::uint32_t b_val = 0;

public:
  XarchOrigin_x32();
  ~XarchOrigin_x32();

  void fetch();
  void decode();
  void execute();

  void run();

  void write_instruction(std::uint32_t &offset, std::uint16_t inst,
                         std::uint32_t des, std::uint32_t a, std::uint32_t b);

  auto &get_gprs() { return this->gprs; }
  std::array<std::uint8_t, 3> get_des_offsets() {
    return {this->des_long_offset, this->des_word_offset,
            this->des_byte_offset};
  }

  std::array<std::uint8_t, 3> get_a_reg_offsets() {
    return {this->a_reg_long_offset, this->a_reg_word_offset,
            this->a_reg_byte_offset};
  }

  std::array<std::uint8_t, 3> get_b_reg_offsets() {
    return {this->b_reg_long_offset, this->b_reg_word_offset,
            this->b_reg_byte_offset};
  }

  std::uint32_t &get_a_value() { return this->a_val; }
  std::uint32_t &get_b_value() { return this->b_val; }
};

} // namespace xarch::origin::x32