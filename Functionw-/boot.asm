[org 0x7c00]
KERNEL_OFFSET equ 0x1000

mov [BOOT_DRIVE_ID], dl
mov bp, 0x9000
mov sp, bp

mov ax, 0x4F02
mov bx, 0x4114
int 0x10
jc vesa_error

call load_kernel
call switch_to_pm
jmp $

load_kernel:
    mov ah, 0x02
    mov al, 64
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [BOOT_DRIVE_ID]
    mov bx, KERNEL_OFFSET
    int 0x13
    ret

vesa_error:
    mov ax, 0x0003
    int 0x10
    mov ah, 0x0e
    mov al, 'V'
    int 0x10
    jmp $

gdt_start:
    dd 0x0, 0x0
gdt_code:
    dw 0xffff, 0x0
    db 0x0, 10011010b, 11001111b, 0x0
gdt_data:
    dw 0xffff, 0x0
    db 0x0, 10010010b, 11001111b, 0x0
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

[bits 16]
switch_to_pm:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 0x1
    mov cr0, eax
    jmp CODE_SEG:init_pm

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ebp, 0x90000
    mov esp, ebp
    call KERNEL_OFFSET
    jmp $

BOOT_DRIVE_ID db 0
times 510-($-$$) db 0
dw 0xaa55
