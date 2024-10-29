CC := clang
LD := ld.lld

CFLAGS := -ffreestanding -MMD -mno-red-zone -std=c11 \
	-target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:efi_main

SRCS := framebuffer.c library.c main.c

all_objects := $(wildcard *.o)

default: all

objects: $(SRCS)
	$(CC) $(CFLAGS) -c $^

pkernel: objects
	$(LD) $(LDFLAGS) $(all_objects) -out:/root/virtual_machine/disk/pkernel #-verbose 

#-include $(SRCS:.c=.d)

install:
	cp /root/virtual_machine/disk/pkernel /boot/pkernel

.PHONY: clean all default install

clean:
	rm *.o
	rm *.d


all: pkernel 
