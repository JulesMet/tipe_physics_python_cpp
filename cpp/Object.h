#pragma once

#include "Vector.h"
#include <array>
#include <string>

using uint = unsigned int;

template <size_t nb_Iterations>
struct Object {
public :
    ldouble mass;

    Object(ldouble _mass, Vec2<ldouble> initial_position, Vec2<ldouble> initial_velocity)
        : mass(_mass)
    {
        positions[0] = initial_position;
        velocities[0] = initial_velocity;
    }


    Vec2<ldouble> GetCurrentPosition() const { return positions[m_Last_index]; }
    Vec2<ldouble> GetCurrentSpeed() const { return positions[m_Last_index]; }

    std::array<Vec2<ldouble>, nb_Iterations> GetPositionsArray() const { return positions; }
    std::array<Vec2<ldouble>, nb_Iterations> GetVelocitiesArray() const { return velocities; }

    void Update_state(Vec2<ldouble> position, Vec2<ldouble> velocity)
    {
        // check if the object is full
        if(m_Last_index > nb_Iterations - 1)
        {
            std::string error_message = std::string("Try accessing the ") +
                                        std::string(m_Last_index + 1) +
                                        std::string("th element while this object size is ") +
                                        std::string(m_Last_index) + std::string('\n');
            throw error_message.c_str();
            return;
        }

        // update the index
        m_Last_index++;

        // update the position
        positions[m_Last_index] = position;

        // update the velocity
        velocities[m_Last_index] = velocity;
    }

private :
    size_t m_Last_index = 0;
    
    std::array<Vec2<ldouble>, nb_Iterations> positions;
    std::array<Vec2<ldouble>, nb_Iterations> velocities;
};