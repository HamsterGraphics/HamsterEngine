import colorama
from colorama import Fore
import platform
import os
import requests
import shutil
import subprocess
import sys
import threading
import zipfile

def check_cmake_installed():
    cmake_path = shutil.which("cmake")
    if cmake_path:
        print(f"{Fore.GREEN}CMake is installed: {cmake_path}{Fore.RESET}")
        get_cmake_version()
    else:
        print(f"{Fore.RED}CMake is not installed.{Fore.RESET}")
        return False
    
    return True

def get_cmake_version():
    try:
        result = subprocess.run(["cmake", "--version"], capture_output=True, text=True, check=True)
        version_line = result.stdout.splitlines()[0]  # Extract the first line (e.g., "cmake version 3.26.4")
        print(f"{Fore.GREEN}CMake Version: {version_line}{Fore.RESET}")
    except subprocess.CalledProcessError:
        print(f"{Fore.RED}Error retrieving CMake version.{Fore.RESET}")

def get_platform_info():
    # Get the platform name
    system = platform.system()

    # Map system names to more user-friendly platform names
    platform_map = {
        "Windows": "Windows",
        "Darwin": "MacOS",
        "Linux": "Linux"
    }

    # Get the platform name from the map or default to 'Unknown'
    platform_name = platform_map.get(system, "Unknown")
    
    # Get CPU architecture information
    cpu_arch = platform.machine()  # 'x86_64', 'AMD64', 'i386', 'armv7l', etc.
    bit_arch = platform.architecture()[0]  # '32bit' or '64bit'

    return platform_name, cpu_arch, bit_arch

def stream_output(pipe, color=Fore.WHITE):
    """Continuously read a process's output and print it in real-time."""
    for line in iter(pipe.readline, ''):
        print(color + line.strip() + Fore.RESET) 
        sys.stdout.flush()  # Ensure real-time output
    pipe.close()

def run_command(cmd, cwd=None):
    """Runs a shell command and streams stdout/stderr in real-time."""
    process = subprocess.Popen(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, bufsize=1, universal_newlines=True)

    # Start separate threads to read stdout and stderr without blocking
    stdout_thread = threading.Thread(target=stream_output, args=(process.stdout, Fore.WHITE))
    stderr_thread = threading.Thread(target=stream_output, args=(process.stderr, Fore.YELLOW))
    stdout_thread.start()
    stderr_thread.start()

    # Wait for the process and threads to finish
    process.wait()
    stdout_thread.join()
    stderr_thread.join()

    if process.returncode != 0:
        print(f"{Fore.RED}Command failed with exit code {process.returncode}.{Fore.RESET}")
        exit(process.returncode)

def build_cmake_project(project_name, configFlags, buildFlags):
    source_dir = os.path.abspath("Engine/Source/ThirdParty/" + project_name)
    
    if not os.path.exists(source_dir):
        print(f"{Fore.RED}Error: Source directory '{source_dir}' not found!{Fore.RESET}")
        exit(1)
    
    # Define CMake options for output directory
    cmake_build_dir = os.path.abspath("Engine/Intermediate/" + project_name)
    cmake_output_dir = os.path.abspath("Engine/Binaries/" + project_name)
    
    os.makedirs(cmake_build_dir, exist_ok=True)
    os.makedirs(cmake_output_dir, exist_ok=True)
    
    cmake_path = shutil.which("cmake")
    
    # Define CMake options
    cmake_generator = "Visual Studio 17 2022"
    cmake_cxx_flags = "/MT"
    
    cmake_cmd = [
        cmake_path, source_dir, 
        "-G", cmake_generator,
        f"-DCMAKE_CXX_FLAGS={cmake_cxx_flags}",
        f"-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY={cmake_output_dir}/lib",
        f"-DCMAKE_LIBRARY_OUTPUT_DIRECTORY={cmake_output_dir}/lib",
        f"-DCMAKE_RUNTIME_OUTPUT_DIRECTORY={cmake_output_dir}/bin"
    ]
    
    # Add any user-provided config flags to the CMake command
    for configFlag in configFlags:
        cmake_cmd.append(configFlag)
    
    # Run CMake configuration
    run_command(cmake_cmd, cwd=cmake_build_dir)

    # Run CMake build
    build_cmd = [cmake_path, "--build", "."]
    
    for buildFlag in buildFlags:
        build_cmd.append(buildFlag)
    
    # Run the build command
    run_command(build_cmd, cwd=cmake_build_dir)

def run_batch_file(batch_file, build_dir):
    """Runs a .bat file using cmd.exe"""
    if not os.path.exists(batch_file):
        print(f"{Fore.RED}Error: Batch file '{batch_file}' not found!{Fore.RESET}")
        exit(1)

    run_command(f'cmd.exe /c "{batch_file}"', cwd=build_dir)  # Use cmd.exe to execute the .bat file

def extract_zip(zip_path, extract_to):
    os.makedirs(extract_to, exist_ok=True)
    with zipfile.ZipFile(zip_path, 'r') as zip_ref:
        zip_ref.extractall(extract_to)
        return True
        
    return False

def download_package(url, destination_path):
    try:
        # Send GET request to the URL
        response = requests.get(url, stream=True)
        
        # Check if the request was successful (status code 200)
        if response.status_code == 200:
            # Open the file in write-binary mode and save the content
            with open(destination_path, 'wb') as file:
                for chunk in response.iter_content(chunk_size=8192):
                    file.write(chunk)

            print(f"{Fore.GREEN}Download successful! File saved to {destination_path}")
            return True
        else:
            print(f"{Fore.RED}Failed to download. HTTP status code: {response.status_code}")
            return False
    except Exception as e:
        print(f"{Fore.RED}An error occurred: {e}")
        return False

def get_release_url(base_url, platform_name, cpu_arch, bit_arch):
    release_url = base_url + platform_name.lower()
    if (cpu_arch == "x86_64" or cpu_arch == "AMD64") and bit_arch == "64bit":
        release_url = release_url + "-x86_64.zip"
    elif cpu_arch == "aarch64" and bit_arch == "64bit":
        release_url = release_url + "-aarch64.zip"
    else:
        return None
        
    return release_url

def build_third_party_projects():
    # cpu_features
    print(f"\n{Fore.CYAN}[cpu_features] Start making project...")
    build_cmake_project("cpu_features", ["-DBUILD_TESTING=OFF"], ["--config", "Release"])
    
    # JoltPhysics
    print(f"\n{Fore.CYAN}[JoltPhysics] Start making project...")
    build_cmake_project("JoltPhysics/Build", ["-DENABLE_ALL_WARNINGS=OFF"], ["--config", "Release"])
    
    # ozz-animation
    print(f"\n{Fore.CYAN}[ozz-animation] Start making project...")
    build_cmake_project("ozz-animation", ["-DCMAKE_CXX_FLAGS=/EHsc", "-Dozz_build_tests=OFF", "-Dozz_build_samples=OFF"], ["--config", "Release"])    
    
