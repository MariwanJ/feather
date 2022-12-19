Note:
I imported this library that I found on github with the hope that I would be able to compile, and benifit of the work done. 
Unfortunatly, using Linux or Windows I couldn't compile the whole project completely and this never worked for me. I wasted my 3 weeks try to fix the issues without any results. Be aware of the problems that you might face.. This is here only as a backup for the past. (Mariwan Jalal 2022-12-11)
In the new branch (temp) you find all forked version saved by other users under the folder checkme. 
You find also a picture showing the size of each version.. But for me, none of them worked really on Linux. The whole project seems to be configured for Linux.
There are hard coded paths like /usr/local ..etc. 
MARIWAN 2022-12-13

Update:
I managed to fix many issues, specially with CMAKE and DLL creation for windows. There are many mores and it is very time consuming. 
Please don't fork at this stage. There will be many changes. 
2022-12-19 Mariwan
**************************************************************************************************************************************************


Feather
=======

![Feather Logo](https://raw.githubusercontent.com/richardlayman/feather/master/assets/images/logo.png)

3d modeling and animation application.

![Feather UI](https://raw.githubusercontent.com/richardlayman/feather/master/assets/images/ui_v0_1.png)

Current Status
---------------
Feather is still a WIP that has not yet reached v0.1. I hope to release v0.1 sometime in 2016. Below is a list of tasks to be completed for the v0.1 release.
* Integrate Vulkan viewport into Qt (in progress)
* Feather file format IO
* Undo/Redo system
* Finish up nodes

Introduction
---------------
Feather is a 3D application targeted for small studios and indie animators. Feather focuses on being easy to modify with idea being that it's a tool that the artist can change to suite their needs. This could be modifying the UI, creating new nodes or commands, or using Feather from the command line. This is achieved by having a fully scripted QML interface and a very simple way of creating plugins. Everything in Feather is a node who's output fields can be plugged into any input node field of the same type. This provides the user with a great amount of flexiblity when dealing with complex problems.

v0.1 Features
---------------
* C++ core
* QtQuick interface
* Open/Save feather project files
* DAG scenegraph
* C++ Plugin architecture
* Import/Export obj files
* Outliner Editor
* SceneGraph Editor
* Field Editor
* Layer Editor
* 3D Viewport Editor
* Objects - Curves, Plane, Cube, MeshShape
* Modify Tools - Bevel, Extrude, Inset
* Selection Tools - Pick, Box, Ring, Loop
* Component Selection - Vertex, Edge, Face, Object
* Transformation Tools (all components) - Translate, Rotate, Scale

