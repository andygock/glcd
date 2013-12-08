
CC := gcc
LIBS := -lrt  -lbcm2835
CFLAGS := -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard -marm -O3 -Wall -std=c99 -I. -Idevices -Icontrollers -Idevices/inc -DGLCD_CONTROLLER_ST7565R  -DGLCD_USE_SPI -DGLCD_DEVICE_RASPBERRYPI

TARGET := lcdprog
HEADERS :=
OBJECTS := devices/RASPBERRYPI.o controllers/ST7565R.o graphics.o graphs.o text_tiny.o text.o glcd.o main.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $^ $(LIBS) $(CFLAGS) -o $(TARGET)

%.o: %.c
	@$(CC) -c $< $(LIBS) $(CFLAGS) -o $@

clean:
	-rm -fr $(OBJECTS)
	-rm -fr $(TARGET)

scp: $(TARGET)
	@scp $<  hanchen@172.16.0.236:/tmp

.PHONY: clean all scp
