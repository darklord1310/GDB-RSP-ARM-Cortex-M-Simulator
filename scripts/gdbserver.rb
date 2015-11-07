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
 :linker_options => ['-g'],                       # Other linker options
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

  config_file =  "#{COIDE_PATH}/config"
  gdb_config_file =  "#{COIDE_PATH}/GDBServerConfig.ini"
  elfLocation_file = "#{COIDE_PATH}/ElfLocation.txt"

  desc 'Release gdbserver'
  task :release do
    dep_list = compile_all(['src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), GDBSERVER_FILE, config)
    Rake::Task[GDBSERVER_FILE].invoke

    dep_list = compile_all(['src/MyFlash'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), MYFLASH_FILE, config)
    Rake::Task[MYFLASH_FILE].invoke
  end

  desc 'Build and deploy gdbserver + coflash'
  task :deploy => :release do
    if !up_to_date?(gdb_target, GDBSERVER_FILE)
      if !File.exist? original_gdb
        sh "mv #{gdb_target} #{original_gdb}"     #rename the original executable file
      end
      sh "cp #{GDBSERVER_FILE} #{gdb_target}"     #move to desire destination
    end

    if !up_to_date?(flash_target, MYFLASH_FILE)
      if !File.exist? original_flash
        sh "mv #{flash_target} #{original_flash}"   #rename the original executable file
      end
      sh "cp #{MYFLASH_FILE} #{flash_target}"     #move to desire destination
    end

    sh "cp config #{config_file}"
    sh "cp GDBServerConfig.ini #{gdb_config_file}"
  end

  desc 'Revert to original gdbserver + coflash'
  task :revert do
    if File.exist? original_gdb
      sh "mv #{original_gdb} #{gdb_target}"
    end
    if File.exist? original_flash
      sh "mv #{original_flash} #{flash_target}"
    end
    if File.exist? config_file
      sh "rm #{config_file}"
    end
    if File.exist? gdb_config_file
      sh "rm #{gdb_config_file}"
    end
    if File.exist? elfLocation_file
      sh "rm #{elfLocation_file}"
    end
  end
end
