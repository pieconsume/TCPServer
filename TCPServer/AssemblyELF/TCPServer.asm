; See https://github.com/pieconsume/HelloWorld/blob/main/HelloAsm_ELF.asm for more info on the headers
defs:
 [BITS 64]
 [DEFAULT REL]
 [ORG 0]
elf:
 dd 0x464C457F
 db 0x02,0x01,0x01,0x00,0x00,0,0,0,0,0,0,0
 dw 0x0003,0x003E,0x0001,0x0000
 dq init,proghead,0
 dw 0,0,0x0040,0x0038,0x0001,0,0,0
 proghead:
 dd 0x01,0x07
 dq 0,0,0,progend,progend,0
init:
 ; Commenting out each syscall arg would be far too tiresome. Use a reference table when working on this
 ; It is expected that you already understand how TCP works before trying to write a TCP server/client in assembly
 mov edi, 2   ; IPV4
 mov esi, 1   ; TCP
 xor edx, edx
 mov eax, 41  ; sys_socket
 syscall
 mov ebx, eax ; Store server socket in ebx so it wont be trashed
 mov edi, eax
 mov esi, 1   ; SOL_SOCKET
 mov edx, 15  ; SO_REUSEPORT
 lea r10, [true]
 mov r8d, 4
 mov eax, 54  ; sys_setsockopt
 syscall
 mov edi,ebx
 lea rsi,[addr]
 mov edx,0x10
 mov eax,49 ; sys_bind
 syscall
 mov edi,ebx
 mov esi,5
 mov eax,50 ; sys_listen
 syscall
listen:
 mov edi, ebx
 lea rsi, [addr]
 lea rdx, [size]
 mov eax, 43  ; sys_accept
 syscall
 mov ebp, eax ; Save the client address in ebp so it wont be trashed
 mov edi, eax
 lea rsi, [buffer]
 mov edx, 0xFF
 xor eax, eax ; sys_read
 syscall
 lea r8, [buffer]
 add r8, rax
 mov byte [r8], 0
 mov edi, 1
 lea rsi, [buffer]
 mov edx, eax
 mov eax, 1
 syscall
 mov edi, ebp
 lea rsi, [reply]
 mov edx, 17
 mov eax, 1
 syscall ; sys_write
exit:
 mov edi, ebp
 mov esi, 1  ; SHUT_WR
 mov eax, 48 ; sys_shutdown
 syscall
 mov edi, ebp
 mov esi, 0  ; SHUT_RD
 mov eax, 48 ; sys_shutdown
 syscall
 mov edi, ebp
 mov eax, 3  ; sys_close
 syscall
 jmp listen

data:
 align 0x04, db 0
 buffer times 0x100 db 0
 true dd 1
 size dd 0x10
 addr:
  dw 0x02               ; Address family, 2 is AF_INET / IPV4
  db 3721>>8, 3721&0xFF ; Port in MSB order
  dd 0                  ; IP address in MSB order. 0.0.0.0 accepts any ip address.
  dd 0,0                ; Padding to 16 bytes
 reply db 'Message received',10
progend: