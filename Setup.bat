@echo off
setlocal

:: Check if python is available
where python >nul 2>nul
if %errorlevel% neq 0 (
    echo [ERROR] Python is not installed or not in PATH!
    goto failure
)

:: Check if pip is available
where pip >nul 2>nul
if %errorlevel% neq 0 (
    echo [WARNING] pip is not installed or not in PATH!
)

:: Check if Python is version 3.x
for /f "tokens=2 delims=. " %%v in ('python -V 2^>nul') do (
    if %%v LSS 3 (
        echo [ERROR] Python version is not 3.x!
        goto failure
    )
)

:: If all checks pass, run the script
echo Python 3 detected...
echo Install colorama module for colored console text...
pip install colorama
pip install requests
echo Run build script...
python Engine/Auto/build.py
goto done

:failure
echo Script terminated due to errors.
pause

:done
pause