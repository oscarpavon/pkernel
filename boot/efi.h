
#ifndef __EFI_H__
#define __EFI_H__

#include "types.h"
#include <stdint.h>

#define EFI_LOADED_IMAGE_PROTOCOL_GUID \
	{ 0x5b1b31a1, 0x9562, 0x11d2, \
	  { 0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

#define EFI_ACPI_20_TABLE_GUID \
	{0x8868e871,0xe4f1,0x11d3,\
		{0xbc,0x22,0x00,0x80,0xc7,0x3c,0x88,0x81}}

#define KEY_CODE_UP 0x01
#define KEY_CODE_DOWN 0x02
#define KEY_CODE_RIGHT 0x03
#define KEY_CODE_LEFT 0x04

typedef void * Handle;

typedef uint64_t efi_uint_t;

typedef uint64_t efi_status_t;

typedef uint64_t Status;

typedef efi_status_t efi_status;

static const efi_status_t EFI_SUCCESS = 0;

static const uint32_t EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL = 0x00000001;
static const uint32_t EFI_OPEN_PROTOCOL_GET_PROTOCOL = 0x00000002;

#define EFI_FILE_MODE_READ 0x0000000000000001
#define EFI_FILE_MODE_WRITE 0x0000000000000002
#define EFI_FILE_MODE_CREATE 0x8000000000000000

#define EFI_FILE_ARCHIVE 0x0000000000000020

static const uint64_t EFI_FILE_READ_ONLY = 0x1;

static const uint64_t MAX_BIT = 0x8000000000000000ULL;

typedef struct GUID{
	uint32_t data1;
	uint16_t data2;
	uint16_t data3;
	uint8_t data4[8];
}EFI_GUID;

struct TableHeader{
	uint64_t signature;
	uint32_t revision;
	uint32_t header_size;
	uint32_t crc32;
	uint32_t reserved;
};


typedef struct{
	uint8_t type;
	uint8_t sub_type;
	uint8_t length[2];
}DevicePathProtocol;

typedef struct{
	uint16_t scan_code;
	uint16_t unicode_char;
}InputKey;

struct InputProtocol{
	void (*reset)();
	efi_status (*read_key_stroke)(struct InputProtocol *self, 
			InputKey* key);
	void (*wait_for_key)();//boot_services.wait_for_event()
};
typedef struct {
	EFI_GUID vendor_guid;
	void* vendor_table;
}EfiConfigurationTable;

typedef struct TextOutputProtocol TextOutputProtocol;

struct SystemTable{
	struct TableHeader header;
	uint16_t *unused1;//firmware vendor
	uint32_t unused2;//firmware revision
	void *unused3;//console in handle
	struct InputProtocol *input; //ConIn
	void *unused5;//console out handle
	TextOutputProtocol *out;//console out
	void *unused6;//standard error handle
	void *unused7;//standard error
	void *unused8;//runtime services
	struct BootTable* boot_table;//boot services
	uint64_t number_of_table_entries;
	EfiConfigurationTable* configuration_tables;//configuration table
};

typedef struct SystemTable SystemTable;


struct MemoryDescriptor{
	uint32_t type;
	uint64_t physical_start;
	uint64_t virtual_start;
	uint64_t pages;
	uint64_t attributes;
};

enum AllocateType{
	EFI_ALLOCATE_ANY_PAGES,
};

enum MemoryType{
	EFI_LOADER_CODE,
	EFI_LOADER_DATA,
};

typedef struct FileProtocol FileProtocol;

typedef struct FileProtocol{
    uint64_t revision;
    Status (*open)(
        FileProtocol* self,
        FileProtocol** new_handle,
        uint16_t * file_name,
        uint64_t open_mode,
        uint64_t attributes);

    Status (*close)(FileProtocol*);

    void (*unused1)();

    Status (*read)(FileProtocol*, efi_uint_t *, void *);

    Status (*write)(FileProtocol*, uint64_t* buffer_size, void* buffer);

    Status (*get_position)(FileProtocol*, uint64_t *);
    Status (*set_position)(FileProtocol*, uint64_t);

    Status (*get_info)(
        FileProtocol*, struct GUID*, efi_uint_t *, void *);

    void (*unused6)();
    void (*unused7)();
    void (*unused8)();
    void (*unused9)();
    void (*unused10)();
    void (*unused11)();
}FileProtocol;

#define EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID \
    { 0x0964e5b22, 0x6459, 0x11d2, \
      { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b } }

struct FileSystemProtocol{
    uint64_t revision;
    efi_status_t (*open_volume)(
        struct FileSystemProtocol* self, struct FileProtocol** root);
};


struct LoadedImageProtocol{
	uint32_t revision;
	Handle parent;
	struct SystemTable *system;

	// Source location of the image
	Handle device;
	DevicePathProtocol *file_path;
	void *reserved;

	// Image's load options
	uint32_t load_options_size;
	void *load_options;

	// Location of the image in memory
	void *image_base;
	uint64_t image_size;
	enum MemoryType image_code_type;
	enum MemoryType image_data_type;
	void (*unused)();
};


struct BootTable 
{
	struct TableHeader header;

	// Task Priority Services
	void (*unused1)();
	void (*unused2)();

	// Memory Services
	efi_status_t (*allocate_pages)(
		enum AllocateType,
		enum MemoryType,
		efi_uint_t,
		uint64_t *);
	efi_status_t (*free_pages)(uint64_t, efi_uint_t);
	efi_status_t (*get_memory_map)(
		efi_uint_t *,
		struct MemoryDescriptor*,
		efi_uint_t *,
		efi_uint_t *,
		uint32_t *);
	efi_status_t (*allocate_pool)(
		enum MemoryType, efi_uint_t, void **);
	efi_status_t (*free_pool)(void *);

	// Event & Timer Services
	void (*unused7)();
	void (*unused8)();
	void (*unused9)();
	void (*unused10)();
	void (*unused11)();
	void (*unused12)();

	// Protocol Handler Services
	void (*unused13)();//install protocol
	void (*unused14)();//reinstall protocol
	void (*unused15)();//unistall protrocol
	Status (*handle_protocol)(Handle handle, struct GUID* protocol_guid, void** interface);//handle protocol
	void *reserved;
	void (*unused17)();//register protocol notify
	void (*unused18)();//locate handle
	void (*unused19)();//locate device path
	void (*unused20)();//install configuration table

	// Image Services
	efi_status (*image_load)(bool boot_policy,
			Handle parent_image_handle,
			DevicePathProtocol *device_path,
			void* source_buffer,
			efi_uint_t source_size,
			Handle* image_handle);

	efi_status_t (*start_image)(Handle image_handle,
			uint64_t * exit_data_size, 
			uint16_t **exit_data);

	void (*unused23)();
	void (*unused24)();

	efi_status_t (*exit_boot_services)(Handle, efi_uint_t);

	// Miscellaneius Services
	void (*unused26)();
	void (*unused27)();
	void (*unused28)();

	// DriverSupport Services
	void (*unused29)();
	void (*unused30)();

	// Open and Close Protocol Services
	efi_status_t (*open_protocol)(
		Handle handle,
		struct GUID * protocol,
		void ** interface,//optional
		Handle agent_handle,
		Handle controller_handle,
		uint32_t attributes);

	efi_status_t (*close_protocol)(
		Handle,
		struct GUID *,
		Handle agent_handle,
		Handle controller_handle);
	void (*unused33)();

	// Library Services
	efi_status_t (*protocols_per_handle)(
		Handle, struct GUID ***, efi_uint_t *);
	void (*unused35)();//locate handle buffer
	Status (*locate_protocol)(struct GUID* protocol_guid, 
			void* registration,
			void** interface);//locate protocol
	void (*unused37)();
	void (*unused38)();

	// 32-bit CRC Services
	void (*unused39)();

	// Miscellaneius Services (cont)
	void (*unused40)();
	void (*unused41)();
	void (*unused42)();
};


struct TextOutputProtocol{
	void (*unused1)();

	Status (*output_string)(
		TextOutputProtocol *self,
		uint16_t *string);

	void (*unused2)();
	void (*unused3)();
	void (*unused4)();
	void (*unused5)();

	Status (*clear_screen)(TextOutputProtocol *self);

	void (*unused6)();
	void (*unused7)();

	void *unused8;
};

#endif
