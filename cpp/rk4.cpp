#include <fstream>
//#include <string>
#include <cstdlib>
#include <iostream>

#include "Vector.h"
#include "Object.h"

//////////  Constants

/// @brief the constant of gravitation
constexpr ldouble G = 6.67e-11;



////////// Structures

struct Object_kinematic_info
{
    Vec2<ldouble> position;
    Vec2<ldouble> velocity;

    Object_kinematic_info(const Vec2<ldouble>& pos, const Vec2<ldouble>& velo)
    : position(pos), velocity(velo)
    {}
};





///////// Functions



void writeData(std::ofstream& file_stream, const std::vector<Vec2<ldouble>>& data) {
    if(!file_stream.is_open())
    {
        std::runtime_error("The file cannot be opened !\n");
        return;
    }

    std::cout << "Starting writing data into the file\n";

    for(auto& pos : data)
    {
        const ldouble x = pos.x;
        const ldouble y = pos.y;

        file_stream << std::to_string(x) << ';' << std::to_string(y) << '\n';
    }

    std::cout << "Data have been writen in the file" << std::endl;
}

Vec2<ldouble> AttractionForce(const Object& source, const Object& target)
{
    const Vec2<ldouble> deplacement_vector = source.GetCurrentPosition() - target.GetCurrentPosition();
    const Vec2<ldouble> force = (G * source.mass * target.mass / deplacement_vector.Magnitude_squared()) * deplacement_vector.Normalised();
    
    return force;
}


void simulation(const size_t nbIteration, const Object& source, Object& target, const ldouble dt, std::ofstream& file_stream)
{
    // Using Euler method
    std::cout << "Starting the simulation...\n";
    for(size_t i = 0; i < nbIteration; i++)
    {
        const Vec2<ldouble> acceleration = AttractionForce(source, target) / target.mass;

        Vec2<ldouble> velocity = target.GetCurrentVelocity() + acceleration * dt * static_cast<ldouble>(0.5f);
        Vec2<ldouble> position = target.GetCurrentPosition() + velocity * dt;
        
        velocity += (dt * static_cast<ldouble>(0.5f)) * acceleration;
        

        target.Update_state(position, velocity);
    }
    std::cout << "Simulation finished.\n";

    writeData(file_stream, target.GetPositionsArray());
}







////// Entry point

#ifndef TESTS
int main(int argc, char** argv) {
    std::cout << "Starting the program ... \n";
    const char* filepath = "simulation_data.log";

    std::ofstream file_stream(filepath, std::fstream::trunc);

    if(!file_stream.is_open())
    {
        std::cout << "Can't open " << filepath << " !\nData have not been generated!" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << filepath << " is open\n";

    if(argc != 9)
    {
        // errors, there should have been more parameters send to the program
        std::cout << "Not enough data have been sended to the program !" << std::endl;
        file_stream << "Error - Not enough data";
        file_stream.close();
        return EXIT_FAILURE;
    }

    std::cout << "the right number of arguments have been passed (argc=" << argc << ")\n";

    /*
    * Argv :
    *   0) name of the command
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

    
    std::cout << "Initialising variables\n";

    char* _stopstring;

    const ldouble timestep =    strtold(argv[2], &_stopstring);     // timestep of the simulation
    const ldouble m_sun =       strtold(argv[3], &_stopstring);     // mass of the sun in kg
    const ldouble m =           strtold(argv[4], &_stopstring);     // mass of the moving planet in kg
    const Vec2<ldouble> initial_position (
                                strtold(argv[5], &_stopstring),     // initial x position
                                strtold(argv[6], &_stopstring));    // initial y position
    const Vec2<ldouble> initial_speed (
                                strtold(argv[7], &_stopstring),     // initial x speed
                                strtold(argv[8], &_stopstring));    // initial y speed
    
    const uint nbIteration = (strtold(argv[1], &_stopstring) * 24 * 60 * 60) / timestep;

    std::cout << "All variables have been initialised :" << std::endl;
    std::cout << "\tNbIteration : " << nbIteration;
    std::cout << "\n\ttimestep : " << timestep;
    std::cout << "\n\tsun's mass : " << m_sun;
    std::cout << "\n\tplanet's mass : " << m;
    std::cout << "\n\tinitial position : " << initial_position;
    std::cout << "\n\tinitial velocity : " << initial_speed << std::endl;


    Object planet(m, initial_position, initial_speed, nbIteration);
    Object sun(m_sun, Vec2<ldouble>(0, 0), Vec2<ldouble>(0,0), nbIteration);

    simulation(nbIteration, sun, planet, timestep, file_stream);

    file_stream.close();
    return EXIT_SUCCESS;
}

#endif