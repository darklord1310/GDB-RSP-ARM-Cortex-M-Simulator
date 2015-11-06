#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "unity.h"
#include "FileOperation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_readFile_should_obtain_all_the_data_from_the_file(void)
{
  FILE file;
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "TEST1.txt", *str, str1[100], str2[100];
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char device[] = "STM32F429ZI";

  // write file to the text
  writeFile(&file, filename, "w", elfPath);
  writeFile(&file, filename, "a", device);

  // read file from the text that was written
	str = readFile(&file, filename);
  sscanf(str, "%s %s", str1, str2);

  TEST_ASSERT_EQUAL_STRING(elfPath, str1);
  TEST_ASSERT_EQUAL_STRING(device, str2);
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

void test_readGdbServerConfigFile_should_return_port_number(void)
{
  FILE file;
  char *filename = "GDBServerConfig.ini";
  int ret;

	ret = readGdbServerConfigFile(&file, filename);

  TEST_ASSERT_EQUAL(2009, ret);
}

void test_writeFile_should_write_the_path_contain_the_elf_file_to_a_text(void)
{
  FILE *file;
  char *filename = "TEST2.txt", *str, str1[100];
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char buffer[1024] = "";

	writeFile(file, filename, "w", elfPath);

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }

  str = fgets(buffer, 1024, file);   // fget from the file for test
  sscanf(str, "%s", str1);

  TEST_ASSERT_EQUAL_STRING(elfPath, str1);

  // Close the file
  fclose(file);
}

void test_writeFile_should_write_a_string_to_a_text(void)
{
  FILE *file;
  char *filename = "TEST2.txt", *str, elfPath[100], secondStr[100];
  char strToWrite[] = "HelloJackson";
  char buffer[1024] = "";

	writeFile(file, filename, "a", strToWrite);

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }

  str = fgets(buffer, 1024, file);   // fget from the file for test
  sscanf(str, "%s %s", elfPath, secondStr);

  TEST_ASSERT_EQUAL_STRING("C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf", elfPath);
  TEST_ASSERT_EQUAL_STRING(strToWrite, secondStr);

  // Close the file
  fclose(file);
}

void test_backwardToForwardSlash_given_string_with_backslash_should_to_forward_slash(void)
{
  char buffer[1024], *str;

  str = getcwd(buffer, 1024);
  backwardToForwardSlash(str);

  TEST_ASSERT_EQUAL_STRING("C:/Users/Asus/Desktop/TDD/Project/GDB-RSP-ARM-Cortex-M-Simulator", str);
}
