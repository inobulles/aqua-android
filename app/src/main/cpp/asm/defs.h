 
#ifndef __AQUA__DECODER_DEFS_H
	#define __AQUA__DECODER_DEFS_H
	
	/*
	 * So each general purpose register has a type and a family.
	 * The family designates its letter (a, c, d or b) and the type designates its size (64, 32, 16 or 8).
	 * Each of these values can be represented in the form of a 2 bit value.
	 * Thus, we can shift the type left by 2 bits and "or" that with the family to get a 4 bit value representing the register.
	 * This is useful as we can very easily get the family or type of the regsiter just by masking it.
	 * 
	 * EXAMPLE:
	 * 
	 * cx -> type = 16 bit, family = C, representation in binary = 0b1001
	 * get family: cx & 0b0011 = 0b0001
	 * get type: cx & 0b1100 = 0b1000
	 * 
	 * We know that 0b1000 means a 16 bit type and that 0b0001 means from family C
	 * 
	*/
	
	#define GENERAL_PURPOSE_REGISTER_BASE 0
	
	#define REGISTER_FAMILY_a 0b0000
	#define REGISTER_FAMILY_c 0b0001
	#define REGISTER_FAMILY_d 0b0010
	#define REGISTER_FAMILY_b 0b0011
	
	#define REGISTER_TYPE_64 0b0000
	#define REGISTER_TYPE_32 0b0100
	#define REGISTER_TYPE_16 0b1000
	#define REGISTER_TYPE_8 0b1100
	
	#define REGISTER_rax (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_64 | REGISTER_FAMILY_a))
	#define REGISTER_rcx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_64 | REGISTER_FAMILY_c))
	#define REGISTER_rdx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_64 | REGISTER_FAMILY_d))
	#define REGISTER_rbx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_64 | REGISTER_FAMILY_b))
	
	#define REGISTER_eax (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_32 | REGISTER_FAMILY_a))
	#define REGISTER_ecx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_32 | REGISTER_FAMILY_c))
	#define REGISTER_edx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_32 | REGISTER_FAMILY_d))
	#define REGISTER_ebx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_32 | REGISTER_FAMILY_b))
	
	#define REGISTER_ax (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_16 | REGISTER_FAMILY_a))
	#define REGISTER_cx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_16 | REGISTER_FAMILY_c))
	#define REGISTER_dx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_16 | REGISTER_FAMILY_d))
	#define REGISTER_bx (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_16 | REGISTER_FAMILY_b))
	
	#define REGISTER_al (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_8 | REGISTER_FAMILY_a))
	#define REGISTER_cl (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_8 | REGISTER_FAMILY_c))
	#define REGISTER_dl (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_8 | REGISTER_FAMILY_d))
	#define REGISTER_bl (GENERAL_PURPOSE_REGISTER_BASE + (REGISTER_TYPE_8 | REGISTER_FAMILY_b))
	
	#define REGISTER_LAST_GENERAL_PURPOSE REGISTER_bl
	
	#define REGISTER_sp (REGISTER_LAST_GENERAL_PURPOSE + 1)
	#define REGISTER_bp (REGISTER_LAST_GENERAL_PURPOSE + 2)
	#define REGISTER_si (REGISTER_LAST_GENERAL_PURPOSE + 3)
	#define REGISTER_di (REGISTER_LAST_GENERAL_PURPOSE + 4)
	#define REGISTER_esi (REGISTER_LAST_GENERAL_PURPOSE + 5)
	#define REGISTER_edi (REGISTER_LAST_GENERAL_PURPOSE + 6)
	#define REGISTER_ebp (REGISTER_LAST_GENERAL_PURPOSE + 7)
	#define REGISTER_esp (REGISTER_LAST_GENERAL_PURPOSE + 8)
	#define REGISTER_rsp (REGISTER_LAST_GENERAL_PURPOSE + 9)
	#define REGISTER_rbp (REGISTER_LAST_GENERAL_PURPOSE + 10)
	#define REGISTER_rsi (REGISTER_LAST_GENERAL_PURPOSE + 11)
	#define REGISTER_rdi (REGISTER_LAST_GENERAL_PURPOSE + 12)
	#define REGISTER_ss (REGISTER_LAST_GENERAL_PURPOSE + 13)
	#define REGISTER_cs (REGISTER_LAST_GENERAL_PURPOSE + 14)
	#define REGISTER_ds (REGISTER_LAST_GENERAL_PURPOSE + 15)
	#define REGISTER_es (REGISTER_LAST_GENERAL_PURPOSE + 16)
	#define REGISTER_fs (REGISTER_LAST_GENERAL_PURPOSE + 17)
	#define REGISTER_gs (REGISTER_LAST_GENERAL_PURPOSE + 18)
	#define REGISTER_eip (REGISTER_LAST_GENERAL_PURPOSE + 19)
	#define REGISTER_rip (REGISTER_LAST_GENERAL_PURPOSE + 20)
	#define REGISTER_r8d (REGISTER_LAST_GENERAL_PURPOSE + 21)
	#define REGISTER_r8 (REGISTER_LAST_GENERAL_PURPOSE + 22)
	#define REGISTER_addr (REGISTER_LAST_GENERAL_PURPOSE + 23)
	#define REGISTER_r12 (REGISTER_LAST_GENERAL_PURPOSE + 24)
	#define REGISTER_r13 (REGISTER_LAST_GENERAL_PURPOSE + 25)
	#define REGISTER_r14 (REGISTER_LAST_GENERAL_PURPOSE + 26)
	#define REGISTER_r15 (REGISTER_LAST_GENERAL_PURPOSE + 27)
	#define REGISTER_r9 (REGISTER_LAST_GENERAL_PURPOSE + 28)
	#define REGISTER_r10 (REGISTER_LAST_GENERAL_PURPOSE + 29)
	#define REGISTER_r11 (REGISTER_LAST_GENERAL_PURPOSE + 30)
	
	#define REGISTER_cf (REGISTER_LAST_GENERAL_PURPOSE + 31)
	#define REGISTER_of (REGISTER_LAST_GENERAL_PURPOSE + 32)
	#define REGISTER_zf (REGISTER_LAST_GENERAL_PURPOSE + 33)
	#define REGISTER_sf (REGISTER_LAST_GENERAL_PURPOSE + 34)
	#define REGISTER_pf (REGISTER_LAST_GENERAL_PURPOSE + 35)
	#define REGISTER_af (REGISTER_LAST_GENERAL_PURPOSE + 36)
	
	#define REGISTER_LAST REGISTER_af
	
	#define TOKEN_END 255
	#define TOKEN_DATA_END 256
	#define TOKEN_DATA_SECTION_END 257
	#define TOKEN_RESERVED_POSITIONS_END -1
	
	#define TOKEN_KEYWORD 1
	#define TOKEN_REGISTER 2
	#define TOKEN_RESERVED 3
	#define TOKEN_NUMBER 4
	#define TOKEN_ADDRESS 6
	#define TOKEN_PRERESERVED 9
	#define TOKEN_QTYPE 12
	
	#define TOKEN_mov 0
	#define TOKEN_ret 1
	#define TOKEN_jmp 2
	#define TOKEN_call 3
	#define TOKEN_push 4
	#define TOKEN_pop 5
	#define TOKEN_add 6
	#define TOKEN_sub 7
	#define TOKEN_mul 8
	#define TOKEN_div 9
	#define TOKEN_mod 10
	#define TOKEN_and 11
	#define TOKEN_or 12
	#define TOKEN_xor 13
	#define TOKEN_inc 14
	#define TOKEN_dec 15
	#define TOKEN_lea 16
	#define TOKEN_shl 17
	#define TOKEN_shr 18
	#define TOKEN_cmp 19
	#define TOKEN_imul 20
	#define TOKEN_idiv 21
	#define TOKEN_movsx 22
	#define TOKEN_cdq 23
	#define TOKEN_test 24
	#define TOKEN_sal 25
	#define TOKEN_sar 26
	#define TOKEN_neg 27
	#define TOKEN_cla 28
	#define TOKEN_mul3 29
	#define TOKEN_div3 30
	#define TOKEN_mul1 31
	#define TOKEN_div1 32
	#define TOKEN_cqo 33
	#define TOKEN_not 34
	#define TOKEN_rep 35
	#define TOKEN_movsq 36
	#define TOKEN_cnd 37
	#define TOKEN_movzx 38
	#define TOKEN_set 39
	
	#define CONDITION_Z 0
	#define CONDITION_NZ 1
	#define CONDITION_S 2
	#define CONDITION_NS 3
	#define CONDITION_E 4
	#define CONDITION_NE 5
	#define CONDITION_LT 6
	#define CONDITION_GT 7
	#define CONDITION_LE 8
	#define CONDITION_GE 9
	#define CONDITION_C 10
	#define CONDITION_NC 11
	
#endif
