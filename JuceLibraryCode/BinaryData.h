/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   favicon16_ico;
    const int            favicon16_icoSize = 1150;

    extern const char*   favicon16_png;
    const int            favicon16_pngSize = 822;

    extern const char*   favicon32_ico;
    const int            favicon32_icoSize = 4286;

    extern const char*   favicon32_png;
    const int            favicon32_pngSize = 1521;

    extern const char*   favicon48_ico;
    const int            favicon48_icoSize = 9662;

    extern const char*   favicon48_png;
    const int            favicon48_pngSize = 1964;

    extern const char*   favicon64_ico;
    const int            favicon64_icoSize = 16958;

    extern const char*   favicon64_png;
    const int            favicon64_pngSize = 3083;

    extern const char*   MyAppResources_aps;
    const int            MyAppResources_apsSize = 17880;

    extern const char*   MyAppResources_rc;
    const int            MyAppResources_rcSize = 125;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
