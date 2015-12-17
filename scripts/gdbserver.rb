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
#  :user_define  => ['GDBSERVER_MAIN_EXPORTS'],      #['CEXCEPTION_USE_CONFIG_FILE'],
# :library_path => 'lib',
  :library => ['ws2_32', 'm'],
# :linker_script => 'MyLinkerScript.ld',
# :compiler_options => ['-DOK'],                  # Other compiler options
  :linker_options => ['-g'],    # Other linker options
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-T',
                    :define => '-D'}
}

config_myflash = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => ['src'],
#  :user_define  => ['GDBSERVER_MAIN_EXPORTS'],      #['CEXCEPTION_USE_CONFIG_FILE'],
#  :library_path => 'lib',
#  :library => [''],
#  :linker_script => 'MyLinkerScript.ld',
#  :compiler_options => ['-DOK'],                  # Other compiler options
#  :linker_options => [''],    # Other linker options
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-T',
                    :define => '-D'}
}

# config_dll = {
  # :verbose      => :no,
  # :compiler     => 'gcc',
  # :linker       => 'gcc',
  # :include_path => ['src',
                    # 'src/GDB',
                    # 'src/ARMSimulator',
                    # 'src/ElfReader',
                    # 'src/FloatingPointInstructions',
                    # 'src/MyFlash'],
  # :user_define  => ['GDBSERVER_MAIN_EXPORTS'],    #['CEXCEPTION_USE_CONFIG_FILE'],
  # :library_path => 'lib',
  # :library => ['ws2_32', 'm'],
  # :linker_script => 'MyLinkerScript.ld',
  # :compiler_options => ['-DOK'],                  # Other compiler options
  # :linker_options => ['-g',
                      # '-s',
                      # '-shared',
                      # '-Wl,--subsystem,windows'], # Other linker options
  # :option_keys  => {:library => '-l',
                    # :library_path => '-L',
                    # :include_path => '-I',
                    # :output_file => '-o',
                    # :compile => '-c',
                    # :linker_script => '-T',
                    # :define => '-D'}
# }

config_dll = {
  :verbose      => :yes,
  :compiler     => 'gcc',
  :linker       => 'gcc',
  :include_path => ['src',
                    'src/GDB',
                    'src/ARMSimulator',
                    'src/ElfReader',
                    'src/FloatingPointInstructions',
                    'src/MyFlash'],
#  :user_define  => ['GDBSERVER_MAIN_EXPORTS'],    #['CEXCEPTION_USE_CONFIG_FILE'],
#  :library_path => 'lib',
  :library => ['ws2_32', 'm'],
#  :linker_script => 'MyLinkerScript.ld',
#  :compiler_options => ['-DOK'],                  # Other compiler options
  :linker_options => ['-g',
                      '-shared',
                      '-Wl,--add-stdcall-alias'], # Other linker options
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
ARM_M_PROFILE_XML = "data/arm-m-profile.xml"
ARM_VFPV2_XML = "data/arm-vfpv2.xml"

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
  dll_file = File.join(coide_gdbserver_path, 'gdbserver.dll')
  
  arm_profile_target = File.join(coide_gdbserver_path, 'target_desc/arm-m-profile.xml')
  vfpv2_target = File.join(coide_gdbserver_path, 'target_desc/arm-vfpv2.xml')
  
  original_arm_profile = File.join(coide_gdbserver_path, 'target_desc/arm-m-profileOriginal.xml')
  original_vfpv2 = File.join(coide_gdbserver_path, 'target_desc/arm-vfpv2Original.xml')

  desc 'Release gdbserver'
  task :release do
    dep_list = compile_all(['src/GDB',
                            'src/GDB/main',
                            'src/GDB/dll',
                            'src/ARMSimulator',
                            'src/ElfReader',
                            'src/FloatingPointInstructions',
                            'src'],
                            'build/release/host/c',
                            config)
    link_all(getDependers(dep_list), GDBSERVER_FILE, config)
    Rake::Task[GDBSERVER_FILE].invoke

    dep_list = compile_all(['src/MyFlash'], 'build/release/host/c', config_myflash)
    link_all(getDependers(dep_list), MYFLASH_FILE, config_myflash)
    Rake::Task[MYFLASH_FILE].invoke
  end

  desc 'Build and deploy gdbserver + coflash'
  task :deploy_all => :release do
    if !up_to_date?(gdb_target, GDBSERVER_FILE)
      if !(File.exists? original_gdb)
        sh "mv #{gdb_target} #{original_gdb}"     #rename the original executable file
      end
      puts "updating gdbserver.exe..."
      sh "cp #{GDBSERVER_FILE} #{gdb_target}"     #move to desire destination
    end

    if !up_to_date?(flash_target, MYFLASH_FILE)
      if !File.exists? original_flash
        sh "mv #{flash_target} #{original_flash}" #rename the original executable file
      end
      puts "updating coflash.exe..."
      sh "cp #{MYFLASH_FILE} #{flash_target}"     #move to desire destination
    end

    if !File.exists? original_arm_profile
        sh "mv #{arm_profile_target} #{original_arm_profile}"
        puts "updating arm-m-profile.xml..."
        sh "cp #{ARM_M_PROFILE_XML} #{arm_profile_target}"
    end
    
    if !File.exists? original_vfpv2
        sh "mv #{vfpv2_target} #{original_vfpv2}"
        puts "updating arm-vfpv2.xml..."
        sh "cp #{ARM_VFPV2_XML} #{vfpv2_target}"
    end

    sh "cp config #{config_file}"
    sh "cp GDBServerConfig.ini #{gdb_config_file}"
    # sh "cp build/release/dll/gdbserver.dll #{dll_file}"
  end

  desc 'Revert to original gdbserver + coflash'
  task :revert_all do
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
    if File.exists? dll_file
      sh "rm #{dll_file}"
    end

    if File.exists? original_arm_profile
      puts "reverting arm-m-profile.xml..."
      sh "mv #{original_arm_profile} #{arm_profile_target}"
    end
    if File.exists? original_vfpv2
      puts "reverting arm-vfpv2.xml..."
      sh "mv #{original_vfpv2} #{vfpv2_target}"
    end
  end
end

namespace :build do
  dll_library = "build/release/dll/gdbserver.dll"
  desc 'Release gdbserver DLL'
  task :dll do
    dep_list = compile_all(['src/GDB',
                            'src/GDB/dll',
                            'src/GDB/main',
                            'src/ARMSimulator',
                            'src/ElfReader',
                            'src/FloatingPointInstructions',
                            'src'],
                            'build/release/dll',
                            config_dll)
    link_all(getDependers(dep_list), dll_library, config_dll)
    Rake::Task[dll_library].invoke
  end
end
