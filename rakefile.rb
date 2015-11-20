PROJECT_CEEDLING_ROOT = "vendor/ceedling"
load "#{PROJECT_CEEDLING_ROOT}/lib/ceedling.rb"

load "scripts/helper.rb"

# With this now we can choose which '.yml' configuration file to be loaded by
# issuing e.g.:  
#     rake project=./myproject.yml test:all
#
project_file = get_value_from_env('p', './project.yml')

Ceedling.load_project(config: project_file)
load_extra_scripts(project_file)

desc 'Test, Build and Deploy'
task :test_build_and_deploy do
  # Test all then build and deploy
  system "rake gdbserver:deploy"
end

task :default => %w[ test:all test_build_and_deploy ]
