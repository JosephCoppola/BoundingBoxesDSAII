#include "BoundingBoxClass.h"
//The big 3
BoundingBoxClass::BoundingBoxClass(String a_sInstanceName)
{
	//Initialize variables
	m_pMeshOBB = nullptr;
	m_pMeshAABB = nullptr;
	OBBCentroid = vector3(0.0f,0.0f,0.0f);
	AABBCentroid = vector3(0.0f, 0.0f, 0.0f);
	OBBColor = MEGREEN;
	AABBColor = MEBLUE;
	m_mModelToWorld = matrix4(1.0f);
	m_obVisible = false;
	m_abVisible = false;
	scaleAABB = vector3(0.0f,0.0f,0.0f);
	scaleOBB = vector3(0.0f,0.0f,0.0f);
	minAABB = vector3(0.0f,0.0f,0.0f);
	maxAABB = vector3(0.0f,0.0f,0.0f);
	minOBB = vector3(0.0f,0.0f,0.0f);
	maxOBB = vector3(0.0f,0.0f,0.0f);

	//Get the singleton instance of the Model Manager
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;
	//Identify the instance from the list inside of the Model Manager
	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	//If there is no instance with that name the Identify Instance will return -1
	//In which case there is nothing to do here so we just return without allocating memory
	if(nInstance == -1)
		return;

	CalculateOBB(m_sInstance);
	CalculateAABB(m_sInstance);

	//Get the Model to World matrix associated with the Instance
	m_mModelToWorld = m_pModelMngr->GetModelMatrix(m_sInstance);
	//If the size of the radius is 0 it means that there are no points or all of them are allocated
	//right at the origin, which will cause an issue, so we just return with no allocations
	if(m_fRadius == 0.0f)
		return;
	//Crete a new Sphere and initialize it using the member variables

	// CREATES OBB
	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEGREEN); //LOOK AT THIS
	matrix4 scaleMat = glm::scale(matrix4(1.0f),scaleOBB);
	matrix4 translateMat = glm::translate(m_mModelToWorld, OBBCentroid);
	m_pMeshOBB->SetModelMatrix(translateMat * scaleMat);

	// CREATES AABB
	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEBLUE); //LOOK AT THIS
	matrix4 scaleMatAABB = glm::scale(matrix4(1.0f),scaleAABB);
	matrix4 translateMatAABB = glm::translate(m_mModelToWorld, AABBCentroid);
	m_pMeshAABB->SetModelMatrix(translateMatAABB * scaleMatAABB);
}
BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	//Initialize the Sphere using other instance of it
	m_sInstance = other.m_sInstance;
	m_obVisible = other.m_obVisible;
	m_abVisible = other.m_abVisible;
	m_fRadius = other.m_fRadius;
	OBBCentroid = other.OBBCentroid;
	AABBCentroid = other.AABBCentroid;
	m_mModelToWorld = other.m_mModelToWorld;
	m_pModelMngr = other.m_pModelMngr;
	
	minOBB = other.minOBB;
	minAABB = other.minAABB;
	maxOBB = other.maxOBB;
	maxAABB = other.maxAABB;

	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE); //LOOK AT THIS
	m_pMeshOBB->SetModelMatrix(glm::translate(m_mModelToWorld, OBBCentroid));
}
BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	//If the incoming instance is the same as the current there is nothing to do here
	if(this != &other)
	{
		//Release the existing object
		Release();
		//Construct the object as in the copy constructor
		m_sInstance = other.m_sInstance;
		m_obVisible = other.m_obVisible;
		m_abVisible = other.m_abVisible;
		m_fRadius = other.m_fRadius;
		OBBCentroid = other.OBBCentroid;
		AABBCentroid = other.AABBCentroid;
		m_mModelToWorld = other.m_mModelToWorld;
		m_pModelMngr = other.m_pModelMngr;

		minOBB = other.minOBB;
		minAABB = other.minAABB;
		maxOBB = other.maxOBB;
		maxAABB = other.maxAABB;
		
		m_pMeshOBB = new PrimitiveWireClass();
		m_pMeshOBB->GenerateCube(m_fRadius, MEWHITE); //LOOK AT THIS
		m_pMeshOBB->SetModelMatrix(glm::translate(m_mModelToWorld, OBBCentroid));
	}
	return *this;
}
BoundingBoxClass::~BoundingBoxClass()
{
	//Destroying the object requires releasing all the allocated memory first
	Release();
}
void BoundingBoxClass::Release(void)
{
	//If the mesh exists release it
	if(m_pMeshOBB != nullptr)
	{
		delete m_pMeshOBB;
		m_pMeshOBB = nullptr;
	}
	if(m_pMeshAABB != nullptr)
	{
		delete m_pMeshAABB;
		m_pMeshAABB = nullptr;
	}

	//The job of releasing the Model Manager Instance is going to be the work
	//of another method, we can't assume that this class is the last class
	//that uses this singleton, so we do not release it, we just make the pointer
	//point at nothing.
	m_pModelMngr = nullptr;
}
//Accessors
float BoundingBoxClass::GetRadius(void){ return m_fRadius; }
vector3 BoundingBoxClass::GetCentroid(void){ return OBBCentroid; } // CHANGE FOR AABB
vector3 BoundingBoxClass::GetColor(void){ return OBBColor; } // CHANGE FOR AABB
void BoundingBoxClass::SetColor(vector3 a_v3Color){ OBBColor = a_v3Color; } // CHANGE FOR AABB
matrix4 BoundingBoxClass::GetModelMatrix(void){ return m_mModelToWorld; }
void BoundingBoxClass::SetModelMatrix(matrix4 a_mModelMatrix) //Check here later
{
	m_mModelToWorld = a_mModelMatrix;

	m_pMeshOBB->SetModelMatrix(a_mModelMatrix);

	CalculateAABB(m_sInstance);

	matrix4 scaleMatOBB = glm::scale(matrix4(1.0f),scaleOBB);
	matrix4 translationMatOBB = glm::translate(m_mModelToWorld,OBBCentroid);
	m_pMeshOBB->SetModelMatrix(translationMatOBB * scaleMatOBB);

	matrix4 scaleMatAABB = glm::scale(matrix4(1.0f), scaleAABB);
	matrix4 translateMatAABB = glm::translate(AABBCentroid);
	m_pMeshAABB->SetModelMatrix(translateMatAABB * scaleMatAABB );
}
bool BoundingBoxClass::GetOBBVisible(void) { return m_obVisible; }
void BoundingBoxClass::SetOBBVisible(bool a_bVisible) { m_obVisible = a_bVisible; }
bool BoundingBoxClass::GetAABBVisible(void) { return m_abVisible; } //CHANGE
void BoundingBoxClass::SetAABBVisible(bool a_bVisible) { m_abVisible = a_bVisible; } //Change
String BoundingBoxClass::GetInstanceName(void){ return m_sInstance; }
//Methods
void BoundingBoxClass::CalculateOBB(String a_sInstance)
{
	//Get the vertices List to calculate the maximum and minimum
	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(a_sInstance);
	int nVertices = static_cast<int>(vVertices.size());
	
	//If the size of the List is 0 it means we dont have any vertices in this Instance
	//which means there is an error somewhere
	if(nVertices == 0)
		return;

	//Go one by one on each component and realize which one is the smallest one
	vector3 v3Minimum;
	if(nVertices > 0)
	{
		//We assume the first vertex is the smallest one
		v3Minimum = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x < v3Minimum.x)
				v3Minimum.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y < v3Minimum.y)
				v3Minimum.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z < v3Minimum.z)
				v3Minimum.z = vVertices[nVertex].z;
		}
		minOBB = v3Minimum;
	}
	
	//Go one by one on each component and realize which one is the largest one
	vector3 v3Maximum;
	if(nVertices > 0)
	{
		//We assume the first vertex is the largest one
		v3Maximum = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x > v3Maximum.x)
				v3Maximum.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y > v3Maximum.y)
				v3Maximum.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z > v3Maximum.z)
				v3Maximum.z = vVertices[nVertex].z;
		}
		maxOBB = v3Maximum;
	}

	//The centroid is going to be the point that is halfway of the min to the max
	OBBCentroid = minOBB + maxOBB;
	OBBCentroid /= 2.0f;

	vector3 scaleVector;

	scaleVector.x = glm::distance(v3Minimum.x,v3Maximum.x);
	scaleVector.y = glm::distance(v3Minimum.y,v3Maximum.y);
	scaleVector.z = glm::distance(v3Minimum.z,v3Maximum.z);

	scaleOBB = scaleVector;
}
void BoundingBoxClass::CalculateAABB(String a_sInstance)
{
	std::vector<vector3> newVertices = m_pModelMngr->GetVertices(a_sInstance);
	int nVertices = static_cast<int>(newVertices.size());

	if(nVertices == 0)
		return;

	std::vector<vector4> globalVerts = std::vector<vector4>(nVertices);

	for(int i = 0; i < nVertices; i++)
	{
		globalVerts[i] = vector4(newVertices[i].x, newVertices[i].y, newVertices[i].z, 1.0f);
		globalVerts[i] = m_mModelToWorld * globalVerts[i];
	}

	//Go one by one on each component and realize which one is the smallest one
	if(nVertices > 0)
	{
		minAABB = static_cast<vector3>(globalVerts[0]);

		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(globalVerts[nVertex].x < minAABB.x)
				minAABB.x = globalVerts[nVertex].x;
	
			if(globalVerts[nVertex].y < minAABB.y)
				minAABB.y = globalVerts[nVertex].y;

			if(globalVerts[nVertex].z < minAABB.z)
				minAABB.z = globalVerts[nVertex].z;
		}
	}
	
	//Go one by one on each component and realize which one is the largest one
	if(nVertices > 0)
	{

		maxAABB = static_cast<vector3>(globalVerts[0]);

		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(globalVerts[nVertex].x > maxAABB.x)
				maxAABB.x = globalVerts[nVertex].x;

			if(globalVerts[nVertex].y > maxAABB.y)
				maxAABB.y = globalVerts[nVertex].y;

			if(globalVerts[nVertex].z > maxAABB.z)
				maxAABB.z = globalVerts[nVertex].z;
		}
	}	

	//The centroid is going to be the point that is halfway of the min to the max
	AABBCentroid = minAABB + maxAABB;
	AABBCentroid /= 2.0f;

	vector3 scaleVector;

	scaleVector.x = glm::distance(minAABB.x,maxAABB.x);
	scaleVector.y = glm::distance(minAABB.y,maxAABB.y);
	scaleVector.z = glm::distance(minAABB.z,maxAABB.z);

	scaleAABB = scaleVector;
	
	return;
}

void BoundingBoxClass::Render( vector3 a_vColor )
{
	//If the shape is visible render it
	//otherwise just return
	if(!m_obVisible) //Check later
		return;
	//Calculate the color we want the shape to be
	vector3 vColor;
	//if the argument was MEDEFAULT just use the color variable in our class
	if(a_vColor == MEDEFAULT)
		vColor = AABBColor;
	else //Otherwise use the argument
		vColor = a_vColor;

	//render the shape using a special case of the Shape Render method which uses the Color Shader.
	m_pMeshOBB->Render( matrix4(1.0f), OBBColor );
	m_pMeshAABB->Render( matrix4(1.0f), AABBColor );
}