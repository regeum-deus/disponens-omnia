#include "model.h"

rend::Model::Model() {
}

rend::Model::Model(std::string vss, std::string fss, float *verts, float vertex_count, unsigned int *indices, float index_count, bool vp, bool fp) {
	if(vp) {
		this->vertexpath = vss;
	}
	if(fp) {
		this->fragmentpath = fss;
	}

	this->vertices = verts; this->vertex_count = vertex_count;
	this->indices = indices; this->index_count = index_count;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_count, this->vertices, GL_STATIC_DRAW);
		
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_count * sizeof(unsigned int), this->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

rend::Model::Model(std::string vss, std::string fss, float *verts, float vertex_count, unsigned int *indices, float index_count, bool vp, bool fp, int vaa, int *vas) {
	this->VAO = 0;
	this->VBO = 0;
	this->EBO = 0;

	if(vp) {
		this->vertexpath = vss;
	}
	if(fp) {
		this->fragmentpath = fss;
	}

	this->vertices = verts; this->vertex_count = vertex_count;
	this->indices = indices; this->index_count = index_count;
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_count, this->vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->index_count * sizeof(unsigned int), this->indices, GL_STATIC_DRAW);

	int vatotal = 0;
	for(int i = 0; i < vaa; i++) {
		vatotal += vas[i] * sizeof(float);
	}

	int stride = vatotal;
	for(int i = 0; i < vaa; i++) {
		int space = 0;
		if(i != 0) {
			for(int j = 0; j < i; j++) {
				space += vas[j] * sizeof(float);
			}
		}

		glVertexAttribPointer(i, vas[i], GL_FLOAT, GL_FALSE, stride, (void*)(intptr_t)(space));
		glEnableVertexAttribArray(i);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void rend::Model::render() {
	this->shader.use();

	if(this->textured) {
		for(int i = 0; i < this->texture_amount; i++) {
			glActiveTexture(this->textures[i].textureUnit);
			glBindTexture(GL_TEXTURE_2D, this->textures[i].ID);
		}
		if(this->texture_amount == 0) {
			this->shader.setInt("texture0", 0);
		} else {
			for(int i = 0; i < this->texture_amount; i++) {
				std::stringstream s;
				s << "texture" << i;
				this->shader.setInt(s.str(), i);
			}
		}
	}

	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void rend::Model::render(rend::Camera c) {
	glm::mat4 mvp = c.projectionMatrix * c.ViewMatrix * modelspace;
	
	this->shader.use();
	GLuint MatrixID = glGetUniformLocation(this->shader.ID, "mvp");
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
	
	if(this->textured) {
		for(int i = 0; i < this->texture_amount; i++) {
			glActiveTexture(this->textures[i].textureUnit);
			glBindTexture(GL_TEXTURE_2D, this->textures[i].ID);
		}
		if(this->texture_amount == 0) {
			this->shader.setInt("texture0", 0);
		} else {
			for(int i = 0; i < this->texture_amount; i++) {
				std::stringstream s;
				s << "texture" << i;
				this->shader.setInt(s.str(), i);
			}
		}
	}
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->index_count, GL_UNSIGNED_INT, (void*)0);
	glBindVertexArray(0);
}

void rend::Model::shaders() {
	this->shader = rend::Shader(this->vertexpath.c_str(), this->fragmentpath.c_str());
}

void rend::Model::programUsage(void (*_usage)(int)) {
	_usage(this->shader.ID);
}

void rend::Model::texture_init(std::string *image_path, int amount) {
	this->textures = new rend::Texture[amount];
	for(int i = 0; i < amount; i++) {
		this->textures[i] = rend::Texture(image_path[i], i);
	}
	this->texture_amount = amount;
	this->textured = true;
}

void rend::Model::model_translate(glm::vec3 vec) {
	this->position += vec;
	this->modelspace = glm::translate(glm::mat4(1.0f), this->position);
}