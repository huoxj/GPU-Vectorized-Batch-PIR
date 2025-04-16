add_rules("mode.release", "mode.debug")

set_languages("c++20")

set_targetdir("build")

add_requires("zlib")
add_requires("vcpkg::seal")

-- 定义目标
target("vbpir")
    set_kind("binary")

    -- Pir scheme
    add_files("pir/src/**.cpp", "pir/src/**.cu")
    add_includedirs("pir/header")

    -- He utils
    add_files("he_utils/src/**.cpp", "he_utils/src/**.cu")
    add_includedirs("he_utils/header")

    -- Batch utils
    add_files("batch_utils/**.cpp")
    add_includedirs("batch_utils")

    add_cugencodes("native")
    set_toolchains("clang")
    
    -- Flags
    add_cxxflags("-g -O0")
    add_cuflags("--std=c++17", {force=true})
    
    -- SEAL
    add_packages("vcpkg::seal", "zlib")
    
    -- Troy
    local troy_dir = "/home/runz/temp/troy"
    add_includedirs(path.join(troy_dir, "include"))
    add_linkdirs(path.join(troy_dir, "lib"))
    add_links("/home/runz/temp/troy/lib/libtroy.so")
    add_ldflags("-Wl,-rpath,/home/runz/temp/troy/lib")
