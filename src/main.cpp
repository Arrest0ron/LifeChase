#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "vmath.hpp"
#include <stdio.h>

int main() {
    // std::cout << alignof(VM::Matrix);
    
    srand(time(0));
    VM::Vector Point;
    Point.push_back(0);
    Point.push_back(0);
    Point.push_back(0);
    Point.push_back(1);

    // // VM::Matrix Projection = VM::Matrix::perspectiveProjection_90_1_77();
    // VM::Vector4 result = VM::Matrix::perspectiveProjection_90_1_77()*NewMatrix*M*target4;
    // result.WNormalize();
  sf::RenderWindow window(sf::VideoMode({1920, 1080}), "My window");
  window.setMouseCursorGrabbed(true);
  window.setMouseCursorVisible(false);
     // 5-pixel radius

    float translationZ = -10;
    float translationY = 2;
    float translationX = 0;
    float X_ROTATION;
    float Y_ROTATION;
   

    // dot.setPosition((result.x+1)/2*1920, (1-(result.y+1)/2)*1080); // Set position to (x, y)


    // Main loop to keep the window open
    VM::Matrix T = VM::Matrix::translation(translationX ,translationY,translationZ);
    


    VM::Vector3 tempUp(0,1,0);                                // world up pos for evaluation purposes
    VM::Vector4 UserPos (0,0,0,1);                           // initial user position
    VM::Vector4 cam4 = UserPos + VM::Vector4(0,0,0,0);        // camera pos, change second to mov camera relative to the character
    VM::Vector3 cam = VM::Vector3(cam4.x,cam4.y,cam4.z);     // 3D version


    VM::Vector4 target4 = VM::Vector4(0,0, -1, 1);                      //abstract look-at object location
    VM::Vector3 target = VM::Vector3(target4.x,target4.y, target4.z);   // 3D version

    VM::Vector3 Fv = (cam - target).normalized();                     // camera - target results in look-at forward vector.
    VM::Vector3 Rv = VM::Vector3::cross(tempUp, Fv).normalized();     // [world Up x forward look-at] = right look-at vector
    VM::Vector3 Uv = VM::Vector3::cross(Fv,Rv).normalized();          // getting true Up look-at vector
    VM::Matrix NewMatrix = VM::Matrix::view(Rv, Uv, Fv, cam);         // combine them to get View matrix (GLOBAL -> VIEW)
    
    VM::Vector3 target_rd = VM::Vector3( 1, -1, 0);
    VM::Vector3 target_lu = VM::Vector3(-1,  1, 0);        // 3D vectors of cube
    VM::Vector3 target_ld = VM::Vector3(-1, -1, 0);
    VM::Vector3 target_ru = VM::Vector3( 1,  1, 0);

    VM::Matrix S = VM::Matrix::scale(10,10,10);             // Scale vector to increase our little cube!

    VM::Vector4 target4_rd = S*VM::Vector4(target_rd.x,target_rd.y,target_rd.z,1);
    VM::Vector4 target4_lu = S*VM::Vector4(target_lu.x,target_lu.y,target_lu.z,1);
    VM::Vector4 target4_ld = S*VM::Vector4(target_ld.x,target_ld.y,target_ld.z,1);            // 4D, initially scaled
    VM::Vector4 target4_ru = S*VM::Vector4(target_ru.x,target_ru.y,target_ru.z,1);

    VM::Matrix RX = VM::Matrix::rotationX(M_PI/60/1);
    VM::Matrix RY = VM::Matrix::rotationY(M_PI/60/1);        // basic rotations, PI/10 * rad *s^-1   for stable 60 fps
    VM::Matrix RZ = VM::Matrix::rotationZ(M_PI/60/1);  

    auto lastMousePos =  sf::Mouse::getPosition(window), newMousePos = lastMousePos, mouseDelta = lastMousePos;
    
    window.setVerticalSyncEnabled(true);                                   // VSync!
    int frames =0;
    int START = 0;
    sf::Mouse::setPosition(sf::Vector2i(1920/2/2, 1080/2), window);

    VM::Matrix rotorY = VM::Matrix::rotationY(0);
    float current_rotationY = 0;

    
    VM::Matrix MovementTranslation = VM::Matrix::translation(0,0,0);
    sf::Clock clock;
            sf::Font TimesNewRoman;
        TimesNewRoman.loadFromFile("TimesNewRoman.ttf");
    int FPS_VAL = 0; 
        sf::Text FPS;
        FPS.setFont(TimesNewRoman);
        FPS.setFillColor(sf::Color::Red);
        FPS.setPosition(25,25);
        FPS.setCharacterSize(50);

        VM::Matrix persp = VM::Matrix::perspectiveProjection_90_1();
    sf::VertexArray triangles(sf::PrimitiveType::TriangleStrip, 4);

    while (window.isOpen()) {
        
        float moveX=0, moveY =0, moveZ =0;            // ACCURATE - AUTOMATIC MOVEMENT!!!



        

        // Event handling loop
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Close the window if the close event is triggered
            }
            if (event.type == sf::Event::MouseMoved)
            {
                START+=1;
            }
        }
            newMousePos =  sf::Mouse::getPosition(window);
            if (newMousePos!=lastMousePos)
            {
                if (START<10)
                {
                    // START+=1;
                }
                else
                {
                    mouseDelta = lastMousePos - newMousePos;
                    sf::Mouse::setPosition(sf::Vector2i(1920/2/2, 1080/2), window);
                    lastMousePos =sf::Vector2i(1920/2/2, 1080/2);
                    current_rotationY += M_PI/60*mouseDelta.x/30;
                    rotorY = VM::Matrix::rotationY(current_rotationY);
                }
            }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            moveZ -= 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            moveZ += 0.1;
        }        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            moveX += 0.1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            moveX -= 0.1;
        }
        VM::Vector4 movement(moveX,moveY,moveZ,1);
        // std::cout << movement << " uncropped\n";
        movement = rotorY*movement;    
        // std::cout << movement << " cropped\n";s
        movement.normalize();                                            // TODO - add limit to normalize
        UserPos = VM::Vector4(UserPos.x+movement.x, UserPos.y+movement.y, UserPos.z+movement.z); // при желании можно накинуть трансформацию камеры но лучше не надо
        MovementTranslation = VM::Matrix::translation(UserPos.x, UserPos.y, UserPos.z);

        target4_ld = RY*RX*RZ*(target4_ld);
        target4_lu = RY*RX*RZ*(target4_lu);
        target4_rd = RY*RX*RZ*(target4_rd);
        target4_ru = RY*RX*RZ*(target4_ru);

        VM::Vector4 Fv4 = (rotorY *(cam4 - target4));
        Fv = VM::Vector3(Fv4.x, Fv4.y, Fv4.z).normalized();  // camera - target
        Rv = VM::Vector3::cross(tempUp, Fv).normalized();
        Uv = VM::Vector3::cross(Fv,Rv).normalized();
        VM::Vector4 VT4 = MovementTranslation*cam4;
        NewMatrix = VM::Matrix::view(Rv, Uv, Fv, VM::Vector3(-VT4.x, -VT4.y, -VT4.z));


        VM::Vector4 result_rd, result_lu, result_ru, result_ld;
        bool drop = true;
        while (true)
        {
            result_rd = persp*NewMatrix*MovementTranslation * target4_rd;
            if (result_rd.w <= 0){drop = false; break;}
            result_rd.WNormalize();
            // std::cout << (result_rd.x+1)/2*1920 << " " << (1-(result_rd.y+1)/2)*1080 << " rd\n";
            result_lu = persp*NewMatrix*MovementTranslation * target4_lu;
            if (result_lu.w <= 0){drop = false; break;}
            result_lu.WNormalize();
            // std::cout << (result_lu.x+1)/2*1920 << " " << (1-(result_lu.y+1)/2)*1080<< " lu\n";
            result_ru = persp*NewMatrix*MovementTranslation * target4_ru;
            if (result_ru.w <= 0){drop = false; break;}
            // std::cout <<  result_ru.w<<  " w ru\n";
            result_ru.WNormalize();
            // std::cout << (result_ru.x+1)/2*1920 << " " << (1-(result_ru.y+1)/2)*1080<< " ru\n";
            result_ld = persp*NewMatrix*MovementTranslation * target4_ld;
            if (result_ld.w <= 0){drop = false; break;}
            result_ld.WNormalize();
            break;
        }
        
        // std::cout << (result_ld.x+1)/2*1920 << " " << (1-(result_ld.y+1)/2)*1080 << "  " << result_ld.w<<  " ld\n";
        // std::cout << UserPos.z - target4_ld.z<<  " ld\n";
        
        
    
        // Create a circle shape to represent the dot
        triangles[0].color = (sf::Color::Red);
        triangles[1].color = (sf::Color::Blue);
        triangles[2].color = (sf::Color::Green);
        triangles[3].color = (sf::Color::Magenta); // Set color

        triangles[0].position.x = (result_rd.x+1)/2*1920;
        triangles[0].position.y = (1-(result_rd.y+1)/2)*1080;

        triangles[1].position.x = (result_ru.x+1)/2*1920;
        triangles[1].position.y = (1-(result_ru.y+1)/2)*1080;

        triangles[2].position.x = (result_ld.x+1)/2*1920;
        triangles[2].position.y = (1-(result_ld.y+1)/2)*1080;

        triangles[3].position.x = (result_lu.x+1)/2*1920;
        triangles[3].position.y = (1-(result_lu.y+1)/2)*1080;

        
        window.clear();

        // Draw the dot
        if (drop)
        {
            window.draw(triangles);
        }
        
        
        if (frames%120 == 0)
        {
            float a = clock.getElapsedTime().asSeconds();
            if (a){
                FPS_VAL = frames/a;
                
                clock.restart();
                frames =0;
            }

        }
        FPS.setString(std::to_string(FPS_VAL));
        window.draw(FPS);
        

        

        // Display the contents of the window
        window.display();
        frames++;
        
    }
    return 0;
}