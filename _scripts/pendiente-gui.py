#!/usr/bin/python3
# -*- coding: utf-8 -*-

from PySide6.QtWidgets import (
    QApplication, QMainWindow, QLabel, QTabWidget)
from PySide6.QtCore import QSize
import sys


class Caja(QLabel):
    def __init__(self, color):
        super().__init__()
        self.setStyleSheet(f"background-color:{color}")


class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # creamos un layout de pestañas
        pestannas = QTabWidget()
        pestannas.setTabPosition(QTabWidget.North)
        pestannas.setMovable(True)

        # Añadimos varios widgets como pestañas con nombres
        pestannas.addTab(Caja("orange"), "Uno")
        pestannas.addTab(Caja("magenta"), "Dos")
        pestannas.addTab(Caja("purple"), "Tres")
        pestannas.addTab(Caja("red"), "Cuatro")

        # asignamos las pestañas como widget central
        self.setCentralWidget(pestannas)
        self.setMinimumSize(QSize(480, 320))


if __name__ == "__main__":
    app = QApplication(sys.argv)
    ventana = MainWindow()
    ventana.show()
    sys.exit(app.exec_())
