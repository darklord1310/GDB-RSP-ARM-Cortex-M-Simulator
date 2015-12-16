# Build script for C (ver 0.12)
# Copyright (C) 2015-2016 Poh Tze Ven <pohtv@acd.tarc.edu.my>
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
# along with C Compiler & Interpreter.  If not, see <http://www.gnu.org/licenses/>.

require 'rake/clean' if !(defined? CLEAN)
require 'rexml/document'
include REXML

load File.join(File.dirname(__FILE__), 'helper.rb')

$programs_found = {}

# task :clobber => :clean do
  # puts "Clobbering. It may take sometime..."
# end

def appendSlashToPath(path)
  return if path == nil || path == ''
  path[-1] == '/'? path : path + '/'
end

def prependProperPathToFilename(filename, src_path, obj_path, exe_path)
  if filename =~ /.+\.o$/i
    obj_path != '' ? File.join(obj_path, filename) : filename
  elsif filename =~ /.+\.(?:exe|bin|hex|elf|dll)$/i
    exe_path != '' ? File.join(exe_path, filename) : filename
  else
    src_path != '' ? File.join(src_path, filename) : filename
  end
end

def prependProperPathToFilenames(filenames, src_path, obj_path, exe_path)
  # If filenames is a string, then just prepend appropriate path
  if filenames.is_a? String
    [prependProperPathToFilename(filenames, src_path, obj_path, exe_path)]
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

def sys_cli(command)
  result = system command
  sh command if result == nil
end

def compile_list(list, src_path, obj_path, exe_path, config)
  return_list = {}

  src_path = '' if src_path == '.' || src_path == nil
  obj_path = '' if obj_path == '.' || obj_path == nil
  exe_path = '' if exe_path == '.' || exe_path == nil

  FileUtils.mkdir_p obj_path if obj_path != ''
  FileUtils.mkdir_p exe_path if exe_path != ''
  directory obj_path
  directory exe_path

#  src_path = appendSlashToPath(src_path)
#  obj_path = appendSlashToPath(obj_path)
#  exe_path = appendSlashToPath(exe_path)

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
  raise ArgumentError,                                                  \
        "Error: There is nothing to compile."                           \
                if list.empty?
  # Get compiler
  raise ArgumentError,                                                  \
        "Error: Missing ':compiler' in the config"                      \
                if (compiler = trim_string(config[:compiler])) == nil
  compiler = ensure_program_available(compiler,                         \
                          "Error: Cannot find #{compiler} to compile files.")
  # Get linker
  raise ArgumentError,                                                  \
        "Error: Missing ':linker' in the config"                        \
                if (linker = trim_string(config[:linker])) == nil
  linker = ensure_program_available(linker,                             \
                          "Error: Cannot find #{linker} to link files.")

  list.each do |obj|
    # Append path to depender
    depender = prependProperPathToFilenames(obj[0], src_path, obj_path, exe_path)[0]
    # Append path to dependee list
#    dependees = [obj_path, exe_path]
    dependees = []
    dependees.push(*prependProperPathToFilenames(obj[1], src_path, obj_path, exe_path))
    return_list[depender] = dependees
#    p depender
#    p dependees.select { |f| File.directory? f }
    case obj[0]
      when /.+\.o$/i     # Handle object file
        file depender => dependees do |n|
          dependees = n.prerequisites.select { |f|
            (f =~ /\.(?:s|asm|c|cpp|cc|c\+\+)$/i) && !(File.directory? f)
          }
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
          sys_cli(command)
        end
#        p depender
        CLEAN.include(depender)
#        CLOBBER << depender

      when /.+\.(?:exe|bin|hex|elf|dll)$/i        # Handle executable file
        file depender => dependees do |n|
          # Gather only dependee files (exclude directories)
          dependees = n.prerequisites.select { |f| !(File.directory? f) }
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
                    dependees.join(' ') + ' ' +  options + ' ' +              \
                    opt_out_file + ' ' + n.name
          if config[:verbose] == :yes
            puts(command)
          else
            puts("linking #{n.name}...")
          end
          sys_cli(command)
        end
#        p depender
        CLEAN.include(depender)
#        CLOBBER << depender

      else
        file depender => dependees do |n|
          sh "touch #{n.name}"
        end
    end
  end
  return return_list
