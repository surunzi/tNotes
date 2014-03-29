﻿#include "Operation.h"
#include <fstream>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

extern string ROOTPATH = "";
string articlePath="";

extern string rootPath = "";
extern string recordPath="";
void print(QString s)
{
    QMessageBox::information(NULL, "OK", s);
}


QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}

string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
}
QString readFile(QString filePath)
{
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QString styleSheet = file.readAll();
    return styleSheet;
}
/************************************************************************/
/*设置用户数据文件夹，传入文件夹路径                                                                  */
/************************************************************************/
void setupRootPath(string path)
{
    ROOTPATH = path + "\\";
    rootPath = path + "\\root.json";
    recordPath = path + "\\record.json";
}
/************************************************************************/
/* 返回文章路径，路径构成为文章ID+.json                                                                    */
/************************************************************************/
void getArticlePath(string articleId)
{
    articlePath = ROOTPATH + articleId + ".json";
}
/************************************************************************/
/* 打开json文件，返回json根                                                                     */
/************************************************************************/
Json::Value returnRoot(string path)
{
    Json::Reader reader;
    Json::Value root;
    ifstream ifs;

    ifs.open(path.c_str());
    reader.parse(ifs,root,false);
    if(ifs.is_open())
    {
    ifs.close();       
    } else {
        std::cout<<"hello"<<std::endl;
    }
   return root;
}

/************************************************************************/
/* 将json树写入json文件，若文件不存在，则创建一个新文件，工作目录下命名为"tnote.json"                                                                     */
/************************************************************************/
bool writeInJson(Json::Value root,string path)
{
    Json::FastWriter writer;
    ofstream ofs;

    ofs.open(path.c_str());
    if(ofs.is_open())
    {
        string json_file = writer.write(root);
        ofs<<json_file;
        ofs.close();
        return 1;
    }
    return 0;
}

/************************************************************************/
/* 创建新目录，传入目录类，以目录id作为索引，离线编辑时以客户端时间戳作为id，
   若在线编辑，向服务器申请id，时间戳
   操作成功返回1，否则返回0*/
/************************************************************************/
bool createRoot(Directory dir)
{
    Json::Value root=returnRoot(rootPath);

    Json::Value recordRoot = returnRoot(recordPath);
    Json::Value d;
    Json::Value r;
    d["name"] = dir.name;
    d["createTime"] = dir.createTime;
    d["modifiedTime"]=dir.modifiedTime;
    d["isSyn"]=dir.isSyn;
    root[dir.nodeId]=d;

    r["mark"]="000";
    r["id"]=dir.nodeId;
    r["name"]=dir.name;
    recordRoot.append(r);
    if(writeInJson(root,rootPath)&&writeInJson(recordRoot,recordPath))
    {
        return 1;
    }
    else return 0;
}

/************************************************************************/
/* 新建文章，传入目录ID和文章类
新建文章只需将前台该文章信息封装成一个类作为参数即可
操作成功返回1，否则返回0*/

/************************************************************************/
bool createArticle(string iRoot,Article art)
{
    Json::Value recordRoot=returnRoot(recordPath);
    Json::Value root=returnRoot(rootPath);
    if(!root[iRoot].isNull())
    {
        Json::Value a;
        Json::Value b;
        Json::Value r;
        r["mark"]="100";
        r["name"]=art.name;
        r["content"]=art.context;
        r["id"]=art.articleId;
        r["location"]=iRoot;
        recordRoot.append(r);
        b["context"] = art.context;
        a["name"] = art.name;
        a["createTime"] = art.createTime;
        a["modifiedTime"]=art.modifiedTime;
        a["isSyn"]=art.isSyn;

        root[iRoot]["array"][art.articleId]=a;
        getArticlePath(art.articleId);
        if(writeInJson(root,rootPath)&&writeInJson(b,articlePath)&&writeInJson(recordRoot,recordPath))
        {
            return 1;    
        }
        else return 0;
    }   
    else return 0;
}

