#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <random>
#include "data.h"
#include "point.h"
#include "point_collection.h"
#include "interpolation.h"

sf::Color Generate_Random_Color(int seed)
{
    std::mt19937 mt(seed);
    std::uniform_real_distribution<float> dist(0, 254);

    sf::Color randomColor;
    randomColor.r = (sf::Uint8)dist(mt);
    randomColor.g = (sf::Uint8)dist(mt);
    randomColor.b = (sf::Uint8)dist(mt);

    return randomColor;
}

template <typename Functor>
std::vector<sf::Vertex> GeneratePath(float start, float end, sf::Color color, int precision, float scale, Functor f)
{
    std::vector<sf::Vertex> line;

    for(float x = start; x < end; x += (end-start)/precision)
    {
        line.push_back(sf::Vertex(sf::Vector2f(x*scale, (float)f(x)*30), color));
    }

    return line;
}

int main() {
    // Load points
    std::vector<PointCollection> point_collections = data::Load_Points();
    std::vector<bool*> hidden_collection_option;
    bool* selected_item = NULL;


    for(const auto& point_collection : point_collections)
    {
        std::cout << point_collection << std::endl;
        hidden_collection_option.push_back(new bool(true));
    }

    // Start SFML window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16; // Enable anti aliasing

    sf::RenderWindow window(sf::VideoMode(640, 480), "Interpolering", sf::Style::Default, settings);
    window.setFramerateLimit(25);
    ImGui::SFML::Init(window);

    // Create circle for showing points
    sf::CircleShape pointShape(2.f);

    sf::Clock deltaClock;
    while (window.isOpen()) {

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Handle IMGUI
        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Configure");

//        ImGui::BeginCombo("##Yeet", (char*)selected_item, NULL);
//        for (int n = 0; n < hidden_collection_option.size(); n++)
//        {
//            bool is_selected = (selected_item == hidden_collection_option[n]);
//            if (ImGui::Selectable(std::to_string(n).c_str(), *selected_item))
//                selected_item = hidden_collection_option[n];
//            if (is_selected)
//                ImGui::SetItemDefaultFocus();
//            ImGui::EndCombo();
//        }

        for(size_t i = 0; i < hidden_collection_option.size(); i++)
        {
            ImGui::PushStyleColor(ImGuiCol_Text, Generate_Random_Color(i));
            ImGui::Checkbox(std::string("line "+std::to_string(i)).c_str(), hidden_collection_option.at(i));
            ImGui::PopStyleColor();
        }


        ImGui::End();



        // Handle sfml
        window.clear(sf::Color::Black);

        // The datafile allows for multiple pointsets to be drawn, therefore we loop through each one
        for(size_t i = 0; i < point_collections.size(); i++)
        {
            if(*hidden_collection_option.at(i) == false)
                continue;

            // Create color for point
            auto randomColor = Generate_Random_Color(i);

            // Set color of point
            pointShape.setFillColor(randomColor);

            // Draw all points in collection
            for(const auto& p : point_collections.at(i))
            {
                pointShape.setPosition({(float)p.x*30-2, (float)p.y*30-2});
                window.draw(pointShape);
            }

            // Create interpolation models
            interpolation::Linear linear_model(point_collections.at(i));
            interpolation::Polynomial polynomial_model(point_collections.at(i));


            // Draw the models
            auto linearPath = GeneratePath(point_collections.at(i).front().x, point_collections.at(i).back().x, randomColor, 5000, 30, linear_model);
            window.draw(linearPath.data(), linearPath.size(), sf::Lines);

            auto polynomialPath = GeneratePath(point_collections.at(i).front().x, point_collections.at(i).back().x, randomColor, 5000, 30, polynomial_model);
            window.draw(polynomialPath.data(), polynomialPath.size(), sf::Lines);
        }

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}

