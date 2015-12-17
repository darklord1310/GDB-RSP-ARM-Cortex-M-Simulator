#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include "unity.h"
#include "FileOperation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_writeFile_should_write_the_path_contain_the_elf_file_to_a_text(void)
{
  FILE *file;
  char *filename = "TEST2.txt", *str, str1[100];
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char buffer[1024] = "";

	writeFile(filename, "w", elfPath);

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

	writeFile(filename, "a", strToWrite);

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

void test_readFile_should_obtain_all_the_data_from_the_file(void)
{
  char *filename = "TEST1.txt", *str, str1[100], str2[100];
  char elfPath[] = "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf";
  char device[] = "STM32F429ZI";

  // write file to the text
  writeFile(filename, "w", elfPath);
  writeFile(filename, "a", device);
  
  // read file from the text that was written
	str = readFile(filename, "r");
  sscanf(str, "%s %s", str1, str2);

  TEST_ASSERT_EQUAL_STRING(elfPath, str1);
  TEST_ASSERT_EQUAL_STRING(device, str2);
}

void test_readConfigfile_given_device_STM32F429ZI_should_read_the_info(void)
{
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "config";
  char device[] = "STM32F429ZI";

	readConfigfile(filename, "r", &configInfo, device);

  // TEST_ASSERT_EQUAL_STRING("STM32F429ZI", configInfo.device);
  TEST_ASSERT_EQUAL(0x8000000, configInfo.flashOrigin);
  TEST_ASSERT_EQUAL(2048*1024, configInfo.flashSize);
  TEST_ASSERT_EQUAL(0x20000000, configInfo.ramOrigin);
  TEST_ASSERT_EQUAL(192*1024, configInfo.ramSize);
}

void test_readConfigfile_given_device_STM32F429YI_should_read_the_info(void)
{
  ConfigInfo configInfo = {0, 0, 0, 0};
  char *filename = "config";
  char device[] = "STM32F429YI";

	readConfigfile(filename, "r", &configInfo, device);

  // TEST_ASSERT_EQUAL_STRING("", configInfo.device);
  TEST_ASSERT_EQUAL(0, configInfo.flashOrigin);
  TEST_ASSERT_EQUAL(0, configInfo.flashSize);
  TEST_ASSERT_EQUAL(0, configInfo.ramOrigin);
  TEST_ASSERT_EQUAL(0, configInfo.ramSize);
}

void test_createGdbServerInfo_given_host_and_port_should_create_GdbServerInfo_object(void)
{
  GdbServerInfo *gdbServerInfo;

  gdbServerInfo = createGdbServerInfo("127.0.1", 2058);

  TEST_ASSERT_EQUAL_STRING("127.0.1", gdbServerInfo->host);
  TEST_ASSERT_EQUAL(2058, gdbServerInfo->port);

  destroyGdbServerInfo(gdbServerInfo);
}

void test_readGdbServerConfigFile_should_return_port_number(void)
{
  GdbServerInfo *gdbServerInfo;
  char *filename = "GDBServerConfig.ini";

	gdbServerInfo = readGdbServerConfigFile(filename, "r");

  TEST_ASSERT_EQUAL_STRING("127.0.0.1", gdbServerInfo->host);
  TEST_ASSERT_EQUAL(2009, gdbServerInfo->port);

  destroyGdbServerInfo(gdbServerInfo);
}

void test_getDirectoryName_given_a_path_name_should_return_the_directory(void)
{
  char buf[] = "C:/CooCox/CoIDE_V2Beta/bin\\coflash.exe", *str;

  str = getDirectoryName(buf);

  TEST_ASSERT_EQUAL_STRING("C:/CooCox/CoIDE_V2Beta/bin", str);

  free(str);
}

void test_getDirectoryName_given_a_non_path_string_should_return_the_null(void)
{
  char buf[] = "hello word", *str;

  str = getDirectoryName(buf);

  TEST_ASSERT_EQUAL_STRING(NULL, str);
}

void test_appendString_given_default_string_and_another_string_should_append_the_string(void)
{
  char *defaultStr = "Hello ";
  char *strToAppend = "and Welcome";
  char *retStr = NULL;

  retStr = appendString(defaultStr, strToAppend);

  TEST_ASSERT_EQUAL_STRING("Hello and Welcome", retStr);

  destroyStr(retStr);
}

void test_appendString_given_default_null_string_and_another_string_should_append_the_string(void)
{
  char *defaultStr = NULL;
  char *strToAppend = "Welcome";
  char *retStr = NULL;

  retStr = appendString(defaultStr, strToAppend);

  TEST_ASSERT_EQUAL_STRING("Welcome", retStr);

  destroyStr(retStr);
}

void test_appendString_given_default_null_string_and_another_null_string_return_null(void)
{
  char *defaultStr = NULL;
  char *strToAppend = NULL;
  char *retStr = NULL;

  retStr = appendString(defaultStr, strToAppend);

  TEST_ASSERT_EQUAL_STRING(NULL, retStr);

  destroyStr(retStr);
}
