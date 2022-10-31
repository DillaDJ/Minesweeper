#include "GUICreator.h"
#include <iostream>

namespace GUICreator {

    // Open windows
    bool new_game_window = false;
    bool how_to_window = false;
    bool victory_window  = false;

    // Game Variables for GUI
    GameManager::Difficulty mines{ GameManager::Difficulty::easy };
    GameManager::Difficulty size { GameManager::Difficulty::easy };
        
    constexpr ImVec2 tile_size{ 50.f, 50.f };
    
    // Theme
    bool dark_mode { false }; // Toggle Dark Mode

    // Colour Presets
    constexpr ImVec4 white          { 1.f   , 1.f   , 1.f   , 1.f };
    constexpr ImVec4 black          { 0.f   , 0.f   , 0.f   , 1.f };

    // Dark Mode
    constexpr ImVec4 d_primary      { 0.2f  , 0.2f  , 0.2f  , 1.f };
    constexpr ImVec4 d_primary_l    { 0.427f, 0.427f, 0.427f, 1.f };
    constexpr ImVec4 d_primary_d    { 0.106f, 0.106f, 0.106f, 1.f };

    // Light Mode
    constexpr ImVec4 l_primary      { 0.925f, 0.937f, 0.945f, 1.f };
    constexpr ImVec4 l_primary_d    { 0.729f, 0.741f, 0.745f, 1.f };

    // Secondary Colour
    constexpr ImVec4 secondary      { 0.129f, 0.588f, 0.953f, 1.f };
    constexpr ImVec4 secondary_l    { 0.431f, 0.776f, 1.f   , 1.f };
    constexpr ImVec4 secondary_d    { 0.f   , 0.412f, 0.753f, 1.f };

    constexpr ImVec4 explored_color { 0.212f, 0.212f, 0.295f, 1.f };
    constexpr ImVec4 mine_color     { 0.892f, 0.112f, 0.353f, 1.f };
    constexpr ImVec4 flagged_color  { 0.892f, 0.612f, 0.253f, 1.f };

    // Mine Text Colours
    constexpr ImVec4 one_mine_col   { 0.36f , 0.86f , 0.96f , 1.f };
    constexpr ImVec4 two_mine_col   { 0.37f , 0.91f , 0.24f , 1.f };
    constexpr ImVec4 three_mine_col { 0.86f , 0.93f , 0.25f , 1.f };
    constexpr ImVec4 four_mine_col  { 0.97f , 0.56f , 0.13f , 1.f };
    constexpr ImVec4 five_mine_col  { 0.95f , 0.24f , 0.25f , 1.f };
    constexpr ImVec4 six_mine_col   { 0.98f , 0.06f , 0.32f , 1.f };
    constexpr ImVec4 seven_mine_col { 0.96f , 0.27f , 0.78f , 1.f };
    constexpr ImVec4 eight_mine_col { 0.73f , 0.19f , 0.91f , 1.f };

    // Forward Declarations
    void NewGameWindow(bool* p_open);
    void HowToWindow(bool* p_open);
    void VictoryWindow(bool* p_open);
    void AboutWindow(bool* p_open);
    bool ExitWindow(bool* p_open);
    void StyleMainGUI(); 
    bool DrawGUI();
    void DrawBoard();
    const char* GetTileLable(GameManager::TileState state);


    void NewGameWindow(bool* p_open)
    {
        ImGuiWindowFlags new_game_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::Begin("New Game", p_open, new_game_flags);

        ImGui::TextUnformatted("Select Difficulty:");

        using GameManager::Difficulty; // Shorten enum names
        ImGui::Indent();

        if (ImGui::RadioButton("Easy",  mines == Difficulty::easy))    mines = Difficulty::easy;
        if (ImGui::RadioButton("Medium",mines == Difficulty::medium))  mines = Difficulty::medium;
        if (ImGui::RadioButton("Hard",  mines == Difficulty::hard))    mines = Difficulty::hard;

        ImGui::Unindent();

        ImGui::Separator();

        ImGui::TextUnformatted("Select Size:");

        ImGui::Indent();

        if (ImGui::RadioButton("Small  (10x10)", size == Difficulty::easy))    size = Difficulty::easy;
        if (ImGui::RadioButton("Medium (20x20)", size == Difficulty::medium))  size = Difficulty::medium;
        if (ImGui::RadioButton("Big    (40x40)", size == Difficulty::hard))    size = Difficulty::hard;

        ImGui::Unindent();

        ImGui::Separator();

        if (ImGui::Button("Start"))
        {
            GameManager::NewGame(mines, size);
            new_game_window = false;
        }

        ImGui::End();
    }

