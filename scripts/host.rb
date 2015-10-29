COIDE_PATH = "C:/CooCox/CoIDE_V2Beta/bin"

# Load build script to help build C program
load "scripts/cbuild.rb"

# Configuration parameters
config = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => ['src', 'src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src/MyFlash'],
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

GDBSERVER_FILE = "build/release/gdbserver.exe"
MYFLASH_FILE   = "build/release/myFlash.exe"

namespace :gdbserver do
  gdb_target = "#{COIDE_PATH}/gdbserver.exe"
  flash_target = "#{COIDE_PATH}/coflash.exe"
  original_gdb = "#{COIDE_PATH}/gdbserverOriginal.exe"
  original_flash = "#{COIDE_PATH}/coflashOriginal.exe"
  desc 'Build and deploy gdbserver + coflash'
  task :deploy do
    dep_list = compile_all(['src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), 'build/release/gdbserver.exe', config)
    Rake::Task[GDBSERVER_FILE].invoke
    if !up_to_date?(gdb_target, GDBSERVER_FILE)
      sh "mv #{gdb_target} #{original_gdb}"       #rename the original executable file
      sh "cp #{GDBSERVER_FILE} #{gdb_target}"     #move to desire destination
    end
    
    dep_list = compile_all(['src/MyFlash'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), 'build/release/myFlash.exe', config)
    Rake::Task[MYFLASH_FILE].invoke
    if !up_to_date?(flash_target, MYFLASH_FILE)
      sh "mv #{flash_target} #{original_flash}"   #rename the original executable file
      sh "cp #{MYFLASH_FILE} #{flash_target}"     #move to desire destination
    end
  end
  
  desc 'Revert to original gdbserver + coflash'
  task :revert do
    if File.exist? original_gdb
      sh "mv #{original_gdb} #{gdb_target}"
    end
    if File.exist? original_flash
      sh "mv #{original_flash} #{flash_target}"
    end
  end
end
