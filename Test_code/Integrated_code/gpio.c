#include "gpio.h"


uint8_t gpio_export()
{
	system("echo 66 > /sys/class/gpio/export");
	system("echo 67 > /sys/class/gpio/export");
	return 0;
}

uint8_t gpio_unexport()
{
	system("echo 66 > /sys/class/gpio/unexport");
	system("echo 67 > /sys/class/gpio/unexport");
	return 0;
}

uint8_t gpio_direction()
{
	system("echo out > /sys/class/gpio/gpio66/direction");
	system("echo out > /sys/class/gpio/gpio67/direction");
	return 0;
}

uint8_t gpio_read()
{
	return 0;
}

uint8_t gpio_setgreen()
{
	system("echo 1 > /sys/class/gpio/gpio66/value");
	return 0;
}

uint8_t gpio_setred()
{
	system("echo 1 > /sys/class/gpio/gpio67/value");
	return 0;
}

uint8_t gpio_cleargreen()
{
	system("echo 0 > /sys/class/gpio/gpio66/value");
	return 0;
}
uint8_t gpio_clearred()
{
	system("echo 0 > /sys/class/gpio/gpio67/value");
	return 0;
}


