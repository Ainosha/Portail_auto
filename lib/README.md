# Project-Specific Libraries

This directory contains various libraries specific to the project. Each library is placed in its own folder under `lib/` and includes source files (e.g., `.cpp`, `.h`), along with any other relevant files for that library.

## Library Structure Overview
lib/  
├── adc_deep_sleep  
│   ├── adc_deep_sleep.cpp  
│   └── adc_deep_sleep.h  
│  
├── Api  
│   ├── api.cpp  
│   └── api.h  
│  
├── buzzer_song  
│   ├── buzzer_song.cpp  
│   └── buzzer_song.h  
│  
├── Network  
│   ├── Network.cpp  
│   ├── Network.h  
│   └── README.md  
│  
├── Portail  
│   ├── exemple.ino  
│   ├── portail_digi.cpp  
│   └── portail_digi.h  
│  
├── RFID  
│   ├── exemple.ino  
│   ├── RFID.cpp  
│   └── RFID.h  
│  
├── wakeup_process  
│   ├── wakeup_process.cpp  
│   └── wakeup_process.h  
│  
└── README.md  --> THIS FILE  

## Adding a New Library

To add a new library, create a new folder inside `lib/` and place your source code files (e.g., `.cpp`, `.h`) there. The folder structure should look similar to the examples provided above.

## Example Usage

Libraries can be included and used in your main project by including their respective header files. For example, to use the `Api` and `Network` libraries and etc. Check wakeup_process.cpp for the use

PlatformIO's Library Dependency Finder will automatically detect and link these libraries.

## Additional Resources

For more information about working with libraries in PlatformIO, refer to the official [PlatformIO Library Dependency Finder documentation](https://docs.platformio.org/page/librarymanager/ldf.html).

Let me know if you'd like further details!
