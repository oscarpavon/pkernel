CC := clang
LD := ld.lld

CFLAGS := -ffreestanding -MMD -mno-red-zone -std=c11 \
	-target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:efi_main

SRCS := $(wildcard *.c)
OBJS := $(SRCS:c=o)

all: pboot.efi

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -c $<

console.o: ../console.c
	$(CC) $(CFLAGS) -c ../console.c

framebuffer.o: ../framebuffer.c
	$(CC) $(CFLAGS) -c ../framebuffer.c


pboot.efi: $(OBJS) console.o framebuffer.o
	$(LD) $(LDFLAGS) ${OBJS} console.o framebuffer.o -out:../pboot.efi


clean:
	rm -f *.o
	rm -f *.d
