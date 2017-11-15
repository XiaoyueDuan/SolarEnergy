#pragma once

#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <QtGui/QOpenGLFunctions> 
#include <QtGui/QOpenGLFunctions_3_3_Core> 
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	string type;
	aiString path;
};

class Mesh{
public:
	/*  Mesh Data  */
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	/*  Functions  */
	// constructor
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures, QOpenGLFunctions_3_3_Core *glModelFuncs)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		glFuncs = glModelFuncs;
		// now that we have all the required data, set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void Draw(QOpenGLShaderProgram &shader)
	{
		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glFuncs->glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
											  // retrieve texture number (the N in diffuse_textureN)
			stringstream ss;
			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++; // transfer unsigned int to stream
			else if (name == "texture_specular")
				ss << specularNr++; // transfer unsigned int to stream
			else if (name == "texture_normal")
				ss << normalNr++; // transfer unsigned int to stream
			else if (name == "texture_height")
				ss << heightNr++; // transfer unsigned int to stream
			number = ss.str();
			// now set the sampler to the correct texture unit
			shader.setUniformValue((name + number).c_str(), i);
			// and finally bind the texture
			glFuncs->glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// draw mesh
		glFuncs->glBindVertexArray(VAO);
		glFuncs->glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glFuncs->glBindVertexArray(0);
		// always good practice to set everything back to defaults once configured.
		glFuncs->glActiveTexture(GL_TEXTURE0);
	}

private:
	/*  Render data  */
	unsigned int VBO, EBO;
	QOpenGLFunctions_3_3_Core* glFuncs = 0;  //opengl 的上下文信息
	/*  Functions    */
	// initializes all the buffer objects/arrays
	void setupMesh()
	{
		// create buffers/arrays
		glFuncs->glGenVertexArrays(1, &VAO);
		glFuncs->glGenBuffers(1, &VBO);
		glFuncs->glGenBuffers(1, &EBO);

		glFuncs->glBindVertexArray(VAO);
		// load data into vertex buffers
		glFuncs->glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glFuncs->glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glFuncs->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glFuncs->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glFuncs->glEnableVertexAttribArray(0);
		glFuncs->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		// vertex normals
		glFuncs->glEnableVertexAttribArray(1);
		glFuncs->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		// vertex texture coords
		glFuncs->glEnableVertexAttribArray(2);
		glFuncs->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		// vertex tangent
		glFuncs->glEnableVertexAttribArray(3);
		glFuncs->glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
		// vertex bitangent
		glFuncs->glEnableVertexAttribArray(4);
		glFuncs->glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
		glFuncs->glBindVertexArray(0);
	}
};