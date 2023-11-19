add_rules("mode.debug", "mode.release")

set_languages("c++17")

set_rundir("$(projectdir)")

target("7zip")
    set_kind("$(kind)")

    add_defines("ZSTD_DISABLE_ASM")
    add_defines("USE_MIXER_MT")
    add_includedirs("C/brotli", "C/lz5", "C/lz4", "C/lizard")
    add_files("C/brotli/*.c")
    add_files("C/lz4/*.c")
    add_files("C/lz5/*.c")
    add_files("C/lizard/*.c")
    add_files("C/fast-lzma2/*.c")
    add_files("C/zstdmt/*.c")
    add_files("C/zstd/*.c")
    add_files("C/hashes/*.c")

    add_files("C/*.c")
    add_files("CPP/7zip/Common/*.cpp")
    add_files("CPP/7zip/Archive/*.cpp|DllExports.cpp")
    for _, n in ipairs({
        "Common",
        "7z",
        "Cab",
        "Chm",
        "Iso",
        "Nsis",
        "Rar",
        "Tar",
        "Udf",
        "Wim",
        "Zip",
    }) do
        add_files("CPP/7zip/Archive/"..n.."/*.cpp")
    end
    add_files("CPP/7zip/Compress/*.cpp|DllExports2Compress.cpp|DllExportsCompress.cpp")
    add_files("CPP/7zip/Crypto/*.cpp")
    add_files(
        "CPP/Windows/FileDir.cpp",
        "CPP/Windows/FileFind.cpp",
        "CPP/Windows/FileIO.cpp",
        "CPP/Windows/FileName.cpp",
        "CPP/Windows/PropVariant.cpp",
        "CPP/Windows/PropVariantConv.cpp",
        "CPP/Windows/System.cpp",
        "CPP/Windows/TimeUtils.cpp",
        "CPP/Windows/PropVariantUtils.cpp",
        "CPP/Windows/PropVariant.cpp",
        "CPP/Windows/Synchronization.cpp",
        "CPP/Common/MyWindows.cpp",
        "CPP/Common/StringConvert.cpp",
        "CPP/Common/Wildcard.cpp",
        "CPP/Common/MyXml.cpp",
        "CPP/Common/MyString.cpp",
        "CPP/Common/UTFConvert.cpp",
        "CPP/Common/IntToString.cpp",
        "CPP/Common/StringToInt.cpp",
        "CPP/Common/MyMap.cpp",
        "CPP/Common/CRC.cpp",
        "CPP/Common/*Reg.cpp"
    )
    -- add_defines("USE_DLL_EXPORT")

target("demo")
    add_includedirs("C")
    add_files("main.cpp")
    set_pcxxheader("CPP/7zip/Bundles/Format7zF/StdAfx.h")
    add_files("CPP/7zip/Bundles/Format7zF/StdAfx.cpp")
    add_deps("7zip")
    if is_plat("windows", "mingw") then
        add_syslinks("OleAut32", "User32", "Advapi32")
    end
