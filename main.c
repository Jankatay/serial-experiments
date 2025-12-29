#include <efi.h>
#include <efilib.h>


// Main entry point
EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable){
  	InitializeLib(ImageHandle, SystemTable);
    Print(L"Hello, World\n");
    return EFI_SUCCESS;
}

