GDB Server and ARM Simulator
============================

Step of using gdbserver
-----------------------
1) Invoke arm-none-eabi-gdb using cmd
2) Compile gdbserver.c to winsocks.exe application at src folder by typing "server"
   - Make sure change the directory to src folder before type "server"
3) Connect the gdbserver using "tar remote :2010" command under arm-none-eabi-gdb
4) Load the .elf or .axf to write the memory into the simulator
5) Type any gdb command to communicate to the gdbserver