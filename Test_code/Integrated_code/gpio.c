#include "gpio.h"


uint8_t gpio_export()
{
	system("echo 66 > /sys/class/gpio/export");
	system("echo 67 > /sys/class/gpio/export");
}

uint8_t gpio_unexport()
{
	system("echo 66 > /sys/class/gpio/unexport");
	system("echo 67 > /sys/class/gpio/unexport");
}

uint8_t gpio_direction()
{
	system("echo out > /sys/class/gpio/gpio66/direction");
	system("echo out > /sys/class/gpio/gpio67/direction");
}

uint8_t gpio_read()
{

}

uint8_t gpio_set()
{
	system("echo 1 > /sys/class/gpio/gpio66/value");
	system("echo 1 > /sys/class/gpio/gpio67/value");
}

uint8_t gpio_clear()
{
	system("echo 0 > /sys/class/gpio/gpio66/value");
	system("echo 0 > /sys/class/gpio/gpio67/value");
}
