obj-m := FirstKernelModule.o

KDIR := /usr/src/linux-6.11
PWD := $(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

