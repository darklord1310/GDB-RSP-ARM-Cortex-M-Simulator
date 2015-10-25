#include <stdio.h>
#include <unistd.h>
#include "unity.h"
#include "MyFlash.h"
#include "FileOperation.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_coflash_given_argv_should_write_elf_path_to_the_text(void)
{
  FILE *file;
  char *filename = "ElfLocation.txt", *str, buffer[1024], str1[100], str2[100];
  const char *argv[] = {"program", "STM32F429ZI", "C:/Users/Asus/Desktop/CoIDE/workspace/BlinkyLED/Test01/Debug/bin/Test01.elf"};

	coflash(3, argv);

  file = fopen(filename, "r");

  if(file == NULL)
  {
    printf("error: cannot open the file %s\n", filename);
    return;
  }

  str = fgets(buffer, 1024, file);   // fget from the file for test
  sscanf(str, "%s %s", str1, str2);

  TEST_ASSERT_EQUAL_STRING(argv[2], str1);
  TEST_ASSERT_EQUAL_STRING(argv[1], str2);

  // Close the file
  fclose(file);
}

void test_writeFile_should_write_the_path_contain_the_elf_file_to_a_text(void)
{
  FILE *file;
  char *filename = "ElfLocation.txt", *str, str1[100];
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
  char *filename = "ElfLocation.txt", *str, elfPath[100], secondStr[100];
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

void xtest_getcwd()
{
  char *str, buffer[1024];
  
  str = getcwd(buffer, 1024);
  puts(str);
}