    void HowToWindow(bool* p_open)
    {



    }

    void VictoryWindow(bool* p_open) 
    {
        ImGuiWindowFlags victory_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize;
        ImGui::GetStyle().WindowBorderSize = 1.f;

        ImGui::Begin("You Win!", p_open, victory_flags);

        ImGui::TextUnformatted("Congratulations!");

        if (ImGui::Button("Play Again"))
        {
            new_game_window = true;
            *p_open = false;
        }

        ImGui::End();
    }

    void AboutWindow(bool* p_open)
    {



    }

    bool ExitWindow(bool* p_open)
    {
        // Are you sure popup

        return true;
    }

    void StyleMainGUI() 
    {
        ImGuiStyle& style{ ImGui::GetStyle() };

        style.WindowBorderSize = 0.0f;
        style.FramePadding = ImVec2(6.f, 6.f);
        style.ItemSpacing = ImVec2(8.f, 4.f);

        // Unary + is overrode to get underlying variable of enums
        if (dark_mode)
        {
            style.Colors[ImGuiCol_Text]         = white;
            style.Colors[ImGuiCol_Border]       = white;
            style.Colors[ImGuiCol_MenuBarBg]    = d_primary;
            style.Colors[ImGuiCol_FrameBg]      = d_primary;
            style.Colors[ImGuiCol_TitleBg]      = d_primary;
            style.Colors[ImGuiCol_TitleBgActive]= d_primary;
            style.Colors[ImGuiCol_WindowBg]     = d_primary_d;
            style.Colors[ImGuiCol_PopupBg]      = d_primary_d;
        }
        else
        {
            style.Colors[ImGuiCol_Text]         = black;
            style.Colors[ImGuiCol_Border]       = black;
            style.Colors[ImGuiCol_MenuBarBg]    = l_primary_d;
            style.Colors[ImGuiCol_FrameBg]      = l_primary_d;
            style.Colors[ImGuiCol_TitleBg]      = l_primary_d;
            style.Colors[ImGuiCol_TitleBgActive]= l_primary_d;
            style.Colors[ImGuiCol_WindowBg]     = l_primary;
            style.Colors[ImGuiCol_PopupBg]      = l_primary;
        }

        style.Colors[ImGuiCol_CheckMark]        = secondary;
        style.Colors[ImGuiCol_Button]           = secondary;
        style.Colors[ImGuiCol_ButtonHovered]    = secondary_l;
        style.Colors[ImGuiCol_ButtonActive]     = secondary_d;
    }
        
    bool DrawGUI() 
    {
        ImGui::ShowDemoWindow();
        bool close = false; // Exit the program if true

        StyleMainGUI();

        // Create menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Menu"))
            {
                if (ImGui::MenuItem("New Game"))                    new_game_window = !new_game_window;
                if (ImGui::MenuItem("Dark Mode", NULL, dark_mode))  dark_mode = !dark_mode;
                if (ImGui::MenuItem("Quit", "Alt + F4"))            new_game_window = !new_game_window;

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("How To Play")) new_game_window = !new_game_window;
                if (ImGui::MenuItem("About"))       new_game_window = !new_game_window;

                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        // Create main window
        static ImGuiWindowFlags main_window_flags{ ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings };

        const ImGuiViewport* viewport{ ImGui::GetMainViewport() };
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);

        if (ImGui::Begin("Main Window", 0, main_window_flags))
        {
            DrawBoard();
        }
        ImGui::End();

