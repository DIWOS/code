#include "Model.h"
#include <windows.h>		// Header File For Windows
#pragma warning(disable : 4996)


Model::Model(char *filename)
{
	cout << "\nA model has been built!";

	numVertices = 0;
	numIndices = 0;

	FbxManager *manager = FbxManager::Create();

	FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
	manager->SetIOSettings(ioSettings);

	FbxImporter *importer = FbxImporter::Create(manager, "");
	importer->Initialize(filename, -1, manager->GetIOSettings());

	FbxScene *scene = FbxScene::Create(manager, "tempName");

	importer->Import(scene);
	importer->Destroy();

	FbxNode* rootNode = scene->GetRootNode();
	this->SetModelName(filename);
	if (rootNode) { this->GetFbxInfo(rootNode); }
	ShowDetails();
	RenderModel();
}

void Model::ShowDetails()
{
	cout << "\nName:" << Name;
	cout << "\nVertices Number:" << numVertices;
	cout << "\nIndices Number:" << numIndices;

}

char* Model::GetModelName()
{
	return Name;
}

void Model::SetModelName(char *x)
{
	strcpy(Name, x);
}

void Model::GetFbxInfo(FbxNode* Node)
{

	int numKids = Node->GetChildCount();
	FbxNode *childNode = 0;

	for (int i = 0; i<numKids; i++)
	{
		childNode = Node->GetChild(i);
		FbxMesh *mesh = childNode->GetMesh();

		if (mesh != NULL)
		{
			//================= Get Vertices ====================================
			int numVerts = mesh->GetControlPointsCount();

			for (int j = 0; j<numVerts; j++)
			{
				FbxVector4 vertex = mesh->GetControlPointAt(j);
				vertices[numVertices].x = (float)vertex.mData[0];
				vertices[numVertices].y = (float)vertex.mData[1];
				vertices[numVertices++].z = (float)vertex.mData[2];
				      cout<<"\n"<<vertices[numVertices-1].x<<" "<<vertices[numVertices-1].y<<" "<<vertices[numVertices-1].z;
			}

			
			//================= Get Indices ====================================
			numIndices = mesh->GetPolygonVertexCount();
			indices = new int[numIndices];
			indices = mesh->GetPolygonVertices();
			cout << numIndices;
			//================= Get Normals ====================================

			

			FbxGeometryElementNormal* normalEl = mesh->GetElementNormal();
			if (normalEl)
			{
				numNormals = mesh->GetPolygonCount() * 3;
				normals = new float[numNormals * 3];
				int vertexCounter = 0;
				for (int polyCounter = 0; polyCounter<mesh->GetPolygonCount(); polyCounter++)
				{
					for (int i = 0; i<3; i++)
					{
						FbxVector4 normal = normalEl->GetDirectArray().GetAt(vertexCounter);
						normals[vertexCounter * 3 + 0] = normal[0];
						normals[vertexCounter * 3 + 1] = normal[1];
						normals[vertexCounter * 3 + 2] = normal[2];
						cout << "\n" << normals[vertexCounter * 3 + 0] << " " << normals[vertexCounter * 3 + 1] << " " << normals[vertexCounter * 3 + 2];
						vertexCounter++;
					}
				}
			}
		}
		this->GetFbxInfo(childNode);
	}
}

void Model::RenderModel()
{
	int i, j;
	//glTranslatef(0.0, 0.0, -15.0);
	for (i = 0; i<numIndices - 3; i++)
	{
		glBegin(GL_TRIANGLES);
		glNormal3f(normals[i * 3 + 0], normals[i * 3 + 1], normals[i * 3 + 2]);
		for (j = i; j <= i + 2; j++)
			glVertex3f(vertices[indices[j]].x, vertices[indices[j]].y, vertices[indices[j]].z);
		cout << " test the render func coordinates " << vertices[indices[j]].x << " " << vertices[indices[j]].y << " " << vertices[indices[j]].z;
		glEnd();
	}
}

Model::~Model()
{
	cout << "\nA model has been destroyed!";
	glDisableClientState(GL_VERTEX_ARRAY);
}