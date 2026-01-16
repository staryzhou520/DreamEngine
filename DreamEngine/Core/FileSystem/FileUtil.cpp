#include "FileUtil.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#ifdef _WIN32
    #include <direct.h>
    #define FileUtil_GETCWD _getcwd
#else
    #include <unistd.h>
    #define FileUtil_GETCWD getcwd
#endif


std::string FileUtil::LoadFileToString(const char* FilePath)
{
    std::string AbsolutePath = ConvertToAbsolutePath(FilePath);
    // const char* AbsolutePath = "D:/DreamEngine/DreamEngine/Rendering/OpenGL/ShaderCode/shader_1.vs";
    std::string OutPut;
    std::ifstream File;
    File.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        File.open(AbsolutePath);
        std::stringstream FileStream;
        FileStream << File.rdbuf();
        File.close();
        OutPut = FileStream.str();
        
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error FIleUtil::GetFileToString Failed" << std::endl;
    }

    return OutPut;
    
}

std::string FileUtil::ConvertToAbsolutePath(const char* RelativePath)
{
    char buff[FILENAME_MAX];
    FileUtil_GETCWD( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    
    // 添加路径分隔符
    if (!current_working_dir.empty() && 
        current_working_dir.back() != '/' && 
        current_working_dir.back() != '\\')
    {
        current_working_dir.append("/");
    }
    
    current_working_dir.append(RelativePath);
    
    std::cout<<"FileUtil::ConvertToAbsolutePath from: "<<RelativePath<<"   to: "<<current_working_dir<<std::endl;

    return current_working_dir;
}
