import sqlite3
from PyQt5 import QtWidgets,QtCore
from PyQt5.QtWidgets import QMessageBox
import sys
import hashlib
import time

class App(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()
        self.connectDatabase()
        self.initiated()

    def connectDatabase(self):
        self.connection = sqlite3.connect("D:/KOdlama denemelerim/Users.db")
        self.lib_pointer= self.connection.cursor()
        self.lib_pointer.execute("CREATE TABLE IF NOT EXISTS Users (Usernames TEXT, Passwords TEXT, Qualifications TEXT)")
        #self.lib_pointer.execute("ALTER TABLE Users ADD COLUMN Qualifications TEXT")
        self.connection.commit()
       
    
    def cutTheConnection(self):
        self.connection.close()
        
        
    def initiated(self):
        self.username_name = QtWidgets.QLabel("Username:")
        self.username_password = QtWidgets.QLabel("Password:")
        self.login_succeed = QtWidgets.QLabel("Login Succeed!")
        #self.success = QtWidgets.QLabel()
        self.register = QtWidgets.QPushButton("Sign Up")
        self.fail = QtWidgets.QLabel("Username or password has an error!")
        self.connectionFault =QtWidgets.QLabel("Database connection has not found!")
        self.login = QtWidgets.QPushButton("Login")
        self.cancel = QtWidgets.QPushButton("Cancel")

        self.horizantial_layout = QtWidgets.QHBoxLayout()
        self.horizantial_layout.addStretch()
        self.horizantial_layout.addWidget(self.login)
        self.horizantial_layout.addWidget(self.cancel)
        self.horizantial_layout.addWidget(self.register)
        

        self.login_name = QtWidgets.QLineEdit()
        self.login_password = QtWidgets.QLineEdit()
        self.login_password.setEchoMode(QtWidgets.QLineEdit.Password) #Kullanıcının girdiği şifrenin karakterlerini gizler.

        self.vertical_layout = QtWidgets.QVBoxLayout()
        self.vertical_layout.addWidget(self.username_name)
        self.vertical_layout.addWidget(self.login_name)
        #vertical_layout.addStretch(1)
        self.vertical_layout.addWidget(self.username_password)
        self.vertical_layout.addWidget(self.login_password)
        #vertical_layout.addStretch(1)
        self.vertical_layout.addLayout(self.horizantial_layout)
        self.vertical_layout.setAlignment(QtCore.Qt.AlignTop)

        self.setLayout(self.vertical_layout)
        self.setWindowTitle("Giris")
        self.login.clicked.connect(self.click)
        self.cancel.clicked.connect(self.click)
        self.register.clicked.connect(self.click)
        self.show()

    def click(self):
        sender = self.sender()
        if sender.text() == "Login":
            try:
                self.connectDatabase()
                self.lib_pointer.execute("""SELECT "Usernames", "Passwords" FROM Users""")
                data = self.lib_pointer.fetchall()
                hash_object = hashlib.new("sha512")
                hash_object.update(self.login_password.text().encode("UTF-8"))
                hashed_password = hash_object.hexdigest()
                if (self.login_name.text(), hashed_password) in data:
                    self.vertical_layout.addWidget(self.login_succeed)
                    self.showSecondInterface()
                    
                else:
                    self.vertical_layout.addWidget(self.fail)
                    self.vertical_layout.addStretch()
                    self.cutTheConnection()
                    
            except:
                self.vertical_layout.addWidget(self.connectionFault)
                self.vertical_layout.addStretch()
                self.cutTheConnection()

        elif sender.text() == "Sign Up":
            self.connectDatabase()
            hash_object_new= hashlib.new("sha512")
            hash_object_new.update(self.login_password.text().encode("UTF-8"))
            hashed_password = hash_object_new.hexdigest()
            self.lib_pointer.execute("""INSERT INTO Users VALUES(?,?,?)""",(self.login_name.text(),hashed_password,"None"))
            self.connection.commit()
            time.sleep(1)
            print("Username has been added into the list")
            #self.cutTheConnection()
            

        elif sender.text() == "Cancel":
            self.cutTheConnection()
            sys.exit()

        
    def showSecondInterface(self):
        self.app2 = QtWidgets.QWidget()
        self.app2.setWindowTitle("Details")
        self.qualifications = QtWidgets.QTextEdit()
        self.vertical_layout2 = QtWidgets.QVBoxLayout()
        self.vertical_layout2.addWidget(self.qualifications)
        self.add_info = QtWidgets.QPushButton("Add Information")
        self.delete_info = QtWidgets.QPushButton("Delete Information")
        self.horizantial_layout2 = QtWidgets.QHBoxLayout()
        self.horizantial_layout2.addStretch()
        self.horizantial_layout2.addWidget(self.add_info)
        self.horizantial_layout2.addWidget(self.delete_info)
        self.vertical_layout2.addLayout(self.horizantial_layout2)
        self.app2.setLayout(self.vertical_layout2)
        self.add_info.clicked.connect(self.click2)
        self.delete_info.clicked.connect(self.click2)
        self.connection.commit()
        #self.cutTheConnection()
        self.app2.show()
    
    def click2(self):
        sender2 = self.sender()
        if  sender2.text() == "Add Information":
            text_in_qualifications = self.qualifications.toPlainText()
            self.messageBox = QMessageBox()
            self.messageBox.setIcon(QMessageBox.Information)
            self.messageBox.setText("Information has been submitted!")
            #self.connectDatabase()
            #self.submit_screen = QtWidgets.QWidget()
            #self.qualification = QtWidgets.QLineEdit()
            self.submit = QtWidgets.QPushButton("Submit")
            self.vertical_layout3 = QtWidgets.QVBoxLayout()
            #self.vertical_layout3.addWidget(self.qualification)
            #self.vertical_layout3.addWidget(self.submit)
            #self.submit_screen.setLayout(self.vertical_layout3)
            #self.submit_screen.show()
            hash_object_qualifications = hashlib.new("sha512")
            hash_object_qualifications.update(text_in_qualifications.encode("UTF-8"))
            hashed_qualifications = hash_object_qualifications.hexdigest()
            self.lib_pointer.execute("""UPDATE Users SET Qualifications = ? WHERE Usernames = ?""",(hashed_qualifications,self.login_name.text()))
            self.messageBox.exec_()
            #self.submit.clicked.connect(self.messageBox.exec_())
            self.connection.commit()
            self.cutTheConnection()

        elif sender2.text() == "Delete Information":
            self.connectDatabase()
            self.lib_pointer.execute("""DELETE FROM Users WHERE Qualifications = ?""",(self.messageBox.text(),))
            self.connection.commit()              

app = QtWidgets.QApplication(sys.argv)
first_app = App()
sys.exit(app.exec_())
