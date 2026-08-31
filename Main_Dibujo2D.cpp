//

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 600;


int main() {
	glfwInit();
	//Verificaci�n de compatibilidad 
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Práctica 2; Dibujo de Pingüino en 2D", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, resize);
	
	//Verificaci�n de errores de creacion  ventana
	if (window== NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificaci�n de errores de inicializaci�n de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Imprimimos informacin de OpenGL del sistema
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;


	// Define las dimensiones del viewport
	//glViewport(0, 0, screenWidth, screenHeight);

    Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Cada vértice tiene: X, Y, Z,  R, G, B
	float vertices[] = {
		// --- VÉRTICES DE LA CABEZA GRIS (EXTERIOR) ---
		// 0: Punto superior central
		0.0f,   0.90f, 0.0f,    0.80f, 0.82f, 0.84f,
		// 1: Superior izquierdo
	   -0.28f,  0.82f, 0.0f,    0.80f, 0.82f, 0.84f,
	   // 2: Lateral izquierdo
	   -0.40f,  0.50f, 0.0f,    0.80f, 0.82f, 0.84f,
	   // 3: Punto medio de la frente
		0.0f,   0.45f, 0.0f,    0.85f, 0.87f, 0.89f,
		// 4: Superior derecho (gris ligeramente más oscuro para sombra)
		 0.28f,  0.82f, 0.0f,    0.68f, 0.70f, 0.72f,
		 // 5: Lateral derecho
		  0.40f,  0.50f, 0.0f,    0.68f, 0.70f, 0.72f,

		  // --- VÉRTICES DE LA CARA BLANCA (INTERIOR) ---
		  // 6: Esquina inferior izquierda cara
		  -0.20f,  0.22f, 0.0f,    0.95f, 0.95f, 0.95f,
		  // 7: Esquina inferior derecha cara
		   0.20f,  0.22f, 0.0f,    0.95f, 0.95f, 0.95f,
		   // 8: Punto inferior donde une el cuello
			0.0f,   0.20f, 0.0f,    0.95f, 0.95f, 0.95f,

			// --- VÉRTICES DEL PICO (AMARILLO) ---
			// 9: Pico superior izq
			-0.10f,  0.42f, 0.0f,    0.98f, 0.85f, 0.10f,
			// 10: Pico superior der
			 0.10f,  0.42f, 0.0f,    0.98f, 0.85f, 0.10f,
			 // 11: Punta del pico abajo
			  0.0f,   0.22f, 0.0f,    0.90f, 0.75f, 0.05f,

			  // --- VÉRTICES DEL PECHO ---
			  // 12: Centro del pecho (corregida la coma al final)
			   0.0f,  -0.10f, 0.0f,    0.98f, 0.82f, 0.76f,
			   // 13: Esquina izquierda del pecho (corregido el -0.25f)
			   -0.25f, -0.10f, 0.0f,    0.98f, 0.82f, 0.76f,
			   // 14: Esquina derecha del pecho
				0.25f, -0.10f, 0.0f,    0.92f, 0.75f, 0.68f,
				// 15: Esquina inferior izquierda del rombo central
				-0.25f, -0.45f, 0.0f,    0.98f, 0.82f, 0.76f,
				// 16: Esquina inferior derecha del rombo central
				 0.25f, -0.45f, 0.0f,    0.92f, 0.75f, 0.68f,
				 // 17: Punta inferior central del abdomen
	0.0f,  -0.80f, 0.0f,    0.95f, 0.78f, 0.70f,
	// --- VÉRTICES DE LOS COSTADOS DEL CUERPO (GRIS) ---
	// 18: Costado medio izquierdo
   -0.38f, -0.10f, 0.0f,    0.80f, 0.82f, 0.84f, // Gris claro
   // 19: Costado inferior izquierdo
  -0.32f, -0.65f, 0.0f,    0.80f, 0.82f, 0.84f,
  // 20: Costado medio derecho
  0.38f, -0.10f, 0.0f,    0.68f, 0.70f, 0.72f, // Gris sombra
  // 21: Costado inferior derecho
  0.32f, -0.65f, 0.0f,    0.68f, 0.70f, 0.72f,
  // --- VÉRTICES DE LAS ALAS Y BASE REDONDEADA ---
	// 22: Punta exterior ala izquierda (Celeste)
   -0.65f, -0.35f, 0.0f,    0.75f, 0.88f, 0.95f,
   // 23: Base redondeada baja izquierda (Gris)
  -0.45f, -0.75f, 0.0f,    0.80f, 0.82f, 0.84f,
  // 24: Punta exterior ala derecha (Celeste)
  0.65f, -0.35f, 0.0f,    0.75f, 0.88f, 0.95f,
  // 25: Base redondeada baja derecha (Gris sombra)
  0.45f, -0.75f, 0.0f,    0.68f, 0.70f, 0.72f,
  // 26: Unión superior ala izquierda
 -0.40f,  0.20f, 0.0f,    0.75f, 0.88f, 0.95f,
 // 27: Unión superior ala derecha
 0.40f,  0.20f, 0.0f,    0.75f, 0.88f, 0.95f
	};

	unsigned int indices[] = {
		// --- Capucha gris izquierda ---
		0, 1, 3,
		1, 2, 3,

		// --- Capucha gris derecha ---
		0, 3, 4,
		4, 3, 5,

		// --- Cara blanca izquierda ---
		3, 2, 6,
		3, 6, 8,

		// --- Cara blanca derecha ---
		3, 8, 7,
		3, 7, 5,

		// --- Pico amarillo ---
		9, 11, 10,

		// --- Primer triángulo del pecho ---
		// --- Pecho superior (Trapecio dividido en triángulos) ---
        8, 6, 13,
        8, 13, 12,
        8, 12, 14,
        8, 14, 7,
		// --- Pecho inferior (patrón de rombos/triángulos) ---
	12, 13, 15,
	12, 15, 17,
	12, 17, 16,
	12, 16, 14,
	// --- Costado izquierdo (Gris claro) ---
	2, 6, 18,
	6, 13, 18,
	13, 15, 18,
	15, 19, 18,
	15, 17, 19,

	// --- Costado derecho (Gris sombra) ---
	5, 20, 7,
	7, 20, 14,
	14, 20, 16,
	16, 20, 21,
	16, 21, 17,
	// --- Ala y costado exterior izquierdo ---
	2, 26, 18,
	26, 22, 18,
	18, 22, 23,
	18, 23, 19,

	// --- Ala y costado exterior derecho ---
	5, 20, 27,
	27, 20, 24,
	20, 25, 24,
	20, 21, 25
	};



	GLuint VBO, VAO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3*sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)


	
	while (!glfwWindowShouldClose(window))
	{
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// Draw our first triangle
        ourShader.Use();
        glBindVertexArray(VAO);


       // glPointSize(10);
        //glDrawArrays(GL_POINTS,0,4);
        
        //glDrawArrays(GL_LINES,0,4);
       // glDrawArrays(GL_LINE_LOOP,0,4);
        
        //glDrawArrays(GL_TRIANGLES,0,3);
        glDrawElements(GL_TRIANGLES, 105 ,GL_UNSIGNED_INT,0);

        
        
        glBindVertexArray(0);
    
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	glfwTerminate();
	return EXIT_SUCCESS;
}

void resize(GLFWwindow* window, int width, int height)
{
	// Set the Viewport to the size of the created window
	glViewport(0, 0, width, height);
	//glViewport(0, 0, screenWidth, screenHeight);
}