/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2014/07
*/
#ifndef __MYENGINE_H_
#define __MYENGINE_H_

#pragma warning( disable : 4251 )

#include "ME\system\MEDefinitions.h" //Definitions of MyEngine
#include "ME\system\SystemClass.h" //System related methods

#include "ME\system\WindowClass.h" //WinAPI encapsulated methods
#include "ME\system\FileReaderClass.h" //Reads an object and returns lines as strings
#include "ME\system\FolderClass.h" //Sets the working directory
#include "ME\system\GLSystemClass.h" //OpenGL 2.0 and 3.0 initialization

#include "ME\system\ShaderManagerClass.h" //Shader Manager, loads and manages different shader files
#include "ME\system\ShaderCompiler.h" //Compiles the shader objects

#include "ME\light\lightManagerClass.h" //Manages the light sources of the world

#include "ME\materials\MaterialManagerClass.h" //Manages the materials
#include "ME\materials\TextureManagerClass.h" //Manages the Textures, loads, display and release

#include "ME\mesh\Animation\AnimationClass.h" //Manages the animations in a model
#include "ME\mesh\Animation\FrameClass.h" //Manages the transformations of a model in a frame of time
#include "ME\mesh\Animation\SequenceClass.h" //Manages the starting and ending point of an animation
#include "ME\mesh\Animation\StateClass.h" //Manages the current state of the model

#include "ME\mesh\debug\AxisFrameClass.h"  //Creates a frame object
#include "ME\mesh\debug\AxisReferenceClass.h" //Creates an axis of reference
#include "ME\mesh\debug\BoxManagerClass.h" //manage boxes of the objects
#include "ME\mesh\debug\LineManagerClass.h" //Manages lines

#include "ME\mesh\physics\AABBClass.h" //Axis Aligned Bounding boxes
#include "ME\mesh\physics\CollisionSystemClass.h" //Manages the collision system

#include "ME\mesh\shape\PrimitiveClass.h" //Creates 3 Dimensional object primitives models based on shapes
#include "ME\mesh\shape\PrimitiveWireClass.h" //Creates 3 Dimensional object primitives in wireframe mode based on shapes
#include "ME\mesh\shape\PolygonClass.h"	//Creates 2 Dimensional objects based on shapes
#include "ME\mesh\shape\ModelManagerClass.h" //Manages models and instances
#include "ME\mesh\CameraClass.h" //Creates and manages the camera object for the world

#endif //__MYENGINE_H__