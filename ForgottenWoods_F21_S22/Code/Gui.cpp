//------------------------------------------------------------------------------
/*!
\file	Gui.cpp
\author	Zak (zak.s), https://github.com/ocornut/imgui
\par	Copyright © 2021 DigiPen (USA) Corporation.
\brief
*/
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// Includes:
//------------------------------------------------------------------------------
#include "stdafx.h"
#include "Gui.h"
#include "ComponentCollider.h"
#include "ComponentGraphics.h"
#include "ComponentPhysics.h"
#include "ComponentTransform.h"
#include "Animation.h"
#include "GLFW/glfw3.h"
#include "imgui.h"
#include "implot.h"
#include "Level1.h"
#include "imconfig.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GameStateManager.h"
#include "GameObjectManager.h"
#include <stdio.h>
#include <filesystem>
#include <random>

using namespace ImGui;
//------------------------------------------------------------------------------
// Private Constants:
//------------------------------------------------------------------------------
#define PI 3.1415962
//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
static std::vector<std::string> artFiles;
static std::string path = "/Art" ;
static ImVec4 clearColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static float barTest[10] = { 1, 2, 3, 4, 4, 3, 4, 5, 9, 2 };
static float ScatterTestX[10] = { 1, 4, 5, 8, 3, 0, 8, 6, 4 };
static float ScatterTestY[10] = {0, 1,2,3,4,5,6,7,8,9};
static const char* PieChartTest[3] = { "One", "Two", "Three" };
static float FrameRateArray[100];
static int FrameRateCounter = 0;
static int index = -1;
static float PieValues[3] = { 25, 25, 50 };
static ImVec4 clearColor2 = ImVec4(0.85f, 0.3f, 0.1f, 1.00f);
static bool showWindow = false;
static float FrameRateScale = 1.319f;
static float GraphsScale = 1.0f;
static float DebugScale = 1.4f;
static float GraphicScale = 1.4f;
static float TestScale = 1.0f;
static float AnimationScale = 1.4f;
static float StatsScale = 1.4f;
bool showGraphs = false;
ImVec2 screenSize;
static ComponentColliderPtr tempCol;
static ComponentPhysicsPtr tempPhys;
static ComponentTransformPtr tempTrans;
static ComponentGraphicsPtr tempGraph;
static ComponentSpritePtr tempSprite;
static Animation* tempAnim;
//static const char* imageOneFilename = "Art/KylieSullivan CharacterBG Test 02.jpg";
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/***********************************************
 \brief     ImGui Init function, used in the init of any gamestate where ImGui is used
 \@param window - the current window
 ***********************************************/
void GuiInitialize(GLFWwindow* window)
{
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	/*for (const auto& entry : std::filesystem::directory_iterator(path))
	{
		artFiles.push_back(path.c_str());
	}*/
}
/***********************************************
 \brief     ImGui Init function for exit gamestate
 \@param window - the current window
 ***********************************************/
void ExitInit(GLFWwindow* window)
{
	CreateContext();
	ImGuiIO& exitIO = GetIO(); (void)exitIO;
	StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}
// dt is the change in time(sec) since the last game loop
/***********************************************
 \brief     ImGui Update function, called in gameplay loop
 \@param window - the current window
 \@param toggle - toggle for Gui display (true = Gui displays, false = no display)
 \@param objects - list of game objects to be read through in data display
 \@param pStats - individual player stats to be shown in data display
 ***********************************************/
