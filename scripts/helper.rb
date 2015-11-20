require 'yaml'
require 'mkmf'

def load_extra_scripts(project_file)
  raise ArgumentError, "Error: Can't find #{project_file} file."        \
                                          if !File.exist?(project_file)
  content = YAML.load_file project_file
  if content.has_key? :project
    scripts_to_load = content[:project][:load_scripts]
    if scripts_to_load
      if scripts_to_load.is_a? Array
        scripts_to_load.each { |script|
          load script
        }
      else
        load scripts_to_load
      end
    end
  end
end

def get_value_from_env(name, default_value)
  trim_string((flasher = ENV[name]) ? String.new(flasher):default_value)
end

def trim_string(str)
  return nil if str == nil
  str.gsub!(/^\s*/, "").gsub!(/\s*$/, "")
end

def up_to_date?(new, old)
  if File.exist?(new) && File.exist?(old)
    return true if File.mtime(new) > File.mtime(old)
  end
  return false
end

# @desc If currently running under Windows, convert the path into Windows
#       form if it is defined in *nix form, otherwise do nothing.
# @note If currently running in *nix, and the path is in Windows form,
#       this function will fail to convert it into the correct *nix form.
#       (Todo: fix this)
def to_native_path(filename)
  (return filename.gsub(/\//, '\\')) if Gem.win_platform?
  filename
end

# @desc Convert the path into *nix form irregardless of running platform
def to_unix_path(filename)
  filename.gsub(/\\/, '/')
end

def program_available?(filename)
  $programs_found[filename] =
    if (name = trim_string (to_unix_path filename))[0] == '.'
      find_executable(File.basename(name), File.dirname(name))
    else
      find_executable(name)
    end if !$programs_found.key? filename
  $programs_found[filename]
end

# @desc   Ensure the program is available and put the filename into native form
# @param  filename is the name of the program to verify
# @param  error_msg is the message enclosed in an exception if file not
#         available
# @return native path name enclosed in double quotations
def ensure_program_available(filename, error_msg)
  raise ArgumentError, error_msg if program_available?(to_unix_path filename) == nil
  '"' + to_native_path(filename) + '"'
end