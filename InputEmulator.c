/* �ο�drivers\input\keyboard\gpio_keys.c */
#include <linux/module.h>
#include <linux/version.h>

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/input.h>


static struct input_dev *input_emulator_dev;

static int input_emulator_init(void)
{
	int i;
	
	/* ����input_dev�ṹ�� */
	input_emulator_dev = input_allocate_device(dev);
	
	/* �����ܲ��������¼� */
	set_bit(EV_KEY, input_emulator_dev->evbit);
	set_bit(EV_REP, input_emulator_dev->evbit);
	
	/* �����ܲ������еİ��� */
	for(i = 0; i < BITS_TO_LONGS(KEY_CNT); i++)
	{
		input_emulator_dev->keybit[i] = ~0UL; //0UL���޷��ų����� 0�� ~ ��ʾ��λȡ��������0xffff
	}

	/* Ϊandroid����һЩ�豸��Ϣ */
	input_emulator_dev->name = "InputEmulatorFromMrCoder";
	input_emulator_dev->id.bustype = 1;
	input_emulator_dev->id.vendor = 0x1234;
	input_emulator_dev->id.product = 0x5678;
	input_emulator_dev->id.version = 1;
	
	/* ע�� */
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

