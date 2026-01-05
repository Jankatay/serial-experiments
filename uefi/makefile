# GNU efi paths
GNU_EFI_RUNTIME = "/usr/lib/crt0-efi-x86_64.o"
GNU_EFI_LDS_X64 = "/usr/lib/elf_x86_64_efi.lds"
GNU_EFI_HEADERS = "/usr/include/efi"
GNU_EFI_LIBPATH = "/usr/lib"

# OVMF paths
OVMF_BIOS_PATH = "/usr/share/ovmf/OVMF.fd"
OVMF_CODE_PATH = "/usr/share/OVMF/OVMF_CODE_4M.fd" # for later
OVMF_VARS_PATH = "/usr/share/OVMF/OVMF_CODE_4M.fd" # for later

# Emulate main.efi using qemu and ovmf
run: uefi.img main.efi
	cp $^ out
	qemu-system-x86_64 -cpu qemu64 \
		-drive format=raw,file=fat:rw:out \
		-bios ${OVMF_BIOS_PATH} -net none

# make a usb-compatible image
uefi.img: main.efi
	dd if=/dev/zero of=$@ bs=1k count=1440
	mformat -i $@ -f 1440 ::
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/BOOT
	mcopy -i $@ $< ::/EFI/BOOT/BOOTX64.EFI

# Copy needed parts from shared-obj to produce efi
main.efi: main.so
	objcopy -j .text -j .sdata -j .data -j .rodata \
		-j .dynamic -j .dynsym -j .rel -j .rela \
		-j .reloc --target=efi-app-x86_64 main.so main.efi

# Link obj-file with gnu-efi c-runtime into a shared-obj
main.so: main.o
	ld $< ${GNU_EFI_RUNTIME} -nostdlib -znocombreloc \
	    -T ${GNU_EFI_LDS_X64} -shared -Bsymbolic \
		-L ${GNU_EFI_LIBPATH} -l:libgnuefi.a \
		-l:libefi.a -o $@

# Compile main.c to an obj-file
main.o: main.c
	gcc $< -c -fno-stack-protector -fpic -fshort-wchar -mno-red-zone \
		-I${GNU_EFI_HEADERS} -I${GNU_EFI_HEADERS}/x86_64 \
		-DEFI_FUNCTION_WRAPPER -o $@

.PHONY: clean
# Clean intermediate files
clean: 
	rm -f main.o main.so main.efi uefi.img
