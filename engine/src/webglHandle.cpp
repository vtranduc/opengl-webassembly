#include "../headers/webglHandle.h"

#define W 800
#define H 800

static EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context;

int WebGLHandle::initialize(char* canvasId, int clearColor) {
    cout << "hello world -----------------> initialize" << endl;


    setContextAttribute();
    context
        = emscripten_webgl_create_context(canvasId, &attrs);
    if (context < 0) {
        printf("failed to create webgl context %d\n", context);
        return 0;
    };
    EMSCRIPTEN_RESULT r = emscripten_webgl_make_context_current(context);
    if (r < 0) {
        printf("failed to make webgl current %d\n", r);
        return 0;
    }
    int purple = 0xff00ff;
    RGB rgb = hexToRGB(clearColor);
    // glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // test0();

    return 1;
};

int WebGLHandle::render() {
    cout << "rendering! ***********************" << endl;

    // float vertices[] = {
    //     -0.3f, 0.5f, 0.0f,	// left-top vertex position
	// 	0.3f, 0.5f, 0.0f,	// right-top vertex position
	// 	0.3f, -0.5f, 0.0f,	// botton-right vertex position

    //     // -0.5f, -0.5f, 0.0f,
    //     // 0.5f, -0.5f, 0.0f,
    //     // 0.0f,  0.5f, 0.0f
    // };

    // unsigned int VBO;
    // glGenBuffers(1, &VBO);

    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const char* vertexShaderSource =
        "precision highp float;"
        // "#version 330 core"
        // "precision highp\n"
        // "precision highp int\n"
        "\n"
        // "layout(location = 0) vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(1.0);\n"
        "}\n";
// https://learnopengl.com/Getting-started/Hello-Tr
    // cout << "show all" << endl << vertexShader15 << endl;

    unsigned int vertexShader15;
    vertexShader15 = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader15, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader15);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader15, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader15, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        cout << "oh it actually compiled?" << endl;
    }

    const char* fragmentShaderSource =
        "precision highp float;"
        // "#version 430\n"
        // "#version 150 core\n"
        // "precision highp float;\n"
        // "precision highp int;\n"
        "\n"
        // "out vec4 FragColor;\n"
        // "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    // unsigned int shaderProgram15 = createShader(vertexShader15, fragmentShader15);

    unsigned int fragmentShader15;
    fragmentShader15 = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShader15, 1, &fragmentShaderSource, NULL);

    glCompileShader(fragmentShader15);

    glGetShaderiv(fragmentShader15, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader15, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else {
        cout << "oh it actually compiled? FRAGMENT" << endl;
    }

    // --------------------------

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader15);
    glAttachShader(shaderProgram, fragmentShader15);

    // ---
    // glBindAttribLocation(programObject, 0, vertexPositionName);
    // ---

    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::P::Create program failed\n" << infoLog << std::endl;
    } else {
        cout << "so far so good" << endl;
    }

    // glUseProgram(shaderProgram);


    glDeleteShader(vertexShader15);
    glDeleteShader(fragmentShader15);

    // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// //glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_FALSE);
	// glViewport(0, 0, W, H);

    // --------------------------

    // float vertices100[] = {
	// 	// (positions)in NDC
	// 	0.0f, 0.5f, 0.0f,
	// -0.5f, -0.5f, 0.0f,
	// 0.5f, -0.5f, 0.0f
	// };

    // --- vertex buffer ---

    float vertices100[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO15;
    glGenBuffers(1, &VBO15);

    glBindBuffer(GL_ARRAY_BUFFER, VBO15);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices100), vertices100, GL_STATIC_DRAW);

    // ----------------------

    unsigned int VAO100;
    glGenVertexArrays(1, &VAO100);  

    // ----------------------

    for (int i = 0; i < 2000; i++) {
        cout << "loop iteration: --" << endl;

        glClearColor(0.13f, 0.13f, 0.13f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        // swapbuff

        // SDL_GL_SwapBuffers(context);

    //     glUseProgram(shaderProgram);

    //     glBindVertexArray(VAO100);

    //     glBindBuffer(GL_ARRAY_BUFFER, VBO15);

    //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices100), vertices100, GL_STATIC_DRAW);

    //     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices100);
    //     glEnableVertexAttribArray(0);
    //     glDrawArrays(GL_TRIANGLES, 0, 3);


        
    // // 2. copy our vertices array in a buffer for OpenGL to use
    //     // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //     // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //     glBindVertexArray(VAO100);
    //     glDrawArrays(GL_TRIANGLES, 0, 3);

        // SDL_GL_SwapBuffers();
    }


    return 0;

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // 0. copy our vertices array in a buffer for OpenGL to use
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // // 1. then set the vertex attributes pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);  
    // // 2. use our shader program when we want to render an object
    // glUseProgram(shaderProgram);
    // // 3. now draw the object 
    // // someOpenGLFunctionThatDrawsOurTriangle();  


    // // --------------------------

    // unsigned int VAO;
    // // glGenVertexArrays(1, &VAO);

    // glGenVertexArrays(1, &VAO);
    // // glBindVertexArray(VAO);

    // // 1. bind Vertex Array Object
    // glBindVertexArray(VAO);
    // // // 2. copy our vertices array in a buffer for OpenGL to use
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // // // 3. then set our vertex attributes pointers
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);

    // // glUseProgram(shaderProgram);
    // // glBindVertexArray(VAO);

    // // // ----------------

    // // glBindVertexArray(VAO);
    // // glDrawArrays(GL_TRIANGLES, 0, 3);

    // glUseProgram(shaderProgram);
    // glBindVertexArray(VAO);
    // glDrawArrays(GL_TRIANGLES, 0, 3);

    // // ------

    // glViewport(0, 0, W, H);

    // triangle vertex data 
	float vertices[] = {
		// (positions)in NDC
		-0.3f, 0.5f, 0.0f,	// left-top vertex position
		0.3f, 0.5f, 0.0f,	// right-top vertex position
		0.3f, -0.5f, 0.0f,	// botton-right vertex position

		//-0.3f, 0.5f, 0.0f,	// left-top vertex position
		//0.3f, -0.5f, 0.0f,	// botton-right vertex position
		//-0.3f, -0.5f, 0.0f,	// bottom-left vertex position
	};

	// generate VAO for store status of subsequent "vertex attribute" calls
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO); // bind VAO

	// generate VBO for allocating memory in GPU
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	// bind VBO with GL_ARRAY_BUFFER target
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// copy data from CPU to GPU
	//		use the currently bounded buffer to GL_ARRAY_BUFFER as container
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// tell OpenGL how it should interpret the vertex data(per
	// vertex attribute) using glVertexAttribPointer:
	// glVertexAttribPointer(index = [vertex attrib location remember the layout (location = n) keyword in vertex shader], 
	//						size = [is vec2 = 2, vec3 = 3, etc..],
	//						type = [GL_FLOAT, GL_BOOL, etc..], 
	//						normalize = [opengl should normalize the given data?],
	//						stride = [distance between each "position" ternas in VBO],
	//						start = [whare is the start index of "position"?];
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
	glEnableVertexAttribArray(0); // enable the vertex attribute at location 0

	// ======================================================================

	// start viewport
	// glViewport(0, 0, W, H);

    for (int i = 0; i < 1000; i++) {
        cout << "show iteration" << endl;

        glClearColor(0.2, 0.5, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    return 0;

    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================
    // ===================================================

//     unsigned int buffer;
//     glGenBuffers(1, &buffer);
//     glBindBuffer(GL_ARRAY_BUFFER, buffer);
//     // glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     string vertexShader =
//         "precision highp float;"
//         // "#version 300 es\n"
//         // "precision highp\n"
//         // "precision highp int\n"
//         "\n"
//         // "layout(location = 0) vec4 position;"
//         "\n"
//         "void main()\n"
//         "{\n"
//         "   gl_Position = vec4(1.0);\n"
//         "}\n";

//     string fragmentShader =
//         // "#version 460 core\n"

//         "precision highp float;"
//         // "#version 430\n"
//         // "#version 150 core\n"
//         // "precision highp float;\n"
//         // "precision highp int;\n"
//         "\n"
//         // "out vec4 FragColor;\n"
//         // "layout(location = 0) out vec4 color;"
//         "\n"
//         "void main()\n"
//         "{\n"
//         "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
//         "}\n";

//     unsigned int shaderProgram = createShader(vertexShader, fragmentShader);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);

//         // 0. copy our vertices array in a buffer for OpenGL to use
//     glBindBuffer(GL_ARRAY_BUFFER, buffer);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     // 1. then set the vertex attributes pointers
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);  
//     // 2. use our shader program when we want to render an object
//     glUseProgram(shaderProgram);
//     // 3. now draw the object 
//     // someOpenGLFunctionThatDrawsOurTriangle();   

//     // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//     // glClear(GL_COLOR_BUFFER_BIT);


//     // // int vertexColorLocation = glGetUniformLocation(shader, "gl_FragColor");
//     // glUseProgram(shader);
//     // // glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

//     // glDrawArrays(GL_TRIANGLES, 0, 3);

//     unsigned int VAO;
//     glGenVertexArrays(1, &VAO);
//     // glBindVertexArray(VAO);
// // // 2. copy our vertices array in a buffer for OpenGL to use
// //     glBindBuffer(GL_ARRAY_BUFFER, buffer);
// //     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//     // 3. then set our vertex attributes pointers
//     // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//     // glEnableVertexAttribArray(0);  

//     // glUseProgram(shaderProgram);
//     // glBindVertexArray(VAO);

//     // glUseProgram(shaderProgram);
//     // glBindVertexArray(VAO);
//     // glDrawArrays(GL_TRIANGLES, 0, 3);

//     return 1;
}

