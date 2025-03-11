#pragma once

#include "Vector.h"
#include <vector>
#include <string>

using uint = unsigned int;

struct Object {
public :
    ldouble mass;

    Object(ldouble _mass, Vec2<ldouble> initial_position, Vec2<ldouble> initial_velocity, size_t nbIter)
        : mass(_mass), nb_Iterations(nbIter)
    {
        positions.reserve(nbIter);
        velocities.reserve(nbIter);

        positions.emplace_back(initial_position);
        velocities.emplace_back(initial_velocity);
    }


    Vec2<ldouble> GetCurrentPosition() const { return positions[m_Last_index]; }
    Vec2<ldouble> GetCurrentVelocity() const { return velocities[m_Last_index]; }

    std::vector<Vec2<ldouble>> GetPositionsArray() const { return positions; }
    std::vector<Vec2<ldouble>> GetVelocitiesArray() const { return velocities; }

    void Update_state(Vec2<ldouble> position, Vec2<ldouble> velocity)
    {
        // check if the object is full
        if(m_Last_index > nb_Iterations - 1)
        {
            std::string error_message = std::string("Try accessing the ") +
                                        std::to_string(m_Last_index + 1) +
                                        std::string("th element while this object size is ") +
                                        std::to_string(m_Last_index) + std::to_string('\n');
            throw error_message.c_str();
            return;
        }

        // update the index
        m_Last_index++;

        // update the position
        positions.emplace_back(position);

        // update the velocity
        velocities.emplace_back(velocity);
    }

private :
    size_t m_Last_index = 0;
    const size_t nb_Iterations;
    
    std::vector<Vec2<ldouble>> positions;
    std::vector<Vec2<ldouble>> velocities;
};