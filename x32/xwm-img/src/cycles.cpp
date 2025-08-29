#include <iostream>
#include <xarch/origin/x32.hpp>

namespace xarch::origin {

void XarchOrigin_x32::fetch() {

  std::uint32_t opcode = static_cast<std::uint32_t>(this->vmu[IP]) >> 14 |
                         static_cast<std::uint32_t>(
                             this->vmu[IP + 1]); // static_cast<std::uint32_t>()

  std::uint32_t dest = (this->vmu[IP + 1]);
  std::uint32_t op_a = this->vmu[IP + 2];
  std::uint32_t op_b = this->vmu[IP + 3];

  this->entry[0] = opcode;
  this->entry[1] = dest;
  this->entry[2] = op_a;
  this->entry[3] = op_b;

  IP += 4;
}

void XarchOrigin_x32::decode() {
  DecodedInstruction decoded_instruction = {0, 0, 0, 0};

  decoded_instruction.opcode = static_cast<std::uint16_t>(this->entry[0]);

  this->decoded_instruction = decoded_instruction;
}

void XarchOrigin_x32::run() {
  std::cout << "Running..." << std::endl;
  this->push_to_vmu(51, 1, 1, 1);
  fetch();
  std::cout << "Entry: " << entry[0] << std::endl;
}

} // namespace xarch::origin