void WebGLHandle::test0() {
    cout << "ZERO" << endl;

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    string vertexShader =
        "precision highp float;"
        // "#version 300 es\n"
        // "precision highp\n"
        // "precision highp int\n"
        "\n"
        // "layout(location = 0) vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(1.0);\n"
        "}\n";

    string fragmentShader =
        "precision highp float;"
        // "#version 430\n"
        // "#version 150 core\n"
        // "precision highp float;\n"
        // "precision highp int;\n"
        "\n"
        // "out vec4 FragColor;\n"
        // "layout(location = 0) out vec4 color;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    // start a loop here

    glClear(GL_COLOR_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    
}

int WebGLHandle::setClearColor(int hex) {
    RGB rgb = hexToRGB(hex);
    glClearColor(rgb.r, rgb.g, rgb.b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    return 1;
}

void WebGLHandle::setContextAttribute() {
    attrs.explicitSwapControl = 0;
    attrs.depth = 1;
    attrs.stencil = 1;
    attrs.antialias = 1;
    attrs.majorVersion = 2;
    attrs.minorVersion = 0;
};

void WebGLHandle::test() {
    cout << "start of experiment" << endl;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // Generate buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copy user-defined data into the currently bound buffer

    // glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    

    const char *vertexShaderSource = "#version 300 es\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    // const char *vertexShaderSource = "#version 330 core\n void main() { gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }\0";

    // const char *vertexShaderSource =
    //     "#version 330 core\n"
    //     "layout (location = 0) in vec3 aPos;\n"
    //     "void main()\n"
    //     "{\n"
    //     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //     "}\0"
    // ;

    // Vertex shader object
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Attach and compile the shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // return;

    // Check whether shader code has been compiled successfully
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }

    // Fin
    cout << "=== fin ===" << endl;
}

void WebGLHandle::test2() {
    cout << "start of triangle attempt" << endl;

    // VAO - No need to know much
    // GLuint VertexArrayID;
    // glGenVertexArrays(1, &VertexArrayID);
    // glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glDisableVertexAttribArray(0);
}

// --------------------------

int WebGLHandle::test3(char* canvasId) {
    // return 1;


    // Create SDL window
    SDL_Window* mpWindow = 
        SDL_CreateWindow(canvasId, 
                         SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                         800, 800, 
                         SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE| SDL_WINDOW_SHOWN);
    Uint32 mWindowID = SDL_GetWindowID(mpWindow);

    // return 1;

    // Create OpenGLES 2 context on SDL window
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    // SDL_GL_SetSwapInterval(1);

    // // return 1;

    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

//     SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // return 1;

    // SDL_GLContext glc = SDL_GL_CreateContext(mpWindow);

    // Create OpenGLES 2 context on SDL window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GLContext glc = SDL_GL_CreateContext(mpWindow);

    // Set clear color to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // SDL_GL_CreateContext(mpWindow);

    // return 1;

    // context
    //     = emscripten_webgl_create_context(canvasId, &attrs);

    // // emscripten_webgl_make_context_current(context);

    // // Set clear color to black
    // glClearColor(1.0f, 0.0f, 0.2f, 1.0f);

    // setClearColor(0xff0000);

    cout << "hello world?" << endl;

    // initialize(canvasId, 0xff0000);

    return 1;

    // Initialize viewport
    // windowResizeEvent(mCamera.windowSize().width, mCamera.windowSize().height);


    // ????????????????????????????????
    // ????????????????????????????????

    cout << "+++ test 3 has started! +++" << endl;

    GLint shaderPan, shaderZoom, shaderAspect;
    const GLchar* vertexSource =
        // "uniform vec2 pan;                             \n"
        // "uniform float zoom;                           \n"
        // "uniform float aspect;                         \n"
        "attribute vec4 position;                      \n"
        // "varying vec3 color;                           \n"
        "void main()                                   \n"
        "{                                             \n"
        // "    gl_Position = vec4(position.xyz, 1.0);    \n"
        // "    gl_Position.xy += pan;                    \n"
        // "    gl_Position.xy *= zoom;                   \n"
        // "    gl_Position.y *= aspect;                  \n"
        // "    color = gl_Position.xyz + vec3(0.5);      \n"
        "    gl_Position = vec4(position, 1.0);        \n"
        "}                                             \n";

// Fragment/pixel shader
    const GLchar* fragmentSource =
        // "precision mediump float;                     \n"
        // "varying vec3 color;                          \n"
        "void main()                                  \n"
        "{                                            \n"
        "    gl_FragColor = vec4 ( 1.0, 0.0, 1.0, 1.0 );\n"
    "}\n";

    return 1;

    // Create and compile vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link vertex and fragment shader into shader program and use it
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Get shader variables and initialize them
    // shaderPan = glGetUniformLocation(shaderProgram, "pan");
    // shaderZoom = glGetUniformLocation(shaderProgram, "zoom");    
    // shaderAspect = glGetUniformLocation(shaderProgram, "aspect");
    // updateShader(eventHandler);

    // -----------------

    // Create vertex buffer object and copy vertex data into it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat vertices[] = 
    {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Specify the layout of the shader vertex data (positions only, 3 floats)
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    // now do main loop

    for (int i = 0; i < 2000; i++) {
        cout << "hello world loop" << endl;

        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(mpWindow);
    }

    return 1;
}

// --------------------------