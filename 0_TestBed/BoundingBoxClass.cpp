#include "BoundingBoxClass.h"
//The big 3
BoundingBoxClass::BoundingBoxClass(String a_sInstanceName)
{
	//Initialize variables
	m_pMeshOBB = nullptr;
	m_pMeshAABB = nullptr;
	OBBCentroid = vector3(0.0f,0.0f,0.0f);
	AABBCentroid = vector3(0.0f, 0.0f, 0.0f);
	OBBColor = MEWHITE;
	AABBColor = MEWHITE;
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

	//Calculate the intial OBB and AABB
	CalculateBoundingBox(m_sInstance);

	//Get the Model to World matrix associated with the Instance
	m_mModelToWorld = m_pModelMngr->GetModelMatrix(m_sInstance);

	// CREATES OBB
	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
	matrix4 scaleOBBMat = glm::scale(matrix4(1.0f),scaleOBB);
	matrix4 translateOBBMat = glm::translate(m_mModelToWorld, OBBCentroid);
	m_pMeshOBB->SetModelMatrix(translateOBBMat * scaleOBBMat);

	// CREATES AABB
	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE); 
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
	OBBCentroid = other.OBBCentroid;
	AABBCentroid = other.AABBCentroid;
	m_mModelToWorld = other.m_mModelToWorld;
	m_pModelMngr = other.m_pModelMngr;
	
	minOBB = other.minOBB;
	minAABB = other.minAABB;
	maxOBB = other.maxOBB;
	maxAABB = other.maxAABB;

	//Calculate the new OBB and AABB
	CalculateBoundingBox(m_sInstance);

	// CREATES OBB
	m_pMeshOBB = new PrimitiveWireClass();
	m_pMeshOBB->GenerateCube(1.0f, MEWHITE);
	matrix4 scaleOBBMat = glm::scale(matrix4(1.0f),scaleOBB);
	matrix4 translateOBBMat = glm::translate(m_mModelToWorld, OBBCentroid);
	m_pMeshOBB->SetModelMatrix(translateOBBMat * scaleOBBMat);

	// CREATES AABB
	m_pMeshAABB = new PrimitiveWireClass();
	m_pMeshAABB->GenerateCube(1.0f, MEWHITE); 
	matrix4 scaleMatAABB = glm::scale(matrix4(1.0f),scaleAABB);
	matrix4 translateMatAABB = glm::translate(m_mModelToWorld, AABBCentroid);
	m_pMeshAABB->SetModelMatrix(translateMatAABB * scaleMatAABB);
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
		OBBCentroid = other.OBBCentroid;
		AABBCentroid = other.AABBCentroid;
		m_mModelToWorld = other.m_mModelToWorld;
		m_pModelMngr = other.m_pModelMngr;

		OBBColor = other.OBBColor;
		AABBColor = other.AABBColor;

		minOBB = other.minOBB;
		minAABB = other.minAABB;
		maxOBB = other.maxOBB;
		maxAABB = other.maxAABB;

		m_pMeshOBB = new PrimitiveWireClass();
		matrix4 scaleMatOBB = glm::scale(matrix4(1.0f),scaleOBB);
		matrix4 translateOBB = glm::translate(m_mModelToWorld, OBBCentroid);
		m_pMeshOBB->SetModelMatrix(scaleMatOBB * translateOBB);


		m_pMeshAABB = new PrimitiveWireClass();
		matrix4 scaleMatAABB = glm::scale(matrix4(1.0f),scaleAABB);
		matrix4 translateAABB = glm::translate(m_mModelToWorld, AABBCentroid);
		m_pMeshAABB->SetModelMatrix(scaleMatAABB * translateAABB);
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
vector3 BoundingBoxClass::GetCentroidOBB(void){ return OBBCentroid; } 
vector3 BoundingBoxClass::GetCentroidAABB(void){ return AABBCentroid; } 

vector3 BoundingBoxClass::GetColorOBB(void){ return OBBColor; }
void BoundingBoxClass::SetColorOBB(vector3 a_v3Color){ OBBColor = a_v3Color; } 

vector3 BoundingBoxClass::GetColorAABB(void){ return AABBColor; } 
void BoundingBoxClass::SetColorAABB(vector3 a_v3Color){ AABBColor = a_v3Color; } 

void BoundingBoxClass::SetAABBVisible(bool a_bVisible){ m_abVisible = a_bVisible; }
bool BoundingBoxClass::GetAABBVisible(void){ return m_abVisible; }

void BoundingBoxClass::SetOBBVisible(bool a_bVisible){ m_obVisible = a_bVisible; }
bool BoundingBoxClass::GetOBBVisible(void){ return m_obVisible; }

