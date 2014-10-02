#pragma warning(disable : 4996)
#include "Model.h"

bool load_model_state = false;

Model::Model(char *filename)
{
	if (!load_model_state)
	{
		cout << "\nA model has been built!";

		numVertices = 0;
		numIndices = 0;

		//load manager
		FbxManager *manager = FbxManager::Create();

		//load IO from manager
		FbxIOSettings *ioSettings = FbxIOSettings::Create(manager, IOSROOT);
		manager->SetIOSettings(ioSettings);

		//Load importer drom manager
		FbxImporter *importer = FbxImporter::Create(manager, "");
		importer->Initialize(filename, -1, manager->GetIOSettings());

		//Create scene from manager
		FbxScene *scene = FbxScene::Create(manager, "tempName");
		importer->Import(scene);
		importer->Destroy();

		//Call func for load and calculate model
		FbxNode* rootNode = scene->GetRootNode();
		this->SetModelName(filename);
		if (rootNode) { this->GetFbxInfo(rootNode); }

		for (int num = 0; num <26; num++)
		{
			cout << "\n vertice " << num << " " << vertices[num].x << " " << vertices[num].y << " " << vertices[num].z;
		}

		ShowDetails();
		load_model_state = true;
	}

	createVertex();

}

//Destructor - delete
Model::~Model()
{
	//cout << "\nA model has been destroyed!";
	//glDisableClientState(GL_VERTEX_ARRAY);
}


//Write in wind inf of file
void Model::ShowDetails()
{
	cout << "\n\nName: " << Name;
	cout << "\nVertices Number: " << numVertices;
	cout << "\nIndices Number: " << numIndices;

}

char* Model::GetModelName()
{
	return Name;
}

void Model::SetModelName(char *x)
{
	strcpy(Name, x);
}


//Load vjdel and get points
void Model::GetFbxInfo(FbxNode* Node)
{
	//get child node
	int numKids = Node->GetChildCount();
	FbxNode *childNode = 0;

	glInterleavedArrays(GL_T2F_V3F, sizeof(indices), vertices);

	//for count child nodes
	for (int i = 0; i<numKids; i++)
	{
		childNode = Node->GetChild(i);
		FbxMesh *mesh = childNode->GetMesh();
		
		//if count chil mesh != 0
		if (mesh != NULL)
		{
			//================= Get Vertices ====================================
			int numVerts = mesh->GetControlPointsCount();

			//load for struct model vertex coordinate
			for (int j = 0; j<numVerts; j++)
			{
				FbxVector4 vert = mesh->GetControlPointAt(j);
				vertices[numVertices].x = (float)vert.mData[0];
				vertices[numVertices].y = (float)vert.mData[1];
				vertices[numVertices++].z = (float)vert.mData[2];
				//cout<<"\n"<<vertices[numVertices-1].x<<" "<<vertices[numVertices-1].y<<" "<<vertices[numVertices-1].z;
			}

			//================= Get Indices ====================================

				indices = new GLsizei[numIndices];
				indices = mesh->GetPolygonVertices();
						
			//================= Get Normals ====================================
			FbxGeometryElementNormal* normalEl = mesh->GetElementNormal();
			if (normalEl)
			{
				//count normals
				numNormals = mesh->GetPolygonCount() * 3;
				normals = new float[numNormals * 3];
				int vertexCounter = 0;
				//load normals of model
				for (int polyCounter = 0; polyCounter<mesh->GetPolygonCount(); polyCounter++)
				{
					for (int i = 0; i<3; i++)
					{
						FbxVector4 normal = normalEl->GetDirectArray().GetAt(vertexCounter);
						normals[vertexCounter * 3 + 0] = normal[0];
						normals[vertexCounter * 3 + 1] = normal[1];
						normals[vertexCounter * 3 + 2] = normal[2];
						//cout << "\n" << normals[vertexCounter * 3 + 0] << " " << normals[vertexCounter * 3 + 1] << " " << normals[vertexCounter * 3 + 2];
						vertexCounter++;
						if (vertices != NULL && normals != NULL);
					}
				}
			}
		}
		this->GetFbxInfo(childNode);

	}
}


void Model::createVertex()
{
	glVertexPointer(26, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glDrawArrays(GL_POLYGON, 0, 9);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

}
