from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QIODevice
from google.protobuf.message import DecodeError
from google.protobuf import message
from google.protobuf.descriptor_pb2 import MessageOptions
from Gen import messages_pb2

class SerialProtoParser(QWidget):
    def __init__(self):
        super(SerialProtoParser, self).__init__()
        # Serial port
        self.__serialPort = QSerialPort()
        # Setup Serialport
        # We are using USB serial driver, so the baud rate doesn't matter
        self.__serialPort.setBaudRate(QSerialPort.Baud115200, QSerialPort.Input)
        self.destroyed.connect(self.close)
        # Get the list of all available serial ports
        portsList = QSerialPortInfo.availablePorts()
        # Only connect to Chibios port
        chibiOsPort = None
        for port in portsList:
            if ("ChibiOS" in port.description()):
                chibiOsPort = port
        if(chibiOsPort is None):
            print("Cannot find chibios based device")
        else:
            # Set the serial port
            self.__serialPort.setPort(chibiOsPort)
            self.__serialPort.setDataBits(QSerialPort.Data8)
            self.__serialPort.setFlowControl(QSerialPort.NoFlowControl)
            self.__serialPort.setParity(QSerialPort.NoParity)
            self.__serialPort.setStopBits(QSerialPort.OneStop)
            # Connect signals and slots
            self.__serialPort.readyRead.connect(self.__onSerialPortReadyRead)
            # Open the device
            self.__serialPort.open(QIODevice.ReadOnly)

    def __onSerialPortReadyRead(self):
        bytesRead = self.__serialPort.readAll()
        msg = messages_pb2.Message1()
        # print(msg.DESCRIPTOR.fields[0].number)
        if(ord(bytesRead[0])) is msg.DESCRIPTOR.fields[0].number:
            msg.ParseFromString(bytesRead[1:])
            print(msg)
        # print('-----------')
        # msg2 = messages_pb2.Message2()
        # msg2.ParseFromString(bytesRead)
        # print(msg2)
        # print('++++++++++++')
    def closeEvent(self, event) -> None:
        # On close, close the serial connection
        print("Closing serial port")
        self.__serialPort.close()

if __name__ == '__main__':
    app = QApplication([])
    parser = SerialProtoParser()
    parser.show()
    app.exec_()
