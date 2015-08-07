int abc = 0xabab;
double value;

void testFunc(void);

int main(void)
{
	abc = 0x10;
	//testFunc();

	while(abc)
	{
		abc--;
	}

	return 0;
}