void GuiUpdate(GLFWwindow* window, bool toggle, GameObjectManager* objects)
{
	if (toggle)
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (showWindow)
		{
			ImGui::ShowDemoWindow(&showWindow);
		}
		static int counter1 = 0, counter2 = 0;
		char WindowTitle[255] = "Forgotten Woods";
		ImGui::Begin(WindowTitle);
		ImGui::SetWindowFontScale(TestScale);
		ImGui::SliderFloat("Font Scale", &TestScale, 0.0f, 4.0f);
		ImGui::Checkbox("Demo Window", &showWindow);
		ImGui::SameLine(550.0f);
		if (ImGui::Button("Exit Game"))
		{
			GameStateManagerSetNextState(GameStates::GsQuit);
		}
		//if (ImGui::ColorButton("Increase", clearColor))
		{
			counter1++;
		}//
		//ImGui::SameLine();
		//ImGui::Text("add = %d", counter1);         // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("Color 1", (float*)&clearColor);
		ImGui::ColorEdit3("Color 2", (float*)&clearColor2); // Edit 3 floats representing a color
		/*float frameRates[10];
		for (int i = 0; i < 10; i++)
		{
			frameRates[i] = (ImGui::GetIO().Framerate);
		}*/
		//ImGui::PlotLines("Frame Rate", frameRates ,10, 0);
		if (ImGui::ColorButton("Increase", clearColor))
		{
			counter1++;
		}
		if (ImGui::ColorButton("Button 2", clearColor2))
		{
			counter2--;
		}
		//ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_WindowBg, clearColor2);
		//ImGui::Text("subtract = %d", counter2);
		ImGui::Text("Zoom In/Out");
		//ImGui::NewLine();
		if (ImGui::ArrowButton("Up", ImGuiDir_Up))
		{
			TestScale += 0.25f;
		}
		if (ImGui::ArrowButton("Down", ImGuiDir_Down))
		{
			TestScale -= 0.25f;
		}
		ImGui::End();
		//ImGui::EndFrame();

		//New Window




		/*ImGui::Begin("Game Objects");
		ImGui::SetWindowFontScale(DebugScale);
		ImGui::SliderFloat("Font Scale", &DebugScale, 0.0f, 4.0f);
		GameObjectMenu(objects, &index);
		if (index >= 0)
		{
			ImGui::Text(objects->list[index]->GetName());
			ImGui::NewLine();
			GameObjectDisplay(objects, index);
		}
		ImGui::End();
		
		Begin("Game Object Graphics and Sprite Data");
		SetWindowFontScale(GraphicScale);
		ImGui::SliderFloat("Font Scale", &GraphicScale, 0.0f, 4.0f);
		GameObjectMenu(objects, &index);
		if (index >= 0)
		{
			ImGui::Text(objects->list[index]->GetName());
			ImGui::NewLine();
			GraphicsDisplay(objects, index);
		}
		ImGui::End();
		*/

		/*Begin("Game Object Animation Data");
		SetWindowFontScale(AnimationScale);
		ImGui::SliderFloat("Font Scale", &AnimationScale, 0.0f, 4.0f);
		GameObjectMenu(objects, &index);
		if (index >= 0)
		{
			ImGui::Text(objects->list[index]->GetName());
			ImGui::NewLine();
			AnimationDisplay(objects, index);
		}
		ImGui::End();*/

		/*Begin("Player Stats");
		SetWindowFontScale(StatsScale);
		ImGui::SliderFloat("Font Scale", &StatsScale, 0.0f, 4.0f);
		Text("Player Gameplay Stats");
		NewLine();
		//Text("Number of Jumps: %i", pStats->numJumps);
		//Text("Number of Double Jumps: %i", pStats->numDoubleJumps);
		NewLine();
		//Text("Number of Deaths: %i", pStats->numDeaths);
		End();*/

		if (showGraphs)
		{
			ImGui::Begin("Graphs Test");
		ImGui::SetWindowFontScale(GraphsScale);
		ImGui::SliderFloat("Font Scale", &GraphsScale, 0.0f, 4.0f);
		BarGraph("Bar Test", barTest, 10);
		if (ImGui::Button("Add 1 Test"))
		{
			for (int i = 0; i < 10; i++)
			{
				barTest[i]++;
			}
		}
		if (ImGui::Button("Subtract 1 Test"))
		{
			for (int i = 0; i < 10; i++)
			{
				if (barTest[i] > 0)
				{
					barTest[i]--;
				}
			}
		}
		Scatter("Scatter Test", ScatterTestX, ScatterTestY, 10);
		if (ImGui::Button("Randomize X Value"))
		{
			for (int i = 0; i < 10; i++)
			{
				ScatterTestX[i] = rand() % 10;
			}
		}
		if (ImGui::Button("Randomize Y Value"))
		{
			for (int i = 0; i < 10; i++)
			{
				ScatterTestY[i] = rand() % 10;
			}
		}/*
		PieChart(PieChartTest, PieValues, 3, "%.1f");
		if (ImGui::Button("Add to 1, Take from 2"))
		{
			PieValues[0] += 5;
			PieValues[1] -= 5;
		}
		if (ImGui::Button("Add to 2, Take from 3"))
		{
			PieValues[1] += 5;
			PieValues[2] -= 5;
		}
		*/
		ImGui::End();
	}
		ImGui::Begin("Frame Rate");
		ImGui::SetWindowFontScale(FrameRateScale);
		ImGui::SliderFloat("Font Scale", &FrameRateScale, 0.0f, 4.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		NewLine();
		screenSize = GetWindowSize();
		Text("Window Size: %f x %f", screenSize.x, screenSize.y);
		//FrameRateArray[FrameRateCounter] = ImGui::GetIO().Framerate;
		//LineGraph("Frame Rate Test", FrameRateArray, 100);
		if (FrameRateCounter == 100)
		{
			FrameRateCounter = 0;
		}FrameRateCounter++;
		ImGui::End();
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		//glClearColor(cleaColor.x * clearColor.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		//ImGui::PopStyleColor(1);
		// set as unreferenced parameter until used
	}
}
/***********************************************
 \brief     Update loop for Exit gamestate Gui (less functionality than gameplay Gui)
 \@param window - the current window
 ***********************************************/
