﻿tNotes客户端
=====

成员
-----
* 胡宽敏
* 林标标
* 林炎厚
* 郑小维

说明
-----

1. markdown2html.dll

  基于cpp-markdown编写的动态库，作用为将markdown语法翻译为html，效率可能有些低。测试时请将dll置于system32（32bit）或者syswow64（64bit）文件夹下。


2. Qt下json配置
   只需要将json文件下所有文件导入项目工程即可。
   调用客户端后台函数只需包含#include "Operation.h"即可，详细函数说明请看"Operation.h"中函数说明。


3 测试数据使用
  将测试数据文件夹下的文件拷到工程目录下即可使用，注意不要建文件夹，因为我用的是相对路径

4. 索引使用例子

    search *b=new search("D:/friso.ini");
    b->connect("demo.db");
    b->init();
    b->insert((char*)"1",(char*)"hello",(char*)"今天的天气很差，没下雨，阳光明媚。");
    b->insert((char*)"2",(char*)"hello",(char*)"今天的天气很好，没下雨，阳光明媚。");
    b->insert((char*)"3",(char*)"hello",(char*)"昨天的天气很好，没下雨，阳光明媚。");
    b->select((char*)"昨天");

5. 读取root.json说明


> 点击登录，输入用户名（注意修改mainwindow类里的ROOT_PATH变量至测试数据存储位置）
> 将测试数据手动调整为ANSI编码（用editplus打开 -> 另存为 -> 选择编码）


=======
图片
-----

1. 主界面设计图
![主界面设计图](medias/doc/tNotes_design.png)

2. 登陆界面设计图
![登陆界面设计图](medias/doc/LoginRegister.png)




