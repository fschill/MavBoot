/*****************************************************************************
 *
 * \file
 *
 * \brief AVR32 UC3 ISP trampoline.
 *
 * In order to be able to program a project with both BatchISP and JTAGICE mkII
 * without having to take the general-purpose fuses into consideration, add this
 * file to the project and change the program entry point to _trampoline.
 *
 * The pre-programmed ISP will be erased if JTAGICE mkII is used.
 *
 * Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * \asf_license_start
 *
 * \page License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an
 *    Atmel microcontroller product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * \asf_license_stop
 *
 ******************************************************************************/


#include "trampoline_uc3.h"


#include <avr32/io.h>
#include "parts.h"

#if UC3C
//  These defines are missing from or wrong in the toolchain header file ip_xxx.h or part.h
#ifndef AVR32_WDT_KEY_VALUE
#define AVR32_WDT_KEY_VALUE                            0x00000055
#endif
#define AVR32_SR_M_SUP                                 0x00000001
#define AVR32_SR_M_SIZE                                         3
#define AVR32_SR_M_OFFSET                                      22
#define AVR32_SRAM_ADDRESS                             0x00000000
#endif

//! @{
//! \verbatim


  // Performs efficiently a bitwise logical Exclusive-OR between the specified
  // register and an immediate value of up to 32 bits. The result is stored in
  // the destination register.
  .macro  eor.w   rd, imm
    .if \imm & 0x0000FFFF
      eorl    \rd, LO(\imm)
    .endif
    .if \imm & 0xFFFF0000
      eorh    \rd, HI(\imm)
    .endif
  .endm

  // Moves efficiently an immediate value of up to 32 bits into a register.
  .macro  mov.w   rd, imm
    .if ((-(1 << (21 - 1))) <= \imm) && (\imm <= ((1 << (21 - 1)) - 1))
      mov     \rd, \imm
#if __AVR32_UC__ >= 2
    .elseif !(\imm & 0x0000FFFF)
      movh    \rd, HI(\imm)
#endif
    .else
      mov     \rd, LO(\imm)
      orh     \rd, HI(\imm)
    .endif
  .endm

  // Performs efficiently a bitwise logical OR between the specified register
  // and an immediate value of up to 32 bits. The result is stored in the
  // destination register.
  .macro  or.w    rd, imm
    .if \imm & 0x0000FFFF
      orl     \rd, LO(\imm)
    .endif
    .if \imm & 0xFFFF0000
      orh     \rd, HI(\imm)
    .endif
  .endm



//! @{
//! \verbatim


  // This must be linked @ 0x80000000 if it is to be run upon reset.
  .section  .reset, "ax", @progbits


  .global _trampoline
  .type _trampoline, @function
_trampoline:
  // Jump to program start.
  rjmp    program_start

//  .org  PROGRAM_START_OFFSET
program_start:
  mov.w   r9, AVR32_WDT_ADDRESS             // r9 = &AVR32_WDT
  mov.w   r11, AVR32_PM_ADDRESS             // r11 = &AVR32_PM

  rcall   disable_wdt

    // Test the reset cause.
  ld.w    r3, r11[AVR32_PM_RCAUSE]          // r3 = AVR32_PM.RCAUSE
  // Was the reset cause a WDT reset?
mov.w   r4, AVR32_PM_RCAUSE_POR_MASK |\
              AVR32_PM_RCAUSE_EXT_MASK |\
              AVR32_PM_RCAUSE_JTAG_MASK |\
              AVR32_PM_RCAUSE_OCDRST_MASK |\
              AVR32_PM_RCAUSE_JTAGHARD_MASK|\
              AVR32_PM_RCAUSE_BOD33_MASK |\
              AVR32_PM_RCAUSE_BOD_MASK  // r4 = POR|EXT|OCD|JTAG|BOD33|BOD  
   
   mov.w   r4, AVR32_PM_RCAUSE_WDT_MASK 
   tst     r3, r4
   brne    _goto_app // The reset cause was one of POR|BOD|EXT|OCD|JTAG|JTAGHARD(|AWIRE|AWIREHARD|BOD33):

  //bld     r3, AVR32_PM_RCAUSE_WDT_OFFSET
  //brcs    _goto_app // The reset cause was a WDT reset: start the application


  // Jump to the C runtime startup routine.
  lda.w   pc, _stext



#define APP_START_ADDRESS	0x80002000

.global	_goto_app
 .type	_goto_app, @function

_goto_app:
  rcall   disable_wdt

  mov.w   r0, AVR32_SR_GM_MASK | AVR32_SR_EM_MASK | (AVR32_SR_M_SUP << AVR32_SR_M_OFFSET)
  mtsr    AVR32_SR, r0
  .irp    rd, r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, sp, lr
    mov.w   \rd, 0
  .endr
  mtsr    AVR32_EVBA, r0
  mtsr    AVR32_COUNT, r0
	
 	lddpc   pc, program_start_address



disable_wdt:
  mov.w   r2, AVR32_WDT_KEY_VALUE << AVR32_WDT_CTRL_KEY_OFFSET
  st.w    r9[AVR32_WDT_CTRL], r2
  eor.w   r2, AVR32_WDT_CTRL_KEY_MASK
  st.w    r9[AVR32_WDT_CTRL], r2
  mov     pc, lr


// Constant data area.
  .balign 4

program_start_address:
  .word APP_START_ADDRESS

//! \endverbatim
//! @}