def download_third_party_packages():
    # slang
    slang_release_version = "v2025.5"
    slang_base_url = f"https://github.com/shader-slang/slang/releases/download/{slang_release_version}/"
    slang_release_pkg_name = get_release_url("slang-2025.5-", platform_name, cpu_arch, bit_arch)
    slang_release_url = slang_base_url + slang_release_pkg_name
    print(f"\n{Fore.CYAN}[slang] Parsed release package url : {slang_release_url}")
    slang_zip_directory = os.path.abspath("Engine/Intermediate/slang")
    os.makedirs(slang_zip_directory, exist_ok=True)
    slang_zip_path = os.path.join(slang_zip_directory, slang_release_pkg_name)
    if not os.path.exists(slang_zip_path):
        download_package(slang_release_url, slang_zip_path)
    else:
        print(f"{Fore.GREEN}[slang] Already existed : {slang_zip_path}.")
        
    slang_extract_to = os.path.abspath("Engine/Binaries/slang")
    if extract_zip(slang_zip_path, slang_extract_to):
        print(f"{Fore.CYAN}[slang] Extracted to {slang_extract_to}...")    
        
    # DirectX Agility SDK
    #dx_agility_sdk_version = "1.615.0"
    #dx_agility_sdk_url = f"https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/{dx_agility_sdk_version}"
    dx_agility_preview_sdk_version = "1.716.0"
    dx_agility_preview_sdk_url = f"https://www.nuget.org/api/v2/package/Microsoft.Direct3D.D3D12/{dx_agility_preview_sdk_version}-preview"
    dx_agility_pkg_name = f"directx-agility-{dx_agility_preview_sdk_version}-preview.zip"
    dx_agility_zip_directory = os.path.abspath("Engine/Intermediate/directx-agility")
    os.makedirs(dx_agility_zip_directory, exist_ok=True)
    dx_agility_zip_path = os.path.join(dx_agility_zip_directory, dx_agility_pkg_name)
    print(f"\n{Fore.CYAN}[directx_agility_sdk] Parsed release package url : {dx_agility_preview_sdk_url}")
    if not os.path.exists(dx_agility_zip_path):
        download_package(dx_agility_preview_sdk_url, dx_agility_zip_path)
    else:
        print(f"{Fore.GREEN}[directx_agility_sdk] Already existed : {dx_agility_preview_sdk_url}.")
    
    dx_agility_extract_to = os.path.abspath("Engine/Binaries/directx-agility")
    if extract_zip(dx_agility_zip_path, dx_agility_extract_to):
        print(f"{Fore.CYAN}[directx_agility_sdk] Extracted to {dx_agility_extract_to}...")

def build_engine_project(platform_name):
    print(f"\n{Fore.CYAN}[Engine] Start building project...")
    premake_config_os_mapping = {}
    premake_config_os_mapping["Windows"] = "windows"
    
    premake_generator_mapping = {}
    premake_generator_mapping["Windows"] = "vs2022"

    premake_path = os.path.abspath(f"Tools/Premake/{platform_name}/premake5")
    makefile_path = os.path.abspath(f"Engine/Auto/Makefiles/premake5.lua")
    premake_cmd = [
        premake_path,
        f"--file={makefile_path}",
        f"--os={premake_config_os_mapping[platform_name]}",
        premake_generator_mapping[platform_name]
    ]
    run_command(premake_cmd, cwd=os.getcwd())

if __name__ == "__main__":
    colorama.init(autoreset=True)
    
    # Set environment variable
    os.environ["HG_BUILD_ROOT"] = os.getcwd()

    # Get platform info
    platform_name, cpu_arch, bit_arch = get_platform_info()
    print(f"{Fore.GREEN}Platform: {platform_name}")
    print(f"{Fore.GREEN}CPU Architecture: {cpu_arch}")
    print(f"{Fore.GREEN}Bit Architecture: {bit_arch}")

    # Check if CMake is installed before proceeding
    if not check_cmake_installed():
        exit(1)

    while True:
        # Display menu options
        print("\nChoose an option:")
        print("0. Full build (all steps)")
        print("1. Build third-party projects")
        print("2. Download third-party packages")
        print("3. Build engine project")

        choice = input(f"{Fore.YELLOW}Enter your choice (0-3): {Fore.RESET}")

        if choice == "0":
            build_third_party_projects()
            download_third_party_packages()
            build_engine_project(platform_name)
        elif choice == "1":
            build_third_party_projects()
        elif choice == "2":
            download_third_party_packages()
        elif choice == "3":
            build_engine_project(platform_name)
        else:
            print(f"{Fore.RED}Invalid choice! Please enter a number between 0 and 3.{Fore.RESET}")