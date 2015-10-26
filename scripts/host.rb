# Set the path to CException source code
CEXCEPTION_PATH = "vendor/ceedling/vendor/c_exception/lib"

# Load build script to help build C program
load "scripts/cbuild.rb"

# Main dependency list
main_dependency = {
  # depender                dependees
  'ErrorObject.o' => ['ErrorObject.c', 'ErrorObject.h'],
  'TokenDebug.o'  => ['TokenDebug.c', 'TokenDebug.h', 'Context.h', 'ErrorObject.h', 'Log.h'],
  'LexerError.o'  => ['LexerError.c', 'Context.h', 'ErrorObject.h', 'Log.h'],
  'Lexer.o'       => ['Lexer.c', 'Lexer.h', 'LexerError.h', 'ErrorObject.h', 'Log.h', 'LexiconIsotopes.inc'],
  'Token.o'       => ['Token.c', 'Token.h', 'Log.h'],
  'Context.o'     => ['Context.c', 'Context.h', 'ErrorObject.h', 'TokenDebug.h', 'Log.h'],
  'ParserParse.o' => ['ParserParse.c', 'ParserParse.h', 'Parser.h'],
  'Parser.o'      => ['Parser.c', 'Parser.h', 'ParserParse.h', 'Context.h', 'Log.h'],
  'Tokenizer.o'   => ['Tokenizer.c', 'Tokenizer.h', 'ErrorCode.h', 'ErrorObject.h'],
  'Main.o'        => ['Main.c', 'Parser.h', 'ParserParse.h', 'Context.h', 'Log.h'],
  'Main.exe'      => ['Main.o', 'Lexer.o', 'LexerError.o', 'Token.o', 'Parser.o',
                      'ParserParse.o', 'Context.o', 'ErrorObject.o', 'TokenDebug.o',
                      'Tokenizer.o', 'CException.o'],
}

# Support library dependency list
exception_dependency = {'CException.o'  => ['CException.c', 'CException.h']}

# Support dependency list
header_dependency = {
  'Lexer.h'       => ['Symbol.h'],
  'Tokenizer.h'   => ['Common.h', 'Token.h'],
  'Token.h'       => ['Common.h', 'Lexer.h'],
  'ParserParse.h' => ['Token.h', 'Parser.h'],
  'Parser.h'      => ['Token.h', 'Tokenizer.h'],
  'LexerError.h'  => ['Common.h', 'Lexer.h', 'ErrorCode.h'],
  'ErrorObject.h' => ['ErrorCode.h'],
  'DeclarationReader.h' => ['Token.h'],
  'Context.h'     => ['Token.h', 'Parser.h', 'ParserParse.h'],
}

# Configuration parameters
config = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => [CEXCEPTION_PATH,
                    'src', 'src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src/MyFlash'],
  # :user_define  => ['CEXCEPTION_USE_CONFIG_FILE'],
#  :library_path => 'lib',
  :library => ['ws2_32'],
#  :linker_script => 'MyLinkerScript.ld',
#  :compiler_options => ['-DOK'],                 # Other compiler options
#  :linker_options => ['-DOK'],                   # Other linker options
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-T',
                    :define => '-D'}
}

namespace :custom do
  desc 'Build custom release code'
  task :release do
    #            dependency list  directory of   directory of     directory of    config
    #                             dependee       .o files         .exe            object
    compile_list(main_dependency, 'src', 'build/release/host/c', 'build/release', config)
    # compile_list(exception_dependency, CEXCEPTION_PATH, 'build/release/host/c', 'build/release', config)
    compile_list(header_dependency, 'src', 'src', 'build/release', config)
    # p Rake.application.tasks
    Rake::Task["build/release/Main.exe"].invoke
  end
end

namespace :brute do
  desc 'Build brute release code'
  task :release do
    #dep_list = compile_list(exception_dependency, CEXCEPTION_PATH, 'build/release/host/c', '.', config)
    #dep_list.merge!(compile_all(['src'], 'build/release/host/c', config))
    dep_list = compile_all(['src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), 'build/release/Main.exe', config)
    Rake::Task["build/release/Main.exe"].invoke
    #rename the original gdbserver
    sh 'mv C:/CooCox/CoIDE_V2Beta/bin/gdbserver.exe C:/CooCox/CoIDE_V2Beta/bin/gdbserverOrignal.exe' if File.exist? "gdbserverOrignal.exe"
    sh 'mv build/release/Main.exe build/release/gdbserver.exe'                      #rename Main to gdbserver
    sh 'mv build/release/gdbserver.exe C:/CooCox/CoIDE_V2Beta/bin/gdbserver.exe'    #move to desire destination
#    p Rake.application.tasks
#    p Rake::Task.tasks
  end
end

namespace :myflash do
  desc 'Build myflash release code'
  task :release do
    #dep_list = compile_list(exception_dependency, CEXCEPTION_PATH, 'build/release/host/c', '.', config)
    #dep_list.merge!(compile_all(['src'], 'build/release/host/c', config))
    dep_list = compile_all(['src/MyFlash'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), 'build/release/myFlash.exe', config)
    Rake::Task["build/release/myFlash.exe"].invoke
    #rename the original coflash
    sh 'mv C:/CooCox/CoIDE_V2Beta/bin/coflash.exe C:/CooCox/CoIDE_V2Beta/bin/coflashOrignal.exe' if File.exist? "coflashOrignal.exe"
    sh 'mv build/release/myFlash.exe build/release/coflash.exe'                 #rename myFlash to coflash
    sh 'mv build/release/coflash.exe C:/CooCox/CoIDE_V2Beta/bin/coflash.exe'    #move to desire destination
#    p Rake.application.tasks
#    p Rake::Task.tasks
  end
end
