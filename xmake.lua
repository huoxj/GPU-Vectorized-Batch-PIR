add_rules("mode.release", "mode.debug")

set_languages("c++17")

set_toolchains("clang", "nvcc")

set_targetdir("build/bin")

-- 定义目标
target("vectorized_batch_pir")
    set_kind("binary")
    add_files("src/*.cpp", "src/*.cu")
    add_includedirs("header")
    add_defines("CMAKE_CUDA_ARCHITECTURES=89")
    
    -- 指定编译器
    set_toolchains("clang", "nvcc")
    
    -- 设定编译选项
    add_cxxflags("-g")
    add_cuflags("--std=c++17")
    
    -- SEAL 库
    add_packages("seal")
    
    -- Troy 库
    local troy_dir = "/home/runz/temp/troy"
    add_includedirs(path.join(troy_dir, "include"))
    add_linkdirs(path.join(troy_dir, "lib"))
    add_links("troy")
    
    -- 链接 SEAL
    add_links("seal")
