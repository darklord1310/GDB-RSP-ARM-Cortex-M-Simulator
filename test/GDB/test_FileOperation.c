// #include <stdio.h>
#include "unity.h"
#include "FileOperation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_readElfText_should_obtain_all_the_data_from_the_file(void)
{
  FILE file;
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "ElfLocation.txt", *str;
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char elfPath2[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf\n";

  // write file to the text
  writeFile(&file, filename, "w", elfPath);
  
  // read file from the text that was written
	str = readElfText(&file, filename);

  TEST_ASSERT_EQUAL_STRING(elfPath2, str);
}

void test_readConfigfile_given_device_STM32F429ZI_should_read_the_info(void)
{
  FILE file;
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "config";
  char device[] = "STM32F429ZI";

	readConfigfile(&file, filename, &configInfo, device);

  // TEST_ASSERT_EQUAL_STRING("STM32F429ZI", configInfo.device);
  TEST_ASSERT_EQUAL(0x8000000, configInfo.flashOrigin);
  TEST_ASSERT_EQUAL(2048*1024, configInfo.flashSize);
  TEST_ASSERT_EQUAL(0x20000000, configInfo.ramOrigin);
  TEST_ASSERT_EQUAL(192*1024, configInfo.ramSize);
}

void test_readConfigfile_given_device_STM32F429YI_should_read_the_info(void)
{
  FILE file;
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "config";
  char device[] = "STM32F429YI";

	readConfigfile(&file, filename, &configInfo, device);

  // TEST_ASSERT_EQUAL_STRING("", configInfo.device);
  TEST_ASSERT_EQUAL(0, configInfo.flashOrigin);
  TEST_ASSERT_EQUAL(0, configInfo.flashSize);
  TEST_ASSERT_EQUAL(0, configInfo.ramOrigin);
  TEST_ASSERT_EQUAL(0, configInfo.ramSize);
}

void test_writeFile_should_write_the_path_contain_the_elf_file_to_a_text(void)
{
  FILE *file;
  char *filename = "ElfLocation.txt", *str;
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char elfPath2[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf\n";
  char buffer[100] = "";

	writeFile(file, filename, "w", elfPath);

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }
  
  str = fgets(buffer, 100, file);   // fget from the file for test

  TEST_ASSERT_EQUAL_STRING(elfPath2, str);

  // Close the file
  fclose(file);
}

void test_writeFile_should_write_a_string_to_a_text(void)
{
  FILE *file;
  char *filename = "ElfLocation.txt", *str;
  char strToWrite[] = "Hello Jackson";
  char strToWrite2[] = "Hello Jackson\n";
  char buffer[100] = "";

	writeFile(file, filename, "a", strToWrite);

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }
  
  str = fgets(buffer, 100, file);   // fget from the file for test

  TEST_ASSERT_EQUAL_STRING("C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf\n", str);
  
  str = fgets(buffer, 100, file);   // fget from the file for test

  TEST_ASSERT_EQUAL_STRING(strToWrite2, str);

  // Close the file
  fclose(file);
}
