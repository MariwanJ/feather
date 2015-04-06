/***********************************************************************
 *
 * Filename: NodeOutMenu.qml 
 *
 * Description: List output fields of the node and their connections. 
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
import QtQuick.Controls 1.2
import feather.node 1.0

PopupMenu {
    id: popup
    visible: false

    ListModel {
        id: popupModel

        ListElement {
            name: "A"
        }
        ListElement {
            name: "B"
        }
    }

    ListView {
        anchors.fill: parent
        anchors.margins: 2
        model: popupModel
        delegate: MenuButton { label: name } 
        spacing: 2
    }
}