        // Open extra windows
        if (new_game_window)    NewGameWindow(&new_game_window);
        if (how_to_window)      HowToWindow(&how_to_window);
        if (victory_window)     VictoryWindow(&victory_window);

        return close;
    }

    void DrawBoard() 
    {
        ImGuiStyle& style{ ImGui::GetStyle() };
        style.ItemSpacing = ImVec2(1.f, 1.f);

        int dimensions{ GameManager::GetDimensions() };
        if (GameManager::GetDimensions() == 0) GameManager::NewGame(mines, size);


        for (int y = 0; y < dimensions; ++y)
        {
            for (int x = 0; x < dimensions; ++x)
            {
                if (x > 0) ImGui::SameLine();

                int id{ y * 10 + x }; // 2D to 1D
                int color_count{ 0 };

                ImGui::PushID(id);
                
                // Color based on mine, explored or untouched
                GameManager::TileState tilestate{ GameManager::GetTileState(id) };

                switch (tilestate)
                {
                    case GameManager::TileState::mine:
                        if (GameManager::IsGameOver())
                        {
                            ImGui::PushStyleColor(ImGuiCol_Button, mine_color);
                            ++color_count;
                        }
                        break;
                    case GameManager::TileState::unexplored:
                        break;
                    case GameManager::TileState::one_adjacent_mine:
                        ImGui::PushStyleColor(ImGuiCol_Text, one_mine_col);
                        break;
                    case GameManager::TileState::two_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, two_mine_col);
                        break;
                    case GameManager::TileState::three_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, three_mine_col);
                        break;
                    case GameManager::TileState::four_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, four_mine_col);
                        break;
                    case GameManager::TileState::five_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, five_mine_col);
                        break;
                    case GameManager::TileState::six_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, six_mine_col);
                        break;
                    case GameManager::TileState::seven_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, seven_mine_col);
                        break;
                    case GameManager::TileState::eight_adjacent_mines:
                        ImGui::PushStyleColor(ImGuiCol_Text, eight_mine_col);
                        break;
                    default:
                        break;
                }

                if (tilestate != GameManager::TileState::mine && tilestate != GameManager::TileState::unexplored)
                {
                    bool text{ tilestate != GameManager::TileState::no_adjacent_mines && tilestate != GameManager::TileState::flagged_tile && tilestate != GameManager::TileState::flagged_mine };
                    
                    if (text) // Pop text color
                        ++color_count;
                    
                    if (tilestate == GameManager::TileState::flagged_tile || tilestate == GameManager::TileState::flagged_mine)
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, flagged_color);
                    }
                    else
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, explored_color);
                    }
                    ++color_count;
                }
                
                // Generate tile
                const char* tile_label = GetTileLable(tilestate);

                if (ImGui::Button(tile_label, tile_size))
                {
                    GameManager::ProcessTile(id);

                    if (GameManager::IsVictory()) victory_window = true;
                }

                // Flag tile (rmb)
                if (ImGui::IsItemClicked(1))
                {
                    GameManager::FlagTile(id);
                }

                // Pop all color styles
                ImGui::PopStyleColor(color_count);
                
                ImGui::PopID();
            }
        }
        
    }

    const char* GetTileLable(GameManager::TileState state)
    {
        const char* lable{};

        switch (state)
        {
            case GameManager::TileState::one_adjacent_mine:
                lable = "1";
                break;
            case GameManager::TileState::two_adjacent_mines:
                lable = "2";
                break;
            case GameManager::TileState::three_adjacent_mines:
                lable = "3";
                break;
            case GameManager::TileState::four_adjacent_mines:
                lable = "4";
                break;
            case GameManager::TileState::five_adjacent_mines:
                lable = "5";
                break;
            case GameManager::TileState::six_adjacent_mines:
                lable = "6";
                break;
            case GameManager::TileState::seven_adjacent_mines:
                lable = "7";
                break;
            case GameManager::TileState::eight_adjacent_mines:
                lable = "8";
                break;
            default:
                lable = "##";
                break;
        }

        return lable;
    }
}