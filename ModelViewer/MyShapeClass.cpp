#include "MyShapeClass.h"
#include <glm\gtx\rotate_vector.hpp>
void MyShapeClass::Render()
{
	super::Render(GL_TRIANGLES);
}
void MyShapeClass::CompileObject(vector3 a_vColor, String a_sName)
{
	m_nVertices = static_cast<int> (m_vVertexPosition.size());
	for(int i = 0; i < m_nVertices ; i++)
	{
		AddVertexColor( a_vColor );
		AddVertexUV(0.0f, 0.0f);
	}
	m_sName = a_sName;

	CompleteTriangleInfo(true);
	CalculateTangents();
	CompileOpenGL3X();
	MaterialManagerClass* pMatMangr = MaterialManagerClass::GetInstance();
	
}
//C--D
//|  |
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyShapeClass::AddQuad(vector3 a_vA, vector3 a_vB, vector3 a_vC, vector3 a_vD)
{
	AddVertexPosition( a_vA );
	AddVertexPosition( a_vB );
	AddVertexPosition( a_vC );

	AddVertexPosition( a_vC );
	AddVertexPosition( a_vB );
	AddVertexPosition( a_vD );
}
void MyShapeClass::GenerateCube(float a_mSize, vector3 a_vColor)
{
	if(a_mSize < 0.01f)
		a_mSize = 0.01f;

	Release(true);

	float fValue = 0.5f * a_mSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue,-fValue, fValue); //0
	vector3 point1( fValue,-fValue, fValue); //1
	vector3 point2( fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue,-fValue,-fValue); //4
	vector3 point5( fValue,-fValue,-fValue); //5
	vector3 point6( fValue, fValue,-fValue); //6
	vector3 point7(-fValue, fValue,-fValue); //7

	//F
	AddQuad( point0, point1, point3, point2);
	
	//B
	AddQuad( point5, point4, point6, point7);

	//L
	AddQuad( point4, point0, point7, point3);

	//R
	AddQuad( point1, point5, point2, point6);

	//U
	AddQuad( point3, point2, point7, point6);

	//D
	AddQuad( point4, point5, point0, point1);

	CompileObject(a_vColor, "cube");
}
void MyShapeClass::GenerateCone
	(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{

}
void MyShapeClass::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{
	if(a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release(true);
		
	//Calculating the bottom vertices
	std::vector<vector3 > vertexB;
	vertexB.push_back( vector3( 0.0f,-a_fHeight/2.0f, 0.0f) );
	GLfloat theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		theta += static_cast<GLfloat>(2*PI/a_nSubdivisions);
		vector3 temp = vector3(	static_cast<GLfloat>(cos(theta)) * a_fRadius,
								-a_fHeight/2.0f,
								-static_cast<GLfloat>(sin(theta)) * a_fRadius);
		vertexB.push_back( temp );
	}

	//calculating the top vertices
	std::vector<vector3 > vertexU;
	vertexU.push_back( vector3( 0.0f, a_fHeight/2.0f, 0.0f) );
	theta = 0;
	vector3 vHeight = vector3( 0.0f, a_fHeight, 0.0f);
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		vertexU.push_back( vertexB[i+1] + vHeight );
	}

	//Bottom Faces
	for (int i = 1; i < a_nSubdivisions; i++) 
	{
		AddVertexPosition(vertexB[0]);
		AddVertexPosition(vertexB[i+1]);
		AddVertexPosition(vertexB[i]);
	}
	AddVertexPosition(vertexB[0]);
	AddVertexPosition(vertexB[1]);
	AddVertexPosition(vertexB[a_nSubdivisions]);
	
	//Top Faces
	for (int i = 1; i < a_nSubdivisions; i++) 
	{
		AddVertexPosition(vertexU[0]);
		AddVertexPosition(vertexU[i]);
		AddVertexPosition(vertexU[i+1]);
	}
	AddVertexPosition(vertexU[0]);
	AddVertexPosition(vertexU[a_nSubdivisions]);
	AddVertexPosition(vertexU[1]);

	//Side Faces
	for (int i = 1; i < a_nSubdivisions; i++) 
	{
		AddVertexPosition(vertexB[i]);
		AddVertexPosition(vertexB[i+1]);
		AddVertexPosition(vertexU[i]);

		AddVertexPosition(vertexU[i]);
		AddVertexPosition(vertexB[i+1]);
		AddVertexPosition(vertexU[i+1]);
	}
	AddVertexPosition(vertexB[a_nSubdivisions]);
	AddVertexPosition(vertexB[1]);
	AddVertexPosition(vertexU[a_nSubdivisions]);

	AddVertexPosition(vertexU[a_nSubdivisions]);
	AddVertexPosition(vertexB[1]);
	AddVertexPosition(vertexU[1]);

	// Adding information about color and UVs to all faces
	int nFaces = (a_nSubdivisions * 6 + 6) * 3;
	for (int i = 1; i < nFaces; i++) 
	{
		AddVertexColor( a_vColor );
		AddVertexUV( 0.0f, 0.0f);
	}
	CompileObject(a_vColor, "cylinder");
}
void MyShapeClass::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor)
{
	if(a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release(true);
		
	//Calculating the top vertices
	std::vector<vector3 > vertexTopOuter;
	GLfloat theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		theta += static_cast<GLfloat>(2*PI/a_nSubdivisions);
		vector3 temp = vector3(	static_cast<GLfloat>(cos(theta)) * a_fOuterRadius,
								a_fHeight/2.0f,
								-static_cast<GLfloat>(sin(theta)) * a_fOuterRadius);
		vertexTopOuter.push_back( temp );
	}

	std::vector<vector3 > vertexTopInner;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		theta += static_cast<GLfloat>(2*PI/a_nSubdivisions);
		vector3 temp = vector3(	static_cast<GLfloat>(cos(theta)) * a_fInnerRadius,
								a_fHeight/2.0f,
								-static_cast<GLfloat>(sin(theta)) * a_fInnerRadius);
		vertexTopInner.push_back( temp );
	}

	//Bottom Outer
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexTopInner[i]);
		AddVertexPosition(vertexTopOuter[i]);
		AddVertexPosition(vertexTopOuter[i+1]);
	}
	AddVertexPosition(vertexTopInner[a_nSubdivisions -1]);
	AddVertexPosition(vertexTopOuter[a_nSubdivisions -1]);
	AddVertexPosition(vertexTopOuter[0]);

	//Bottom Inner
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexTopOuter[i+1]);
		AddVertexPosition(vertexTopInner[i+1]);
		AddVertexPosition(vertexTopInner[i]);
	}
	AddVertexPosition(vertexTopOuter[0]);
	AddVertexPosition(vertexTopInner[0]);
	AddVertexPosition(vertexTopInner[a_nSubdivisions -1]);

	//Calculating the bottom vertices
	std::vector<vector3 > vertexBottomOuter;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		theta += static_cast<GLfloat>(2*PI/a_nSubdivisions);
		vector3 temp = vector3(	static_cast<GLfloat>(cos(theta)) * a_fOuterRadius,
								-a_fHeight/2.0f,
								-static_cast<GLfloat>(sin(theta)) * a_fOuterRadius);
		vertexBottomOuter.push_back( temp );
	}

	std::vector<vector3 > vertexBottomInner;
	theta = 0;
	for (int i = 0; i < a_nSubdivisions; i++) 
	{
		theta += static_cast<GLfloat>(2*PI/a_nSubdivisions);
		vector3 temp = vector3(	static_cast<GLfloat>(cos(theta)) * a_fInnerRadius,
								-a_fHeight/2.0f,
								-static_cast<GLfloat>(sin(theta)) * a_fInnerRadius);
		vertexBottomInner.push_back( temp );
	}

	//Bottom Outer
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexBottomOuter[i+1]);
		AddVertexPosition(vertexBottomOuter[i]);
		AddVertexPosition(vertexBottomInner[i]);
	}
	AddVertexPosition(vertexBottomOuter[0]);
	AddVertexPosition(vertexBottomOuter[a_nSubdivisions -1]);
	AddVertexPosition(vertexBottomInner[a_nSubdivisions -1]);
	

	//Bottom Inner
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexBottomInner[i]);
		AddVertexPosition(vertexBottomInner[i+1]);
		AddVertexPosition(vertexBottomOuter[i+1]);
	}
	AddVertexPosition(vertexBottomInner[a_nSubdivisions -1]);
	AddVertexPosition(vertexBottomInner[0]);
	AddVertexPosition(vertexBottomOuter[0]);
	

	// Adding information about color and UVs to all faces
	int nFaces = ((a_nSubdivisions * 24) + 24);
	for (int i = 1; i < nFaces; i++) 
	{
		AddVertexColor( a_vColor );
		AddVertexUV( 0.0f, 0.0f);
	}
	//Vertical Inner
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexTopInner[i]);
		AddVertexPosition(vertexBottomInner[i+1]);
		AddVertexPosition(vertexBottomInner[i]);
	}
	AddVertexPosition(vertexTopInner[a_nSubdivisions - 1]);
	AddVertexPosition(vertexBottomInner[0]);
	AddVertexPosition(vertexBottomInner[a_nSubdivisions -1]);

	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexTopInner[i+1]);
		AddVertexPosition(vertexBottomInner[i+1]);
		AddVertexPosition(vertexTopInner[i]);
	}
	AddVertexPosition(vertexTopInner[0]);
	AddVertexPosition(vertexBottomInner[0]);
	AddVertexPosition(vertexTopInner[ a_nSubdivisions -1]);
	

	nFaces = ((a_nSubdivisions * 6) + 6);
	for (int i = 1; i < nFaces; i++) 
	{
		AddVertexColor( a_vColor );
		AddVertexUV( 0.0f, 0.0f);
	}

	//Vertical Outer
	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexBottomOuter[i]);
		AddVertexPosition(vertexBottomOuter[i+1]);
		AddVertexPosition(vertexTopOuter[i]);
	}
	AddVertexPosition(vertexBottomOuter[a_nSubdivisions - 1]);
	AddVertexPosition(vertexBottomOuter[0]);
	AddVertexPosition(vertexTopOuter[a_nSubdivisions -1]);

	for(int i = 0; i < a_nSubdivisions -1; i++)
	{
		AddVertexPosition(vertexTopOuter[i+1]);
		AddVertexPosition(vertexTopOuter[i]);
		AddVertexPosition(vertexBottomOuter[i+1]);
	}
	AddVertexPosition(vertexTopOuter[0]);
	AddVertexPosition(vertexTopOuter[ a_nSubdivisions -1]);
	AddVertexPosition(vertexBottomOuter[0]);
	

	nFaces = ((a_nSubdivisions * 6) + 6);
	for (int i = 1; i < nFaces; i++) 
	{
		AddVertexColor( a_vColor );
		AddVertexUV( 0.0f, 0.0f);
	}

	CompileObject(a_vColor, "tube");
}
void MyShapeClass::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor)
{
	//Sets minimum and maximum of subdivisions
	if(a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_vColor);
		return;
	}
	if(a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release(true);

	float fValue = 0.5f;
	vector3 pointA(-fValue,-fValue, fValue); //0
	vector3 pointB( fValue,-fValue, fValue); //1
	vector3 pointC(-fValue, fValue, fValue); //2

	//left to right List of vector3
	std::vector<vector3> vectorAB;
	vectorAB.push_back(pointA);
	for(int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp(pointB-pointA);
		temp /= a_nSubdivisions + 1;
		temp *= (i +1);
		vectorAB.push_back(temp + pointA);
	}
	vectorAB.push_back(pointB);

	//height increments
	float fHeight = pointC.y-pointA.y;
	fHeight /= a_nSubdivisions + 1;

	//List of Lists
	std::vector<std::vector<vector3>> list;
	list.push_back(vectorAB);
	for(int j = 0; j < a_nSubdivisions +1; j++)
	{
		std::vector<vector3> temp = list[0];
		float increment = fHeight * (j + 1);
		for(int i = 0; i < a_nSubdivisions + 2; i++)
		{
			temp[i].y += increment;
		}
		list.push_back(temp);
	}

	//Creating the patch of quads
	for(int j = 0; j < a_nSubdivisions + 1; j++)
	{
		for(int i = 0; i < a_nSubdivisions + 1; i++)
		{
			AddQuad(list[j][i], list[j][i+1], list[j+1][i], list[j+1][i+1]);
		}
	}
	
	//normalizing the vectors to make them round
	for(int i = 0; i < m_nVertices; i++)
	{
		m_vVertexPosition[i] = glm::normalize(m_vVertexPosition[i]);
		m_vVertexPosition[i] *= a_fRadius;
	}

	//RightSideFace
	int nVert = m_nVertices;
	std::vector<vector3> right;
	for(int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(0.0f,1.0f,0.0f));
		right.push_back(	static_cast <vector3>(rotation * glm::vec4(m_vVertexPosition[i],1.0f)));
	}

	
	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(right[i]);
	}

	//LeftSideFace
	std::vector<vector3> left;
	for(int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(0.0f,1.0f,0.0f));
		left.push_back(	static_cast <vector3>(rotation * glm::vec4(m_vVertexPosition[i],1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(left[i]);
	}

	//BackSideFace
	std::vector<vector3> back;
	for(int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 180.0f, vector3(0.0f,1.0f,0.0f));
		back.push_back(	static_cast <vector3>(rotation * glm::vec4(m_vVertexPosition[i],1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(back[i]);
	}

	//TopSideFace
	std::vector<vector3> top;
	for(int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(1.0f,0.0f,0.0f));
		top.push_back(	static_cast <vector3>(rotation * glm::vec4(m_vVertexPosition[i],1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(top[i]);
	}

	//BottomSideFace
	std::vector<vector3> bottom;
	for(int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(1.0f,0.0f,0.0f));
		bottom.push_back(	static_cast <vector3>(rotation * glm::vec4(m_vVertexPosition[i],1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(bottom[i]);
	}

	//int n = 0;
	//Vertices calculated
	//CompileObject(a_vColor, "sphere");
	CompileObject(a_vColor, "Sphere");
}