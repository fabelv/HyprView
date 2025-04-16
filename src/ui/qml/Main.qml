import QtQuick.Controls.Material 2.15

import "screens"
import "components"
import "dialogs"

ApplicationWindow {
    id: window
    objectName: "applicationWindow"

    Material.theme: Material.Dark
    Material.accent: Material.Teal

    visible: true
    width: 1280
    height: 800
    title: "HyprView"

    menuBar: AppMenuBar { }

    ConfirmDialog {}

    MainScreen {}
}


