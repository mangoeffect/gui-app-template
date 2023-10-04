﻿/******************************************************************************************
*                                                                                         *
*    GUI App Template                                                                     *
*                                                                                         *
*    Copyright (c) 2023 Onur AKIN <https://github.com/onurae>                             *
*    Licensed under the MIT License.                                                      *
*                                                                                         *
******************************************************************************************/

#include "GuiApp.hpp"

class MyApp : public GuiApp
{
public:
    MyApp() : GuiApp("MyApp") {};
    ~MyApp() final = default;

    void Update() override
    {
        switch (1)
        {
        case 1:
            ImGui::ShowDemoWindow();
            break;
        case 2:
            TestBasic();
            break;
        case 3:
            TestDock();
            break;
        case 4:
            ImPlot::ShowDemoWindow();
            break;
        case 5:
            TestLinePlot();
            break;
        default:
            break;
        }
    }

    void TestBasic() const
    {
        ImGui::Begin("Basic", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("Hello, world %d", 123);
        ImGui::Text("This is RobotoMedium %d", 123); // the first loaded font gets used by default
        ImGui::PushFont(fontRobotoRegular); // use ImGui::PushFont()/ImGui::PopFont() to change the font at runtime
        ImGui::Text("This is RobotoRegular %d", 123);
        ImGui::PopFont();
        ImGui::Text(u8"\uefe1 Hello % d", 123);
        ImGui::Text(u8"\uea16 Hello % d", 123);

        ImGui::PushFont(fontLarge);
        ImGui::Text(u8"\uf011 This is RobotoMedium24");
        ImGui::PopFont();

        ImGui::Spacing();
        static float f = 0;
        if (ImGui::Button(u8"\ue1c4 Run")) { f = 0.0f; }
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

        static std::string inputStr = "test";
        ImGui::InputText("std::string", &inputStr);
        ImGui::Text(inputStr.c_str());
        ImGui::End();
    }

    void TestDock()
    {
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGui::Begin("DockSpace", &open, window_flags);
        ImGui::PopStyleVar(3);

        if (ImGui::DockBuilderGetNode(ImGui::GetID("MyDockspace")) == nullptr || redock)
        {
            redock = false;
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockBuilderRemoveNode(dockspace_id); // Clear out existing layout
            ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace); // Add empty node
            ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

            ImGuiID dock_main_id = dockspace_id;
            ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);
            ImGuiID dock_id_left_bottom = ImGui::DockBuilderSplitNode(dock_id_left, ImGuiDir_Down, 0.60f, nullptr, &dock_id_left);
            ImGuiID dock_id_right = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Right, 0.25f, nullptr, &dock_main_id);
            ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, nullptr, &dock_main_id);

            ImGui::DockBuilderDockWindow("View_1", dock_id_left);
            ImGui::DockBuilderDockWindow("View_2", dock_main_id);
            ImGui::DockBuilderDockWindow("View_3", dock_id_right);
            ImGui::DockBuilderDockWindow("View_4", dock_id_left_bottom);
            ImGui::DockBuilderDockWindow("View_5", dock_id_bottom);
            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Redock", nullptr, false, true))
                {
                    redock = true;
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("About"))
            {
                ImGui::MenuItem("https://github.com/onurae", nullptr, true, false);
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        ImGui::End();

        ImGui::Begin("View_1", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Text");
        ImGui::Text("(%.1f FPS)", ImGui::GetIO().Framerate);
        ImGui::End();
        
        ImGui::Begin("View_2", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Text");
        ImGui::End();

        ImGui::Begin("View_3", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Text");
        ImGui::End();

        ImGui::Begin("View_4", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Text");
        ImGui::End();

        ImGui::Begin("View_5", nullptr, ImGuiWindowFlags_None);
        ImGui::Text("Text");
        ImGui::End();
    }

    void TestLinePlot()
    {
        for (int i = 0; i < 1001; ++i)
        {
            xs1[i] = (float)i * 0.001f;
            ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
        }
        for (int i = 0; i < 20; ++i)
        {
            xs2[i] = (float)i / 19.0f;
            ys2[i] = xs2[i] * xs2[i];
        }
        ImGui::SetNextWindowSize(ImVec2(817, 438), ImGuiCond_FirstUseEver);
        ImGui::Begin("Plotter", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (ImPlot::BeginPlot("Line Plots", ImVec2(800, 400), ImPlotFlags_None))
        {
            ImPlot::SetupAxes("x", "y");
            ImPlot::PlotLine("f(x)", xs1, ys1, 1001);
            ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle);
            ImPlot::PlotLine("g(x)", xs2, ys2, 20, ImPlotLineFlags_Segments);
            ImPlot::EndPlot();
        }
        ImGui::End();
    }
private:
    bool open = true;
    bool redock = false;

    float xs1[1001];
    float ys1[1001];
    double xs2[20];
    double ys2[20];
};

int main()
{
    MyApp myApp;
    myApp.Run();
    return 0;
}