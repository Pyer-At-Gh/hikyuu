# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'Ui_HkuXueqiuAccountWidget.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_HkuXueqiuAccountForm(object):
    def setupUi(self, HkuXueqiuAccountForm):
        HkuXueqiuAccountForm.setObjectName("HkuXueqiuAccountForm")
        HkuXueqiuAccountForm.resize(400, 300)
        self.formLayout = QtWidgets.QFormLayout(HkuXueqiuAccountForm)
        self.formLayout.setObjectName("formLayout")
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.add_pushButton = QtWidgets.QPushButton(HkuXueqiuAccountForm)
        self.add_pushButton.setObjectName("add_pushButton")
        self.horizontalLayout.addWidget(self.add_pushButton)
        self.edit_pushButton = QtWidgets.QPushButton(HkuXueqiuAccountForm)
        self.edit_pushButton.setObjectName("edit_pushButton")
        self.horizontalLayout.addWidget(self.edit_pushButton)
        self.remove_pushButton = QtWidgets.QPushButton(HkuXueqiuAccountForm)
        self.remove_pushButton.setObjectName("remove_pushButton")
        self.horizontalLayout.addWidget(self.remove_pushButton)
        self.refresh_pushButton = QtWidgets.QPushButton(HkuXueqiuAccountForm)
        self.refresh_pushButton.setObjectName("refresh_pushButton")
        self.horizontalLayout.addWidget(self.refresh_pushButton)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.horizontalLayout.addItem(spacerItem)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.line = QtWidgets.QFrame(HkuXueqiuAccountForm)
        self.line.setFrameShape(QtWidgets.QFrame.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.verticalLayout.addWidget(self.line)
        self.tableView = QtWidgets.QTableView(HkuXueqiuAccountForm)
        self.tableView.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.tableView.setObjectName("tableView")
        self.tableView.horizontalHeader().setStretchLastSection(True)
        self.verticalLayout.addWidget(self.tableView)
        self.formLayout.setLayout(0, QtWidgets.QFormLayout.SpanningRole, self.verticalLayout)

        self.retranslateUi(HkuXueqiuAccountForm)
        QtCore.QMetaObject.connectSlotsByName(HkuXueqiuAccountForm)

    def retranslateUi(self, HkuXueqiuAccountForm):
        _translate = QtCore.QCoreApplication.translate
        HkuXueqiuAccountForm.setWindowTitle(_translate("HkuXueqiuAccountForm", "Form"))
        self.add_pushButton.setText(_translate("HkuXueqiuAccountForm", "Add"))
        self.edit_pushButton.setText(_translate("HkuXueqiuAccountForm", "Edit"))
        self.remove_pushButton.setText(_translate("HkuXueqiuAccountForm", "Remove"))
        self.refresh_pushButton.setText(_translate("HkuXueqiuAccountForm", "Refresh"))
