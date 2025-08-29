#pragma once

#include <array>
#include <cstdint>
#include <filesystem>
#include <fstream>

#include <xwm/base_architecture.hpp>

namespace xarch::origin {

struct DecodedInstruction {
  std::uint16_t opcode;
  std::uint32_t dest;
  std::uint32_t op_a;
  std::uint32_t op_b;
};

class XarchOrigin_x32 : public xwm::BaseArchitecture {
private:
  std::uint32_t IP = 0;               // Instruction Pointer
  std::array<std::uint32_t, 16> gprs; // General Purpose Registers

  std::vector<std::uint8_t> vmu; // Virtual Memory Unit

  std::array<std::uint32_t, 4>
      entry; // OP(12 bits) | DEST(32 bits) | OP_A(32 bits) | OP_B(32 bits)

  DecodedInstruction decoded_instruction;

public:
  void fetch();
  void decode();
  void execute() {}

  void run();

  std::uint32_t &get_ip() { return this->IP; }
  std::array<std::uint32_t, 16> &get_gprs() { return this->gprs; }
  std::array<std::uint32_t, 4> &get_entry() { return this->entry; }

  void push_to_vmu(std::uint16_t op, std::uint32_t dest, std::uint32_t op_a,
                   std::uint32_t op_b) {
    op &= 0xFFF;

    this->vmu.push_back(static_cast<std::uint8_t>(op & 0xFF));
    this->vmu.push_back(static_cast<std::uint8_t>((op >> 8) & 0x0F) |
                        static_cast<std::uint8_t>((dest & 0x7F) << 4));

    this->vmu.push_back(static_cast<std::uint8_t>((dest >> 7) & 0xFF));
    this->vmu.push_back(static_cast<std::uint8_t>((dest >> 15) & 0xFF));
    this->vmu.push_back(static_cast<std::uint8_t>((dest >> 23) & 0xFF));

    this->vmu.push_back(static_cast<std::uint8_t>(op_a >> 0));
    this->vmu.push_back(static_cast<std::uint8_t>(op_a >> 8));
    this->vmu.push_back(static_cast<std::uint8_t>(op_a >> 16));
    this->vmu.push_back(static_cast<std::uint8_t>(op_a >> 24));

    this->vmu.push_back(static_cast<std::uint8_t>(op_b >> 0));
    this->vmu.push_back(static_cast<std::uint8_t>(op_b >> 8));
    this->vmu.push_back(static_cast<std::uint8_t>(op_b >> 16));
    this->vmu.push_back(static_cast<std::uint8_t>(op_b >> 24));
  }

  void load_to_vmu(const std::filesystem::path &path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if (!file.is_open())
      return;

    auto size = file.tellg();
    file.seekg(0);

    this->vmu.resize(size);
    file.read(reinterpret_cast<char *>(this->vmu.data()), size);
  }
};

} // namespace xarch::origin