/************************************************************************
* 删除目录，传入目录ID，删除该目录及目录下所有文章，操作成功返回1，否则返回0   *                                                                  */
/************************************************************************/
bool deleteRoot(string index)
{
    Json::Value root=returnRoot(rootPath);

    Json::Value r;
    r["mark"]="001";
    r["id"]=index;


    Json::Value recordRoot = returnRoot(recordPath);
    recordRoot.append(r);
    vector<string>articleLsit=root[index]["array"].getMemberNames();
    for(int i=0;i<(int)articleLsit.size();i++)
    {
        getArticlePath(articleLsit[i]);
        remove(articlePath.c_str());
    }
    root.removeMember(index);
    if(writeInJson(root,rootPath)&&writeInJson(recordRoot,recordPath))return 1;
    else return 0;
}

/************************************************************************/
/* 删除指定目录下特点文章，传入目录ID，文章ID   
   操作成功返回1，否则返回0*/
/************************************************************************/
bool deleteArticle(string iRoot,string iArticle)
{
    Json::Value root=returnRoot(rootPath);
    Json::Value recordRoot=returnRoot(recordPath);
    Json::Value r;
    r["mark"]="101";
    r["id"]=iArticle;
    recordRoot.append(r);

    root[iRoot]["array"].removeMember(iArticle);
    getArticlePath(iArticle);
    remove(articlePath.c_str());

    if(writeInJson(root,rootPath)&&writeInJson(recordRoot,recordPath))return 1;
    else return 0;
}

/************************************************************************
* 查找所有目录信息，返回目录列表，若不存在目录，则返回一个空列表 *                                                                  */
/************************************************************************/
vector<Directory> searchAllRoot()
{

    Json::Value root = returnRoot(rootPath);
    std::cout<<rootPath<<std::endl;
    std::cout<<root.toStyledString()<<std::endl;
    vector<string> listRoot=root.getMemberNames();
    vector<Directory> allRoot;
    Directory obj;
    string nodeId;
    std::cout << listRoot.size() << std::endl;
    for(int i=0;i<(int)listRoot.size();i++)
    {
        nodeId=listRoot[i];
        obj.nodeId=nodeId;
        obj.createTime=root[nodeId]["createTime"].asString();
        obj.name=root[nodeId]["name"].asString();

       // std::cout << obj.name << std::endl;
        obj.modifiedTime=root[nodeId]["modifiedTime"].asString();
        obj.isSyn=root[nodeId]["isSyn"].asBool();
        allRoot.push_back(obj);
    }

    return allRoot;
}

/************************************************************************
* 查找特定目录下所有文章，传入目录ID，返回文章列表，若该目录下无文章，返回一个空列表                                                                     */
/************************************************************************/
vector<Article> searchRootArticle(string iRoot)
{
    Json::Value root=returnRoot(rootPath);
    Json::Value allArticle=root[iRoot]["array"];
    vector<string> listRootArticle=allArticle.getMemberNames();
    vector<Article> allRootArticle;
    Article obj;
    string articleId;
    for(int i=0;i<(int)listRootArticle.size();i++)
    {
        articleId=listRootArticle[i];
        getArticlePath(articleId);
        Json::Value article=returnRoot(articlePath);
        obj.articleId=articleId;
        obj.createTime=allArticle[articleId]["createTime"].asString();
        obj.name=allArticle[articleId]["name"].asString();
        obj.modifiedTime=allArticle[articleId]["modifiedTime"].asString();
        obj.isSyn=allArticle[articleId]["isSyn"].asBool();
        obj.context=article["context"].asString();
        allRootArticle.push_back(obj);
    }

    return allRootArticle;
}

/************************************************************************
 *查找所有文章，前台搜索调用，返回所有文章列表，若无文章，返回空队列                                                                  */
/************************************************************************/
vector<Article> searchAllArticle()
{
    Json::Value root=returnRoot(rootPath);
    vector<string>listRoot=root.getMemberNames();
    vector<Article>allArticle;
    vector<Article>rootArticle;
    vector<Article>::iterator it;
    for(int i=0;i<(int)listRoot.size();i++)
    {
        it=allArticle.end();
        rootArticle=searchRootArticle(listRoot[i]);
        allArticle.insert(it,rootArticle.begin(),rootArticle.end());

    }
 
    return allArticle;
}

