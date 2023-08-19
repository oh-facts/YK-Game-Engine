import subprocess
import os

SCRIPTS_FOLDER = "scripts"

def main():
    print("Welcome! I'll help compile the engine for you")

    platform = choose_option("Choose a platform:", ["Windows", "Docker"])

    if platform == 1:
        build_type = choose_option("Choose build type:", ["Debug", "Release"])
        if build_type == 1:
            execute_script(os.path.join(SCRIPTS_FOLDER, "dgen.bat"))
        elif build_type == 2:
            execute_script(os.path.join(SCRIPTS_FOLDER, "gen.bat"))
        else:
            print("Invalid build type. Exiting.")
    elif platform == 2:
        execute_script(os.path.join(SCRIPTS_FOLDER, "docker.sh"))
    else:
        print("Invalid platform choice. Exiting.")

def choose_option(prompt, options):
    print(prompt)
    for i, option in enumerate(options, start=1):
        print(f"{i}. {option}")
    while True:
        try:
            choice = int(input("Enter the number of your choice: "))
            if 1 <= choice <= len(options):
                return choice
            else:
                print("Invalid choice. Please enter a valid number.")
        except ValueError:
            print("Invalid input. Please enter a number.")

def execute_script(script_path):
    try:
        subprocess.run([script_path], shell=True, check=True)
        print("Script execution successful!")
    except subprocess.CalledProcessError:
        print(f"Error executing {script_path} script.")

if __name__ == "__main__":
    main()