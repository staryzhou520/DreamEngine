## OpenGL 笔记

### OpenGL定义
OpenGL是一个图形规范，不同的显卡厂商去具体实现其中的接口。所以OpenGL并不需要安装，类似与C++这种规范，提供一些接口

### 着色器定义
着色器是一段运行在GPU上的代码，像C++运行在CPU上一样，他帮助你更好的使用GPU。

### 踩坑指南
#### Shader编译报错
Failed to compile shander code:ERROR: 0:2: '�' : unexpected token
ERROR: 0:2: '' : compilation terminated
ERROR: 2 compilation errors.  No code generated.

解决办法：将UTF-8去除BOM