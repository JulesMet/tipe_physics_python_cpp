#include <fstream>
//#include <string>
#include <cstdlib>
#include <iostream>

#include "Vector.h"
#include "Object.h"

//////////  Constants

/// @brief the constant of gravitation
constexpr ldouble G = 6.67e-11;






///////// Functions

template <size_t nb_Iterations>
Vec2<ldouble> AttractionForce(const Object<nb_Iterations>& source, const Object<nb_Iterations>& target)
{
    constexpr Vec2<ldouble> deplacement_vector = source.GetCurrentPosition() - target.GetCurrentPosition();
    constexpr Vec2<ldouble> force = (G * source.mass * target.mass / deplacement_vector.Magnitude_squared()) * deplacement_vector.Normalise();

    return force;
}









////// Entry point

#ifndef TESTS
int main(int argc, char** argv) {
    const char* filepath = "simulation_data.log";

    std::ofstream file_stream(filepath, std::fstream::trunc);

    if(!file_stream.is_open())
    {
        std::cout << "Can't open " << filepath << " !\nData have not been generated!" << std::endl;
        return EXIT_FAILURE;
    }

    if(argc < 1 || argc > 8)
    {
        // errors, there should have been more parameters send to the program
        file_stream << "Error - Not enough data";
        std::cout << "Not enough data have been sended to the program !" << std::endl;
        file_stream.close();
        return EXIT_FAILURE;
    }


    /*
    * Argv :
    *   1) Nombre de jours à simuler
    *   2) timestep in second
    *   3) Masse de l'astre fixe
    *   4) Masse de la planète
    *   5) Position initial en x
    *   6) Position initial en y
    *   7) Vitesse initial en x
    *   8) Vitesse initial en y
    * 
    * */

    char* _stopstring;

    const ldouble timestep =    strtold(argv[1], &_stopstring);     // timestep of the simulation
    const ldouble m_sun =       strtold(argv[2], &_stopstring);     // mass of the sun in kg
    const ldouble m =           strtold(argv[3], &_stopstring);     // mass of the moving planet in kg
    const Vec2<ldouble> initial_position (
                                strtold(argv[4], &_stopstring),     // initial x position
                                strtold(argv[5], &_stopstring));    // initial y position
    const Vec2<ldouble> initial_speed (
                                strtold(argv[6], &_stopstring),     // initial x speed
                                strtold(argv[7], &_stopstring));    // initial y speed
    
    const uint nbIteration = (atoi(argv[0]) * 24 * 60 * 60) / timestep;

    file_stream.close();
    return EXIT_SUCCESS;
}

#endif