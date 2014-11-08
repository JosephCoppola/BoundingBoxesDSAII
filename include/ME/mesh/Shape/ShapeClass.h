/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2013
--------------------------------------------------------------------------------------------------*/
#ifndef __SHAPECLASS_H_
#define __SHAPECLASS_H_
#include "ME\system\SystemClass.h"
#include "ME\mesh\CameraClass.h"
#include "ME\materials\MaterialManagerClass.h"
#include "ME\light\LightManagerClass.h"
#include "ME\System\ShaderManagerClass.h"
#include <vector>

namespace MyEngine
{

class MyEngineDLL ShapeClass
{
public:
	glm::mat4 m_mToWorld; //GLM Model Matrix
	MaterialManagerClass* m_pMaterialMngr; //Material Manager
	LightManagerClass* m_pLightMngr; //Light Manager
	ShaderManagerClass* m_pShaderMngr; //Shader Manager
	int m_nMaterialIndex; //Material of the Shape
protected:
	GLuint m_vao; //OpenGL Vertex Array Object
	GLuint m_VertexBuffer; //OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer; //OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer; //OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer;	//OpenGL Buffer (will hold the Normal Buffer)
	GLuint m_TangentBuffer;	//OpenGL Buffer (will hold the Tangent Buffer)
	GLuint m_BinormalBuffer;	//OpenGL Buffer (will hold the Binormal Buffer)
	
	String m_sShaderProgramName;

	String m_sName;

	int m_nVertices; //Number of vertices in the shape
	std::vector<vector3> m_vVertexPosition; //Vector of Vertices
	std::vector<vector3> m_vVertexColor; //Vector of Colors
	std::vector<vector3> m_vVertexNormal; //Vector of Normals
	std::vector<vector3> m_vVertexTangent; //Vector of Tangents
	std::vector<vector3> m_vVertexBinormal; //Vector of Binormals
	std::vector<vector3> m_vVertexUV; //vector of UVS
	
	CameraClass* m_pCamera; //Pointer to the singleton of CameraClass

	bool m_bBinded; //Indicate if memory has been reserved for GPU variables
	vector3 m_v3Pivot;
	vector3 m_v3Max;
	vector3 m_v3Min;

	bool m_bVisible;
	bool m_bCollidable;
public:
	//Constructor
	ShapeClass();
	//Copy Constructor
	ShapeClass(const ShapeClass& other);
	//Copy Assignment Operator
	virtual ShapeClass& operator=(const ShapeClass& other);

	//Destructor
	~ShapeClass(void);
	
	//Release
	void Release (bool a_bReleaseOpenGL = false);

	//Clears OpenGL Buffers
	void ReleaseOpenGL(void);

	//Initializes the OpenGL vao, Buffer and Program
	bool CompileOpenGL3X(void);
	
	//Sets the Model Matrix in base of another Matrix (No Parameters sets the Identity)
	void SetModelMatrix(const glm::mat4 a_mToWorld = glm::mat4(1.0f));
	//Returns the Model Matrix
	glm::mat4& GetModelMatrix(void);
	//Property of the ModelMatrix
	__declspec(property(put = SetModelMatrix, get = GetModelMatrix)) glm::mat4 ModelMatrix;

	void SetName(String input);
	String GetName(void);
	__declspec(property(put = SetName, get = GetName)) String Name;

	//Swaps the content with other shape
	void Swap(ShapeClass& other);
	
	//Renders the content of the shape
	virtual void Render(GLenum mode = GL_TRIANGLE_FAN, matrix4 input = matrix4(1.0f));
	
	virtual void Render( matrix4 a_mToWorld, vector3 a_vColor);

	//Adds a new point to the vector of vertices
	void AddVertexPosition(vector3 input);
	void AddVertexPosition(const float x, const float y, const float z);

	//Adds a new color to the vector of vertices
	void AddVertexColor(vector3 input);
	void AddVertexColor(const float r, const float g, const float b);

	//Adds a new normal to the vector of vertices
	void AddVertexNormal(vector3 input);
	void AddVertexNormal(const float x, const float y, const float z);

	//Adds a new binormal to the vector of vertices
	void AddVertexBinormal(vector3 input);
	void AddVertexBinormal(const float x, const float y, const float z);

	//Adds a new tangent to the vector of vertices
	void AddVertexTangent(vector3 input);
	void AddVertexTangent(const float x, const float y, const float z);

	//Adds a new uv to the vector of vertices
	void AddVertexUV(vector3 input);
	void AddVertexUV(const float u, const float v, const float w = 0);

	vector3 GetMin(void);
	void SetMin(vector3 a_v3Min);
	vector3 GetMax(void);
	void SetMax(vector3 a_v3Max);

	//Releases the vectors (leaving the OpenGL buffer initializated)
	void ReleaseVectors(void);

	bool IsBinded(void); //Specifies if the model has been binded to a shader structure

	bool InstanceFromShape(const ShapeClass& other);

	void CompleteTriangleInfo(bool a_bAverageNormals = false);
	void CalculateTangents(void);

	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);//Set the shader to the newly load shader
	void SetShaderProgram(String a_sShaderName);//Sets the shader of the Shape to a loaded shader

	void SetPivot(vector3 a_v3Pivot);

	void SetCollidable(bool a_bCollidable);
	bool GetCollidable(void);

	void SetVisible(bool a_bVisible);
	bool GetVisible(void);

	
	void SetMaterial(String a_sMaterialName);

	void CalculateMaxAndMin(void);
	void CalculateBoxes(void);

	std::vector<vector3> GetVertices(void);

protected:
	void Init(void); //Initializes various settings
private:
	
};

EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ShapeClass>;
EXPIMP_TEMPLATE template class MyEngineDLL std::vector<ShapeClass*>;

}
#endif //_SHAPECLASS_H