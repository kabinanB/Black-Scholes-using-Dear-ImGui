#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include "black.h"
#include "functions.h"

// Forward declarations
void ShowMainMenu();
void ShowOptionPricing();
void ShowGreeksEvaluation();
void ShowSidebar();

// Global variables to store user input
double N = 100, K = 100, t = 1, S = 100, r = 0.05, q = 0.02, v = 0.2;
int optionChoice = 0, greekChoice = 0;
double C = 0, P = 0, D = 0, G = 0, VG = 0;

void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main() {
    // Initialize GLFW and OpenGL context
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Black-Scholes Calculator", NULL, NULL);
    if (!window) {
        glfwTerminate();
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize GLEW (on non-macOS systems)
#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
#endif

    // Check OpenGL version
    const GLubyte* glVersion = glGetString(GL_VERSION);
    if (glVersion) {
        printf("OpenGL Version: %s\n", glVersion);
    } else {
        fprintf(stderr, "Failed to retrieve OpenGL version\n");
    }

    // Initialize Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 120"); // Use GLSL 120 for OpenGL 2.1

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ShowMainMenu();
        ShowSidebar();

        if (optionChoice == 1 || optionChoice == 2) {
            ShowOptionPricing();
        } else if (greekChoice == 1 || greekChoice == 2 || greekChoice == 3) {
            ShowGreeksEvaluation();
        }

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void ShowMainMenu() {
    ImGui::Begin("Main Menu");
    if (ImGui::Button("1. Price an Option")) {
        optionChoice = 1;
        greekChoice = 0;
    }
    if (ImGui::Button("2. Evaluate the Greeks")) {
        greekChoice = 1;
        optionChoice = 0;
    }
    ImGui::End();
}

void ShowSidebar() {
    ImGui::Begin("Input Parameters");
    ImGui::InputDouble("Number of stocks", &N);
    ImGui::InputDouble("Strike Price", &K);
    ImGui::InputDouble("Time to maturity", &t);
    ImGui::InputDouble("Spot Price", &S);
    ImGui::InputDouble("Interest rate", &r);
    ImGui::InputDouble("Dividend", &q);
    ImGui::InputDouble("Volatility", &v);
    ImGui::End();
}

void ShowOptionPricing() {
    ImGui::Begin("Option Pricing");
    if (ImGui::Button("1. Calculate Call Option")) {
        double dp = log(S/K) + (r-q + (pow(v,2))/2);
        double dn = log(S/K) + (r-q - (pow(v,2))/2);
        C = N * ((S*exp(-q*t)*CumulativeNormalDistribution(dp)) - (K*exp(-r*t)*CumulativeNormalDistribution(dn)));
    }
    if (ImGui::Button("2. Calculate Put Option")) {
        double dp = log(S/K) + (r-q + (pow(v,2))/2);
        double dn = log(S/K) + (r-q - (pow(v,2))/2);
        P = N * ((-S*exp(-q*t)*CumulativeNormalDistribution(-dp)) + (K*exp(-r*t)*CumulativeNormalDistribution(-dn)));
    }
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "Call Option Price: %f", C);
    ImGui::TextColored(ImVec4(1, 0, 0, 1), "Put Option Price: %f", P);
    ImGui::End();
}

void ShowGreeksEvaluation() {
    ImGui::Begin("Greeks Evaluation");
    if (ImGui::Button("1. Calculate Delta")) {
        double dp = log(S/K) + (r-q + (pow(v,2))/2);
        D = N * exp(-q*t) * CumulativeNormalDistribution(dp);
    }
    if (ImGui::Button("2. Calculate Gamma")) {
        double dp = log(S/K) + (r-q + (pow(v,2))/2);
        G = N * exp(-q*t) * (p(dp) / (v * S * sqrt(t)));
    }
    if (ImGui::Button("3. Calculate Vega")) {
        double dp = log(S/K) + (r-q + (pow(v,2))/2);
        VG = N * exp(-q*t) * sqrt(t) * p(dp);
    }
    ImGui::TextColored(ImVec4(0.5, 0.8, 1, 1), "Delta: %f", D);
    ImGui::TextColored(ImVec4(0, 0, 1, 1), "Gamma: %f", G);
    ImGui::TextColored(ImVec4(0.5, 0, 1, 1), "Vega: %f", VG);
    ImGui::End();
}