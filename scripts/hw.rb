#FLASHER = "\"/C/Program Files (x86)/STMicroelectronics/STM32 ST-LINK Utility/ST-LINK Utility/ST-LINK_CLI\" "
FLASHER = "ST-LINK_CLI "

# Load build script to help build C program
load "scripts/cbuild.rb"

# Configuration parameters
config = {
  :verbose      => :no,
  :compiler     => 'arm-none-eabi-gcc',
  :linker       => 'arm-none-eabi-gcc',
# -IC:\Users\user26\CoIDE\workspace\RTOS
  :include_path => ['../STM32Cube_FW_F4_V1.5.0/Drivers/STM32F4xx_HAL_Driver/Inc',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/STM32F4xx_HAL_Driver',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/CMSIS',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/CMSIS/Device/ST',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/CMSIS/Device/ST/STM32F4xx',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/CMSIS/Device/ST/STM32F4xx/Include',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers/CMSIS/Include',
                    '../STM32Cube_FW_F4_V1.5.0/Drivers',
                    'app'],
  :user_define  => ['STM32F429ZI', 'STM32F429xx'],
  :library_path => '.',
#  :library => ['libusb'],
  :linker_script => 'stm32f429zi_flash.ld',
  :compiler_options => ['-mcpu=cortex-m4 -mthumb -g2 -Wall -O0 -g'],          # Other compiler options
  :linker_options => ['-mcpu=cortex-m4 -mthumb -g2 -O0 -Wl,--gc-sections'],   # Other linker options
  :option_keys  => {:library => '-l',
                    :library_path => '-L',
                    :include_path => '-I',
                    :output_file => '-o',
                    :compile => '-c',
                    :linker_script => '-Wl,-T',
                    :define => '-D'}
}

namespace :hw do
  task :prepare_release do
    filenames = getAllSrcFiles("RTOS.coproj")
    dep_list = createCompilationDependencyList(filenames, ['c', '.c++', '.s', 'cpp', 'asm'], '.', '.o')
    dep_list = compile_list(dep_list, '.', 'build/release/hw', '.', config)
    link_all(getDependers(dep_list), 'build/release/hw/RTOS.elf', config)

    file 'build/release/hw/RTOS.hex' => 'build/release/hw/RTOS.elf' do |n|
      puts "converting #{n.prerequisites[0]} to hex..."
      system "arm-none-eabi-objcopy -O ihex #{n.prerequisites[0]} #{n.name}"
    end
  end
  CLEAN.include('build/release/hw') if File.exist? 'build/release/hw'

  desc 'Build hardware release code'
  task :release => :prepare_release do
  #  p Rake.application.tasks
    Rake::Task["build/release/hw/RTOS.elf"].invoke
  end


  desc 'Flash program and run test'
  task :flash => :prepare_release do
    Rake::Task["build/release/hw/RTOS.hex"].invoke
    system (FLASHER + '-P build/release/hw/RTOS.hex -V while_programming -Rst -Run')
  end
end
