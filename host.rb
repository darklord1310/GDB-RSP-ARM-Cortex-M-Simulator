# Set the path to CException source code
CEXCEPTION_PATH = "vendor/ceedling/vendor/c_exception/lib"

# Load build script to help build C program
load "cbuild.rb"

# Main dependency list
main_dependency = {
  # depender                dependee
  'ErrorSignal.o' => ['ErrorSignal.c', 'ErrorSignal.h', 'ARMSimulator/ARMRegisters.h'],
  'MemoryBlock.o' => ['MemoryBlock.c', 'MemoryBlock.h'],
  'Packet.o'      => ['GDB/Packet.c', 'GDB/Packet.h'],
  'RemoteSerialProtocol.o'
                  => ['GDB/RemoteSerialProtocol.c', 'GDB/RemoteSerialProtocol.h', 'GDB/Packet.h',
                      'ARMSimulator/ARMRegisters.h', 'ARMSimulator/ARMSimulator.h',
                      '..vendor/ceedling/vendor/c_exception/lib/CException', 'ErrorSignal.h', 'MemoryBlock.h'],
  'ServeRSP.o'    => ['GDB/ServeRSP.h', 'GDB/RemoteSerialProtocol.h', 'GDB/Packet.h',
                      '..vendor/ceedling/vendor/c_exception/lib/CException', 'ErrorSignal.h',],
  'StateRSP.o'    => ['GDB/StateRSP.h', 'GDB/ServeRSP.h', 'GDB/State.h', 'GDB/Packet.h'],
  'gdbServer.o'   => ['Main.c', 'Parser.h', 'ParserParse.h', 'Context.h', 'Log.h'],
  'gdbServer.exe' => ['Main.o', 'Lexer.o', 'LexerError.o', 'Token.o', 'Parser.o',
                      'ParserParse.o', 'Context.o', 'ErrorObject.o', 'TokenDebug.o',
                      'Tokenizer.o', 'CException.o'],
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
  #            dependency list  directory of   directory of     directory of    config
  #                             dependee       .o files         .exe            object
  compile_list(main_dependency, 'src', 'build/test/out', 'build/release', config)
  #compile_list(exception_dependency, CEXCEPTION_PATH, 'build/test/out', 'build/release', config)

  desc 'Build release code'
  task :release => 'build/release/Main.exe'
end

