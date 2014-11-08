#include "BoundingSphereClass.h"
//The big 3
BoundingSphereClass::BoundingSphereClass(String a_sInstanceName)
{
	//Initialize variables
	m_pMesh = nullptr;
	m_v3Centroid = vector3(0.0f,0.0f,0.0f);
	m_v3Color = MEWHITE;
	m_mModelToWorld = matrix4(1.0f);
	m_bVisible = false;

	//Get the singleton instance of the Model Manager
	m_pModelMngr = ModelManagerClass::GetInstance();
	m_sInstance = a_sInstanceName;
	//Identify the instance from the list inside of the Model Manager
	int nInstance = m_pModelMngr->IdentifyInstance(m_sInstance);
	//If there is no instance with that name the Identify Instance will return -1
	//In which case there is nothing to do here so we just return without allocating memory
	if(nInstance == -1)
		return;

	//Construct a sphere with the dimensions of the instance, they will be allocated in the
	//corresponding member variables inside the method
	CalculateSphere(m_sInstance);
	//Get the Model to World matrix associated with the Instance
	m_mModelToWorld = m_pModelMngr->GetModelMatrix(m_sInstance);
	//If the size of the radius is 0 it means that there are no points or all of them are allocated
	//right at the origin, which will cause an issue, so we just return with no allocations
	if(m_fRadius == 0.0f)
		return;
	//Crete a new Sphere and initialize it using the member variables
	m_pMesh = new PrimitiveWireClass();
	m_pMesh->GenerateSphere(m_fRadius, 5, MEWHITE);
	m_pMesh->SetModelMatrix(glm::translate(m_mModelToWorld, m_v3Centroid));
}
BoundingSphereClass::BoundingSphereClass(BoundingSphereClass const& other)
{
	//Initialize the Sphere using other instance of it
	m_sInstance = other.m_sInstance;
	m_bVisible = other.m_bVisible;
	m_fRadius = other.m_fRadius;
	m_v3Centroid = other.m_v3Centroid;
	m_mModelToWorld = other.m_mModelToWorld;
	m_pModelMngr = other.m_pModelMngr;

	m_pMesh = new PrimitiveWireClass();
	m_pMesh->GenerateSphere(m_fRadius, 5, MEWHITE);
	m_pMesh->SetModelMatrix(glm::translate(m_mModelToWorld, m_v3Centroid));
}
BoundingSphereClass& BoundingSphereClass::operator=(BoundingSphereClass const& other)
{
	//If the incoming instance is the same as the current there is nothing to do here
	if(this != &other)
	{
		//Release the existing object
		Release();
		//Construct the object as in the copy constructor
		m_sInstance = other.m_sInstance;
		m_bVisible = other.m_bVisible;
		m_fRadius = other.m_fRadius;
		m_v3Centroid = other.m_v3Centroid;
		m_mModelToWorld = other.m_mModelToWorld;
		m_pModelMngr = other.m_pModelMngr;
		
		m_pMesh = new PrimitiveWireClass();
		m_pMesh->GenerateSphere(m_fRadius, 5, MEWHITE);
		m_pMesh->SetModelMatrix(glm::translate(m_mModelToWorld, m_v3Centroid));
	}
	return *this;
}
BoundingSphereClass::~BoundingSphereClass()
{
	//Destroying the object requires releasing all the allocated memory first
	Release();
}
void BoundingSphereClass::Release(void)
{
	//If the mesh exists release it
	if(m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}

	//The job of releasing the Model Manager Instance is going to be the work
	//of another method, we can't assume that this class is the last class
	//that uses this singleton, so we do not release it, we just make the pointer
	//point at nothing.
	m_pModelMngr = nullptr;
}
//Accessors
float BoundingSphereClass::GetRadius(void){ return m_fRadius; }
vector3 BoundingSphereClass::GetCentroid(void){ return m_v3Centroid; }
vector3 BoundingSphereClass::GetColor(void){ return m_v3Color; }
void BoundingSphereClass::SetColor(vector3 a_v3Color){ m_v3Color = a_v3Color; }
matrix4 BoundingSphereClass::GetModelMatrix(void){ return m_mModelToWorld; }
void BoundingSphereClass::SetModelMatrix(matrix4 a_mModelMatrix)
{
	//Sets the model matrix of the Sphere
	m_mModelToWorld = a_mModelMatrix;
	//Sets the Model Matrix of the actual Sphere shape
	//(which is translated m_v3Centrod away from the origin of our sphere)
	m_pMesh->SetModelMatrix(glm::translate(a_mModelMatrix, m_v3Centroid));
}
bool BoundingSphereClass::GetVisible(void) { return m_bVisible; }
void BoundingSphereClass::SetVisible(bool a_bVisible) { m_bVisible = a_bVisible; }
String BoundingSphereClass::GetInstanceName(void){ return m_sInstance; }
//Methods
void BoundingSphereClass::CalculateSphere(String a_sInstance)
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
	}

	//The centroid is going to be the point that is halfway of the min to the max
	m_v3Centroid = v3Minimum + v3Maximum;
	m_v3Centroid /= 2.0f;

	//Now we need to iterate through all the vertices to see which one is the furthest away from
	//the center point.
	for(int nVertex = 0; nVertex < nVertices; nVertex++)
	{
		float fDistance = glm::distance(m_v3Centroid, vVertices[nVertex]);
		if(fDistance > m_fRadius)
			m_fRadius = fDistance;
	}

	return;
}

void BoundingSphereClass::Render( vector3 a_vColor )
{
	//If the shape is visible render it
	//otherwise just return
	if(!m_bVisible)
		return;
	//Calculate the color we want the shape to be
	vector3 vColor;
	//if the argument was MEDEFAULT just use the color variable in our class
	if(a_vColor == MEDEFAULT)
		vColor = m_v3Color;
	else //Otherwise use the argument
		vColor = a_vColor;

	//render the shape using a special case of the Shape Render method which uses the Color Shader.
	m_pMesh->Render( matrix4(1.0f), vColor );
	
}