end

def compile_all(src_paths, obj_path, config)
  return_list = {}
  dependency_list = {}
  depender_list = []

  if !src_paths.is_a? Array
    src_paths = [src_paths]
  end
  src_paths.each do |path|
    raise ArgumentError,                                   \
        "Error: #{path} folder does not exist."            \
                if !File.exist?(path)
    raise ArgumentError,                                   \
        "Error: #{path} is not a folder."                  \
                if !File.directory?(path)
    file_list = FileList.new( File.join(path, '*.s'),      \
                              File.join(path, '*.asm'),    \
                              File.join(path, '*.c'),      \
                              File.join(path, '*.cc'),     \
                              File.join(path, '*.cpp'),    \
                              File.join(path, '*.c++'))
#    trimmed_file_list = file_list.pathmap("%f")
#    p file_list
#    p trimmed_file_list
    # Create dependency list and depender list
    file_list.each do |n|
      name = File.basename(n)
      depender = name.gsub(/\.(?:s|asm|c|cpp|cc|c\+\+)$/i, ".o")
      dependency_list[depender] = [n]
      depender_list << depender
#      # Add to clean and clobber lists
#      CLEAN.include(depender)
#      CLOBBER << depender
    end
#    p dependency_list
  end
  return return_list = compile_list(dependency_list, ".", obj_path, ".", config)
end

def link_all(obj_list, exe_path_and_name, config)
  dependency_list = {File.basename(exe_path_and_name) => obj_list}
  compile_list(dependency_list, '.', '.', File.dirname(exe_path_and_name), config)
end

def getDependers(dependency_list)
  dependency_list.keys
end

def find_coproj(coproj)
  coproj = './' if coproj == nil
  if File.directory? coproj
    directory = coproj
    coproj = FileList.new(File.join coproj, "*.coproj").to_a
    raise ArgumentError,                                                \
        "Please specify the .coproj file: #{coproj}" if coproj.length > 1
    raise ArgumentError,                                                \
        "Error: Cannot find .coproj file in #{directory}" if coproj.length == 0
    coproj = coproj[0]
  else
    coproj = coproj + ".coproj" if !File.exists? coproj
  end
  return coproj
end

# @desc   Collect all sources in coproj file
# @param  coIdeProjectFile is the file coproj file to load
# @param  default_search_path is the default path name to search for coproj
#         file if coIdeProjectFile is not specified
def get_all_source_files_in_coproj(coIdeProjectFile = nil, default_search_path = nil)
  list = []
  coIdeProjectFile = default_search_path if (coIdeProjectFile == nil) ||            \
                                            (trim_string(coIdeProjectFile).empty?)
  xmlfile = File.new(coproj = find_coproj(coIdeProjectFile))
  xmldoc = Document.new(xmlfile)

  # Now get the root element
  root = xmldoc.root
#  puts "Root element : " + root.attributes["version"]

  path = File.dirname(coproj)
  xmldoc.elements.each("Project/Files/File") { |e|
    name = e.attributes["path"]
#    puts "File name : " + name if e.attributes["type"] == "1"  && name =~ /\.(?:c|cc|cpp|c++|s|asm)$/i
#    puts "File name : " + name if e.attributes["type"] == "1"
    list << File.join(path, name) if e.attributes["type"] == "1"
  }
  return list, coproj
end

def match_extensions(name, ext_filter_list)
  exts = [ext_filter_list.each {|n| trim_string(n).gsub!(/^\./, "") }]
  name =~ /#{"\\.(?:#{exts.join("|")})$"}/i
end

def createCompilationDependencyList(list, ext_filter_list, out_path, out_ext)
  dependency_list = {}
  out_path = '' if out_path == '.' || out_path == nil
  list = list.select {|n| n if match_extensions(n, ext_filter_list) }
  dependers = list.map {|n|
    name = File.basename(n.gsub(/\.[^\/]+$/i, out_ext))
    out_path == '' ? File.join(out_path, name) : name
  }
  dependers.zip(list) { |key, val| dependency_list[key] = val }
  dependency_list
end

def get_all_tests(path)
  filenames = FileList.new(path)
  filenames = filenames.map {|f| 'test:' + File.basename(f, '.')}
end