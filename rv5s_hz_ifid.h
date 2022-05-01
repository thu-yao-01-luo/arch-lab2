#pragma once

#include "VSRTL/core/vsrtl_component.h"
#include "VSRTL/core/vsrtl_register.h"

#include "../riscv.h"

namespace vsrtl {
namespace core {
using namespace Ripes;

class RV5S_HZ_IFID : public Component {
public:
    RV5S_HZ_IFID(std::string name, SimComponent* parent) : Component(name, parent) {
        CONNECT_REGISTERED_CLEN_INPUT(pc4, clear, enable);
        CONNECT_REGISTERED_CLEN_INPUT(pc, clear, enable);
        CONNECT_REGISTERED_CLEN_INPUT(instr, clear, enable);

        CONNECT_REGISTERED_CLEN_INPUT(valid, clear, enable);
    }

    REGISTERED_CLEN_INPUT(pc4, RV_REG_WIDTH); // pc4: current pc value + 4, which is the address of the next instruction if there are no branch instructions.
    REGISTERED_CLEN_INPUT(instr, RV_REG_WIDTH); // instr: the instruction.
    REGISTERED_CLEN_INPUT(pc, RV_REG_WIDTH); // pc: current pc value.

    // Register controls
    INPUTPORT(enable, 1);
    INPUTPORT(clear, 1);

    // Valid signal. False when the register bank has been cleared. May be used by UI to determine whether the NOP in
    // the stage is a user-inserted nop or the result of some pipeline action.
    REGISTERED_CLEN_INPUT(valid, 1);
};

}  // namespace core
}  // namespace vsrtl
