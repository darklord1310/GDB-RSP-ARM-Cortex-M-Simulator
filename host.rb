# Set the path to CException source code
CEXCEPTION_PATH = "vendor/ceedling/vendor/c_exception/lib"

# Load build script to help build C program
load "cbuild.rb"

# Main dependency list
main_dependency = {
  # depender                                dependee
  'ErrorSignal.o'           => ['ErrorSignal.c', 'ErrorSignal.h', 'ARMSimulator/ARMRegisters.h'],
  'MemoryBlock.o'           => ['MemoryBlock.c', 'MemoryBlock.h'],
  #GDB
  'ExceptionObject.o'       => ['ExceptionObject.c', 'ExceptionObject.h', 'ErrorSignal.h', 'MemoryBlock.h', 'ARMSimulator/ARMRegisters.h'],
  'Packet.o'                => ['GDB/Packet.c', 'GDB/Packet.h'],
  'RemoteSerialProtocol.o'  => ['ErrorSignal.h', 'MemoryBlock.h', 'GDB/RemoteSerialProtocol.c', 'GDB/RemoteSerialProtocol.h', 'GDB/Packet.h',
                                'ARMSimulator/ARMRegisters.h', 'ARMSimulator/ARMSimulator.h',
                                '..vendor/ceedling/vendor/c_exception/lib/CException'],
  'ServeRSP.o'              => ['GDB/ServeRSP.h', 'GDB/ServeRSP.c', 'GDB/RemoteSerialProtocol.h', 'GDB/Packet.h',
                                '..vendor/ceedling/vendor/c_exception/lib/CException', 'ErrorSignal.h'],
  'StateRSP.o'              => ['GDB/StateRSP.h', 'GDB/ServeRSP.c', 'GDB/State.h', 'GDB/Packet.h'],
  'LoadElf.o'               => ['MemoryBlock.h', 'GDB/LoadElf.h', 'GDB/LoadElf.c', 'ARMSimulator/ARMRegisters.h',
                                'ElfReader/ProgramElf.h', 'ElfReader/GetHeaders.h', 'ElfReader/Relocator.h', 'ElfReader/Read_File.h',
                                'ElfReader/elf.h', 'ElfReader/ErrorCode.h', '..vendor/ceedling/vendor/c_exception/lib/CException'],
  #ELF Reader
  'GetHeaders.o'            => ['ElfReader/GetHeaders.h', 'ElfReader/GetHeaders.c', 'ElfReader/ProgramElf.h', 'ElfReader/Relocator.h',
                                'ElfReader/Read_File.h', 'ElfReader/elf.h', 'ElfReader/ErrorCode.h',
                                '..vendor/ceedling/vendor/c_exception/lib/CException'],
  'Read_File.o'             => ['ElfReader/Read_File.h', 'ElfReader/Read_File.c', 'ElfReader/ErrorCode.h'],
  'Relocator.o'             => ['ElfReader/Relocator.h', 'ElfReader/Relocator.c', 'ElfReader/ProgramElf.h', 'ElfReader/GetHeaders.h',
                                'ElfReader/Read_File.h', 'ElfReader/elf.h', 'ElfReader/ErrorCode.h',
                                '..vendor/ceedling/vendor/c_exception/lib/CException'],
  #gdbserver
  'gdbServer.o'             => ['GDB/gdbServer.c', 'GDB/gdbServer.h', 'GDB/ServeRSP.h', 'GDB/StateRSP.h', 'GDB/State.h',
                                'GDB/RemoteSerialProtocol.h', 'ARMSimulator/ARMRegisters.h', 'ARMSimulator/ARMSimulator.h',
                                'MemoryBlock.h'],
  'gdbServer.exe'           => ['Main.o', 'ErrorSignal.o', 'MemoryBlock.o', 'GDB/Packet.o', 'GDB/RemoteSerialProtocol.o',
                                'GDB/ServeRSP.o', 'GDB/StateRSP.o', 'GDB/gdbServer.o', 'CException.o'],
}

# Support dependency list
exception_dependency = {'CException.o'  => ['CException.c', 'CException.h']}

# Configuration parameters
config = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => [CEXCEPTION_PATH,
                   'src'],
#  :user_define  => ['CEXCEPTION_USE_CONFIG_FILE', 'TEST='],
#  :library_path => 'lib',
#  :library => ['libusb'],
#  :compiler_options => ['-DOK'],                 # Other compiler options
#  :linker_options => ['-DOK'],                   # Other linker options
#  :linker_script => 'MyLinkerScript.ld',
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-T',
                    :define => '-D'}
}

namespace :host do
  desc 'Build custom release code'
  task :release do
    #            dependency list  directory of   directory of     directory of    config
    #                             dependee       .o files         .exe            object
    compile_list(main_dependency, 'src', 'build/test/out', 'build/release', config)
    #compile_list(exception_dependency, CEXCEPTION_PATH, 'build/test/out', 'build/release', config)
    Rake::Task["build/release/gdbserver.exe"].invoke
    #task :release => 'build/release/Main.exe'
  end
end

namespace :easy do
  desc 'Build easy release code'
  task :release do
    #dep_list = compile_list(exception_dependency, CEXCEPTION_PATH, 'build/release/host/c', '.', config)
    dep_list.merge!(compile_all(['src'], 'build/release/host/c', config))
    link_all(getDependers(dep_list), 'build/release/Main.exe', config)
    Rake::Task["build/release/Main.exe"].invoke
  end
end
