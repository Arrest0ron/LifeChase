#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "vmath.hpp"
#include <math.h>

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
     // 5-pixel radius

    float translationZ = -10;
    float translationY = 2;
    float translationX = 0;
    float X_ROTATION;
    float Y_ROTATION;
   

    // dot.setPosition((result.x+1)/2*1920, (1-(result.y+1)/2)*1080); // Set position to (x, y)


    // Main loop to keep the window open
    VM::Matrix T = VM::Matrix::translation(translationX ,translationY,translationZ);
    VM::Matrix RX = VM::Matrix::rotationX(M_PI/60/10);
    VM::Matrix RY = VM::Matrix::rotationY(M_PI/60/10);
    VM::Matrix RZ = VM::Matrix::rotationZ(M_PI/60/10);
    VM::Matrix S = VM::Matrix::scale(10,10,10);
    // VM::Matrix M = T*RZ*RX*RY*S;
    VM::Matrix m1 = VM::Matrix::randomatrix(4);
    
    VM::Matrix m2 = VM::Matrix::randomatrix(4);
    VM::Vector3 tempUp(0,1,0);
    VM::Vector4 cam4 = VM::Vector4(0,0,0,1);
    VM::Vector3 cam = VM::Vector3(cam4.x,cam4.y,cam4.z);
    
    VM::Vector4 targetMDL4 = VM::Vector4(0,0, -1, 1);
    
    
    VM::Vector3 targetMDL = VM::Vector3(targetMDL4.x,targetMDL4.y, targetMDL4.z);
    VM::Vector3 Fv = (cam - targetMDL).normalized();  // camera - target
    VM::Vector3 Rv = VM::Vector3::cross(tempUp, Fv).normalized();
    VM::Vector3 Uv = VM::Vector3::cross(Fv,Rv).normalized();
    VM::Matrix NewMatrix = VM::Matrix::view(Rv, Uv, Fv, cam);
    
    VM::Vector3 target_rd = VM::Vector3(1, -1, -10);
    VM::Vector3 target_lu = VM::Vector3(-1, 1, -10);
    VM::Vector3 target_ld = VM::Vector3(-1, -1, -10);
    VM::Vector3 target_ru = VM::Vector3(1, 1, -10);
    VM::Vector4 target4_rd = S*VM::Vector4(target_rd.x,target_rd.y,target_rd.z,1);
    VM::Vector4 target4_lu = S*VM::Vector4(target_lu.x,target_lu.y,target_lu.z,1);
    VM::Vector4 target4_ld = S*VM::Vector4(target_ld.x,target_ld.y,target_ld.z,1);
    VM::Vector4 target4_ru = S*VM::Vector4(target_ru.x,target_ru.y,target_ru.z,1);
    float t = 0;
    auto lastMousePos =  sf::Mouse::getPosition(window), newMousePos = lastMousePos, mouseDelta = lastMousePos;
    
    window.setVerticalSyncEnabled(true);
    int frames =0;
    int START = 0;
    sf::Mouse::setPosition(sf::Vector2i(1920/2/2, 1080/2), window);

    VM::Matrix rotorY = VM::Matrix::rotationY(0);
    float current_rotationY = 0;

    while (window.isOpen()) {

        

        // Event handling loop
        sf::Event event;
        VM::Vector4 target = rotorY*targetMDL4;
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
                    // if (mouseDelta>=0){X_ROTATION_R += M_PI/60*mouseDelta.x/30;} 
                    // else (X_ROTATION_L += M_PI/60*mouseDelta.x/30;)
                    // X_ROTATION += M_PI/60*mouseDelta.x/30;
                    
                    // if (fabs(X_ROTATION) < M_PI/4)
                    {
                        current_rotationY += M_PI/60*mouseDelta.x/30;
                        rotorY = VM::Matrix::rotationY(current_rotationY);
                        target = rotorY*targetMDL4;
                    }
                    // else
                    // {
                    //     X_ROTATION = M_PI /4;
                    // }
                    // Y_ROTATION += M_PI/60*mouseDelta.y/30;
                    // if (fabs(Y_ROTATION) < M_PI/2)
                    // {
                        // targetMDL4 = VM::Matrix::rotationY(M_PI/60*mouseDelta.y/30)*VM::Vector4(targetMDL4.x,targetMDL4.y, targetMDL4.z, targetMDL4.w);
                    // }

                    // targetMDL = VM::Vector3(targetMDL4.x,targetMDL4.y, targetMDL4.z);
                }
                
            }

          
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            translationZ -= 1.0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            translationZ += 1.0;
        }        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            translationX += 1.0;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            translationX -= 1.0;
        }
        // T = T;
        T = VM::Matrix::translation(translationX,translationY,translationZ);
        

        // M = T*M;


        // t=1;
        // NewMatrix = VM::Matrix::view(Rv, Uv, Fv, cam);
        // R = VM::Matrix::rotationZ(M_PI*t);
        


        // target4_ld = RY*RX*RZ*(target4_ld);
        // target4_lu = RY*RX*RZ*(target4_lu);
        // target4_rd = RY*RX*RZ*(target4_rd);
        // target4_ru = RY*RX*RZ*(target4_ru);

        // значит слушай сюда. нужно вращать чисто вектор направления взгляда (!!!) причем сделать, чтобы сначала вращалось, потом прибавлялась матрица позиции
        // обязательно нужно сделать матрицу движения с учетом частоты кадров, это будет очень понтово.

        VM::Matrix persp = VM::Matrix::perspectiveProjection_90_1();

        Fv = (cam - VM::Vector3(target.x, target.y, target.z)).normalized();  // camera - target
        Rv = VM::Vector3::cross(tempUp, Fv).normalized();
        Uv = VM::Vector3::cross(Fv,Rv).normalized();
        VM::Vector4 VT4 = T*cam4;
        NewMatrix = VM::Matrix::view(Rv, Uv, Fv, VM::Vector3(-VT4.x, -VT4.y, -VT4.z));

        bool drop[4] = {1,1,1,1};

        VM::Vector4 result_rd = persp*NewMatrix*target4_rd;
        if (result_rd.w <= 0){drop[0] = false;}
        result_rd.WNormalize();
        // std::cout << (result_rd.x+1)/2*1920 << " " << (1-(result_rd.y+1)/2)*1080 << " rd\n";
        VM::Vector4 result_lu = persp*NewMatrix*target4_lu;
        if (result_lu.w <= 0){drop[1] = false;}
        result_lu.WNormalize();
        // std::cout << (result_lu.x+1)/2*1920 << " " << (1-(result_lu.y+1)/2)*1080<< " lu\n";
        VM::Vector4 result_ru = persp*NewMatrix*target4_ru;
        if (result_ru.w <= 0){drop[2] = false;}
        // std::cout <<  result_ru.w<<  " w ru\n";
        result_ru.WNormalize();
        // std::cout << (result_ru.x+1)/2*1920 << " " << (1-(result_ru.y+1)/2)*1080<< " ru\n";
        VM::Vector4 result_ld = persp*NewMatrix*target4_ld;
        if (result_ld.w <= 0){drop[3] = false;}
        
        
        result_ld.WNormalize();
        // std::cout << (result_ld.x+1)/2*1920 << " " << (1-(result_ld.y+1)/2)*1080 << "  " << result_ld.w<<  " ld\n";

        sf::VertexArray triangles(sf::PrimitiveType::TriangleStrip, 4);
        
    
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

        

        // Clear the window
        // if (triangles[1].position.x > 1920){triangles[1].position.x = 1920;}
        // if (triangles[2].position.x > 1920){triangles[2].position.x = 1920;}
        // if (triangles[3].position.x > 1920){triangles[3].position.x = 1920;}

        // if (triangles[0].position.y > 1080){triangles[0].position.y = 1080;}
        // if (triangles[1].position.y > 1080){triangles[1].position.y = 1080;}
        // if (triangles[2].position.y > 1080){triangles[2].position.y = 1080;}
        // if (triangles[3].position.y > 1080){triangles[3].position.y = 1080;}

        // if (triangles[0].position.x < 0){triangles[0].position.x = 0;}
        // if (triangles[1].position.x < 0){triangles[1].position.x = 0;}
        // if (triangles[2].position.x < 0){triangles[2].position.x = 0;}
        // if (triangles[3].position.x < 0){triangles[3].position.x = 0;}
        
        // if (triangles[0].position.y < 0){triangles[0].position.y = 0;}
        // if (triangles[1].position.y < 0){triangles[1].position.y= 0;}
        // if (triangles[2].position.y < 0){triangles[2].position.y = 0;}
        // if (triangles[3].position.y < 0){triangles[3].position.y = 0;}

        // if (triangles[0].position.x > 1920){continue;}
        // if (triangles[1].position.x > 1920){continue;}
        // if (triangles[2].position.x > 1920){continue;}
        // if (triangles[3].position.x > 1920){continue;}

        // if (triangles[0].position.y > 1080){continue;}
        // if (triangles[1].position.y > 1080){continue;}
        // if (triangles[2].position.y > 1080){continue;}
        // if (triangles[3].position.y > 1080){continue;}

        // if (triangles[0].position.x < 0){continue;}
        // if (triangles[1].position.x < 0){continue;}
        // if (triangles[2].position.x < 0){continue;}
        // if (triangles[3].position.x < 0){continue;}
        
        // if (triangles[0].position.y < 0){continue;}
        // if (triangles[1].position.y < 0){continue;}
        // if (triangles[2].position.y < 0){continue;}
        // if (triangles[3].position.y < 0){continue;}

        window.clear();

        // Draw the dot
        if (drop[0] && drop[1] && drop[2] && drop[3])
        {
            window.draw(triangles);
        }
        

        // Display the contents of the window
        window.display();
        frames++;
        if (frames>1200){frames =0;}
    }
    return 0;
}
