# Windows_Programming
## A. Execute c/cpp program via command line(without resources of windows)
**If you want to build executable 32 bit then use following steps:**
1. Open Developer command prompt or open x86 Native Tools command prompt
2. Go to your source code file directory
3. Now just compile your program use command:
  ```
  cl /c /EHsc NameSourceFile.cpp
  ```
4. After successfull compilation .obj file will generate. link that file to libraries using
  ```
  link NameOfObjectFile.obj user32.lib kernel32.lib gdi32.lib /subsystem:windows
  ```
5. After that just execute .exe
  ```
  NameOfExe.exe
  ```
  
## B. Execute c/cpp program via command line(with resources of windows)
1. Open Developer command prompt or open x86 Native Tools command prompt
2. Go to your source code file directory
3. Now just compile your program use command:
  ```
  cl /c /EHsc NameSourceFile.cpp
  ```
  After successfull compilation .obj file will generate
  
4. Now to compile resource file use command
  ```
  rc Reources.rc
  ```
  After successfull compilation .res file will generate
  
5. Now link both Reources.res and NameOfObject.obj
  ```
  link NameOfObjectFile.obj Resources.res user32.lib kernel32.lib gdi32.lib /subsystem:windows
  ```
5. After that just execute .exe
  ```
  NameOfExe.exe
  ```
 **Note : for x64 executable exe use x64 Native Tools command prompt**
## C. How to build DLL using command line
1. compile
  ```
  cl /c /EHsc [name of source file]
  ```
2. link
  ```
  link [name of obj file] /DLL user32.lib kernel32.lib gdi32.lib /subsystem:windows
  ```
## D. How to build DLL with Module defination file using command line
1. compile
  ```
  cl /c /EHsc [name of source file]
  ```
2. link
  ```
  link [name of obj file] /DLL /DEF:[Name of .def file] user32.lib kernel32.lib gdi32.lib /subsystem:windows
  ```
 
## D. How to execute COM - ClassFactory and Containement code
1. compile
  ```
  cl /c /EHsc [name of source file]
  ```
2. link
  ```
  link [name of obj file] user32.lib kernel32.lib gdi32.lib ole32.lib oleaut32.lib /subsystem:windows
  ```
 
