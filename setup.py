import sys
import os
import subprocess
import configparser

# v2.1 of magic make

CONFIG_FILE = "config.ini"

def build_script():
    print("Hi.\n")
    prompt_os = "Pick OS\n"
    prompt_os += "If you press something that is not in the options, I will simply crash this script. Please don't test my patience.\n"

    type_os = choose_option(prompt_os, ["Windows", "Linux"])
    type_build = choose_option("Pick Build type", ["Debug", "Release"])
    type_compiler = choose_option("Pick Compiler", ["clang", "gcc", "msvc"])
    type_build_system = choose_option("Pick cmake generator", ["ninja", "makefile"])

    innit(type_os)

    cum = "cmake " +  build_compiler_type(type_compiler) +  " -B " + build_path_command(type_build)
    cum += "\ -G " + build_generator(type_build_system, type_os)  + "\n"
    cum += "cd " + build_path_command(type_build) + "\n"
    cum += build_generator_command(type_build_system)

    cum_name = get_script_name(type_os)
    save_script_to_config(cum_name, cum)

    print(cum)

def choose_option(prompt, options):
    while True:
        print(prompt)
        for idx, opt in enumerate(options, start=1):
            print(f"{idx}. {opt}")
        choice = input("Enter the number of your choice: ")
        try:
            choice = int(choice)
            if 1 <= choice <= len(options):
                return options[choice - 1]
            else:
                print("Invalid choice. Please select a valid option.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

def build_type_command(build_type):
    prefix = "-DCMAKE_BUILD_TYPE="

    dick = {}
    dick["Debug"] = "Debug"
    dick["Release"] = "Release"

    return prefix + dick[build_type]

def build_path_command(build_type):
    prefix = "out/"
    dick = {}
    dick["Debug"] = "debug"
    dick["Release"] = "release"

    return prefix +  dick[build_type]

def build_compiler_type(build_type):
    dick = {}
    dick["clang"] = "-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"
    dick["gcc"] = "-DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++"
    dick["msvc"] = "-DCMAKE_C_COMPILER=cl -DCMAKE_CXX_COMPILER=cl"

    return dick[build_type]

def build_generator(build_type, os_type):
    dick = {}
    dick["ninja"] = "\"Ninja\""

    if os_type == "Windows":
        dick["makefile"] = "\"MinGW Makefiles\""
    elif os_type == "Linux":
        dick["makefile"] = "\"Unix Makefiles\""
    else:
        print("Invalid OS selection.")
        exit()

    return dick[build_type]

def build_generator_command(build_type):
    dick = {}
    dick["ninja"] = "ninja"
    dick["makefile"] = "make"

    return dick[build_type]

def innit(os_type):
    if os_type == "Windows":
        subprocess.call(["scripts\\internal\\innit.bat"])
        print("f \n")
    elif os_type == "Linux":
        subprocess.call(["scripts/internal/innit.sh"])

def get_script_name(os_type):
    cum_name = "temp_script"
    if(os_type == "Windows"):
        cum_name += ".bat"
    elif(os_type == "Linux"):
        cum_name += ".sh"
    return cum_name

def save_script_to_config(script_name, script_data):
    config = read_config()
    config.set('General', 'last_script_name', script_name)
    config.set('General', 'last_script_data', script_data)
    write_config(config)

def load_script_from_config():
    config = read_config()
    script_name = config.get('General', 'last_script_name', fallback=None)
    script_data = config.get('General', 'last_script_data', fallback=None)
    return script_name, script_data

def execute_script(script_name, script_data):
    if script_name and script_data:
        with open(script_name, 'w') as f:
            f.write(script_data)

        if os.name == 'posix' and script_name.endswith('.sh'):
            subprocess.call(["bash", script_name])  # Execute as a shell script on Unix-based systems
        else:
            subprocess.call([script_name])  # Execute on Windows and other systems

        os.remove(script_name)

def run_last_script():
    script_name, script_data = load_script_from_config()
    if script_name and script_data:
        print("Executing the last script:\n")
        print(script_data)
        execute_script(script_name, script_data)
    else:
        print("No last script found in the config.ini file.")

def read_config():
    config = configparser.ConfigParser()
    
    if not os.path.exists(CONFIG_FILE):
        config.add_section('General')
        write_config(config)
    else:
        config.read(CONFIG_FILE)
    
    return config

def write_config(config):
    with open(CONFIG_FILE, 'w') as configfile:
        config.write(configfile)

if __name__ == "__main__":
    if(len(sys.argv) == 2):
        if(sys.argv[1] == "r"):
            run_last_script()
            exit()

    build_script()
    execute_script(*load_script_from_config())