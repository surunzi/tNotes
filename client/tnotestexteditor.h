#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QMap>
#include <QPointer>
#include <QString>

class QTextEdit;
class QGroupBox;
class QLabel;
class QToolButton;
class QToolBar;
class QAction;
class QFrame;

class tNotesButton;

#define EDIT_MODE 0
#define VIEW_MODE 1

class tNotesTextEditor : public QWidget
{
	Q_OBJECT

public:
		tNotesTextEditor(QWidget *parent = 0);

private:

		QLabel *noteTitle;
		QToolBar *noteToolBar;
		QLabel *noteCreatedTime;
		QLabel *noteLastModifiedTime;
		QGroupBox *noteEditorGroupBox;
		QTextEdit *noteEditor;
		QAction *actionUndo;
		QFrame *horizonLine;

        QString plainText;
        QString htmlText;
		tNotesButton *buttonEdit;

		tNotesButton *buttonBold;
		tNotesButton *buttonItalic;
		tNotesButton *buttonQuotes;
		tNotesButton *buttonUndo;
		tNotesButton *buttonRedo;
		tNotesButton *buttonCode;
		tNotesButton *buttonLink;

		bool editMode;

private:

		QString getTitle();
		QString getCreatedTime();
		QString getLastModifiedTime();
        QString markdown2html(QString articleContents);

		void setTextEditorLayout();
		void setupEditActions();

private slots:

		void editModeChange();
		void setBold();


};

#endif
