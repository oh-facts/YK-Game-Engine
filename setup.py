import subprocess
import os
import configparser

SCRIPTS_FOLDER = "scripts\internal"
CONFIG_FILE = "config.ini"

def main():
    print("\nWelcome! I'll help compile the engine for you.")

    setup_option = choose_option("\nChoose an option:", ["First time setup", "Reload last script"])

    if setup_option == 1:
        platform = choose_option("\nChoose a platform:", ["Windows", "Docker (headless)"])
        if platform == 1:
            build_type = choose_option("\nChoose build type:", ["Debug", "Release", "Debug - Headless", "Release - Headless"])
            script_options = ["dgen.bat", "gen.bat", "dgen_h.bat", "gen_h.bat"]
            if build_type in range(1, len(script_options) + 1):
                execute_script(os.path.join(SCRIPTS_FOLDER, script_options[build_type - 1]))
            else:
                print("Invalid build type. Exiting.\n")
        elif platform == 2:
            execute_script(os.path.join(SCRIPTS_FOLDER,"docker_image.bat"))
        else:
            print("Invalid platform choice. Exiting.\n")
    elif setup_option == 2:
        last_script = get_last_script()
        if last_script:
            execute_script(last_script)
        else:
            print("No last script found. Exiting.\n")
    else:
        print("Invalid option. Exiting.\n")

def choose_option(prompt, options):
    print(prompt)
    for i, option in enumerate(options, start=1):
        print(f"{i}. {option}")
    while True:
        try:
            choice = int(input("\nEnter the number of your choice: \n"))
            if 1 <= choice <= len(options):
                return choice
            else:
                print("\nInvalid choice. Please enter a valid number.\n")
        except ValueError:
            print("\nInvalid input. Please enter a number.\n")

def execute_script(script_path):
    try:
        subprocess.run([script_path], shell=True, check=True)
        print("\nScript execution successful!\n")
        update_last_script(script_path)
    except subprocess.CalledProcessError:
        print(f"\nError executing {script_path} script.\n")

def update_last_script(script_path):
    config = read_config()
    config.set('General', 'last_script', script_path)
    write_config(config)

def get_last_script():
    config = read_config()
    if config.has_option('General', 'last_script'):
        return config.get('General', 'last_script')
    else:
        return None

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
    main()