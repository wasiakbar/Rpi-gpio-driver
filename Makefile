obj-m := gpio.o
all:
	make -C /lib/modules/4.9.41-v7+/build M=$(PWD) modules
clean:
	make -C /lib/modules/4.9.41-v7+/build M=$(PWD) clean
