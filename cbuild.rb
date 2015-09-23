# Build script for C
# Copyright (C) 2015 Poh Tze Ven, <pohtv@acd.tarc.edu.my>
#
# This file is part of C Compiler & Interpreter project.
#
# C Compiler & Interpreter is free software, you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# C Compiler & Interpreter is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with GDB RSP and ARM Simulator.  If not, see <http://www.gnu.org/licenses/>.

def appendSlashToPath(path)
  path[-1] == '/'? path : path + '/'
end

def prependProperPathToFilename(filename, src_path, obj_path, exe_path)
  if filename =~ /.+\.o$/
    obj_path + filename
  elsif filename =~ /.+\.exe$/
    exe_path + filename
  else
    src_path + filename
  end
end

def prependProperPathToFilenames(filenames, src_path, obj_path, exe_path)
  # If filenames is a string, then just prepend appropriate path
  if filenames.is_a? String
    prependProperPathToFilename(filenames, src_path, obj_path, exe_path)
  else
    filenames.map { |f|
      prependProperPathToFilename(f, src_path, obj_path, exe_path)
    }
  end
end

def optionize(option_key, data, err_msg)
  return '' if data == nil
  raise ArgumentError, "Error: #{err_msg}" if option_key == nil
  if data.is_a? Array
    data.map { |d|
      option_key + d
    }.join(' ') + ' '
  else
    option_key + data + ' '
  end
end

def compile_list(list, src_path, obj_path, exe_path, config)
  FileUtils.mkdir_p obj_path
  FileUtils.mkdir_p exe_path
  directory obj_path
  directory exe_path
  src_path = appendSlashToPath(src_path)
  obj_path = appendSlashToPath(obj_path)
  exe_path = appendSlashToPath(exe_path)

  raise ArgumentError,                                                        \
        "Error: Missing ':option_keys:output_file' in the config."            \
        if (opt_out_file = config[:option_keys][:output_file]) == nil
  # Get compiler options
  opt_inc_path = config[:option_keys][:include_path]
  opt_out_file = config[:option_keys][:output_file]
  opt_compile = config[:option_keys][:compile]
  opt_define = config[:option_keys][:define]
  # Get linker options
  opt_lib = config[:option_keys][:library]
  opt_lib_path = config[:option_keys][:library_path]
  opt_linker_script = config[:option_keys][:linker_script]

  list.each do |obj|
    # Append path to depender
    depender = prependProperPathToFilenames(obj[0], src_path, obj_path, exe_path)
    # Append path to dependee list
#    dependees = [obj_path, exe_path]
    dependees = []
    dependees += prependProperPathToFilenames(obj[1], src_path, obj_path, exe_path)
#    p dependees
#    p dependees.select { |f| File.directory? f }  
    file depender => dependees do |n|
      case obj[0]
        when /.+\.o$/     # Handle object file
          dependees = n.prerequisites.select { |f|
            f =~ /.+\.c$/ || f =~ /.+\.cpp$/ || f =~ /.+\.cc$/
          }
          # Get compiler
          raise ArgumentError,                                                \
                "Error: Missing ':compiler' in the config"                    \
                if (compiler = config[:compiler]) == nil
          # Compile compiler options
          options = optionize(opt_inc_path, config[:include_path],            \
                      "Missing ':option_keys:include_path' in the config.") + \
                    optionize(opt_define, config[:user_define],               \
                      "Missing ':option_keys:include_path' in the config.") + \
                    ' ' + optionize('', config[:compiler_options], nil)
          # Compile the command
          command = compiler + ' ' + opt_compile + ' ' +                      \
                    options + ' ' + dependees.join(' ') + ' ' +               \
                    opt_out_file + ' ' + n.name
          if config[:verbose] == :yes
            puts(command)
          else
            puts("compiling #{n.name}...")
          end
          system(command)
        when /.+\.exe$/   # Handle executable file
          # Gather only dependee files (exclude directories)
          dependees = n.prerequisites.select { |f| !(File.directory? f) }
          # Get linker
          raise ArgumentError,                                                \
                "Error: Missing ':linker' in the config"                      \
                if (linker = config[:linker]) == nil
          # Compile linker options
          options = optionize(opt_lib_path, config[:library_path],            \
                      "Missing ':option_keys:library_path' in the config.") + \
                    optionize(opt_lib, config[:library],                      \
                      "Missing ':option_keys:library' in the config.") +      \
                    optionize(opt_linker_script, config[:linker_script],      \
                      "Missing ':option_keys:linker_script' in the config.") +\
                    ' ' + optionize('', config[:linker_options], nil)
          # Compile the command
          command = linker + ' ' +                                            \
                    options + ' ' + dependees.join(' ') + ' ' +               \
                    opt_out_file + ' ' + n.name
          if config[:verbose] == :yes
            puts(command)
          else
            puts("linking #{n.name}...")
          end
          system(command)
        else
          raise TypeError, "Error: Sorry, don't know how to produce '#{obj[0]}'"
      end
    end
  end
end