vector3 BoundingBoxClass::GetSizeOBB(void) {return scaleOBB;}
void BoundingBoxClass::SetSizeOBB(vector3 p_sizeVector){scaleOBB = p_sizeVector;}

vector3 BoundingBoxClass::GetSizeAABB(void){return scaleAABB;}
void BoundingBoxClass::SetSizeAABB(vector3 p_sizeVector){scaleAABB = p_sizeVector;}

matrix4 BoundingBoxClass::GetModelMatrix(void){ return m_mModelToWorld; }

vector3 BoundingBoxClass::GetMinOBB(void){ return minOBB; }
vector3 BoundingBoxClass::GetMaxOBB(void){ return maxOBB; }

vector3 BoundingBoxClass::GetMinAABB(void){ return minAABB; }
vector3 BoundingBoxClass::GetMaxAABB(void){ return maxAABB; }

String BoundingBoxClass::GetInstanceName(void){ return m_sInstance; }

void BoundingBoxClass::SetModelMatrix(matrix4 a_mModelMatrix) //Check here later
{
	m_mModelToWorld = a_mModelMatrix;

	m_pMeshOBB->SetModelMatrix(a_mModelMatrix);

	CalculateBoundingBox(m_sInstance);

	matrix4 scaleMatOBB = glm::scale(matrix4(1.0f),scaleOBB);
	matrix4 translationMatOBB = glm::translate(m_mModelToWorld,OBBCentroid);
	m_pMeshOBB->SetModelMatrix(translationMatOBB * scaleMatOBB);

	matrix4 scaleMatAABB = glm::scale(matrix4(1.0f), scaleAABB);
	matrix4 translateMatAABB = glm::translate(AABBCentroid);
	m_pMeshAABB->SetModelMatrix(translateMatAABB * scaleMatAABB );
}

//Methods
void BoundingBoxClass::CalculateBoundingBox(String a_sInstance)
{
	//Get the vertices List to calculate the maximum and minimum
	std::vector<vector3> vVertices = m_pModelMngr->GetVertices(a_sInstance);
	int nVertices = static_cast<int>(vVertices.size());
	
	//If the size of the List is 0 it means we dont have any vertices in this Instance
	//which means there is an error somewhere
	if(nVertices == 0)
		return;

	//Go one by one on each component and realize which one is the smallest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the smallest one
		minOBB = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x < minOBB.x)
				minOBB.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y < minOBB.y)
				minOBB.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z < minOBB.z)
				minOBB.z = vVertices[nVertex].z;
		}
	}
	
	//Go one by one on each component and realize which one is the largest one
	if(nVertices > 0)
	{
		//We assume the first vertex is the largest one
		maxOBB = vVertices[0];
		//And iterate one by one
		for(int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			if(vVertices[nVertex].x > maxOBB.x)
				maxOBB.x = vVertices[nVertex].x;

			if(vVertices[nVertex].y > maxOBB.y)
				maxOBB.y = vVertices[nVertex].y;

			if(vVertices[nVertex].z > maxOBB.z)
				maxOBB.z = vVertices[nVertex].z;
		}
	}

	//The centroid is going to be the point that is halfway of the min to the max
	OBBCentroid = minOBB + maxOBB;
	OBBCentroid /= 2.0f;

	vector3 scaleVectorOBB;

	scaleVectorOBB.x = glm::distance(minOBB.x,maxOBB.x);
	scaleVectorOBB.y = glm::distance(minOBB.y,maxOBB.y);
	scaleVectorOBB.z = glm::distance(minOBB.z,maxOBB.z);

	scaleOBB = scaleVectorOBB;


	//Now calculate AABB

	if(nVertices == 0)
		return;

	std::vector<vector4> globalVerts = std::vector<vector4>(nVertices);

	for(int i = 0; i < nVertices; i++)
	{
		globalVerts[i] = vector4(vVertices[i].x, vVertices[i].y, vVertices[i].z, 1.0f);
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
	if(!GetAABBVisible() && !GetOBBVisible())
		return;

	if(GetOBBVisible())
	{
		vector3 vColor;

		if(a_vColor == MEWHITE)
			vColor = OBBColor;

		else //Otherwise use the argument
			vColor = a_vColor;

		//render the shape using a special case of the Shape Render method which uses the Color Shader.
		m_pMeshOBB->Render( matrix4(1.0f), vColor );
	}

	if(GetAABBVisible())
	{
		vector3 vColor;

		if(a_vColor == MEDEFAULT)
			vColor = AABBColor;

		else //Otherwise use the argument
			vColor = a_vColor;

		//render the shape using a special case of the Shape Render method which uses the Color Shader.
		m_pMeshAABB->Render( matrix4(1.0f), vColor );
	}
}