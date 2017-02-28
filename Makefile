SDK = ~/src/esp-open-sdk/sdk

CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

main-0x00000.bin: main
	esptool.py elf2image $^

main: main.o

main.o: main.c

flash: main-0x00000.bin
	esptool.py --baud 115200 write_flash --flash_mode dio 0 main-0x00000.bin 0x10000 main-0x10000.bin 0x3fc000 $(SDK)/bin/esp_init_data_default.bin 0x7e000 $(SDK)/bin/blank.bin 0x3fe000 $(SDK)/bin/blank.bin

clean:
	rm -f main main.o main-0x00000.bin main-0x10000.bin
