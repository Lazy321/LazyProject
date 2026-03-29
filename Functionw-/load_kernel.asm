[bits 16]
load_kernel:
    mov ah, 0x02
    mov al, 64
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    mov dl, [boot_driver_id]
    mov bx, KERNEL_OFFSET
    int 0x13
    ret
