#include "CLIViewer.h"

CLIViewer::CLIViewer () : cout(stdout, QIODevice::WriteOnly), cin (stdin, QIODevice::ReadOnly)
{
}

void CLIViewer::launchUserInterface ()
{
	cout << "SuperDeutschLerner3000 started. For a command list type \"help\"" << endl;

	do cout << endl << "SDL3k> " << flush; while (listenKeyBoardInput ());

	cout << "bye" << endl;
}

void CLIViewer::displayLessonList (QDir folder, QFileInfoList& lessonList)
{
	cout << "displaying lessons in: " << folder.path() << endl << endl;
	for (auto fileInfo : lessonList)
	{
		cout << fileInfo.fileName() << endl;
	}
}

void CLIViewer::showCommandList ()
{
	QList<QPair<QString, QString>> cmdHelps;
	cmdHelps.push_back ({ "pwd", "show the current working directory" });
	cmdHelps.push_back ({ "cd [dir]", "change current working directory to [dir]" });
	cmdHelps.push_back ({ "help (h)", "display command list" });
	cmdHelps.push_back ({ "lessons (ls)", "show the current working directory" });
	cmdHelps.push_back ({ "train (t) [file.les]", "start a training session on the [file.les]" });
	cmdHelps.push_back ({ "exit", "exit SDL3k" });
	
	for (auto pair : cmdHelps)
	{
		cout.setFieldWidth (25);
		cout << left << pair.first;
		cout.setFieldWidth (0);
		cout << pair.second;
		cout << endl;
	}
}

void CLIViewer::showWorkingDirectory (QDir dir)
{
	cout << dir.path() << endl;
}

void CLIViewer::showUnknownCommand (QString command)
{
	cout << "Unknown command: \'" << command << '\'' << endl;
}

void CLIViewer::showPathMissing ()
{
	cout << "Please provide a path" << endl;
}

void CLIViewer::showFileMissing ()
{
	cout << "Please provide a lesson file name" << endl;
}

void CLIViewer::showFileError (QFileInfo fileInfo)
{
	cout << "Error" << " : could not open file \'" << fileInfo.fileName() << '\''<< endl;
}

void CLIViewer::showTrainingStarted (QFileInfo fileInfo)
{
	cout << "TRAINING STARTED" << endl;
	cout << "To stop training, type \"STOP\"" << endl;
	cout << "lesson selected : " << fileInfo.fileName() << endl;
	cout << "GOOD LUCK" << endl << endl;
}

void CLIViewer::showTrainingEnded (int correctAnswers, int totalAnswers)
{
	cout << "TRAINING SESSION OVER" << endl;
	cout << "Correct answers: ";
	cout.setFieldWidth (4);
	cout << correctAnswers << endl;
	cout << "Errors: ";
	cout.setFieldWidth (9+4); 
	cout << (totalAnswers - correctAnswers) << endl;
}

void CLIViewer::giveAnswer (QString originalWord, QString translatedWord, bool success)
{
	if (success)
		cout << originalWord << " : " << translatedWord << " CORRECT" << endl;
	else
		cout << originalWord << " : " << translatedWord << " INCORRECT" << endl;
	cout << endl;
}

void CLIViewer::askWord (QString word)
{
	cout << "What's the meaning of : \"" << word << '\"' << endl;
}

bool CLIViewer::listenKeyBoardInput ()
{
	QString userInput;
	userInput = cin.readLine ();
	cout << endl;
	return eventDispatcher->handleUserInput (userInput);
}
