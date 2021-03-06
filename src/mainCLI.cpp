#include "view\CLI\CLIViewer.h"
#include "view\CLI\CLIEventDispatcher.h"
#include "controller\Controller.h"

int main(int argc, char** argv)
{
	Controller controller;
	if (argc > 1) controller.setFolderPath (QString(argv[1]));
	CLIViewer viewer;
	controller.setViewer (&viewer);
	CLIEventDispatcher dispatcher(&controller, &viewer);
	viewer.setEventDispatcher (&dispatcher);
	viewer.launchUserInterface ();
	return 0;
}