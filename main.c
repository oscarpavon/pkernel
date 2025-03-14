
#include "library.h"
#include "console.h"
#include "framebuffer.h"
#include "acpi.h"

#include "input.h"
#include "drivers/pci.h"

void hang(){
	while(1){};
}

void main(void* in_frame_buffer,uint64_t acpi_table){
	init_frambuffer(in_frame_buffer);	
	clear();

	print("pkernel");


	XSDT = (struct XSDT_t*)acpi_table;
	//parse_XDST();

	//print("parsed acpi");
	print_pci_list();


	print("--You are in owner space now--");
	input_loop();

	hang();	
}
