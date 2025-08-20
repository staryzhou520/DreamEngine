#include "DrawObjectTwoTexture.h"

void DrawObjectTwoTexture::InitDrwBuffer()
{
    DrawObject::InitDrwBuffer();

    // 顶点数据
    float Vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
   };
    // 每个顶点数据由几个元素组成
    int ONE_VERTICE_DATA_NUM = 8;

    // 索引缓冲区
    unsigned int indices[] = {
        0,1,2,
        0,2,3,
    };

    // 生成一个顶点Array
    unsigned int VAO;
    glGenVertexArrays(1,&VAO);
    // 将这个Array绑定为顶点Array
    glBindVertexArray(VAO);

    // 创建顶点索引buffer
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    
    // 将Buffer绑定到 GL_ELEMENT_ARRAY_BUFFER （索引缓冲区上）
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 设置索引缓冲区的值
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 
    
    // 创建OpenGL Buffer  VertexBuffer
    unsigned int VertexBufferID;  //当前Buffer的ID
    glGenBuffers(1,&VertexBufferID);

    // 这里告诉OpenGL要绑定哪个Buffer,后面直接调用Draw就可以
    glBindBuffer(GL_ARRAY_BUFFER,VertexBufferID);

    // 穿数据到Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices),Vertices,GL_STATIC_DRAW);

    // // 纹理
    // glGenTextures(1,&texture1);
    // // 激活UV0，第一套UV
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D,texture1);
    //
    //
    // // 设置环绕和过滤方式
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    // std::string TexPath = "/Saved/Image/wall.jpg";
    // int Width, Height, NrChannels;
    // unsigned char* ImageData = ImageUtil::LoadImage(FileUtil::ConvertToAbsolutePath(TexPath.c_str()), Width, Height, NrChannels);
    //
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, ImageData);
    // glGenerateMipmap(GL_TEXTURE_2D);
    //
    // // 手动释放ImageData内存
    // ImageUtil::ReleaseImageData(ImageData);
    //
    // glGenTextures(1,&texture2);
    // glActiveTexture(GL_TEXTURE1);
    // glBindTexture(GL_TEXTURE_2D,texture2);
    //
    // // 设置环绕和过滤方式
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //
    // std::string Tex2Path = "/Saved/Image/awesomeface.png";
    // int Width2, Height2, NrChannels2;
    // unsigned char* ImageData2 = ImageUtil::LoadImage(FileUtil::ConvertToAbsolutePath(Tex2Path.c_str()), Width2, Height2, NrChannels2);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width2, Height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImageData2);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // ImageUtil::ReleaseImageData(ImageData2);
    //
    // // 定义顶点, 2代表顶点是二维的
    // glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(float) * ONE_VERTICE_DATA_NUM,0);
    // glEnableVertexAttribArray(0);
    //
    // // 定义顶点颜色
    // glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(float) * ONE_VERTICE_DATA_NUM,(void*) (3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    //
    // glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(float) * ONE_VERTICE_DATA_NUM,(void*)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);
    //
    // CurShader = new Shader("/Rendering/OpenGL/ShaderCode/shader_1.vs","/Rendering/OpenGL/ShaderCode/shader_1.fs");
    //
    // CurShader->Use(); // don't forget to activate the shader before setting uniforms!  
    // glUniform1i(glGetUniformLocation(CurShader->ProgramID, "texture1"), 0); // set it manually
    // CurShader->SetInt("texture2", 1);
}
