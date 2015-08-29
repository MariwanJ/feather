/***********************************************************************
 *
 * Filename: LayerEditor.qml 
 *
 * Description: Container for layers.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

import QtQuick 2.3
import QtQuick.Window 2.2
import feather.scenegraph 1.0
import feather.layer 1.0
import QtQuick.Controls 1.4

Window {
    id: layerEditor 
    title: "Layer Editor"
    visible: true
    flags: Qt.Tool
    width: 200
    height: 200
    property SceneGraph scenegraph: Null

    AddLayerDialog { id: addLayerDialog }

    Action {
        id: addLayerAction
        text: "Add Layer"
        tooltip: "Add a new layer to the Layer Editor"
        onTriggered: { addLayerDialog.visible = true }
    }

    Action {
        id: removeLayerAction
        text: "Remove Layer"
        tooltip: "Remove selected layer from the Layer Editor"
        onTriggered: { if(view.currentIndex){ layerModel.removeLayer(view.currentIndex); view.currentIndex = view.currentIndex-1 } }
    }

    Action {
        id: moveLayerUpAction
        text: "Move Layer Up"
        tooltip: "move the selected layer up the Layer Editor stack"
        onTriggered: { if(view.currentIndex < layerModel.rowCount()-1){ layerModel.moveLayer(view.currentIndex,view.currentIndex+1); view.currentIndex = view.currentIndex+1 } }
    }

    Action {
        id: moveLayerDownAction
        text: "Move Layer Down"
        tooltip: "move the selected layer down the Layer Editor stack"
        onTriggered: { if(view.currentIndex > 0){ layerModel.moveLayer(view.currentIndex,view.currentIndex-1); view.currentIndex = view.currentIndex-1 } }
    }


    Rectangle {
        id: toolBar
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        height: 36
        border.color: "black"
        border.width: 1
        color: properties.getColor("menu")

        Row {
            spacing: 4
            anchors.fill: parent
            anchors.margins: 2

            ToolButton {
                width: 32; height: 32
                iconSource: "/usr/local/feather/ui/icons/layer_add.svg"
                iconName: "add layer"
                action: addLayerAction 
            }

            ToolButton {
                width: 32; height: 32
                iconSource: "/usr/local/feather/ui/icons/layer_remove.svg"
                iconName: "remove layer"
                action: removeLayerAction 
            }

            ToolButton {
                width: 32; height: 32
                iconSource: "/usr/local/feather/ui/icons/layer_move_up.svg"
                iconName: "move layer up"
                action: moveLayerUpAction 
            }

            ToolButton {
                width: 32; height: 32
                iconSource: "/usr/local/feather/ui/icons/layer_move_down.svg"
                iconName: "move layer down"
                action: moveLayerDownAction 
            }

        }

    }    


    LayerModel { id: layerModel }

    Component {
        id: layerBar
        LayerBar { 
            id: bar
            width: parent.width
        }
    }
 
    Rectangle {
        id: layerFrame
        anchors.top: toolBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: parent.height
        anchors.margins: 1
        border.color: "black"
        border.width: 1
        color: properties.getColor("windowBg")
 
        ListView {
            id: view
            spacing: 0
            anchors.fill: parent
            verticalLayoutDirection: ListView.BottomToTop
            model: layerModel
            delegate: layerBar
        }

    }


    function updateColor() {
        layerFrame.color = properties.getColor("panel")        
        layerEditor.color = properties.getColor("windowBg")
        toolBar.color = properties.getColor("menu")
        
    }

    function layout_changed(){
        view.update()
    }

    function add_layer(name){
        if(name!="")
            layerModel.addLayer(view.currentIndex,name,properties.getColor("windowBg"),true,false)
    }

    Component.onCompleted: {
        updateColor()
        properties.colorsChanged.connect(updateColor)
        layerModel.layoutChanged.connect(layout_changed)
        addLayerDialog.addLayer.connect(add_layer)
    }    

}