#include <xarch/origin/x32/xarch_origin_x32.hpp>

#include <xuci/log.hpp>

namespace xarch::origin::x32 {

void XarchOrigin_x32::fetch() {
  for (std::size_t i = 0; i < this->entry.size(); i++) {
    this->entry[i] = this->vmu.read(IP++);
  }
}

void XarchOrigin_x32::decode() {
  this->current_instruction = (entry.at(0) << 8) | entry.at(1);

  auto read_u32 = [&](size_t offset) {
    return (static_cast<uint32_t>(entry.at(offset)) << 24) |
           (static_cast<uint32_t>(entry.at(offset + 1)) << 16) |
           (static_cast<uint32_t>(entry.at(offset + 2)) << 8) |
           (static_cast<uint32_t>(entry.at(offset + 3)));
  };

  auto decode_operand = [&](uint32_t val, uint8_t &long_off, uint8_t &word_off,
                            uint8_t &byte_off) {
    long_off = (val & 0b111100) >> 2;
    word_off = (val & 0b000010) >> 1;
    byte_off = val & 0x1;
  };

  uint32_t des_val = read_u32(2);
  uint32_t a_val_tmp = read_u32(6);
  uint32_t b_val_tmp = read_u32(10);

  decode_operand(des_val, des_long_offset, des_word_offset, des_byte_offset);
  decode_operand(a_val_tmp, a_reg_long_offset, a_reg_word_offset,
                 a_reg_byte_offset);
  decode_operand(b_val_tmp, b_reg_long_offset, b_reg_word_offset,
                 b_reg_byte_offset);

  a_val = a_val_tmp;
  b_val = b_val_tmp;
}

void XarchOrigin_x32::execute() {
  xuci::log_fatal(!instruction_set.count(this->current_instruction),
                  "Unknown instruction has been passed");

  instruction_set[current_instruction](this);

  std::cout << (std::uint64_t)this->gprs.at(0).l << std::endl;
}

void XarchOrigin_x32::run() {

  std::uint32_t offset = 0;
  write_instruction(offset, 3,
                    0b00'00'00'00'00'00'00'00'00'00'00'00'00'00'00'11,
                    0xFFFFFFFF, 0);

  write_instruction(offset, 2,
                    0b00'00'00'00'00'00'00'00'00'00'00'00'00'00'00'10,
                    0xAAAA, 0);

  write_instruction(offset, 1,
                    0b00'00'00'00'00'00'00'00'00'00'00'00'00'00'00'00, 0x00, 0);

  write_instruction(offset, 0xFFFF,
                    0b00'00'00'00'00'00'00'00'00'00'00'00'00'00'00'00, 0x00, 0);



  do {
    fetch();
    decode();
    execute();
  } while (this->is_running());
}

} // namespace xarch::origin::x32