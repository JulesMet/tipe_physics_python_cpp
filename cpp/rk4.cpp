#include <fstream>
//#include <string>
#include <cstdlib>
#include <iostream>

#include "Vector.h"
#include "Object.h"

//////////  Constants

/// @brief the constant of gravitation
constexpr ldouble G = 6.67e-11;

constexpr ldouble PI=3.141592653589793;



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

ldouble periode(ldouble a,ldouble masse_central){
    return sqrt(4*PI*PI*a*a*a/(G*masse_central));
}

ldouble suite_psi(ldouble T,ldouble t,ldouble e,ldouble psi){
    return -(psi-e*sin(psi)-2*PI*t/T)/(1-e*cos(psi))+psi;
}

ldouble newton(ldouble T,ldouble t,ldouble e,ldouble psi){
    ldouble psi_precedent=psi;
    ldouble psi_nouveau=psi+1;  //valeur arbitraire pour entrer dans la boucle
    int i=0;
    while(i<1000 && abs(psi_precedent-psi_nouveau)>0.00001){
        psi_nouveau=suite_psi(T,t,e,psi_precedent);
        i=i+1;
    }
    return psi_nouveau;
}

ldouble conv_psi_en_phi(ldouble e,ldouble psi){
    return 2*atan(abs(tan(psi/2))*sqrt((1+e)/(1-e)));
}

ldouble calcul_rayon(ldouble e,ldouble phi,ldouble p){
    return p/(1+e*cos(phi));
}

void simu(ldouble r1,ldouble r2,ldouble masse_central,int nombre_iteration,ldouble pas, std::ofstream& file_stream){
    ldouble a=(r1+r2)/2;
    ldouble e= abs((r1-r2)/(r1+r2));
    ldouble c=e*a;
    ldouble b=sqrt(a*a - c*c);
    ldouble p=b*b/a;
    ldouble T=periode(a,masse_central);
    ldouble psi;
    ldouble phi;
    ldouble rayon;
    ldouble x,y;
    std::vector<Vec2<ldouble>> polaire; //polaire(phi,rayon)
    std::vector<Vec2<ldouble>> cartesien; //cartesien(x,y)

    polaire.reserve(nombre_iteration);
    cartesien.reserve(nombre_iteration);

    constexpr int step = 1;
    for(int i=0;i<nombre_iteration;i++){
        psi=newton(T,i*pas,e,0);
        phi=conv_psi_en_phi(e,psi);
        rayon=calcul_rayon(e,phi,p);
        polaire.push_back(Vec2<ldouble>(phi,rayon));
        cartesien.push_back(Vec2<ldouble>(rayon*cos(phi),rayon*sin(phi)));
    }

    writeData(file_stream, cartesien);
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


    if(argc == 9)
    {
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
    }
    else if(argc == 6)
    {
        //ldouble r1,ldouble r2,ldouble masse_central,int nombre_iteration,ldouble pas

        /*
        * Argv :
        *   0) name of the command
        *   1) Nombre de jours à simuler
        *   2) timestep in second
        *   3) Masse de l'astre fixe
        *   4) Rayon dbt
        *   5) Rayon fin
        * 
        * */

        char* _stopstring;

        const ldouble pas =                 strtold(argv[2], &_stopstring);     // timestep of the simulation
        const ldouble masse_central =       strtold(argv[3], &_stopstring);     // mass of the sun in kg
        const ldouble r1 =                  strtold(argv[4], &_stopstring);     // Rayon dbt
        const ldouble r2 =                  strtold(argv[5], &_stopstring);     // Rayon fin
        
        const uint nombre_iteration = (strtold(argv[1], &_stopstring) * 24 * 60 * 60) / pas;


        simu(r1, r2, masse_central, nombre_iteration, pas, file_stream);

    }
    else
    {
        // errors, there should have been more parameters send to the program
        std::cout << "Not enough data have been sended to the program !" << std::endl;
        file_stream << "Error - Not enough data";
        file_stream.close();
        return EXIT_FAILURE;
    }
    

    file_stream.close();
    return EXIT_SUCCESS;
}

#endif