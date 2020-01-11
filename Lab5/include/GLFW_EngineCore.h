#pragma once
#include "IEngineCore.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include "CameraComponent.h"
#include <map>


class Model;
class Game;

class GLFW_EngineCore : public IEngineCore
{
public:
	~GLFW_EngineCore() override;

	bool initWindow(int width, int height, std::string windowName) override;
	bool runEngine(Game* game) override;
	void renderColouredBackground(float r, float g, float b) override;
	void renderText(std::string text, float x, float y, float scale, glm::vec3 colour) override;

	void setCamera(const CameraComponent* cam) override;
	void drawCube(const glm::mat4& modelMatrix) override;
	void drawModel(Model* model, const glm::mat4& modelMatrix) override;

	double getFrameDuration();

	void getMouseState(double& mouseX, double& mouseY, int& mouseButtons) override;


private:
	GLFWwindow* m_window;
	GLuint m_defaultShaderProgram;
	GLuint m_fontShaderProgram;

	static double m_mouseX;
	static double m_mouseY;
	static int m_mouseButtons;
	static int m_mouseAction;


	struct Character {
		GLuint textureID;  
		glm::ivec2 size;    
		glm::ivec2 bearing;  // Offset from baseline
		GLuint advance;    // Horizontal offset
	};

	std::map<GLchar, Character> Characters;
	GLuint font_VAO, font_VBO;

	static int m_screenWidth;
	static int m_screenHeight;
	static std::vector<bool> m_keyBuffer;
	static const int m_keyBufferSize = 400;

	static const int m_framesToMonitor = 64;
	std::vector<double> m_frameTimes;

	static void mouseMoveCallbackEvent(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallbackEvent(GLFWwindow* window, int button, int action, int mods);
	static void keyCallbackEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void windowResizeCallbackEvent(GLFWwindow* window, int width, int height);

	void loadShader(std::string vertexShaderFile, std::string fragmentShaderFile, GLuint& shaderProgram);
	void setDefaultShaders();
	void initCubeModel();
	void setupDefaultFont();



};

