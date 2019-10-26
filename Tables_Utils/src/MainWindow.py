#!/usr/bin/env python3.8
# coding: utf-8

from PyQt5.QtWidgets import QMainWindow, QApplication, QPushButton, QWidget, QVBoxLayout, QHBoxLayout
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt

class TipFormat():

	def __init__( self, text:str):
		self.string = "<html><table style=\" white-space: nowrap;\"><tr><td><center>" + text + "</center></td></tr></table></html>"

	def __str__(self):
		return self.string

	def __repr__(self):
		return self.string


class Head(QHBoxLayout):

	def __init__( self, call_back:callable):

		# Innitialization
		super(QHBoxLayout,self).__init__()

		# Internal layout
		self.setContentsMargins(0,0,0,0)
		self.setSpacing(0)

		menu_hbox:QHBoxLayout = QHBoxLayout()	# The Left Header Hbox
		menu_hbox.setContentsMargins(4,4,4,4)
		menu_hbox.setSpacing(4)

		self.addLayout(menu_hbox,50)			# Half of it, is the menu Hbox
		self.addStretch(50)						# The rest is a blank by now

		# Menu buttons
		button1 = QPushButton('B1')
		button1.setToolTip(TipFormat("<h4>Click here on B1</h4>").__str__())
		button1.clicked.connect(call_back)
		#button1.setMinimumSize(20,30)
		menu_hbox.addWidget(button1,1)

		button2 = QPushButton('B2')
		button2.setToolTip(TipFormat("<h4>Click here on B2</h4>").__str__())
		button2.clicked.connect(call_back)
		#button2.setMinimumSize(20,30)
		menu_hbox.addWidget(button2,1)

		button3 = QPushButton('B3')
		button3.setToolTip(TipFormat("<h4>Click here on B3</h4>").__str__())
		button3.clicked.connect(call_back)
		#button3.setMinimumSize(20,30)
		menu_hbox.addWidget(button3,1)

		menu_hbox.addStretch(3)					# Add the space occupied by 3 buttons

		button4 = QPushButton('UNDO')
		button4.setToolTip(TipFormat("Clique para desfazer").__str__())
		button4.clicked.connect(call_back)
		#button4.setMinimumSize(20,30)
		menu_hbox.addWidget(button4,1)

		button5 = QPushButton('REDO')
		button5.setToolTip(TipFormat("Clique para refazer").__str__())
		button5.clicked.connect(call_back)
		#button5.setMinimumSize(20,30)
		menu_hbox.addWidget(button5,1)


class Body(QHBoxLayout):

	def __init__( self, call_back:callable):

		# Innitialization
		super(QHBoxLayout,self).__init__()

		# Internal layout
		self.setContentsMargins(0,0,0,0)
		self.setSpacing(0)

		# Create all inner widgets
		box1:QWidget = QWidget()
		box2:QWidget = QWidget()
		box3:QWidget = QWidget()

		#############
		# Debbug
		box1.setStyleSheet("background-color:red;")
		box2.setStyleSheet("background-color:blue;")
		box3.setStyleSheet("background-color:green;")
		# Debbug
		#############

		# Bind all to the body
		self.addWidget(box1,45)
		self.addWidget(box2,10)
		self.addWidget(box3,45)


class MainWindow(QMainWindow):

	# Creates the main window, call internal layout creation and then show up
	def __init__( self, app:QApplication, icon:QIcon):

		# Innitialization
		super(QMainWindow,self).__init__()

		# Instance variables
		self.layout = QWidget()
		self.app = app

		# Position and size
		height:float = app.primaryScreen().size().height()
		width:float = app.primaryScreen().size().width()

		self.setGeometry(width/8,height/8,width*6.0/8,height*6.0/8)
		self.setMinimumSize(width/2,height/2)
		self.setMaximumSize(width,height)

		# General decoration
		self.setWindowTitle('Tables Utils GUI 0.1-alpha')
		self.setWindowIcon(icon)

		# Layout creation
		main_vbox:QVBoxLayout = QVBoxLayout()
		main_vbox.setContentsMargins(0,0,0,0)
		main_vbox.setSpacing(0)

		main_vbox.addLayout(Head(self.onButtonClick),5)
		main_vbox.addLayout(Body(None),95)

		self.setCentralWidget(self.layout)
		self.layout.setLayout(main_vbox)
		self.show()

	def onButtonClick( self) -> None:
		print('Clicked')























