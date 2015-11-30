# This will be the default path if auto-locate fails
coide_gdbserver_path = "C:/CooCox/CoIDE_V2Beta/bin"

require 'pathname'
# Load build script to help build C program
load "scripts/cbuild.rb"

# Configuration parameters
config = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => ['src',
                    'src/GDB',
                    'src/ARMSimulator',
                    'src/ElfReader',
                    'src/FloatingPointInstructions',
                    'src/MyFlash'],
  # :user_define  => ['CEXCEPTION_USE_CONFIG_FILE'],
#  :library_path => 'lib',
  :library => ['ws2_32', 'm'],
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

def auto_locate_coide_gdbserver_path(default)
  name = 'start_gdbserver.bat'
  program = `sh -c "which #{name}"`
  if !program.empty?
    dirname = File.dirname program
    dirname.gsub!(/^\/(\w+)/, '\1:') if Gem.win_platform?
    return dirname
  else
    raise ArgumentError,                                                  \
          "Error: Can't locate CoIDE gdbserver path"                      \
                if File.exists? default
  end
  return default
end

namespace :gdbserver do
# coide_gdbserver_path = auto_locate_coide_gdbserver_path(coide_gdbserver_path)

  gdb_target = File.join(coide_gdbserver_path, 'gdbserver.exe')
  flash_target = File.join(coide_gdbserver_path, 'coflash.exe')

  original_gdb = File.join(coide_gdbserver_path, 'gdbserverOriginal.exe')
  original_flash = File.join(coide_gdbserver_path, 'coflashOriginal.exe')

  config_file =  File.join(coide_gdbserver_path, 'config')
  gdb_config_file = File.join(coide_gdbserver_path, 'GDBServerConfig.ini')
  elfLocation_file = File.join(coide_gdbserver_path, 'ElfLocation.txt')

  desc 'Release gdbserver'
  task :release do
    dep_list = compile_all(['src/GDB', 'src/ARMSimulator', 'src/ElfReader', 'src/FloatingPointInstructions', 'src'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), GDBSERVER_FILE, config)
    Rake::Task[GDBSERVER_FILE].invoke

    dep_list = compile_all(['src/MyFlash'], 'build/release/host/c', config)
    link_all(getDependers(dep_list), MYFLASH_FILE, config)
    Rake::Task[MYFLASH_FILE].invoke
  end

  desc 'Build and deploy gdbserver + coflash'
  task :deploy => :release do
    if !up_to_date?(gdb_target, GDBSERVER_FILE)
      if !(File.exists? original_gdb)
        sh "mv #{gdb_target} #{original_gdb}"     #rename the original executable file
      end
      puts "updating gdbserver.exe..."
      sh "cp #{GDBSERVER_FILE} #{gdb_target}"     #move to desire destination
    end

    if !up_to_date?(flash_target, MYFLASH_FILE)
      if !File.exists? original_flash
        sh "mv #{flash_target} #{original_flash}"   #rename the original executable file
      end
      puts "updating coflash.exe..."
      sh "cp #{MYFLASH_FILE} #{flash_target}"     #move to desire destination
    end

    sh "cp config #{config_file}"
    sh "cp GDBServerConfig.ini #{gdb_config_file}"
  end

  desc 'Revert to original gdbserver + coflash'
  task :revert do
    if File.exists? original_gdb
      puts "reverting gdbserver.exe..."
      sh "mv #{original_gdb} #{gdb_target}"
    end
    if File.exists? original_flash
      puts "reverting coflash.exe..."
      sh "mv #{original_flash} #{flash_target}"
    end
    if File.exists? config_file
      sh "rm #{config_file}"
    end
    if File.exists? gdb_config_file
      sh "rm #{gdb_config_file}"
    end
    if File.exists? elfLocation_file
      sh "rm #{elfLocation_file}"
    end
  end
end
