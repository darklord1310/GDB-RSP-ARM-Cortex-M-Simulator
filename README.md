GDB Server and ARM Simulator
============================

Steps of using gdbserver
-----------------------
1) Compile an .elf file with assembly code
   - Open Git Bash under 'GDB-RSP-ARM-Cortex-M-Simulator' folder and change directory to 'data' folder
   - Then, type 'compile' to compile 'startup_stm32f429xx.s' into 'AssemblyCode.elf'
     (Code inside startup_stm32f429xx.s can be change according to your need. Make sure you compile everytime changes was made)

2) Under the same folder, invoke ARM GDB by insert 'arm-none-eabi-gdb' command using Git Bash

3) Before using gdbserver, open another Git Bash under 'GDB-RSP-ARM-Cortex-M-Simulator' folder

4) Then, type 'rake release' to compile and release gdbServer.exe. Open gdbServer.exe using 'build/release/gdbServer.exe' command as the .exe file release under 'build/release/' folder

4) Connect the gdbserver using 'tar remote :2010' command under ARM GDB that was open in step 2

5) Load the 'AssemblyCode.elf' to write the memory into the simulator (Type 'load AssemblyCode.elf' command under ARM GDB)

6) Try any gdb command to communicate to the gdbserver
