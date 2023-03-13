#pragma once

#include <iostream>
#include <list>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <regex>

#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "lib/model.h"
#include "lib/shaders.h"
#include "types.h"

namespace STANDARD {
	//variables
		extern int width;
		extern int height;
		extern GLFWwindow *window;
		extern std::list<rend::Camera> cameras;
		extern int current_camera_id;

	//data stuff
		template <typename T> T get(std::list<T> _l, int _i);

	//scary camera shit
		int setupCamera();
		void workCam(int k);
		void loopCam();

	//model stuff
		rend::Model square(float position[2], float size[2], float r=0, float g=0, float b=0);

	//basic window stuff
		void framebuffer_size_callback(GLFWwindow *window, int width, int height);
		void processInput(GLFWwindow *window);

		void initializeWindow();

		bool closed();
		void loopSetup();
		void loopEnd();
		void terminate();

	//input code
		bool getKeyPressed(int key);
		bool getKeyReleased(int key);

	//math
		float wrap(float x, float min, float max);

	//File stuff
		void write_to_file(std::string s, std::string path);
		void write_to_file(std::stringstream s, std::string path);
		std::string read_file(std::string path);

	//String stuff
		void split_string(std::string input, std::list<std::string> &output, char tok=' ', std::string option="", const char *args="", int num_args=0);
			/*
			* remnl - removes newlines from a string
			* rembracks - removes brackets
			* remtab - removes tabs
			*/
		void sub_replace(std::string &input, std::string x, std::string y);
		std::string list_as_string(std::list<std::string> input);
		bool has_char(std::string &input, char x);

	//Console stuff
		template <class T>
		void print(T s);
}