/************************************************************************
* 查找特定目录下特定文章，传入目录ID和文章ID，返回文章类，若无该文章，返回空对象 *                                                                    */
/************************************************************************/
Article searchArticle(string iRoot,string iArticle)
{
    Json::Value root=returnRoot(rootPath);
    Json::Value art=root[iRoot]["array"][iArticle];
    Article article;
    if(!art.isNull())
    {
        getArticlePath(iArticle);
        Json::Value articleContext=returnRoot(articlePath);
        article.articleId=iArticle;
        article.context=articleContext["context"].asString();

        article.name=art["name"].asString();
        article.createTime=art["createTime"].asString();
        article.modifiedTime=art["modifiedTime"].asString();
        article.isSyn=art["isSyn"].asBool();
      
    }
    return article;
}

/**********************************************************************
 * 修改目录名
   传入目录ID和新目录名
   若查找到原目录，则返回1，否则返回0*
*************************************************************************/
bool changeRoot(string iRoot ,string name)
{
    Json::Value root=returnRoot(rootPath);

    if(!root[iRoot].isNull())
    {


            root[iRoot]["name"]=name;

            Json::Value recordRoot=returnRoot(recordPath);
            Json::Value r;
            r["mark"]="010";
            r["id"]=iRoot;
            r["name"]=name;
            recordRoot.append(r);
            writeInJson(recordRoot,recordPath);



            writeInJson(root,rootPath);
            return 1;
    }
    else return 0;
   
}
//与服务器同步修改目录id和时间戳
bool changeRootId(string oldId,string newId,string modifiedTime)
{
    Json::Value root=returnRoot(rootPath);
    Json::Value obj=root[oldId];
    if(!obj.isNull())
    {


            obj["modifiedTime"]=modifiedTime;
            root.removeMember(oldId);
            root[newId]=obj;
            writeInJson(root,rootPath);
            return 1;
    }
    else return 0;
}

/************************************************************************/
/* 修改文章标题。
   传入文章所属目录ID和文章id和文章标题
   若查找到原文章，则返回1，否则返回0*/
/*************************************************************************/
bool changeArticleName(string iRoot,string iArticle,string name)
{
    Json::Value root=returnRoot(rootPath);

    if(!root[iRoot]["array"][iArticle].isNull())
    {

        root[iRoot]["array"][iArticle]["name"]=name;
         Json::Value recordRoot=returnRoot(recordPath);
         Json::Value r;
         r["mark"]="110";
         r["id"]=iArticle;
         r["name"]=name;

         recordRoot.append(r);
         writeInJson(recordRoot,recordPath);
         writeInJson(root,rootPath);


        return 1;
    }
    else return 0;

}
/************************************************************************/
/* 修改文章内容。
   传入文章所属目录ID和文章id和内容
   若查找到原文章，则返回1，否则返回0*/
/*************************************************************************/
bool changeArticleContent(string iRoot,string iArticle,string content)
{
    Json::Value root=returnRoot(rootPath);

    if(!root[iRoot]["array"][iArticle].isNull())
    {

        getArticlePath(iArticle);
        Json::Value article=returnRoot(articlePath);
        article["context"]=content;
         Json::Value recordRoot=returnRoot(recordPath);
         Json::Value r;
         r["mark"]="110";
         r["id"]=iArticle;
         r["content"]=content;

         recordRoot.append(r);
         writeInJson(recordRoot,recordPath);
         writeInJson(article,articlePath);



        return 1;
    }
    else return 0;

}
//与服务器同步，修改文章id和时间戳
bool changeArticleId(string rootid,string oldId,string newId,string modifiedTime)
{
    Json::Value root=returnRoot(rootPath);
    Json::Value obj=root[rootid]["array"][oldId];
    if(!obj.isNull())
    {


            obj["modifiedTime"]=modifiedTime;
            root[rootid]["array"].removeMember(oldId);
            root[rootid]["array"][newId]=obj;
            getArticlePath(oldId);
            string  oldpath=articlePath;
            getArticlePath(newId);
            rename(oldpath.c_str(),articlePath.c_str());

            writeInJson(root,rootPath);
            return 1;
    }
    else return 0;
}
