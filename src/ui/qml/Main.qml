import QtQuick.Controls

import "screens"
import  "components"
import "dialogs"

ApplicationWindow {
    id: window

    visible: true
    width: 1200
    height: 600
    title: "HyprView"

    menuBar: AppMenuBar { }

    ConfirmDialog {}

    MainScreen {}
}

