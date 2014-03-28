﻿#ifndef TNOTESCATEGORYLIST_H
#define TNOTESCATEGORYLIST_H

#include "MyQItemDelegate.h"
#include <QtGui> 
#include <QListView>
#include <string>
#include <vector>
#include "Operation.h"

class tNotesCategoryList :public QListView
{  
    Q_OBJECT
public:  
    bool updateListView(string id);
    QString addCategory(QString name);
    tNotesCategoryList();
	void mouseDoubleClickEvent(QMouseEvent *event);   //鼠标点击响应
	vector<Article>dirVector;
private:
	//QStandardItemModel是一个多用途的model,可用于表示list,table,tree views所需要的各种不同的数据结构。
	QStandardItemModel *model;
    QIcon qic;
    MyQItemDelegate *myqit;
    string currentNotebookId;
    void setupActions();


signals:
    void initNotesEditor(string dirId, string articleId);

private slots:
    void initNotesCategory(string dirId);
    void noteSelected(const QModelIndex &index);
};

#endif