// #include <stdio.h>
// #include <stdarg.h>
// #include "Hal.hpp"

// #ifdef __cplusplus
// extern "C" {
// #endif

// static constexpr size_t bufferSize = 1024;
// bool isErrorOccured = false;

// static char buffer[bufferSize];

// FILE * fopen(const char *filename, const char *mode)
// {
//    //TODO 
// }

// int printf(const char *format, ...)
// {
//     va_list args;
//     va_start(args, format);
    
//     auto result = vsnprintf(buffer, bufferSize, format, args);
//     va_end(args);

//     if(result > bufferSize || result < 0)
//         return -1;
    
//     Chal::GetHal()->Transmit((unsigned char *)buffer, result + 1);
//     return result;
// }

// int scanf(const char * format, ...)
// {
//     va_list args;
//     va_start(args, format);

//     auto readedChars = Chal::ReadReceivedData((unsigned char *)buffer, bufferSize - 1);
    
//     //feof
//     buffer[readedChars] = '\0';

//     auto result = vsscanf(buffer, format, args);

//     va_end(args);
//     return result;
// }

// char * fgets(char * string, int size, FILE *)
// {

// }

// int ferror(FILE *)
// {
//     return (isErrorOccured ? 1 : 0);
// }

// void clearerr (FILE *)
// {
//     isErrorOccured = false;
// }

// #ifdef __cplusplus
// }
// #endif