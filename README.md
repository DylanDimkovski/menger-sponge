# Menger Sponge Generated For COSC1226

## Overview
The main goals of this assignmentare to allow you put into practice the topics and techniques you are learning in the first half of this course, and to help you gain an appreciation for the differences between programming 3D Graphics using OpenGL in Immediate Mode (Fixed-FunctionPipeline)and the Modern approach (ShaderPrograms).This includes not only differences in the programming model and APIs, but also how the latter approach allows you to makemore efficient utilisationof modern GPU hardware.

## Interaction Control

### Scene Controls
⋅⋅* '+' / '-' - Increase Or Decrease Sponge Subdivision Level
⋅⋅* '1' to '6' - Select the Respective Scene
⋅⋅* 'H' - Toggle On Screen Display On/Off (Does not affect FPS counter)
⋅⋅* 'L' - Toggle Lighting On/Off
⋅⋅* '<' and '>' - Increaase or Decrease Number Of Lights in a Scene
⋅⋅* 'Z' - Toggle Depth Buffering On/Off
⋅⋅* 'C' - Toggle Backface Culling On/Off

### Camera Controls
⋅⋅* 'WASD' - Move Camera Forward/Backward & Strafe Left/Right
⋅⋅* 'QE' - Move Camera Directly Up/Down
⋅⋅* Horizontal Or Vertical Mouse Movement - Rotate Camera (Only when Left Mouse Button is Pressed)

## On Screen Display
The OSD will include:

⋅⋅⋅
* Scene: Scene Name
* Display: Resolution and Refresh Rate
* FPS: Frames Per Second
* Subdivisons: Division Number of Sponge
* Verticies: Number of Verticies Rendered
* Faces: Number of Faces Rendered
* Data: Size of Vertex Data in Bytes
* Lighting: On/Off
* Depth Testing: On/Off
* Backface Culling: On/Off