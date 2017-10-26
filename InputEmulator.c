/* 参考drivers\input\keyboard\gpio_keys.c */
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/input.h>


static struct input_dev *input_emulator_dev;

static int input_emulator_init(void)
{
	int i;
	
	/* 分配input_dev结构体 */
	input_emulator_dev = input_allocate_device(dev);
	
	/* 设置能产生哪类事件 */
	set_bit(EV_KEY, input_emulator_dev->evbit);
	set_bit(EV_REP, input_emulator_dev->evbit);
	
	/* 设置能产生所有的按键 */
	for(i = 0; i < BITS_TO_LONGS(KEY_CNT); i++)
	{
		input_emulator_dev->keybit[i] = ~0UL; //0UL是无符号长整型 0， ~ 表示按位取反，即：0xffff
	}

	/* 为android构造一些设备信息 */
	input_emulator_dev->name = "InputEmulatorFromMrCoder";
	input_emulator_dev->id.bustype = 1;
	input_emulator_dev->id.vendor = 0x1234;
	input_emulator_dev->id.product = 0x5678;
	input_emulator_dev->id.version = 1;
	
	/* 注册 */
	input_register_device(input_emulator_dev);
	return 0;
}

static void input_emulator_exit(void)
{
	input_unregister_device(input_emulator_dev);
	input_free_device(input_emulator_dev);
}

module_init(input_emulator_init);

module_exit(input_emulator_exit);

MODULE_LICENSE("GPL");

