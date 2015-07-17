# Class openGL Homeworks

## 中興大學資工系 103 下學期 成圖技術與應用 作業結果

### Compilation

To compile a project, there are some dependencies to resolve:  

 * `cd` into a project
 * Get the dependencies,
    * if you are using Microsoft Visual Studio, 
        * Go to [Transmission Zero](http://www.transmissionzero.co.uk/software/freeglut-devel/) to download the latest `freeglut for MSVC`
            * extract `freeglut\bin\freeglut.dll` to the `Debug` and `Release` (if has) directory of this repo
            * extract `freeglut\lib\freeglut.lib` to the `lib` directory of this repo
            * extract all contents of `freeglut\include\GL` to the `{project_name}\GL\` folder of this repo
        * Go to [glew](http://glew.sourceforge.net/) to download `Windows 32-bit and 64-bit` Binaries
            * extract `glew-*\lib\Release\Win32\glew32.lib` to the `lib` directory of this repo
            * extract `glew-*\include\GL\glew.h` to `{project_name}\GL\` folder of this repo
    * if you are using OSX, open a terminal and use [brew](http://brew.sh/) to install `glew`:
        * (if you don't have `brew` installed) follow the instructions on [brew](http://brew.sh/) to install it.
        * do this command on terminal: `brew tap homebrew/versions`
        * do this command on terminal: `brew install glfw3 glew`
        * The dependency is for the whole system, so you only have to do it for the first time
 * And compile of course,
    * With Microsoft Visual Studio, open the `{project_name}.sln` directly and build it with `Debug` (in HW5, use `Release`) configuration, this will generate `Debug\{project_name}.exe` (or `Release\{project_name}.exe` in HW5)
    * With OSX terminal,
        * `cd <this_repo>`
        * `make`
        * then the executable `OSX_build/{project_name}` should be generated.

> Not tested, but it should work ^_<

### Execution

 * With Microsoft Visual Studio, just run it with the IDE
   * You can also execute the `.exe` after compilation
 * With OSX terminal, use `./OSX_build/{project_name}` to run it