void ExitUpdate(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	char WindowTitle[255] = " ";
	ImGui::Begin(WindowTitle);
	SetWindowFontScale(3.0f);
	if (ImGui::Button("Exit Game"))
	{
		GameStateManagerSetNextState(GameStates::GsQuit);
	}
	End();
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
/***********************************************
 \brief     Creates game objects in a dropdown list
 \@param objects - the game objects to be displayed
 \@param index - the selected object's index
 ***********************************************/
void GameObjectMenu(GameObjectManager* objects, int* index)
{
	static const char* currentItem = NULL;
	ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;
	ImGuiStyle& style = ImGui::GetStyle();
	float width = ImGui::CalcItemWidth();
	float spacing = style.ItemInnerSpacing.x;
	float buttonHeight = ImGui::GetFrameHeight();
	ImGui::PushItemWidth(width - spacing * 2.0f - buttonHeight * 2.0f);
	if (ImGui::BeginCombo("##test combo", currentItem, ImGuiComboFlags_NoArrowButton))
	{
		for (int i = 0; i < objects->listCount; i++)
		{
			bool isSelected = (currentItem == objects->list[i]->GetName());
			if (ImGui::Selectable(objects->list[i]->GetName(), isSelected))
			{
				currentItem = objects->list[i]->GetName();
				*index = i;
			}
			if (isSelected)
			{
				ImGui::SetItemDefaultFocus();
			}

		}
		ImGui::EndCombo();

	}
	ImGui::PopItemWidth();
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##r", ImGuiDir_Up))
	{
		
	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##r", ImGuiDir_Down))
	{
	
	}
	ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
	ImGui::Text("Objects");
}
/***********************************************
 \brief     Displays game objects in a dropdown list
 \@param objects - the game objects to be displayed
 \@param index - the selected object's index
 ***********************************************/
void GameObjectDisplay(GameObjectManager* objects, int index)
{
	tempCol = objects->list[index]->GetCollider();
	tempPhys = objects->list[index]->GetPhysics();
	tempTrans = objects->list[index]->GetTransform();
	const glm::mat3x3* matrix = tempTrans->GetTransformMatrix();
	Text("General Object Data");
	Text("Is Alive: %i" , objects->list[index]->CheckDestroyed());
	if (tempCol)
	{
		ImGui::Text("Collider Data");
		ImGui::Text("Collider Type: %s", tempCol->GetType());
		ImGui::Text("Collision Box Data");
		ImGui::Text("X Size: %f | ", tempCol->GetBoxDataTransformed().XSize);
		ImGui::SameLine();
		ImGui::Text("Y Size: %f", tempCol->GetBoxDataTransformed().YSize);
		ImGui::Text("Collider Wall Data");
		if (tempCol->GetWallDataTransformed().Orientation)
		{
			ImGui::Text("Orientation: %c", tempCol->GetWallDataTransformed().Orientation);
		}
		ImGui::Text("Length: %f", tempCol->GetWallDataTransformed().Length);
		NewLine();
	}
	if (tempPhys)
	{
		ImGui::NewLine();
		ImGui::Text("Physics Data");
		ImGui::Text("Old Translation");
		ImGui::Text("X Value: %f | ", tempPhys->GetOldTranslation()->x);
		SameLine();
		Text("Y Value: %f", tempPhys->GetOldTranslation()->y);
		Text("Homogeneous Value: %f", tempPhys->GetOldTranslation()->z);
		Text("Velocity");
		Text("X Value: %f | ", tempPhys->GetVelocity()->x);
		SameLine();
		Text("Y Value: %f", tempPhys->GetVelocity()->y);
		Text("Homogenous Value: %i", tempPhys->GetVelocity()->z);
		Text("Acceleration");
		Text("X Value: %f | ", tempPhys->GetAcceleration()->x);
		SameLine();
		Text("Y Value: %f", tempPhys->GetAcceleration()->y);
		Text("Homegeneous Value: %i", tempPhys->GetAcceleration()->z);
		Text("Rotational Velocity: %f", tempPhys->GetRotationalVelocity());
		Text("Mass", tempPhys->GetMass());
		NewLine();
	}
	if (tempTrans)
	{
		Text("Transform Data");
		Text("Position");
		Text("X Value: %f | ", tempTrans->GetPosition()->x);
		SameLine();
		Text("Y Value: %f", tempTrans->GetPosition()->y);
		Text("Homogeneous Value: %i", tempTrans->GetPosition()->z);
		Text("Scale");
		Text("X Value: %f | ", tempTrans->GetScale()->x);
		SameLine();
		Text("Y Value: %f", tempTrans->GetScale()->y);
		Text("Homogeneous Value: %i", tempTrans->GetScale()->z);
		Text("Rotation: %f", tempTrans->GetRotation());
		Text("Transformation Matrix");
		Text("%f | %f | %f", matrix[0][0], matrix [0][1], matrix[0][2]);
		Text("%f | %f | %f", matrix[1][0], matrix[1][1], matrix[1][2]);
		Text("%f | %f | %f", matrix[2][1], matrix[2][1], matrix[2][2]);
	}
}
/***********************************************
 \brief     Displays graphics data in a dropdown list
 \@param objects - the graphics to be displayed
 \@param index - the selected object's index
 ***********************************************/
void GraphicsDisplay(GameObjectManager* objects, int index)
{
	tempGraph = objects->list[index]->GetGraphic();
	tempSprite = objects->list[index]->GetSprite();
	Text("Game Object Graphic and Sprite Data");
	if (tempGraph)
	{
		Text("Graphic Component");
		Text("Vertices");
		Text("VAO: %f", tempGraph->get_VAO());
		Text("VBO: %f", tempGraph->get_VBO());
		Text("EBO: %f", tempGraph->get_EBO());
		NewLine();
		Text("Texture Data");
		Text("Height: %f", tempGraph->get_height());
		Text("Width: %f", tempGraph->get_width());
		Text("X Position: %f", tempGraph->getPosition().x);
		Text("Y Position: %f", tempGraph->getPosition().y);
	}
	if (tempSprite)
	{
		Text("Graphics Sprite");
		Text("U Value: %f", tempSprite->GetU());
		Text("V Value: %f", tempSprite->GetV());
		Text("Alpha Value: %f", tempSprite->GetAlpha());
		Text("Frame Index: %f", tempSprite->GetFrameIndex());
	}
}
/***********************************************
 \brief     Displays Animation data in a dropdown list
 \@param objects - the game object's animations to be displayed
 \@param index - the selected object's index
 ***********************************************/
void AnimationDisplay(GameObjectManager* objects, int index)
{
	tempAnim = objects->list[index]->GetAnimation();
	Text("Game Object Animation Data");
	if (tempAnim)
	{
		Text("Index: %f", tempAnim->GetIndex());
		Text("Count: %f", tempAnim->GetCount());
		Text("Delay: %f", tempAnim->GetDelay());
		Text("Duration: %f", tempAnim->GetDuration());
		if (tempAnim->GetRunning())
		{
			Text("Animation is running");
		}
		else
		{
			Text("Animation is not running");
		}
		if (tempAnim->GetLooping())
		{
			Text("Animation is looping");
		}
		else
		{
			Text("Animation is not looping");
		}
		if (tempAnim->GetDone())
		{
			Text("Animation is done");
		}
		else
		{
			Text("Animation is not done");
		}
	}
	else
	{
		Text("Selected Game Object has no Animation");
	}
}
/***********************************************
 \brief     Displays textures in a dropdown list (Work In Progress)
 ***********************************************/
void ImageMenu()
{
	static int currentItem = NULL;
	ImGuiComboFlags flags = ImGuiComboFlags_NoArrowButton;
	ImGuiStyle& style = ImGui::GetStyle();
	float width = ImGui::CalcItemWidth();
	float spacing = style.ItemInnerSpacing.x;
	float buttonHeight = ImGui::GetFrameHeight();
	ImGui::PushItemWidth(width - spacing * 2.0f - buttonHeight * 2.0f);
	if (ImGui::BeginCombo("##test combo", "Image Files", ImGuiComboFlags_NoArrowButton))
	{
		for (int i = 0; i < artFiles.size(); i++)
		{
				bool isSelected = (currentItem == i);
			//	if (ImGui::Selectable(artFiles[i], isSelected))
				{

				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
		}
		ImGui::EndCombo();

	}
	ImGui::PopItemWidth();
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##r", ImGuiDir_Up))
	{

	}
	ImGui::SameLine(0.0f, spacing);
	if (ImGui::ArrowButton("##r", ImGuiDir_Down))
	{

	}
	ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
}
/***********************************************
 \brief     Creates Bar Chart data display
 \@param name - name of the chart
 \@param data - data to display
 \@param numElements - number of elements in the data array
 ***********************************************/
void BarGraph(const char * name, float* data, float numElements)
{
	if (ImPlot::BeginPlot(name))
	{
		ImPlot::PlotBars(name, data, numElements);
	}
	ImPlot::EndPlot();
}
/***********************************************
 \brief     Creates Line Graph data display
 \@param name - name of the chart
 \@param data - data to display
 \@param numElements - max number in data display
 ***********************************************/
void LineGraph(const char* name, float* data, float max)
{
	if (ImPlot::BeginPlot(name))
	{
		ImPlot::PlotLine(name, data, max, 1, sizeof(float));
	}
	ImPlot::EndPlot();
}
/*
void PieChart(const char* const* sliceNames, const float* data, int numSlices, const char * labelFormat)
{
	if (ImPlot::BeginPlot("Pie Chart"))
	{
		ImPlot::PlotPieChart(sliceNames, data, numSlices, 0.5, 0.5, 0.2, false, labelFormat, 90.0);
	}
	ImPlot::EndPlot();
}
*/
/***********************************************
 \brief     Creates Scatter Plot data display
 \@param name - name of the chart
 \@param xData - x data to display
 \@param yData - y data to display
 \@param numPlots - number of elements in the data arrays
 ***********************************************/
void Scatter(const char* name, float* xData, float* yData, float numPlots)
{
	if (ImPlot::BeginPlot(name))
	{
		ImPlot::PlotScatter(name, xData, yData, numPlots, 0, sizeof(float));
	}
	ImPlot::EndPlot();
}

// shutting down
/***********************************************
 \brief   Shuts down basic ImGui display
 ***********************************************/
void GuiShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImPlot::DestroyContext();
	ImGui::DestroyContext();
}
/***********************************************
 \brief   Shuts down exit ImGui display
 ***********************************************/
void ExitShutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}
/***********************************************
 \brief   Helper function for setting font and creating font slider
 \@param windowScale - ImGui window font
 ***********************************************/
void ScaleFont(float windowScale)
{
	ImGui::SetWindowFontScale(windowScale);
	ImGui::SliderFloat("Font Scale", &windowScale, 0.0f, 4.0f);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------