#include "lib.h"

//variable definitions
	int STANDARD::width = 800;
	int STANDARD::height = 600;
	GLFWwindow *STANDARD::window = nullptr;
	int STANDARD::current_camera_id = 0;
	
	std::list<rend::Camera> STANDARD::cameras;

//scary camera shit
	int STANDARD::setupCamera() {
		rend::Camera c(glm::vec3(0.0f, 0.0f, 0.0f), (float)STANDARD::width / (float)STANDARD::height, 0.1, 100);
		c.perspective();
		c.lookat(glm::vec3(0.0f, 0.0f, 0.0f));
		STANDARD::cameras.push_back(c);
		return STANDARD::cameras.size() - 1;
	}
	void STANDARD::workCam(int k) {
		STANDARD::current_camera_id = k;
	}
	void STANDARD::loopCam() {
		STANDARD::get<rend::Camera>(STANDARD::cameras, STANDARD::current_camera_id).perspective();
	}

//model stuff
	rend::Model STANDARD::square(float position[2], float size[2], float r, float g, float b) {
		float tr[2] = { position[0], position[1] };
		float br[2] = { tr[0], tr[1] + size[1] };
		float tl[2] = { tr[0] + size[0], tr[1] };
		float bl[2] = { br[0] + size[0], br[1] };
		float vert[24] = {
			tr[0], tr[1], 0.0f, r, g, b,
			br[0], br[1], 0.0f, r, g, b,
			tl[0], tl[1], 0.0f, r, g, b,
			bl[0], bl[1], 0.0f, r, g, b,
		};
		unsigned int idx[] = {
			0,1,2,
			1,2,3
		};
		rend::Model ret("./res/shaders/2Dshader.vert", "./res/shaders/2Dshader.frag", vert, 24, idx, 6, true, true, 2, new int[] {3, 3});
		return ret;
	}

//general window stuff
	void STANDARD::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}
	void STANDARD::processInput(GLFWwindow *window) {
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
	void STANDARD::initializeWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		STANDARD::window = glfwCreateWindow(STANDARD::width, STANDARD::height, "GAME ENGINE RENDERER ATTEMPT 4", NULL, NULL);
		if(STANDARD::window == NULL) {
			std::cout << "Failed to create window" << std::endl;
			glfwTerminate();
			exit(-1);
		}
		glfwMakeContextCurrent(STANDARD::window);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(-1);
		}
		glViewport(0, 0, 800, 600);
	}
	bool STANDARD::closed() {
		return glfwWindowShouldClose(window);
	}
	void STANDARD::loopSetup() {
		if(glfwWindowShouldClose(window)) {
			
		}
		processInput(STANDARD::window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}
	void STANDARD::loopEnd() {
		glfwSwapBuffers(STANDARD::window);
		glfwPollEvents();
	}
	void STANDARD::terminate() {
		glfwTerminate();
	}

//input
	bool STANDARD::getKeyPressed(int key) {
		return glfwGetKey(STANDARD::window, key) == GLFW_PRESS;
	}
	bool STANDARD::getKeyReleased(int key) {
		return glfwGetKey(STANDARD::window, key) == GLFW_RELEASE;
	}

//data stuff
	template <typename T> T STANDARD::get(std::list<T> _l, int _i) {
		auto l_front = _l.begin();
		std::advance(l_front, _i);
		return *l_front;
	}
	
//math
	float STANDARD::wrap(float x, float min, float max) {
		if(x < min) {
			return STANDARD::wrap(max - (min - x), min, max);
		} else if(x > max) {
			return STANDARD::wrap(min + (max - x), min, max);
		}
		return x;
	}

//File stuff
	void STANDARD::write_to_file(std::string s, std::string path) {
		std::ofstream file(path);
		file << s;
		file.close();
	}
	void STANDARD::write_to_file(std::stringstream s, std::string path) {
		std::ofstream file(path);
		file << s.str();
		file.close();
	}
	std::string STANDARD::read_file(std::string path) {
		std::string s = "";
		std::ifstream file(path);
		std::stringstream ss("");
		while(getline(file, s)) {
			ss << s << "\n";
		}
		return ss.str();
	}

//string stuff
	void STANDARD::split_string(std::string input, std::list<std::string> &output, char tok, std::string option, const char *args, int num_args) {
		std::string s = input;
		std::string str = "";
		std::list<std::string> opts;
		char *ac = new char[num_args + 1] {' '};
		for(int i = 0; i < num_args; i++) {
			ac[i] = args[i];
		}
		if(option != "") {
			STANDARD::split_string(option, opts, ' ');
			for(std::list<std::string>::iterator it = opts.begin(); it != opts.end(); ++it) {
				std::cout << *it << "\n";
				if(*it == "remnl")
					s.erase(std::remove(s.begin(), s.end(), '\n'), s.cend());
				else if(*it == "rembracks") {
					s.erase(std::remove(s.begin(), s.end(), '('), s.cend());
					s.erase(std::remove(s.begin(), s.end(), ')'), s.cend());
				} else if(*it == "remtabs") {
					s.erase(std::remove(s.begin(), s.end(), '\t'), s.cend());
				} else if(*it == "replts") {
					STANDARD::sub_replace(s, "\t", " ");
				}
			}
		}
		std::stringstream ss(s);
		while(getline(ss, str, tok))
			output.push_back(str);
	}

	void STANDARD::sub_replace(std::string &input, std::string x, std::string y) {
		input = std::regex_replace(input, std::regex(x), yo);
		return input;
	}

	std::string STANDARD::list_as_string(std::list<std::string> input) {
		std::string s("");
		for(const auto &el : input)
			s += el;
		return s;
	}

	bool STANDARD::has_char(std::string &input, char x) {
		return input.find(x) != std::string::npos;
	}

//Console
	template <class T>
	void STANDARD::print(T s) {
		std::cout << s;
	}