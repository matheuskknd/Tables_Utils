#!/usr/bin/env python3.8
# coding: utf-8

from PyQt5.QtWidgets import QApplication
from MainWindow import MainWindow
from PyQt5.QtGui import QIcon

from sys import argv, exit
from os import path

if __name__ == "__main__":

	app:QApplication = QApplication(argv)
	mainWin:MainWindow = MainWindow(app,QIcon(path.dirname(path.realpath(__file__)) + '/icons/program.png'))
	exit( app.exec_() )
